#ifndef PIE2D_H
#define PIE2D_H

#include <QObject>

#include "../3rdparty/qcustomplot/qcustomplot.h"
#include "Graph2DCommon.h"

class AxisRect2D;
class Column;
class Table;
class PieLegendItem2D;
class XmlStreamReader;
class XmlStreamWriter;

class Pie2D : public QCPAbstractItem {
  Q_OBJECT
 public:
  Pie2D(AxisRect2D *axisrect, const Graph2DCommon::PieStyle &style,
        Table *table, Column *xData, Column *yData, int from, int to);
  ~Pie2D();

  void setGraphData(Table *table, Column *xData, Column *yData, int from,
                    int to);
  // reimplemented virtual methods:
  double selectTest(const QPointF &pos, bool onlySelectable,
                    QVariant *details = nullptr) const;

  AxisRect2D *getaxisrect() const;
  Qt::PenStyle getstrokestyle_pieplot() const;
  QColor getstrokecolor_pieplot() const;
  double getstrokethickness_pieplot() const;
  int getmarginpercent_pieplot() const;
  Graph2DCommon::PieStyle getStyle_pieplot() const;
  Table *gettable_pieplot() { return table_; }
  Column *getxcolumn_pieplot() { return xcolumn_; }
  Column *getycolumn_pieplot() { return ycolumn_; }
  int getfrom_pieplot() const { return from_; }
  int getto_pieplot() const { return to_; }
  QIcon getIcon() const { return icon_; }

  void setstrokestyle_pieplot(const Qt::PenStyle &style);
  void setstrokecolor_pieplot(const QColor &color);
  void setstrokethickness_pieplot(const double value);
  void setmarginpercent_pieplot(const int value);
  void setstyle_pieplot(const Graph2DCommon::PieStyle &style);
  void setstrokepen_pieplot(const QPen pen);

  void drawdoughnutslice(QPainter *painter, double startangle, double stopangle,
                         double outerradius, double innerradius, double offset,
                         QPen strokepen, QBrush fillbrush);

  void save(XmlStreamWriter *xmlwriter);
  bool load(XmlStreamReader *xmlreader);

 protected:
  void draw(QCPPainter *painter);

 private:
  AxisRect2D *axisrect_;
  QVector<double> *pieData_;
  Graph2DCommon::PieStyle style_;
  QVector<QColor> *pieColors_;
  QVector<PieLegendItem2D *> *pieLegendItems_;
  QString layername_;
  QPen mPen;
  QBrush mBrush;
  int marginpercent_;
  Table *table_;
  Column *xcolumn_;
  Column *ycolumn_;
  int from_;
  int to_;
  QIcon icon_;
};

#endif  // PIE2D_H
