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




#include "DlgTorsethaugenSpectrum.h"
#include <Mod/SeaLabPlugins/SeaLabPlugin/ui_DlgTorsethaugenSpectrum.h>
#include <Mod/SeaLabPlugins/SeaLabPlugin/RPSTorsethaugenSpectrum.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeaLabGui;

/* TRANSLATOR SeaLabGui::DlgTorsethaugenSpectrum */

DlgTorsethaugenSpectrum::DlgTorsethaugenSpectrum(const App::PropertyLength&  SignificantWaveHeight, const App::PropertyTime&  PeakPeriod, const App::PropertyBool&  AutoGamma, const App::PropertyBool& AutoSigma, const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2, const App::PropertyBool& DoublePeaks, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgTorsethaugenSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_SignificantWaveHeight->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_PeakPeriod->setUnit(Base::Unit::TimeSpan);

    ui->doubleSpinBox_SignificantWaveHeight->setValue(SignificantWaveHeight.getValue());
    ui->doubleSpinBox_PeakPeriod->setValue(PeakPeriod.getValue());
    ui->GroupBox_AutoGamma->setChecked(AutoGamma.getValue());
    ui->GroupBox_AutoSigma->setChecked(AutoSigma.getValue());
    ui->doubleSpinBox_Gamma->setValue(Gamma.getValue());
    ui->doubleSpinBox_Sigma1->setValue(Sigma1.getValue());
    ui->doubleSpinBox_Sigma2->setValue(Sigma2.getValue());
    ui->checkBox_DoublePeak->setChecked(DoublePeaks.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSTorsethaugenSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgTorsethaugenSpectrum::~DlgTorsethaugenSpectrum()
{
}

void DlgTorsethaugenSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeaLab::CRPSTorsethaugenSpectrum* activefeature = static_cast<SeaLab::CRPSTorsethaugenSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->SignificantWaveHeight.setValue(ui->doubleSpinBox_SignificantWaveHeight->value().getValue());
    activefeature->PeakPeriod.setValue(ui->doubleSpinBox_PeakPeriod->value().getValue());
    activefeature->AutoGamma.setValue(ui->GroupBox_AutoGamma->isChecked());
    activefeature->Gamma.setValue(ui->doubleSpinBox_Gamma->value().getValue());
    activefeature->AutoSigma.setValue(ui->GroupBox_AutoSigma->isChecked());
    activefeature->Sigma1.setValue(ui->doubleSpinBox_Sigma1->value().getValue());
    activefeature->Sigma2.setValue(ui->doubleSpinBox_Sigma2->value().getValue());
    activefeature->DoublePeaks.setValue(ui->checkBox_DoublePeak->isChecked());


  }

void DlgTorsethaugenSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgTorsethaugenSpectrumEdit */

DlgTorsethaugenSpectrumEdit::DlgTorsethaugenSpectrumEdit(const App::PropertyLength&  SignificantWaveHeight, const App::PropertyTime&  PeakPeriod, const App::PropertyBool&  AutoGamma, const App::PropertyBool& AutoSigma, const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2, const App::PropertyBool& DoublePeaks, const App::PropertyString& featureName)
{
	// create and show dialog for the SeaLabFeatures
    widget = new DlgTorsethaugenSpectrum(SignificantWaveHeight, PeakPeriod, AutoGamma, AutoSigma, Gamma, Sigma1, Sigma2, DoublePeaks, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgTorsethaugenSpectrumEdit::~DlgTorsethaugenSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgTorsethaugenSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgTorsethaugenSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgTorsethaugenSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgTorsethaugenSpectrum.cpp"
