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

#include "DlgGeneralizedKaimalSpectrum.h"
#include <Mod/WindLabPlugins/generalizedSpectrum/ui_DlgGeneralizedKaimalSpectrum.h>
#include <Mod/WindLabPlugins/generalizedSpectrum/generalizedAlongWindKaimalSpectrum.h>
#include <Mod/WindLabPlugins/generalizedSpectrum/generalizedAcrossWindKaimalSpectrum.h>
#include <Mod/WindLabPlugins/generalizedSpectrum/generalizedVerticalWindKaimalSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgGeneralizedKaimalSpectrum */

DlgGeneralizedKaimalSpectrum::DlgGeneralizedKaimalSpectrum(
    const App::PropertyFloat& ParameterA, const App::PropertyFloat& ParameterB,
    const App::PropertyFloat& ParameterC, const App::PropertyFloat& ParameterD,
    const App::PropertyFloat& ParameterE, const App::PropertyFloat& ParameterF,
    const App::PropertyFloat& ParameterG, const App::PropertyFloat& ParameterH,
    const App::PropertyFloat& ParameterI, const App::PropertyFloat& ParameterJ,
    const App::PropertySpeed& ShearVelocity, const App::PropertyString& featureName,
    int type, QWidget* parent)
    : QWidget(parent), ui(new Ui_DlgGeneralizedKaimalSpectrum),
      _featureName(featureName.getStrValue()), _type(type)
{
	ui->setupUi(this);

    ui->doubleSpinBox_ParameterA->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterB->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterC->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterD->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterE->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterF->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterG->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterH->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterI->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ParameterJ->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ShearVelocity->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_ParameterA->setValue(ParameterA.getValue());
    ui->doubleSpinBox_ParameterB->setValue(ParameterB.getValue());
    ui->doubleSpinBox_ParameterC->setValue(ParameterC.getValue());
    ui->doubleSpinBox_ParameterD->setValue(ParameterD.getValue());
    ui->doubleSpinBox_ParameterE->setValue(ParameterE.getValue());
    ui->doubleSpinBox_ParameterF->setValue(ParameterF.getValue());
    ui->doubleSpinBox_ParameterG->setValue(ParameterG.getValue());
    ui->doubleSpinBox_ParameterH->setValue(ParameterH.getValue());
    ui->doubleSpinBox_ParameterI->setValue(ParameterI.getValue());
    ui->doubleSpinBox_ParameterJ->setValue(ParameterJ.getValue());
    ui->doubleSpinBox_ShearVelocity->setValue(ShearVelocity.getValue());

    ui->doubleSpinBox_ShearVelocity->setUnit(Base::Unit::Velocity);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgGeneralizedKaimalSpectrum::~DlgGeneralizedKaimalSpectrum()
{
}

void DlgGeneralizedKaimalSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    if (_type == 4)
    {
    WindLab::CRPSGeneralizedAlongWindKaimalSpectrum* activefeature = static_cast<WindLab::CRPSGeneralizedAlongWindKaimalSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ParameterA.setValue(ui->doubleSpinBox_ParameterA->value().getValue());
    activefeature->ParameterB.setValue(ui->doubleSpinBox_ParameterB->value().getValue());
    activefeature->ParameterC.setValue(ui->doubleSpinBox_ParameterC->value().getValue());
    activefeature->ParameterD.setValue(ui->doubleSpinBox_ParameterD->value().getValue());
    activefeature->ParameterE.setValue(ui->doubleSpinBox_ParameterE->value().getValue());
    activefeature->ParameterF.setValue(ui->doubleSpinBox_ParameterF->value().getValue());
    activefeature->ParameterG.setValue(ui->doubleSpinBox_ParameterG->value().getValue());
    activefeature->ParameterH.setValue(ui->doubleSpinBox_ParameterH->value().getValue());
    activefeature->ParameterI.setValue(ui->doubleSpinBox_ParameterI->value().getValue());
    activefeature->ParameterJ.setValue(ui->doubleSpinBox_ParameterJ->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_ShearVelocity->value().getValue());
    }
    if (_type == 5)
    {
        WindLab::CRPSGeneralizedAcrossWindKaimalSpectrum* activefeature = static_cast<WindLab::CRPSGeneralizedAcrossWindKaimalSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ParameterA.setValue(ui->doubleSpinBox_ParameterA->value().getValue());
    activefeature->ParameterB.setValue(ui->doubleSpinBox_ParameterB->value().getValue());
    activefeature->ParameterC.setValue(ui->doubleSpinBox_ParameterC->value().getValue());
    activefeature->ParameterD.setValue(ui->doubleSpinBox_ParameterD->value().getValue());
    activefeature->ParameterE.setValue(ui->doubleSpinBox_ParameterE->value().getValue());
    activefeature->ParameterF.setValue(ui->doubleSpinBox_ParameterF->value().getValue());
    activefeature->ParameterG.setValue(ui->doubleSpinBox_ParameterG->value().getValue());
    activefeature->ParameterH.setValue(ui->doubleSpinBox_ParameterH->value().getValue());
    activefeature->ParameterI.setValue(ui->doubleSpinBox_ParameterI->value().getValue());
    activefeature->ParameterJ.setValue(ui->doubleSpinBox_ParameterJ->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_ShearVelocity->value().getValue());
    }
    if (_type == 6) 
    {
        WindLab::CRPSGeneralizedVerticalWindKaimalSpectrum* activefeature = static_cast<WindLab::CRPSGeneralizedVerticalWindKaimalSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ParameterA.setValue(ui->doubleSpinBox_ParameterA->value().getValue());
    activefeature->ParameterB.setValue(ui->doubleSpinBox_ParameterB->value().getValue());
    activefeature->ParameterC.setValue(ui->doubleSpinBox_ParameterC->value().getValue());
    activefeature->ParameterD.setValue(ui->doubleSpinBox_ParameterD->value().getValue());
    activefeature->ParameterE.setValue(ui->doubleSpinBox_ParameterE->value().getValue());
    activefeature->ParameterF.setValue(ui->doubleSpinBox_ParameterF->value().getValue());
    activefeature->ParameterG.setValue(ui->doubleSpinBox_ParameterG->value().getValue());
    activefeature->ParameterH.setValue(ui->doubleSpinBox_ParameterH->value().getValue());
    activefeature->ParameterI.setValue(ui->doubleSpinBox_ParameterI->value().getValue());
    activefeature->ParameterJ.setValue(ui->doubleSpinBox_ParameterJ->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_ShearVelocity->value().getValue());
    }


  }

void DlgGeneralizedKaimalSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgGeneralizedKaimalSpectrumEdit */

DlgGeneralizedKaimalSpectrumEdit::DlgGeneralizedKaimalSpectrumEdit(
    const App::PropertyFloat& ParameterA, const App::PropertyFloat& ParameterB,
    const App::PropertyFloat& ParameterC, const App::PropertyFloat& ParameterD,
    const App::PropertyFloat& ParameterE, const App::PropertyFloat& ParameterF,
    const App::PropertyFloat& ParameterG, const App::PropertyFloat& ParameterH,
    const App::PropertyFloat& ParameterI, const App::PropertyFloat& ParameterJ,
    const App::PropertySpeed& ShearVelocity, const App::PropertyString& featureName, int type)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgGeneralizedKaimalSpectrum(
        ParameterA, ParameterB,
        ParameterC, ParameterD,
        ParameterE, ParameterF,
        ParameterG, ParameterH,
        ParameterI, ParameterJ,
        ShearVelocity, featureName, type, nullptr);

	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgGeneralizedKaimalSpectrumEdit::~DlgGeneralizedKaimalSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgGeneralizedKaimalSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgGeneralizedKaimalSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgGeneralizedKaimalSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgGeneralizedKaimalSpectrum.cpp"
