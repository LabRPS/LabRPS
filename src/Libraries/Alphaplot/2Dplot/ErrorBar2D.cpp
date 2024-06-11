#include "Precompiled.h"

#include "ErrorBar2D.h"

#include "Axis2D.h"
#include "Bar2D.h"
#include "Curve2D.h"
#include "DataManager2D.h"
#include "LineSpecial2D.h"
#include "Table.h"
#include "core/Utilities.h"
#include "future/core/column/Column.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"

ErrorBar2D::ErrorBar2D(Table *table, Column *errorcol, int from, int to,
                       Axis2D *xAxis, Axis2D *yAxis,
                       QCPErrorBars::ErrorType errortype,
                       LineSpecial2D *linespecial)
    : QCPErrorBars(xAxis, yAxis),
      xAxis_(xAxis),
      yAxis_(yAxis),
      errortype_(errortype),
      linespecial_(linespecial),
      curve_(nullptr),
      bar_(nullptr),
      errordata_(new DataBlockError(table, errorcol, from, to)) {
  layer()->setMode(QCPLayer::LayerMode::lmBuffered);
  setErrorType(errortype_);
  setData(errordata_->data());
  setDataPlottable(linespecial_);
  setAntialiased(false);
  setAntialiasedFill(false);
  setAntialiasedScatters(false);
}

ErrorBar2D::ErrorBar2D(Table *table, Column *errorcol, int from, int to,
                       Axis2D *xAxis, Axis2D *yAxis,
                       QCPErrorBars::ErrorType errortype, Curve2D *curve)
    : QCPErrorBars(xAxis, yAxis),
      xAxis_(xAxis),
      yAxis_(yAxis),
      errortype_(errortype),
      linespecial_(nullptr),
      curve_(curve),
      bar_(nullptr),
      errordata_(new DataBlockError(table, errorcol, from, to)) {
  setAntialiased(false);
  setErrorType(errortype_);
  setData(errordata_->data());
  setDataPlottable(curve_);
  setAntialiased(false);
  setAntialiasedFill(false);
  setAntialiasedScatters(false);
}

ErrorBar2D::ErrorBar2D(Table *table, Column *errorcol, int from, int to,
                       Axis2D *xAxis, Axis2D *yAxis,
                       QCPErrorBars::ErrorType errortype, Bar2D *bar)
    : QCPErrorBars(xAxis, yAxis),
      xAxis_(xAxis),
      yAxis_(yAxis),
      errortype_(errortype),
      linespecial_(nullptr),
      curve_(nullptr),
      bar_(bar),
      errordata_(new DataBlockError(table, errorcol, from, to)) {
  setErrorType(errortype_);
  setData(errordata_->data());
  setDataPlottable(bar_);
  setAntialiased(false);
  setAntialiasedFill(false);
  setAntialiasedScatters(false);
}

ErrorBar2D::~ErrorBar2D() { delete errordata_; }

void ErrorBar2D::setErrorData(Table *table, Column *errorcol, int from,
                              int to) {
  errordata_->regenerateDataBlock(table, errorcol, from, to);
  setData(errordata_->data());
}

bool ErrorBar2D::getfillstatus_errorbar() const {
  if (brush().style() == Qt::NoBrush) {
    return false;
  } else {
    return true;
  }
}

void ErrorBar2D::setfillstatus_errorbar(const bool status) {
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

void ErrorBar2D::save(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("errorbar"));
  switch (errortype_) {
    case QCPErrorBars::ErrorType::etKeyError:
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("x"));
      break;
    case QCPErrorBars::ErrorType::etValueError:
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("y"));
      break;
  }

  // data
  xmlwriter->writeAttribute(QString::fromLatin1("table"), errordata_->gettable()->name());
  xmlwriter->writeAttribute(QString::fromLatin1("errcolumn"), errordata_->geterrorcolumn()->name());
  xmlwriter->writeAttribute(QString::fromLatin1("from"), QString::number(errordata_->getfrom()));
  xmlwriter->writeAttribute(QString::fromLatin1("to"), QString::number(errordata_->getto()));

  xmlwriter->writeAttribute(QString::fromLatin1("whiskerwidth"), QString::number(whiskerWidth()));
  xmlwriter->writeAttribute(QString::fromLatin1("symbolgap"), QString::number(symbolGap()));
  (getfillstatus_errorbar()) ? xmlwriter->writeAttribute(QString::fromLatin1("fill"), QString::fromLatin1("true"))
                             : xmlwriter->writeAttribute(QString::fromLatin1("fill"), QString::fromLatin1("false"));
  (antialiasedFill()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialiasfill"), QString::fromLatin1("true"))
                      : xmlwriter->writeAttribute(QString::fromLatin1("antialiasfill"), QString::fromLatin1("false"));
  xmlwriter->writePen(pen());
  xmlwriter->writeBrush(brush());
  xmlwriter->writeEndElement();
}

bool ErrorBar2D::load(XmlStreamReader *xmlreader) {
  if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("errorbar")) {
    bool ok;

    // whiskerwidth property
    int whiskerwdth = xmlreader->readAttributeInt(QString::fromLatin1("whiskerwidth"), &ok);
    (ok) ? setWhiskerWidth(whiskerwdth)
         : xmlreader->raiseWarning(
               tr("ErrorBar2D whiskerwidth property setting error"));

    // symbolgap property
    int symbolgp = xmlreader->readAttributeInt(QString::fromLatin1("symbolgap"), &ok);
    (ok) ? setSymbolGap(symbolgp)
         : xmlreader->raiseWarning(
               tr("ErrorBar2D symbolgap property setting error"));

    // fill status property
    bool fill = xmlreader->readAttributeBool(QString::fromLatin1("fill"), &ok);
    (ok) ? setfillstatus_errorbar(fill)
         : xmlreader->raiseWarning(
               tr("ErrorBar2D fill status property setting error"));

    // antialiasfill status property
    bool antialiasf = xmlreader->readAttributeBool(QString::fromLatin1("antialiasfill"), &ok);
    (ok) ? setAntialiasedFill(antialiasf)
         : xmlreader->raiseWarning(
               tr("ErrorBar2D antialias fill property setting error"));

    // strokepen property
    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("pen")) break;
      // pen
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("pen")) {
        QPen strokep = xmlreader->readPen(&ok);
        if (ok)
          setPen(strokep);
        else
          xmlreader->raiseWarning(
              tr("ErrorBar2D strokepen property setting error"));
      }
    }

    // strokepen property
    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("brush")) break;
      // pen
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("brush")) {
        QBrush b = xmlreader->readBrush(&ok);
        if (ok)
          setBrush(b);
        else
          xmlreader->raiseWarning(
              tr("ErrorBar2D brush property setting error"));
      }
    }

  } else  // no element
    xmlreader->raiseError(tr("no ErrorBar2D item element found"));

  return !xmlreader->hasError();
}
