/***************************************************************************
    File                 : fitclasses.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : MultiPeakFit module with Lorentz and Gauss peak
 shapes

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#include "PreCompiled.h"

#include "MultiPeakFit.h"

#include "MainWindow.h"

#include <QLocale>
#include <QMessageBox>

#include <2Dplot/AxisRect2D.h>
#include <future/core/column/Column.h>

#include "ColorBox.h"
#include "fit_gsl.h"

MultiPeakFit::MultiPeakFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                           PeakProfile profile, int peaks)
    : Fit(parent, axisrect), d_profile(profile) {
  setObjectName(tr("MultiPeak"));

  if (profile == Gauss) {
    d_f = gauss_multi_peak_f;
    d_df = gauss_multi_peak_df;
    d_fdf = gauss_multi_peak_fdf;
    d_fsimplex = gauss_multi_peak_d;
  } else {
    d_f = lorentz_multi_peak_f;
    d_df = lorentz_multi_peak_df;
    d_fdf = lorentz_multi_peak_fdf;
    d_fsimplex = lorentz_multi_peak_d;
  }

  d_param_init = nullptr;
  covar = nullptr;

  setNumPeaks(peaks);

  generate_peak_curves = true;
  d_peaks_color = 2;  // green
}

void MultiPeakFit::setNumPeaks(int n) {
  d_peaks = n;
  if (d_profile == Gauss)
    d_explanation = tr("Gauss Fit");
  else
    d_explanation = tr("Lorentz Fit");
  if (d_peaks > 1)
    d_explanation += QString::fromLatin1("(") + QString::number(d_peaks) + QString::fromLatin1(") ") + tr("multi-peak");

  d_p = 3 * d_peaks + 1;
  d_min_points = d_p;

  if (d_param_init) gsl_vector_free(d_param_init);
  d_param_init = gsl_vector_alloc(static_cast<size_t>(d_p));
  gsl_vector_set_all(d_param_init, 1.0);

  if (covar) gsl_matrix_free(covar);
  covar = gsl_matrix_alloc(static_cast<size_t>(d_p), static_cast<size_t>(d_p));

  d_results.resize(d_p);

  d_param_names = generateParameterList(d_peaks);
  d_param_explain = generateExplanationList(d_peaks);
  d_formula = generateFormula(d_peaks, d_profile);
}

QStringList MultiPeakFit::generateParameterList(int peaks) {
  if (peaks == 1)
    return QStringList() << QString::fromLatin1("A")
                         << QString::fromLatin1("xc")
                         << QString::fromLatin1("w")
                         << QString::fromLatin1("y0");

  QStringList lst;
  for (int i = 0; i < peaks; i++) {
    QString index = QString::number(i + 1);
    lst << QString::fromLatin1("A") + index;
    lst << QString::fromLatin1("xc") + index;
    lst << QString::fromLatin1("w") + index;
  }
  lst << QString::fromLatin1("y0");
  return lst;
}

QStringList MultiPeakFit::generateExplanationList(int peaks) {
  if (peaks == 1)
    return QStringList() << tr("(amplitude)") << tr("(center)") << tr("(width)")
                         << tr("(offset)");

  QStringList lst;
  for (int i = 0; i < peaks; i++) {
    QString index = QString::number(i + 1);
    lst << tr("(amplitude %1)").arg(index);
    lst << tr("(center %1)").arg(index);
    lst << tr("(width %1)").arg(index);
  }
  lst << tr("(offset)");
  return lst;
}

QString MultiPeakFit::generateFormula(int peaks, PeakProfile profile) {
  if (peaks == 1) switch (profile) {
      case Gauss:
        return QString::fromLatin1("y0+A*sqrt(2/PI)/w*exp(-2*((x-xc)/w)^2)");

      case Lorentz:
        return QString::fromLatin1("y0+2*A/PI*w/(4*(x-xc)^2+w^2)");
    }

  QString formula = QString::fromLatin1("y0+");
  for (int i = 0; i < peaks; i++) {
    formula += peakFormula(i + 1, profile);
        if (i < peaks - 1) formula += QString::fromLatin1("+");
  }
  return formula;
}

QString MultiPeakFit::peakFormula(int peakIndex, PeakProfile profile) {
  QString formula;
  QString index = QString::number(peakIndex);
  switch (profile) {
    case Gauss:
      formula += QString::fromLatin1("sqrt(2/PI)*A") + index + QString::fromLatin1("/w") + index;
      formula += QString::fromLatin1("*exp(-2*(x-xc") + index + QString::fromLatin1(")^2/w") + index + QString::fromLatin1("^2)");
      break;
    case Lorentz:
      formula += QString::fromLatin1("2*A") + index + QString::fromLatin1("/PI*w") + index + QString::fromLatin1("/(4*(x-xc") + index +
                 QString::fromLatin1(")^2+w") + index + QString::fromLatin1("^2)");
      break;
  }
  return formula;
}

void MultiPeakFit::guessInitialValues() {
 /* if (d_peaks > 1) return;

  gsl_vector_view x = gsl_vector_view_array(d_x, static_cast<size_t>(d_n));
  gsl_vector_view y = gsl_vector_view_array(d_y, static_cast<size_t>(d_n));

  double min_out, max_out;
  gsl_vector_minmax(&y.vector, &min_out, &max_out);

  if (d_profile == Gauss)
    gsl_vector_set(d_param_init, 0, sqrt(M_2_PI) * (max_out - min_out));
  else if (d_profile == Lorentz)
    gsl_vector_set(d_param_init, 0, 1.0);

  gsl_vector_set(d_param_init, 1,
                 gsl_vector_get(&x.vector, gsl_vector_max_index(&y.vector)));
  gsl_vector_set(d_param_init, 2, 1.0);
  gsl_vector_set(d_param_init, 3, min_out);*///koffa the way
}

void MultiPeakFit::storeCustomFitResults(const std::vector<double> &par) {
  d_results = par;

  if (d_profile == Lorentz) {
    for (int j = 0; j < d_peaks && unsigned(j) < d_results.size(); j++)
      d_results[3 * j] = M_PI_2 * d_results[3 * j];
  }
}

void MultiPeakFit::insertPeakFunctionCurve(double *x, double *y, int peak) {
  /*QString title = app_->generateUniqueName(tr("Peak"));

  QString formula;
  for (int j = 0; j < 3; j++) {
    int p = 3 * peak + j;
    formula += QString::fromLatin1("%1=%2\n")
                   .arg(d_param_names[p])
                   .arg(d_results[p], 0, 'g', d_prec);
  }
  formula += QString::fromLatin1("%1=%2\n\ny0+%3")
                 .arg(d_param_names[d_p - 1])
                 .arg(d_results[d_p - 1], 1, 'g', d_prec)
                 .arg(peakFormula(peak + 1, d_profile));
  app_->addFunctionPlot(0, QStringList() << formula, QString::fromLatin1("x"),
                        QList<double>() << d_x[0] << d_x[d_n - 1], d_points,
                        axisrect_);*///koffa the way
}

void MultiPeakFit::generateFitCurve(const std::vector<double> &par) {
  if (!d_gen_function) d_points = d_n;

  gsl_matrix *m = gsl_matrix_alloc(static_cast<size_t>(d_points),
                                   static_cast<size_t>(d_peaks));
  if (!m) {
    QMessageBox::warning(
        app_, tr("Fit Error"),
        tr("Could not allocate enough memory for the fit curves!"));
    return;
  }

  double *X = new double[static_cast<size_t>(d_points)];
  double *Y = new double[static_cast<size_t>(d_points)];
  int i, j;
  int peaks_aux = d_peaks;
  if (d_peaks == 1) peaks_aux--;

  if (d_gen_function) {
    double step = (d_x[d_n - 1] - d_x[0]) / (d_points - 1);
    for (i = 0; i < d_points; i++) {
      X[i] = d_x[0] + i * step;
      double yi = 0;
      for (j = 0; j < d_peaks; j++) {
        double diff = X[i] - par[3 * j + 1];
        double w = par[3 * j + 2];
        double y_aux = 0;
        if (d_profile == Gauss)
          y_aux +=
              sqrt(M_2_PI) * par[3 * j] / w * exp(-2 * diff * diff / (w * w));
        else
          y_aux += par[3 * j] * w / (4 * diff * diff + w * w);

        yi += y_aux;
        y_aux += par[d_p - 1];
        gsl_matrix_set(m, static_cast<size_t>(i), static_cast<size_t>(j),
                       y_aux);
      }
      Y[i] = yi + par[d_p - 1];  // add offset
    }

    if (d_peaks > 1)
      insertFitFunctionCurve(objectName() + tr("Fit"), X, Y, 2);
    else
      insertFitFunctionCurve(objectName() + tr("Fit"), X, Y);

    if (generate_peak_curves) {
      for (i = 0; i < peaks_aux; i++) {  // add the peak curves
        for (j = 0; j < d_points; j++)
          Y[j] =
              gsl_matrix_get(m, static_cast<size_t>(j), static_cast<size_t>(i));

        insertPeakFunctionCurve(X, Y, i);
      }
    }
  } else {
  } /*{
QString tableName = app_->generateUniqueName(tr("Fit"));
QString label = d_explanation + " " + tr("fit of") + " " +
             associateddata_->table->name() + "_" +
             associateddata_->xcol->name() + "_" +
             associateddata_->ycol->name();

QList<Column *> columns;
columns << new Column(tr("1", "multipeak fit table first column name"),
                   AlphaPlot::Numeric);
for (i = 0; i < peaks_aux; i++)
columns << new Column(tr("peak%1").arg(QString::number(i + 1)),
                     AlphaPlot::Numeric);
columns << new Column(tr("2", "multipeak fit table last column name"),
                   AlphaPlot::Numeric);
Table *t = app_->newHiddenTable(tableName, label, columns);

for (i = 0; i < d_points; i++) {
X[i] = d_x[i];
columns.at(0)->setValueAt(i, X[i]);

double yi = 0;
for (j = 0; j < d_peaks; j++) {
 double diff = X[i] - par[3 * j + 1];
 double w = par[3 * j + 2];
 double y_aux = 0;
 if (d_profile == Gauss)
   y_aux +=
       sqrt(M_2_PI) * par[3 * j] / w * exp(-2 * diff * diff / (w * w));
 else
   y_aux += par[3 * j] * w / (4 * diff * diff + w * w);

 yi += y_aux;
 y_aux += par[d_p - 1];
 columns.at(j + 1)->setValueAt(i, y_aux);
 gsl_matrix_set(m, static_cast<size_t>(i), static_cast<size_t>(j),
                y_aux);
}
Y[i] = yi + par[d_p - 1];  // add offset
if (d_peaks > 1) columns.at(d_peaks + 1)->setValueAt(i, Y[i]);
}

label = tableName + "_2";
Curve2D *curve = axisrect_->addCurve2DPlot(AxisRect2D::LineScatterType::Line2D,
t, ) DataCurve *c = new DataCurve(t, tableName + "_" + columns.at(0)->name(),
label); if (d_peaks > 1) c->setPen(QPen(ColorBox::color(d_curveColorIndex), 2));
else
c->setPen(QPen(ColorBox::color(d_curveColorIndex), 1));
c->setData(X, Y, d_points);
axisrect_->insertPlotItem(c, Graph::Line);
axisrect_->addFitCurve(c);

if (generate_peak_curves) {
for (i = 0; i < peaks_aux; i++) {  // add the peak curves
 for (j = 0; j < d_points; j++)
   Y[j] =
       gsl_matrix_get(m, static_cast<size_t>(j), static_cast<size_t>(i));

 label = tableName + "_" + tr("peak") + QString::number(i + 1);
 c = new DataCurve(t, tableName + "_" + columns.at(0)->name(), label);
 c->setPen(QPen(ColorBox::color(d_peaks_color), 1));
 c->setData(X, Y, d_points);
 axisrect_->insertPlotItem(c, Graph::Line);
 axisrect_->addFitCurve(c);
}
}
}*/

  delete[] X;
  delete[] Y;
  gsl_matrix_free(m);
}

