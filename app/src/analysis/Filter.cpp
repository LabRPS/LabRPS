#include "Filter.h"

#include <gsl/gsl_sort.h>

#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <algorithm>

#include "2Dplot/AxisRect2D.h"
#include "2Dplot/Curve2D.h"
#include "2Dplot/Legend2D.h"
#include "2Dplot/PickerTool2D.h"
#include "2Dplot/Plotcolumns.h"
#include "ColorBox.h"
#include "Table.h"
#include "core/column/Column.h"
using namespace std;

Filter::Filter(ApplicationWindow *parent, AxisRect2D *axisrect, QString name)
    : QObject(parent), app_(parent), axisrect_(axisrect) {
  QObject::setObjectName(name);
  init();
}

Filter::Filter(ApplicationWindow *parent, Table *table, QString name)
    : QObject(parent), app_(parent), d_table(table) {
  QObject::setObjectName(name);
  init();
  d_table = table;
}

void Filter::init() {
  d_n = 0;
  data_ = std::unique_ptr<std::vector<std::pair<double, double>>>(
      new std::vector<std::pair<double, double>>);
  d_curveColorIndex = 1;
  d_tolerance = 1e-4;
  d_points = app_->fitPoints;
  d_max_iterations = 1000;
  associateddata_ = nullptr;
  d_prec = app_->fit_output_precision;
  d_init_err = false;
  d_sort_data = false;
  d_min_points = 2;
  d_explanation = objectName();
}

void Filter::setInterval(double from, double to) {
  if (!associateddata_) {
    QMessageBox::critical(app_, tr("LabRPS") + " - " + tr("Error"),
                          tr("Please assign a curve first!"));
    return;
  }
  setDataFromCurve(associateddata_, from, to);
}

void Filter::setDataCurve(PlotData::AssociatedData *associateddata,
                          double start, double end) {
  if (start > end) qSwap(start, end);

  if (d_n > 0) {  // delete previousely allocated memory
    delete[] d_x;
    delete[] d_y;
  }

  d_init_err = false;
  associateddata_ = associateddata;
  // if (d_sort_data)
  d_n = sortedCurveData(start, end, &d_x, &d_y);
  // else
  // d_n = curveData(start, end, &d_x, &d_y);

  if (!isDataAcceptable()) {
    d_init_err = true;
    return;
  }

  // ensure range is within data range
  if (d_n > 0) {
    d_from = max(start, *min_element(d_x, d_x + d_n));
    d_to = min(end, *max_element(d_x, d_x + d_n));
  }
}

bool Filter::isDataAcceptable() {
  if (d_n < d_min_points) {
    QMessageBox::critical(
        app_, tr("LabRPS") + " - " + tr("Error"),
        tr("You need at least %1 points in order to perform this operation!")
            .arg(d_min_points));
    return false;
  }
  return true;
}

bool Filter::setDataFromCurve(PlotData::AssociatedData *associateddata,
                              AxisRect2D *axisrect) {
  associateddata_ = associateddata;
  if (!associateddata_) {
    d_init_err = true;
    return false;
  }

  bool setminmaxasfromto = true;
  PickerTool2D *picker = axisrect_->getPickerTool();
  if (picker) {
    if (picker->getPicker() == Graph2DCommon::Picker::DataRange) {
      Curve2D *curve = picker->getRangePickerCurve();
      if (curve) {
        QString cname = PlotColumns::getstringfromassociateddata(
            curve->getdatablock_cplot()->getassociateddata());
        if (cname == PlotColumns::getstringfromassociateddata(associateddata)) {
          d_from = picker->getRangePickerLower().first;
          d_to = picker->getRangePickerUpper().first;
          setminmaxasfromto = false;
        }
      }
    }
  }

  if (setminmaxasfromto) {
    d_from = associateddata->minmax.minx;
    d_to = associateddata->minmax.maxx;
  }

  setDataCurve(associateddata, d_from, d_to);
  return true;
}

bool Filter::setDataFromCurve(PlotData::AssociatedData *associateddata,
                              double from, double to, AxisRect2D *axisrect) {
  if (!associateddata) {
    d_init_err = true;
    return false;
  }

  setDataCurve(associateddata, from, to);
  return true;
}

void Filter::setColor(const QString &colorName) {
  QColor c = QColor(colorName);
  if (colorName == "green")
    c = QColor(Qt::green);
  else if (colorName == "darkYellow")
    c = QColor(Qt::darkYellow);
  if (!ColorBox::isValidColor(c)) {
    QMessageBox::critical(app_, tr("Color Name Error"),
                          tr("The color name '%1' is not valid, a default "
                             "color (red) will be used instead!")
                              .arg(colorName));
    d_curveColorIndex = 1;
    return;
  }

  d_curveColorIndex = ColorBox::colorIndex(c);
}

