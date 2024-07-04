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

#include "DlgSimuAcrossWindSpectrum.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgSimuAcrossWindSpectrum.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSSimuAcrossWindSpectrum.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgSimuAcrossWindSpectrum */

DlgSimuAcrossWindSpectrum::DlgSimuAcrossWindSpectrum(const App::PropertySpeed& ShearVelocity, const App::PropertyFloat& Constant1, const App::PropertyFloat& Constant2, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgSimuAcrossWindSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ShearVelocity->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_Constant1->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_Constant2->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_ShearVelocity->setValue(ShearVelocity.getValue());
    ui->doubleSpinBox_Constant1->setValue(Constant1.getValue());
    ui->doubleSpinBox_Constant2->setValue(Constant2.getValue());

    ui->doubleSpinBox_ShearVelocity->setUnit(Base::Unit::Velocity);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSSimuAlongWindSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgSimuAcrossWindSpectrum::~DlgSimuAcrossWindSpectrum()
{
}

void DlgSimuAcrossWindSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CRPSSimuAcrossWindSpectrum* activefeature = static_cast<WindLab::CRPSSimuAcrossWindSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_ShearVelocity->value().getValue());
    activefeature->Constant1.setValue(ui->doubleSpinBox_Constant1->value().getValue());
    activefeature->Constant2.setValue(ui->doubleSpinBox_Constant2->value().getValue());


  }

void DlgSimuAcrossWindSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgSimuAcrossWindSpectrumEdit */

DlgSimuAcrossWindSpectrumEdit::DlgSimuAcrossWindSpectrumEdit(const App::PropertySpeed& ShearVelocity, const App::PropertyFloat& Constant1, const App::PropertyFloat& Constant2, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgSimuAcrossWindSpectrum(ShearVelocity, Constant1, Constant2, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgSimuAcrossWindSpectrumEdit::~DlgSimuAcrossWindSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgSimuAcrossWindSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgSimuAcrossWindSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgSimuAcrossWindSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgSimuAcrossWindSpectrum.cpp"
