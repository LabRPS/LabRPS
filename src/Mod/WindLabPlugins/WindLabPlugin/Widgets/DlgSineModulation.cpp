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




#include "DlgSineModulation.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgSineModulation.h>
#include <Mod/WindLabPlugins/WindLabPlugin/SineModulation.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgSineModulation */

DlgSineModulation::DlgSineModulation(const App::PropertyTime& PulseDuration, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgSineModulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_PulseDuration->setRange(0.00, DBL_MAX);


    ui->doubleSpinBox_PulseDuration->setValue(PulseDuration.getValue());


    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgSineModulation::~DlgSineModulation()
{
}

void DlgSineModulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CSineModulation* activefeature = static_cast<WindLab::CSineModulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->PulseDuration.setValue(ui->doubleSpinBox_PulseDuration->value().getValue());


  }

void DlgSineModulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgSineModulationEdit */

DlgSineModulationEdit::DlgSineModulationEdit(const App::PropertyTime& PulseDuration, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgSineModulation(PulseDuration, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgSineModulationEdit::~DlgSineModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgSineModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgSineModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgSineModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgSineModulation.cpp"
