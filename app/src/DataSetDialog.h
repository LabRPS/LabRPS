#ifndef DATASETDIALOG_H
#define DATASETDIALOG_H

#include <QDialog>

class QGroupBox;
class QPushButton;
class QCheckBox;
class QLineEdit;
class QComboBox;

class AxisRect2D;

//! Multi purpose dialog for choosing a data set
class DataSetDialog : public QDialog {
  Q_OBJECT

 public:
  DataSetDialog(const QString& text, QWidget* parent = nullptr,
                Qt::WindowFlags fl = Qt::Widget);
  ~DataSetDialog() {}

  QPushButton* buttonOk;
  QPushButton* buttonCancel;
  QGroupBox* groupBox1;
  QCheckBox* boxShowFormula;
  QComboBox* boxName;

 public slots:
  void accept();
  void setCurveNames(const QStringList& names);
  void setOperationType(const QString& op) { operation = op; }
  void setCurentDataSet(const QString& set);
  void setAxisRect(AxisRect2D* axisrect);

 signals:
  void options(const QString&);

 private:
  QString operation;
  QString windowTitle;
  AxisRect2D* axisrect_;
};

#endif  // DATASETDIALOG_H
