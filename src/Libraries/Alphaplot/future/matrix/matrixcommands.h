/***************************************************************************
    File                 : matrixcommands.h
    Project              : AlphaPlot
    Description          : Commands used in Matrix (part of the undo/redo
 framework)
    --------------------------------------------------------------------
    Copyright            : (C) 2008-2009 Tilman Benkert (thzs*gmx.net)
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

#ifndef MATRIX_COMMANDS_H
#define MATRIX_COMMANDS_H

#include <QUndoCommand>
#include "future/matrix/future_Matrix.h"
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


///////////////////////////////////////////////////////////////////////////
// class MatrixInsertColumnsCmd
///////////////////////////////////////////////////////////////////////////
//! Insert columns
class AlphaplotExport MatrixInsertColumnsCmd : public QUndoCommand {
 public:
  MatrixInsertColumnsCmd(Gui::MatrixViewProvider::Private* private_obj, int before,
                         int count, QUndoCommand* parent = 0);
  ~MatrixInsertColumnsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! Column to insert before
  int d_before;
  //! The number of new columns
  int d_count;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixInsertColumnsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixInsertRowsCmd
///////////////////////////////////////////////////////////////////////////
//! Insert rows
class MatrixInsertRowsCmd : public QUndoCommand {
 public:
  MatrixInsertRowsCmd(Gui::MatrixViewProvider::Private* private_obj, int before,
                      int count, QUndoCommand* parent = 0);
  ~MatrixInsertRowsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! Row to insert before
  int d_before;
  //! The number of new rows
  int d_count;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixInsertRowsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixRemoveColumnsCmd
///////////////////////////////////////////////////////////////////////////
//! Remove columns
class MatrixRemoveColumnsCmd : public QUndoCommand {
 public:
  MatrixRemoveColumnsCmd(Gui::MatrixViewProvider::Private* private_obj, int first,
                         int count, QUndoCommand* parent = 0);
  ~MatrixRemoveColumnsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! First column to remove
  int d_first;
  //! The number of columns to remove
  int d_count;
  //! Backups of the removed columns
  QVector<QVector<qreal> > d_backups;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixRemoveColumnsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixRemoveRowsCmd
///////////////////////////////////////////////////////////////////////////
//! Remove rows
class MatrixRemoveRowsCmd : public QUndoCommand {
 public:
  MatrixRemoveRowsCmd(Gui::MatrixViewProvider::Private* private_obj, int first,
                      int count, QUndoCommand* parent = 0);
  ~MatrixRemoveRowsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! First row to remove
  int d_first;
  //! The number of rows to remove
  int d_count;
  //! Backups of the removed rows
  QVector<QVector<qreal> > d_backups;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixRemoveRowsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixClearCmd
///////////////////////////////////////////////////////////////////////////
//! Clear matrix
class MatrixClearCmd : public QUndoCommand {
 public:
  MatrixClearCmd(Gui::MatrixViewProvider::Private* private_obj,
                 QUndoCommand* parent = 0);
  ~MatrixClearCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! Backups of the cleared cells
  QVector<QVector<qreal> > d_backups;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixClearCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixClearColumnCmd
///////////////////////////////////////////////////////////////////////////
//! Clear matrix column
class MatrixClearColumnCmd : public QUndoCommand {
 public:
  MatrixClearColumnCmd(Gui::MatrixViewProvider::Private* private_obj, int col,
                       QUndoCommand* parent = 0);
  ~MatrixClearColumnCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! The index of the column
  int d_col;
  //! Backup of the cleared column
  QVector<qreal> d_backup;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixClearColumnCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetCellValueCmd
///////////////////////////////////////////////////////////////////////////
//! Set cell value
class MatrixSetCellValueCmd : public QUndoCommand {
 public:
  MatrixSetCellValueCmd(Gui::MatrixViewProvider::Private* private_obj, int row, int col,
                        double value, QUndoCommand* parent = 0);
  ~MatrixSetCellValueCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! The index of the row
  int d_row;
  //! The index of the column
  int d_col;
  //! New cell value
  double d_value;
  //! Backup of the changed value
  double d_old_value;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetCellValueCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetCoordinatesCmd
///////////////////////////////////////////////////////////////////////////
//! Set matrix coordinates
class MatrixSetCoordinatesCmd : public QUndoCommand {
 public:
  MatrixSetCoordinatesCmd(Gui::MatrixViewProvider::Private* private_obj, double x1,
                          double x2, double y1, double y2,
                          QUndoCommand* parent = 0);
  ~MatrixSetCoordinatesCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  double d_new_x1;
  double d_new_x2;
  double d_new_y1;
  double d_new_y2;
  double d_old_x1;
  double d_old_x2;
  double d_old_y1;
  double d_old_y2;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetCoordinatesCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetFormatCmd
///////////////////////////////////////////////////////////////////////////
//! Set numeric format
class MatrixSetFormatCmd : public QUndoCommand {
 public:
  MatrixSetFormatCmd(Gui::MatrixViewProvider::Private* private_obj, char new_format);

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  char d_other_format;
};
///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetFormatCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetDigitsCmd
///////////////////////////////////////////////////////////////////////////
//! Set displayed digits
class MatrixSetDigitsCmd : public QUndoCommand {
 public:
  MatrixSetDigitsCmd(Gui::MatrixViewProvider::Private* private_obj, int new_digits);

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  int d_other_digits;
};
///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetDigitsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetFormulaCmd
///////////////////////////////////////////////////////////////////////////
//! Set matrix formula
class MatrixSetFormulaCmd : public QUndoCommand {
 public:
  MatrixSetFormulaCmd(Gui::MatrixViewProvider::Private* private_obj, QString formula);

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  QString d_other_formula;
};
///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetFormulaCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetColumnCellsCmd
///////////////////////////////////////////////////////////////////////////
//! Set cell values for (a part of) a column at once
class MatrixSetColumnCellsCmd : public QUndoCommand {
 public:
  MatrixSetColumnCellsCmd(Gui::MatrixViewProvider::Private* private_obj, int col,
                          int first_row, int last_row,
                          const QVector<qreal>& values,
                          QUndoCommand* parent = 0);
  ~MatrixSetColumnCellsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! The index of the column
  int d_col;
  //! The index of the first row
  int d_first_row;
  //! The index of the last row
  int d_last_row;
  //! New cell values
  QVector<qreal> d_values;
  //! Backup of the changed values
  QVector<qreal> d_old_values;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetColumnCellsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixSetRowCellsCmd
///////////////////////////////////////////////////////////////////////////
//! Set cell values for (a part of) a row at once
class MatrixSetRowCellsCmd : public QUndoCommand {
 public:
  MatrixSetRowCellsCmd(Gui::MatrixViewProvider::Private* private_obj, int row,
                       int first_column, int last_column,
                       const QVector<qreal>& values, QUndoCommand* parent = 0);
  ~MatrixSetRowCellsCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
  //! The index of the row
  int d_row;
  //! The index of the first column
  int d_first_column;
  //! The index of the last column
  int d_last_column;
  //! New cell values
  QVector<qreal> d_values;
  //! Backup of the changed values
  QVector<qreal> d_old_values;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixSetRowCellsCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixTransposeCmd
///////////////////////////////////////////////////////////////////////////
//! Transpose the matrix
class MatrixTransposeCmd : public QUndoCommand {
 public:
  MatrixTransposeCmd(Gui::MatrixViewProvider::Private* private_obj,
                     QUndoCommand* parent = 0);
  ~MatrixTransposeCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixTransposeCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixMirrorHorizontallyCmd
///////////////////////////////////////////////////////////////////////////
//! Mirror the matrix horizontally
class MatrixMirrorHorizontallyCmd : public QUndoCommand {
 public:
  MatrixMirrorHorizontallyCmd(Gui::MatrixViewProvider::Private* private_obj,
                              QUndoCommand* parent = 0);
  ~MatrixMirrorHorizontallyCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixMirrorHorizontallyCmd
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// class MatrixMirrorVerticallyCmd
///////////////////////////////////////////////////////////////////////////
//! Mirror the matrix vertically
class MatrixMirrorVerticallyCmd : public QUndoCommand {
 public:
  MatrixMirrorVerticallyCmd(Gui::MatrixViewProvider::Private* private_obj,
                            QUndoCommand* parent = 0);
  ~MatrixMirrorVerticallyCmd();

  virtual void redo();
  virtual void undo();

 private:
  //! The private object to modify
  Gui::MatrixViewProvider::Private* d_private_obj;
};

///////////////////////////////////////////////////////////////////////////
// end of class MatrixMirrorVerticallyCmd
///////////////////////////////////////////////////////////////////////////

#endif  // MATRIX_COMMANDS_H
