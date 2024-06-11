/***************************************************************************
    File                 : tablecommands.h
    Project              : AlphaPlot
    Description          : Commands used in Table (part of the undo/redo
 framework)
    --------------------------------------------------------------------
    Copyright            : (C) 2007 Tilman Benkert (thzs*gmx.net)
                           (replace * with @ in the email addresses)

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef TABLE_COMMANDS_H
#define TABLE_COMMANDS_H

#include <QUndoCommand>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QItemSelection>

#include "future/core/column/Column.h"
#include "future/core/column/ColumnPrivate.h"
#include "future/table/future_Table.h"
#include "future/core/AbstractFilter.h"
#include "future/lib/IntervalAttribute.h"
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


///////////////////////////////////////////////////////////////////////////
// class TableInsertColumnsCmd
///////////////////////////////////////////////////////////////////////////
//! Insert columns
/**
 * The number of inserted columns is cols.size().
 */
class AlphaplotExport TableInsertColumnsCmd: public QUndoCommand
{
 public:
  TableInsertColumnsCmd(Gui::TableViewProvider::Private* private_obj, int before,
                        QList<Column*> cols, QUndoCommand* parent = 0);
  ~TableInsertColumnsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::TableViewProvider::Private* d_private_obj;
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
class AlphaplotExport TableSetNumberOfRowsCmd: public QUndoCommand
{
 public:
  TableSetNumberOfRowsCmd(Gui::TableViewProvider::Private* private_obj, int rows,
                          QUndoCommand* parent = 0);
  ~TableSetNumberOfRowsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::TableViewProvider::Private* d_private_obj;
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
class AlphaplotExport TableRemoveColumnsCmd: public QUndoCommand
{
 public:
  TableRemoveColumnsCmd(Gui::TableViewProvider::Private* private_obj, int first,
                        int count, QList<Column*> cols,
                        QUndoCommand* parent = 0);
  ~TableRemoveColumnsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::TableViewProvider::Private* d_private_obj;
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
class AlphaplotExport TableMoveColumnCmd: public QUndoCommand
{
 public:
  TableMoveColumnCmd(Gui::TableViewProvider::Private* private_obj, int from, int to,
                     QUndoCommand* parent = 0);
  ~TableMoveColumnCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::TableViewProvider::Private* d_private_obj;
  //! The old column index
  int d_from;
  //! The new column index
  int d_to;
};

///////////////////////////////////////////////////////////////////////////
// end of class TableMoveColumnCmd
///////////////////////////////////////////////////////////////////////////

#endif  // TABLE_COMMANDS_H
