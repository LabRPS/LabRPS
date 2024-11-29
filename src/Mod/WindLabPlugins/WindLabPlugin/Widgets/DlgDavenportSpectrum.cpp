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

#include "DlgDavenportSpectrum.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgDavenportSpectrum.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSDavenportSpectrum.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>



using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgDavenportSpectrum */

DlgDavenportSpectrum::DlgDavenportSpectrum(const App::PropertySpeed& MeanWindSpeed10, const App::PropertySpeed& ShearVelocity, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgDavenportSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_MeanWindSpeed10->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ShearVelocity->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_MeanWindSpeed10->setValue(MeanWindSpeed10.getValue());
    ui->doubleSpinBox_ShearVelocity->setValue(ShearVelocity.getValue());

    ui->doubleSpinBox_MeanWindSpeed10->setUnit(Base::Unit::Velocity);
    ui->doubleSpinBox_ShearVelocity->setUnit(Base::Unit::Velocity);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgDavenportSpectrum::~DlgDavenportSpectrum()
{
}

void DlgDavenportSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CRPSDavenportSpectrum* activefeature = static_cast<WindLab::CRPSDavenportSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->MeanWindSpeed10.setValue(ui->doubleSpinBox_MeanWindSpeed10->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_ShearVelocity->value().getValue());

  }

void DlgDavenportSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgDavenportSpectrumEdit */

DlgDavenportSpectrumEdit::DlgDavenportSpectrumEdit(const App::PropertySpeed& MeanWindSpeed10, const App::PropertySpeed& ShearVelocity, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgDavenportSpectrum(MeanWindSpeed10, ShearVelocity, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgDavenportSpectrumEdit::~DlgDavenportSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgDavenportSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgDavenportSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgDavenportSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgDavenportSpectrum.cpp"
