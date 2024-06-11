#include "PreCompiled.h"

#include "LineItem2D.h"

#include "AxisRect2D.h"
#include "Plot2D.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"

const int LineItem2D::selectionpixelsize_ = 10;

LineItem2D::LineItem2D(AxisRect2D *axisrect, Plot2D *plot)
    : QCPItemLine(plot),
      axisrect_(axisrect),
      ending_(new QCPLineEnding),
      starting_(new QCPLineEnding),
      layername_(QString::fromLatin1("<LineItem>") + QDateTime::currentDateTime().toString(
                                             QString::fromLatin1("yyyy:MM:dd:hh:mm:ss:zzz"))),
      dragginglineitem_(false),
      draggingendlineitem_(false),
      draggingstartlineitem_(false),
      lineitemclicked_(false),
      cursorshape_(axisrect->getParentPlot2D()->cursor()) {
  if (axisrect_->getAxes2D().count() > 0) {
    QThread::msleep(1);
    parentPlot()->addLayer(layername_, axisrect_->getAxes2D().at(0)->layer(),
                           QCustomPlot::limBelow);
    setLayer(layername_);
  }
  layer()->setMode(QCPLayer::LayerMode::lmBuffered);
  setClipAxisRect(axisrect_);
  setClipToAxisRect(true);
  setHead(*starting_);
  setTail(*ending_);
}

LineItem2D::~LineItem2D() {
  delete starting_;
  delete ending_;
  parentPlot()->removeLayer(layer());
}

AxisRect2D *LineItem2D::getaxisrect() const { return axisrect_; }

QColor LineItem2D::getstrokecolor_lineitem() const { return pen().color(); }

double LineItem2D::getstrokethickness_lineitem() const {
  return pen().widthF();
}

Qt::PenStyle LineItem2D::getstrokestyle_lineitem() const {
  return pen().style();
}

QCPLineEnding::EndingStyle LineItem2D::getendstyle_lineitem(
    const LineItem2D::LineEndLocation &location) const {
  if (location == LineItem2D::LineEndLocation::Start) {
    return starting_->style();
  } else {
    return ending_->style();
  }
}

double LineItem2D::getendwidth_lineitem(
    const LineItem2D::LineEndLocation &location) const {
  if (location == LineItem2D::LineEndLocation::Start) {
    return starting_->width();
  } else {
    return ending_->width();
  }
}

double LineItem2D::getendlength_lineitem(
    const LineItem2D::LineEndLocation &location) const {
  if (location == LineItem2D::LineEndLocation::Start) {
    return starting_->length();
  } else {
    return ending_->length();
  }
}

void LineItem2D::setstrokecolor_lineitem(const QColor &color) {
  QPen p = pen();
  p.setColor(color);
  setPen(p);
}

void LineItem2D::setstrokethickness_lineitem(const double value) {
  QPen p = pen();
  p.setWidthF(value);
  setPen(p);
}

void LineItem2D::setstrokestyle_lineitem(const Qt::PenStyle &style) {
  QPen p = pen();
  p.setStyle(style);
  setPen(p);
}

void LineItem2D::setendstyle_lineitem(const LineEndLocation &location,
                                      const QCPLineEnding::EndingStyle &style) {
  switch (location) {
    case LineEndLocation::Start:
      starting_->setStyle(style);
      setHead(*starting_);
      break;
    case LineEndLocation::Stop:
      ending_->setStyle(style);
      setTail(*ending_);
      break;
  }
}

void LineItem2D::setendwidth_lineitem(
    const double value, const LineItem2D::LineEndLocation &location) {
  switch (location) {
    case LineEndLocation::Start:
      starting_->setWidth(value);
      setHead(*starting_);
      break;
    case LineEndLocation::Stop:
      ending_->setWidth(value);
      setTail(*ending_);
      break;
  }
}

void LineItem2D::setendlength_lineitem(
    const double value, const LineItem2D::LineEndLocation &location) {
  switch (location) {
    case LineEndLocation::Start:
      starting_->setLength(value);
      setHead(*starting_);
      break;
    case LineEndLocation::Stop:
      ending_->setLength(value);
      setTail(*ending_);
      break;
  }
}

