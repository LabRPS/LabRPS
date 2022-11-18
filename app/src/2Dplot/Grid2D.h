#ifndef GRID2D_H
#define GRID2D_H

#include "../3rdparty/qcustomplot/qcustomplot.h"
#include "core/propertybrowser/ObjectBrowserTreeItem.h"

class Axis2D;
class XmlStreamReader;
class XmlStreamWriter;

class Grid2D : public QCPGrid, public ObjectBrowserTreeItem {
  Q_OBJECT
 public:
  explicit Grid2D(ObjectBrowserTreeItem *parentitem, Axis2D *parent);
  ~Grid2D();

  virtual QString getItemName() override;
  virtual QIcon getItemIcon() override;
  virtual QString getItemTooltip() override;

  // Grid & Zeroline
  void setMajorGridColor(const QColor &color);
  void setMajorGridStyle(const Qt::PenStyle &penstyle);
  void setMajorGridThickness(const double thickness);
  void setMinorGridColor(const QColor &color);
  void setMinorGridStyle(const Qt::PenStyle &penstyle);
  void setMinorGridThickness(const double thickness);
  void setZerothLineColor(const QColor &color);
  void setZerothLineStyle(const Qt::PenStyle &penstyle);
  void setZerothLineThickness(const double thickness);
  void setMajorGridVisible(const bool status);
  void setMinorGridVisible(const bool status);
  void setZerothLineVisible(const bool status);
  QColor getMajorGridColor() const;
  Qt::PenStyle getMajorGridStyle() const;
  double getMajorGridwidth() const;
  QColor getMinorGridColor() const;
  Qt::PenStyle getMinorGridStyle() const;
  double getMinorGridwidth() const;
  QColor getZerothLineColor() const;
  Qt::PenStyle getZeroLineStyle() const;
  double getZeroLinewidth() const;
  bool getMajorGridVisible() const;
  bool getMinorGridVisible() const;
  bool getZerothLineVisible() const;

  void save(XmlStreamWriter *xmlwriter, const QString tag);
  bool load(XmlStreamReader *xmlreader, const QString tag);

 private:
  // Grid & zeroline settings
  ObjectBrowserTreeItem *parentitem_;
  Axis2D *axis_;
  QString layername_;
  QColor majorgridcolor_;
  Qt::PenStyle majorgridstyle_;
  double majorgridthickness_;
  QColor zerolinecolor_;
  Qt::PenStyle zerolinestyle_;
  double zerolinethickness_;

};

Q_DECLARE_METATYPE(Grid2D *);
#endif  // GRID2D_H
