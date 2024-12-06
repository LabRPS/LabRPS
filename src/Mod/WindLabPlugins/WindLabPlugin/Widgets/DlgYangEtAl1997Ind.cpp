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

#include "DlgYangEtAl1997Ind.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgYangEtAl1997Ind.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSYangEtAl1997Ind.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgYangEtAl1997Ind */

DlgYangEtAl1997Ind::DlgYangEtAl1997Ind(const App::PropertyInteger& NumberOfLocation,
                       const App::PropertyInteger& NumberOfFrequencies,
                       const App::PropertyLength& LocationHeight,
                       const App::PropertyLength& LocationSpacing,
                       const App::PropertySpeed& MeanSpeed, 
                       const App::PropertyFloat& CoherenceDecayCoefficient,
                       const App::PropertyFrequency& UpperCutOffFrequency,
    const App::PropertyInteger& NumberOfTimeIncrements, const App::PropertyLength& RoughnessLength,
                       const App::PropertyString& featureName, 
                       QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgYangEtAl1997Ind), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->spinBox_NumberOfLocation->setValue(NumberOfLocation.getValue());
    ui->spinBox_NumberOfFrequencies->setValue(NumberOfFrequencies.getValue());
    ui->doubleSpinBox_LocationHeight->setValue(LocationHeight.getValue());
    ui->doubleSpinBox_LocationSpacing->setValue(LocationSpacing.getValue());
    ui->doubleSpinBox_MeanSpeed->setValue(MeanSpeed.getValue());
    ui->doubleSpinBox_CoherenceDecayCoefficient->setValue(CoherenceDecayCoefficient.getValue());
    ui->doubleSpinBox_UpperCutOffFrequency->setValue(UpperCutOffFrequency.getValue());
    ui->spinBox_NumberOfTimeIncrements->setValue(NumberOfTimeIncrements.getValue());
    ui->doubleSpinBox_RoughnessLength->setValue(RoughnessLength.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgYangEtAl1997Ind::~DlgYangEtAl1997Ind()
{
}

void DlgYangEtAl1997Ind::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CRPSYangEtAl1997Ind* activefeature = static_cast<WindLab::CRPSYangEtAl1997Ind*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->NumberOfLocation.setValue(ui->spinBox_NumberOfLocation->value());
    activefeature->NumberOfFrequencies.setValue(ui->spinBox_NumberOfFrequencies->value());
    activefeature->LocationHeight.setValue(ui->doubleSpinBox_LocationHeight->value().getValue());
    activefeature->LocationSpacing.setValue(ui->doubleSpinBox_LocationSpacing->value().getValue());
    activefeature->MeanSpeed.setValue(ui->doubleSpinBox_MeanSpeed->value().getValue());
    activefeature->CoherenceDecayCoefficient.setValue(ui->doubleSpinBox_CoherenceDecayCoefficient->value().getValue());
    activefeature->UpperCutOffFrequency.setValue(ui->doubleSpinBox_UpperCutOffFrequency->value().getValue());
    activefeature->NumberOfTimeIncrements.setValue(ui->spinBox_NumberOfTimeIncrements->value());
    activefeature->RoughnessLength.setValue(ui->doubleSpinBox_RoughnessLength->value().getValue());

  }

void DlgYangEtAl1997Ind::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgYangEtAl1997IndEdit */

DlgYangEtAl1997IndEdit::DlgYangEtAl1997IndEdit(
    const App::PropertyInteger& NumberOfLocation, const App::PropertyInteger& NumberOfFrequencies,
    const App::PropertyLength& LocationHeight, const App::PropertyLength& LocationSpacing,
    const App::PropertySpeed& MeanSpeed, const App::PropertyFloat& CoherenceDecayCoefficient,
    const App::PropertyFrequency& UpperCutOffFrequency,
    const App::PropertyInteger& NumberOfTimeIncrements, const App::PropertyLength& RoughnessLength,
    const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgYangEtAl1997Ind(NumberOfLocation, NumberOfFrequencies, LocationHeight,LocationSpacing, MeanSpeed, CoherenceDecayCoefficient,UpperCutOffFrequency, NumberOfTimeIncrements, RoughnessLength, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
   
}

DlgYangEtAl1997IndEdit::~DlgYangEtAl1997IndEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgYangEtAl1997IndEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgYangEtAl1997IndEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgYangEtAl1997IndEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgYangEtAl1997Ind.cpp"
