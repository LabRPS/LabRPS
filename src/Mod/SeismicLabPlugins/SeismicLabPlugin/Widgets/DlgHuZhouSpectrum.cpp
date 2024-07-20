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




#include "DlgHuZhouSpectrum.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgHuZhouSpectrum.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSHuZhouSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgHuZhouSpectrum */

DlgHuZhouSpectrum::DlgHuZhouSpectrum(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFrequency& LowFrequencyControlFactor, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgHuZhouSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_GroundNaturalFrequency->setUnit(Base::Unit::Frequency);
    ui->doubleSpinBox_LowFrequencyControlFactor->setUnit(Base::Unit::Frequency);

    ui->doubleSpinBox_GroundNaturalFrequency->setValue(GroundNaturalFrequency.getValue());
    ui->doubleSpinBox_GroundDampingRatio->setValue(GroundDampingRatio.getValue());
    ui->doubleSpinBox_LowFrequencyControlFactor->setValue(LowFrequencyControlFactor.getValue());
    ui->doubleSpinBox_GroundShakingIntensity->setValue(ConstantSpectralIntensity.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSHuZhouSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgHuZhouSpectrum::~DlgHuZhouSpectrum()
{
}

void DlgHuZhouSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSHuZhouSpectrum* activefeature = static_cast<SeismicLab::CRPSHuZhouSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->GroundNaturalFrequency.setValue(ui->doubleSpinBox_GroundNaturalFrequency->value().getValue());
    activefeature->GroundDampingRatio.setValue(ui->doubleSpinBox_GroundDampingRatio->value().getValue());
    activefeature->LowFrequencyControlFactor.setValue(ui->doubleSpinBox_LowFrequencyControlFactor->value().getValue());
    activefeature->ConstantSpectralIntensity.setValue(ui->doubleSpinBox_GroundShakingIntensity->value().getValue());
  }

void DlgHuZhouSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgHuZhouSpectrumEdit */

DlgHuZhouSpectrumEdit::DlgHuZhouSpectrumEdit(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFrequency& LowFrequencyControlFactor, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgHuZhouSpectrum(GroundNaturalFrequency,GroundDampingRatio, LowFrequencyControlFactor, ConstantSpectralIntensity, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgHuZhouSpectrumEdit::~DlgHuZhouSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgHuZhouSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgHuZhouSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgHuZhouSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgHuZhouSpectrum.cpp"
