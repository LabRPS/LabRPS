#ifndef SURFACEDIALOG_H
#define SURFACEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QPushButton;
class QLineEdit;
class QComboBox;

//! Define surface plot dialog
class SurfaceDialog : public QDialog {
  Q_OBJECT

 public:
  SurfaceDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);
  ~SurfaceDialog();

 public slots:
  void accept();
  void insertFunctionsList(const QStringList& list);
  void clearList();
  void setFunction(const QString& s);
  void setLimits(double xs, double xe, double ys, double ye, double zs,
                 double ze);

 signals:
  void options(const QString&, double, double, double, double, double, double);
  void clearFunctionsList();
  void custom3DToolBar();

 private:
  QPushButton* buttonOk;
  QPushButton* buttonCancel;
  QPushButton* buttonClear;
  QComboBox* boxFunction;
  QLineEdit* boxXFrom;
  QLineEdit* boxXTo;
  QLineEdit* boxYFrom;
  QLineEdit* boxYTo;
  QLineEdit* boxZFrom;
  QLineEdit* boxZTo;
};

#endif  // SURFACEDIALOG_H
