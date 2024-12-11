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

#include "DlgTogbenouEtAl2016.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgTogbenouEtAl2016.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSTogbenouEtAl2016.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgTogbenouEtAl2016 */

DlgTogbenouEtAl2016::DlgTogbenouEtAl2016(const App::PropertyInteger& NumberOfLocation,
                       const App::PropertyInteger& NumberOfFrequencies,
                       const App::PropertyLength& LocationSpacing,
                       const App::PropertyFloat& CoherenceDecayCoefficient,
                       const App::PropertyFrequency& UpperCutOffFrequency,
                       const App::PropertyInteger& NumberOfTimeIncrements, 
                       const App::PropertyLength& RoughnessLength,
                       const App::PropertyLength& StartingElevation,
                       const App::PropertyInteger& ReferencePointIndex,
                       const App::PropertyString& featureName, 
                       QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgTogbenouEtAl2016), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->spinBox_NumberOfLocation->setValue(NumberOfLocation.getValue());
    ui->spinBox_NumberOfFrequencies->setValue(NumberOfFrequencies.getValue());
    ui->doubleSpinBox_LocationSpacing->setValue(LocationSpacing.getValue());
    ui->doubleSpinBox_CoherenceDecayCoefficient->setValue(CoherenceDecayCoefficient.getValue());
    ui->doubleSpinBox_UpperCutOffFrequency->setValue(UpperCutOffFrequency.getValue());
    ui->spinBox_NumberOfTimeIncrements->setValue(NumberOfTimeIncrements.getValue());
    ui->doubleSpinBox_RoughnessLength->setValue(RoughnessLength.getValue());
    ui->doubleSpinBox_StartingElevation->setValue(StartingElevation.getValue());
    ui->spinBox_ReferencePointIndex->setValue(ReferencePointIndex.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgTogbenouEtAl2016::~DlgTogbenouEtAl2016()
{
}

void DlgTogbenouEtAl2016::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CRPSTogbenouEtAl2016* activefeature = static_cast<WindLab::CRPSTogbenouEtAl2016*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->NumberOfLocation.setValue(ui->spinBox_NumberOfLocation->value());
    activefeature->NumberOfFrequencies.setValue(ui->spinBox_NumberOfFrequencies->value());
    activefeature->LocationSpacing.setValue(ui->doubleSpinBox_LocationSpacing->value().getValue());
    activefeature->CoherenceDecayCoefficient.setValue(ui->doubleSpinBox_CoherenceDecayCoefficient->value().getValue());
    activefeature->UpperCutOffFrequency.setValue(ui->doubleSpinBox_UpperCutOffFrequency->value().getValue());
    activefeature->NumberOfTimeIncrements.setValue(ui->spinBox_NumberOfTimeIncrements->value());
    activefeature->RoughnessLength.setValue(ui->doubleSpinBox_RoughnessLength->value().getValue());
    activefeature->StartingElevation.setValue(ui->doubleSpinBox_StartingElevation->value().getValue());
    activefeature->ReferencePointIndex.setValue(ui->spinBox_ReferencePointIndex->value());


  }

void DlgTogbenouEtAl2016::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgTogbenouEtAl2016Edit */

DlgTogbenouEtAl2016Edit::DlgTogbenouEtAl2016Edit(
    const App::PropertyInteger& NumberOfLocation, 
    const App::PropertyInteger& NumberOfFrequencies,
    const App::PropertyLength& LocationSpacing,
    const App::PropertyFloat& CoherenceDecayCoefficient,
    const App::PropertyFrequency& UpperCutOffFrequency,
    const App::PropertyInteger& NumberOfTimeIncrements, 
    const App::PropertyLength& RoughnessLength,
    const App::PropertyLength& StartingElevation,
    const App::PropertyInteger& ReferencePointIndex,
    const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgTogbenouEtAl2016(NumberOfLocation, NumberOfFrequencies, LocationSpacing, CoherenceDecayCoefficient,UpperCutOffFrequency, NumberOfTimeIncrements, RoughnessLength, StartingElevation, ReferencePointIndex, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
   
}

DlgTogbenouEtAl2016Edit::~DlgTogbenouEtAl2016Edit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgTogbenouEtAl2016Edit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgTogbenouEtAl2016Edit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgTogbenouEtAl2016Edit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgTogbenouEtAl2016.cpp"
