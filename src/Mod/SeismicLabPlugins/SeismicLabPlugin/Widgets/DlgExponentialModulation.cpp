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




#include "DlgExponentialModulation.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgExponentialModulation.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSExponentialModulation.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgExponentialModulation */

DlgExponentialModulation::DlgExponentialModulation(const App::PropertyFloat& Alpha, const App::PropertyFloat& Beta, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgExponentialModulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_Alpha->setValue(Alpha.getValue());
    ui->doubleSpinBox_Beta->setValue(Beta.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSCloughPenzienSpectrum.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgExponentialModulation::~DlgExponentialModulation()
{
}

void DlgExponentialModulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSExponentialModulation* activefeature = static_cast<SeismicLab::CRPSExponentialModulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->Alpha.setValue(ui->doubleSpinBox_Alpha->value().getValue());
    activefeature->Beta.setValue(ui->doubleSpinBox_Beta->value().getValue());

  }

void DlgExponentialModulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgExponentialModulationEdit */

DlgExponentialModulationEdit::DlgExponentialModulationEdit(const App::PropertyFloat& Alpha, const App::PropertyFloat& Beta, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgExponentialModulation(Alpha,Beta, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgExponentialModulationEdit::~DlgExponentialModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgExponentialModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgExponentialModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgExponentialModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgExponentialModulation.cpp"
