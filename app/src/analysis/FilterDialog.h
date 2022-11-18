#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QComboBox;
class QCheckBox;
class AxisRect2D;
class ColorBox;

//! Filter options dialog
class FilterDialog : public QDialog {
  Q_OBJECT

 public:
  FilterDialog(int type, QWidget* parent = nullptr,
               Qt::WindowFlags flag = Qt::Widget);
  ~FilterDialog() {}

  QPushButton* buttonFilter;
  QPushButton* buttonCancel;
  QComboBox* boxName;
  QCheckBox* boxOffset;
  QLineEdit* boxStart;
  QLineEdit* boxEnd;
  ColorBox* boxColor;

 public slots:
  void setAxisRect(AxisRect2D* axisrect);
  void filter();

 private:
  AxisRect2D* axisrect_;
  int filter_type;
};

#endif  // FILTERDIALOG_H
