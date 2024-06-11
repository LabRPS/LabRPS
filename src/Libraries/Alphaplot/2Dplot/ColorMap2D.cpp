#include "Precompiled.h"

#include "ColorMap2D.h"

#include "AxisRect2D.h"
#include "Matrix.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"

ColorMap2D::ColorMap2D(Matrix *matrix, Axis2D *xAxis, Axis2D *yAxis)
    : QCPColorMap(xAxis, yAxis),
      margingroup_(new QCPMarginGroup(parentPlot())),
      xaxis_(xAxis),
      yaxis_(yAxis),
      matrix_(matrix),
      colorScale_(new QCPColorScale(parentPlot())),
      layername_(
          QString::fromLatin1("<ColorMap2D>") +
          QDateTime::currentDateTime().toString(QString::fromLatin1("yyyy:MM:dd:hh:mm:ss:zzz"))),
      gradient_(Gradient::Spectrum),
      invertgradient_(false) {
  // setting layer
  QThread::msleep(1);
  parentPlot()->addLayer(layername_, xaxis_->layer(), QCustomPlot::limBelow);
  setLayer(layername_);
  layer()->setMode(QCPLayer::LayerMode::lmBuffered);

  rows_ = matrix_->numRows();
  columns_ = matrix_->numCols();
  data_ = new QCPColorMapData(rows_, columns_, QCPRange(0, rows_ - 1),
                              QCPRange(0, columns_ - 1));
  parentPlot()->plotLayout()->addElement(0, 1, colorScale_);
  colorScale_->setType(QCPAxis::atRight);
  setColorScale(colorScale_);
  setgradient_colormap(gradient_);
  xaxis_->getaxisrect_axis()->setMarginGroup(QCP::msBottom | QCP::msTop,
                                             margingroup_);
  colorScale_->setMarginGroup(QCP::msBottom | QCP::msTop, margingroup_);
  colorScale_->setRangeDrag(true);
  setColorMapData(matrix_);
  setData(data_);
}

ColorMap2D::~ColorMap2D() {
  delete colorScale_;
  delete margingroup_;
  parentPlot()->removeLayer(layer());
}

void ColorMap2D::setColorMapData(Matrix *matrix) {
  matrix_ = matrix;
  rows_ = matrix_->numRows();
  columns_ = matrix_->numCols();
  data_->setSize(matrix_->numRows(), matrix_->numCols());
  data_->setRange(QCPRange(matrix_->xStart(), matrix_->xEnd()),
                  QCPRange(matrix_->yStart(), matrix_->yEnd()));
  double datamin = matrix_->cell(0, 0);
  double datamax = matrix_->cell(0, 0);
  double value = datamin;
  for (int i = 0; i < matrix_->numRows(); i++) {
    for (int j = 0; j < matrix_->numCols(); j++) {
      value = matrix_->cell(i, j);
      data_->setCell(i, j, value);
      datamin = qMin(datamin, value);
    }
    datamax = qMax(datamax, value);
  }
  setDataRange(QCPRange(datamin, datamax));
}

Axis2D *ColorMap2D::getxaxis() const { return xaxis_; }

Axis2D *ColorMap2D::getyaxis() const { return yaxis_; }

ColorMap2D::Gradient ColorMap2D::getgradient_colormap() const {
  return gradient_;
}

int ColorMap2D::getlevelcount_colormap() const {
  return colorgradient_.levelCount();
}

bool ColorMap2D::getgradientinverted_colormap() const {
  return invertgradient_;
}

bool ColorMap2D::getgradientperiodic_colormap() const {
  return colorgradient_.periodic();
}

QString ColorMap2D::getname_colormap() const { return colorScale_->label(); }

int ColorMap2D::getcolormapscalewidth_colormap() const {
  return colorScale_->barWidth();
}

