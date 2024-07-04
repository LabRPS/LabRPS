
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

#include "DlgUniformRandomPhases.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgUniformRandomPhases.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSUniformRandomPhases.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgUniformRandomPhases */

DlgUniformRandomPhases::DlgUniformRandomPhases(const App::PropertyFloat& MinimumValue, const App::PropertyFloat& MaximumValue, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgUniformRandomPhases), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_MinValue->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_MaxValue->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_MinValue->setValue(MinimumValue.getValue());
    ui->doubleSpinBox_MaxValue->setValue(MaximumValue.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSUniformRandomPhases.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgUniformRandomPhases::~DlgUniformRandomPhases()
{
}

void DlgUniformRandomPhases::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CRPSUniformRandomPhases* activefeature = static_cast<WindLab::CRPSUniformRandomPhases*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->MinimumValue.setValue(ui->doubleSpinBox_MinValue->value().getValue());
    activefeature->MaximumValue.setValue(ui->doubleSpinBox_MaxValue->value().getValue());

  }

void DlgUniformRandomPhases::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgUniformRandomPhasesEdit */

DlgUniformRandomPhasesEdit::DlgUniformRandomPhasesEdit(const App::PropertyFloat& MinimumValue, const App::PropertyFloat& MaximumValue, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgUniformRandomPhases(MinimumValue, MaximumValue, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgUniformRandomPhasesEdit::~DlgUniformRandomPhasesEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgUniformRandomPhasesEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgUniformRandomPhasesEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgUniformRandomPhasesEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgUniformRandomPhases.cpp"
