//#ifndef FUTURE_SORTDIALOG_H
//#define FUTURE_SORTDIALOG_H

#include "core/column/Column.h"
#include <QDialog>

class QPushButton;
class QComboBox;

namespace future {

//! Sorting options dialog
class SortDialog : public QDialog {
  Q_OBJECT

 public:
  SortDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);
  void setColumnsList(QList<Column*> list);

  enum { Separately = 0, Together = 1 };
  enum { Ascending = 0, Descending = 1 };

 private slots:
  void accept();
  void changeType(int index);

 signals:
  void sort(Column* leading, QList<Column*> cols, bool ascending);

 private:
  QList<Column*> d_columns_list;
  struct {
    QPushButton* button_ok;
    QPushButton* button_close;
    QPushButton* button_help;
    QComboBox* box_type;
    QComboBox* box_order;
    QComboBox* columns_list;
  } ui;
};
}  // namespace

//#endif FUTURE_SORTDIALOG_H
