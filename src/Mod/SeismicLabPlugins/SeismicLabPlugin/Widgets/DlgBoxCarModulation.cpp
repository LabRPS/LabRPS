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

#include "DlgBoxCarModulation.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgBoxCarModulation.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSBoxCarModulation.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgBoxCarModulation */

DlgBoxCarModulation::DlgBoxCarModulation(const App::PropertyFloat& ScalingFactor, const App::PropertyTime& StrongMotionDuration, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgBoxCarModulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ScaleFactor->setValue(ScalingFactor.getValue());
    ui->doubleSpinBox_StrongMotionDuration->setValue(StrongMotionDuration.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSBoxCarModulation.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgBoxCarModulation::~DlgBoxCarModulation()
{
}

void DlgBoxCarModulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSBoxCarModulation* activefeature = static_cast<SeismicLab::CRPSBoxCarModulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->ScalingFactor.setValue(ui->doubleSpinBox_ScaleFactor->value().getValue());
    activefeature->StrongMotionDuration.setValue(ui->doubleSpinBox_StrongMotionDuration->value().getValue());
  }

void DlgBoxCarModulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgBoxCarModulationEdit */

DlgBoxCarModulationEdit::DlgBoxCarModulationEdit(const App::PropertyFloat& ScalingFactor, const App::PropertyTime& StrongMotionDuration, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgBoxCarModulation(ScalingFactor, StrongMotionDuration, featureName);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgBoxCarModulationEdit::~DlgBoxCarModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgBoxCarModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgBoxCarModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgBoxCarModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgBoxCarModulation.cpp"
