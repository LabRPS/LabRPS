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




#include "DlgKanaiTajimiSpectrum.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgKanaiTajimiSpectrum.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSKanaiTajimiSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgKanaiTajimiSpectrum */

DlgKanaiTajimiSpectrum::DlgKanaiTajimiSpectrum(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgKanaiTajimiSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_GroundNaturalFrequency->setUnit(Base::Unit::Frequency);

    ui->doubleSpinBox_GroundNaturalFrequency->setValue(GroundNaturalFrequency.getValue());
    ui->doubleSpinBox_GroundDampingRatio->setValue(GroundDampingRatio.getValue());
    ui->doubleSpinBox_GroundShakingIntensity->setValue(ConstantSpectralIntensity.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSKanaiTajimiSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgKanaiTajimiSpectrum::~DlgKanaiTajimiSpectrum()
{
}

void DlgKanaiTajimiSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSKanaiTajimiSpectrum* activefeature = static_cast<SeismicLab::CRPSKanaiTajimiSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->GroundNaturalFrequency.setValue(ui->doubleSpinBox_GroundNaturalFrequency->value().getValue());
    activefeature->GroundDampingRatio.setValue(ui->doubleSpinBox_GroundDampingRatio->value().getValue());
    activefeature->ConstantSpectralIntensity.setValue(ui->doubleSpinBox_GroundShakingIntensity->value().getValue());
  }

void DlgKanaiTajimiSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgKanaiTajimiSpectrumEdit */

DlgKanaiTajimiSpectrumEdit::DlgKanaiTajimiSpectrumEdit(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgKanaiTajimiSpectrum(GroundNaturalFrequency,GroundDampingRatio, ConstantSpectralIntensity, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgKanaiTajimiSpectrumEdit::~DlgKanaiTajimiSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgKanaiTajimiSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgKanaiTajimiSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgKanaiTajimiSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgKanaiTajimiSpectrum.cpp"
