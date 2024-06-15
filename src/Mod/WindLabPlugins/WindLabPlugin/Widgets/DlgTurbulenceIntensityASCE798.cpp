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




#include "DlgTurbulenceIntensityASCE798.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgTurbulenceIntensityASCE798.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSTurbulenceIntensityASCE798.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgTurbulenceIntensityASCE798 */

DlgTurbulenceIntensityASCE798::DlgTurbulenceIntensityASCE798(const App::PropertyFloat& TurbulenceIntensity, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgTurbulenceIntensityASCE798), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_TurbulenceIntensity10->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_TurbulenceIntensity10->setValue(TurbulenceIntensity.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/TurbulenceIntensityASCE798.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgTurbulenceIntensityASCE798::~DlgTurbulenceIntensityASCE798()
{
}

void DlgTurbulenceIntensityASCE798::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::RPSTurbulenceIntensityASCE798* activefeature = static_cast<WindLab::RPSTurbulenceIntensityASCE798*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->TenMetersHighTurbulenceIntensity.setValue(ui->doubleSpinBox_TurbulenceIntensity10->value().getValue());


  }

void DlgTurbulenceIntensityASCE798::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgTurbulenceIntensityASCE798Edit */

DlgTurbulenceIntensityASCE798Edit::DlgTurbulenceIntensityASCE798Edit(const App::PropertyFloat& IntegralLengthScale, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgTurbulenceIntensityASCE798(IntegralLengthScale, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgTurbulenceIntensityASCE798Edit::~DlgTurbulenceIntensityASCE798Edit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgTurbulenceIntensityASCE798Edit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgTurbulenceIntensityASCE798Edit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgTurbulenceIntensityASCE798Edit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgTurbulenceIntensityASCE798.cpp"
