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

#include "DlgGeneralizedVonKarmanSpectrum.h"
#include <Mod/WindLabPlugins/generalizedSpectrum/ui_DlgGeneralizedVonKarmanSpectrum.h>
#include <Mod/WindLabPlugins/generalizedSpectrum/generalizedAlongWindVonKarmanSpectrum.h>
#include <Mod/WindLabPlugins/generalizedSpectrum/generalizedAcrossWindVonKarmanSpectrum.h>
#include <Mod/WindLabPlugins/generalizedSpectrum/generalizedVerticalWindVonKarmanSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgGeneralizedVonKarmanSpectrum */

DlgGeneralizedVonKarmanSpectrum::DlgGeneralizedVonKarmanSpectrum(
    const App::PropertyFloat& ParameterA, const App::PropertyFloat& ParameterB,
    const App::PropertyFloat& ParameterC, const App::PropertyFloat& ParameterD,
    const App::PropertyFloat& ParameterE, const App::PropertyFloat& ParameterF,
    const App::PropertyFloat& ParameterG, const App::PropertyFloat& ParameterH,
    const App::PropertyFloat& ParameterI, const App::PropertyFloat& ParameterJ,
    const App::PropertyFloat& IntegralLengthScale, const App::PropertyFloat& StandardDeviation,
    const App::PropertyString& featureName, int type,
    QWidget* parent)
    : QWidget(parent), ui(new Ui_DlgGeneralizedVonKarmanSpectrum),
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
    ui->doubleSpinBox_IntegralLengthScale->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_StandardDeviation->setRange(0.00, DBL_MAX);

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
    ui->doubleSpinBox_IntegralLengthScale->setValue(IntegralLengthScale.getValue());
    ui->doubleSpinBox_StandardDeviation->setValue(StandardDeviation.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgGeneralizedVonKarmanSpectrum::~DlgGeneralizedVonKarmanSpectrum()
{
}

void DlgGeneralizedVonKarmanSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    if (_type == 1)
    {
        WindLab::CRPSGeneralizedAlongWindVonKarmanSpectrum* activefeature = static_cast<WindLab::CRPSGeneralizedAlongWindVonKarmanSpectrum*>(doc->getObject(_featureName.c_str()));
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
    activefeature->IntegralLengthScale.setValue(ui->doubleSpinBox_IntegralLengthScale->value().getValue());
    activefeature->StandardDeviation.setValue(ui->doubleSpinBox_StandardDeviation->value().getValue());

    }
    else if(_type == 2)
    {
        WindLab::CRPSGeneralizedAcrossWindVonKarmanSpectrum* activefeature = static_cast<WindLab::CRPSGeneralizedAcrossWindVonKarmanSpectrum*>(doc->getObject(_featureName.c_str()));
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
    activefeature->IntegralLengthScale.setValue(ui->doubleSpinBox_IntegralLengthScale->value().getValue());
    activefeature->StandardDeviation.setValue(ui->doubleSpinBox_StandardDeviation->value().getValue());

    }
    else if (_type == 3)
    {
        WindLab::CRPSGeneralizedVerticalWindVonKarmanSpectrum* activefeature = static_cast<WindLab::CRPSGeneralizedVerticalWindVonKarmanSpectrum*>(doc->getObject(_featureName.c_str()));
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
    activefeature->IntegralLengthScale.setValue(ui->doubleSpinBox_IntegralLengthScale->value().getValue());
    activefeature->StandardDeviation.setValue(ui->doubleSpinBox_StandardDeviation->value().getValue());

    }

  }

void DlgGeneralizedVonKarmanSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgGeneralizedVonKarmanSpectrumEdit */

DlgGeneralizedVonKarmanSpectrumEdit::DlgGeneralizedVonKarmanSpectrumEdit(
    const App::PropertyFloat& ParameterA, const App::PropertyFloat& ParameterB,
    const App::PropertyFloat& ParameterC, const App::PropertyFloat& ParameterD,
    const App::PropertyFloat& ParameterE, const App::PropertyFloat& ParameterF,
    const App::PropertyFloat& ParameterG, const App::PropertyFloat& ParameterH,
    const App::PropertyFloat& ParameterI, const App::PropertyFloat& ParameterJ,
    const App::PropertyFloat& IntegralLengthScale, const App::PropertyFloat& StandardDeviation,
    const App::PropertyString& featureName, int type)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgGeneralizedVonKarmanSpectrum(
        ParameterA, ParameterB,
        ParameterC, ParameterD,
        ParameterE, ParameterF,
        ParameterG, ParameterH,
        ParameterI, ParameterJ, 
        IntegralLengthScale,StandardDeviation, featureName, type, nullptr);

	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgGeneralizedVonKarmanSpectrumEdit::~DlgGeneralizedVonKarmanSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgGeneralizedVonKarmanSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgGeneralizedVonKarmanSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgGeneralizedVonKarmanSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgGeneralizedVonKarmanSpectrum.cpp"
