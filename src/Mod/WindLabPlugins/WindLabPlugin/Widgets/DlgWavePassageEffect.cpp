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




#include "DlgWavePassageEffect.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgWavePassageEffect.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSWavePassageEffect.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgWavePassageEffect */

DlgWavePassageEffect::DlgWavePassageEffect(const App::PropertySpeed& ApparentWaveVelocity, const App::PropertyFloat& Coefficient, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgWavePassageEffect), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ApparentWaveVelocity->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_Coefficient->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_ApparentWaveVelocity->setValue(ApparentWaveVelocity.getValue());
    ui->doubleSpinBox_Coefficient->setValue(Coefficient.getValue());

    ui->doubleSpinBox_ApparentWaveVelocity->setUnit(Base::Unit::Velocity);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgWavePassageEffect::~DlgWavePassageEffect()
{
}

void DlgWavePassageEffect::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CRPSWavePassageEffect* activefeature = static_cast<WindLab::CRPSWavePassageEffect*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ApparentWaveVelocity.setValue(ui->doubleSpinBox_ApparentWaveVelocity->value().getValue());
    activefeature->Coefficient.setValue(ui->doubleSpinBox_Coefficient->value().getValue());

  }

void DlgWavePassageEffect::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgWavePassageEffectEdit */

DlgWavePassageEffectEdit::DlgWavePassageEffectEdit(const App::PropertySpeed& ApparentWaveVelocity, const App::PropertyFloat& Coefficient,const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgWavePassageEffect(ApparentWaveVelocity, Coefficient, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgWavePassageEffectEdit::~DlgWavePassageEffectEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgWavePassageEffectEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgWavePassageEffectEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgWavePassageEffectEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgWavePassageEffect.cpp"
