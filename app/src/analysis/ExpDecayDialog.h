#ifndef EXPDECAYDIALOG_H
#define EXPDECAYDIALOG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QComboBox;
class QLabel;
class AxisRect2D;
class ColorBox;
class Fit;
class ApplicationWindow;

//! Fit exponential decay dialog
class ExpDecayDialog : public QDialog {
  Q_OBJECT

 public:
  ExpDecayDialog(int type, QWidget* parent = nullptr,
                 Qt::WindowFlags fl = Qt::Widget);
  ~ExpDecayDialog() {}

 public slots:
  void fit();
  void setAxisRect(AxisRect2D* axisrect);

 private slots:
  void activateCurve(const QString& curveName);
  void changeDataRange();

 signals:
  void options(const QString&, double, double, double, double, int);
  void options(const QString&, double, double, double, int);
  void options3(const QString&, double, double, double, double, double, int);

 private:
  void closeEvent(QCloseEvent*);

  Fit* fitter;
  AxisRect2D* axisrect_;
  ApplicationWindow *app_;
  double xmin_;
  double xmax_;
  int slopes;

  QPushButton* buttonFit;
  QPushButton* buttonCancel;
  QComboBox* boxName;
  QLineEdit* boxAmplitude;
  QLineEdit* boxFirst;
  QLineEdit* boxSecond;
  QLineEdit* boxThird;
  QLineEdit* boxStart;
  QLineEdit* boxYOffset;
  QLabel *thirdLabel, *dampingLabel;
  ColorBox* boxColor;
};

#endif  // EXPDECAYDIALOG_H
