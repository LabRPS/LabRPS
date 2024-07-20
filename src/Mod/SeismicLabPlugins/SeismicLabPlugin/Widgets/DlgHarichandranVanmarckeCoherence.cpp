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




#include "DlgHarichandranVanmarckeCoherence.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgHarichandranVanmarckeCoherence.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSHarichandranVanmarckeCoherence.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>

using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgHarichandranVanmarckeCoherence */

DlgHarichandranVanmarckeCoherence::DlgHarichandranVanmarckeCoherence(const App::PropertyFloat& parameterA, const App::PropertyFloat& parameterAlpha, const App::PropertyLength& parameterK, const App::PropertyFrequency& parameterOmegaZero, const App::PropertyFloat& parameterB, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgHarichandranVanmarckeCoherence), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ParameterA->setValue(parameterA.getValue());
    ui->doubleSpinBox_ParameterAlpha->setValue(parameterAlpha.getValue());
    ui->doubleSpinBox_ParameterK->setValue(parameterK.getValue());
    ui->doubleSpinBox_ParameterOmegaZero->setValue(parameterOmegaZero.getValue());
    ui->doubleSpinBox_ParameterB->setValue(parameterB.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSHarichandranVanmarckeCoherence.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgHarichandranVanmarckeCoherence::~DlgHarichandranVanmarckeCoherence()
{
}

void DlgHarichandranVanmarckeCoherence::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSHarichandranVanmarckeCoherence* activefeature = static_cast<SeismicLab::CRPSHarichandranVanmarckeCoherence*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->ParameterA.setValue(ui->doubleSpinBox_ParameterA->value().getValue());
    activefeature->ParameterAlpha.setValue(ui->doubleSpinBox_ParameterAlpha->value().getValue());
    activefeature->ParameterK.setValue(ui->doubleSpinBox_ParameterK->value().getValue());
    activefeature->ParameterOmegaZero.setValue(ui->doubleSpinBox_ParameterOmegaZero->value().getValue());
    activefeature->ParameterB.setValue(ui->doubleSpinBox_ParameterB->value().getValue());
  }

void DlgHarichandranVanmarckeCoherence::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgHarichandranVanmarckeCoherenceEdit */

DlgHarichandranVanmarckeCoherenceEdit::DlgHarichandranVanmarckeCoherenceEdit(const App::PropertyFloat& parameterA, const App::PropertyFloat& parameterAlpha, const App::PropertyLength& parameterK, const App::PropertyFrequency& parameterOmegaZero, const App::PropertyFloat& parameterB, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgHarichandranVanmarckeCoherence(parameterA, parameterAlpha, parameterK, parameterOmegaZero, parameterB, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgHarichandranVanmarckeCoherenceEdit::~DlgHarichandranVanmarckeCoherenceEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgHarichandranVanmarckeCoherenceEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgHarichandranVanmarckeCoherenceEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgHarichandranVanmarckeCoherenceEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgHarichandranVanmarckeCoherence.cpp"
