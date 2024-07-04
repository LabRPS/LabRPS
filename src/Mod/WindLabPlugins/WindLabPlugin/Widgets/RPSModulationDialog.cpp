
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

#include "RPSModulationDialog.h"
#include <QDebug>
#include <QSettings>
#include <cmath>

#include "IconLoader.h"
#include "ui_RPSModulationDialog.h"

using namespace WindLab;

RPSModulationDialog::RPSModulationDialog(double para1, double para2, double para3, int option, QWidget *parent)
    : QDialog(parent), ui_(new Ui_RPSModulationDialog) {
  ui_->setupUi(this);
  IconLoader::init();
  IconLoader::lumen_ = 101;
  setWindowIcon(IconLoader::load(QString::fromLatin1("edit-random-dist"), IconLoader::LightDark));
  ui_->formulaLabel->setAlignment(Qt::AlignCenter);
  setModal(true);

  // Theaming based pixmap loading
  (IconLoader::lumen_ < 100)
      ? formulaPath = QString::fromLatin1(":icons/dark/equations/")
      : formulaPath = QString::fromLatin1(":icons/light/equations/");

  // Set layout margins
  ui_->gridLayout->setContentsMargins(0, 0, 0, 0);


  switch (option) {
    case 1:
      // set parameter bounds (move to switch case for more control)
      ui_->SpinBoxContant1->setMinimum(0);
      ui_->SpinBoxContant1->setMaximum(std::numeric_limits<double>::max());
      ui_->SpinBoxContant2->setMinimum(0);
      ui_->SpinBoxContant2->setMaximum(std::numeric_limits<double>::max());
      ui_->SpinBoxContant3->setMinimum(0);
      ui_->SpinBoxContant3->setMaximum(std::numeric_limits<double>::max());

      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + QString::fromLatin1("ThreeParameterModulation.png")));
      ui_->parameter1Label->setText(QString::fromUtf8("𝛼<sub>0</sub> = "));
      ui_->parameter2Label->setText(QString::fromUtf8("𝛽<sub>0</sub> = "));
      ui_->parameter3Label->setText(QString::fromUtf8("𝜆 = "));

      ui_->SpinBoxContant1->setValue(para1);
      ui_->SpinBoxContant2->setValue(para2);
      ui_->SpinBoxContant3->setValue(para3);

      ui_->parameter4Label->hide();
      ui_->SpinBoxContant4->hide();
      ui_->parameter5Label->hide();
      ui_->SpinBoxContant5->hide();

      break;
  case 2:
      // set parameter bounds (move to switch case for more control)
      ui_->SpinBoxContant1->setMinimum(0);
      ui_->SpinBoxContant1->setMaximum(std::numeric_limits<double>::max());

      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + QString::fromLatin1("SineModulation.png")));
      ui_->parameter1Label->setText(QString::fromUtf8("t<sub>d</sub> = "));

      ui_->SpinBoxContant1->setValue(para1);

      ui_->parameter2Label->hide();
      ui_->SpinBoxContant2->hide();
      ui_->parameter3Label->hide();
      ui_->SpinBoxContant3->hide();
      ui_->parameter4Label->hide();
      ui_->SpinBoxContant4->hide();
      ui_->parameter5Label->hide();
      ui_->SpinBoxContant5->hide();


    break;
  case 3:
      // set parameter bounds (move to switch case for more control)
      ui_->SpinBoxContant1->setMinimum(0);
      ui_->SpinBoxContant1->setMaximum(std::numeric_limits<double>::max());
      ui_->SpinBoxContant2->setMinimum(0);
      ui_->SpinBoxContant2->setMaximum(std::numeric_limits<double>::max());


      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + QString::fromLatin1("ExpoModulation.png")));
      ui_->parameter1Label->setText(QString::fromUtf8("t<sub>0</sub> = "));
      ui_->parameter2Label->setText(QString::fromUtf8("D<sub>t</sub> = "));

      ui_->SpinBoxContant1->setValue(para1);
      ui_->SpinBoxContant2->setValue(para2);

      ui_->parameter3Label->hide();
      ui_->SpinBoxContant3->hide();
      ui_->parameter4Label->hide();
      ui_->SpinBoxContant4->hide();
      ui_->parameter5Label->hide();
      ui_->SpinBoxContant5->hide();

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
          &RPSModulationDialog::ok);
  connect(ui_->RPSButonButtonBox, &QDialogButtonBox::rejected, this,
          &RPSModulationDialog::cancel);
}

RPSModulationDialog::~RPSModulationDialog() { delete ui_; }

void RPSModulationDialog::ok() {
m_para1 = ui_->SpinBoxContant1->value();
m_para2 = ui_->SpinBoxContant2->value();
m_para3 = ui_->SpinBoxContant3->value();
  QDialog::accept();
}

void RPSModulationDialog::cancel() { QDialog::reject(); }
