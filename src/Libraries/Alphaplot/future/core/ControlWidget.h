#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class AlphaplotExport ControlWidget: public QWidget
{
  Q_OBJECT
 public:
  explicit ControlWidget(QWidget *parent = nullptr);

 protected:
  void resizeEvent(QResizeEvent *event);

 Q_SIGNALS:
  void widthChanged();
};

#endif  // CONTROLWIDGET_H
