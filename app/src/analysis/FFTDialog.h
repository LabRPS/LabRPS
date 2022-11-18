#ifndef FFTDIALOG_H
#define FFTDIALOG_H

#include <QDialog>
#include "2Dplot/AxisRect2D.h"
#include "2Dplot/Graph2DCommon.h"

class QPushButton;
class QRadioButton;
class QLineEdit;
class QComboBox;
class QCheckBox;
class Table;

//! Fast Fourier transform options dialog
class FFTDialog : public QDialog {
  Q_OBJECT

 public:
  enum DataType { onGraph = 0, onTable = 1 };

  FFTDialog(int type, QWidget* parent = nullptr,
            Qt::WindowFlags flag = Qt::Widget);
  ~FFTDialog() {}

  QPushButton* buttonOK;
  QPushButton* buttonCancel;
  QRadioButton *forwardBtn, *backwardBtn;
  QComboBox *boxName, *boxReal, *boxImaginary;
  QLineEdit* boxSampling;
  QCheckBox *boxNormalize, *boxOrder;

 public slots:
  void setAxisrect(AxisRect2D* axisrect);
  void setTable(Table* table);
  void activateCurve(const QString& curveName);
  void accept();

 private:
  AxisRect2D* axisrect_;
  Table* d_table;
  int d_type;
};

#endif  // FFTDIALOG_H
