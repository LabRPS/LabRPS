#include "Precompiled.h"

#include "XmlStreamWriter.h"

#include <QColor>
#include <QFont>
#include <QPen>

XmlStreamWriter::XmlStreamWriter() : QXmlStreamWriter() {}

XmlStreamWriter::XmlStreamWriter(QIODevice *device)
    : QXmlStreamWriter(device) {}

XmlStreamWriter::XmlStreamWriter(QByteArray *bytearray)
    : QXmlStreamWriter(bytearray) {}

void XmlStreamWriter::writeFont(const QFont &font, const QColor &color) {
  writeStartElement(QString::fromLatin1("font"));
  writeAttribute(QString::fromLatin1("family"), font.family());
  writeAttribute(QString::fromLatin1("size"), QString::number(font.pointSize()));
  writeAttribute(QString::fromLatin1("weight"), QString::number(font.weight()));
  (font.bold()) ? writeAttribute(QString::fromLatin1("bold"), QString::fromLatin1("true"))
                : writeAttribute(QString::fromLatin1("bold"), QString::fromLatin1("false"));
  (font.italic()) ? writeAttribute(QString::fromLatin1("italic"), QString::fromLatin1("true"))
                  : writeAttribute(QString::fromLatin1("italic"), QString::fromLatin1("false"));
  (font.underline()) ? writeAttribute(QString::fromLatin1("underline"), QString::fromLatin1("true"))
                     : writeAttribute(QString::fromLatin1("underline"), QString::fromLatin1("false"));
  (font.overline()) ? writeAttribute(QString::fromLatin1("overline"), QString::fromLatin1("true"))
                    : writeAttribute(QString::fromLatin1("overline"), QString::fromLatin1("false"));
  writeAttribute(QString::fromLatin1("color"), color.name(QColor::HexArgb));
  writeEndElement();
}

void XmlStreamWriter::writePen(const QPen &pen) {
  writeStartElement(QString::fromLatin1("pen"));
  writeAttribute(QString::fromLatin1("color"), pen.color().name(QColor::HexArgb));
  writeAttribute(QString::fromLatin1("style"), QString::number(pen.style()));
  writeAttribute(QString::fromLatin1("width"), QString::number(pen.widthF()));
  writeAttribute(QString::fromLatin1("cap"), QString::number(pen.capStyle()));
  writeAttribute(QString::fromLatin1("join"), QString::number(pen.joinStyle()));
  writeEndElement();
}

void XmlStreamWriter::writeBrush(const QBrush &brush) {
  writeStartElement(QString::fromLatin1("brush"));
  writeAttribute(QString::fromLatin1("color"), brush.color().name(QColor::HexArgb));
  writeAttribute(QString::fromLatin1("style"), QString::number(brush.style()));
  writeEndElement();
}
