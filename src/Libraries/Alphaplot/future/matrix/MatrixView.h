/***************************************************************************
    File                 : MatrixView.h
    Project              : AlphaPlot
    Description          : View class for Matrix
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

#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSize>
#include <QSpinBox>
#include <QTabWidget>
#include <QTableView>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "MyWidget.h"
#include "globals.h"
#include <Libraries/Alphaplot/ui_matrixcontroltabs.h>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


namespace Gui{
class MatrixViewProvider;
}

class MatrixModel;

//! Helper class for MatrixView
class AlphaplotExport MatrixViewWidget : public QTableView {
  Q_OBJECT

 public:
  //! Constructor
  MatrixViewWidget(QWidget* parent = 0) : QTableView(parent) {}

 protected:
  //! Overloaded function (cf. Qt documentation)
  virtual void keyPressEvent(QKeyEvent* event);

 Q_SIGNALS:
  void advanceCell();

 public Q_SLOTS:
  void selectAll();
};

//! View class for Matrix
class AlphaplotExport MatrixView: public MyWidget
{
  Q_OBJECT

 public:
//! Constructor
#ifndef LEGACY_CODE_0_2_x
  MatrixView(Gui::MatrixViewProvider* matrix);
#else
  MatrixView(const QString& label, QWidget* parent = nullptr,
             const QString name = QString(), Qt::WindowFlags f = Qt::Widget);
  void setMatrix(Gui::MatrixViewProvider* matrix);
#endif
  //! Destructor
  virtual ~MatrixView();
  bool isControlTabBarVisible() { return d_control_tabs->isVisible(); }

  //! \name selection related functions
  //@{
  //! Return how many columns are selected
  /**
   * If full is true, this function only returns the number of fully
   * selected columns.
   */
  int selectedColumnCount(bool full = false);
  //! Returns true if column 'col' is selected; otherwise false
  /**
   * If full is true, this function only returns true if the whole
   * column is selected.
   */
  bool isColumnSelected(int col, bool full = false);
  //! Return how many rows are (at least partly) selected
  /**
   * If full is true, this function only returns the number of fully
   * selected rows.
   */
  int selectedRowCount(bool full = false);
  //! Returns true if row 'row' is selected; otherwise false
  /**
   * If full is true, this function only returns true if the whole
   * row is selected.
   */
  bool isRowSelected(int row, bool full = false);
  //! Return the index of the first selected column
  /**
   * If full is true, this function only looks for fully
   * selected columns.
   */
  int firstSelectedColumn(bool full = false);
  //! Return the index of the last selected column
  /**
   * If full is true, this function only looks for fully
   * selected columns.
   */
  int lastSelectedColumn(bool full = false);
  //! Return the index of the first selected row
  /**
   * If full is true, this function only looks for fully
   * selected rows.
   */
  int firstSelectedRow(bool full = false);
  //! Return the index of the last selected row
  /**
   * If full is true, this function only looks for fully
   * selected rows.
   */
  int lastSelectedRow(bool full = false);
  //! Return whether a cell is selected
  bool isCellSelected(int row, int col);
  //! Select a cell
  void setCellSelected(int row, int col);
  //! Select a range of cells
  void setCellsSelected(int first_row, int first_col, int last_row,
                        int last_col);
  //! Determine the current cell (-1 if no cell is designated as the current)
  void getCurrentCell(int* row, int* col);
  //@}

  void setRowHeight(int row, int height);
  void setColumnWidth(int col, int width);
  int rowHeight(int row) const;
  int columnWidth(int col) const;
  void loadIcons();

 public Q_SLOTS:
  void rereadSectionSizes();
  void goToCell(int row, int col);
  void selectAll();
  void toggleControlTabBar();
  void showControlCoordinatesTab();
  void showControlFormatTab();
  void showControlFormulaTab();
  void applyCoordinates();
  void updateCoordinatesTab();
  void updateFormulaTab();
#ifndef LEGACY_CODE_0_2_x
  void applyFormula();
#endif
  void updateFormatTab();
  void applyFormat();
  void handleHorizontalSectionResized(int logicalIndex, int oldSize,
                                      int newSize);
  void handleVerticalSectionResized(int logicalIndex, int oldSize, int newSize);

 Q_SIGNALS:
  void controlTabBarStatusChanged(bool visible);

 protected Q_SLOTS:
  //! Advance current cell after [Return] or [Enter] was pressed
  void advanceCell();
  void updateTypeInfo();

 protected:
  Ui::MatrixControlTabs ui;
  //! The matrix view (first part of the UI)
  MatrixViewWidget* d_view_widget;
  //! Widget that contains the control tabs UI from #ui
  QWidget* d_control_tabs;
  //! Button to toogle the visibility of #d_tool_box
  QToolButton* d_hide_button;
  QHBoxLayout* d_main_layout;
  QWidget* d_main_widget;
  Gui::MatrixViewProvider* d_matrix;

  //! Pointer to the current underlying model
  MatrixModel* d_model;

  virtual void changeEvent(QEvent* event);
  virtual void resizeEvent(QResizeEvent* event);
  void retranslateStrings();

  bool eventFilter(QObject* watched, QEvent* event);

  //! Initialization
  void init();

 private:
  void moveFloatingButton();
};

#endif  // MATRIXVIEW_H
