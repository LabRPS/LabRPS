/***************************************************************************
    File                 : Correlation.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2007 by Ion Vasilief
    Email (use @ for *)  : ion_vasilief*yahoo.fr
    Description          : Numerical correlation of data sets

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

#include "Correlation.h"
#include "MainWindow.h"
#include <gsl/gsl_fft_halfcomplex.h>

#include <QLocale>
#include <QMessageBox>
#include <vector>

#include <future/core/column/Column.h>
#include <analysis/Filter.h>
#include <Table.h>

Correlation::Correlation(Gui::MainWindow *parent, Table *t,
                         const QString &colName1, const QString &colName2)
    : Filter(parent, t) {
  setObjectName(tr("Correlation"));
  setDataFromTable(t, colName1, colName2);
}

void Correlation::setDataFromTable(Table *t, const QString &colName1,
                                   const QString &colName2) {
  if (!t) {
    d_init_err = true;
    return;
  }
  if (t && d_table != t) d_table = t;

  int col1 = d_table->colIndex(colName1);
  int col2 = d_table->colIndex(colName2);

  if (col1 < 0) {
    QMessageBox::warning(qobject_cast<Gui::MainWindow *>(parent()),
                         tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Error"),
                         tr("The data set %1 does not exist!").arg(colName1));
    d_init_err = true;
    return;
  } else if (col2 < 0) {
    QMessageBox::warning(qobject_cast<Gui::MainWindow *>(parent()),
                         tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Error"),
                         tr("The data set %1 does not exist!").arg(colName2));
    d_init_err = true;
    return;
  } else if (d_table->columnType(col1) != AlphaPlot::ColumnMode::Numeric ||
             d_table->columnType(col2) != AlphaPlot::ColumnMode::Numeric) {
    QString description;
    (col1 == col2)
        ? description = tr("The data set %1 should be of column type numeric!")
                            .arg(colName1)
        : description =
              tr("The data set %1 and %2 should be of column type numeric!")
                  .arg(colName1, colName2);
    QMessageBox::warning(qobject_cast<Gui::MainWindow *>(parent()),
                         tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Error"), description);
    d_init_err = true;
    return;
  }

  if (d_n > 0) {  // delete previousely allocated memory
    delete[] d_x;
    delete[] d_y;
  }

  int rows = d_table->numRows();
  d_n = 16;  // tmp number of points
  while (d_n < rows) d_n *= 2;

  d_x = new double[d_n];
  d_y = new double[d_n];

  if (d_y && d_x) {
    memset(d_x, 0, d_n * sizeof(double));  // zero-pad the two arrays...
    memset(d_y, 0, d_n * sizeof(double));
    for (int i = 0; i < rows; i++) {
      d_x[i] = d_table->cell(i, col1);
      d_y[i] = d_table->cell(i, col2);
    }
  } else {
    QMessageBox::critical(qobject_cast<Gui::MainWindow *>(parent()),
                          tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Error"),
                          tr("Could not allocate memory, operation aborted!"));
    d_init_err = true;
    d_n = 0;
  }
}

void Correlation::output() {
  // calculate the FFTs of the two functions
  if (gsl_fft_real_radix2_transform(d_x, 1, d_n) == 0 &&
      gsl_fft_real_radix2_transform(d_y, 1, d_n) == 0) {
    // multiply the FFT by its complex conjugate
    for (int i = 0; i < d_n / 2; i++) {
      if (i == 0 || i == (d_n / 2) - 1)
        d_x[i] *= d_x[i];
      else {
        int ni = d_n - i;
        double dReal = d_x[i] * d_y[i] + d_x[ni] * d_y[ni];
        double dImag = d_x[i] * d_y[ni] - d_x[ni] * d_y[i];
        d_x[i] = dReal;
        d_x[ni] = dImag;
      }
    }
  } else {
    QMessageBox::warning(qobject_cast<Gui::MainWindow *>(parent()),
                         tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Error"),
                         tr("Error in GSL forward FFT operation!"));
    return;
  }

  gsl_fft_halfcomplex_radix2_inverse(d_x, 1, d_n);  // inverse FFT

  addResultCurve();
}

void Correlation::addResultCurve() {
  Gui::MainWindow *app = qobject_cast<Gui::MainWindow *>(parent());
  if (!app) return;

  int rows = d_table->numRows();
  int cols = d_table->numCols();
  int cols2 = cols + 1;
  d_table->addCol();
  d_table->addCol();
  int n = rows / 2;

  std::vector<double> x_temp(rows), y_temp(rows);
  for (int i = 0; i < rows; i++) {
    x_temp[i] = i - n;

    if (i < n)
      y_temp[i] = d_x[d_n - n + i];
    else
      y_temp[i] = d_x[i - n];

    d_table->column(cols)->setValueAt(i, x_temp[i]);
    d_table->column(cols2)->setValueAt(i, y_temp[i]);
  }

  QStringList l = d_table->colNames().filter(tr("Lag"));
  QString id = QString::number((int)l.size() + 1);
  QString label = objectName() + id;

  d_table->setColName(cols, tr("Lag") + id);
  d_table->setColName(cols2, label);
  d_table->setColPlotDesignation(cols, AlphaPlot::X);
  //app->newCurve2D(d_table, d_table->column(cols), d_table->column(cols2));//koffa the way
}
