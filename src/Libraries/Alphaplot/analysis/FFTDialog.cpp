/***************************************************************************
    File                 : FFTDialog.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Fast Fourier transform options dialog

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

#include "FFTDialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>

#include <2Dplot/Plotcolumns.h>
#include "MainWindow.h"
#include "FFT.h"
#include <Table.h>

FFTDialog::FFTDialog(int type, QWidget *parent, Qt::WindowFlags flag)
    : QDialog(parent, flag),
      axisrect_(nullptr),
      d_table(nullptr),
      d_type(type) {
  setWindowTitle(tr("FFT Options"));

  forwardBtn = new QRadioButton(tr("&Forward"));
  forwardBtn->setChecked(true);
  backwardBtn = new QRadioButton(tr("&Inverse"));

  QHBoxLayout *hbox1 = new QHBoxLayout();
  hbox1->addWidget(forwardBtn);
  hbox1->addWidget(backwardBtn);

  QGroupBox *gb1 = new QGroupBox();
  gb1->setLayout(hbox1);

  QGridLayout *gl1 = new QGridLayout();
  if (d_type == onGraph)
    gl1->addWidget(new QLabel(tr("Curve")), 0, 0);
  else
    gl1->addWidget(new QLabel(tr("Sampling")), 0, 0);

  boxName = new QComboBox();
  gl1->addWidget(boxName, 0, 1);

  boxSampling = new QLineEdit();
  if (d_type == onTable) {
    gl1->addWidget(new QLabel(tr("Real")), 1, 0);
    boxReal = new QComboBox();
    gl1->addWidget(boxReal, 1, 1);

    gl1->addWidget(new QLabel(tr("Imaginary")), 2, 0);
    boxImaginary = new QComboBox();
    gl1->addWidget(boxImaginary, 2, 1);

    gl1->addWidget(new QLabel(tr("Sampling Interval")), 3, 0);
    gl1->addWidget(boxSampling, 3, 1);
  } else {
    gl1->addWidget(new QLabel(tr("Sampling Interval")), 1, 0);
    gl1->addWidget(boxSampling, 1, 1);
  }
  QGroupBox *gb2 = new QGroupBox();
  gb2->setLayout(gl1);

  boxNormalize = new QCheckBox(tr("&Normalize Amplitude"));
  boxNormalize->setChecked(true);

  boxOrder = new QCheckBox(tr("&Shift Results"));
  boxOrder->setChecked(true);

  QVBoxLayout *vbox1 = new QVBoxLayout();
  vbox1->addWidget(gb1);
  vbox1->addWidget(gb2);
  vbox1->addWidget(boxNormalize);
  vbox1->addWidget(boxOrder);
  vbox1->addStretch();

  buttonOK = new QPushButton(tr("&OK"));
  buttonOK->setDefault(true);
  buttonCancel = new QPushButton(tr("&Close"));

  QVBoxLayout *vbox2 = new QVBoxLayout();
  vbox2->addWidget(buttonOK);
  vbox2->addWidget(buttonCancel);
  vbox2->addStretch();

  QHBoxLayout *hbox2 = new QHBoxLayout(this);
  hbox2->addLayout(vbox1);
  hbox2->addLayout(vbox2);

  setFocusProxy(boxName);

  // signals and slots connections
  connect(boxName, &QComboBox::textActivated, this, &FFTDialog::activateCurve);
  connect(buttonOK, &QPushButton::clicked, this, &FFTDialog::accept);
  connect(buttonCancel, &QPushButton::clicked, this, &FFTDialog::reject);
}

void FFTDialog::accept() {
  double sampling;
  /*try {
    MyParser parser;
    parser.SetExpr(boxSampling->text().toUtf8().constData());
    sampling = parser.Eval();
  } catch (mu::ParserError &e) {
    QMessageBox::critical(this, tr("Sampling value error"),
                          QString::fromStdString(e.GetMsg()));
    boxSampling->setFocus();
    return;
  }*/

  Gui::MainWindow *app = qobject_cast<Gui::MainWindow *>(parent());
  if (!app) return;
  FFT *fft = nullptr;
  if (axisrect_) {
    PlotColumns::plottedcolumns(axisrect_);
    fft = new FFT(app, axisrect_,
                  PlotColumns::getassociateddatafromstring(
                      axisrect_, boxName->currentText()));
  } else if (d_table) {
    if (boxReal->currentText().isEmpty()) {
      QMessageBox::critical(
          this, tr("Error"),
          tr("Please choose a column for the real part of the data!"));
      boxReal->setFocus();
      return;
    }
    fft = new FFT(app, d_table, boxReal->currentText(),
                  boxImaginary->currentText());
  }
  if (!fft) return;
  fft->setInverseFFT(backwardBtn->isChecked());
  fft->setSampling(sampling);
  fft->normalizeAmplitudes(boxNormalize->isChecked());
  fft->shiftFrequencies(boxOrder->isChecked());
  fft->run();
  delete fft;
  close();
}

void FFTDialog::setAxisrect(AxisRect2D *axisrect) {
  axisrect_ = axisrect;
  boxName->addItems(PlotColumns::getstringlistfromassociateddata(axisrect_));
  activateCurve(boxName->currentText());
}

void FFTDialog::activateCurve(const QString &curveName) {
  if (axisrect_) {
    PlotData::AssociatedData *associateddata;
    associateddata =
        PlotColumns::getassociateddatafromstring(axisrect_, curveName);
    if (!associateddata) return;

    boxSampling->setText(QString::number(
        associateddata->xcol->valueAt(associateddata->from + 1) -
        associateddata->xcol->valueAt(associateddata->from)));
  } else if (d_table) {
    int col = d_table->colIndex(curveName);
    double x0 = d_table->text(0, col).toDouble();
    double x1 = d_table->text(1, col).toDouble();
    boxSampling->setText(QString::number(x1 - x0));
  }
}

void FFTDialog::setTable(Table *table) {
  d_table = table;
  QStringList l = table->columnsList();
  boxName->addItems(l);
  boxReal->addItems(l);
  boxImaginary->addItems(l);

  int xcol = table->firstXCol();
  if (xcol >= 0) {
    boxName->setCurrentIndex(xcol);

    double x0 = table->text(0, xcol).toDouble();
    double x1 = table->text(1, xcol).toDouble();
    boxSampling->setText(QString::number(x1 - x0));
  }

  l = table->selectedColumns();
  int selected = l.size();
  if (!selected) {
    boxReal->setItemText(boxReal->currentIndex(), QString());
    boxImaginary->setItemText(boxImaginary->currentIndex(), QString());
  } else if (selected == 1) {
    boxReal->setCurrentIndex(table->colIndex(l.at(0)));
    boxImaginary->setItemText(boxImaginary->currentIndex(), QString());
  } else {
    boxReal->setCurrentIndex(table->colIndex(l.at(0)));
    boxImaginary->setCurrentIndex(table->colIndex(l.at(1)));
  }
}
