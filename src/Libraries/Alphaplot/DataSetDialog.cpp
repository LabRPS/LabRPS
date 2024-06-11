/***************************************************************************
    File                 : DataSetDialog.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Multi purpose dialog for choosing a data set

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

#include "DataSetDialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <2Dplot/AxisRect2D.h>
#include <2Dplot/Graph2DCommon.h>
#include <2Dplot/Plotcolumns.h>
#include "MainWindow.h"

using namespace Gui;

DataSetDialog::DataSetDialog(const QString& text, QWidget* parent,
                             Qt::WindowFlags fl)
    : QDialog(parent, fl), axisrect_(nullptr) {
  setWindowTitle(tr("Select data set"));

  operation = QString();

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  QHBoxLayout* bottomLayout = new QHBoxLayout();
  bottomLayout->addStretch();

  groupBox1 = new QGroupBox();
  QHBoxLayout* topLayout = new QHBoxLayout(groupBox1);

  topLayout->addWidget(new QLabel(text));
  boxName = new QComboBox();
  topLayout->addWidget(boxName);

  buttonOk = new QPushButton(tr("&OK"));
  buttonOk->setAutoDefault(true);
  buttonOk->setDefault(true);
  bottomLayout->addWidget(buttonOk);

  buttonCancel = new QPushButton(tr("&Cancel"));
  buttonCancel->setAutoDefault(true);
  bottomLayout->addWidget(buttonCancel);

  mainLayout->addWidget(groupBox1);
  mainLayout->addLayout(bottomLayout);

  connect(buttonOk, &QPushButton::clicked, this, &DataSetDialog::accept);
  connect(buttonCancel, &QPushButton::clicked, this, &DataSetDialog::reject);
}

void DataSetDialog::accept() {
  if (operation.isEmpty()) {
    Q_EMIT options(boxName->currentText());
  } else if (axisrect_) {
    
      Gui::MainWindow* app = qobject_cast<Gui::MainWindow*>(this->parent());
    //Gui::MainWindow* app = Gui::MainWindow::getInstance();

    //if (app) app->analyzeCurve(axisrect_, operation, boxName->currentText());//koffa the way
  }
  close();
}

void DataSetDialog::setCurveNames(const QStringList& names) {
  boxName->addItems(names);
}

void DataSetDialog::setCurentDataSet(const QString& set) {
  int row = boxName->findText(set);
  boxName->setCurrentIndex(row);
}

void DataSetDialog::setAxisRect(AxisRect2D* axisrect) {
  if (!axisrect) return;

  axisrect_ = axisrect;
  boxName->addItems(PlotColumns::getstringlistfromassociateddata(axisrect_));
}
