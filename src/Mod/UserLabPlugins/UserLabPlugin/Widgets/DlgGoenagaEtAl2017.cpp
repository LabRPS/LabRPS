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

#include "DlgGoenagaEtAl2017.h"
#include <Mod/UserLabPlugins/UserLabPlugin/ui_DlgGoenagaEtAl2017.h>
#include <Mod/UserLabPlugins/UserLabPlugin/RPSGoenagaEtAl2017.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace UserLabGui;

/* TRANSLATOR UserLabGui::DlgGoenagaEtAl2017 */

DlgGoenagaEtAl2017::DlgGoenagaEtAl2017(const App::PropertyFloat& ReferenceWaveNumber,
                                       const App::PropertyFloat& ReferenceSpectrum,
                                       const App::PropertyFloat& PavementWavinessIndicator,
                       const App::PropertyString& featureName, 
                       QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgGoenagaEtAl2017), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);


    ui->doubleSpinBox_ReferenceWaveNumber->setValue(ReferenceWaveNumber.getValue());
    ui->doubleSpinBox_ReferenceSpectrum->setValue(ReferenceSpectrum.getValue());
    ui->doubleSpinBox_PavementWavinessIndicator->setValue(PavementWavinessIndicator.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgGoenagaEtAl2017::~DlgGoenagaEtAl2017()
{
}

void DlgGoenagaEtAl2017::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    UserLab::CRPSGoenagaEtAl2017* activefeature = static_cast<UserLab::CRPSGoenagaEtAl2017*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

     activefeature->ReferenceWaveNumber.setValue(ui->doubleSpinBox_ReferenceWaveNumber->value().getValue());
     activefeature->ReferenceSpectrum.setValue(ui->doubleSpinBox_ReferenceSpectrum->value().getValue());
     activefeature->PavementWavinessIndicator.setValue(ui->doubleSpinBox_PavementWavinessIndicator->value().getValue());

  }

void DlgGoenagaEtAl2017::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgGoenagaEtAl2017Edit */

DlgGoenagaEtAl2017Edit::DlgGoenagaEtAl2017Edit(const App::PropertyFloat& ReferenceWaveNumber,
                                               const App::PropertyFloat& ReferenceSpectrum,
                                               const App::PropertyFloat& PavementWavinessIndicator,
    const App::PropertyString& featureName)
{
	// create and show dialog for the UserLabFeatures
    widget = new DlgGoenagaEtAl2017(ReferenceWaveNumber, ReferenceSpectrum, PavementWavinessIndicator, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
   
}

DlgGoenagaEtAl2017Edit::~DlgGoenagaEtAl2017Edit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgGoenagaEtAl2017Edit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgGoenagaEtAl2017Edit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgGoenagaEtAl2017Edit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgGoenagaEtAl2017.cpp"
