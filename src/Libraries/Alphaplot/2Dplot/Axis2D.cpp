/* This file is part of AlphaPlot.
   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   AlphaPlot is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   AlphaPlot is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with AlphaPlot.  If not, see <http://www.gnu.org/licenses/>.

   Description : Plot2D axis related stuff */
#include "Precompiled.h"

#include "Axis2D.h"

#include <QVector>

#include "AxisRect2D.h"
#include "Plot2D.h"
#include "core/IconLoader.h"
#include "core/Utilities.h"
#include "future/core/column/Column.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"

Axis2D::Axis2D(AxisRect2D *parent, const AxisType type,
               const TickerType tickertype)
    : QCPAxis(parent, type),
      axisrect_(parent),
      tickertype_(tickertype),
      ticker_(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker)),
      layername_(axisrect_->getParentPlot2D()->getAxis2DLayerName()),
      tickertext_(new QVector<QString>()),
      tickertextcol_(nullptr) {
  setLayer(layername_);
  switch (tickertype) {
    case Axis2D::TickerType::Value:
      ticker_ = ticker();
      break;
    case Axis2D::TickerType::Log:
      setscaletype_axis(Axis2D::AxisScaleType::Logarithmic);
      ticker_ = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerLog);
      break;
    case Axis2D::TickerType::Pi:
      ticker_ = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerPi);
      break;
    case Axis2D::TickerType::Text:
      ticker_ = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerText);
      break;
    case Axis2D::TickerType::Time:
      ticker_ = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerTime);
      break;
    case Axis2D::TickerType::DateTime:
      ticker_ = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerDateTime);
      break;
  }
  setTicker(ticker_);
  reloadIcon();
  layer()->setMode(QCPLayer::LayerMode::lmBuffered);

  connect(this, QOverload<const QCPRange &>::of(&Axis2D::rangeChanged), this,
          [=]() { Q_EMIT rescaleAxis2D(this); });
}

Axis2D::~Axis2D() {}

AxisRect2D *Axis2D::getaxisrect_axis() const { return axisrect_; }

bool Axis2D::getshowhide_axis() const { return realVisibility(); }

int Axis2D::getoffset_axis() const { return offset(); }

double Axis2D::getfrom_axis() const { return range().lower; }

double Axis2D::getto_axis() const { return range().upper; }

Axis2D::AxisScaleType Axis2D::getscaletype_axis() const {
  AxisScaleType scaletype;
  switch (scaleType()) {
    case QCPAxis::stLinear:
      scaletype = AxisScaleType::Linear;
      break;
    case QCPAxis::stLogarithmic:
      scaletype = AxisScaleType::Logarithmic;
      break;
  }
  return scaletype;
}

Axis2D::AxisOreantation Axis2D::getorientation_axis() const {
  AxisOreantation orientation;
  switch (axisType()) {
    case QCPAxis::atLeft:
      orientation = AxisOreantation::Left;
      break;
    case QCPAxis::atBottom:
      orientation = AxisOreantation::Bottom;
      break;
    case QCPAxis::atRight:
      orientation = AxisOreantation::Right;
      break;
    case QCPAxis::atTop:
      orientation = AxisOreantation::Top;
      break;
  }
  return orientation;
}

Axis2D::TickerType Axis2D::gettickertype_axis() const { return tickertype_; }

bool Axis2D::getinverted_axis() const { return rangeReversed(); }

QColor Axis2D::getstrokecolor_axis() const { return basePen().color(); }

double Axis2D::getstrokethickness_axis() const { return basePen().widthF(); }

Qt::PenStyle Axis2D::getstroketype_axis() const { return basePen().style(); }

bool Axis2D::getantialiased_axis() const { return antialiased(); }

QString Axis2D::getlabeltext_axis() const { return label(); }

QColor Axis2D::getlabelcolor_axis() const { return labelColor(); }

QFont Axis2D::getlabelfont_axis() const { return labelFont(); }

int Axis2D::getlabelpadding_axis() const { return labelPadding(); }

bool Axis2D::gettickvisibility_axis() const { return ticks(); }

int Axis2D::getticklengthin_axis() const { return tickLengthIn(); }

int Axis2D::getticklengthout_axis() const { return tickLengthOut(); }

QColor Axis2D::gettickstrokecolor_axis() const { return tickPen().color(); }

double Axis2D::gettickstrokethickness_axis() const {
  return tickPen().widthF();
}

Qt::PenStyle Axis2D::gettickstrokestyle_axis() const {
  return tickPen().style();
}

int Axis2D::gettickscount_axis() const { return ticker_->tickCount(); }

double Axis2D::getticksorigin() const { return ticker_->tickOrigin(); }

bool Axis2D::getsubtickvisibility_axis() const { return subTicks(); }

int Axis2D::getsubticklengthin_axis() const { return subTickLengthIn(); }

int Axis2D::getsubticklengthout_axis() const { return subTickLengthOut(); }

QColor Axis2D::getsubtickstrokecolor_axis() const {
  return subTickPen().color();
}

double Axis2D::getsubtickstrokethickness_axis() const {
  return subTickPen().widthF();
}

Qt::PenStyle Axis2D::getsubtickstrokestyle_axis() const {
  return subTickPen().style();
}

bool Axis2D::getticklabelvisibility_axis() const { return tickLabels(); }

int Axis2D::getticklabelpadding_axis() const { return tickLabelPadding(); }

QFont Axis2D::getticklabelfont_axis() const { return tickLabelFont(); }

QColor Axis2D::getticklabelcolor_axis() const { return tickLabelColor(); }

double Axis2D::getticklabelrotation_axis() const { return tickLabelRotation(); }

Axis2D::AxisLabelSide Axis2D::getticklabelside_axis() const {
  AxisLabelSide side;
  switch (tickLabelSide()) {
    case lsInside:
      side = AxisLabelSide::Inside;
      break;
    case lsOutside:
      side = AxisLabelSide::Outside;
      break;
  }
  return side;
}

