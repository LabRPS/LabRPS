/***************************************************************************
    File                 : AssociationsDialog.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Plot associations dialog

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

#include "AssociationsDialog.h"
#include <2Dplot/AxisRect2D.h>
#include <Table.h>

#include <QApplication>
#include <QCheckBox>
#include <QEvent>
#include <QHeaderView>
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>

AssociationsDialog::AssociationsDialog(QWidget *parent, Qt::WindowFlags fl)
    : QDialog(parent, fl), axisrect_(nullptr) {
  setWindowTitle(tr("Plot Associations"));
  setSizeGripEnabled(true);
  setFocus();

  QVBoxLayout *vl = new QVBoxLayout();

  QHBoxLayout *hbox1 = new QHBoxLayout();
  hbox1->addWidget(new QLabel(tr("Spreadsheet: ")));

  tableCaptionLabel = new QLabel();
  hbox1->addWidget(tableCaptionLabel);
  vl->addLayout(hbox1);

  table = new QTableWidget(3, 5);
  table->horizontalHeader()->setSelectionMode(
      QAbstractItemView::SingleSelection);
  table->verticalHeader()->hide();
  table->setMaximumHeight(8 * table->rowHeight(0));
  table->setHorizontalHeaderLabels(QStringList()
                                   << tr("Column") << tr("X") << tr("Y")
                                   << tr("xErr") << tr("yErr"));
  vl->addWidget(table);

  associations = new QListWidget();
  associations->setSelectionMode(QListWidget::SingleSelection);
  vl->addWidget(associations);

  btnApply = new QPushButton(tr("&Update curves"));
  btnOK = new QPushButton(tr("&OK"));
  btnOK->setDefault(true);
  btnCancel = new QPushButton(tr("&Cancel"));

  QHBoxLayout *hbox2 = new QHBoxLayout();
  hbox2->addStretch();
  hbox2->addWidget(btnApply);
  hbox2->addWidget(btnOK);
  hbox2->addWidget(btnCancel);
  vl->addStretch();
  vl->addLayout(hbox2);
  setLayout(vl);

  active_table = 0;

  connect(associations, SIGNAL(currentRowChanged(int)), this,
          SLOT(updateTable(int)));
  connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
  connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
  connect(btnApply, SIGNAL(clicked()), this, SLOT(updateCurves()));
}

void AssociationsDialog::accept() {
  updateCurves();
  close();
}

void AssociationsDialog::updateCurves() {
  /* if (!graph) return;

   QApplication::setOverrideCursor(Qt::WaitCursor);

   for (int i = 0; i < associations->count(); i++)
     changePlotAssociation(i, plotAssociation(associations->item(i)->text()));
   graph->updatePlot();

   QApplication::restoreOverrideCursor();*/
}

void AssociationsDialog::changePlotAssociation(int curve, const QString &text) {
  /* DataCurve *c = (DataCurve *)graph->curve(curve);  // c_keys[curve]);
   if (!c) return;

   if (c->plotAssociation() == text) return;

   QStringList lst = text.split(",", QString::SkipEmptyParts);
   if (lst.count() == 2) {
     c->setXColumnName(lst[0].remove("(X)"));
     c->setTitle(lst[1].remove("(Y)"));
     c->loadData();
   } else if (lst.count() == 3) {  // curve with error bars
     QwtErrorPlotCurve *er = (QwtErrorPlotCurve *)c;
     QString xColName = lst[0].remove("(X)");
     QString yColName = lst[1].remove("(Y)");
     QString erColName = lst[2].remove("(xErr)").remove("(yErr)");
     DataCurve *master_curve = graph->masterCurve(xColName, yColName);
     if (!master_curve) return;
   } else if (lst.count() == 4) {
   }
   graph->notifyChanges();*/
}

QString AssociationsDialog::plotAssociation(const QString &text) {
  QString s = text;
  QStringList lst = s.split(QString::fromLatin1(": "), QString::SkipEmptyParts);
  QStringList cols = lst[1].split(QString::fromLatin1(","), QString::SkipEmptyParts);

  QString tableName = lst[0];
  s = tableName + QString::fromLatin1("_") + cols[0];
  for (int i = 1; i < (int)cols.count(); i++)
    s += QString::fromLatin1(",") + tableName + QString::fromLatin1("_") + cols[i];
  return s;
}

void AssociationsDialog::initTablesList(QList<QMdiSubWindow *> *lst,
                                        int curve) {
  tables = lst;
  active_table = nullptr;

  if (curve < 0 || curve >= (int)associations->count()) curve = 0;

  associations->setCurrentRow(curve);
}

Table *AssociationsDialog::findTable(int index) {
  QString text = associations->item(index)->text();
  QStringList lst = text.split(QString::fromLatin1(":"), QString::SkipEmptyParts);
  for (int i = 0; i < (int)tables->count(); i++) {
    if (tables->at(i)->objectName() == lst[0]) return (Table *)tables->at(i);
  }
  return 0;
}