QString MultiPeakFit::logFitInfo(const std::vector<double> &par, int iterations,
                                 int status, const QString &plotName) {
  QString info = Fit::logFitInfo(par, iterations, status, plotName);
  if (d_peaks == 1) return info;

  info += tr("Peak") + QString::fromLatin1("\t") + tr("Area") + QString::fromLatin1("\t");
  info += tr("Center") + QString::fromLatin1("\t") + tr("Width") + QString::fromLatin1("\t") + tr("Height") + QString::fromLatin1("\n");
  info +=
      QString::fromLatin1("------------------------------------------------------------------------"
      "---------------\n");
  for (int j = 0; j < d_peaks; j++) {
    info += QString::number(j + 1) + QString::fromLatin1("\t");
    info += QLocale().toString(par[3 * j], 'g', d_prec) + QString::fromLatin1("\t");
    info += QLocale().toString(par[3 * j + 1], 'g', d_prec) + QString::fromLatin1("\t");
    info += QLocale().toString(par[3 * j + 2], 'g', d_prec) + QString::fromLatin1("\t");

    if (d_profile == Lorentz)
      info += QLocale().toString(M_2_PI * par[3 * j] / par[3 * j + 2], 'g',
                                 d_prec) +
              QString::fromLatin1("\n");
    else
      info += QLocale().toString(sqrt(M_2_PI) * par[3 * j] / par[3 * j + 2],
                                 'g', d_prec) +
              QString::fromLatin1("\n");
  }
  info +=
      QString::fromLatin1("------------------------------------------------------------------------"
      "---------------\n");
  return info;
}

