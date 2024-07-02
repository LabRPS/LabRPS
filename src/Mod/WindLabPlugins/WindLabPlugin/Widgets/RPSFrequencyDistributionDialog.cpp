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

#include "RPSFrequencyDistributionDialog.h"

#include <QDebug>
#include <QSettings>
#include <cmath>
#include "IconLoader.h"
#include "ui_RPSFrequencyDistributionDialog.h"

using namespace WindLab;

RPSFrequencyDistributionDialog::RPSFrequencyDistributionDialog(int option, QWidget *parent)
    : QDialog(parent), ui_(new Ui_RPSFrequencyDistributionDialog) {
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

  switch (option) {
    case 1:
      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "SingleIndexFrequency.png"));

      break;
  case 2:
      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "DoubleIndexFrequency.png"));

    break;
  case 3:
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
          &RPSFrequencyDistributionDialog::ok);
  connect(ui_->RPSButonButtonBox, &QDialogButtonBox::rejected, this,
          &RPSFrequencyDistributionDialog::cancel);
}

RPSFrequencyDistributionDialog::~RPSFrequencyDistributionDialog() { delete ui_; }

void RPSFrequencyDistributionDialog::ok() {

  QDialog::accept();
}

void RPSFrequencyDistributionDialog::cancel() { QDialog::reject(); }
