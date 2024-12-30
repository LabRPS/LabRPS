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

#include "DlgGridPoints.h"
#include <Mod/SeaLabPlugins/SeaLabPlugin/ui_DlgGridPoints.h>
#include <Mod/SeaLabPlugins/SeaLabPlugin/WLGridPoints.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace SeaLabGui;

/* TRANSLATOR SeaLabGui::DlgGridPoints */

DlgGridPoints::DlgGridPoints(const App::PropertyPosition& startPoint, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui_DlgGridPoints), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_X->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Y->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Z->setRange(-DBL_MAX, DBL_MAX);

    ui->doubleSpinBox_X->setValue(startPoint.getValue().x);
    ui->doubleSpinBox_Y->setValue(startPoint.getValue().y);
    ui->doubleSpinBox_Z->setValue(startPoint.getValue().z);

    ui->label_Image->setPixmap(QPixmap(":icons/GridPoints.png"));

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgGridPoints::~DlgGridPoints()
{
}

void DlgGridPoints::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    SeaLab::WLGridPoints* activefeature = static_cast<SeaLab::WLGridPoints*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    Base::Vector3d lowestPoint(ui->doubleSpinBox_X->value().getValue(), ui->doubleSpinBox_Y->value().getValue(), ui->doubleSpinBox_Z->value().getValue());
    activefeature->GridStartingPoint.setValue(lowestPoint);

}

void DlgGridPoints::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::GridPointsDialogEdit */

GridPointsDialogEdit::GridPointsDialogEdit(const App::PropertyPosition& startPoint, const App::PropertyString& featureName)
{
	// create and show dialog for the SeaLabFeatures
    widget = new DlgGridPoints(startPoint, featureName,  nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

GridPointsDialogEdit::~GridPointsDialogEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons GridPointsDialogEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool GridPointsDialogEdit::accept()
{ 
	widget->accept();
	return true;
}

bool GridPointsDialogEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgGridPoints.cpp"
