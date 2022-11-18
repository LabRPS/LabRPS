#ifndef SMOOTHDIALOG_H
#define SMOOTHDIALOG_H

#include <QDialog>

class QPushButton;
class QComboBox;
class QSpinBox;
class AxisRect2D;
class ColorBox;
class ApplicationWindow;

//! Smoothing options dialog
class SmoothCurveDialog : public QDialog {
  Q_OBJECT

 public:
  SmoothCurveDialog(int method, QWidget* parent = nullptr,
                    Qt::WindowFlags fl = Qt::Widget);
  ~SmoothCurveDialog() {}

  QPushButton* btnSmooth;
  QPushButton* buttonCancel;
  QComboBox* boxName;
  QSpinBox *boxPointsLeft, *boxPointsRight, *boxOrder;
  ColorBox* boxColor;

 public slots:
  void setAxisRect(AxisRect2D* axisrect);
  void smooth();
  void activateCurve(const QString& curveName);

 private:
  AxisRect2D* axisrect_;
  ApplicationWindow* app_;
  int smooth_method;
};

#endif  // SMOOTHDIALOG_H
