/***************************************************************************
    File                 : InterpolationDialog.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Interpolation options dialog

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
#include "PreCompiled.h"

#include "InterpolationDialog.h"

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>

#include <2Dplot/AxisRect2D.h>
#include <2Dplot/PickerTool2D.h>
#include <2Dplot/Plotcolumns.h>
#include <2Dplot/Graph2DCommon.h>

#include "ColorBox.h"
#include "Interpolation.h"
#include "MainWindow.h"

InterpolationDialog::InterpolationDialog(QWidget *parent, Qt::WindowFlags fl)
    : QDialog(parent, fl),
      axisrect_(nullptr),
      app_(qobject_cast<Gui::MainWindow *>(parent)) {
  Q_ASSERT(app_);
  setWindowTitle(tr("Interpolation Options"));

  QGroupBox *gb1 = new QGroupBox();
  QGridLayout *gl1 = new QGridLayout(gb1);
  gl1->addWidget(new QLabel(tr("Make curve from")), 0, 0);

  boxName = new QComboBox();
  gl1->addWidget(boxName, 0, 1);

  gl1->addWidget(new QLabel(tr("Spline")), 1, 0);
  boxMethod = new QComboBox();
  boxMethod->addItem(tr("Linear"));
  boxMethod->addItem(tr("Polynomial"));
  boxMethod->addItem(tr("Cubic"));
  boxMethod->addItem(tr("Cubic Periodic"));
  boxMethod->addItem(tr("Non-rounded Akima"));
  boxMethod->addItem(tr("Non-rounded Akima Periodic"));
  boxMethod->addItem(tr("Steffen"));
  gl1->addWidget(boxMethod, 1, 1);

  gl1->addWidget(new QLabel(tr("Points")), 2, 0);
  boxPoints = new QSpinBox();
  boxPoints->setRange(3, 100000);
  boxPoints->setSingleStep(10);
  boxPoints->setValue(1000);
  gl1->addWidget(boxPoints, 2, 1);

  gl1->addWidget(new QLabel(tr("From Xmin")), 3, 0);
  boxStart = new QLineEdit();
  boxStart->setText(tr("0"));
  gl1->addWidget(boxStart, 3, 1);

  gl1->addWidget(new QLabel(tr("To Xmax")), 4, 0);
  boxEnd = new QLineEdit();
  gl1->addWidget(boxEnd, 4, 1);

  gl1->addWidget(new QLabel(tr("Color")), 5, 0);

  boxColor = new ColorBox();
  boxColor->setColor(QColor(Qt::red));
  gl1->addWidget(boxColor, 5, 1);
  gl1->setRowStretch(6, 1);

  buttonFit = new QPushButton(tr("&Make"));
  buttonFit->setDefault(true);
  buttonCancel = new QPushButton(tr("&Close"));

  QVBoxLayout *vl = new QVBoxLayout();
  vl->addWidget(buttonFit);
  vl->addWidget(buttonCancel);
  vl->addStretch();

  QHBoxLayout *hb = new QHBoxLayout(this);
  hb->addWidget(gb1);
  hb->addLayout(vl);

  connect(boxName, SIGNAL(activated(const QString &)), this,
          SLOT(activateCurve(const QString &)));
  connect(buttonFit, SIGNAL(clicked()), this, SLOT(interpolate()));
  connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void InterpolationDialog::interpolate() {
  if (!axisrect_) return;
  QString curve = boxName->currentText();
  QStringList curvesList =
      PlotColumns::getstringlistfromassociateddata(axisrect_);
  if (!curvesList.contains(curve)) {
    QMessageBox::critical(
        this, tr("Warning"),
        tr("The curve <b> %1 </b> doesn't exist anymore! Operation aborted!")
            .arg(curve));
    boxName->clear();
    boxName->addItems(curvesList);
    return;
  }
  PlotData::AssociatedData *associateddata =
      PlotColumns::getassociateddatafromstring(axisrect_,
                                               boxName->currentText());

  double from, to;
  /*try {
    MyParser parser;
    parser.SetExpr(boxStart->text().replace(QString::fromLatin1(","), QString::fromLatin1(".")).toUtf8().constData());
    from = parser.Eval();
  } catch (mu::ParserError &e) {
    QMessageBox::critical(this, tr("Start limit error"),
                          QString::fromStdString(e.GetMsg()));
    boxStart->setFocus();
    return;
  }*/

  /*try {
    MyParser parser;
    parser.SetExpr(boxEnd->text().replace(QString::fromLatin1(","), QString::fromLatin1(".")).toUtf8().constData());
    to = parser.Eval();
  } catch (mu::ParserError &e) {
    QMessageBox::critical(this, tr("End limit error"),
                          QString::fromStdString(e.GetMsg()));
    boxEnd->setFocus();
    return;
  }*/

  if (from >= to) {
    QMessageBox::critical(this, tr("Input error"),
                          tr("Please enter x limits that satisfy: from < to!"));
    boxEnd->setFocus();
    return;
  }

  Interpolation *i =
      new Interpolation(app_, axisrect_, associateddata, from, to,
                        static_cast<Interpolation::InterpolationMethod>(
                            boxMethod->currentIndex()));
  i->setOutputPoints(boxPoints->value());
  i->setColor(boxColor->currentIndex());
  i->run();
  delete i;
}

void InterpolationDialog::setAxisRect(AxisRect2D *axisrect) {
  if (!axisrect) return;
  axisrect_ = axisrect;
  boxName->addItems(PlotColumns::getstringlistfromassociateddata(axisrect_));
  PickerTool2D *picker = axisrect_->getPickerTool();
  if (picker) {
    if (picker->getPicker() == Graph2DCommon::Picker::DataRange) {
      Curve2D *curve = picker->getRangePickerCurve();
      if (curve) {
        QString cname = PlotColumns::getstringfromassociateddata(
            curve->getdatablock_cplot()->getassociateddata());
        boxName->setCurrentText(cname);
      }
    }
  }
  activateCurve(boxName->currentText());
}

void InterpolationDialog::activateCurve(const QString &curveName) {
 /* if (!axisrect_) return;
  double start = 0;
  double end = 0;
  PlotData::AssociatedData *associateddata;
  associateddata =
      PlotColumns::getassociateddatafromstring(axisrect_, curveName);
  if (!associateddata) return;
  xmin_ = associateddata->minmax.minx;
  xmax_ = associateddata->minmax.maxx;

  PickerTool2D *picker = axisrect_->getPickerTool();
  if (!picker) {
    qDebug() << "unable to get picker handle";
    return;
  }

  bool setminmaxasstartend = true;
  if (picker->getPicker() == Graph2DCommon::Picker::DataRange) {
    Curve2D *curve = picker->getRangePickerCurve();
    if (curve) {
      QString cname = PlotColumns::getstringfromassociateddata(
          curve->getdatablock_cplot()->getassociateddata());
      if (cname == curveName) {
        start = picker->getRangePickerLower().first;
        end = picker->getRangePickerUpper().first;
        setminmaxasstartend = false;
      }
    }
  }

  if (setminmaxasstartend) {
    start = xmin_;
    end = xmax_;
  }

  boxStart->setText(QString::number(start, 'g', app_->d_decimal_digits));
  boxEnd->setText(QString::number(end, 'g', app_->d_decimal_digits));*///koffa the way
}

void InterpolationDialog::changeDataRange() {
  //double start = xmin_;
  //double end = xmax_;
  //boxStart->setText(
  //    QString::number(std::min(start, end), 'g', app_->d_decimal_digits));
  //boxEnd->setText(
  //    QString::number(std::max(start, end), 'g', app_->d_decimal_digits));//koffa the way
}
