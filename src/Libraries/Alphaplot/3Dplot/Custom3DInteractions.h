#ifndef CUSTOM3DINTERACTIONS_H
#define CUSTOM3DINTERACTIONS_H

#include <QtDataVisualization/QAbstract3DInputHandler>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


using namespace QtDataVisualization;

class AlphaplotExport Custom3DInteractions : public QAbstract3DInputHandler {
  Q_OBJECT
 public:
  Custom3DInteractions(QObject *parent = nullptr);

  virtual void mousePressEvent(QMouseEvent *event, const QPoint &mousePos);
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos);
  virtual void mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos);
  virtual void wheelEvent(QWheelEvent *event);

Q_SIGNALS:
  void showContextMenu();
  void activateParentWindow();

 private:
  QPoint mousepoint_;
  bool mouserotation_;
  float zoomfactor_;
  float xrotation_;
  float yrotation_;
  static const int deltazoom_;
};

#endif  // CUSTOM3DINTERACTIONS_H