void AssociationsDialog::updateTable(int index) {
  Table *t = findTable(index);
  if (!t) return;

  if (active_table != t) {
    active_table = t;
    tableCaptionLabel->setText(t->name());
    table->clearContents();
    table->setRowCount(t->numCols());

    QStringList colNames = t->colNames();
    for (int i = 0; i < table->rowCount(); i++) {
      QTableWidgetItem *cell = new QTableWidgetItem(colNames[i]);
      cell->setBackground(QBrush(Qt::lightGray));
      cell->setFlags(Qt::ItemIsEnabled);
      table->setItem(i, 0, cell);
    }

    for (int j = 1; j < table->columnCount(); j++) {
      for (int i = 0; i < table->rowCount(); i++) {
        QTableWidgetItem *cell = new QTableWidgetItem();
        cell->setBackground(QBrush(Qt::lightGray));
        table->setItem(i, j, cell);

        QCheckBox *cb = new QCheckBox(table);
        cb->installEventFilter(this);
        table->setCellWidget(i, j, cb);
      }
    }
  }
  updateColumnTypes();
}

void AssociationsDialog::updateColumnTypes() {
  QString text = associations->currentItem()->text();
  QStringList lst = text.split(QString::fromLatin1(": "), QString::SkipEmptyParts);
  QStringList cols = lst[1].split(QString::fromLatin1(","), QString::SkipEmptyParts);

  QString xColName = cols[0].remove(QString::fromLatin1("(X)"));
  QString yColName = cols[1].remove(QString::fromLatin1("(Y)"));

  int n = (int)cols.count();
  if (n == 2) {
    table->hideColumn(3);
    table->hideColumn(4);
  }

  QCheckBox *it = 0;
  for (int i = 0; i < table->rowCount(); i++) {
    it = (QCheckBox *)table->cellWidget(i, 1);
    if (table->item(i, 0)->text() == xColName)
      it->setChecked(true);
    else
      it->setChecked(false);

    it = (QCheckBox *)table->cellWidget(i, 2);
    if (table->item(i, 0)->text() == yColName)
      it->setChecked(true);
    else
      it->setChecked(false);
  }

  bool xerr = false, yerr = false, vectors = false;
  QString errColName, xEndColName, yEndColName;
  if (n > 2) {
    table->showColumn(3);
    table->showColumn(4);

    if (cols[2].contains(QString::fromLatin1("(xErr)")) ||
        cols[2].contains(QString::fromLatin1("(yErr)"))) {  // if error bars
      table->horizontalHeaderItem(3)->setText(tr("xErr"));
      table->horizontalHeaderItem(4)->setText(tr("yErr"));
    }

    if (cols[2].contains(QString::fromLatin1("(xErr)"))) {
      xerr = true;
      errColName = cols[2].remove(QString::fromLatin1("(xErr)"));
    } else if (cols[2].contains(QString::fromLatin1("(yErr)"))) {
      yerr = true;
      errColName = cols[2].remove(QString::fromLatin1("(yErr)"));
    } else if (cols.count() > 3 && cols[2].contains(QString::fromLatin1("(X)")) &&
               cols[3].contains(QString::fromLatin1("(Y)"))) {
      vectors = true;
      xEndColName = cols[2].remove(QString::fromLatin1("(X)"));
      yEndColName = cols[3].remove(QString::fromLatin1("(Y)"));
      table->horizontalHeaderItem(3)->setText(tr("xEnd"));
      table->horizontalHeaderItem(4)->setText(tr("yEnd"));
    } else if (cols.count() > 3 && cols[2].contains(QString::fromLatin1("(A)")) &&
               cols[3].contains(QString::fromLatin1("(M)"))) {
      vectors = true;
      xEndColName = cols[2].remove(QString::fromLatin1("(A)"));
      yEndColName = cols[3].remove(QString::fromLatin1("(M)"));
      table->horizontalHeaderItem(3)->setText(tr("Angle"));
      table->horizontalHeaderItem(4)->setText(
          tr("Magn.", "Magnitude, vector length"));
    }
  }

  for (int i = 0; i < table->rowCount(); i++) {
    it = (QCheckBox *)table->cellWidget(i, 3);
    if (xerr || vectors) {
      if (table->item(i, 0)->text() == errColName ||
          table->item(i, 0)->text() == xEndColName)
        it->setChecked(true);
      else
        it->setChecked(false);
    } else
      it->setChecked(false);

    it = (QCheckBox *)table->cellWidget(i, 4);
    if (yerr || vectors) {
      if (table->item(i, 0)->text() == errColName ||
          table->item(i, 0)->text() == yEndColName)
        it->setChecked(true);
      else
        it->setChecked(false);
    } else
      it->setChecked(false);
  }
}

void AssociationsDialog::uncheckCol(int col) {
  for (int i = 0; i < table->rowCount(); i++) {
    QCheckBox *it = (QCheckBox *)table->cellWidget(i, col);
    if (it) it->setChecked(false);
  }
}

void AssociationsDialog::setAxisRect(AxisRect2D *axisrect) {
  /*  graph = g;

    for (int i = 0; i < graph->curves(); i++) {
      const QwtPlotItem *it = (QwtPlotItem *)graph->plotItem(i);
      if (!it) continue;
      if (it->rtti() != QwtPlotItem::Rtti_PlotCurve) continue;

      if (((DataCurve *)it)->type() != Graph::Function) {
        QString s = ((DataCurve *)it)->plotAssociation();
        QString table = ((DataCurve *)it)->table()->name();
        plotAssociationsList << table + ": " + s.remove(table + "_");
      }
    }
    associations->addItems(plotAssociationsList);
    associations->setMaximumHeight(
        (plotAssociationsList.count() + 1) *
        associations->visualItemRect(associations->item(0)).height());*/
}

void AssociationsDialog::updatePlotAssociation(int row, int col) {
  int index = associations->currentRow();
  QString text = associations->currentItem()->text();
  QStringList lst = text.split(QString::fromLatin1(": "), QString::SkipEmptyParts);
  QStringList cols = lst[1].split(QString::fromLatin1(","), QString::SkipEmptyParts);

  if (col == 1) {
    cols[0] = table->item(row, 0)->text() + QString::fromLatin1("(X)");
    text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
  } else if (col == 2) {
    cols[1] = table->item(row, 0)->text() + QString::fromLatin1("(Y)");
    text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
  } else if (col == 3) {
    if (text.contains(QString::fromLatin1("(A)"))) {  // vect XYAM curve
      cols[2] = table->item(row, 0)->text() + QString::fromLatin1("(A)");
      text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
    } else if (!text.contains(QString::fromLatin1("(A)")) && text.count(QString::fromLatin1("(X)")) == 1) {
      cols[2] = table->item(row, 0)->text() + QString::fromLatin1("(xErr)");
      text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
      uncheckCol(4);
    } else if (text.count(QString::fromLatin1("(X)")) == 2) {  // vect XYXY curve
      cols[2] = table->item(row, 0)->text() + QString::fromLatin1("(X)");
      text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
    }
  } else if (col == 4) {
      if (text.contains(QString::fromLatin1("(M)"))) {// vect XYAM curve
      cols[3] = table->item(row, 0)->text() + QString::fromLatin1("(M)");
      text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
      } else if (!text.contains(QString::fromLatin1("(M)")) && text.count(QString::fromLatin1("(X)")) == 1) {
      cols[2] = table->item(row, 0)->text() + QString::fromLatin1("(yErr)");
      text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
      uncheckCol(3);
    } else if (text.count(QString::fromLatin1("(Y)")) == 2) {  // vect XYXY curve
      cols[3] = table->item(row, 0)->text() + QString::fromLatin1("(Y)");
      text = lst[0] + QString::fromLatin1(": ") + cols.join(QString::fromLatin1(","));
    }
  }

  // change associations for error bars depending on the curve "index"
  QString old_as = plotAssociationsList[index];
  for (int i = 0; i < (int)plotAssociationsList.count(); i++) {
    QString as = plotAssociationsList[i];
    if (as.contains(old_as) &&
        (as.contains(QString::fromLatin1("(xErr)")) || as.contains(QString::fromLatin1("(yErr)")))) {
      QStringList ls = as.split(QString::fromLatin1(","), QString::SkipEmptyParts);
      as = text + QString::fromLatin1(",") + ls[2];
      plotAssociationsList[i] = as;
    }
  }

  plotAssociationsList[index] = text;
  associations->item(index)->setText(text);
}

bool AssociationsDialog::eventFilter(QObject *object, QEvent *e) {
  QTableWidgetItem *it = (QTableWidgetItem *)object;
  if (!it) return false;

  if (e->type() == QEvent::MouseButtonPress) {
    if (((QCheckBox *)it)->isChecked()) return true;

    int col = 0, row = 0;
    for (int j = 1; j < table->columnCount(); j++) {
      for (int i = 0; i < table->rowCount(); i++) {
        QCheckBox *cb = (QCheckBox *)table->cellWidget(i, j);
        if (cb == (QCheckBox *)object) {
          row = i;
          col = j;
          break;
        }
      }
    }

    uncheckCol(col);
    ((QCheckBox *)it)->setChecked(true);

    updatePlotAssociation(row, col);
    return true;
  } else if (e->type() == QEvent::MouseButtonDblClick)
    return true;
  else
    return false;
}

AssociationsDialog::~AssociationsDialog() { delete tables; }
