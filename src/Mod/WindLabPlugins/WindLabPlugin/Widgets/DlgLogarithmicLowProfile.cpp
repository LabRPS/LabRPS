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

#include "DlgLogarithmicLowProfile.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgLogarithmicLowProfile.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSLogarithmicLowProfile.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgLogarithmicLowProfile */

DlgLogarithmicLowProfile::DlgLogarithmicLowProfile(const App::PropertyLength& TerrainRoughness, const App::PropertySpeed& ShearVelocity, const App::PropertyLength& ZeroPlanDisplacement, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgLogarithmicLowProfile), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_Zo->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Mu->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Zd->setRange(-DBL_MAX, DBL_MAX);

    ui->doubleSpinBox_Zo->setValue(TerrainRoughness.getValue());
    ui->doubleSpinBox_Mu->setValue(ShearVelocity.getValue());
    ui->doubleSpinBox_Zd->setValue(ZeroPlanDisplacement.getValue());

    ui->doubleSpinBox_Zo->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Mu->setUnit(Base::Unit::Velocity);
    ui->doubleSpinBox_Zd->setUnit(Base::Unit::Length);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSLogarithmicLowProfile.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgLogarithmicLowProfile::~DlgLogarithmicLowProfile()
{
}

void DlgLogarithmicLowProfile::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::RPSLogarithmicLowProfile* activefeature = static_cast<WindLab::RPSLogarithmicLowProfile*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->TerrainRoughness.setValue(ui->doubleSpinBox_Zo->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_Mu->value().getValue());
    activefeature->ZeroPlanDisplacement.setValue(ui->doubleSpinBox_Zd->value().getValue());
}

void DlgLogarithmicLowProfile::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgLogarithmicLowProfileEdit */

DlgLogarithmicLowProfileEdit::DlgLogarithmicLowProfileEdit(const App::PropertyLength& TerrainRoughness, const App::PropertySpeed& ShearVelocity, const App::PropertyLength& ZeroPlanDisplacement, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgLogarithmicLowProfile(TerrainRoughness, ShearVelocity, ZeroPlanDisplacement, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgLogarithmicLowProfileEdit::~DlgLogarithmicLowProfileEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgLogarithmicLowProfileEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgLogarithmicLowProfileEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgLogarithmicLowProfileEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgLogarithmicLowProfile.cpp"
