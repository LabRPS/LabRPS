#ifndef POLINOMFITDIALOG_H
#define POLINOMFITDIALOG_H

#include <QDialog>

class QCheckBox;
class QSpinBox;
class QPushButton;
class QLineEdit;
class QComboBox;
class ColorBox;
class AxisRect2D;
class ApplicationWindow;

//! Fit polynomial dialog
class PolynomFitDialog : public QDialog {
  Q_OBJECT

 public:
  PolynomFitDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);

 public slots:
  void fit();
  void setAxisRect(AxisRect2D* axisrect);
  void activateCurve(const QString& curveName);

 private:
  AxisRect2D* axisrect_;
  ApplicationWindow *app_;
  double xmin_;
  double xmax_;

  QPushButton* buttonFit;
  QPushButton* buttonCancel;
  QCheckBox* boxShowFormula;
  QComboBox* boxName;
  QSpinBox* boxOrder;
  QLineEdit* boxStart;
  QLineEdit* boxEnd;
  ColorBox* boxColor;
};

#endif  // POLINOMFITDIALOG_H
