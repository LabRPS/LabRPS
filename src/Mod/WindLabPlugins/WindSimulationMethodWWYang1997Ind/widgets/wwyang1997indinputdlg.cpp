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

#include "wwyang1997indinputdlg.h"
#include "ui_wwyang1997indinputdlg.h"
#include <cmath>

WWYang1997IndInputDlg::WWYang1997IndInputDlg(int numberOfLocation,
                                             int numberOfFrequencies,
                                             double locationHeight,
                                             double locationSpacing,
                                             double meanSpeed,
                                             double shearVelocity,
                                             double upperCutoffFrequency,
                                             int numberOfTimeIncrements,
                                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WWYang1997IndInputDlg)
{
    ui->setupUi(this);
    ui->lineEditNumberOfLocation->setMinimum(1);
    ui->lineEditNumberOfLocation->setMaximum(std::numeric_limits<int>::max());
    ui->lineEditNumberOfFrequencies->setMinimum(1);
    ui->lineEditNumberOfFrequencies->setMaximum(std::numeric_limits<int>::max());
    ui->lineEditLocationHeight->setMinimum(-INFINITY);
    ui->lineEditLocationHeight->setMaximum(std::numeric_limits<double>::max());
    ui->lineEditLocationSpacing->setMinimum(-INFINITY);
    ui->lineEditLocationSpacing->setMaximum(std::numeric_limits<double>::max());
    ui->lineEditMeanSpeed->setMinimum(-INFINITY);
    ui->lineEditMeanSpeed->setMaximum(std::numeric_limits<double>::max());
    ui->lineEditShearVelocity->setMinimum(-INFINITY);
    ui->lineEditShearVelocity->setMaximum(std::numeric_limits<double>::max());
    ui->lineEditUpperCutoffFrequency->setMinimum(-INFINITY);
    ui->lineEditUpperCutoffFrequency->setMaximum(std::numeric_limits<double>::max());
    ui->lineEditNumberOfTimeIncrements->setMinimum(1);
    ui->lineEditNumberOfTimeIncrements->setMaximum(std::numeric_limits<int>::max());

    ui->lineEditNumberOfLocation->setValue(numberOfLocation);
    ui->lineEditNumberOfFrequencies->setValue(numberOfFrequencies);
    ui->lineEditLocationHeight->setValue(locationHeight);
    ui->lineEditLocationSpacing->setValue(locationSpacing);
    ui->lineEditMeanSpeed->setValue(meanSpeed);
    ui->lineEditShearVelocity->setValue(shearVelocity);
    ui->lineEditUpperCutoffFrequency->setValue(upperCutoffFrequency);
    ui->lineEditNumberOfTimeIncrements->setValue(numberOfTimeIncrements);

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

}

WWYang1997IndInputDlg::~WWYang1997IndInputDlg()
{
    delete ui;
}

void WWYang1997IndInputDlg::acceptInput()
{
    m_numberOfLocation = ui->lineEditNumberOfLocation->text().toDouble();
    m_numberOfFrequencies = ui->lineEditNumberOfFrequencies->text().toDouble();
    m_locationHeight = ui->lineEditLocationHeight->text().toDouble();
    m_locationSpacing = ui->lineEditLocationSpacing->text().toDouble();
    m_meanSpeed = ui->lineEditMeanSpeed->text().toDouble();
    m_shearVelocity = ui->lineEditShearVelocity->text().toDouble();
    m_upperCutoffFrequency = ui->lineEditUpperCutoffFrequency->text().toDouble();
    m_numberOfTimeIncrements = ui->lineEditNumberOfTimeIncrements->text().toDouble();

}
