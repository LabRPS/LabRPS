#include "Precompiled.h"

#include "TextItem2D.h"

#include "AxisRect2D.h"
#include "Plot2D.h"
#include "core/Utilities.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"

#include <QPen>

TextItem2D::TextItem2D(AxisRect2D *axisrect, Plot2D *plot)
    : QCPItemText(plot),
      axisrect_(axisrect),
      layername_(QString::fromLatin1("<TextItem>") + QDateTime::currentDateTime().toString(QString::fromLatin1("yyyy:MM:dd:hh:mm:ss:zzz"))),
      draggingtextitem_(false),
      cursorshape_(axisrect->getParentPlot2D()->cursor()) {
  if (axisrect_->getAxes2D().count() > 0) {
    QThread::msleep(1);
    parentPlot()->addLayer(layername_, axisrect_->getAxes2D().at(0)->layer(),
                           QCustomPlot::limBelow);
    setLayer(layername_);
  }
  layer()->setMode(QCPLayer::LayerMode::lmBuffered);
  setClipToAxisRect(true);
  setClipAxisRect(axisrect_);
  setAntialiased(false);
  setstrokestyle_textitem(Qt::SolidLine);
  QBrush b = brush();
  b.setStyle(Qt::SolidPattern);
  b.setColor(Qt::white);
  setBrush(b);
  settextalignment_textitem(TextAlignment::CenterCenter);
}

TextItem2D::~TextItem2D() { parentPlot()->removeLayer(layer()); }

AxisRect2D *TextItem2D::getaxisrect() const { return axisrect_; }

QColor TextItem2D::getstrokecolor_textitem() const { return pen().color(); }

double TextItem2D::getstrokethickness_textitem() const {
  return pen().widthF();
}

Qt::PenStyle TextItem2D::getstrokestyle_textitem() const {
  return pen().style();
}

TextItem2D::TextAlignment TextItem2D::gettextalignment_textitem() const {
  return textalignment_;
}

void TextItem2D::setstrokecolor_textitem(const QColor &color) {
  QPen p = pen();
  p.setColor(color);
  setPen(p);
}

void TextItem2D::setstrokethickness_textitem(const double value) {
  QPen p = pen();
  p.setWidthF(value);
  setPen(p);
}

void TextItem2D::setstrokestyle_textitem(const Qt::PenStyle &style) {
  QPen p = pen();
  p.setStyle(style);
  setPen(p);
}

void TextItem2D::settextalignment_textitem(const TextAlignment &value) {
  textalignment_ = value;
  switch (value) {
    case TextItem2D::TextAlignment::TopLeft:
      setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
      break;
    case TextItem2D::TextAlignment::TopCenter:
      setTextAlignment(Qt::AlignTop | Qt::AlignHCenter);
      break;
    case TextItem2D::TextAlignment::TopRight:
      setTextAlignment(Qt::AlignTop | Qt::AlignRight);
      break;
    case TextItem2D::TextAlignment::CenterLeft:
      setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
      break;
    case TextItem2D::TextAlignment::CenterCenter:
      setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
      break;
    case TextItem2D::TextAlignment::CenterRight:
      setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      break;
    case TextItem2D::TextAlignment::BottomLeft:
      setTextAlignment(Qt::AlignBottom | Qt::AlignLeft);
      break;
    case TextItem2D::TextAlignment::BottomCenter:
      setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
      break;
    case TextItem2D::TextAlignment::BottomRight:
      setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
      break;
  }
}

void TextItem2D::setpixelposition_textitem(const QPointF &point) {
  position->setPixelPosition(point);
}

