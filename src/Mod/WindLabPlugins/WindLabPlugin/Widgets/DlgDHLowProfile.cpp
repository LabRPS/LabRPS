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




#include "DlgDHLowProfile.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgDHLowProfile.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSDHLowProfile.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgDHLowProfile */

DlgDHLowProfile::DlgDHLowProfile(const App::PropertyLength& TerrainRoughness, const App::PropertySpeed& ShearVelocity, const App::PropertyLength& ZeroPlanDisplacement, const App::PropertyAngle& Latitude, const App::PropertyFrequency& EarthAngularVelocity, const App::PropertyFloat& Betta, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgDHLowProfile), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_Zo->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Mu->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Zd->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Phi->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Omega->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Beta->setRange(-DBL_MAX, DBL_MAX);

    ui->doubleSpinBox_Zo->setValue(TerrainRoughness.getValue());
    ui->doubleSpinBox_Mu->setValue(ShearVelocity.getValue());
    ui->doubleSpinBox_Zd->setValue(ZeroPlanDisplacement.getValue());
    ui->doubleSpinBox_Phi->setValue(Latitude.getValue());
    ui->doubleSpinBox_Omega->setValue(EarthAngularVelocity.getValue());
    ui->doubleSpinBox_Beta->setValue(Betta.getValue());

    ui->doubleSpinBox_Zo->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Mu->setUnit(Base::Unit::Velocity);
    ui->doubleSpinBox_Zd->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Phi->setUnit(Base::Unit::Angle);
    ui->doubleSpinBox_Omega->setUnit(Base::Unit::Frequency);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSDHLowProfile.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgDHLowProfile::~DlgDHLowProfile()
{
}

void DlgDHLowProfile::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CRPSDHLowProfile* activefeature = static_cast<WindLab::CRPSDHLowProfile*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->TerrainRoughness.setValue(ui->doubleSpinBox_Zo->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_Mu->value().getValue());
    activefeature->ZeroPlanDisplacement.setValue(ui->doubleSpinBox_Zd->value().getValue());
    activefeature->Latitude.setValue(ui->doubleSpinBox_Phi->value().getValue());
    activefeature->EarthAngularVelocity.setValue(ui->doubleSpinBox_Omega->value().getValue());
    activefeature->Betta.setValue(ui->doubleSpinBox_Beta->value().getValue());
}

void DlgDHLowProfile::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgDHLowProfileEdit */

DlgDHLowProfileEdit::DlgDHLowProfileEdit(const App::PropertyLength& TerrainRoughness, const App::PropertySpeed& ShearVelocity, const App::PropertyLength& ZeroPlanDisplacement, const App::PropertyAngle& Latitude, const App::PropertyFrequency& EarthAngularVelocity, const App::PropertyFloat& Betta, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgDHLowProfile(TerrainRoughness, ShearVelocity, ZeroPlanDisplacement, Latitude, EarthAngularVelocity, Betta, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgDHLowProfileEdit::~DlgDHLowProfileEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgDHLowProfileEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgDHLowProfileEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgDHLowProfileEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgDHLowProfile.cpp"
