/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "RPSVonKarmanDialog.h"
#include <QDebug>
#include <QSettings>
#include <cmath>

#include "IconLoader.h"
#include "ui_RPSVonKarmanDialog.h"

using namespace WindLab;


RPSVonKarmanDialog::RPSVonKarmanDialog(double constant1, double constant2, double constant3, double integralLength, double standardDeviation, int option, QWidget *parent)
    : QDialog(parent), ui_(new Ui_RPSVonKarmanDialog) {
  ui_->setupUi(this);
  IconLoader::init();
  IconLoader::lumen_ = 101;
  setWindowIcon(IconLoader::load("edit-random-dist", IconLoader::LightDark));
  ui_->formulaLabel->setAlignment(Qt::AlignCenter);
  setModal(true);

  // Theaming based pixmap loading
  (IconLoader::lumen_ < 100)
      ? formulaPath = QString(":icons/dark/equations/")
      : formulaPath = QString(":icons/light/equations/");

  // Set layout margins
  ui_->gridLayout->setContentsMargins(0, 0, 0, 0);

  // set parameter bounds (move to switch case for more control)
  ui_->SpinBoxContant1->setMinimum(-INFINITY);
  ui_->SpinBoxContant1->setMaximum(std::numeric_limits<double>::max());
  ui_->SpinBoxContant2->setMinimum(-INFINITY);
  ui_->SpinBoxContant2->setMaximum(std::numeric_limits<double>::max());
  ui_->SpinBoxContant3->setMinimum(-INFINITY);
  ui_->SpinBoxContant3->setMaximum(std::numeric_limits<double>::max());
  ui_->SpinBoxStandarDeviation->setMinimum(-INFINITY);
  ui_->SpinBoxStandarDeviation->setMaximum(std::numeric_limits<double>::max());
  ui_->SpinBoxIntegralLength->setMinimum(-INFINITY);
  ui_->SpinBoxIntegralLength->setMaximum(std::numeric_limits<double>::max());

  ui_->SpinBoxContant1->setValue(constant1);
  ui_->SpinBoxContant2->setValue(constant2);
  ui_->SpinBoxContant3->setValue(constant3);
  ui_->SpinBoxStandarDeviation->setValue(integralLength);
  ui_->SpinBoxIntegralLength->setValue(standardDeviation);

  switch (option) {
    case 1:

      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "AlongWindVonKarmanPSD.png"));
      ui_->parameter1Label->setText(QString::fromUtf8("C<sub>1</sub> = "));
      ui_->parameter2Label->setText(QString::fromUtf8("C<sub>2</sub> = "));
      ui_->parameter4Label->setText(QString::fromUtf8("σ<sub>u</sub> = "));
      ui_->parameter5Label->setText(QString::fromUtf8("L<sub>u</sub> = "));

      ui_->parameter3Label->hide();
      ui_->SpinBoxContant3->hide();

      break;
  case 2:
      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "AcrossWindVonKarmanPSD.png"));
      ui_->parameter1Label->setText(QString::fromUtf8("C<sub>1</sub> = "));
      ui_->parameter2Label->setText(QString::fromUtf8("C<sub>2</sub> = "));
      ui_->parameter3Label->setText(QString::fromUtf8("C<sub>3</sub> = "));
      ui_->parameter4Label->setText(QString::fromUtf8("σ<sub>v</sub> = "));
      ui_->parameter5Label->setText(QString::fromUtf8("L<sub>v</sub> = "));

    break;
  case 3:
      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "VerticalWindVonKarmanPSD.png"));
      ui_->parameter1Label->setText(QString::fromUtf8("C<sub>1</sub> = "));
      ui_->parameter2Label->setText(QString::fromUtf8("C<sub>2</sub> = "));
      ui_->parameter3Label->setText(QString::fromUtf8("C<sub>3</sub> = "));
      ui_->parameter4Label->setText(QString::fromUtf8("σ<sub>w</sub> = "));
      ui_->parameter5Label->setText(QString::fromUtf8("L<sub>w</sub> = "));

    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  }


  // Slot connections
  connect(ui_->RPSButonButtonBox, &QDialogButtonBox::accepted, this,
          &RPSVonKarmanDialog::ok);
  connect(ui_->RPSButonButtonBox, &QDialogButtonBox::rejected, this,
          &RPSVonKarmanDialog::cancel);
}

RPSVonKarmanDialog::~RPSVonKarmanDialog() { delete ui_; }

void RPSVonKarmanDialog::ok() {
m_constant1 = ui_->SpinBoxContant1->value();
m_constant2 = ui_->SpinBoxContant2->value();
m_constant3 = ui_->SpinBoxContant3->value();
m_standardDeviation = ui_->SpinBoxStandarDeviation->value();
m_integralLength = ui_->SpinBoxIntegralLength->value();

  QDialog::accept();
}

void RPSVonKarmanDialog::cancel() { QDialog::reject(); }
