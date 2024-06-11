/***************************************************************************
    File                 : Matrix.cpp
    Project              : AlphaPlot
    Description          : Aspect providing a spreadsheet to manage MxN matrix
 data
    --------------------------------------------------------------------
    Copyright            : (C) 2006-2009 Tilman Benkert (thzs*gmx.net)
    Copyright            : (C) 2006-2009 Knut Franke (knut.franke*gmx.de)
    Copyright            : (C) 2006-2007 Ion Vasilief (ion_vasilief*yahoo.fr)
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
#include "Precompiled.h"

#include "future/matrix/future_Matrix.h"

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QProgressDialog>
#include <QtCore>
#include <QtDebug>
#include <QtGui>
#include <QApplication>

#include "core/IconLoader.h"
#include "Matrix.h"
#include "future/core/future_Folder.h"
#include "future/lib/ActionManager.h"
#include "future/lib/XmlStreamReader.h"
#include "matrixcommands.h"

namespace Gui {

#define WAIT_CURSOR QApplication::setOverrideCursor(QCursor(Qt::WaitCursor))
#define RESET_CURSOR QApplication::restoreOverrideCursor()

int MatrixViewProvider::default_column_width = 120;
int MatrixViewProvider::default_row_height = 20;

#ifndef LEGACY_CODE_0_2_x
//MatrixViewProvider::Matrix(AbstractScriptingEngine *engine, int rows, int cols,
//               const QString &name)
//    : AbstractPart(name),
//      d_plot_menu(0),
//      scripted(engine)
#else
MatrixViewProvider::MatrixViewProvider(void *, int rows, int cols, const QString &name)
    : AbstractPart(name),
      d_plot_menu(nullptr),
      showonlyvalues_(false)
#endif
{
  d_matrix_private = new Private(this);
  // set initial number of rows and columns
  appendColumns(cols);
  appendRows(rows);

  d_view = nullptr;
  createActions();
  connectActions();
}

#ifndef LEGACY_CODE_0_2_x
MatrixViewProvider::Matrix()
    : AbstractPart("temp"),
      scripted(0)
#else
MatrixViewProvider::MatrixViewProvider()
    : AbstractPart(QString::fromLatin1("temp")),
      showonlyvalues_(false)
#endif
{
  d_view = nullptr;
  createActions();
}

MatrixViewProvider::~MatrixViewProvider() {}

void MatrixViewProvider::setView(MatrixView *view) {
  d_view = view;
  addActionsToView();
  connect(d_view, SIGNAL(controlTabBarStatusChanged(bool)), this,
          SLOT(adjustTabBarAction(bool)));
  adjustTabBarAction(true);
}

QWidget *MatrixViewProvider::view() {
#ifndef LEGACY_CODE_0_2_x
  if (!d_view) {
    d_view = new MatrixView(this);
    addActionsToView();
    connect(d_view, SIGNAL(controlTabBarStatusChanged(bool)), this,
            SLOT(adjustTabBarAction(bool)));
    adjustTabBarAction(true);
  }
#else
  Q_ASSERT(d_view != NULL);
#endif
  return d_view;
}

void MatrixViewProvider::insertColumns(int before, int count) {
  if (count < 1 || before < 0 || before > columnCount()) return;
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: insert %2 column(s)").arg(name()).arg(count));
  exec(new MatrixInsertColumnsCmd(d_matrix_private, before, count));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::removeColumns(int first, int count) {
  if (count < 1 || first < 0 || first + count > columnCount()) return;
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: remove %2 column(s)").arg(name()).arg(count));
  exec(new MatrixRemoveColumnsCmd(d_matrix_private, first, count));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::removeRows(int first, int count) {
  if (count < 1 || first < 0 || first + count > rowCount()) return;
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: remove %2 row(s)").arg(name()).arg(count));
  exec(new MatrixRemoveRowsCmd(d_matrix_private, first, count));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::insertRows(int before, int count) {
  if (count < 1 || before < 0 || before > rowCount()) return;
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: insert %2 row(s)").arg(name()).arg(count));
  exec(new MatrixInsertRowsCmd(d_matrix_private, before, count));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::setDimensions(int rows, int cols) {
  if ((rows < 0) || (cols < 0) || (rows == rowCount() && cols == columnCount()))
    return;
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: set matrix size to %2x%3")
                 .arg(name())
                 .arg(rows)
                 .arg(cols));
  int col_diff = cols - columnCount();
  int row_diff = rows - rowCount();
  if (col_diff > 0)
    exec(new MatrixInsertColumnsCmd(d_matrix_private, columnCount(), col_diff));
  else if (col_diff < 0)
    exec(new MatrixRemoveColumnsCmd(d_matrix_private, columnCount() + col_diff,
                                    -col_diff));
  if (row_diff > 0)
    exec(new MatrixInsertRowsCmd(d_matrix_private, rowCount(), row_diff));
  else if (row_diff < 0)
    exec(new MatrixRemoveRowsCmd(d_matrix_private, rowCount() + row_diff,
                                 -row_diff));
  endMacro();
  RESET_CURSOR;
}

int MatrixViewProvider::columnCount() const { return d_matrix_private->columnCount(); }

int MatrixViewProvider::rowCount() const { return d_matrix_private->rowCount(); }

void MatrixViewProvider::clear() {
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: clear").arg(name()));
  exec(new MatrixClearCmd(d_matrix_private));
  endMacro();
  RESET_CURSOR;
}

double MatrixViewProvider::cell(int row, int col) const {
  if (row < 0 || row >= rowCount() || col < 0 || col >= columnCount())
    return 0.0;
  return d_matrix_private->cell(row, col);
}

void MatrixViewProvider::cutSelection() {
  if (!d_view) return;
  int first = d_view->firstSelectedRow();
  if (first < 0) return;

  WAIT_CURSOR;
  beginMacro(tr("%1: cut selected cell(s)").arg(name()));
  copySelection();
  clearSelectedCells();
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::copySelection() {
  if (!d_view) return;
  int first_col = d_view->firstSelectedColumn(false);
  if (first_col == -1) return;
  int last_col = d_view->lastSelectedColumn(false);
  if (last_col == -2) return;
  int first_row = d_view->firstSelectedRow(false);
  if (first_row == -1) return;
  int last_row = d_view->lastSelectedRow(false);
  if (last_row == -2) return;
  int cols = last_col - first_col + 1;
  int rows = last_row - first_row + 1;

  WAIT_CURSOR;
  QString output_str;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (d_view->isCellSelected(first_row + r, first_col + c))
        output_str += QLocale().toString(cell(first_row + r, first_col + c),
                                         d_matrix_private->numericFormat(),
                                         16);  // copy with max. precision
      if (c < cols - 1) output_str += QString::fromLatin1("\t");
    }
    if (r < rows - 1) output_str += QString::fromLatin1("\n");
  }
  QApplication::clipboard()->setText(output_str);
  RESET_CURSOR;
}

void MatrixViewProvider::pasteIntoSelection() {
  if (!d_view) return;
  if (columnCount() < 1 || rowCount() < 1) return;

  WAIT_CURSOR;
  beginMacro(tr("%1: paste from clipboard").arg(name()));

  int first_col = d_view->firstSelectedColumn(false);
  int last_col = d_view->lastSelectedColumn(false);
  int first_row = d_view->firstSelectedRow(false);
  int last_row = d_view->lastSelectedRow(false);
  int input_row_count = 0;
  int input_col_count = 0;
  int rows, cols;

  const QClipboard *clipboard = QApplication::clipboard();
  const QMimeData *mimeData = clipboard->mimeData();
  ;
  if (mimeData->hasText()) {
    QString input_str = QString(clipboard->text());
    QList<QStringList> cell_texts;
    QStringList input_rows(input_str.split(QRegExp(QString::fromLatin1("\\n|\\r\\n|\\r"))));
    input_row_count = input_rows.count();
    input_col_count = 0;
    for (int i = 0; i < input_row_count; i++) {
      cell_texts.append(input_rows.at(i).split(QString::fromLatin1("\t")));
      if (cell_texts.at(i).count() > input_col_count)
        input_col_count = cell_texts.at(i).count();
    }

    if ((first_col == -1 || first_row == -1) ||
        (last_row == first_row && last_col == first_col))
    // if the is no selection or only one cell selected, the
    // selection will be expanded to the needed size from the current cell
    {
      int current_row, current_col;
      d_view->getCurrentCell(&current_row, &current_col);
      if (current_row == -1) current_row = 0;
      if (current_col == -1) current_col = 0;
      d_view->setCellSelected(current_row, current_col);
      first_col = current_col;
      first_row = current_row;
      last_row = first_row + input_row_count - 1;
      last_col = first_col + input_col_count - 1;
      // resize the matrix if necessary
      if (last_col >= columnCount())
        appendColumns(last_col + 1 - columnCount());
      if (last_row >= rowCount()) appendRows(last_row + 1 - rowCount());
      // select the rectangle to be pasted in
      d_view->setCellsSelected(first_row, first_col, last_row, last_col);
    }

    rows = last_row - first_row + 1;
    cols = last_col - first_col + 1;
    for (int r = 0; r < rows && r < input_row_count; r++) {
      for (int c = 0; c < cols && c < input_col_count; c++) {
        if (d_view->isCellSelected(first_row + r, first_col + c) &&
            (c < cell_texts.at(r).count())) {
          setCell(first_row + r, first_col + c,
                  cell_texts.at(r).at(c).toDouble());
        }
      }
    }
  }
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::insertEmptyColumns() {
  if (!d_view) return;
  int first = d_view->firstSelectedColumn();
  int last = d_view->lastSelectedColumn();
  if (first < 0) return;
  int count, current = first;

  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: insert empty column(s)").arg(name()));
  while (current <= last) {
    current = first + 1;
    while (current <= last && d_view->isColumnSelected(current)) current++;
    count = current - first;
    insertColumns(first, count);
    current += count;
    last += count;
    while (current <= last && !d_view->isColumnSelected(current)) current++;
    first = current;
  }
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::removeSelectedColumns() {
  if (!d_view) return;
  int first = d_view->firstSelectedColumn();
  int last = d_view->lastSelectedColumn();
  if (first < 0) return;

  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: remove selected column(s)").arg(name()));
  for (int i = last; i >= first; i--)
    if (d_view->isColumnSelected(i, false)) removeColumns(i, 1);
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::clearSelectedColumns() {
  if (!d_view) return;
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: clear selected column(s)").arg(name()));
  for (int i = 0; i < columnCount(); i++)
    if (d_view->isColumnSelected(i, false))
      exec(new MatrixClearColumnCmd(d_matrix_private, i));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::insertEmptyRows() {
  if (!d_view) return;
  int first = d_view->firstSelectedRow();
  int last = d_view->lastSelectedRow();
  int count, current = first;

  if (first < 0) return;

  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: insert empty rows(s)").arg(name()));
  while (current <= last) {
    current = first + 1;
    while (current <= last && d_view->isRowSelected(current)) current++;
    count = current - first;
    insertRows(first, count);
    current += count;
    last += count;
    while (current <= last && !d_view->isRowSelected(current)) current++;
    first = current;
  }
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::removeSelectedRows() {
  if (!d_view) return;
  int first = d_view->firstSelectedRow();
  int last = d_view->lastSelectedRow();
  if (first < 0) return;

  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: remove selected rows(s)").arg(name()));
  for (int i = last; i >= first; i--)
    if (d_view->isRowSelected(i, false)) removeRows(i, 1);
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::clearSelectedRows() {
  if (!d_view) return;
  int first = d_view->firstSelectedRow();
  int last = d_view->lastSelectedRow();
  if (first < 0) return;

  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: clear selected rows(s)").arg(name()));
  for (int i = first; i <= last; i++) {
    if (d_view->isRowSelected(i))
      for (int j = 0; j < columnCount(); j++)
        exec(new MatrixSetCellValueCmd(d_matrix_private, i, j, 0.0));
  }
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::clearSelectedCells() {
  if (!d_view) return;
  int first_row = d_view->firstSelectedRow();
  int last_row = d_view->lastSelectedRow();
  if (first_row < 0) return;
  int first_col = d_view->firstSelectedColumn();
  int last_col = d_view->lastSelectedColumn();
  if (first_col < 0) return;

  WAIT_CURSOR;
  beginMacro(tr("%1: clear selected cell(s)").arg(name()));
  for (int i = first_row; i <= last_row; i++)
    for (int j = first_col; j <= last_col; j++)
      if (d_view->isCellSelected(i, j))
        exec(new MatrixSetCellValueCmd(d_matrix_private, i, j, 0.0));
  endMacro();
  RESET_CURSOR;
}

QMenu *MatrixViewProvider::createContextMenu() const {
  QMenu *menu = AbstractPart::createContextMenu();
  Q_ASSERT(menu);
  menu->addSeparator();

  menu->addAction(action_duplicate);
  // TODO menu->addAction( ....

  return menu;
}

QMenu *MatrixViewProvider::createSelectionMenu(QMenu *append_to) {
  QMenu *menu = append_to;
  if (!menu) menu = new QMenu();

  menu->addAction(action_cut_selection);
  menu->addAction(action_copy_selection);
  menu->addAction(action_paste_into_selection);
  menu->addAction(action_clear_selection);

  return menu;
}

QMenu *MatrixViewProvider::createColumnMenu(QMenu *append_to) {
  QMenu *menu = append_to;
  if (!menu) menu = new QMenu();

  menu->addAction(action_insert_columns);
  menu->addAction(action_remove_columns);
  menu->addAction(action_clear_columns);
  menu->addSeparator();
  menu->addAction(action_edit_coordinates);

  return menu;
}

QMenu *MatrixViewProvider::createMatrixMenu(QMenu *append_to) {
  QMenu *menu = append_to;
  if (!menu) menu = new QMenu();

  menu->addAction(action_toggle_tabbar);
  menu->addSeparator();
  menu->addAction(action_select_all);
  menu->addAction(action_clear_matrix);
  menu->addSeparator();
  menu->addAction(action_set_formula);
  menu->addAction(action_recalculate);
  menu->addSeparator();
  menu->addAction(action_edit_format);
  menu->addSeparator();
  menu->addAction(action_go_to_cell);

  return menu;
}

QMenu *MatrixViewProvider::createRowMenu(QMenu *append_to) {
  QMenu *menu = append_to;
  if (!menu) menu = new QMenu();

  menu->addAction(action_insert_rows);
  menu->addAction(action_remove_rows);
  menu->addAction(action_clear_rows);
  menu->addSeparator();
  menu->addAction(action_edit_coordinates);

  return menu;
}

void MatrixViewProvider::createActions() {
  // selection related actions
  action_cut_selection = new QAction(
      IconLoader::load(QString::fromLatin1("edit-cut"), IconLoader::LightDark), tr("Cu&t"), this);
  actionManager()->addAction(action_cut_selection, QString::fromLatin1("cut_selection"));

  action_copy_selection = new QAction(
      IconLoader::load(QString::fromLatin1("edit-copy"), IconLoader::LightDark), tr("&Copy"), this);
  actionManager()->addAction(action_copy_selection, QString::fromLatin1("copy_selection"));

  action_paste_into_selection =
      new QAction(IconLoader::load(QString::fromLatin1("edit-paste"), IconLoader::LightDark),
                  tr("Past&e"), this);
  actionManager()->addAction(action_paste_into_selection,
                             QString::fromLatin1("paste_into_selection"));

  action_clear_selection =
      new QAction(IconLoader::load(QString::fromLatin1("clear-loginfo"), IconLoader::General),
                  tr("Clea&r", "clear selection"), this);
  actionManager()->addAction(action_clear_selection, QString::fromLatin1("clear_selection"));

  // matrix related actions
  action_set_formula =
      new QAction(IconLoader::load(QString::fromLatin1("math-fofx"), IconLoader::LightDark),
                  tr("Assign &Formula"), this);
  action_set_formula->setShortcut(tr("Alt+Q"));
  actionManager()->addAction(action_set_formula, QString::fromLatin1("set_formula"));

  action_recalculate =
      new QAction(IconLoader::load(QString::fromLatin1("edit-recalculate"), IconLoader::LightDark),
                  tr("Recalculate"), this);
  action_recalculate->setShortcut(tr("Ctrl+Return"));
  actionManager()->addAction(action_recalculate, QString::fromLatin1("recalculate"));

  action_toggle_tabbar =
      new QAction(IconLoader::load(QString::fromLatin1("edit-unhide"), IconLoader::LightDark),
                  QString::fromLatin1(("Show/Hide Controls")),
                  this);  // show/hide control tabs
  action_toggle_tabbar->setShortcut(tr("F12"));
  actionManager()->addAction(action_toggle_tabbar, QString::fromLatin1("toggle_tabbar"));

  action_select_all = new QAction(
      IconLoader::load(QString::fromLatin1("edit-matrix-select-all"), IconLoader::LightDark),
      tr("Select All"), this);
  actionManager()->addAction(action_select_all, QString::fromLatin1("select_all"));

  action_clear_matrix =
      new QAction(IconLoader::load(QString::fromLatin1("edit-matrix-clear"), IconLoader::LightDark),
                  tr("Clear Matrix"), this);
  actionManager()->addAction(action_clear_matrix, QString::fromLatin1("clear_matrix"));

  action_go_to_cell =
      new QAction(IconLoader::load(QString::fromLatin1("goto-cell"), IconLoader::LightDark),
                  tr("&Go to Cell"), this);
  action_go_to_cell->setShortcut(tr("Ctrl+Alt+G"));
  actionManager()->addAction(action_go_to_cell, QString::fromLatin1("go_to_cell"));

  action_transpose = new QAction(tr("&Transpose"), this);
  actionManager()->addAction(action_transpose, QString::fromLatin1("transpose"));

  action_mirror_horizontally = new QAction(tr("Mirror &Horizontally"), this);
  actionManager()->addAction(action_mirror_horizontally, QString::fromLatin1("mirror_horizontally"));

  action_mirror_vertically = new QAction(tr("Mirror &Vertically"), this);
  actionManager()->addAction(action_mirror_vertically, QString::fromLatin1("mirror_vertically"));

  action_import_image =
      new QAction(tr("&Import Image", "import image as matrix"), this);
  actionManager()->addAction(action_import_image, QString::fromLatin1("import_image"));

  action_duplicate =
      new QAction(IconLoader::load(QString::fromLatin1("edit-duplicate"), IconLoader::LightDark),
                  tr("&Duplicate", "duplicate matrix"), this);
  actionManager()->addAction(action_duplicate, QString::fromLatin1("duplicate"));

  action_edit_coordinates = new QAction(tr("Set &Coordinates"), this);
  actionManager()->addAction(action_edit_coordinates, QString::fromLatin1("edit_coordinates"));

  action_edit_format = new QAction(tr("Set Display &Format"), this);
  actionManager()->addAction(action_edit_format, QString::fromLatin1("edit_format"));

  // column related actions
  action_insert_columns = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-insert-column"), IconLoader::LightDark),
      tr("&Insert Empty Columns"), this);
  actionManager()->addAction(action_insert_columns, QString::fromLatin1("insert_columns"));

  action_remove_columns = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-delete-column"), IconLoader::LightDark),
      tr("Remo&ve Columns"), this);
  actionManager()->addAction(action_remove_columns, QString::fromLatin1("remove_columns"));

  action_clear_columns = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-clear-column"), IconLoader::LightDark),
      tr("Clea&r Columns"), this);
  actionManager()->addAction(action_clear_columns, QString::fromLatin1("clear_columns"));

  action_add_columns = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-insert-column-right"), IconLoader::LightDark),
      tr("&Add Columns"), this);
  actionManager()->addAction(action_add_columns, QString::fromLatin1("add_columns"));

  // row related actions
  action_insert_rows = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-insert-row"), IconLoader::LightDark),
      tr("&Insert Empty Rows"), this);
  actionManager()->addAction(action_insert_rows, QString::fromLatin1("insert_rows"));

  action_remove_rows = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-delete-row"), IconLoader::LightDark),
      tr("Remo&ve Rows"), this);
  actionManager()->addAction(action_remove_rows, QString::fromLatin1("remove_rows"));

  action_clear_rows = new QAction(
      IconLoader::load(QString::fromLatin1("edit-table-clear-row"), IconLoader::LightDark),
      tr("Clea&r Rows"), this);
  actionManager()->addAction(action_clear_rows, QString::fromLatin1("clear_rows"));

  action_add_rows =
      new QAction(IconLoader::load(QString::fromLatin1("edit-table-add-row"), IconLoader::LightDark),
                  tr("&Add Rows"), this);
  actionManager()->addAction(action_add_rows, QString::fromLatin1("add_rows"));
}

void MatrixViewProvider::connectActions() {
  connect(action_cut_selection, SIGNAL(triggered()), this,
          SLOT(cutSelection()));
  connect(action_copy_selection, SIGNAL(triggered()), this,
          SLOT(copySelection()));
  connect(action_paste_into_selection, SIGNAL(triggered()), this,
          SLOT(pasteIntoSelection()));
  connect(action_set_formula, SIGNAL(triggered()), this, SLOT(editFormula()));
  connect(action_edit_coordinates, SIGNAL(triggered()), this,
          SLOT(editCoordinates()));
  connect(action_edit_format, SIGNAL(triggered()), this, SLOT(editFormat()));
  connect(action_clear_selection, SIGNAL(triggered()), this,
          SLOT(clearSelectedCells()));
#ifdef LEGACY_CODE_0_2_x
  connect(action_recalculate, SIGNAL(triggered()), this,
          SLOT(recalculateSelectedCells()));
#endif
  connect(action_select_all, SIGNAL(triggered()), this, SLOT(selectAll()));
  connect(action_clear_matrix, SIGNAL(triggered()), this, SLOT(clear()));
  connect(action_transpose, SIGNAL(triggered()), this, SLOT(transpose()));
  connect(action_mirror_horizontally, SIGNAL(triggered()), this,
          SLOT(mirrorHorizontally()));
  connect(action_mirror_vertically, SIGNAL(triggered()), this,
          SLOT(mirrorVertically()));
  connect(action_go_to_cell, SIGNAL(triggered()), this, SLOT(goToCell()));
  connect(action_import_image, SIGNAL(triggered()), this,
          SLOT(importImageDialog()));
  connect(action_duplicate, SIGNAL(triggered()), this, SLOT(duplicate()));
  connect(action_insert_columns, SIGNAL(triggered()), this,
          SLOT(insertEmptyColumns()));
  connect(action_remove_columns, SIGNAL(triggered()), this,
          SLOT(removeSelectedColumns()));
  connect(action_clear_columns, SIGNAL(triggered()), this,
          SLOT(clearSelectedColumns()));
  connect(action_insert_rows, SIGNAL(triggered()), this,
          SLOT(insertEmptyRows()));
  connect(action_remove_rows, SIGNAL(triggered()), this,
          SLOT(removeSelectedRows()));
  connect(action_clear_rows, SIGNAL(triggered()), this,
          SLOT(clearSelectedRows()));
  connect(action_add_columns, SIGNAL(triggered()), this, SLOT(addColumns()));
  connect(action_add_rows, SIGNAL(triggered()), this, SLOT(addRows()));
}

void MatrixViewProvider::addActionsToView() {
  connect(action_toggle_tabbar, SIGNAL(triggered()), d_view,
          SLOT(toggleControlTabBar()));

  d_view->addAction(action_cut_selection);
  d_view->addAction(action_copy_selection);
  d_view->addAction(action_paste_into_selection);
  d_view->addAction(action_set_formula);
  d_view->addAction(action_edit_coordinates);
  d_view->addAction(action_edit_format);
  d_view->addAction(action_clear_selection);
  d_view->addAction(action_recalculate);
  d_view->addAction(action_toggle_tabbar);
  d_view->addAction(action_select_all);
  d_view->addAction(action_clear_matrix);
  d_view->addAction(action_transpose);
  d_view->addAction(action_mirror_horizontally);
  d_view->addAction(action_mirror_vertically);
  d_view->addAction(action_go_to_cell);
  d_view->addAction(action_import_image);
#ifndef LEGACY_CODE_0_2_x
  d_view->addAction(action_duplicate);
#endif
  d_view->addAction(action_insert_columns);
  d_view->addAction(action_remove_columns);
  d_view->addAction(action_clear_columns);
  d_view->addAction(action_insert_rows);
  d_view->addAction(action_remove_rows);
  d_view->addAction(action_clear_rows);
  d_view->addAction(action_add_columns);
  d_view->addAction(action_add_rows);
}

bool MatrixViewProvider::fillProjectMenu(QMenu *menu) {
  menu->setTitle(tr("&Matrix"));

  menu->addAction(action_toggle_tabbar);
  menu->addSeparator();
  menu->addAction(action_edit_coordinates);
  menu->addAction(action_edit_format);
  menu->addSeparator();
  menu->addAction(action_set_formula);
  menu->addAction(action_recalculate);
  menu->addSeparator();
  menu->addAction(action_clear_matrix);
  menu->addAction(action_transpose);
  menu->addAction(action_mirror_horizontally);
  menu->addAction(action_mirror_vertically);
  menu->addSeparator();
#ifndef LEGACY_CODE_0_2_x
  menu->addAction(action_duplicate);
#endif
  menu->addAction(action_import_image);
  menu->addSeparator();
  menu->addAction(action_go_to_cell);

  return true;

  // TODO:
  // Convert to Table
  // Export
}

void MatrixViewProvider::showMatrixViewContextMenu(const QPoint &pos) {
  if (!d_view) return;
  QMenu context_menu;

  createSelectionMenu(&context_menu);
  context_menu.addSeparator();
  createMatrixMenu(&context_menu);
  context_menu.addSeparator();

  context_menu.exec(pos);
}

void MatrixViewProvider::showMatrixViewColumnContextMenu(const QPoint &pos) {
  QMenu context_menu;

  createColumnMenu(&context_menu);

  context_menu.exec(pos);
}

void MatrixViewProvider::showMatrixViewRowContextMenu(const QPoint &pos) {
  QMenu context_menu;

  createRowMenu(&context_menu);

  context_menu.exec(pos);
}

void MatrixViewProvider::goToCell() {
  if (!d_view) return;
  bool ok;

  int col = QInputDialog::getInt(nullptr, tr("Go to Cell"), tr("Enter column"),
                                 1, 1, columnCount(), 1, &ok);
  if (!ok) return;

  int row = QInputDialog::getInt(nullptr, tr("Go to Cell"), tr("Enter row"), 1,
                                 1, rowCount(), 1, &ok);
  if (!ok) return;

  d_view->goToCell(row - 1, col - 1);
}

void MatrixViewProvider::copy(MatrixViewProvider* other) {
  WAIT_CURSOR;
  beginMacro(QObject::tr("%1: copy %2").arg(name()).arg(other->name()));
  int rows = other->rowCount();
  int columns = other->columnCount();
  setDimensions(rows, columns);
  for (int i = 0; i < rows; i++) setRowHeight(i, other->rowHeight(i));
  for (int i = 0; i < columns; i++) setColumnWidth(i, other->columnWidth(i));
  d_matrix_private->blockChangeSignals(true);
  for (int i = 0; i < columns; i++)
    setColumnCells(i, 0, rows - 1, other->columnCells(i, 0, rows - 1));
  setCoordinates(other->xStart(), other->xEnd(), other->yStart(),
                 other->yEnd());
  setNumericFormat(other->numericFormat());
  setDisplayedDigits(other->displayedDigits());
  setFormula(other->formula());
  d_matrix_private->blockChangeSignals(false);
  Q_EMIT dataChanged(0, 0, rows - 1, columns - 1);
  if (d_view) d_view->rereadSectionSizes();
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::setPlotMenu(QMenu *menu) { d_plot_menu = menu; }

QIcon MatrixViewProvider::icon() const {
  return IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark);
}

QString MatrixViewProvider::text(int row, int col) {
  return QLocale().toString(cell(row, col), d_matrix_private->numericFormat(),
                            d_matrix_private->displayedDigits());
}

void MatrixViewProvider::selectAll() {
  if (!d_view) return;
  d_view->selectAll();
}

void MatrixViewProvider::setCell(int row, int col, double value) {
  if (row < 0 || row >= rowCount()) return;
  if (col < 0 || col >= columnCount()) return;
  exec(new MatrixSetCellValueCmd(d_matrix_private, row, col, value));
}

void MatrixViewProvider::importImageDialog() {
  QList<QByteArray> formats = QImageReader::supportedImageFormats();
  QString filter = tr("Images") + QString::fromLatin1(" (");
  for (int i = 0; i < formats.count(); i++)
    filter += QString::fromLatin1(" *.") + QString::fromLatin1(formats.at(i)) + QString::fromLatin1(" ");
  filter += QString::fromLatin1(");;");
  for (int i = 0; i < formats.count(); i++)
    filter += QString::fromLatin1(" *.") + QString::fromLatin1(formats.at(i)) + QString::fromLatin1(" (*.") + QString::fromLatin1(formats.at(i)) + QString::fromLatin1(");;");

  QString images_path = global(QString::fromLatin1("images_path")).toString();
  QString file_name = QFileDialog::getOpenFileName(
      nullptr, tr("Import image from file"), images_path, filter);
  if (!file_name.isEmpty()) {
    QFileInfo file_info(file_name);
    images_path = file_info.canonicalPath();
    setGlobal(QString::fromLatin1("images_path"), images_path);
    QImage image(file_name);
    MatrixViewProvider* matrix = nullptr;
    if (!image.isNull()) matrix = MatrixViewProvider::fromImage(image);
    if (matrix) {
      copy(matrix);
      delete matrix;
    } else
      QMessageBox::information(
          nullptr, tr("Error importing image"),
          tr("Import of image '%1' failed").arg(file_name));
  }
}

void MatrixViewProvider::duplicate() {
#ifndef LEGACY_CODE_0_2_x
  Matrix *matrix = new Matrix(0, rowCount(), columnCount(), name());
  matrix->copy(this);
  if (folder()) folder()->addChild(matrix);
#endif
}

void MatrixViewProvider::editFormat() {
  if (!d_view) return;
  d_view->showControlFormatTab();
}

void MatrixViewProvider::editCoordinates() {
  if (!d_view) return;
  d_view->showControlCoordinatesTab();
}

void MatrixViewProvider::editFormula() {
  if (!d_view) return;
  d_view->showControlFormulaTab();
}

void MatrixViewProvider::addRows() {
  if (!d_view) return;
  WAIT_CURSOR;
  int count = d_view->selectedRowCount(false);
  beginMacro(QObject::tr("%1: add %2 rows(s)").arg(name()).arg(count));
  exec(new MatrixInsertRowsCmd(d_matrix_private, rowCount(), count));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::addColumns() {
  if (!d_view) return;
  WAIT_CURSOR;
  int count = d_view->selectedRowCount(false);
  beginMacro(QObject::tr("%1: add %2 column(s)").arg(name()).arg(count));
  exec(new MatrixInsertColumnsCmd(d_matrix_private, columnCount(), count));
  endMacro();
  RESET_CURSOR;
}

void MatrixViewProvider::setXStart(double x) {
  WAIT_CURSOR;
  exec(new MatrixSetCoordinatesCmd(d_matrix_private, x, xEnd(), yStart(),
                                   yEnd()));
  RESET_CURSOR;
}

void MatrixViewProvider::setXEnd(double x) {
  WAIT_CURSOR;
  exec(new MatrixSetCoordinatesCmd(d_matrix_private, xStart(), x, yStart(),
                                   yEnd()));
  RESET_CURSOR;
}

void MatrixViewProvider::setYStart(double y) {
  WAIT_CURSOR;
  exec(new MatrixSetCoordinatesCmd(d_matrix_private, xStart(), xEnd(), y,
                                   yEnd()));
  RESET_CURSOR;
}

void MatrixViewProvider::setYEnd(double y) {
  WAIT_CURSOR;
  exec(new MatrixSetCoordinatesCmd(d_matrix_private, xStart(), xEnd(), yStart(),
                                   y));
  RESET_CURSOR;
}

void MatrixViewProvider::setCoordinates(double x1, double x2, double y1, double y2) {
  WAIT_CURSOR;
  exec(new MatrixSetCoordinatesCmd(d_matrix_private, x1, x2, y1, y2));
  RESET_CURSOR;
}

void MatrixViewProvider::setNumericFormat(char format) {
  if (format == numericFormat()) return;
  WAIT_CURSOR;
  exec(new MatrixSetFormatCmd(d_matrix_private, format));
  RESET_CURSOR;
}

void MatrixViewProvider::setDisplayedDigits(int digits) {
  if (digits == displayedDigits()) return;
  WAIT_CURSOR;
  exec(new MatrixSetDigitsCmd(d_matrix_private, digits));
  RESET_CURSOR;
}

double MatrixViewProvider::xStart() const { return d_matrix_private->xStart(); }

double MatrixViewProvider::yStart() const { return d_matrix_private->yStart(); }

double MatrixViewProvider::xEnd() const { return d_matrix_private->xEnd(); }

double MatrixViewProvider::yEnd() const { return d_matrix_private->yEnd(); }

QString MatrixViewProvider::formula() const { return d_matrix_private->formula(); }

void MatrixViewProvider::setFormula(const QString &formula) {
  WAIT_CURSOR;
  exec(new MatrixSetFormulaCmd(d_matrix_private, formula));
  RESET_CURSOR;
}

char MatrixViewProvider::numericFormat() const { return d_matrix_private->numericFormat(); }

int MatrixViewProvider::displayedDigits() const {
  return d_matrix_private->displayedDigits();
}

void MatrixViewProvider::save(QXmlStreamWriter *writer, const bool saveastemplate) const {
  int cols = columnCount();
  int rows = rowCount();
  writer->writeStartElement(QString::fromLatin1("matrix"));
  writeBasicAttributes(writer);
  writer->writeAttribute(QString::fromLatin1("columns"), QString::number(cols));
  writer->writeAttribute(QString::fromLatin1("rows"), QString::number(rows));
  writeCommentElement(writer);
  writer->writeStartElement(QString::fromLatin1("formula"));
  writer->writeCharacters(formula());
  writer->writeEndElement();
  writer->writeStartElement(QString::fromLatin1("display"));
  writer->writeAttribute(QString::fromLatin1("numeric_format"), QString(QChar::fromLatin1(numericFormat())));
  writer->writeAttribute(QString::fromLatin1("displayed_digits"),
                         QString::number(displayedDigits()));
  writer->writeEndElement();
  writer->writeStartElement(QString::fromLatin1("coordinates"));
  writer->writeAttribute(QString::fromLatin1("x_start"), QString::number(xStart()));
  writer->writeAttribute(QString::fromLatin1("x_end"), QString::number(xEnd()));
  writer->writeAttribute(QString::fromLatin1("y_start"), QString::number(yStart()));
  writer->writeAttribute(QString::fromLatin1("y_end"), QString::number(yEnd()));
  writer->writeEndElement();

  if (!saveastemplate)
    for (int col = 0; col < cols; col++)
      for (int row = 0; row < rows; row++) {
        writer->writeStartElement(QString::fromLatin1("cell"));
        writer->writeAttribute(QString::fromLatin1("row"), QString::number(row));
        writer->writeAttribute(QString::fromLatin1("column"), QString::number(col));
        writer->writeCharacters(QString::number(cell(row, col), 'e', 16));
        writer->writeEndElement();
      }
  for (int col = 0; col < cols; col++) {
    writer->writeStartElement(QString::fromLatin1("column_width"));
    writer->writeAttribute(QString::fromLatin1("column"), QString::number(col));
    writer->writeCharacters(QString::number(columnWidth(col)));
    writer->writeEndElement();
  }
  for (int row = 0; row < rows; row++) {
    writer->writeStartElement(QString::fromLatin1("row_height"));
    writer->writeAttribute(QString::fromLatin1("row"), QString::number(row));
    writer->writeCharacters(QString::number(rowHeight(row)));
    writer->writeEndElement();
  }
  writer->writeEndElement();  // "matrix"
}

bool MatrixViewProvider::load(XmlStreamReader *reader) {
  if (reader->isStartElement() && reader->name() == QString::fromLatin1("matrix")) {
    setDimensions(0, 0);
    setComment(QString::fromLatin1(""));
    setFormula(QString::fromLatin1(""));
    setNumericFormat('f');
    setDisplayedDigits(6);
    setCoordinates(0.0, 1.0, 0.0, 1.0);

    if (!readBasicAttributes(reader)) return false;

    // read dimensions
    bool ok1, ok2;
    int rows, cols;
    rows = reader->readAttributeInt(QString::fromLatin1("rows"), &ok1);
    cols = reader->readAttributeInt(QString::fromLatin1("columns"), &ok2);
    if (!ok1 || !ok2) {
      reader->raiseError(tr("invalid row or column count"));
      return false;
    }
    d_matrix_private->blockChangeSignals(true);
    setDimensions(rows, cols);

    // read child elements
    while (!reader->atEnd()) {
      reader->readNext();

      if (reader->isEndElement()) break;

      if (reader->isStartElement()) {
        bool ret_val = true;
        if (reader->name() == QString::fromLatin1("comment"))
          ret_val = readCommentElement(reader);
        else if (reader->name() == QString::fromLatin1("formula"))
          ret_val = readFormulaElement(reader);
        else if (reader->name() == QString::fromLatin1("display"))
          ret_val = readDisplayElement(reader);
        else if (reader->name() == QString::fromLatin1("coordinates"))
          ret_val = readCoordinatesElement(reader);
        else if (reader->name() == QString::fromLatin1("cell"))
          ret_val = readCellElement(reader);
        else if (reader->name() == QString::fromLatin1("row_height"))
          ret_val = readRowHeightElement(reader);
        else if (reader->name() == QString::fromLatin1("column_width"))
          ret_val = readColumnWidthElement(reader);
        else  // unknown element
        {
          reader->raiseWarning(
              tr("unknown element '%1'").arg(reader->name().toString()));
          if (!reader->skipToEndElement()) return false;
        }
        if (!ret_val) return false;
      }
    }
    d_matrix_private->blockChangeSignals(false);
  } else  // no matrix element
    reader->raiseError(tr("no matrix element found"));

  return !reader->hasError();
}

bool MatrixViewProvider::readDisplayElement(XmlStreamReader *reader) {
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("display"));
  QXmlStreamAttributes attribs = reader->attributes();

  QString str =
      attribs.value(reader->namespaceUri().toString(), QString::fromLatin1("numeric_format"))
          .toString();
  if (str.isEmpty() || str.length() != 1) {
    reader->raiseError(tr("invalid or missing numeric format"));
    return false;
  }
  setNumericFormat(str.at(0).toLatin1());

  bool ok;
  int digits = reader->readAttributeInt(QString::fromLatin1("displayed_digits"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid or missing number of displayed digits"));
    return false;
  }
  setDisplayedDigits(digits);
  if (!reader->skipToEndElement()) return false;

  return true;
}

bool MatrixViewProvider::readCoordinatesElement(XmlStreamReader *reader) {
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("coordinates"));

  bool ok;
  int val;

  val = reader->readAttributeInt(QString::fromLatin1("x_start"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid x start value"));
    return false;
  }
  setXStart(val);

  val = reader->readAttributeInt(QString::fromLatin1("x_end"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid x end value"));
    return false;
  }
  setXEnd(val);

  val = reader->readAttributeInt(QString::fromLatin1("y_start"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid y start value"));
    return false;
  }
  setYStart(val);

  val = reader->readAttributeInt(QString::fromLatin1("y_end"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid y end value"));
    return false;
  }
  setYEnd(val);
  if (!reader->skipToEndElement()) return false;

  return true;
}

bool MatrixViewProvider::readFormulaElement(XmlStreamReader *reader) {
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("formula"));
  setFormula(reader->readElementText());
  return true;
}

bool MatrixViewProvider::readRowHeightElement(XmlStreamReader *reader) {
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("row_height"));
  bool ok;
  int row = reader->readAttributeInt(QString::fromLatin1("row"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid or missing row index"));
    return false;
  }
  QString str = reader->readElementText();
  int value = str.toInt(&ok);
  if (!ok) {
    reader->raiseError(tr("invalid row height"));
    return false;
  }
  if (d_view)
    d_view->setRowHeight(row, value);
  else
    setRowHeight(row, value);
  return true;
}

bool MatrixViewProvider::readColumnWidthElement(XmlStreamReader *reader) {
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("column_width"));
  bool ok;
  int col = reader->readAttributeInt(QString::fromLatin1("column"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid or missing column index"));
    return false;
  }
  QString str = reader->readElementText();
  int value = str.toInt(&ok);
  if (!ok) {
    reader->raiseError(tr("invalid column width"));
    return false;
  }
  if (d_view)
    d_view->setColumnWidth(col, value);
  else
    setColumnWidth(col, value);
  return true;
}

bool MatrixViewProvider::readCellElement(XmlStreamReader *reader) {
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("cell"));

  QString str;
  int row, col;
  bool ok;

  QXmlStreamAttributes attribs = reader->attributes();
  row = reader->readAttributeInt(QString::fromLatin1("row"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid or missing row index"));
    return false;
  }
  col = reader->readAttributeInt(QString::fromLatin1("column"), &ok);
  if (!ok) {
    reader->raiseError(tr("invalid or missing column index"));
    return false;
  }

  str = reader->readElementText();
  double value = str.toDouble(&ok);
  if (!ok) {
    reader->raiseError(tr("invalid cell value"));
    return false;
  }
  setCell(row, col, value);

  return true;
}

void MatrixViewProvider::setRowHeight(int row, int height) {
  d_matrix_private->setRowHeight(row, height);
}

void MatrixViewProvider::setColumnWidth(int col, int width) {
  d_matrix_private->setColumnWidth(col, width);
}

int MatrixViewProvider::rowHeight(int row) const {
  return d_matrix_private->rowHeight(row);
}

int MatrixViewProvider::columnWidth(int col) const {
  return d_matrix_private->columnWidth(col);
}

void MatrixViewProvider::loadIcons() {
  action_cut_selection->setIcon(
      IconLoader::load(QString::fromLatin1("edit-cut"), IconLoader::LightDark));
  action_copy_selection->setIcon(
      IconLoader::load(QString::fromLatin1("edit-copy"), IconLoader::LightDark));
  action_paste_into_selection->setIcon(
      IconLoader::load(QString::fromLatin1("edit-paste"), IconLoader::LightDark));
  action_clear_selection->setIcon(
      IconLoader::load(QString::fromLatin1("clear-loginfo"), IconLoader::General));
  // matrix related actions
  action_set_formula->setIcon(
      IconLoader::load(QString::fromLatin1("math-fofx"), IconLoader::LightDark));
  action_recalculate->setIcon(
      IconLoader::load(QString::fromLatin1("edit-recalculate"), IconLoader::LightDark));
  action_select_all->setIcon(
      IconLoader::load(QString::fromLatin1("edit-matrix-select-all"), IconLoader::LightDark));
  action_clear_matrix->setIcon(
      IconLoader::load(QString::fromLatin1("edit-matrix-clear"), IconLoader::LightDark));
  action_go_to_cell->setIcon(
      IconLoader::load(QString::fromLatin1("goto-cell"), IconLoader::LightDark));
  action_duplicate->setIcon(
      IconLoader::load(QString::fromLatin1("edit-duplicate"), IconLoader::LightDark));
  // column related actions
  action_insert_columns->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-insert-column"), IconLoader::LightDark));
  action_remove_columns->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-delete-column"), IconLoader::LightDark));
  action_clear_columns->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-clear-column"), IconLoader::LightDark));
  action_add_columns->setIcon(IconLoader::load(QString::fromLatin1("edit-table-insert-column-right"),
                                               IconLoader::LightDark));
  // row related actions
  action_insert_rows->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-insert-row"), IconLoader::LightDark));
  action_remove_rows->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-delete-row"), IconLoader::LightDark));
  action_clear_rows->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-clear-row"), IconLoader::LightDark));
  action_add_rows->setIcon(
      IconLoader::load(QString::fromLatin1("edit-table-add-row"), IconLoader::LightDark));
  d_view->loadIcons();
}

void MatrixViewProvider::adjustTabBarAction(bool visible) {
  if (visible) {
    action_toggle_tabbar->setText(tr("Hide Controls"));
    action_toggle_tabbar->setIcon(
        IconLoader::load(QString::fromLatin1("edit-hide"), IconLoader::LightDark));
  } else {
    action_toggle_tabbar->setText(tr("Show Controls"));
    action_toggle_tabbar->setIcon(
        IconLoader::load(QString::fromLatin1("edit-unhide"), IconLoader::LightDark));
  }
}

QVector<qreal> MatrixViewProvider::columnCells(int col, int first_row, int last_row) {
  return d_matrix_private->columnCells(col, first_row, last_row);
}

void MatrixViewProvider::setColumnCells(int col, int first_row, int last_row,
                            const QVector<qreal> &values) {
  WAIT_CURSOR;
  exec(new MatrixSetColumnCellsCmd(d_matrix_private, col, first_row, last_row,
                                   values));
  RESET_CURSOR;
}

QVector<qreal> MatrixViewProvider::rowCells(int row, int first_column, int last_column) {
  return d_matrix_private->rowCells(row, first_column, last_column);
}

void MatrixViewProvider::setRowCells(int row, int first_column, int last_column,
                         const QVector<qreal> &values) {
  WAIT_CURSOR;
  exec(new MatrixSetRowCellsCmd(d_matrix_private, row, first_column,
                                last_column, values));
  RESET_CURSOR;
}

void MatrixViewProvider::transpose() {
  WAIT_CURSOR;
  exec(new MatrixTransposeCmd(d_matrix_private));
  RESET_CURSOR;
}

void MatrixViewProvider::mirrorHorizontally() {
  WAIT_CURSOR;
  exec(new MatrixMirrorHorizontallyCmd(d_matrix_private));
  RESET_CURSOR;
}

void MatrixViewProvider::mirrorVertically() {
  WAIT_CURSOR;
  exec(new MatrixMirrorVerticallyCmd(d_matrix_private));
  RESET_CURSOR;
}

void MatrixViewProvider::recalculateSelectedCells() {
 /* if (!d_view) return;
#ifdef LEGACY_CODE_0_2_x
  WAIT_CURSOR;
  beginMacro(tr("%1: apply formula to selection").arg(name()));
  Q_EMIT recalculate();
  endMacro();
  RESET_CURSOR;
#endif*/
}

void MatrixViewProvider::showOnlyValues(const bool status) { showonlyvalues_ = status; }

bool MatrixViewProvider::getShowOnlyValues() const { return showonlyvalues_; }

/* ========================= static methods ======================= */
ActionManager *MatrixViewProvider::action_manager = nullptr;

ActionManager *MatrixViewProvider::actionManager() {
  if (!action_manager) initActionManager();

  return action_manager;
}

void MatrixViewProvider::initActionManager() {
  if (!action_manager) action_manager = new ActionManager();

  action_manager->setTitle(tr("Matrix"));
  volatile MatrixViewProvider* action_creator =
      new MatrixViewProvider();  // initialize the action texts
  delete action_creator;
}

MatrixViewProvider* MatrixViewProvider::fromImage(const QImage &image) {
  int cols = image.width();
  int rows = image.height();

  QProgressDialog progress;
  progress.setRange(0, cols);
  progress.setWindowTitle(tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Import image..."));
  progress.raise();

  MatrixViewProvider* matrix = new MatrixViewProvider(nullptr, rows, cols, tr("Matrix %1").arg(1));

  QVector<qreal> values;
  values.resize(rows);

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++)
      values[j] = qGray(image.pixel(i, rows - 1 - j));

    matrix->setColumnCells(i, 0, rows - 1, values);

    if (i % 5 == 4) {
      progress.setValue(i);
      QApplication::processEvents();
    }

    if (progress.wasCanceled()) break;
  }

  if (progress.wasCanceled()) {
    delete matrix;
    return nullptr;
  }
  return matrix;
}

