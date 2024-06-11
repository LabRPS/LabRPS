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




#include "DlgDavenportCoherence.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgDavenportCoherence.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSDavenportCoherence.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgDavenportCoherence */

DlgDavenportCoherence::DlgDavenportCoherence(const App::PropertyFloat& ExponentialDecayCx, const App::PropertyFloat& ExponentialDecayCy, const App::PropertyFloat& ExponentialDecayCz, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgDavenportCoherence), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_ExponentialDecayCx->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ExponentialDecayCy->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ExponentialDecayCz->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_ExponentialDecayCx->setValue(ExponentialDecayCx.getValue());
    ui->doubleSpinBox_ExponentialDecayCy->setValue(ExponentialDecayCy.getValue());
    ui->doubleSpinBox_ExponentialDecayCz->setValue(ExponentialDecayCz.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgDavenportCoherence::~DlgDavenportCoherence()
{
}

void DlgDavenportCoherence::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CRPSDavenportCoherence* activefeature = static_cast<WindLab::CRPSDavenportCoherence*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->ExponentialDecayCx.setValue(ui->doubleSpinBox_ExponentialDecayCx->value().getValue());
    activefeature->ExponentialDecayCy.setValue(ui->doubleSpinBox_ExponentialDecayCy->value().getValue());
    activefeature->ExponentialDecayCz.setValue(ui->doubleSpinBox_ExponentialDecayCz->value().getValue());

  }

void DlgDavenportCoherence::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgDavenportCoherenceEdit */

DlgDavenportCoherenceEdit::DlgDavenportCoherenceEdit(const App::PropertyFloat& ExponentialDecayCx, const App::PropertyFloat& ExponentialDecayCy, const App::PropertyFloat& ExponentialDecayCz, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgDavenportCoherence(ExponentialDecayCx,ExponentialDecayCy, ExponentialDecayCz, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgDavenportCoherenceEdit::~DlgDavenportCoherenceEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgDavenportCoherenceEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgDavenportCoherenceEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgDavenportCoherenceEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgDavenportCoherence.cpp"
