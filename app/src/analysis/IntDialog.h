#ifndef INTDIALOG_H
#define INTDIALOG_H

#include <QDialog>

class QPushButton;
class QCheckBox;
class QLineEdit;
class QComboBox;
class QSpinBox;
class ApplicationWindow;
class AxisRect2D;

//! Integration options dialog
class IntDialog : public QDialog {
  Q_OBJECT

 public:
  IntDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);
  ~IntDialog() {}

  QPushButton* buttonOk;
  QPushButton* buttonCancel;
  QPushButton* buttonHelp;
  QCheckBox* boxShowFormula;
  QComboBox* boxName;
  QComboBox* boxMethod;
  QLineEdit* boxStart;
  QLineEdit* boxEnd;

 public slots:
  void accept();
  void setAxisrect(AxisRect2D* axisrect);
  void activateCurve(const QString& curveName);
  void help();
  void changeDataRange();

 signals:
  void integrate(int, int, int, double, double, double);

 private:
  AxisRect2D* axisrect_;
  ApplicationWindow *app_;
  double xmin_;
  double xmax_;
};

#endif  // INTDIALOG_H