/* ========================== MatrixViewProvider::Private ====================== */

MatrixViewProvider::Private::Private(MatrixViewProvider* owner)
    : d_owner(owner), d_column_count(0), d_row_count(0) {
  d_block_change_signals = false;
  d_numeric_format = 'f';
  d_displayed_digits = 6;
  d_x_start = 0.0;
  d_x_end = 1.0;
  d_y_start = 0.0;
  d_y_end = 1.0;
}

void MatrixViewProvider::Private::insertColumns(int before, int count) {
  Q_ASSERT(before >= 0);
  Q_ASSERT(before <= d_column_count);

  Q_EMIT d_owner->columnsAboutToBeInserted(before, count);
  for (int i = 0; i < count; i++) {
    d_data.insert(before + i, QVector<qreal>(d_row_count));
    d_column_widths.insert(before + i, MatrixViewProvider::defaultColumnWidth());
  }

  d_column_count += count;
  Q_EMIT d_owner->columnsInserted(before, count);
}

void MatrixViewProvider::Private::removeColumns(int first, int count) {
  Q_EMIT d_owner->columnsAboutToBeRemoved(first, count);
  Q_ASSERT(first >= 0);
  Q_ASSERT(first + count <= d_column_count);
  d_data.remove(first, count);
  for (int i = 0; i < count; i++) d_column_widths.removeAt(first);
  d_column_count -= count;
  Q_EMIT d_owner->columnsRemoved(first, count);
}

void MatrixViewProvider::Private::insertRows(int before, int count) {
  Q_EMIT d_owner->rowsAboutToBeInserted(before, count);
  Q_ASSERT(before >= 0);
  Q_ASSERT(before <= d_row_count);
  for (int col = 0; col < d_column_count; col++)
    for (int i = 0; i < count; i++) d_data[col].insert(before + i, 0.0);
  for (int i = 0; i < count; i++)
    d_row_heights.insert(before + i, MatrixViewProvider::defaultRowHeight());

  d_row_count += count;
  Q_EMIT d_owner->rowsInserted(before, count);
}

void MatrixViewProvider::Private::removeRows(int first, int count) {
  Q_EMIT d_owner->rowsAboutToBeRemoved(first, count);
  Q_ASSERT(first >= 0);
  Q_ASSERT(first + count <= d_row_count);
  for (int col = 0; col < d_column_count; col++)
    d_data[col].remove(first, count);
  for (int i = 0; i < count; i++) d_row_heights.removeAt(first);

  d_row_count -= count;
  Q_EMIT d_owner->rowsRemoved(first, count);
}

double MatrixViewProvider::Private::cell(int row, int col) const {
  Q_ASSERT(row >= 0 && row < d_row_count);
  Q_ASSERT(col >= 0 && col < d_column_count);
  return d_data.at(col).at(row);
}

void MatrixViewProvider::Private::setCell(int row, int col, double value) {
  Q_ASSERT(row >= 0 && row < d_row_count);
  Q_ASSERT(col >= 0 && col < d_column_count);
  d_data[col][row] = value;
  if (!d_block_change_signals) Q_EMIT d_owner->dataChanged(row, col, row, col);
}

QVector<qreal> MatrixViewProvider::Private::columnCells(int col, int first_row,
                                            int last_row) {
  Q_ASSERT(first_row >= 0 && first_row < d_row_count);
  Q_ASSERT(last_row >= 0 && last_row < d_row_count);

  if (first_row == 0 && last_row == d_row_count - 1) return d_data.at(col);

  QVector<qreal> result;
  for (int i = first_row; i <= last_row; i++)
    result.append(d_data.at(col).at(i));
  return result;
}

void MatrixViewProvider::Private::setColumnCells(int col, int first_row, int last_row,
                                     const QVector<qreal> &values) {
  Q_ASSERT(first_row >= 0 && first_row < d_row_count);
  Q_ASSERT(last_row >= 0 && last_row < d_row_count);
  Q_ASSERT(values.count() > last_row - first_row);

  if (first_row == 0 && last_row == d_row_count - 1) {
    d_data[col] = values;
    d_data[col].resize(d_row_count);  // values may be larger
    if (!d_block_change_signals)
      Q_EMIT d_owner->dataChanged(first_row, col, last_row, col);
    return;
  }

  for (int i = first_row; i <= last_row; i++)
    d_data[col][i] = values.at(i - first_row);
  if (!d_block_change_signals)
    Q_EMIT d_owner->dataChanged(first_row, col, last_row, col);
}

QVector<qreal> MatrixViewProvider::Private::rowCells(int row, int first_column,
                                         int last_column) {
  Q_ASSERT(first_column >= 0 && first_column < d_column_count);
  Q_ASSERT(last_column >= 0 && last_column < d_column_count);

  QVector<qreal> result;
  for (int i = first_column; i <= last_column; i++)
    result.append(d_data.at(i).at(row));
  return result;
}

void MatrixViewProvider::Private::setRowCells(int row, int first_column, int last_column,
                                  const QVector<qreal> &values) {
  Q_ASSERT(first_column >= 0 && first_column < d_column_count);
  Q_ASSERT(last_column >= 0 && last_column < d_column_count);
  Q_ASSERT(values.count() > last_column - first_column);

  for (int i = first_column; i <= last_column; i++)
    d_data[i][row] = values.at(i - first_column);
  if (!d_block_change_signals)
    Q_EMIT d_owner->dataChanged(row, first_column, row, last_column);
}

void MatrixViewProvider::Private::clearColumn(int col) {
  d_data[col].fill(0.0);
  if (!d_block_change_signals)
    Q_EMIT d_owner->dataChanged(0, col, d_row_count - 1, col);
}

double MatrixViewProvider::Private::xStart() const { return d_x_start; }

double MatrixViewProvider::Private::yStart() const { return d_y_start; }

double MatrixViewProvider::Private::xEnd() const { return d_x_end; }

double MatrixViewProvider::Private::yEnd() const { return d_y_end; }

void MatrixViewProvider::Private::setXStart(double x) {
  d_x_start = x;
  Q_EMIT d_owner->coordinatesChanged();
}

void MatrixViewProvider::Private::setXEnd(double x) {
  d_x_end = x;
  Q_EMIT d_owner->coordinatesChanged();
}

void MatrixViewProvider::Private::setYStart(double y) {
  d_y_start = y;
  Q_EMIT d_owner->coordinatesChanged();
}

void MatrixViewProvider::Private::setYEnd(double y) {
  d_y_end = y;
  Q_EMIT d_owner->coordinatesChanged();
}

QString MatrixViewProvider::Private::formula() const { return d_formula; }

void MatrixViewProvider::Private::setFormula(const QString &formula) {
  d_formula = formula;
  Q_EMIT d_owner->formulaChanged();
}

}  // namespace future