QString LineItem2D::getendstylestring_lineitem(
    const QCPLineEnding::EndingStyle endstyle) const {
  QString end = QString::fromLatin1("none");
  switch (endstyle) {
    case QCPLineEnding::EndingStyle::esBar:
      end = QString::fromLatin1("bar");
      break;
    case QCPLineEnding::EndingStyle::esDisc:
      end = QString::fromLatin1("disc");
      break;
    case QCPLineEnding::EndingStyle::esNone:
      end = QString::fromLatin1("none");
      break;
    case QCPLineEnding::EndingStyle::esSquare:
      end = QString::fromLatin1("square");
      break;
    case QCPLineEnding::EndingStyle::esDiamond:
      end = QString::fromLatin1("diamond");
      break;
    case QCPLineEnding::EndingStyle::esHalfBar:
      end = QString::fromLatin1("halfbar");
      break;
    case QCPLineEnding::EndingStyle::esFlatArrow:
      end = QString::fromLatin1("flatarrow");
      break;
    case QCPLineEnding::EndingStyle::esLineArrow:
      end = QString::fromLatin1("linearrow");
      break;
    case QCPLineEnding::EndingStyle::esSkewedBar:
      end = QString::fromLatin1("skewedbar");
      break;
    case QCPLineEnding::EndingStyle::esSpikeArrow:
      end = QString::fromLatin1("spikearrow");
      break;
  }
  return end;
}

QCPLineEnding::EndingStyle LineItem2D::getendstyleenum_lineitem(
    const QString end) const {
  QCPLineEnding::EndingStyle endstyle = QCPLineEnding::EndingStyle::esNone;
  if (end == QString::fromLatin1("bar")) {
    endstyle = QCPLineEnding::EndingStyle::esBar;
  } else if (end == QString::fromLatin1("disc")) {
    endstyle = QCPLineEnding::EndingStyle::esDisc;
  } else if (end == QString::fromLatin1("none")) {
    endstyle = QCPLineEnding::EndingStyle::esNone;
  } else if (end == QString::fromLatin1("square")) {
    endstyle = QCPLineEnding::EndingStyle::esSquare;
  } else if (end == QString::fromLatin1("diamond")) {
    endstyle = QCPLineEnding::EndingStyle::esDiamond;
  } else if (end == QString::fromLatin1("halfbar")) {
    endstyle = QCPLineEnding::EndingStyle::esHalfBar;
  } else if (end == QString::fromLatin1("flatarrow")) {
    endstyle = QCPLineEnding::EndingStyle::esFlatArrow;
  } else if (end == QString::fromLatin1("linearrow")) {
    endstyle = QCPLineEnding::EndingStyle::esLineArrow;
  } else if (end == QString::fromLatin1("skewedbar")) {
    endstyle = QCPLineEnding::EndingStyle::esSkewedBar;
  } else if (end == QString::fromLatin1("spikearrow")) {
    endstyle = QCPLineEnding::EndingStyle::esSpikeArrow;
  }
  return endstyle;
}