bool Filter::run() {
  if (d_init_err) return false;

  if (d_n < 0) {
    QMessageBox::critical(
        app_, tr("LabRPS") + " - " + tr("Error"),
        tr("You didn't specify a valid data set for this operation!"));
    return false;
  }

  QApplication::setOverrideCursor(Qt::WaitCursor);
  output();  // data analysis and output
  app_->updateLog(logInfo());

  QApplication::restoreOverrideCursor();
  return true;
}

void Filter::output() {
  double *X = new double[d_points];
  double *Y = new double[d_points];

  // do the data analysis
  calculateOutputData(X, Y);
  addResultCurve(X, Y);
}

int Filter::sortedCurveData(double start, double end, double **x, double **y) {
  if (!associateddata_) return 0;
  // start/end finding only works on nondecreasing data, so sort first
  int datasize = (associateddata_->to - associateddata_->from) + 1;
  std::unique_ptr<std::vector<std::pair<double, double>>> temp =
      std::unique_ptr<std::vector<std::pair<double, double>>>(
          new std::vector<std::pair<double, double>>);
  temp->reserve(datasize);
  for (int i = 0; i < datasize; i++) {
    if (!associateddata_->xcol->isInvalid(i) &&
        !associateddata_->ycol->isInvalid(i)) {
      temp->push_back(
          std::pair<double, double>(associateddata_->xcol->valueAt(i),
                                    associateddata_->ycol->valueAt(i)));
    }
  }
  std::stable_sort(temp->begin(), temp->end());

  auto inside_range = [&](const std::pair<double, double> &x) {
    if (std::fabs(std::fabs(x.first) - std::fabs(start)) <
            std::numeric_limits<double>::epsilon() ||
        std::fabs(std::fabs(x.first) - std::fabs(end)) <
            std::numeric_limits<double>::epsilon()) {
      return false;
    } else
      return (x.first < start || x.first > end);
  };

  temp->erase(std::remove_if(temp->begin(), temp->end(), inside_range),
              temp->end());

  datasize = temp->size();
  data_->clear();
  data_->reserve(datasize);
  data_ = std::move(temp);

  (*x) = new double[datasize];
  (*y) = new double[datasize];
  for (int i = 0; i < datasize; i++) {
    (*x)[i] = data_->at(i).first;
    (*y)[i] = data_->at(i).second;
  }

  return datasize;
}

Curve2D *Filter::addResultCurve(double *xdata, double *ydata) {
  const QString tableName = app_->generateUniqueName(this->objectName());
  Column *xCol =
      new Column(tr("1", "filter table x column name"), LabRPS::Numeric);
  Column *yCol =
      new Column(tr("2", "filter table y column name"), LabRPS::Numeric);
  xCol->setPlotDesignation(LabRPS::X);
  yCol->setPlotDesignation(LabRPS::Y);
  for (int i = 0; i < d_points; i++) {
    xCol->setValueAt(i, xdata[i]);
    yCol->setValueAt(i, ydata[i]);
  }

  // first set the values, then add the columns to the table, otherwise, we
  // generate too many undo commands
  QString label = associateddata_->table->name() + "_" +
                  associateddata_->xcol->name() + "_" +
                  associateddata_->ycol->name();
  Table *table = app_->newHiddenTable(
      tableName, d_explanation + " " + tr("of") + " " + label,
      QList<Column *>() << xCol << yCol);
  QList<Axis2D *> xaxes = axisrect_->getXAxes2D();
  QList<Axis2D *> yaxes = axisrect_->getYAxes2D();
  Curve2D *curve = axisrect_->addCurve2DPlot(
      AxisRect2D::LineScatterType::Line2D, table, xCol, yCol, 0,
      xCol->rowCount() - 1, xaxes.at(0), yaxes.at(0));
  curve->setlinestrokecolor_cplot(ColorBox::color(d_curveColorIndex));
  curve->layer()->replot();
  axisrect_->getLegend()->layer()->replot();
  xaxes.at(0)->rescale();
  yaxes.at(0)->rescale();

  delete[] xdata;
  delete[] ydata;
  return curve;
}

Filter::~Filter() {
  if (d_n > 0) {  // delete the memory allocated for the data
    delete[] d_x;
    delete[] d_y;
  }
}
