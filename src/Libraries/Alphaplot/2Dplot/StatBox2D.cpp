#include "Precompiled.h"

#include "StatBox2D.h"

#include <gsl/gsl_sort.h>
#include <gsl/gsl_statistics.h>

#include "Axis2D.h"
#include "PickerTool2D.h"
#include "Table.h"
#include "core/IconLoader.h"
#include "core/Utilities.h"
#include "future/core/column/Column.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"

StatBox2D::StatBox2D(BoxWhiskerData boxWhiskerData, Axis2D *xAxis,
                     Axis2D *yAxis)
    : QCPStatisticalBox(xAxis, yAxis),
      xAxis_(xAxis),
      yAxis_(yAxis),
      layername_(QString::fromLatin1("<StatBox2D>") + QDateTime::currentDateTime().toString(
                                              QString::fromLatin1("yyyy:MM:dd:hh:mm:ss:zzz"))),
      boxwhiskerdata_(boxWhiskerData),
      sBoxdata_(
          std::unique_ptr<QCPStatisticalBoxData>(new QCPStatisticalBoxData)),
      scatter_(Scatter::Outliers),
      scatterstyle_(new QCPScatterStyle(
          QCPScatterStyle::ssDisc,
          Utilities::getRandColorGoldenRatio(Utilities::ColorPal::Dark),
          Utilities::getRandColorGoldenRatio(Utilities::ColorPal::Dark), 6.0)),
      boxstyle_(StatBox2D::BoxWhiskerStyle::Perc_25_75),
      whiskerstyle_(StatBox2D::BoxWhiskerStyle::IQR_1_5_auto) {
  // setting icon
    icon_ = IconLoader::load(QString::fromLatin1("graph2d-box"), IconLoader::LightDark);

  QThread::msleep(1);
  parentPlot()->addLayer(layername_, xAxis_->layer(), QCustomPlot::limBelow);
  setLayer(layername_);
  layer()->setMode(QCPLayer::LayerMode::lmBuffered);
  setWhiskerAntialiased(false);
  setAntialiasedFill(false);
  setAntialiased(false);
  setOutlierStyle(*scatterstyle_);
  setfillcolor_statbox(
      Utilities::getRandColorGoldenRatio(Utilities::ColorPal::Light));
  setboxwhiskerdata(boxWhiskerData);
}

StatBox2D::~StatBox2D() {
  delete scatterstyle_;
  parentPlot()->removeLayer(layer());
}

Axis2D *StatBox2D::getxaxis() const { return xAxis_; }

Axis2D *StatBox2D::getyaxis() const { return yAxis_; }

StatBox2D::BoxWhiskerStyle StatBox2D::getboxstyle_statbox() const {
  return boxstyle_;
}

StatBox2D::BoxWhiskerStyle StatBox2D::getwhiskerstyle_statbox() const {
  return whiskerstyle_;
}

QColor StatBox2D::getfillcolor_statbox() const { return brush().color(); }

Qt::BrushStyle StatBox2D::getfillstyle_statbox() const {
  return brush().style();
}

bool StatBox2D::getfillstatus_statbox() const {
  if (brush().style() == Qt::NoBrush) {
    return false;
  } else {
    return true;
  }
}

Qt::PenStyle StatBox2D::getwhiskerstrokestyle_statbox() const {
  return whiskerPen().style();
}

QColor StatBox2D::getwhiskerstrokecolor_statbox() const {
  return whiskerPen().color();
}

double StatBox2D::getwhiskerstrokethickness_statbox() const {
  return whiskerPen().widthF();
}

Qt::PenStyle StatBox2D::getwhiskerbarstrokestyle_statbox() const {
  return whiskerBarPen().style();
}

QColor StatBox2D::getwhiskerbarstrokecolor_statbox() const {
  return whiskerBarPen().color();
}

double StatBox2D::getwhiskerbarstrokethickness_statbox() const {
  return whiskerBarPen().widthF();
}

Qt::PenStyle StatBox2D::getmedianstrokestyle_statbox() const {
  return medianPen().style();
}

QColor StatBox2D::getmedianstrokecolor_statbox() const {
  return medianPen().color();
}

double StatBox2D::getmedianstrokethickness_statbox() const {
  return medianPen().widthF();
}

Graph2DCommon::ScatterStyle StatBox2D::getscattershape_statbox() const {
  Graph2DCommon::ScatterStyle scatterstyle;
  switch (outlierStyle().shape()) {
    case QCPScatterStyle::ssNone:
      scatterstyle = Graph2DCommon::ScatterStyle::None;
      break;
    case QCPScatterStyle::ssDot:
      scatterstyle = Graph2DCommon::ScatterStyle::Dot;
      break;
    case QCPScatterStyle::ssCross:
      scatterstyle = Graph2DCommon::ScatterStyle::Cross;
      break;
    case QCPScatterStyle::ssPlus:
      scatterstyle = Graph2DCommon::ScatterStyle::Plus;
      break;
    case QCPScatterStyle::ssCircle:
      scatterstyle = Graph2DCommon::ScatterStyle::Circle;
      break;
    case QCPScatterStyle::ssDisc:
      scatterstyle = Graph2DCommon::ScatterStyle::Disc;
      break;
    case QCPScatterStyle::ssSquare:
      scatterstyle = Graph2DCommon::ScatterStyle::Square;
      break;
    case QCPScatterStyle::ssDiamond:
      scatterstyle = Graph2DCommon::ScatterStyle::Diamond;
      break;
    case QCPScatterStyle::ssStar:
      scatterstyle = Graph2DCommon::ScatterStyle::Star;
      break;
    case QCPScatterStyle::ssTriangle:
      scatterstyle = Graph2DCommon::ScatterStyle::Triangle;
      break;
    case QCPScatterStyle::ssTriangleInverted:
      scatterstyle = Graph2DCommon::ScatterStyle::TriangleInverted;
      break;
    case QCPScatterStyle::ssCrossSquare:
      scatterstyle = Graph2DCommon::ScatterStyle::CrossSquare;
      break;
    case QCPScatterStyle::ssPlusSquare:
      scatterstyle = Graph2DCommon::ScatterStyle::PlusSquare;
      break;
    case QCPScatterStyle::ssCrossCircle:
      scatterstyle = Graph2DCommon::ScatterStyle::CrossCircle;
      break;
    case QCPScatterStyle::ssPlusCircle:
      scatterstyle = Graph2DCommon::ScatterStyle::PlusCircle;
      break;
    case QCPScatterStyle::ssPeace:
      scatterstyle = Graph2DCommon::ScatterStyle::Peace;
      break;
    case QCPScatterStyle::ssCustom:
    case QCPScatterStyle::ssPixmap:
      qDebug() << "QCPScatterStyle::ssCustom & QCPScatterStyle::ssPixmap "
                  "unsupported! using QCPScatterStyle::ssDisc insted";
      scatterstyle = Graph2DCommon::ScatterStyle::Disc;
      break;
  }
  return scatterstyle;
}

QColor StatBox2D::getscatterfillcolor_statbox() const {
  return outlierStyle().brush().color();
}

double StatBox2D::getscattersize_statbox() const {
  return outlierStyle().size();
}

Qt::PenStyle StatBox2D::getscatterstrokestyle_statbox() const {
  return outlierStyle().pen().style();
}

QColor StatBox2D::getscatterstrokecolor_statbox() const {
  return outlierStyle().pen().color();
}

double StatBox2D::getscatterstrokethickness_statbox() const {
  return outlierStyle().pen().widthF();
}

void StatBox2D::setxaxis_statbox(Axis2D *axis) {
  Q_ASSERT(axis->getorientation_axis() == Axis2D::AxisOreantation::Bottom ||
           axis->getorientation_axis() == Axis2D::AxisOreantation::Top);
  if (axis == getxaxis()) return;

  xAxis_ = axis;
  setKeyAxis(axis);
}

void StatBox2D::setyaxis_statbox(Axis2D *axis) {
  Q_ASSERT(axis->getorientation_axis() == Axis2D::AxisOreantation::Left ||
           axis->getorientation_axis() == Axis2D::AxisOreantation::Right);
  if (axis == getyaxis()) return;

  yAxis_ = axis;
  setValueAxis(axis);
}

void StatBox2D::setboxwhiskerdata(const BoxWhiskerData boxWhiskerData) {
  boxwhiskerdata_ = boxWhiskerData;
  sBoxdata_->key = boxWhiskerData.key;
  sBoxdata_->median = boxWhiskerData.median;
  setboxstyle_statbox(boxstyle_);
  setwhiskerstyle_statbox(whiskerstyle_);
  setOutliers();
  data().data()->clear();
  addData(sBoxdata_->key, sBoxdata_->minimum, sBoxdata_->lowerQuartile,
          sBoxdata_->median, sBoxdata_->upperQuartile, sBoxdata_->maximum,
          sBoxdata_->outliers);
}

void StatBox2D::setboxstyle_statbox(
    const StatBox2D::BoxWhiskerStyle &boxStyle) {
  switch (boxStyle) {
    case BoxWhiskerStyle::SD:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.sd_lower;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.sd_upper;
      break;
    case BoxWhiskerStyle::SE:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.se_lower;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.se_upper;
      break;
    case BoxWhiskerStyle::Perc_25_75:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_25;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_75;
      break;
    case BoxWhiskerStyle::Perc_10_90:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_10;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_90;
      break;
    case BoxWhiskerStyle::Perc_5_95:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_5;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_95;
      break;
    case BoxWhiskerStyle::Perc_1_99:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_1;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_99;
      break;
    case BoxWhiskerStyle::MinMax:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.min;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.max;
      break;
    case BoxWhiskerStyle::Constant:
      sBoxdata_->lowerQuartile =
          boxwhiskerdata_.boxWhiskerDataBounds.constant_lower;
      sBoxdata_->upperQuartile =
          boxwhiskerdata_.boxWhiskerDataBounds.constant_upper;
      break;
    default:
      sBoxdata_->lowerQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_25;
      sBoxdata_->upperQuartile = boxwhiskerdata_.boxWhiskerDataBounds.perc_75;
      break;
  }
  boxstyle_ = boxStyle;
  if (whiskerstyle_ == BoxWhiskerStyle::IQR_1_5_auto)
    setwhiskerstyle_statbox(whiskerstyle_);
  setOutliers();
  data().data()->clear();
  addData(sBoxdata_->key, sBoxdata_->minimum, sBoxdata_->lowerQuartile,
          sBoxdata_->median, sBoxdata_->upperQuartile, sBoxdata_->maximum,
          sBoxdata_->outliers);
}

void StatBox2D::setOutliers() {
  double q1 = sBoxdata_->lowerQuartile;
  double q2 = sBoxdata_->upperQuartile;
  double iqr = q2 - q1;
  double lowerq_range = q1 - (iqr * 1.5);
  double upperq_range = q2 + (iqr * 1.5);
  Column *col = boxwhiskerdata_.column_;
  int from = boxwhiskerdata_.from_;
  int to = boxwhiskerdata_.to_;
  sBoxdata_->outliers.clear();
  if (scatter_ == Scatter::Outliers) {
    if (lowerq_range > boxwhiskerdata_.boxWhiskerDataBounds.min ||
        upperq_range < boxwhiskerdata_.boxWhiskerDataBounds.max) {
      for (int i = 0, row = from; row <= to; row++) {
        if (!col->isInvalid(row)) {
          double data = std::numeric_limits<double>::quiet_NaN();
          data = col->valueAt(row);
          if (lowerq_range > data || upperq_range < data)
            sBoxdata_->outliers << data;
        }
        i++;
      }
    }
  } else if (scatter_ == Scatter::All) {
    for (int i = 0, row = from; row <= to; row++) {
      if (!col->isInvalid(row)) {
        double data = std::numeric_limits<double>::quiet_NaN();
        data = col->valueAt(row);
        sBoxdata_->outliers << data;
      }
      i++;
    }
  } else if (scatter_ == Scatter::MinMax) {
    sBoxdata_->outliers << boxwhiskerdata_.boxWhiskerDataBounds.min
                        << boxwhiskerdata_.boxWhiskerDataBounds.max;
  } else if (scatter_ == Scatter::None) {
    sBoxdata_->outliers.clear();
  }
}

void StatBox2D::setOutlierScatter(const Scatter &scatter) {
  scatter_ = scatter;
  setOutliers();
  data().data()->clear();
  addData(sBoxdata_->key, sBoxdata_->minimum, sBoxdata_->lowerQuartile,
          sBoxdata_->median, sBoxdata_->upperQuartile, sBoxdata_->maximum,
          sBoxdata_->outliers);
}

void StatBox2D::setwhiskerstyle_statbox(
    const StatBox2D::BoxWhiskerStyle &whiskerStyle) {
  switch (whiskerStyle) {
    case BoxWhiskerStyle::SD:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.sd_lower;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.sd_upper;
      break;
    case BoxWhiskerStyle::SE:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.se_lower;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.se_upper;
      break;
    case BoxWhiskerStyle::Perc_25_75:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.perc_25;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.perc_75;
      break;
    case BoxWhiskerStyle::Perc_10_90:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.perc_10;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.perc_90;
      break;
    case BoxWhiskerStyle::Perc_5_95:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.perc_5;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.perc_95;
      break;
    case BoxWhiskerStyle::Perc_1_99:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.perc_1;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.perc_99;
      break;
    case BoxWhiskerStyle::MinMax:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.min;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.max;
      break;
    case BoxWhiskerStyle::Constant:
      sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.constant_lower;
      sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.constant_upper;
      break;
    case BoxWhiskerStyle::IQR_1_5_auto: {
      double q1 = sBoxdata_->lowerQuartile;
      double q2 = sBoxdata_->upperQuartile;
      double iqr = q2 - q1;
      double lowerq_range = q1 - (iqr * 1.5);
      double upperq_range = q2 + (iqr * 1.5);
      if (lowerq_range <= boxwhiskerdata_.boxWhiskerDataBounds.min)
        sBoxdata_->minimum = boxwhiskerdata_.boxWhiskerDataBounds.min;
      else {
        qDebug() << "entering IQR";
        double min = boxwhiskerdata_.boxWhiskerDataBounds.max;
        Column *col = boxwhiskerdata_.column_;
        int from = boxwhiskerdata_.from_;
        int to = boxwhiskerdata_.to_;
        for (int i = 0, row = from; row <= to; row++) {
          if (!col->isInvalid(row)) {
            double data = std::numeric_limits<double>::quiet_NaN();
            data = col->valueAt(row);
            if (data > lowerq_range)
              if (data < min) {
                min = data;
              }
          }
          i++;
        }
        sBoxdata_->minimum = min;
      }

      if (upperq_range >= boxwhiskerdata_.boxWhiskerDataBounds.max)
        sBoxdata_->maximum = boxwhiskerdata_.boxWhiskerDataBounds.max;
      else {
        double max = boxwhiskerdata_.boxWhiskerDataBounds.min;
        Column *col = boxwhiskerdata_.column_;
        int from = boxwhiskerdata_.from_;
        int to = boxwhiskerdata_.to_;
        for (int i = 0, row = from; row <= to; row++) {
          if (!col->isInvalid(row)) {
            double data = std::numeric_limits<double>::quiet_NaN();
            data = col->valueAt(row);
            if (data < upperq_range)
              if (data > max) max = data;
          }
          i++;
        }
        sBoxdata_->maximum = max;
      }
    } break;
  }
  whiskerstyle_ = whiskerStyle;
  data().data()->clear();
  addData(sBoxdata_->key, sBoxdata_->minimum, sBoxdata_->lowerQuartile,
          sBoxdata_->median, sBoxdata_->upperQuartile, sBoxdata_->maximum,
          sBoxdata_->outliers);
}

void StatBox2D::setfillcolor_statbox(const QColor &color) {
  QBrush b = brush();
  b.setColor(color);
  setBrush(b);
}

void StatBox2D::setfillstyle_statbox(const Qt::BrushStyle &style) {
  QBrush b = brush();
  if (b.style() != Qt::BrushStyle::NoBrush) {
    b.setStyle(style);
    setBrush(b);
  }
}

void StatBox2D::setfillstatus_statbox(const bool status) {
  if (status) {
    QBrush b = brush();
    b.setStyle(Qt::SolidPattern);
    setBrush(b);
  } else {
    QBrush b = brush();
    b.setStyle(Qt::NoBrush);
    setBrush(b);
  }
}

void StatBox2D::setwhiskerstrokestyle_statbox(const Qt::PenStyle &style) {
  QPen p = whiskerPen();
  p.setStyle(style);
  setWhiskerPen(p);
}

void StatBox2D::setwhiskerstrokecolor_statbox(const QColor &color) {
  QPen p = whiskerPen();
  p.setColor(color);
  setWhiskerPen(p);
}

void StatBox2D::setwhiskerstrokethickness_statbox(const double value) {
  QPen p = whiskerPen();
  p.setWidthF(value);
  setWhiskerPen(p);
}

void StatBox2D::setwhiskerbarstrokestyle_statbox(const Qt::PenStyle &style) {
  QPen p = whiskerBarPen();
  p.setStyle(style);
  setWhiskerBarPen(p);
}

void StatBox2D::setwhiskerbarstrokecolor_statbox(const QColor &color) {
  QPen p = whiskerBarPen();
  p.setColor(color);
  setWhiskerBarPen(p);
}

void StatBox2D::setwhiskerbarstrokethickness_statbox(const double value) {
  QPen p = whiskerBarPen();
  p.setWidthF(value);
  setWhiskerBarPen(p);
}

void StatBox2D::setmedianstrokestyle_statbox(const Qt::PenStyle &style) {
  QPen p = medianPen();
  p.setStyle(style);
  setMedianPen(p);
}

void StatBox2D::setmedianstrokecolor_statbox(const QColor &color) {
  QPen p = medianPen();
  p.setColor(color);
  setMedianPen(p);
}

void StatBox2D::setmedianstrokethickness_statbox(const double value) {
  QPen p = medianPen();
  p.setWidthF(value);
  setMedianPen(p);
}

void StatBox2D::setscattershape_statbox(
    const Graph2DCommon::ScatterStyle &shape) {
  switch (shape) {
    case Graph2DCommon::ScatterStyle::None:
      scatterstyle_->setShape(QCPScatterStyle::ssNone);
      break;
    case Graph2DCommon::ScatterStyle::Dot:
      scatterstyle_->setShape(QCPScatterStyle::ssDot);
      break;
    case Graph2DCommon::ScatterStyle::Cross:
      scatterstyle_->setShape(QCPScatterStyle::ssCross);
      break;
    case Graph2DCommon::ScatterStyle::Plus:
      scatterstyle_->setShape(QCPScatterStyle::ssPlus);
      break;
    case Graph2DCommon::ScatterStyle::Circle:
      scatterstyle_->setShape(QCPScatterStyle::ssCircle);
      break;
    case Graph2DCommon::ScatterStyle::Disc:
      scatterstyle_->setShape(QCPScatterStyle::ssDisc);
      break;
    case Graph2DCommon::ScatterStyle::Square:
      scatterstyle_->setShape(QCPScatterStyle::ssSquare);
      break;
    case Graph2DCommon::ScatterStyle::Diamond:
      scatterstyle_->setShape(QCPScatterStyle::ssDiamond);
      break;
    case Graph2DCommon::ScatterStyle::Star:
      scatterstyle_->setShape(QCPScatterStyle::ssStar);
      break;
    case Graph2DCommon::ScatterStyle::Triangle:
      scatterstyle_->setShape(QCPScatterStyle::ssTriangle);
      break;
    case Graph2DCommon::ScatterStyle::TriangleInverted:
      scatterstyle_->setShape(QCPScatterStyle::ssTriangleInverted);
      break;
    case Graph2DCommon::ScatterStyle::CrossSquare:
      scatterstyle_->setShape(QCPScatterStyle::ssCrossSquare);
      break;
    case Graph2DCommon::ScatterStyle::PlusSquare:
      scatterstyle_->setShape(QCPScatterStyle::ssPlusSquare);
      break;
    case Graph2DCommon::ScatterStyle::CrossCircle:
      scatterstyle_->setShape(QCPScatterStyle::ssCrossCircle);
      break;
    case Graph2DCommon::ScatterStyle::PlusCircle:
      scatterstyle_->setShape(QCPScatterStyle::ssPlusCircle);
      break;
    case Graph2DCommon::ScatterStyle::Peace:
      scatterstyle_->setShape(QCPScatterStyle::ssPeace);
      break;
  }
  setOutlierStyle(*scatterstyle_);
}

void StatBox2D::setscatterfillcolor_statbox(const QColor &color) {
  QBrush b = scatterstyle_->brush();
  b.setColor(color);
  scatterstyle_->setBrush(b);
  setOutlierStyle(*scatterstyle_);
}

void StatBox2D::setscattersize_statbox(const double value) {
  scatterstyle_->setSize(value);
  setOutlierStyle(*scatterstyle_);
}

void StatBox2D::setscatterstrokestyle_statbox(const Qt::PenStyle &style) {
  QPen p = scatterstyle_->pen();
  p.setStyle(style);
  scatterstyle_->setPen(p);
  setOutlierStyle(*scatterstyle_);
}

void StatBox2D::setscatterstrokecolor_statbox(const QColor &color) {
  QPen p = scatterstyle_->pen();
  p.setColor(color);
  scatterstyle_->setPen(p);
  setOutlierStyle(*scatterstyle_);
}

void StatBox2D::setscatterstrokethickness_statbox(const double value) {
  QPen p = scatterstyle_->pen();
  p.setWidthF(value);
  scatterstyle_->setPen(p);
  setOutlierStyle(*scatterstyle_);
}

void StatBox2D::setlegendtext_statbox(const QString name) {
  QSharedPointer<QCPAxisTickerText> textTicker =
      qSharedPointerCast<QCPAxisTickerText>(getxaxis()->getticker_axis());
  boxwhiskerdata_.name = name;
  textTicker->addTick(boxwhiskerdata_.key, boxwhiskerdata_.name);
  getxaxis()->setTicker(textTicker);
  setName(boxwhiskerdata_.name);
}

void StatBox2D::save(XmlStreamWriter *xmlwriter, int xaxis, int yaxis) {
  xmlwriter->writeStartElement(QString::fromLatin1("statbox"));
  // axis
  xmlwriter->writeAttribute(QString::fromLatin1("xaxis"), QString::number(xaxis));
  xmlwriter->writeAttribute(QString::fromLatin1("yaxis"), QString::number(yaxis));
  xmlwriter->writeAttribute(QString::fromLatin1("legend"), name());
  // data
  xmlwriter->writeAttribute(QString::fromLatin1("table"), boxwhiskerdata_.table_->name());
  xmlwriter->writeAttribute(QString::fromLatin1("column"), boxwhiskerdata_.column_->name());
  xmlwriter->writeAttribute(QString::fromLatin1("from"), QString::number(boxwhiskerdata_.from_));
  xmlwriter->writeAttribute(QString::fromLatin1("to"), QString::number(boxwhiskerdata_.to_));
  xmlwriter->writeAttribute(QString::fromLatin1("key"), QString::number(boxwhiskerdata_.key));

  // box
  xmlwriter->writeStartElement(QString::fromLatin1("box"));
  (getfillstatus_statbox()) ? xmlwriter->writeAttribute(QString::fromLatin1("fill"), QString::fromLatin1("true"))
                            : xmlwriter->writeAttribute(QString::fromLatin1("fill"), QString::fromLatin1("true"));
  (antialiased()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("true"))
                  : xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("false"));
  (antialiasedFill()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialiasfill"), QString::fromLatin1("true"))
                      : xmlwriter->writeAttribute(QString::fromLatin1("antialiasfill"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("width"), QString::number(width()));

  switch (getboxstyle_statbox()) {
    case StatBox2D::BoxWhiskerStyle::SE:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("se"));
      break;
    case StatBox2D::BoxWhiskerStyle::SD:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("sd"));
      break;
    case StatBox2D::BoxWhiskerStyle::MinMax:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("minmax"));
      break;
    case StatBox2D::BoxWhiskerStyle::Constant:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("constant"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_1_99:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("perc_1_99"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_5_95:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("perc_5_95"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_10_90:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("perc_10_90"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_25_75:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("perc_25_75"));
      break;
    case StatBox2D::BoxWhiskerStyle::IQR_1_5_auto:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("perc_25_75"));
      break;
  }
  xmlwriter->writePen(pen());
  xmlwriter->writeBrush(brush());
  xmlwriter->writeEndElement();
  // median
  xmlwriter->writeStartElement(QString::fromLatin1("median"));
  xmlwriter->writePen(medianPen());
  xmlwriter->writeEndElement();
  // whisker
  xmlwriter->writeStartElement(QString::fromLatin1("whisker"));
  (whiskerAntialiased()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("true"))
                         : xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("width"), QString::number(whiskerWidth()));
  xmlwriter->writePen(whiskerPen());
  xmlwriter->writeEndElement();
  // whisker bar
  xmlwriter->writeStartElement(QString::fromLatin1("whiskerbar"));
  switch (getwhiskerstyle_statbox()) {
    case StatBox2D::BoxWhiskerStyle::SE:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("se"));
      break;
    case StatBox2D::BoxWhiskerStyle::SD:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("sd"));
      break;
    case StatBox2D::BoxWhiskerStyle::MinMax:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("minmax"));
      break;
    case StatBox2D::BoxWhiskerStyle::Constant:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("constant"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_1_99:
      xmlwriter->writeAttribute(QString::fromLatin1("boxstyle"), QString::fromLatin1("perc_1_99"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_5_95:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("perc_5_95"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_10_90:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("perc_10_90"));
      break;
    case StatBox2D::BoxWhiskerStyle::Perc_25_75:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("perc_25_75"));
      break;
    case StatBox2D::BoxWhiskerStyle::IQR_1_5_auto:
      xmlwriter->writeAttribute(QString::fromLatin1("whiskerstyle"), QString::fromLatin1("IQR_1_5_auto"));
      break;
  }
  xmlwriter->writePen(whiskerBarPen());
  xmlwriter->writeEndElement();
  // scatter
  xmlwriter->writeStartElement(QString::fromLatin1("scatter"));
  (scatter_ == Scatter::All) ? xmlwriter->writeAttribute(QString::fromLatin1("show"), QString::fromLatin1("all"))
  : (scatter_ == Scatter::Outliers)
      ? xmlwriter->writeAttribute(QString::fromLatin1("show"), QString::fromLatin1("outlier"))
  : (scatter_ == Scatter::MinMax) ? xmlwriter->writeAttribute(QString::fromLatin1("show"), QString::fromLatin1("minmax"))
  : (scatter_ == Scatter::None)   ? xmlwriter->writeAttribute(QString::fromLatin1("show"), QString::fromLatin1("none"))
                                : xmlwriter->writeAttribute(QString::fromLatin1("show"), QString::fromLatin1("outlier"));
  switch (getscattershape_statbox()) {
    case Graph2DCommon::ScatterStyle::None:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("none"));
      break;
    case Graph2DCommon::ScatterStyle::Dot:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("dot"));
      break;
    case Graph2DCommon::ScatterStyle::Disc:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("disc"));
      break;
    case Graph2DCommon::ScatterStyle::Plus:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("plus"));
      break;
    case Graph2DCommon::ScatterStyle::Star:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("star"));
      break;
    case Graph2DCommon::ScatterStyle::Cross:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("cross"));
      break;
    case Graph2DCommon::ScatterStyle::Peace:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("peace"));
      break;
    case Graph2DCommon::ScatterStyle::Circle:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("circle"));
      break;
    case Graph2DCommon::ScatterStyle::Square:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("square"));
      break;
    case Graph2DCommon::ScatterStyle::Diamond:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("diamond"));
      break;
    case Graph2DCommon::ScatterStyle::Triangle:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("triangle"));
      break;
    case Graph2DCommon::ScatterStyle::PlusCircle:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("pluscircle"));
      break;
    case Graph2DCommon::ScatterStyle::PlusSquare:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("plussquare"));
      break;
    case Graph2DCommon::ScatterStyle::CrossCircle:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("crosscircle"));
      break;
    case Graph2DCommon::ScatterStyle::CrossSquare:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("crosssquare"));
      break;
    case Graph2DCommon::ScatterStyle::TriangleInverted:
      xmlwriter->writeAttribute(QString::fromLatin1("style"), QString::fromLatin1("triangleinverted"));
      break;
  }
  xmlwriter->writeAttribute(QString::fromLatin1("size"), QString::number(scatterstyle_->size()));
  (antialiasedScatters()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("true"))
                          : xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("false"));
  xmlwriter->writePen(scatterstyle_->pen());
  xmlwriter->writeBrush(scatterstyle_->brush());
  xmlwriter->writeEndElement();
  xmlwriter->writeEndElement();
}

bool StatBox2D::load(XmlStreamReader *xmlreader) {
  bool ok;
  while (!xmlreader->atEnd()) {
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("statbox")) break;

    // box
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("box")) {
      // box fill status
        bool fill = xmlreader->readAttributeBool(QString::fromLatin1("fill"), &ok);
      (ok) ? setfillstatus_statbox(fill)
           : xmlreader->raiseWarning(
                 tr("StatBox2D box fill status property setting error"));

      // box antialias
      bool boxantialias = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
      (ok) ? setAntialiased(boxantialias)
           : xmlreader->raiseWarning(
                 tr("StatBox2D box antialias property setting error"));

      // box antialias fill
      bool boxantialiasfill =
          xmlreader->readAttributeBool(QString::fromLatin1("antialiasfill"), &ok);
      (ok) ? setAntialiasedFill(boxantialiasfill)
           : xmlreader->raiseWarning(
                 tr("StatBox2D box antialias propfill erty setting error"));

      // box width
      double boxwidth = xmlreader->readAttributeDouble(QString::fromLatin1("width"), &ok);
      if (ok) {
        setWidth(boxwidth);
      } else
        xmlreader->raiseWarning(
            tr("StatBox2D box width property setting error"));

      // box style
      QString boxstyle = xmlreader->readAttributeString(QString::fromLatin1("boxstyle"), &ok);
      if (ok) {
        if (boxstyle == QString::fromLatin1("sd")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::SD);
        } else if (boxstyle == QString::fromLatin1("se")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::SE);
        } else if (boxstyle == QString::fromLatin1("minmax")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::MinMax);
        } else if (boxstyle == QString::fromLatin1("constant")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::Constant);
        } else if (boxstyle == QString::fromLatin1("perc_1_99")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_1_99);
        } else if (boxstyle == QString::fromLatin1("perc_5_95")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_5_95);
        } else if (boxstyle == QString::fromLatin1("perc_10_90")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_10_90);
        } else if (boxstyle == QString::fromLatin1("perc_25_75")) {
          setboxstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_25_75);
        }
      } else
        xmlreader->raiseWarning(
            tr("StatBox2D box style property setting error"));

      // box pen property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
        // pen
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
          QPen boxpen = xmlreader->readPen(&ok);
          (ok) ? setPen(boxpen)
               : xmlreader->raiseWarning(
                     tr("StatBox2D box pen property setting error"));
        }
      }

      // box brush property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("brush")) break;
        // brush
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("brush")) {
          QBrush boxbrush = xmlreader->readBrush(&ok);
          (ok) ? setBrush(boxbrush)
               : xmlreader->raiseWarning(
                     tr("Curve2D linebrush property setting error"));
        }
      }
    }

    // median
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("median")) {
      // box pen property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
        // pen
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
          QPen mpen = xmlreader->readPen(&ok);
          (ok) ? setMedianPen(mpen)
               : xmlreader->raiseWarning(
                     tr("StatBox2D median pen property setting error"));
        }
      }
    }

    // whisker
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("whisker")) {
      // whisker antialias
      bool boxantialias = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
      (ok) ? setWhiskerAntialiased(boxantialias)
           : xmlreader->raiseWarning(
                 tr("StatBox2D whisker antialias property setting error"));

      // whisker width
      double whiskerwidth = xmlreader->readAttributeDouble(QString::fromLatin1("width"), &ok);
      (ok) ? setWhiskerWidth(whiskerwidth)
           : xmlreader->raiseWarning(
                 tr("StatBox2D whisker width property setting error"));

      // pen property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
        // pen
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
          QPen wpen = xmlreader->readPen(&ok);
          (ok) ? setWhiskerPen(wpen)
               : xmlreader->raiseWarning(
                     tr("StatBox2D whisker pen property setting error"));
        }
      }
    }

    // whiskerbar
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("whiskerbar")) {
      // box style
      QString wstyle = xmlreader->readAttributeString(QString::fromLatin1("whiskerstyle"), &ok);
      if (ok) {
        if (wstyle == QString::fromLatin1("sd")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::SD);
        } else if (wstyle == QString::fromLatin1("se")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::SE);
        } else if (wstyle == QString::fromLatin1("minmax")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::MinMax);
        } else if (wstyle == QString::fromLatin1("constant")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::Constant);
        } else if (wstyle == QString::fromLatin1("perc_1_99")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_1_99);
        } else if (wstyle == QString::fromLatin1("perc_5_95")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_5_95);
        } else if (wstyle == QString::fromLatin1("perc_10_90")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_10_90);
        } else if (wstyle == QString::fromLatin1("perc_25_75")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::Perc_25_75);
        } else if (wstyle == QString::fromLatin1("IQR_1_5_auto")) {
          setwhiskerstyle_statbox(StatBox2D::BoxWhiskerStyle::IQR_1_5_auto);
        }
      } else
        xmlreader->raiseWarning(
            tr("StatBox2D whisker style property setting error"));
      // pen property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
        // pen
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
          QPen wbpen = xmlreader->readPen(&ok);
          (ok) ? setWhiskerBarPen(wbpen)
               : xmlreader->raiseWarning(
                     tr("StatBox2D whiskerbar pen property setting error"));
        }
      }
    }

    // scatter
    // scatter show
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("scatter")) {
      QString scattershow = xmlreader->readAttributeString(QString::fromLatin1("show"), &ok);
      if (ok) {
        (scattershow == QString::fromLatin1("all"))       ? setOutlierScatter(Scatter::All)
        : (scattershow == QString::fromLatin1("outlier")) ? setOutlierScatter(Scatter::Outliers)
        : (scattershow == QString::fromLatin1("minmax"))  ? setOutlierScatter(Scatter::MinMax)
        : (scattershow == QString::fromLatin1("none"))    ? setOutlierScatter(Scatter::None)
                                     : setOutlierScatter(Scatter::Outliers);
      } else
        xmlreader->raiseWarning(
            tr("StatBox2D scatter show property setting error"));

      // scatter shape
      QString scattershape = xmlreader->readAttributeString(QString::fromLatin1("style"), &ok);
      if (ok) {
        if (scattershape == QString::fromLatin1("dot")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Dot);
        } else if (scattershape == QString::fromLatin1("disc")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Disc);
        } else if (scattershape == QString::fromLatin1("none")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::None);
        } else if (scattershape == QString::fromLatin1("plus")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Plus);
        } else if (scattershape == QString::fromLatin1("star")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Star);
        } else if (scattershape == QString::fromLatin1("cross")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Cross);
        } else if (scattershape == QString::fromLatin1("peace")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Peace);
        } else if (scattershape == QString::fromLatin1("circle")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Circle);
        } else if (scattershape == QString::fromLatin1("square")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Square);
        } else if (scattershape == QString::fromLatin1("diamond")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Diamond);
        } else if (scattershape == QString::fromLatin1("triangle")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::Triangle);
        } else if (scattershape == QString::fromLatin1("pluscircle")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::PlusCircle);
        } else if (scattershape == QString::fromLatin1("plussquare")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::PlusSquare);
        } else if (scattershape == QString::fromLatin1("crosscircle")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::CrossCircle);
        } else if (scattershape == QString::fromLatin1("crosssquare")) {
          setscattershape_statbox(Graph2DCommon::ScatterStyle::CrossSquare);
        } else if (scattershape == QString::fromLatin1("triangleinverted")) {
          setscattershape_statbox(
              Graph2DCommon::ScatterStyle::TriangleInverted);
        }
      } else
        xmlreader->raiseWarning(
            tr("StatBox2D scatter shape property setting error"));

      // scatter size
      int scattersize = xmlreader->readAttributeInt(QString::fromLatin1("size"), &ok);
      (ok) ? setscattersize_statbox(scattersize)
           : xmlreader->raiseWarning(
                 tr("Scatter2D scatter size property setting error"));

      // scatter antialias
      bool scatterantialias = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
      (ok) ? setAntialiasedScatters(scatterantialias)
           : xmlreader->raiseWarning(
                 tr("ScatterBox2D scatter antialias property setting error"));

      // scatter pen property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
        // pen
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
          QPen strokep = xmlreader->readPen(&ok);
          if (ok) {
            setscatterstrokecolor_statbox(strokep.color());
            setscatterstrokestyle_statbox(strokep.style());
            setscatterstrokethickness_statbox(strokep.widthF());
          } else
            xmlreader->raiseWarning(
                tr("ScatterBox2D scatter pen property setting error"));
        }
      }
    }
    xmlreader->readNext();
  }
  return !xmlreader->hasError();
}

void StatBox2D::rescaleaxes_statbox() {
  xAxis_->rescale();
  yAxis_->rescale();
  QCPRange keyRange = xAxis_->range();
  QCPRange valueRange = yAxis_->range();
  double keyRangeSpan = keyRange.upper - keyRange.lower;
  double valueRangeSpan = valueRange.upper - valueRange.lower;
  xAxis_->setRange(QCPRange(keyRange.lower - keyRangeSpan * 0.2,
                            keyRange.upper + keyRangeSpan * 0.2));
  yAxis_->setRange(QCPRange(valueRange.lower - valueRangeSpan * 0.2,
                            valueRange.upper + valueRangeSpan * 0.2));
}

void StatBox2D::mousePressEvent(QMouseEvent *event, const QVariant &details) {
  if (event->button() == Qt::LeftButton) {
    switch (xAxis_->getaxisrect_axis()->getPickerTool()->getPicker()) {
      case Graph2DCommon::Picker::None:
      case Graph2DCommon::Picker::DataGraph:
      case Graph2DCommon::Picker::DragRange:
      case Graph2DCommon::Picker::ZoomRange:
      case Graph2DCommon::Picker::DataRange:
        break;
      case Graph2DCommon::Picker::DataPoint:
        datapicker(event, details);
        break;
      case Graph2DCommon::Picker::DataMove:
        movepicker(event, details);
        break;
      case Graph2DCommon::Picker::DataRemove:
        removepicker(event, details);
        break;
    }
  }
  QCPStatisticalBox::mousePressEvent(event, details);
}

void StatBox2D::datapicker(QMouseEvent *event, const QVariant &details) {
  QCPStatisticalBoxDataContainer::const_iterator it = data()->constEnd();
  QCPDataSelection dataPoints = details.value<QCPDataSelection>();
  if (dataPoints.dataPointCount() > 0) {
    dataPoints.dataRange();
    it = data()->at(dataPoints.dataRange().begin());
    QPointF point = coordsToPixels(it->mainKey(), it->mainValue());
    if (point.x() > event->localPos().x() - 10 &&
        point.x() < event->localPos().x() + 10 &&
        point.y() > event->localPos().y() - 10 &&
        point.y() < event->localPos().y() + 10) {
      xAxis_->getaxisrect_axis()->getPickerTool()->showtooltip(
          point, it->mainKey(), it->mainValue(), getxaxis(), getyaxis());
    }
  }
}

void StatBox2D::movepicker(QMouseEvent *, const QVariant &) {
  qDebug() << "move picker unavailable for StatBox2D plots";
}

void StatBox2D::removepicker(QMouseEvent *, const QVariant &) {
  qDebug() << "remove picker unavailable for StatBox2D plots";
}