void LineItem2D::save(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("lineitem"));
  xmlwriter->writeAttribute(QString::fromLatin1("x1"),
                            QString::number(position(QString::fromLatin1("start"))->coords().x()));
  xmlwriter->writeAttribute(QString::fromLatin1("y1"),
                            QString::number(position(QString::fromLatin1("start"))->coords().y()));
  xmlwriter->writeAttribute(QString::fromLatin1("x2"),
                            QString::number(position(QString::fromLatin1("end"))->coords().x()));
  xmlwriter->writeAttribute(QString::fromLatin1("y2"),
                            QString::number(position(QString::fromLatin1("end"))->coords().y()));
  (antialiased()) ? xmlwriter->writeAttribute(
      QString::fromLatin1("antialias"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(
          QString::fromLatin1("antialias"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(
      QString::fromLatin1("startstyle"),
      getendstylestring_lineitem(getendstyle_lineitem(LineEndLocation::Start)));
  xmlwriter->writeAttribute(QString::fromLatin1("startwidth"), QString::number(starting_->width()));
  xmlwriter->writeAttribute(QString::fromLatin1("startlength"),
                            QString::number(starting_->length()));
  xmlwriter->writeAttribute(
      QString::fromLatin1("endstyle"),
      getendstylestring_lineitem(getendstyle_lineitem(LineEndLocation::Stop)));
  xmlwriter->writeAttribute(QString::fromLatin1("endwidth"), QString::number(ending_->width()));
  xmlwriter->writeAttribute(QString::fromLatin1("endlength"), QString::number(ending_->length()));
  xmlwriter->writePen(pen());
  xmlwriter->writeEndElement();
}

bool LineItem2D::load(XmlStreamReader *xmlreader) {
  if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("lineitem")) {
    bool ok;

    // position
    double x1 = xmlreader->readAttributeDouble(QString::fromLatin1("x1"), &ok);
    if (ok) {
      double y1 = xmlreader->readAttributeDouble(QString::fromLatin1("y1"), &ok);
      if (ok) {
        double x2 = xmlreader->readAttributeDouble(QString::fromLatin1("x2"), &ok);
        if (ok) {
          double y2 = xmlreader->readAttributeDouble(QString::fromLatin1("y2"), &ok);
          if (ok) {
            position(QString::fromLatin1("start"))->setCoords(QPointF(x1, y1));
            position(QString::fromLatin1("end"))->setCoords(QPointF(x2, y2));
          } else
            xmlreader->raiseWarning(
                tr("LineItem2D set position y2 property setting error"));
        } else
          xmlreader->raiseWarning(
              tr("LineItem2D set position x2 property setting error"));
      } else
        xmlreader->raiseWarning(
            tr("LineItem2D set position y1 property setting error"));
    } else
      xmlreader->raiseWarning(
          tr("LineItem2D set position x1 property setting error"));

    // antialias property
    bool antialias = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
    (ok) ? setAntialiased(antialias)
         : xmlreader->raiseWarning(
               tr("LineItem2D antialias property setting error"));

    QString startstyle = xmlreader->readAttributeString(QString::fromLatin1("startstyle"), &ok);
    (ok) ? setendstyle_lineitem(LineEndLocation::Start,
                                getendstyleenum_lineitem(startstyle))
         : xmlreader->raiseWarning(
               tr("LineItem2D startstyle property setting error"));

    int startwidth = xmlreader->readAttributeInt(QString::fromLatin1("startwidth"), &ok);
    (ok) ? setendwidth_lineitem(startwidth, LineEndLocation::Start)
         : xmlreader->raiseWarning(
               tr("LineItem2D startwidth property setting error"));

    int startlength = xmlreader->readAttributeInt(QString::fromLatin1("startlength"), &ok);
    (ok) ? setendlength_lineitem(startlength, LineEndLocation::Start)
         : xmlreader->raiseWarning(
               tr("LineItem2D startlength property setting error"));

    QString endstyle = xmlreader->readAttributeString(QString::fromLatin1("endstyle"), &ok);
    (ok) ? setendstyle_lineitem(LineEndLocation::Stop,
                                getendstyleenum_lineitem(endstyle))
         : xmlreader->raiseWarning(
               tr("LineItem2D endstyle property setting error"));

    int endwidth = xmlreader->readAttributeInt(QString::fromLatin1("endwidth"), &ok);
    (ok) ? setendwidth_lineitem(endwidth, LineEndLocation::Stop)
         : xmlreader->raiseWarning(
               tr("LineItem2D endwidth property setting error"));

    int endlength = xmlreader->readAttributeInt(QString::fromLatin1("endlength"), &ok);
    (ok) ? setendlength_lineitem(endlength, LineEndLocation::Stop)
         : xmlreader->raiseWarning(
               tr("LineItem2D endlength property setting error"));

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
              tr("LineItem2D strokepen property setting error"));
      }
    }
  } else  // no element
    xmlreader->raiseError(tr("no LineItem2D element found"));

  return !xmlreader->hasError();
}

void LineItem2D::draw(QCPPainter *painter) {
  QCPItemLine::draw(painter);
  if (lineitemclicked_) {
    painter->setBrush(QBrush(QColor(0, 0, 0, 50)));
    painter->setPen(QPen(Qt::NoPen));
    painter->setAntialiasing(false);
    QRectF rect;
    rect.setCoords(this->start->pixelPosition().x() - selectionpixelsize_,
                   this->start->pixelPosition().y() - selectionpixelsize_,
                   this->start->pixelPosition().x() + selectionpixelsize_,
                   this->start->pixelPosition().y() + selectionpixelsize_);
    painter->drawRect(rect);
    rect.adjust(+2, +2, -3, -3);
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->setPen(QColor(Qt::red));
    painter->setAntialiasing(true);
    painter->drawEllipse(rect);
    painter->setBrush(QBrush(QColor(0, 0, 0, 50)));
    painter->setPen(QPen(Qt::NoPen));
    painter->setAntialiasing(false);
    rect.setCoords(this->end->pixelPosition().x() - selectionpixelsize_,
                   this->end->pixelPosition().y() - selectionpixelsize_,
                   this->end->pixelPosition().x() + selectionpixelsize_,
                   this->end->pixelPosition().y() + selectionpixelsize_);
    painter->drawRect(rect);
    rect.adjust(+2, +2, -3, -3);
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->setPen(QColor(Qt::red));
    painter->setAntialiasing(true);
    painter->drawLine(rect.topLeft(), rect.bottomRight());
    painter->drawLine(rect.topRight(), rect.bottomLeft());
  }
}

