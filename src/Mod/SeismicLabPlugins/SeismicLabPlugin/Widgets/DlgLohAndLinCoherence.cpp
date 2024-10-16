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




#include "DlgLohAndLinCoherence.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgLohAndLinCoherence.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSLohAndLinCoherence.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgLohAndLinCoherence */

DlgLohAndLinCoherence::DlgLohAndLinCoherence(const App::PropertyFloat& ParameterAlpha, const App::PropertyFloat& ParameterB, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgLohAndLinCoherence), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ParameterAlpha->setValue(ParameterAlpha.getValue());
    ui->doubleSpinBox_ParameterB->setValue(ParameterB.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSLohAndLinCoherence.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgLohAndLinCoherence::~DlgLohAndLinCoherence()
{
}

void DlgLohAndLinCoherence::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSLohAndLinCoherence* activefeature = static_cast<SeismicLab::CRPSLohAndLinCoherence*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->ParameterAlpha.setValue(ui->doubleSpinBox_ParameterAlpha->value().getValue());
    activefeature->ParameterB.setValue(ui->doubleSpinBox_ParameterB->value().getValue());
  }

void DlgLohAndLinCoherence::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgLohAndLinCoherenceEdit */

DlgLohAndLinCoherenceEdit::DlgLohAndLinCoherenceEdit(const App::PropertyFloat& ParameterAlpha, const App::PropertyFloat& ParameterB, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgLohAndLinCoherence(ParameterAlpha, ParameterB, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgLohAndLinCoherenceEdit::~DlgLohAndLinCoherenceEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgLohAndLinCoherenceEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgLohAndLinCoherenceEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgLohAndLinCoherenceEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgLohAndLinCoherence.cpp"