Axis2D::AxisLabelFormat Axis2D::getticklabelformat_axis() const {
  const QString format = numberFormat();
  Axis2D::AxisLabelFormat axisformat;
  if (format == QString::fromLatin1("e")) {
    axisformat = AxisLabelFormat::e;
  } else if (format == QString::fromLatin1("eb")) {
    axisformat = AxisLabelFormat::eb;
  } else if (format == QString::fromLatin1("ebc")) {
    axisformat = AxisLabelFormat::ebc;
  } else if (format == QString::fromLatin1("E")) {
    axisformat = AxisLabelFormat::E;
  } else if (format == QString::fromLatin1("f")) {
    axisformat = AxisLabelFormat::f;
  } else if (format == QString::fromLatin1("g")) {
    axisformat = AxisLabelFormat::g;
  } else if (format == QString::fromLatin1("gb")) {
    axisformat = AxisLabelFormat::gb;
  } else if (format == QString::fromLatin1("gbc")) {
    axisformat = AxisLabelFormat::gbc;
  } else if (format == QString::fromLatin1("G")) {
    axisformat = AxisLabelFormat::G;
  } else {
    qDebug() << "unknown Axis2D::AxisLabelFormat: " << format;
    axisformat = AxisLabelFormat::gbc;
  }
  return axisformat;
}

int Axis2D::getticklabelprecision_axis() const { return numberPrecision(); }

QString Axis2D::getname_axis() const {
  QString name;
  name = label();
  name = name.remove(QString::fromLatin1("\n"));
  if (name.length() > 15) {
    name.truncate(15);
    name = name + QString::fromLatin1("***");
  }
  switch (getorientation_axis()) {
    case Axis2D::AxisOreantation::Left:
    case Axis2D::AxisOreantation::Right:
      name = name + QString::fromLatin1(" (Y):");
      break;
    case Axis2D::AxisOreantation::Top:
    case Axis2D::AxisOreantation::Bottom:
        name = name + QString::fromLatin1(" (X):");
      break;
  }
  return name;
}

uint Axis2D::getnumber_axis() const {
  switch (getorientation_axis()) {
    case Axis2D::AxisOreantation::Left:
    case Axis2D::AxisOreantation::Right: {
      QList<Axis2D *> yaxes = getaxisrect_axis()->getYAxes2D();
      for (int i = 0; i < yaxes.size(); i++) {
        if (yaxes.at(i) == this) return i + 1;
      }
    } break;
    case Axis2D::AxisOreantation::Top:
    case Axis2D::AxisOreantation::Bottom: {
      QList<Axis2D *> xaxes = getaxisrect_axis()->getXAxes2D();
      for (int i = 0; i < xaxes.size(); i++) {
        if (xaxes.at(i) == this) return i + 1;
      }
    } break;
  }

  return 0;
}

QSharedPointer<QCPAxisTicker> Axis2D::getticker_axis() { return ticker_; }

void Axis2D::setshowhide_axis(const bool value) { setVisible(value); }

void Axis2D::setoffset_axis(const int value) { setOffset(value); }

void Axis2D::setfrom_axis(const double value) { setRangeLower(value); }

void Axis2D::setto_axis(const double value) { setRangeUpper(value); }

void Axis2D::setscaletype_axis(const Axis2D::AxisScaleType &type) {
  switch (type) {
    case AxisScaleType::Linear:
      setScaleType(QCPAxis::stLinear);
      break;
    case AxisScaleType::Logarithmic:
      setScaleType(QCPAxis::stLogarithmic);
      break;
  }
}

void Axis2D::setinverted_axis(const bool value) { setRangeReversed(value); }

void Axis2D::setstrokecolor_axis(const QColor &color) {
  QPen pen = basePen();
  pen.setColor(color);
  setBasePen(pen);
}

void Axis2D::setstrokethickness_axis(const double value) {
  QPen pen = basePen();
  pen.setWidthF(value);
  setBasePen(pen);
}

void Axis2D::setstroketype_axis(const Qt::PenStyle &style) {
  QPen pen = basePen();
  pen.setStyle(style);
  setBasePen(pen);
}

void Axis2D::setantialiased_axis(const bool value) { setAntialiased(value); }

void Axis2D::setlabeltext_axis(const QString value) { setLabel(value); }

void Axis2D::setlabelcolor_axis(const QColor &color) { setLabelColor(color); }

void Axis2D::setlabelfont_axis(const QFont &font) { setLabelFont(font); }

void Axis2D::setlabelpadding_axis(const int value) { setLabelPadding(value); }

void Axis2D::settickvisibility_axis(const bool value) { setTicks(value); }

void Axis2D::setticklengthin_axis(const int value) { setTickLengthIn(value); }

void Axis2D::setticklengthout_axis(const int value) { setTickLengthOut(value); }

void Axis2D::settickstrokecolor_axis(const QColor &color) {
  QPen pen = tickPen();
  pen.setColor(color);
  setTickPen(pen);
}

void Axis2D::settickstrokethickness_axis(const double value) {
  QPen pen = tickPen();
  pen.setWidthF(value);
  setTickPen(pen);
}

void Axis2D::settickstrokestyle_axis(const Qt::PenStyle &style) {
  QPen pen = tickPen();
  pen.setStyle(style);
  setTickPen(pen);
}

void Axis2D::settickscount_axis(const int count) {
  ticker_->setTickCount(count);
  setTicker(ticker_);
}

void Axis2D::setticksorigin(const double value) {
  ticker_->setTickOrigin(value);
}

void Axis2D::setsubtickvisibility_axis(const bool value) { setSubTicks(value); }

void Axis2D::setsubticklengthin_axis(const int value) {
  setSubTickLengthIn(value);
}

void Axis2D::setsubticklengthout_axis(const int value) {
  setSubTickLengthOut(value);
}

void Axis2D::setsubtickstrokecolor_axis(const QColor &color) {
  QPen pen = subTickPen();
  pen.setColor(color);
  setSubTickPen(pen);
}

void Axis2D::setsubtickstrokethickness_axis(const double value) {
  QPen pen = subTickPen();
  pen.setWidthF(value);
  setSubTickPen(pen);
}

void Axis2D::setsubtickstrokestyle_axis(const Qt::PenStyle &style) {
  QPen pen = subTickPen();
  pen.setStyle(style);
  setSubTickPen(pen);
}

void Axis2D::setticklabelvisibility_axis(const bool value) {
  setTickLabels(value);
}

void Axis2D::setticklabelpadding_axis(const int value) {
  setTickLabelPadding(value);
}

void Axis2D::setticklabelfont_axis(const QFont &font) {
  setTickLabelFont(font);
}

void Axis2D::setticklabelcolor_axis(const QColor &color) {
  setTickLabelColor(color);
}

void Axis2D::setticklabelrotation_axis(const double value) {
  setTickLabelRotation(value);
}

void Axis2D::setticklabelside_axis(const Axis2D::AxisLabelSide &side) {
  switch (side) {
    case AxisLabelSide::Inside:
      setTickLabelSide(LabelSide::lsInside);
      break;
    case AxisLabelSide::Outside:
      setTickLabelSide(LabelSide::lsOutside);
      break;
  }
}

void Axis2D::setticklabelformat_axis(
    const Axis2D::AxisLabelFormat &axisformat) {
  switch (axisformat) {
    case Axis2D::AxisLabelFormat::e:
      setNumberFormat(QString::fromLatin1("e"));
      break;
    case Axis2D::AxisLabelFormat::eb:
      setNumberFormat(QString::fromLatin1("eb"));
      break;
    case Axis2D::AxisLabelFormat::ebc:
      setNumberFormat(QString::fromLatin1("ebc"));
      break;
    case Axis2D::AxisLabelFormat::E:
      setNumberFormat(QString::fromLatin1("E"));
      break;
    case Axis2D::AxisLabelFormat::f:
      setNumberFormat(QString::fromLatin1("f"));
      break;
    case Axis2D::AxisLabelFormat::g:
      setNumberFormat(QString::fromLatin1("g"));
      break;
    case Axis2D::AxisLabelFormat::gb:
      setNumberFormat(QString::fromLatin1("gb"));
      break;
    case Axis2D::AxisLabelFormat::gbc:
      setNumberFormat(QString::fromLatin1("gbc"));
      break;
    case Axis2D::AxisLabelFormat::G:
      setNumberFormat(QString::fromLatin1("G"));
      break;
  }
}

void Axis2D::setticklabelprecision_axis(const int value) {
  setNumberPrecision(value);
}

void Axis2D::settickertext(Column *col, const int from, const int to) {
  if (tickertype_ == Axis2D::TickerType::Text &&
      col->dataType() == AlphaPlot::ColumnDataType::TypeString &&
      tickertextcol_ == nullptr) {
    QSharedPointer<QCPAxisTickerText> textticker =
        qSharedPointerCast<QCPAxisTickerText>(ticker_);
    textticker->clear();
    for (int i = 0, row = from; row <= to; row++, i++) {
      textticker->addTick(i, Utilities::splitstring(col->textAt(row)));
    }
    setTicker(textticker);
    tickertextcol_ = col;
    tickertextcolfrom_ = from;
    tickertextcolto_ = to;
  }
}

void Axis2D::removetickertext() {
  if (tickertype_ == Axis2D::TickerType::Text)
    if (!plottables().count()) {
      QSharedPointer<QCPAxisTickerText> textticker =
          qSharedPointerCast<QCPAxisTickerText>(ticker_);
      textticker->clear();
      setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTickerText));
      tickertextcol_ = nullptr;
    }
}

void Axis2D::reloadIcon() {
  switch (getorientation_axis()) {
    case Axis2D::AxisOreantation::Left:
      switch (gettickertype_axis()) {
        case Axis2D::TickerType::Value:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-left-value"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Log:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-left-log"), IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Pi:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-left-symbol"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Time:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-left-time"), IconLoader::LightDark);
          break;
        case Axis2D::TickerType::DateTime:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-left-datetime"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Text:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-left-text"), IconLoader::LightDark);
          break;
      }
      break;
    case Axis2D::AxisOreantation::Bottom:
      switch (gettickertype_axis()) {
        case Axis2D::TickerType::Value:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-value"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Log:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-log"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Pi:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-symbol"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Time:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-time"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::DateTime:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-datetime"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Text:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-text"),
                                   IconLoader::LightDark);
          break;
      }
      break;
    case Axis2D::AxisOreantation::Right:
      switch (gettickertype_axis()) {
        case Axis2D::TickerType::Value:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-right-value"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Log:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-right-log"), IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Pi:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-right-symbol"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Time:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-right-time"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::DateTime:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-right-datetime"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Text:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-right-text"),
                                   IconLoader::LightDark);
          break;
      }
      break;
    case Axis2D::AxisOreantation::Top:
      switch (gettickertype_axis()) {
        case Axis2D::TickerType::Value:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-top-value"), IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Log:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-top-log"), IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Pi:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-top-symbol"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Time:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-top-time"), IconLoader::LightDark);
          break;
        case Axis2D::TickerType::DateTime:
          icon_ = IconLoader::load(QString::fromLatin1("graph2d-axis-top-datetime"),
                                   IconLoader::LightDark);
          break;
        case Axis2D::TickerType::Text:
          icon_ =
              IconLoader::load(QString::fromLatin1("graph2d-axis-top-text"), IconLoader::LightDark);
          break;
      }
      break;
  }
}

