#ifndef ASSOCIATIONSDIALOG_H
#define ASSOCIATIONSDIALOG_H

#include <QDialog>

class QLabel;
class QListWidget;
class QPushButton;
class QTableWidget;
class QStringList;
class Table;
class QMdiSubWindow;
class AxisRect2D;

//! Plot associations dialog
class AssociationsDialog : public QDialog {
  Q_OBJECT

 public:
  AssociationsDialog(QWidget *parent = nullptr,
                     Qt::WindowFlags fl = Qt::Widget);
  ~AssociationsDialog();

  void initTablesList(QList<QMdiSubWindow *> *lst, int curve);
  void setAxisRect(AxisRect2D *axisrect);

 private slots:
  void updateTable(int index);
  void updateCurves();
  void accept();

 private:
  void changePlotAssociation(int curve, const QString &text);
  void updateColumnTypes();
  void uncheckCol(int col);
  void updatePlotAssociation(int row, int col);
  QString plotAssociation(const QString &text);
  Table *findTable(int index);
  bool eventFilter(QObject *object, QEvent *e);

  QList<QMdiSubWindow *> *tables;
  Table *active_table;
  AxisRect2D *axisrect_;
  QStringList plotAssociationsList;

  QLabel *tableCaptionLabel;
  QTableWidget *table;
  QPushButton *btnOK, *btnCancel, *btnApply;
  QListWidget *associations;
};

#endif  // ASSOCIATIONSDIALOG_H