void TextItem2D::save(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("textitem"));
  double xposition = position->coords().x();
  double yposition = position->coords().y();
  xmlwriter->writeAttribute(QString::fromLatin1("xposition"), QString::number(xposition));
  xmlwriter->writeAttribute(QString::fromLatin1("yposition"), QString::number(yposition));
  switch (gettextalignment_textitem()) {
    case TextAlignment::TopLeft:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("topleft"));
      break;
    case TextAlignment::TopCenter:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("topcenter"));
      break;
    case TextAlignment::TopRight:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("topright"));
      break;
    case TextAlignment::CenterLeft:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("centerleft"));
      break;
    case TextAlignment::CenterCenter:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("centercenter"));
      break;
    case TextAlignment::CenterRight:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("centerright"));
      break;
    case TextAlignment::BottomLeft:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("bottomleft"));
      break;
    case TextAlignment::BottomCenter:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("bottomcenter"));
      break;
    case TextAlignment::BottomRight:
      xmlwriter->writeAttribute(QString::fromLatin1("textalignment"), QString::fromLatin1("bottomright"));
      break;
  }
  xmlwriter->writeAttribute(QString::fromLatin1("text"), text());
  xmlwriter->writeAttribute(QString::fromLatin1("rotation"), QString::number(rotation()));
  (antialiased()) ? xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("true"))
                  : xmlwriter->writeAttribute(QString::fromLatin1("antialias"), QString::fromLatin1("false"));
  xmlwriter->writeStartElement(QString::fromLatin1("margin"));
  xmlwriter->writeAttribute(QString::fromLatin1("left"), QString::number(padding().left()));
  xmlwriter->writeAttribute(QString::fromLatin1("top"), QString::number(padding().top()));
  xmlwriter->writeAttribute(QString::fromLatin1("right"), QString::number(padding().right()));
  xmlwriter->writeAttribute(QString::fromLatin1("bottom"), QString::number(padding().bottom()));
  xmlwriter->writeEndElement();
  xmlwriter->writeFont(font(), color());
  xmlwriter->writePen(pen());
  xmlwriter->writeBrush(brush());
  xmlwriter->writeEndElement();
}