void LineItem2D::mousePressEvent(QMouseEvent *event, const QVariant &details) {
  Q_UNUSED(details);
  if (event->button() == Qt::LeftButton) {
    if (selectTest(event->pos(), false) > 0) {
      lineitemclicked_ = true;
      if (end->pixelPosition().x() > (event->pos().x() - selectionpixelsize_) &&
          end->pixelPosition().x() < (event->pos().x() + selectionpixelsize_) &&
          end->pixelPosition().y() > (event->pos().y() - selectionpixelsize_) &&
          end->pixelPosition().y() < (event->pos().y() + selectionpixelsize_)) {
        draggingendlineitem_ = true;
        parentPlot()->setCursor(Qt::CursorShape::CrossCursor);
      } else if (start->pixelPosition().x() >
                     (event->pos().x() - selectionpixelsize_) &&
                 start->pixelPosition().x() <
                     (event->pos().x() + selectionpixelsize_) &&
                 start->pixelPosition().y() >
                     (event->pos().y() - selectionpixelsize_) &&
                 start->pixelPosition().y() <
                     (event->pos().y() + selectionpixelsize_)) {
        draggingstartlineitem_ = true;
        cursorshape_ = axisrect_->getParentPlot2D()->cursor();
        axisrect_->getParentPlot2D()->setCursor(Qt::CursorShape::CrossCursor);
      } else {
        draglineitemorigin_ = event->pos() - end->pixelPosition();
        draglineitemendin_ = event->pos() - start->pixelPosition();
        cursorshape_ = axisrect_->getParentPlot2D()->cursor();
        axisrect_->getParentPlot2D()->setCursor(
            Qt::CursorShape::ClosedHandCursor);
        dragginglineitem_ = true;
      }
    }
    this->layer()->replot();
  }
}

void LineItem2D::mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) {
  Q_UNUSED(startPos);
  QPointF eventpos = event->pos();
  if (draggingendlineitem_) {
    // set bounding rect for drag event
    if (event->pos().x() < axisrect_->left()) {
      eventpos.setX(axisrect_->left());
    }
    if (event->pos().x() > axisrect_->right()) {
      eventpos.setX(axisrect_->right());
    }
    if (event->pos().y() < axisrect_->top()) {
      eventpos.setY(axisrect_->top());
    }
    if (event->pos().y() > axisrect_->bottom()) {
      eventpos.setY(axisrect_->bottom());
    }
    end->setPixelPosition(eventpos);
    this->layer()->replot();
  } else if (draggingstartlineitem_) {
    QPoint eventpos = event->pos();
    if (event->pos().x() < axisrect_->left()) {
      eventpos.setX(axisrect_->left());
    }
    if (event->pos().x() > axisrect_->right()) {
      eventpos.setX(axisrect_->right());
    }
    if (event->pos().y() < axisrect_->top()) {
      eventpos.setY(axisrect_->top());
    }
    if (event->pos().y() > axisrect_->bottom()) {
      eventpos.setY(axisrect_->bottom());
    }
    start->setPixelPosition(eventpos);
    this->layer()->replot();
  } else if (dragginglineitem_) {
    start->setPixelPosition(eventpos - draglineitemendin_);
    end->setPixelPosition(eventpos - draglineitemorigin_);
    layer()->replot();
  }
}

void LineItem2D::mouseReleaseEvent(QMouseEvent *event,
                                   const QPointF &startPos) {
  Q_UNUSED(startPos);
  if (event->button() == Qt::LeftButton) {
    lineitemclicked_ = false;
    if (draggingendlineitem_) {
      draggingendlineitem_ = false;
      axisrect_->getParentPlot2D()->setCursor(cursorshape_);
      this->layer()->replot();
      Q_EMIT axisrect_->LineItem2DMoved();
    }
    if (draggingstartlineitem_) {
      draggingstartlineitem_ = false;
      axisrect_->getParentPlot2D()->setCursor(cursorshape_);
      this->layer()->replot();
      Q_EMIT axisrect_->LineItem2DMoved();
    }
    if (dragginglineitem_) {
      dragginglineitem_ = false;
      axisrect_->getParentPlot2D()->setCursor(cursorshape_);
      this->layer()->replot();
      Q_EMIT axisrect_->LineItem2DMoved();
    }
  }
}
