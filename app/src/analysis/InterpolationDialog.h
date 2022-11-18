#ifndef INTERPOLATIONDIALOG_H
#define INTERPOLATIONDIALOG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QComboBox;
class QSpinBox;
class AxisRect2D;
class ColorBox;
class ApplicationWindow;

//! Interpolation options dialog
class InterpolationDialog : public QDialog {
  Q_OBJECT

 public:
  InterpolationDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);
  ~InterpolationDialog() {}

  QPushButton* buttonFit;
  QPushButton* buttonCancel;
  QComboBox* boxName;
  QComboBox* boxMethod;
  QSpinBox* boxPoints;
  QLineEdit* boxStart;
  QLineEdit* boxEnd;
  ColorBox* boxColor;

 public slots:
  void activateCurve(const QString& curveName);
  void setAxisRect(AxisRect2D* axisrect);
  void interpolate();
  void changeDataRange();

 private:
  AxisRect2D *axisrect_;
  ApplicationWindow *app_;
  double xmin_;
  double xmax_;
};

#endif  // INTERPOLATIONDIALOG_H
