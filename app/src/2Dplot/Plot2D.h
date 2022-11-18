#ifndef PLOT2D_H
#define PLOT2D_H

#include "../3rdparty/qcustomplot/qcustomplot.h"
#include "core/propertybrowser/ObjectBrowserTreeItem.h"

class Plot2D : public QCustomPlot, public ObjectBrowserTreeItem {
  Q_OBJECT
 public:
  explicit Plot2D(ObjectBrowserTreeItem *parentitem, QWidget *parent = nullptr);
  ~Plot2D();

  virtual QString getItemName() override;
  virtual QIcon getItemIcon() override;
  virtual QString getItemTooltip() override;

  void setBackgroundColor(const QColor &color, const bool backpixmap = true);
  QColor getBackgroundColor() const;
  bool saveSvg(const QString &fileName, int width = 0, int height = 0,
               QCP::ExportPen exportPen = QCP::epAllowCosmetic,
               const QString &svgTitle = QString(),
               const QString &svgDescription = QString());
  bool savePs(const QString &fileName, int width = 0, int height = 0,
              QCP::ExportPen exportPen = QCP::epAllowCosmetic,
              const QString &psCreator = QString(),
              const QString &psTitle = QString());
  QString getGrid2DLayerName() const { return layernamegrid2d_; }
  QString getAxis2DLayerName() const { return layernameaxis2d_; }
  QString getLegend2DLayerName() const { return layernamelegend2d_; }
  QString getBackground2DLayerName() const { return layernamebackground2d_; }

 signals:
  void backgroundColorChange(QColor color);

 private:
  ObjectBrowserTreeItem *rootitem_;
  QColor canvasBackground_;
  // Layers
  QString layernamebackground2d_;
  QString layernamegrid2d_;
  QString layernameaxis2d_;
  QString layernamepicker2d_;
  QString layernamelegend2d_;
};

Q_DECLARE_METATYPE(Plot2D *);
#endif  // PLOT2D_H
