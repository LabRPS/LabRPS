#ifndef XMLSTREAMWRITER_H
#define XMLSTREAMWRITER_H

#include <QXmlStreamWriter>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class AlphaplotExport XmlStreamWriter: public QXmlStreamWriter
{
 public:
  XmlStreamWriter();
  XmlStreamWriter(QIODevice* device);
  XmlStreamWriter(QByteArray* bytearray);

  void writeFont(const QFont &font, const QColor &color);
  void writePen(const QPen &pen);
  void writeBrush(const QBrush &brush);
};

#endif  // XMLSTREAMWRITER_H
