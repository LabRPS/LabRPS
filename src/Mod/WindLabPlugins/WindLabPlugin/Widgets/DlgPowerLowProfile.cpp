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




#include "DlgPowerLowProfile.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgPowerLowProfile.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSWLPowerLowProfile.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgPowerLowProfile */

DlgPowerLowProfile::DlgPowerLowProfile(const App::PropertyLength& ReferenceHeight, const App::PropertySpeed& ReferenceSpeed, const App::PropertyFloat& DimensionlessPower,  const App::PropertyLength& ZeroPlanDisplacement, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgPowerLowProfile), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ReferenceHeight->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ReferenceSpeed->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_DimensionlessPower->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ZeroPlanDisplacement->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_ReferenceHeight->setValue(ReferenceHeight.getValue());
    ui->doubleSpinBox_ReferenceSpeed->setValue(ReferenceHeight.getValue());
    ui->doubleSpinBox_DimensionlessPower->setValue(DimensionlessPower.getValue());
    ui->doubleSpinBox_ZeroPlanDisplacement->setValue(ZeroPlanDisplacement.getValue());

    ui->doubleSpinBox_ReferenceHeight->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_ReferenceSpeed->setUnit(Base::Unit::Velocity);
    ui->doubleSpinBox_ZeroPlanDisplacement->setUnit(Base::Unit::Length);

    int w = ui->label_Image->width ();
    int h = ui->label_Image->height ();
    QPixmap pix(":icons/PowerMeanProfil.svg");// load pixmap
    //ui->label_Image->setPixmap(QPixmap(":icons/VerticalPointsDistribution1.png"));
    ui->label_Image->setPixmap (pix.scaled (200,60,Qt::KeepAspectRatio));

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgPowerLowProfile::~DlgPowerLowProfile()
{
}

void DlgPowerLowProfile::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::RPSWLPowerLowProfile* activefeature = static_cast<WindLab::RPSWLPowerLowProfile*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ReferenceHeight.setValue(ui->doubleSpinBox_ReferenceHeight->value().getValue());
    activefeature->ReferenceSpeed.setValue(ui->doubleSpinBox_ReferenceSpeed->value().getValue());
    activefeature->DimensionlessPower.setValue(ui->doubleSpinBox_DimensionlessPower->value().getValue());
    activefeature->ZeroPlanDisplacement.setValue(ui->doubleSpinBox_ZeroPlanDisplacement->value().getValue());
}

void DlgPowerLowProfile::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgPowerLowProfileEdit */

DlgPowerLowProfileEdit::DlgPowerLowProfileEdit(const App::PropertyLength& ReferenceHeight, const App::PropertySpeed& ReferenceSpeed, const App::PropertyFloat& DimensionlessPower,  const App::PropertyLength& ZeroPlanDisplacement, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgPowerLowProfile(ReferenceHeight, ReferenceSpeed, DimensionlessPower,  ZeroPlanDisplacement, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgPowerLowProfileEdit::~DlgPowerLowProfileEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgPowerLowProfileEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgPowerLowProfileEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgPowerLowProfileEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgPowerLowProfile.cpp"
