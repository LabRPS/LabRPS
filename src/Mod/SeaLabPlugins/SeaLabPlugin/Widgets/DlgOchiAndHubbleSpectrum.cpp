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




#include "DlgOchiAndHubbleSpectrum.h"
#include <Mod/SeaLabPlugins/SeaLabPlugin/ui_DlgOchiAndHubbleSpectrum.h>
#include <Mod/SeaLabPlugins/SeaLabPlugin/RPSOchiAndHubbleSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeaLabGui;

/* TRANSLATOR SeaLabGui::DlgOchiAndHubbleSpectrum */

DlgOchiAndHubbleSpectrum::DlgOchiAndHubbleSpectrum(
    const App::PropertyLength& SignificantWaveHeight1,
    const App::PropertyLength& SignificantWaveHeight2,
    const App::PropertyFrequency& PeakFrequency1, const App::PropertyFrequency& PeakFrequency2, const App::PropertyFloat& PeakShape1,
    const App::PropertyFloat& PeakShape2, const App::PropertyBool& AutoPara,
    const App::PropertyLength& SignificantWaveHeight,
    const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgOchiAndHubbleSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_SignificantWaveHeight1->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_SignificantWaveHeight2->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_SignificantWaveHeight->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_PeakFrequency1->setUnit(Base::Unit::Frequency);
    ui->doubleSpinBox_PeakFrequency2->setUnit(Base::Unit::Frequency);

    ui->doubleSpinBox_SignificantWaveHeight1->setValue(SignificantWaveHeight1.getValue());
    ui->doubleSpinBox_SignificantWaveHeight2->setValue(SignificantWaveHeight2.getValue());
    ui->doubleSpinBox_PeakFrequency1->setValue(PeakFrequency1.getValue());
    ui->doubleSpinBox_PeakFrequency2->setValue(PeakFrequency2.getValue());
    ui->doubleSpinBox_PeakShape1->setValue(PeakShape1.getValue());
    ui->doubleSpinBox_PeakShape2->setValue(PeakShape2.getValue());
    ui->GroupBox_AutoPara->setChecked(AutoPara.getValue());
    ui->doubleSpinBox_SignificantWaveHeight->setValue(SignificantWaveHeight.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSOchiAndHubbleSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgOchiAndHubbleSpectrum::~DlgOchiAndHubbleSpectrum()
{
}

void DlgOchiAndHubbleSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeaLab::CRPSOchiAndHubbleSpectrum* activefeature = static_cast<SeaLab::CRPSOchiAndHubbleSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->SignificantWaveHeight1.setValue(ui->doubleSpinBox_SignificantWaveHeight1->value().getValue());
    activefeature->SignificantWaveHeight2.setValue(ui->doubleSpinBox_SignificantWaveHeight2->value().getValue());
    activefeature->PeakFrequency1.setValue(ui->doubleSpinBox_PeakFrequency1->value().getValue());
    activefeature->PeakFrequency2.setValue(ui->doubleSpinBox_PeakFrequency2->value().getValue());
    activefeature->PeakShape1.setValue(ui->doubleSpinBox_PeakShape1->value().getValue());
    activefeature->PeakShape2.setValue(ui->doubleSpinBox_PeakShape2->value().getValue());
    activefeature->AutoPara.setValue(ui->GroupBox_AutoPara->isChecked());
    activefeature->SignificantWaveHeight.setValue(ui->doubleSpinBox_SignificantWaveHeight->value().getValue());


  }

void DlgOchiAndHubbleSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgOchiAndHubbleSpectrumEdit */

DlgOchiAndHubbleSpectrumEdit::DlgOchiAndHubbleSpectrumEdit(
    const App::PropertyLength& SignificantWaveHeight1,
    const App::PropertyLength& SignificantWaveHeight2,
    const App::PropertyFrequency& PeakFrequency1, const App::PropertyFrequency& PeakFrequency2, const App::PropertyFloat& PeakShape1,
    const App::PropertyFloat& PeakShape2, const App::PropertyBool& AutoPara,
    const App::PropertyLength& SignificantWaveHeight,
    const App::PropertyString& featureName)
{
	// create and show dialog for the SeaLabFeatures
    widget = new DlgOchiAndHubbleSpectrum(SignificantWaveHeight1, SignificantWaveHeight2, PeakFrequency1, PeakFrequency2,  PeakShape1, PeakShape2, AutoPara, SignificantWaveHeight, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgOchiAndHubbleSpectrumEdit::~DlgOchiAndHubbleSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgOchiAndHubbleSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgOchiAndHubbleSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgOchiAndHubbleSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgOchiAndHubbleSpectrum.cpp"
