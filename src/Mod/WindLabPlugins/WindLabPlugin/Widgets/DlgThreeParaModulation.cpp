/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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




#include "DlgThreeParaModulation.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgThreeParaModulation.h>
#include <Mod/WindLabPlugins/WindLabPlugin/ThreeParaModulation.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgThreeParaModulation */

DlgThreeParaModulation::DlgThreeParaModulation(const App::PropertyFloat& Alpha, const App::PropertyFloat& Betta, const App::PropertyFloat& Lambda, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgThreeParaModulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_Alpha->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_Betta->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_Lambda->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_Alpha->setValue(Alpha.getValue());
    ui->doubleSpinBox_Betta->setValue(Betta.getValue());
    ui->doubleSpinBox_Lambda->setValue(Lambda.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSThreeParaModulation.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgThreeParaModulation::~DlgThreeParaModulation()
{
}

void DlgThreeParaModulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CThreeParaModulation* activefeature = static_cast<WindLab::CThreeParaModulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->Alpha.setValue(ui->doubleSpinBox_Alpha->value().getValue());
    activefeature->Betta.setValue(ui->doubleSpinBox_Betta->value().getValue());
    activefeature->Lambda.setValue(ui->doubleSpinBox_Lambda->value().getValue());

  }

void DlgThreeParaModulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgThreeParaModulationEdit */

DlgThreeParaModulationEdit::DlgThreeParaModulationEdit(const App::PropertyFloat& Alpha, const App::PropertyFloat& Betta, const App::PropertyFloat& Lambda, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgThreeParaModulation(Alpha, Betta, Lambda, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgThreeParaModulationEdit::~DlgThreeParaModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgThreeParaModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgThreeParaModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgThreeParaModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgThreeParaModulation.cpp"