void Axis2D::save(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("axis"));
  (getshowhide_axis()) ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
                       : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
  switch (getorientation_axis()) {
    case Axis2D::AxisOreantation::Left:
      xmlwriter->writeAttribute(QString::fromLatin1("position"), QString::fromLatin1("left"));
      break;
    case Axis2D::AxisOreantation::Bottom:
      xmlwriter->writeAttribute(QString::fromLatin1("position"), QString::fromLatin1("bottom"));
      break;
    case Axis2D::AxisOreantation::Right:
      xmlwriter->writeAttribute(QString::fromLatin1("position"), QString::fromLatin1("right"));
      break;
    case Axis2D::AxisOreantation::Top:
      xmlwriter->writeAttribute(QString::fromLatin1("position"), QString::fromLatin1("top"));
      break;
  }
  switch (gettickertype_axis()) {
    case Axis2D::TickerType::Value:
      xmlwriter->writeAttribute(QString::fromLatin1("tickertype"), QString::fromLatin1("value"));
      break;
    case Axis2D::TickerType::Log:
      xmlwriter->writeAttribute(QString::fromLatin1("tickertype"), QString::fromLatin1("log"));
      break;
    case Axis2D::TickerType::Pi:
      xmlwriter->writeAttribute(QString::fromLatin1("tickertype"), QString::fromLatin1("pi"));
      break;
    case Axis2D::TickerType::Time:
      xmlwriter->writeAttribute(QString::fromLatin1("tickertype"), QString::fromLatin1("time"));
      break;
    case Axis2D::TickerType::DateTime:
      xmlwriter->writeAttribute(QString::fromLatin1("tickertype"), QString::fromLatin1("datetime"));
      break;
    case Axis2D::TickerType::Text:
      xmlwriter->writeAttribute(QString::fromLatin1("tickertype"), QString::fromLatin1("text"));
      break;
  }
  (axisrect_->getGridPair().first.second == this ||
   axisrect_->getGridPair().second.second == this)
      ? xmlwriter->writeAttribute(QString::fromLatin1("grid"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("grid"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("offset"), QString::number(getoffset_axis()));
  xmlwriter->writeAttribute(QString::fromLatin1("from"), QString::number(getfrom_axis()));
  xmlwriter->writeAttribute(QString::fromLatin1("to"), QString::number(getto_axis()));
  switch (getscaletype_axis()) {
    case Axis2D::AxisScaleType::Linear:
      xmlwriter->writeAttribute(QString::fromLatin1("scaletype"), QString::fromLatin1("linear"));
      break;
    case Axis2D::AxisScaleType::Logarithmic:
      xmlwriter->writeAttribute(QString::fromLatin1("scaletype"), QString::fromLatin1("logarithemic"));
      break;
  }
  // upperending style
  switch (upperEnding().style()) {
    case QCPLineEnding::EndingStyle::esNone:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("none"));
      break;
    case QCPLineEnding::EndingStyle::esBar:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("bar"));
      break;
    case QCPLineEnding::EndingStyle::esDisc:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("disc"));
      break;
    case QCPLineEnding::EndingStyle::esSquare:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("square"));
      break;
    case QCPLineEnding::EndingStyle::esDiamond:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("diamond"));
      break;
    case QCPLineEnding::EndingStyle::esHalfBar:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("halfbar"));
      break;
    case QCPLineEnding::EndingStyle::esFlatArrow:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("flatarrow"));
      break;
    case QCPLineEnding::EndingStyle::esLineArrow:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("linearrow"));
      break;
    case QCPLineEnding::EndingStyle::esSkewedBar:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("skewedbar"));
      break;
    case QCPLineEnding::EndingStyle::esSpikeArrow:
      xmlwriter->writeAttribute(QString::fromLatin1("upperending"), QString::fromLatin1("spikearrow"));
      break;
  }
  // lowerending style
  switch (lowerEnding().style()) {
    case QCPLineEnding::EndingStyle::esNone:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("none"));
      break;
    case QCPLineEnding::EndingStyle::esBar:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("bar"));
      break;
    case QCPLineEnding::EndingStyle::esDisc:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("disc"));
      break;
    case QCPLineEnding::EndingStyle::esSquare:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("square"));
      break;
    case QCPLineEnding::EndingStyle::esDiamond:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("diamond"));
      break;
    case QCPLineEnding::EndingStyle::esHalfBar:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("halfbar"));
      break;
    case QCPLineEnding::EndingStyle::esFlatArrow:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("flatarrow"));
      break;
    case QCPLineEnding::EndingStyle::esLineArrow:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("linearrow"));
      break;
    case QCPLineEnding::EndingStyle::esSkewedBar:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("skewedbar"));
      break;
    case QCPLineEnding::EndingStyle::esSpikeArrow:
      xmlwriter->writeAttribute(QString::fromLatin1("lowerending"), QString::fromLatin1("spikearrow"));
      break;
  }
  (getinverted_axis()) ? xmlwriter->writeAttribute(QString::fromLatin1("inverted"), QString::fromLatin1("true"))
                       : xmlwriter->writeAttribute(QString::fromLatin1("inverted"), QString::fromLatin1("false"));
  (getantialiased_axis()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("true"))
                          : xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("false"));
  xmlwriter->writePen(basePen());
  xmlwriter->writeStartElement(QString::fromLatin1("ticker"));
  (ticker_->tickStepStrategy() ==
   QCPAxisTicker::TickStepStrategy::tssReadability)
      ? xmlwriter->writeAttribute(QString::fromLatin1("tickstepstrategy"), QString::fromLatin1("readability"))
      : xmlwriter->writeAttribute(QString::fromLatin1("tickstepstrategy"), QString::fromLatin1("meettickcount"));
  switch (tickertype_) {
    case Axis2D::TickerType::Pi: {
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("symbol"));
      QSharedPointer<QCPAxisTickerPi> piticker =
          qSharedPointerCast<QCPAxisTickerPi>(ticker_);
      if (piticker) {
        xmlwriter->writeAttribute(QString::fromLatin1("symbol"), piticker->piSymbol());
        xmlwriter->writeAttribute(QString::fromLatin1("symbolvalue"),
                                  QString::number(piticker->piValue()));
        (piticker->fractionStyle() ==
         QCPAxisTickerPi::FractionStyle::fsFloatingPoint)
            ? xmlwriter->writeAttribute(QString::fromLatin1("fractionstyle"), QString::fromLatin1("floatingpoint"))
        : (piticker->fractionStyle() ==
           QCPAxisTickerPi::FractionStyle::fsAsciiFractions)
            ? xmlwriter->writeAttribute(QString::fromLatin1("fractionstyle"), QString::fromLatin1("asciifractions"))
            : xmlwriter->writeAttribute(QString::fromLatin1("fractionstyle"), QString::fromLatin1("unicodefractions"));
      }
    } break;
    case Axis2D::TickerType::Value:
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("value"));
      break;
    case Axis2D::TickerType::Log: {
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("log"));
      QSharedPointer<QCPAxisTickerLog> logticker =
          qSharedPointerCast<QCPAxisTickerLog>(ticker_);
      if (logticker) {
        xmlwriter->writeAttribute(QString::fromLatin1("logbase"),
                                  QString::number(logticker->logBase()));
      }
    } break;
    case Axis2D::TickerType::Time: {
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("time"));
      QSharedPointer<QCPAxisTickerTime> timeticker =
          qSharedPointerCast<QCPAxisTickerTime>(ticker_);
      if (timeticker) {
        xmlwriter->writeAttribute(QString::fromLatin1("format"), timeticker->timeFormat());
      }
    } break;
    case Axis2D::TickerType::DateTime: {
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("datetime"));
      QSharedPointer<QCPAxisTickerDateTime> datetimeticker =
          qSharedPointerCast<QCPAxisTickerDateTime>(ticker_);
      if (datetimeticker) {
        xmlwriter->writeAttribute(QString::fromLatin1("format"), datetimeticker->dateTimeFormat());
      }
    } break;
    case Axis2D::TickerType::Text: {
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("text"));
      for (int i = 0; i < tickertext_->count(); i++) {
        xmlwriter->writeStartElement(QString::fromLatin1("tick"));
        xmlwriter->writeAttribute(QString::fromLatin1("value"),
                                  Utilities::joinstring(tickertext_->at(i)));
        xmlwriter->writeEndElement();
      }
    } break;
  }
  xmlwriter->writeEndElement();
  xmlwriter->writeStartElement(QString::fromLatin1("label"));
  xmlwriter->writeAttribute(QString::fromLatin1("text"), getlabeltext_axis());
  xmlwriter->writeAttribute(QString::fromLatin1("padding"), QString::number(getlabelpadding_axis()));
  xmlwriter->writeFont(getlabelfont_axis(), getlabelcolor_axis());
  xmlwriter->writeEndElement();
  // Ticks
  xmlwriter->writeStartElement(QString::fromLatin1("ticks"));
  (gettickvisibility_axis()) ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
                             : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("count"), QString::number(gettickscount_axis()));
  xmlwriter->writeAttribute(QString::fromLatin1("origin"), QString::number(getticksorigin()));
  xmlwriter->writeAttribute(QString::fromLatin1("in"), QString::number(getticklengthin_axis()));
  xmlwriter->writeAttribute(QString::fromLatin1("out"), QString::number(getticklengthout_axis()));
  xmlwriter->writePen(tickPen());
  xmlwriter->writeEndElement();
  // Subticks
  xmlwriter->writeStartElement(QString::fromLatin1("subticks"));
  if (tickertype_ == Axis2D::TickerType::Log) {
    QSharedPointer<QCPAxisTickerLog> logticker =
        qSharedPointerCast<QCPAxisTickerLog>(getticker_axis());
    if (logticker) {
      xmlwriter->writeAttribute(QString::fromLatin1("count"),
                                QString::number(logticker->subTickCount()));
    }
  } else if (tickertype_ == Axis2D::TickerType::Text) {
    QSharedPointer<QCPAxisTickerText> textticker =
        qSharedPointerCast<QCPAxisTickerText>(getticker_axis());
    if (textticker) {
      xmlwriter->writeAttribute(QString::fromLatin1("count"),
                                QString::number(textticker->subTickCount()));
    }
  }
  (getsubtickvisibility_axis()) ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
                                : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("in"), QString::number(getsubticklengthin_axis()));
  xmlwriter->writeAttribute(QString::fromLatin1("out"), QString::number(getsubticklengthout_axis()));
  xmlwriter->writePen(subTickPen());
  xmlwriter->writeEndElement();
  // Tick Labels
  xmlwriter->writeStartElement(QString::fromLatin1("ticklabels"));
  (getticklabelvisibility_axis())
      ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("padding"),
                            QString::number(getticklabelpadding_axis()));
  xmlwriter->writeAttribute(QString::fromLatin1("rotation"),
                            QString::number(getticklabelrotation_axis()));
  switch (getticklabelside_axis()) {
    case Axis2D::AxisLabelSide::Inside:
      xmlwriter->writeAttribute(QString::fromLatin1("side"), QString::fromLatin1("up"));
      break;
    case Axis2D::AxisLabelSide::Outside:
      xmlwriter->writeAttribute(QString::fromLatin1("side"), QString::fromLatin1("down"));
      break;
  }
  switch (getticklabelformat_axis()) {
    case Axis2D::AxisLabelFormat::E:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("E"));
      break;
    case Axis2D::AxisLabelFormat::G:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("G"));
      break;
    case Axis2D::AxisLabelFormat::e:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("e"));
      break;
    case Axis2D::AxisLabelFormat::eb:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("eb"));
      break;
    case Axis2D::AxisLabelFormat::ebc:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("ebc"));
      break;
    case Axis2D::AxisLabelFormat::f:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("f"));
      break;
    case Axis2D::AxisLabelFormat::g:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("g"));
      break;
    case Axis2D::AxisLabelFormat::gb:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("gb"));
      break;
    case Axis2D::AxisLabelFormat::gbc:
      xmlwriter->writeAttribute(QString::fromLatin1("format"), QString::fromLatin1("gbc"));
      break;
  }
  xmlwriter->writeAttribute(QString::fromLatin1("precision"),
                            QString::number(getticklabelprecision_axis()));
  xmlwriter->writeFont(getticklabelfont_axis(), getticklabelcolor_axis());
  xmlwriter->writeEndElement();
  xmlwriter->writeEndElement();
}

bool Axis2D::load(XmlStreamReader *xmlreader) {
  if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("axis")) {
    bool ok;
    // visible property
    bool visible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
    (ok) ? setshowhide_axis(visible)
         : xmlreader->raiseWarning(tr("Axis2D visible property setting error"));
    // offset property
    int offset = xmlreader->readAttributeInt(QString::fromLatin1("offset"), &ok);
    (ok) ? setoffset_axis(offset)
         : xmlreader->raiseWarning(tr("Axis2D offset property setting error"));
    // from property
    double from = xmlreader->readAttributeDouble(QString::fromLatin1("from"), &ok);
    if (ok) {
      setfrom_axis(from);
      setRangeLower(from);  // temporary fix the rescaling of axes
    } else
      xmlreader->raiseWarning(tr("Axis2D from property setting error"));
    // to property
    double to = xmlreader->readAttributeDouble(QString::fromLatin1("to"), &ok);
    (ok) ? setto_axis(to)
         : xmlreader->raiseWarning(tr("Axis2D to property setting error"));
    // Scaletype property
    QString scaletype = xmlreader->readAttributeString(QString::fromLatin1("scaletype"), &ok);
    if (ok) {
      (scaletype == QString::fromLatin1("linear")) ? setscaletype_axis(AxisScaleType::Linear)
      : (scaletype == QString::fromLatin1("logarithemic"))
          ? setscaletype_axis(AxisScaleType::Logarithmic)
          : xmlreader->raiseWarning(
                tr("Axis2D Scaletype property setting error"));
    } else
      xmlreader->raiseWarning(tr("Axis2D Scaletype property setting error"));

    // upperending
    QString upperending = xmlreader->readAttributeString(QString::fromLatin1("upperending"), &ok);
    if (ok) {
      if (upperending == QString::fromLatin1("none"))
        setUpperEnding(QCPLineEnding::EndingStyle::esNone);
      else if (upperending == QString::fromLatin1("bar"))
        setUpperEnding(QCPLineEnding::EndingStyle::esBar);
      else if (upperending == QString::fromLatin1("disc"))
        setUpperEnding(QCPLineEnding::EndingStyle::esDisc);
      else if (upperending == QString::fromLatin1("square"))
        setUpperEnding(QCPLineEnding::EndingStyle::esSquare);
      else if (upperending == QString::fromLatin1("diamond"))
        setUpperEnding(QCPLineEnding::EndingStyle::esDiamond);
      else if (upperending == QString::fromLatin1("halfbar"))
        setUpperEnding(QCPLineEnding::EndingStyle::esHalfBar);
      else if (upperending == QString::fromLatin1("flatarrow"))
        setUpperEnding(QCPLineEnding::EndingStyle::esFlatArrow);
      else if (upperending == QString::fromLatin1("linearrow"))
        setUpperEnding(QCPLineEnding::EndingStyle::esLineArrow);
      else if (upperending == QString::fromLatin1("skewedbar"))
        setUpperEnding(QCPLineEnding::EndingStyle::esSkewedBar);
      else if (upperending == QString::fromLatin1("spikearrow"))
        setUpperEnding(QCPLineEnding::EndingStyle::esSpikeArrow);
      else
        xmlreader->raiseWarning(tr("Axis2D unknown upper ending property"));
    } else
      xmlreader->raiseWarning(tr("Axis2D upper ending property setting error"));

    // lowerending
    QString lowerending = xmlreader->readAttributeString(QString::fromLatin1("lowerending"), &ok);
    if (ok) {
      if (lowerending == QString::fromLatin1("none"))
        setLowerEnding(QCPLineEnding::EndingStyle::esNone);
      else if (lowerending == QString::fromLatin1("bar"))
        setLowerEnding(QCPLineEnding::EndingStyle::esBar);
      else if (lowerending == QString::fromLatin1("disc"))
        setLowerEnding(QCPLineEnding::EndingStyle::esDisc);
      else if (lowerending == QString::fromLatin1("square"))
        setLowerEnding(QCPLineEnding::EndingStyle::esSquare);
      else if (lowerending == QString::fromLatin1("diamond"))
        setLowerEnding(QCPLineEnding::EndingStyle::esDiamond);
      else if (lowerending == QString::fromLatin1("halfbar"))
        setLowerEnding(QCPLineEnding::EndingStyle::esHalfBar);
      else if (lowerending == QString::fromLatin1("flatarrow"))
        setLowerEnding(QCPLineEnding::EndingStyle::esFlatArrow);
      else if (lowerending == QString::fromLatin1("linearrow"))
        setLowerEnding(QCPLineEnding::EndingStyle::esLineArrow);
      else if (lowerending == QString::fromLatin1("skewedbar"))
        setLowerEnding(QCPLineEnding::EndingStyle::esSkewedBar);
      else if (lowerending == QString::fromLatin1("spikearrow"))
        setLowerEnding(QCPLineEnding::EndingStyle::esSpikeArrow);
      else
        xmlreader->raiseWarning(tr("Axis2D unknown lower ending property"));
    } else
      xmlreader->raiseWarning(tr("Axis2D lower ending property setting error"));

    // inverted property
    bool inverted = xmlreader->readAttributeBool(QString::fromLatin1("inverted"), &ok);
    (ok)
        ? setinverted_axis(inverted)
        : xmlreader->raiseWarning(tr("Axis2D inverted property setting error"));
    // antialias property
    bool antialias = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
    if (ok)
      setantialiased_axis(antialias);
    else
      xmlreader->raiseWarning(tr("Axis2D antialias property setting error"));
    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
      // pen
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
        QPen basep = xmlreader->readPen(&ok);
        if (ok)
          setBasePen(basep);
        else
          xmlreader->raiseWarning(tr("Axis2D pen property setting error"));
      }
    }
    // Loop through sub elements
    while (!xmlreader->atEnd()) {
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("axis")) break;
      // ticker
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("ticker")) {
        // Tick step strategy
        QString tickss =
            xmlreader->readAttributeString(QString::fromLatin1("tickstepstrategy"), &ok);
        if (ok) {
          if (tickss == QString::fromLatin1("readability"))
            ticker_->setTickStepStrategy(
                QCPAxisTicker::TickStepStrategy::tssReadability);
          else if (tickss == QString::fromLatin1("meettickcount"))
            ticker_->setTickStepStrategy(
                QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
          else
            xmlreader->raiseWarning(
                tr("Axis2D tick step strategy property setting error"));
          setTicker(ticker_);
        } else
          xmlreader->raiseWarning(
              tr("Axis2D tick step strategy property setting error"));

        QString tkrtype = xmlreader->readAttributeString(QString::fromLatin1("type"), &ok);
        Q_UNUSED(tkrtype)
        switch (tickertype_) {
          case Axis2D::TickerType::Log: {
            QSharedPointer<QCPAxisTickerLog> logticker =
                qSharedPointerCast<QCPAxisTickerLog>(ticker_);
            if (logticker) {
              // logbase
              double lbase = xmlreader->readAttributeDouble(QString::fromLatin1("logbase"), &ok);
              if (ok)
                logticker->setLogBase(lbase);
              else
                xmlreader->raiseWarning(
                    tr("Axis2D log base property setting error"));
              setTicker(logticker);
            }
          } break;
          case Axis2D::TickerType::Pi: {
            QSharedPointer<QCPAxisTickerPi> piticker =
                qSharedPointerCast<QCPAxisTickerPi>(ticker_);
            if (piticker) {
              // symbol
              QString symbol = xmlreader->readAttributeString(QString::fromLatin1("symbol"), &ok);
              if (ok)
                piticker->setPiSymbol(symbol);
              else
                xmlreader->raiseWarning(
                    tr("Axis2D piticker symbol property setting error"));
              // symbol value
              double svalue =
                  xmlreader->readAttributeDouble(QString::fromLatin1("symbolvalue"), &ok);
              if (ok)
                piticker->setPiValue(svalue);
              else
                xmlreader->raiseWarning(
                    tr("Axis2D piticker pivalue property setting error"));
              // Fraction style
              QString fstyle =
                  xmlreader->readAttributeString(QString::fromLatin1("fractionstyle"), &ok);
              if (ok) {
                (fstyle == QString::fromLatin1("floatingpoint"))
                    ? piticker->setFractionStyle(
                          QCPAxisTickerPi::FractionStyle::fsFloatingPoint)
                : (fstyle == QString::fromLatin1("asciifractions"))
                    ? piticker->setFractionStyle(
                          QCPAxisTickerPi::FractionStyle::fsAsciiFractions)
                    : piticker->setFractionStyle(
                          QCPAxisTickerPi::FractionStyle::fsUnicodeFractions);
              } else
                xmlreader->raiseWarning(
                    tr("Axis2D piticker fractionstyle property setting error"));
              setTicker(piticker);
            }
          } break;
          case Axis2D::TickerType::Time: {
            QSharedPointer<QCPAxisTickerTime> timeticker =
                qSharedPointerCast<QCPAxisTickerTime>(ticker_);
            if (timeticker) {
              // time format
              QString tformat = xmlreader->readAttributeString(QString::fromLatin1("format"), &ok);
              if (ok)
                timeticker->setTimeFormat(Utilities::splitstring(tformat));
              else
                xmlreader->raiseWarning(
                    tr("Axis2D time ticker format in property setting error"));
              setTicker(timeticker);
            }
          } break;
          case Axis2D::TickerType::DateTime: {
            QSharedPointer<QCPAxisTickerDateTime> datetimeticker =
                qSharedPointerCast<QCPAxisTickerDateTime>(ticker_);
            if (datetimeticker) {
              // datetime format
              QString dtformat = xmlreader->readAttributeString(QString::fromLatin1("format"), &ok);
              if (ok)
                datetimeticker->setDateTimeFormat(
                    Utilities::splitstring(dtformat));
              else
                xmlreader->raiseWarning(tr(
                    "Axis2D datetime ticker format in property setting error"));
              setTicker(datetimeticker);
            }
          } break;
          case Axis2D::TickerType::Text:
            while (!xmlreader->atEnd()) {
              if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("ticker"))
                break;

              if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("tick")) {
                QString tkrtext = xmlreader->readAttributeString(QString::fromLatin1("value"), &ok);
                (ok) ? tickertext_->append(tkrtext)
                     : xmlreader->raiseWarning(
                           tr("Axis2D tickertype text element "
                              "formatproperty setting error"));
              }
              xmlreader->readNext();
            }
            break;
          case Axis2D::TickerType::Value:
            break;
        }
      }
      // Label element
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("label")) {
        // Label text
        QString text = xmlreader->readAttributeString(QString::fromLatin1("text"), &ok);
        if (ok)
          setlabeltext_axis(text);
        else
          xmlreader->raiseWarning(tr("Axis2D label property setting error"));
        // Label padding
        int padding = xmlreader->readAttributeInt(QString::fromLatin1("padding"), &ok);
        if (ok)
          setlabelpadding_axis(padding);
        else
          xmlreader->raiseWarning(tr("Axis2D padding property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("label")) break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("font")) {
            QPair<QFont, QColor> fontpair = xmlreader->readFont(&ok);
            if (ok) {
              setlabelfont_axis(fontpair.first);
              setlabelcolor_axis(fontpair.second);
            } else
              xmlreader->raiseWarning(
                  tr("Axis2D font & color property setting error"));
          }
        }
      }
      // Ticks element
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("ticks")) {
        // tick visible property
        bool tickvisible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
        if (ok)
          settickvisibility_axis(tickvisible);
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick visible property setting error"));
        // Tick count
        int count = xmlreader->readAttributeInt(QString::fromLatin1("count"), &ok);
        (ok) ? settickscount_axis(count)
             : xmlreader->raiseWarning(
                   tr("Axis2D Tick count in property setting error"));
        // Tick count
        double origin = xmlreader->readAttributeInt(QString::fromLatin1("origin"), &ok);
        (ok) ? setticksorigin(origin)
             : xmlreader->raiseWarning(
                   tr("Axis2D Tick origin in property setting error"));
        // Ticks in
        int in = xmlreader->readAttributeInt(QString::fromLatin1("in"), &ok);
        if (ok)
          setticklengthin_axis(in);
        else
          xmlreader->raiseWarning(
              tr("Axis2D Tick length in property setting error"));
        // Tick out
        int out = xmlreader->readAttributeInt(QString::fromLatin1("out"), &ok);
        if (ok)
          setticklengthout_axis(out);
        else
          xmlreader->raiseWarning(
              tr("Axis2D Tick Length out property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("ticks")) break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
            QPen p = xmlreader->readPen(&ok);
            if (ok) {
              setTickPen(p);
            } else
              xmlreader->raiseWarning(
                  tr("Axis2D tick pen property setting error"));
          }
        }
      }
      // Sub Ticks element
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("subticks")) {
        // visible property
        bool subtickvisible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
        if (ok)
          setsubtickvisibility_axis(subtickvisible);
        else
          xmlreader->raiseWarning(
              tr("Axis2D subtick visible property setting error"));
        // subtick count
        if (tickertype_ == Axis2D::TickerType::Log ||
            tickertype_ == Axis2D::TickerType::Text) {
          int sbtkcount = xmlreader->readAttributeInt(QString::fromLatin1("count"), &ok);
          if (ok) {
            if (tickertype_ == Axis2D::TickerType::Log) {
              QSharedPointer<QCPAxisTickerLog> logticker =
                  qSharedPointerCast<QCPAxisTickerLog>(getticker_axis());
              if (logticker) {
                logticker->setSubTickCount(sbtkcount);
              }
            } else if (tickertype_ == Axis2D::TickerType::Text) {
              QSharedPointer<QCPAxisTickerText> textticker =
                  qSharedPointerCast<QCPAxisTickerText>(getticker_axis());
              if (textticker) {
                textticker->setSubTickCount(sbtkcount);
              }
            } else
              xmlreader->raiseWarning(
                  tr("subTick count in property setting error for unknown "
                     "ticker type"));
          } else
            xmlreader->raiseWarning(
                tr("Axis2D subTick count in property setting error"));
        }
        // Ticks in
        int in = xmlreader->readAttributeInt(QString::fromLatin1("in"), &ok);
        if (ok)
          setsubticklengthin_axis(in);
        else
          xmlreader->raiseWarning(
              tr("Axis2D subTick length in property setting error"));
        // out length
        int out = xmlreader->readAttributeInt(QString::fromLatin1("out"), &ok);
        if (ok)
          setsubticklengthout_axis(out);
        else
          xmlreader->raiseWarning(
              tr("Axis2D subTick Length out property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("subticks"))
            break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
            QPen p = xmlreader->readPen(&ok);
            if (ok) {
              setSubTickPen(p);
            } else
              xmlreader->raiseWarning(
                  tr("Axis2D subtick pen property setting error"));
          }
        }
      }
      // Tick label element
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("ticklabels")) {
        // visible property
        bool ticklabelvisible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
        if (ok)
          setticklabelvisibility_axis(ticklabelvisible);
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick label visible property setting error"));
        // Tick label padding
        int ticklabelpadding = xmlreader->readAttributeInt(QString::fromLatin1("padding"), &ok);
        if (ok)
          setticklabelpadding_axis(ticklabelpadding);
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick label padding in property setting error"));
        // Tick Label Rotation
        double ticklabelrotation =
            xmlreader->readAttributeDouble(QString::fromLatin1("rotation"), &ok);
        if (ok)
          setticklabelrotation_axis(ticklabelrotation);
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick label rotation property setting error"));
        // Tick label side
        QString ticklabelside = xmlreader->readAttributeString(QString::fromLatin1("side"), &ok);
        if (ok)
          if (ticklabelside == QString::fromLatin1("up"))
            setticklabelside_axis(Axis2D::AxisLabelSide::Inside);
          else if (ticklabelside == QString::fromLatin1("down"))
            setticklabelside_axis(Axis2D::AxisLabelSide::Outside);
          else
            xmlreader->raiseWarning(
                tr("Axis2D tick label side property setting error"));
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick label side property setting error"));
        // tick label format
        QString ticklabelformat = xmlreader->readAttributeString(QString::fromLatin1("format"), &ok);
        if (ok)
          if (ticklabelformat == QString::fromLatin1("E"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::E);
          else if (ticklabelformat == QString::fromLatin1("G"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::G);
          else if (ticklabelformat == QString::fromLatin1("e"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::e);
          else if (ticklabelformat == QString::fromLatin1("eb"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::eb);
          else if (ticklabelformat == QString::fromLatin1("ebc"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::ebc);
          else if (ticklabelformat == QString::fromLatin1("f"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::f);
          else if (ticklabelformat == QString::fromLatin1("g"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::g);
          else if (ticklabelformat == QString::fromLatin1("gb"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::gb);
          else if (ticklabelformat == QString::fromLatin1("gbc"))
            setticklabelformat_axis(Axis2D::AxisLabelFormat::gbc);
          else
            xmlreader->raiseWarning(
                tr("Axis2D tick label format property setting error"));
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick label format property setting error"));
        // Tick label precision
        int ticklabelprecision = xmlreader->readAttributeInt(QString::fromLatin1("precision"), &ok);
        if (ok)
          setticklabelprecision_axis(ticklabelprecision);
        else
          xmlreader->raiseWarning(
              tr("Axis2D tick label precision property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("ticklabels"))
            break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("font")) {
            QPair<QFont, QColor> fontpair = xmlreader->readFont(&ok);
            if (ok) {
              setticklabelfont_axis(fontpair.first);
              setticklabelcolor_axis(fontpair.second);
            } else
              xmlreader->raiseWarning(
                  tr("Axis2D font & color property setting error"));
          }
        }
      }
      xmlreader->readNext();
    }
  } else  // no element
    xmlreader->raiseError(tr("no axis element found"));
  // settext tics
  if (!tickertext_->isEmpty()) {
    QSharedPointer<QCPAxisTickerText> textticker =
        qSharedPointerCast<QCPAxisTickerText>(ticker_);
    for (int i = 0; i < tickertext_->size(); i++) {
      textticker->addTick(i, Utilities::splitstring(tickertext_->at(i)));
    }
  }

  return !xmlreader->hasError();
}

void Axis2D::clone(Axis2D *axis) {
  // set ticker text
  for (int i = 0; i < tickertext_->size(); i++) {
    axis->tickertext_->append(tickertext_->at(i));
  }
  QSharedPointer<QCPAxisTickerText> textticker =
      qSharedPointerCast<QCPAxisTickerText>(axis->ticker_);
  for (int i = 0; i < axis->tickertext_->count(); i++) {
    textticker->addTick(i, Utilities::splitstring(axis->tickertext_->at(i)));
  }
  // set ticker date time format
  if (gettickertype_axis() == Axis2D::TickerType::DateTime) {
    QSharedPointer<QCPAxisTickerDateTime> newdtticker =
        qSharedPointerCast<QCPAxisTickerDateTime>(axis->ticker_);
    QSharedPointer<QCPAxisTickerDateTime> dtticker =
        qSharedPointerCast<QCPAxisTickerDateTime>(ticker_);
    newdtticker->setDateTimeFormat(dtticker->dateTimeFormat());
  }
  axis->setshowhide_axis(getshowhide_axis());
  axis->setoffset_axis(getoffset_axis());
  axis->setfrom_axis(getfrom_axis());
  axis->setto_axis(getto_axis());
  axis->setscaletype_axis(getscaletype_axis());
  axis->setinverted_axis(getinverted_axis());
  axis->setstrokecolor_axis(getstrokecolor_axis());
  axis->setstrokethickness_axis(getstrokethickness_axis());
  axis->setstroketype_axis(getstroketype_axis());
  axis->setantialiased_axis(getantialiased_axis());
  // Axis label properties
  axis->setlabeltext_axis(getlabeltext_axis());
  axis->setlabelcolor_axis(getlabelcolor_axis());
  axis->setlabelfont_axis(getlabelfont_axis());
  axis->setlabelpadding_axis(getlabelpadding_axis());
  // Tick properties
  axis->settickvisibility_axis(gettickvisibility_axis());
  axis->setticklengthin_axis(getticklengthin_axis());
  axis->setticklengthout_axis(getticklengthout_axis());
  axis->settickstrokecolor_axis(gettickstrokecolor_axis());
  axis->settickstrokethickness_axis(gettickstrokethickness_axis());
  axis->settickstrokestyle_axis(gettickstrokestyle_axis());
  // Sub-tick properties
  axis->setsubtickvisibility_axis(getsubtickvisibility_axis());
  axis->setsubticklengthin_axis(getsubticklengthin_axis());
  axis->setsubticklengthout_axis(getsubticklengthout_axis());
  axis->setsubtickstrokecolor_axis(getsubtickstrokecolor_axis());
  axis->setsubtickstrokethickness_axis(getsubtickstrokethickness_axis());
  axis->setsubtickstrokestyle_axis(getsubtickstrokestyle_axis());
  // Tick label properties
  axis->setticklabelvisibility_axis(getticklabelvisibility_axis());
  axis->setticklabelpadding_axis(getticklabelpadding_axis());
  axis->setticklabelfont_axis(getticklabelfont_axis());
  axis->setticklabelcolor_axis(getticklabelcolor_axis());
  axis->setticklabelrotation_axis(getticklabelrotation_axis());
  axis->setticklabelside_axis(getticklabelside_axis());
  axis->setticklabelformat_axis(getticklabelformat_axis());
  axis->setticklabelprecision_axis(getticklabelprecision_axis());
}
