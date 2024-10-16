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




#include "DlgJenningsEtAl1968Modulation.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgJenningsEtAl1968Modulation.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSJenningsEtAl1968Modulation.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgJenningsEtAl1968Modulation */

DlgJenningsEtAl1968Modulation::DlgJenningsEtAl1968Modulation(const App::PropertyTime& RiseTime, const App::PropertyTime& LevelTime, const App::PropertyFloat& Alpha, const App::PropertyFloat& Power, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgJenningsEtAl1968Modulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_RiseTime->setUnit(Base::Unit::TimeSpan);
    ui->doubleSpinBox_LevelTime->setUnit(Base::Unit::TimeSpan);

    ui->doubleSpinBox_RiseTime->setValue(RiseTime.getValue());
    ui->doubleSpinBox_LevelTime->setValue(LevelTime.getValue());
    ui->doubleSpinBox_Alpha->setValue(Alpha.getValue());
    ui->doubleSpinBox_Power->setValue(Power.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSCloughPenzienSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgJenningsEtAl1968Modulation::~DlgJenningsEtAl1968Modulation()
{
}

void DlgJenningsEtAl1968Modulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSJenningsEtAl1968Modulation* activefeature = static_cast<SeismicLab::CRPSJenningsEtAl1968Modulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->RiseTime.setValue(ui->doubleSpinBox_RiseTime->value().getValue());
    activefeature->LevelTime.setValue(ui->doubleSpinBox_LevelTime->value().getValue());
    activefeature->Alpha.setValue(ui->doubleSpinBox_Alpha->value().getValue());
    activefeature->Power.setValue(ui->doubleSpinBox_Power->value().getValue());
  }

void DlgJenningsEtAl1968Modulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgJenningsEtAl1968ModulationEdit */

DlgJenningsEtAl1968ModulationEdit::DlgJenningsEtAl1968ModulationEdit(const App::PropertyTime& RiseTime, const App::PropertyTime& LevelTime, const App::PropertyFloat& Alpha, const App::PropertyFloat& Power, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgJenningsEtAl1968Modulation(RiseTime,LevelTime, Alpha, Power, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgJenningsEtAl1968ModulationEdit::~DlgJenningsEtAl1968ModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgJenningsEtAl1968ModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgJenningsEtAl1968ModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgJenningsEtAl1968ModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgJenningsEtAl1968Modulation.cpp"
