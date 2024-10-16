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




#include "DlgSaragoniHart1974Modulation.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgSaragoniHart1974Modulation.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSSaragoniHart1974Modulation.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgSaragoniHart1974Modulation */

DlgSaragoniHart1974Modulation::DlgSaragoniHart1974Modulation(const App::PropertyFloat& AlphaOne, const App::PropertyFloat& AlphaTow, const App::PropertyFloat& AlphaThree, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgSaragoniHart1974Modulation), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_AlphaOne->setValue(AlphaOne.getValue());
    ui->doubleSpinBox_AlphaTwo->setValue(AlphaTow.getValue());
    ui->doubleSpinBox_AlphaThree->setValue(AlphaThree.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSCloughPenzienSpectrum.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgSaragoniHart1974Modulation::~DlgSaragoniHart1974Modulation()
{
}

void DlgSaragoniHart1974Modulation::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSSaragoniHart1974Modulation* activefeature = static_cast<SeismicLab::CRPSSaragoniHart1974Modulation*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

    activefeature->AlphaOne.setValue(ui->doubleSpinBox_AlphaOne->value().getValue());
    activefeature->AlphaTwo.setValue(ui->doubleSpinBox_AlphaTwo->value().getValue());
    activefeature->AlphaThree.setValue(ui->doubleSpinBox_AlphaThree->value().getValue());
  }

void DlgSaragoniHart1974Modulation::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgSaragoniHart1974ModulationEdit */

DlgSaragoniHart1974ModulationEdit::DlgSaragoniHart1974ModulationEdit(const App::PropertyFloat& AlphaOne, const App::PropertyFloat& AlphaTow, const App::PropertyFloat& AlphaThree, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgSaragoniHart1974Modulation(AlphaOne,AlphaTow, AlphaThree, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgSaragoniHart1974ModulationEdit::~DlgSaragoniHart1974ModulationEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgSaragoniHart1974ModulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgSaragoniHart1974ModulationEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgSaragoniHart1974ModulationEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgSaragoniHart1974Modulation.cpp"
