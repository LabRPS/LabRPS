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




#include "DlgHarrisSpectrum.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgHarrisSpectrum.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSHarrisSpectrum.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgHarrisSpectrum */

DlgHarrisSpectrum::DlgHarrisSpectrum(const App::PropertySpeed& MeanWindSpeed10, const App::PropertySpeed& ShearVelocity, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgHarrisSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_MeanWindSpeed10->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ShearVelocity->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_MeanWindSpeed10->setValue(MeanWindSpeed10.getValue());
    ui->doubleSpinBox_ShearVelocity->setValue(ShearVelocity.getValue());

    ui->doubleSpinBox_MeanWindSpeed10->setUnit(Base::Unit::Velocity);
    ui->doubleSpinBox_ShearVelocity->setUnit(Base::Unit::Velocity);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSHarrisSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgHarrisSpectrum::~DlgHarrisSpectrum()
{
}

void DlgHarrisSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CRPSHarrisSpectrum* activefeature = static_cast<WindLab::CRPSHarrisSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->MeanWindSpeed10.setValue(ui->doubleSpinBox_MeanWindSpeed10->value().getValue());
    activefeature->ShearVelocity.setValue(ui->doubleSpinBox_ShearVelocity->value().getValue());

  }

void DlgHarrisSpectrum::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgHarrisSpectrumEdit */

DlgHarrisSpectrumEdit::DlgHarrisSpectrumEdit(const App::PropertySpeed& MeanWindSpeed10, const App::PropertySpeed& ShearVelocity, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgHarrisSpectrum(MeanWindSpeed10, ShearVelocity, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgHarrisSpectrumEdit::~DlgHarrisSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgHarrisSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgHarrisSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgHarrisSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgHarrisSpectrum.cpp"
