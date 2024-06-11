#ifndef LINEITEM2D_H
#define LINEITEM2D_H

#include <Libraries/Alphaplot/3rdparty/qcustomplot/qcustomplot.h>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class AxisRect2D;
class Plot2D;
class XmlStreamReader;
class XmlStreamWriter;

class AlphaplotExport LineItem2D : public QCPItemLine {
 public:
  LineItem2D(AxisRect2D *axisrect, Plot2D *plot);
  ~LineItem2D();

  enum class LineEndLocation : int {
    Start = 0,
    Stop = 1,
  };

  AxisRect2D *getaxisrect() const;
  QColor getstrokecolor_lineitem() const;
  double getstrokethickness_lineitem() const;
  Qt::PenStyle getstrokestyle_lineitem() const;
  QCPLineEnding::EndingStyle getendstyle_lineitem(
      const LineEndLocation &location) const;
  double getendwidth_lineitem(const LineEndLocation &location) const;
  double getendlength_lineitem(const LineEndLocation &location) const;

  void setstrokecolor_lineitem(const QColor &color);
  void setstrokethickness_lineitem(const double value);
  void setstrokestyle_lineitem(const Qt::PenStyle &style);
  void setendstyle_lineitem(const LineEndLocation &location,
                            const QCPLineEnding::EndingStyle &style);
  void setendwidth_lineitem(const double value,
                            const LineEndLocation &location);
  void setendlength_lineitem(const double value,
                             const LineEndLocation &location);

  QString getendstylestring_lineitem(
      const QCPLineEnding::EndingStyle endstyle) const;
  QCPLineEnding::EndingStyle getendstyleenum_lineitem(const QString end) const;
  void save(XmlStreamWriter *xmlwriter);
  bool load(XmlStreamReader *xmlreader);

 protected:
  void draw(QCPPainter *painter);
  void mousePressEvent(QMouseEvent *event, const QVariant &details);
  void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos);
  void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos);

 private:
  static const int selectionpixelsize_;
  AxisRect2D *axisrect_;
  QCPLineEnding *ending_;
  QCPLineEnding *starting_;
  QString layername_;
  bool dragginglineitem_;
  QPointF draglineitemorigin_;
  QPointF draglineitemendin_;
  bool draggingendlineitem_;
  bool draggingstartlineitem_;
  bool lineitemclicked_;
  QCursor cursorshape_;
};

#endif  // LINEITEM2D_H
