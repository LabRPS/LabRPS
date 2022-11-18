#ifndef TABLECOMMENTSHEADERMODEL_H
#define TABLECOMMENTSHEADERMODEL_H

#include <QAbstractTableModel>
#include "TableModel.h"

//! Model class wrapping a TableModel to display column comments in a
//! TableCommentsHeaderView
class TableCommentsHeaderModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  //! Constructor
  explicit TableCommentsHeaderModel(TableModel *table_model,
                                    QObject *parent = 0);
  //! Destructor
  virtual ~TableCommentsHeaderModel();

  //! \name Overloaded functions from QAbstractItemModel
  //@{
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  //@}
  QColor headerDataColorCode(int logicalIndex) const;

 private:
  TableModel *d_table_model;
};

#endif  // TABLECOMMENTSHEADERMODEL_H
