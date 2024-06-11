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




#include "DlgKrenkCoherence.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgKrenkCoherence.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSKrenkCoherence.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgKrenkCoherence */

DlgKrenkCoherence::DlgKrenkCoherence(const App::PropertyFloat& IntegralLengthScale, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgKrenkCoherence), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_IntegralLengthScale->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_IntegralLengthScale->setValue(IntegralLengthScale.getValue());
    ui->doubleSpinBox_IntegralLengthScale->setUnit(Base::Unit::Length);

    ui->label_Image->setPixmap(QPixmap(":icons/KrenkCoherence.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgKrenkCoherence::~DlgKrenkCoherence()
{
}

void DlgKrenkCoherence::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::RPSKrenkCoherence* activefeature = static_cast<WindLab::RPSKrenkCoherence*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->IntegralLengthScale.setValue(ui->doubleSpinBox_IntegralLengthScale->value().getValue());


  }

void DlgKrenkCoherence::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgKrenkCoherenceEdit */

DlgKrenkCoherenceEdit::DlgKrenkCoherenceEdit(const App::PropertyFloat& IntegralLengthScale, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgKrenkCoherence(IntegralLengthScale, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgKrenkCoherenceEdit::~DlgKrenkCoherenceEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgKrenkCoherenceEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgKrenkCoherenceEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgKrenkCoherenceEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgKrenkCoherence.cpp"