Axis2D::AxisLabelFormat ColorMap2D::getcolormapscaleticklabelformat_axis()
    const {
  const QString format = colorScale_->axis()->numberFormat();
  Axis2D::AxisLabelFormat axisformat;
  if (format == QString::fromLatin1("e")) {
    axisformat = Axis2D::AxisLabelFormat::e;
  } else if (format == QString::fromLatin1("eb")) {
    axisformat = Axis2D::AxisLabelFormat::eb;
  } else if (format == QString::fromLatin1("ebc")) {
    axisformat = Axis2D::AxisLabelFormat::ebc;
  } else if (format == QString::fromLatin1("E")) {
    axisformat = Axis2D::AxisLabelFormat::E;
  } else if (format == QString::fromLatin1("f")) {
    axisformat = Axis2D::AxisLabelFormat::f;
  } else if (format == QString::fromLatin1("g")) {
    axisformat = Axis2D::AxisLabelFormat::g;
  } else if (format == QString::fromLatin1("gb")) {
    axisformat = Axis2D::AxisLabelFormat::gb;
  } else if (format == QString::fromLatin1("gbc")) {
    axisformat = Axis2D::AxisLabelFormat::gbc;
  } else if (format == QString::fromLatin1("G")) {
    axisformat = Axis2D::AxisLabelFormat::G;
  } else {
    qDebug() << "unknown Axis2D::AxisLabelFormat: " << format;
    axisformat = Axis2D::AxisLabelFormat::gbc;
  }
  return axisformat;
}

void ColorMap2D::setgradient_colormap(const ColorMap2D::Gradient &grad) {
  gradient_ = grad;
  switch (gradient_) {
    case Gradient::Grayscale:
      colorgradient_.loadPreset(QCPColorGradient::gpGrayscale);
      break;
    case Gradient::Hot:
      colorgradient_.loadPreset(QCPColorGradient::gpHot);
      break;
    case Gradient::Cold:
      colorgradient_.loadPreset(QCPColorGradient::gpCold);
      break;
    case Gradient::Night:
      colorgradient_.loadPreset(QCPColorGradient::gpNight);
      break;
    case Gradient::candy:
      colorgradient_.loadPreset(QCPColorGradient::gpCandy);
      break;
    case Gradient::Geography:
      colorgradient_.loadPreset(QCPColorGradient::gpGeography);
      break;
    case Gradient::Ion:
      colorgradient_.loadPreset(QCPColorGradient::gpIon);
      break;
    case Gradient::Thermal:
      colorgradient_.loadPreset(QCPColorGradient::gpThermal);
      break;
    case Gradient::Polar:
      colorgradient_.loadPreset(QCPColorGradient::gpPolar);
      break;
    case Gradient::Spectrum:
      colorgradient_.loadPreset(QCPColorGradient::gpSpectrum);
      break;
    case Gradient::Jet:
      colorgradient_.loadPreset(QCPColorGradient::gpJet);
      break;
    case Gradient::Hues:
      colorgradient_.loadPreset(QCPColorGradient::gpHues);
      break;
  }
  (invertgradient_) ? setGradient(colorgradient_.inverted())
                    : setGradient(colorgradient_);
}

void ColorMap2D::setlevelcount_colormap(const int value) {
  colorgradient_.setLevelCount(value);
  (invertgradient_) ? setGradient(colorgradient_.inverted())
                    : setGradient(colorgradient_);
}

void ColorMap2D::setgradientinverted_colormap(bool status) {
  invertgradient_ = status;
  setgradient_colormap(gradient_);
}

void ColorMap2D::setgradientperiodic_colormap(bool status) {
  colorgradient_.setPeriodic(status);
  (invertgradient_) ? setGradient(colorgradient_.inverted())
                    : setGradient(colorgradient_);
}

void ColorMap2D::setname_colormap(const QString &value) {
  setName(value);
  colorScale_->setLabel(value);
}

void ColorMap2D::setcolormapscalewidth_colormap(const int width) {
  colorScale_->setBarWidth(width);
}

void ColorMap2D::setcolormapscaleticklabelformat_axis(
    const Axis2D::AxisLabelFormat &axisformat) {
  switch (axisformat) {
    case Axis2D::AxisLabelFormat::e:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("e"));
      break;
    case Axis2D::AxisLabelFormat::eb:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("eb"));
      break;
    case Axis2D::AxisLabelFormat::ebc:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("ebc"));
      break;
    case Axis2D::AxisLabelFormat::E:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("E"));
      break;
    case Axis2D::AxisLabelFormat::f:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("f"));
      break;
    case Axis2D::AxisLabelFormat::g:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("g"));
      break;
    case Axis2D::AxisLabelFormat::gb:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("gb"));
      break;
    case Axis2D::AxisLabelFormat::gbc:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("gbc"));
      break;
    case Axis2D::AxisLabelFormat::G:
      colorScale_->axis()->setNumberFormat(QString::fromLatin1("G"));
      break;
  }
}

void ColorMap2D::save(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("colormap"));
  xmlwriter->writeAttribute(QString::fromLatin1("matrix"), matrix_->name());
  (interpolate())
      ? xmlwriter->writeAttribute(QString::fromLatin1("interpolate"), QString::fromLatin1("true"))
                  : xmlwriter->writeAttribute(QString::fromLatin1("interpolate"), QString::fromLatin1("false"));
  (tightBoundary()) ? xmlwriter->writeAttribute(QString::fromLatin1("tightboundary"), QString::fromLatin1("true"))
                    : xmlwriter->writeAttribute(QString::fromLatin1("tightboundary"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("levelcount"),
                            QString::number(getlevelcount_colormap()));
  switch (getgradient_colormap()) {
    case ColorMap2D::Gradient::Hot:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("hot"));
      break;
    case ColorMap2D::Gradient::Ion:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("ion"));
      break;
    case ColorMap2D::Gradient::Jet:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("jet"));
      break;
    case ColorMap2D::Gradient::Cold:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("cold"));
      break;
    case ColorMap2D::Gradient::Hues:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("hues"));
      break;
    case ColorMap2D::Gradient::Night:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("night"));
      break;
    case ColorMap2D::Gradient::Polar:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("polar"));
      break;
    case ColorMap2D::Gradient::candy:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("candy"));
      break;
    case ColorMap2D::Gradient::Thermal:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("thermal"));
      break;
    case ColorMap2D::Gradient::Spectrum:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("spectrum"));
      break;
    case ColorMap2D::Gradient::Geography:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("geography"));
      break;
    case ColorMap2D::Gradient::Grayscale:
      xmlwriter->writeAttribute(QString::fromLatin1("gradient"), QString::fromLatin1("grayscale"));
      break;
  }
  (getgradientinverted_colormap())
      ? xmlwriter->writeAttribute(QString::fromLatin1("invertgradient"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("invertgradient"), QString::fromLatin1("false"));
  (getgradientperiodic_colormap())
      ? xmlwriter->writeAttribute(QString::fromLatin1("periodicgradient"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("periodicgradient"), QString::fromLatin1("false"));
  xmlwriter->writeStartElement(QString::fromLatin1("scale"));
  (getcolormapscale_colormap()->visible())
      ? xmlwriter->writeAttribute(QString::fromLatin1("mapscalevisible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("mapscalevisible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("width"),
                            QString::number(getcolormapscalewidth_colormap()));
  (getcolormapscale_colormap()->axis()->visible())
      ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1(
          "visible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(
      QString::fromLatin1("offset"), QString::number(getcolormapscale_colormap()->axis()->offset()));
  xmlwriter->writeAttribute(
      QString::fromLatin1("from"),
      QString::number(getcolormapscale_colormap()->axis()->range().lower));
  xmlwriter->writeAttribute(
      QString::fromLatin1("to"),
      QString::number(getcolormapscale_colormap()->axis()->range().upper));
  switch (dataScaleType()) {
    case QCPAxis::ScaleType::stLinear:
      xmlwriter->writeAttribute( QString::fromLatin1("scaletype"),  QString::fromLatin1("linear"));
      break;
    case QCPAxis::ScaleType::stLogarithmic:
      xmlwriter->writeAttribute( QString::fromLatin1("scaletype"),  QString::fromLatin1("logarithemic"));
      break;
  }
  (getcolormapscale_colormap()->axis()->rangeReversed()) ? xmlwriter->writeAttribute(
      QString::fromLatin1("inverted"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute( QString::fromLatin1("inverted"),  QString::fromLatin1("false"));
  (getcolormapscale_colormap()->axis()->antialiased()) ? xmlwriter->writeAttribute(
      QString::fromLatin1("antialias"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute( QString::fromLatin1("antialias"),  QString::fromLatin1("false"));
  xmlwriter->writePen(getcolormapscale_colormap()->axis()->basePen());
  xmlwriter->writeStartElement( QString::fromLatin1("label"));
  xmlwriter->writeAttribute( QString::fromLatin1("text"), getname_colormap());
  xmlwriter->writeAttribute(
       QString::fromLatin1("padding"),
      QString::number(getcolormapscale_colormap()->axis()->labelPadding()));
  xmlwriter->writeFont(getcolormapscale_colormap()->axis()->labelFont(),
                       getcolormapscale_colormap()->axis()->labelColor());
  xmlwriter->writeEndElement();
  // Ticks
  xmlwriter->writeStartElement( QString::fromLatin1("ticks"));
  (getcolormapscale_colormap()->axis()->ticks()) ? xmlwriter->writeAttribute(
      QString::fromLatin1("visible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute( QString::fromLatin1("visible"),  QString::fromLatin1("false"));
  xmlwriter->writeAttribute(
       QString::fromLatin1("in"),
      QString::number(getcolormapscale_colormap()->axis()->tickLengthIn()));
  xmlwriter->writeAttribute(
       QString::fromLatin1("out"),
      QString::number(getcolormapscale_colormap()->axis()->tickLengthOut()));
  xmlwriter->writePen(getcolormapscale_colormap()->axis()->tickPen());
  xmlwriter->writeEndElement();
  // Subticks
  xmlwriter->writeStartElement( QString::fromLatin1("subticks"));
  (getcolormapscale_colormap()->axis()->subTicks()) ? xmlwriter->writeAttribute(
      QString::fromLatin1("visible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute( QString::fromLatin1("visible"),  QString::fromLatin1("false"));
  xmlwriter->writeAttribute(
       QString::fromLatin1("in"),
      QString::number(getcolormapscale_colormap()->axis()->subTickLengthIn()));
  xmlwriter->writeAttribute(
       QString::fromLatin1("out"),
      QString::number(getcolormapscale_colormap()->axis()->subTickLengthOut()));
  xmlwriter->writePen(getcolormapscale_colormap()->axis()->subTickPen());
  xmlwriter->writeEndElement();
  // Tick Labels
  xmlwriter->writeStartElement( QString::fromLatin1("ticklabels"));
  (getcolormapscale_colormap()->axis()->tickLabels()) ? xmlwriter->writeAttribute(
      QString::fromLatin1("visible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute( QString::fromLatin1("visible"),  QString::fromLatin1("false"));
  xmlwriter->writeAttribute(
       QString::fromLatin1("padding"),
      QString::number(getcolormapscale_colormap()->axis()->tickLabelPadding()));
  xmlwriter->writeAttribute(
       QString::fromLatin1("rotation"),
      QString::number(
          getcolormapscale_colormap()->axis()->tickLabelRotation()));
  switch (getcolormapscale_colormap()->axis()->tickLabelSide()) {
    case QCPAxis::LabelSide::lsInside:
      xmlwriter->writeAttribute( QString::fromLatin1("side"),  QString::fromLatin1("up"));
      break;
    case QCPAxis::LabelSide::lsOutside:
      xmlwriter->writeAttribute( QString::fromLatin1("side"),  QString::fromLatin1("down"));
      break;
  }
  switch (getcolormapscaleticklabelformat_axis()) {
    case Axis2D::AxisLabelFormat::E:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("E"));
      break;
    case Axis2D::AxisLabelFormat::G:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("G"));
      break;
    case Axis2D::AxisLabelFormat::e:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("e"));
      break;
    case Axis2D::AxisLabelFormat::eb:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("eb"));
      break;
    case Axis2D::AxisLabelFormat::ebc:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("ebc"));
      break;
    case Axis2D::AxisLabelFormat::f:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("f"));
      break;
    case Axis2D::AxisLabelFormat::g:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("g"));
      break;
    case Axis2D::AxisLabelFormat::gb:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("gb"));
      break;
    case Axis2D::AxisLabelFormat::gbc:
      xmlwriter->writeAttribute( QString::fromLatin1("format"),  QString::fromLatin1("gbc"));
      break;
  }
  xmlwriter->writeAttribute(
       QString::fromLatin1("precision"),
      QString::number(getcolormapscale_colormap()->axis()->numberPrecision()));
  xmlwriter->writeFont(getcolormapscale_colormap()->axis()->tickLabelFont(),
                       getcolormapscale_colormap()->axis()->tickLabelColor());
  xmlwriter->writeEndElement();
  xmlwriter->writeEndElement();
  xmlwriter->writeEndElement();
}

bool ColorMap2D::load(XmlStreamReader *xmlreader) {
  bool ok;
  // interpolate
  bool intpo = xmlreader->readAttributeBool(QString::fromLatin1("interpolate"), &ok);
  (ok) ? setInterpolate(intpo)
       : xmlreader->raiseWarning(
             tr("ColorMap2D interpolate property setting error"));
  // tightboundary
  bool tgtbny = xmlreader->readAttributeBool(QString::fromLatin1("tightboundary"), &ok);
  (ok) ? setTightBoundary(tgtbny)
       : xmlreader->raiseWarning(
             tr("ColorMap2D tightboundry property setting error"));
  // levelcount
  int lvlcnt = xmlreader->readAttributeInt(QString::fromLatin1("levelcount"), &ok);
  (ok) ? setlevelcount_colormap(lvlcnt)
       : xmlreader->raiseWarning(
             tr("ColorMap2D levelcount property setting error"));
  // gradient
  QString gdnt = xmlreader->readAttributeString(QString::fromLatin1("gradient"), &ok);
  if (ok) {
    if (gdnt == QString::fromLatin1("hot")) {
      setgradient_colormap(ColorMap2D::Gradient::Hot);
    } else if (gdnt == QString::fromLatin1("ion")) {
      setgradient_colormap(ColorMap2D::Gradient::Ion);
    } else if (gdnt == QString::fromLatin1("jet")) {
      setgradient_colormap(ColorMap2D::Gradient::Jet);
    } else if (gdnt == QString::fromLatin1("cold")) {
      setgradient_colormap(ColorMap2D::Gradient::Cold);
    } else if (gdnt == QString::fromLatin1("hues")) {
      setgradient_colormap(ColorMap2D::Gradient::Hues);
    } else if (gdnt == QString::fromLatin1("night")) {
      setgradient_colormap(ColorMap2D::Gradient::Night);
    } else if (gdnt == QString::fromLatin1("polar")) {
      setgradient_colormap(ColorMap2D::Gradient::Polar);
  } else if (gdnt == QString::fromLatin1("candy")) {
      setgradient_colormap(ColorMap2D::Gradient::candy);
    } else if (gdnt == QString::fromLatin1("thermal")) {
      setgradient_colormap(ColorMap2D::Gradient::Thermal);
    } else if (gdnt == QString::fromLatin1("spectrum")) {
      setgradient_colormap(ColorMap2D::Gradient::Spectrum);
    } else if (gdnt == QString::fromLatin1("geography")) {
      setgradient_colormap(ColorMap2D::Gradient::Geography);
    } else if (gdnt == QString::fromLatin1("grayscale")) {
      setgradient_colormap(ColorMap2D::Gradient::Grayscale);
    } else {
      qDebug() << "unknown gradient parameter: xml";
    }
  } else
    xmlreader->raiseWarning(tr("ColorMap2D gradient property setting error"));

  // invertgradient
  bool invgra = xmlreader->readAttributeBool(QString::fromLatin1("invertgradient"), &ok);
  (ok) ? setgradientinverted_colormap(invgra)
       : xmlreader->raiseWarning(
             tr("ColorMap2D gradient invert property setting error"));
  // periodicgradient
  bool pergra = xmlreader->readAttributeBool(QString::fromLatin1("periodicgradient"), &ok);
  (ok) ? setgradientperiodic_colormap(pergra)
       : xmlreader->raiseWarning(
             tr("ColorMap2D gradient periodic property setting error"));

  while (!xmlreader->atEnd()) {
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("colormap")) break;

    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("scale")) {
      // color map scale visible
      bool mapv = xmlreader->readAttributeBool(QString::fromLatin1("mapscalevisible"), &ok);
      (ok) ? getcolormapscale_colormap()->setVisible(mapv)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D mapscale visible property setting error"));
      // levelcount
      int wdt = xmlreader->readAttributeInt(QString::fromLatin1("width"), &ok);
      (ok) ? setcolormapscalewidth_colormap(wdt)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale width property setting error"));
      // visible
      bool sv = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
      (ok) ? getcolormapscale_colormap()->axis()->setVisible(sv)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale visible property setting error"));
      // offset
      int ofst = xmlreader->readAttributeInt(QString::fromLatin1("offset"), &ok);
      (ok) ? getcolormapscale_colormap()->axis()->setOffset(ofst)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale offset property setting error"));
      // from
      double frm = xmlreader->readAttributeDouble(QString::fromLatin1("from"), &ok);
      (ok) ? getcolormapscale_colormap()->axis()->setRange(
                 frm, getcolormapscale_colormap()->axis()->range().upper)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale from property setting error"));
      // to
      double to = xmlreader->readAttributeDouble(QString::fromLatin1("to"), &ok);
      (ok) ? getcolormapscale_colormap()->axis()->setRange(
                 getcolormapscale_colormap()->axis()->range().lower, to)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale to property setting error"));
      // scale type
      QString scaletype = xmlreader->readAttributeString(QString::fromLatin1("scaletype"), &ok);
      if (ok) {
        if (scaletype == QString::fromLatin1("linear")) {
          setDataScaleType(QCPAxis::ScaleType::stLinear);
        } else if (scaletype == QString::fromLatin1("logarithemic")) {
          setDataScaleType(QCPAxis::ScaleType::stLogarithmic);
        }
      } else
        xmlreader->raiseWarning(
            tr("ColorMap2D scale type property setting error"));
      // scale inverted
      bool invrt = xmlreader->readAttributeBool(QString::fromLatin1("inverted"), &ok);
      (ok) ? getcolormapscale_colormap()->axis()->setRangeReversed(invrt)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale inverted property setting error"));
      // scale antialias
      bool ant = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
      (ok) ? getcolormapscale_colormap()->axis()->setAntialiased(ant)
           : xmlreader->raiseWarning(
                 tr("ColorMap2D scale antialias property setting error"));
      // scale pen property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
        // pen
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
          QPen strokep = xmlreader->readPen(&ok);
          if (ok) {
            getcolormapscale_colormap()->axis()->setBasePen(strokep);
          } else
            xmlreader->raiseWarning(
                tr("ColorMap2D scale pen property setting error"));
        }
      }
      // label property
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("label")) break;
        // label text
        QString lbltxt = xmlreader->readAttributeString(QString::fromLatin1("text"), &ok);
        (ok) ? setname_colormap(lbltxt)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D label text property setting error"));
        // label padding
        int lblpadding = xmlreader->readAttributeInt(QString::fromLatin1("padding"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setLabelPadding(lblpadding)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D label padding property setting error"));
        // label font
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("font")) break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("font")) {
            QPair<QFont, QColor> fontpair = xmlreader->readFont(&ok);
            if (ok) {
              getcolormapscale_colormap()->axis()->setLabelFont(fontpair.first);
              getcolormapscale_colormap()->axis()->setLabelColor(
                  fontpair.second);
            } else
              xmlreader->raiseWarning(
                  tr("ColorMap2D font & color property setting error"));
          }
        }
      }
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("ticks")) break;
        // tick visible property
        bool tickvisible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
        if (ok)
          getcolormapscale_colormap()->axis()->setTicks(tickvisible);
        else
          xmlreader->raiseWarning(
              tr("ColorMap2D tick visible property setting error"));
        // Ticks in
        int in = xmlreader->readAttributeInt(QString::fromLatin1("in"), &ok);
        if (ok)
          getcolormapscale_colormap()->axis()->setTickLengthIn(in);
        else
          xmlreader->raiseWarning(
              tr("ColorMap2D Tick length in property setting error"));
        // Tick out
        int out = xmlreader->readAttributeInt(QString::fromLatin1("out"), &ok);
        if (ok)
          getcolormapscale_colormap()->axis()->setTickLengthOut(out);
        else
          xmlreader->raiseWarning(
              tr("ColorMap2D Tick Length out property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
            QPen p = xmlreader->readPen(&ok);
            if (ok) {
              getcolormapscale_colormap()->axis()->setTickPen(p);
            } else
              xmlreader->raiseWarning(
                  tr("Axis2D tick pen property setting error"));
          }
        }
      }
      // Sub Ticks element
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("subticks")) break;
        // visible property
        bool subtickvisible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setSubTicks(subtickvisible)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D subtick visible property setting error"));
        // Ticks in
        int in = xmlreader->readAttributeInt(QString::fromLatin1("in"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setSubTickLengthIn(in)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D subTick length in property setting error"));
        // out length
        int out = xmlreader->readAttributeInt(QString::fromLatin1("out"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setSubTickLengthOut(out)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D subTick Length out property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
            QPen p = xmlreader->readPen(&ok);
            (ok) ? getcolormapscale_colormap()->axis()->setSubTickPen(p)
                 : xmlreader->raiseWarning(
                       tr("ColorMap2D subtick pen property setting error"));
          }
        }
      }
      // Tick label element
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("ticklabels"))
          break;

        // visible property
        bool ticklabelvisible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setTickLabels(
                   ticklabelvisible)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D tick label visible property setting error"));
        // Tick label padding
        int ticklabelpadding = xmlreader->readAttributeInt(QString::fromLatin1("padding"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setTickLabelPadding(
                   ticklabelpadding)
             : xmlreader->raiseWarning(tr(
                   "ColorMap2D tick label padding in property setting error"));
        // Tick Label Rotation
        double ticklabelrotation =
            xmlreader->readAttributeDouble(QString::fromLatin1("rotation"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setTickLabelRotation(
                   ticklabelrotation)
             : xmlreader->raiseWarning(
                   tr("ColorMap2D tick label rotation property setting error"));
        // Tick label side
        QString ticklabelside = xmlreader->readAttributeString(QString::fromLatin1("side"), &ok);
        if (ok)
          if (ticklabelside == QString::fromLatin1("up"))
            getcolormapscale_colormap()->axis()->setTickLabelSide(
                QCPAxis::LabelSide::lsInside);
          else if (ticklabelside == QString::fromLatin1("down"))
            getcolormapscale_colormap()->axis()->setTickLabelSide(
                QCPAxis::LabelSide::lsOutside);
          else
            xmlreader->raiseWarning(
                tr("ColorMap2D tick label side property setting error"));
        else
          xmlreader->raiseWarning(
              tr("ColorMap2D tick label side property setting error"));
        // tick label format
        QString ticklabelformat = xmlreader->readAttributeString(QString::fromLatin1("format"), &ok);
        if (ok)
          if (ticklabelformat == QString::fromLatin1("E"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::E);
          else if (ticklabelformat == QString::fromLatin1("G"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::G);
          else if (ticklabelformat == QString::fromLatin1("e"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::e);
          else if (ticklabelformat == QString::fromLatin1("eb"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::eb);
          else if (ticklabelformat == QString::fromLatin1("ebc"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::ebc);
          else if (ticklabelformat == QString::fromLatin1("f"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::f);
          else if (ticklabelformat == QString::fromLatin1("g"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::g);
          else if (ticklabelformat == QString::fromLatin1("gb"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::gb);
          else if (ticklabelformat == QString::fromLatin1("gbc"))
            setcolormapscaleticklabelformat_axis(Axis2D::AxisLabelFormat::gbc);
          else
            xmlreader->raiseWarning(
                tr("ColorMap2D tick label format property setting error"));
        else
          xmlreader->raiseWarning(
              tr("ColorMap2D tick label format property setting error"));
        // Tick label precision
        int ticklabelprecision = xmlreader->readAttributeInt(QString::fromLatin1("precision"), &ok);
        (ok) ? getcolormapscale_colormap()->axis()->setNumberPrecision(
                   ticklabelprecision)
             : xmlreader->raiseWarning(tr(
                   "ColorMap2D tick label precision property setting error"));
        while (!xmlreader->atEnd()) {
          xmlreader->readNext();
          if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("font")) break;
          if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("font")) {
            QPair<QFont, QColor> fontpair = xmlreader->readFont(&ok);
            if (ok) {
              getcolormapscale_colormap()->axis()->setTickLabelFont(
                  fontpair.first);
              getcolormapscale_colormap()->axis()->setTickLabelColor(
                  fontpair.second);
            } else
              xmlreader->raiseWarning(
                  tr("ColorMap2D font & color property setting error"));
          }
        }
      }
    }
    xmlreader->readNext();
  }

  return !xmlreader->hasError();
}
