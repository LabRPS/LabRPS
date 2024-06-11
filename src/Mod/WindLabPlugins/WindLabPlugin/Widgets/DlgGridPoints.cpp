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



#include "DlgGridPoints.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgGridPoints.h>
#include <Mod/WindLabPlugins/WindLabPlugin/WLGridPoints.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgGridPoints */

DlgGridPoints::DlgGridPoints(App::PropertyPosition& centerPoint, App::PropertyLength& spacing1, App::PropertyLength& spacing2, App::PropertyLength& length1, App::PropertyLength& length2, const App::PropertyEnumeration& locationPlan, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui_DlgGridPoints), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_Length1->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Length2->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Spacing1->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Spacing2->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_X->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Y->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Z->setRange(-DBL_MAX, DBL_MAX);

    ui->doubleSpinBox_X->setValue(centerPoint.getValue().x);
    ui->doubleSpinBox_Y->setValue(centerPoint.getValue().y);
    ui->doubleSpinBox_Z->setValue(centerPoint.getValue().z);
    ui->doubleSpinBox_Spacing1->setValue(spacing1.getQuantityValue());
    ui->doubleSpinBox_Spacing2->setValue(spacing2.getQuantityValue());
    ui->doubleSpinBox_Length1->setValue(length1.getQuantityValue());
    ui->doubleSpinBox_Length2->setValue(length2.getQuantityValue());

    ui->doubleSpinBox_X->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Y->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Z->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Spacing1->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Spacing2->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Length1->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Length2->setUnit(Base::Unit::Length);

    ui->label_Image->setPixmap(QPixmap(":icons/GridPoints.png"));

    int currentIndex = 0;
    const char** enums = locationPlan.getEnums();
    for (int i = 0; i <= locationPlan.getEnum().maxValue(); ++i) {
        ui->comboBox->addItem(QString::fromUtf8(enums[i]));

        if (QString::fromUtf8(enums[i]) == locationPlan.getValueAsString())
            currentIndex = i;
    }

    ui->comboBox->setCurrentIndex(currentIndex);
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
    WindLab::WLGridPoints* activefeature = static_cast<WindLab::WLGridPoints*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    Base::Vector3d lowestPoint(ui->doubleSpinBox_X->value().getValue(), ui->doubleSpinBox_Y->value().getValue(), ui->doubleSpinBox_Z->value().getValue());
    activefeature->CenterPoint.setValue(lowestPoint);
    activefeature->Spacing1.setValue(ui->doubleSpinBox_Spacing1->value().getValue());
    activefeature->Spacing2.setValue(ui->doubleSpinBox_Spacing2->value().getValue());
    activefeature->Length1.setValue(ui->doubleSpinBox_Length1->value().getValue());
    activefeature->Length2.setValue(ui->doubleSpinBox_Length2->value().getValue());

    activefeature->LocationPlan.setValue(ui->comboBox->currentText().toUtf8().constData());
}

void DlgGridPoints::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::GridPointsDialogEdit */

GridPointsDialogEdit::GridPointsDialogEdit(App::PropertyPosition& centerPoint, App::PropertyLength& spacing1, App::PropertyLength& spacing2, App::PropertyLength& length1, App::PropertyLength& length2, const App::PropertyEnumeration& locationPlan, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgGridPoints(centerPoint, spacing1, spacing2, length1, length2, locationPlan, featureName,  nullptr);
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
