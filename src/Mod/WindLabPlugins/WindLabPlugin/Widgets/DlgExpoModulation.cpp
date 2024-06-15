/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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




#include "DlgExpoModulation.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgExpoModulation.h>
#include <Mod/WindLabPlugins/WindLabPlugin/ExpoModulation.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgExpoModulation */

DlgExpoModulation::DlgExpoModulation(const App::PropertyTime& TimeOfMax, const App::PropertyFloat& StormLength, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgExpoModulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_TimeOfMax->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_StormLength->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_TimeOfMax->setValue(TimeOfMax.getValue());
    ui->doubleSpinBox_StormLength->setValue(StormLength.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSExpoModulation.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgExpoModulation::~DlgExpoModulation()
{
}

void DlgExpoModulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CExpoModulation* activefeature = static_cast<WindLab::CExpoModulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->TimeOfMax.setValue(ui->doubleSpinBox_TimeOfMax->value().getValue());
    activefeature->StormLength.setValue(ui->doubleSpinBox_StormLength->value().getValue());

  }

void DlgExpoModulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgExpoModulationEdit */

DlgExpoModulationEdit::DlgExpoModulationEdit(const App::PropertyTime& TimeOfMax, const App::PropertyFloat& StormLength, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgExpoModulation(TimeOfMax, StormLength, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgExpoModulationEdit::~DlgExpoModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgExpoModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgExpoModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgExpoModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgExpoModulation.cpp"