bool TextItem2D::load(XmlStreamReader *xmlreader) {
  if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("textitem")) {
    bool ok;
    QPointF itemposition;
    // item X position property
    double positionx = xmlreader->readAttributeDouble(QString::fromLatin1("xposition"), &ok);
    if (ok) {
      itemposition.setX(positionx);
    } else {
      itemposition.setX(axisrect_->center().x());
      xmlreader->raiseWarning(
          tr("TextItem2D x position property setting error"));
    }
    // item Y position property
    double positiony = xmlreader->readAttributeDouble(QString::fromLatin1("yposition"), &ok);
    if (ok) {
      itemposition.setY(positiony);
    } else {
      itemposition.setY(axisrect_->center().y());
      xmlreader->raiseWarning(
          tr("TextItem2D y position property setting error"));
    }
    position->setCoords(itemposition);

    QString txtalign = xmlreader->readAttributeString(QString::fromLatin1("textalignment"), &ok);
    if (ok) {
      if (txtalign == QString::fromLatin1("topleft"))
        settextalignment_textitem(TextAlignment::TopLeft);
      else if (txtalign == QString::fromLatin1("topcenter"))
        settextalignment_textitem(TextAlignment::TopCenter);
      else if (txtalign == QString::fromLatin1("topright"))
        settextalignment_textitem(TextAlignment::TopRight);
      else if (txtalign == QString::fromLatin1("centerleft"))
        settextalignment_textitem(TextAlignment::CenterLeft);
      else if (txtalign == QString::fromLatin1("centercenter"))
        settextalignment_textitem(TextAlignment::CenterCenter);
      else if (txtalign == QString::fromLatin1("centerright"))
        settextalignment_textitem(TextAlignment::CenterRight);
      else if (txtalign == QString::fromLatin1("bottomleft"))
        settextalignment_textitem(TextAlignment::BottomLeft);
      else if (txtalign == QString::fromLatin1("bottomcenter"))
        settextalignment_textitem(TextAlignment::BottomCenter);
      else if (txtalign == QString::fromLatin1("bottomright"))
        settextalignment_textitem(TextAlignment::BottomRight);
      else
        xmlreader->raiseWarning(tr("TextItem2D unknown TextAlignment"));

    } else
      xmlreader->raiseWarning(
          tr("TextItem2D text alignment property setting error"));

    // item text property
    QString itemtext = xmlreader->readAttributeString(QString::fromLatin1("text"), &ok);
    if (ok)
      setText(itemtext);
    else {
      setText(QString::fromLatin1("Text"));
      xmlreader->raiseWarning(
          tr("TextItem2D text property setting error"));
    }

    // rotation
    double rotn = xmlreader->readAttributeDouble(QString::fromLatin1("rotation"), &ok);
    (ok) ? setRotation(rotn)
         : xmlreader->raiseWarning(
               tr("TextItem2D rotation property setting error"));

    // line antialias
    bool antial = xmlreader->readAttributeBool(QString::fromLatin1("antialias"), &ok);
    (ok) ? setAntialiased(antial)
         : xmlreader->raiseWarning(
               tr("TextItem2D antialias property setting error"));

    // margin property
    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("margin")) break;
      // brush
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("margin")) {
        int left = xmlreader->readAttributeInt(QString::fromLatin1("left"), &ok);
        if (ok) {
          int top = xmlreader->readAttributeInt(QString::fromLatin1("top"), &ok);
          if (ok) {
            int right = xmlreader->readAttributeInt(QString::fromLatin1("right"), &ok);
            if (ok) {
              int bottom = xmlreader->readAttributeInt(QString::fromLatin1("bottom"), &ok);
              if (ok)
                setPadding(QMargins(left, top, right, bottom));
              else
                xmlreader->raiseWarning(
                    tr("TextItem2D bottom margin property setting error"));
            } else
              xmlreader->raiseWarning(
                  tr("TextItem2D right margin property setting error"));
          } else
            xmlreader->raiseWarning(
                tr("TextItem2D top margin property setting error"));
        } else
          xmlreader->raiseWarning(
              tr("TextItem2D left margin property setting error"));
      }
    }

    // font and color
    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("font")) break;
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("font")) {
        QPair<QFont, QColor> fontpair = xmlreader->readFont(&ok);
        if (ok) {
          setFont(fontpair.first);
          setColor(fontpair.second);
        } else
          xmlreader->raiseWarning(
              tr("TextItem2D font & color property setting error"));
      }
    }

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
              tr("TextItem2D strokepen property setting error"));
      }
    }

    // brush property
    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("brush")) break;
      // brush
      if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("brush")) {
        QBrush b = xmlreader->readBrush(&ok);
        (ok) ? setBrush(b)
             : xmlreader->raiseWarning(
                   tr("TextItem2D brush property setting error"));
      }
    }

    while (!xmlreader->atEnd()) {
      xmlreader->readNext();
      if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("textitem")) break;
    }
  } else  // no element
    xmlreader->raiseError(tr("no text item element found"));

  return !xmlreader->hasError();
}

void TextItem2D::mousePressEvent(QMouseEvent *event, const QVariant &details) {
  Q_UNUSED(details);
  if (event->button() == Qt::LeftButton) {
    if (selectTest(event->pos(), false) > 0) {
      draggingtextitem_ = true;
      dragtextitemorigin_ = event->localPos() - position->pixelPosition();
      cursorshape_ = axisrect_->getParentPlot2D()->cursor();
      axisrect_->getParentPlot2D()->setCursor(
          Qt::CursorShape::ClosedHandCursor);
    }
  }
}

void TextItem2D::mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) {
  Q_UNUSED(startPos);
  if (draggingtextitem_) {
    // set bounding rect for drag event
    QPointF eventpos = event->pos();
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
    setpixelposition_textitem(eventpos - dragtextitemorigin_);
    this->layer()->replot();
  }
}

void TextItem2D::mouseReleaseEvent(QMouseEvent *event,
                                   const QPointF &startPos) {
  Q_UNUSED(startPos);
  if (event->button() == Qt::LeftButton) {
    if (draggingtextitem_) {
      draggingtextitem_ = false;
      axisrect_->getParentPlot2D()->setCursor(cursorshape_);
      Q_EMIT axisrect_->TextItem2DMoved();
    }
  }
}