/*****************************************************************************
 *
 * Class LorentzFit
 *
 *****************************************************************************/

LorentzFit::LorentzFit(Gui::MainWindow *parent, AxisRect2D *axisrect)
    : MultiPeakFit(parent, axisrect, MultiPeakFit::Lorentz, 1) {
  init();
}

LorentzFit::LorentzFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                       PlotData::AssociatedData *associateddata)
    : MultiPeakFit(parent, axisrect, MultiPeakFit::Lorentz, 1) {
  init();
  setDataFromCurve(associateddata);
}

LorentzFit::LorentzFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                       PlotData::AssociatedData *associateddata, double start,
                       double end)
    : MultiPeakFit(parent, axisrect, MultiPeakFit::Lorentz, 1) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void LorentzFit::init() {
  setObjectName(QString::fromLatin1("Lorentz"));
  d_explanation = tr("Lorentz");
  d_param_explain << tr("(area)") << tr("(center)") << tr("(width)")
                  << tr("(offset)");
}

/*****************************************************************************
 *
 * Class GaussFit
 *
 *****************************************************************************/

GaussFit::GaussFit(Gui::MainWindow *parent, AxisRect2D *axisrect)
    : MultiPeakFit(parent, axisrect, MultiPeakFit::Gauss, 1) {
  setObjectName(QString::fromLatin1("Gauss"));
  d_explanation = tr("Gauss");
  d_param_explain << tr("(area)") << tr("(center)") << tr("(width)")
                  << tr("(offset)");
}

GaussFit::GaussFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                   PlotData::AssociatedData *associateddata)
    : MultiPeakFit(parent, axisrect, MultiPeakFit::Gauss, 1) {
  init();
  setDataFromCurve(associateddata);
}

GaussFit::GaussFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                   PlotData::AssociatedData *associateddata, double start,
                   double end)
    : MultiPeakFit(parent, axisrect, MultiPeakFit::Gauss, 1) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void GaussFit::init() {
  setObjectName(QString::fromLatin1("Gauss"));
  d_explanation = tr("Gauss");
  d_param_explain << tr("(area)") << tr("(center)") << tr("(width)")
                  << tr("(offset)");
}

/*****************************************************************************
 *
 * Class GaussAmpFit
 *
 *****************************************************************************/

GaussAmpFit::GaussAmpFit(Gui::MainWindow *parent, AxisRect2D *axisrect)
    : Fit(parent, axisrect) {
  init();
}

GaussAmpFit::GaussAmpFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                         PlotData::AssociatedData *associateddata)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata);
}

GaussAmpFit::GaussAmpFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                         PlotData::AssociatedData *associateddata, double start,
                         double end)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void GaussAmpFit::init() {
  setObjectName(QString::fromLatin1("GaussAmp"));
  d_f = gauss_f;
  d_df = gauss_df;
  d_fdf = gauss_fdf;
  d_fsimplex = gauss_d;
  d_p = 4;
  d_min_points = d_p;
  d_param_init = gsl_vector_alloc(static_cast<size_t>(d_p));
  gsl_vector_set_all(d_param_init, 1.0);
  covar = gsl_matrix_alloc(static_cast<size_t>(d_p), static_cast<size_t>(d_p));
  d_results.resize(d_p);
  d_param_explain << tr("(offset)") << tr("(height)") << tr("(center)")
                  << tr("(width)");
  d_param_names << QString::fromLatin1("y0")
                << QString::fromLatin1("A")
                << QString::fromLatin1("xc")
                << QString::fromLatin1("w");
  d_explanation = tr("GaussAmp Fit");
  d_formula = QString::fromLatin1("y0+A*exp(-(x-xc)^2/(2*w^2))");
}

void GaussAmpFit::calculateFitCurveData(const std::vector<double> &par,
                                        double *X, double *Y) {
  double w2 = par[3] * par[3];
  if (d_gen_function) {
    double X0 = d_x[0];
    double step = (d_x[d_n - 1] - X0) / (d_points - 1);
    for (int i = 0; i < d_points; i++) {
      X[i] = X0 + i * step;
      double diff = X[i] - par[2];
      Y[i] = par[1] * exp(-0.5 * diff * diff / w2) + par[0];
    }
  } else {
    for (int i = 0; i < d_points; i++) {
      X[i] = d_x[i];
      double diff = X[i] - par[2];
      Y[i] = par[1] * exp(-0.5 * diff * diff / w2) + par[0];
    }
  }
}
