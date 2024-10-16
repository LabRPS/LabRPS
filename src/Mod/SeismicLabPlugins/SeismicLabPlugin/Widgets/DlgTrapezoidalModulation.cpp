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




#include "DlgTrapezoidalModulation.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgTrapezoidalModulation.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSTrapezoidalModulation.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgTrapezoidalModulation */

DlgTrapezoidalModulation::DlgTrapezoidalModulation(const App::PropertyTime& RiseTime, const App::PropertyTime& LevelTime, const App::PropertyTime& MaxTime, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgTrapezoidalModulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_RiseTime->setValue(RiseTime.getValue());
    ui->doubleSpinBox_LevelTime->setValue(LevelTime.getValue());
    ui->doubleSpinBox_MaximumTime->setValue(MaxTime.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSCloughPenzienSpectrum.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgTrapezoidalModulation::~DlgTrapezoidalModulation()
{
}

void DlgTrapezoidalModulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSTrapezoidalModulation* activefeature = static_cast<SeismicLab::CRPSTrapezoidalModulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->RiseTime.setValue(ui->doubleSpinBox_RiseTime->value().getValue());
    activefeature->LevelTime.setValue(ui->doubleSpinBox_LevelTime->value().getValue());
    activefeature->MaxTime.setValue(ui->doubleSpinBox_MaximumTime->value().getValue());
  }

void DlgTrapezoidalModulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgTrapezoidalModulationEdit */

DlgTrapezoidalModulationEdit::DlgTrapezoidalModulationEdit(const App::PropertyTime& RiseTime, const App::PropertyTime& LevelTime, const App::PropertyTime& MaxTime, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgTrapezoidalModulation(RiseTime,LevelTime, MaxTime, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgTrapezoidalModulationEdit::~DlgTrapezoidalModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgTrapezoidalModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgTrapezoidalModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgTrapezoidalModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgTrapezoidalModulation.cpp"
