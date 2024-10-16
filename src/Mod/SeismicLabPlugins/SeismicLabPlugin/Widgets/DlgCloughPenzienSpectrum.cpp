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




#include "DlgCloughPenzienSpectrum.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgCloughPenzienSpectrum.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSCloughPenzienSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgCloughPenzienSpectrum */

DlgCloughPenzienSpectrum::DlgCloughPenzienSpectrum(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFrequency& SecondFilterLayerFrequency, const App::PropertyFloat& SecondFilterLayerDampingRatio, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgCloughPenzienSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_GroundNaturalFrequency->setUnit(Base::Unit::Frequency);
    ui->doubleSpinBox_SecondFilterLayerFrequency->setUnit(Base::Unit::Frequency);

    ui->doubleSpinBox_GroundNaturalFrequency->setValue(GroundNaturalFrequency.getValue());
    ui->doubleSpinBox_GroundDampingRatio->setValue(GroundDampingRatio.getValue());
    ui->doubleSpinBox_SecondFilterLayerFrequency->setValue(SecondFilterLayerFrequency.getValue());
    ui->doubleSpinBox_SecondFilterLayerDampingRatio->setValue(SecondFilterLayerDampingRatio.getValue());
    ui->doubleSpinBox_GroundShakingIntensity->setValue(ConstantSpectralIntensity.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSCloughPenzienSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgCloughPenzienSpectrum::~DlgCloughPenzienSpectrum()
{
}

void DlgCloughPenzienSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSCloughPenzienSpectrum* activefeature = static_cast<SeismicLab::CRPSCloughPenzienSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->GroundNaturalFrequency.setValue(ui->doubleSpinBox_GroundNaturalFrequency->value().getValue());
    activefeature->GroundDampingRatio.setValue(ui->doubleSpinBox_GroundDampingRatio->value().getValue());
    activefeature->SecondFilterLayerFrequency.setValue(ui->doubleSpinBox_SecondFilterLayerFrequency->value().getValue());
    activefeature->SecondFilterLayerDampingRatio.setValue(ui->doubleSpinBox_SecondFilterLayerDampingRatio->value().getValue());
    activefeature->ConstantSpectralIntensity.setValue(ui->doubleSpinBox_GroundShakingIntensity->value().getValue());
  }

void DlgCloughPenzienSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgCloughPenzienSpectrumEdit */

DlgCloughPenzienSpectrumEdit::DlgCloughPenzienSpectrumEdit(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFrequency& SecondFilterLayerFrequency, const App::PropertyFloat& SecondFilterLayerDampingRatio, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgCloughPenzienSpectrum(GroundNaturalFrequency,GroundDampingRatio, SecondFilterLayerFrequency, SecondFilterLayerDampingRatio, ConstantSpectralIntensity, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgCloughPenzienSpectrumEdit::~DlgCloughPenzienSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgCloughPenzienSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgCloughPenzienSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgCloughPenzienSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgCloughPenzienSpectrum.cpp"
