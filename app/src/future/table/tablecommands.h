#ifndef TABLE_COMMANDS_H
#define TABLE_COMMANDS_H

#include <QUndoCommand>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QItemSelection>
#include "core/column/Column.h"
#include "core/column/ColumnPrivate.h"
#include "table/future_Table.h"
#include "core/AbstractFilter.h"
#include "lib/IntervalAttribute.h"

///////////////////////////////////////////////////////////////////////////
// class TableInsertColumnsCmd
///////////////////////////////////////////////////////////////////////////
//! Insert columns
/**
 * The number of inserted columns is cols.size().
 */
class TableInsertColumnsCmd : public QUndoCommand {
 public:
  TableInsertColumnsCmd(future::Table::Private* private_obj, int before,
                        QList<Column*> cols, QUndoCommand* parent = 0);
  ~TableInsertColumnsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  future::Table::Private* d_private_obj;
  //! Column to insert before
  int d_before;
  //! The new columns
  QList<Column*> d_cols;
  //! Row count before the command
  int d_rows_before;
};

///////////////////////////////////////////////////////////////////////////
// end of class TableInsertColumnsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class TableSetNumberOfRowsCmd
///////////////////////////////////////////////////////////////////////////
//! Set the number of rows in the table
class TableSetNumberOfRowsCmd : public QUndoCommand {
 public:
  TableSetNumberOfRowsCmd(future::Table::Private* private_obj, int rows,
                          QUndoCommand* parent = 0);
  ~TableSetNumberOfRowsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  future::Table::Private* d_private_obj;
  //! Number of rows
  int d_rows;
  //! Number of rows before
  int d_old_rows;
};

///////////////////////////////////////////////////////////////////////////
// end of class TableSetNumberOfRowsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class TableRemoveColumnsCmd
///////////////////////////////////////////////////////////////////////////
//! Remove columns
class TableRemoveColumnsCmd : public QUndoCommand {
 public:
  TableRemoveColumnsCmd(future::Table::Private* private_obj, int first,
                        int count, QList<Column*> cols,
                        QUndoCommand* parent = 0);
  ~TableRemoveColumnsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  future::Table::Private* d_private_obj;
  //! The first column
  int d_first;
  //! The number of columns to be removed
  int d_count;
  //! The removed columns
  QList<Column*> d_old_cols;
};

///////////////////////////////////////////////////////////////////////////
// end of class TableRemoveColumnsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class TableMoveColumnCmd
///////////////////////////////////////////////////////////////////////////
//! Move a column
class TableMoveColumnCmd : public QUndoCommand {
 public:
  TableMoveColumnCmd(future::Table::Private* private_obj, int from, int to,
                     QUndoCommand* parent = 0);
  ~TableMoveColumnCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  future::Table::Private* d_private_obj;
  //! The old column index
  int d_from;
  //! The new column index
  int d_to;
};

///////////////////////////////////////////////////////////////////////////
// end of class TableMoveColumnCmd
///////////////////////////////////////////////////////////////////////////

#endif  // TABLE_COMMANDS_H
