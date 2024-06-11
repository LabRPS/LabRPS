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




#include "DlgHorizontalLocationDistribution.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgHorizontalLocationDistribution.h>
#include <Mod/WindLabPlugins/WindLabPlugin/WLHorizontalUniformDistribution.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgHorizontalLocationDistribution */

DlgHorizontalLocationDistribution::DlgHorizontalLocationDistribution(App::PropertyVector& lowestPoint, App::PropertyLength& spacing, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui_DlgHorizontalLocationDistribution), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_X->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Y->setRange(-DBL_MAX, DBL_MAX);
    ui->doubleSpinBox_Z->setRange(10.00, DBL_MAX);
    ui->doubleSpinBox_Spacing->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_X->setValue(lowestPoint.getValue().x);
    ui->doubleSpinBox_Y->setValue(lowestPoint.getValue().y);
    ui->doubleSpinBox_Z->setValue(lowestPoint.getValue().z);
    ui->doubleSpinBox_Spacing->setValue(spacing.getQuantityValue());

    ui->doubleSpinBox_X->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Y->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Z->setUnit(Base::Unit::Length);
    ui->doubleSpinBox_Spacing->setUnit(Base::Unit::Length);



    ui->label_Image->setPixmap(QPixmap(":icons/HorizontalPointsDistribution0.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgHorizontalLocationDistribution::~DlgHorizontalLocationDistribution()
{
}

void DlgHorizontalLocationDistribution::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CWLHorizontalUniformDistribution* activefeature = static_cast<WindLab::CWLHorizontalUniformDistribution*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    Base::Vector3d lowestPoint(ui->doubleSpinBox_X->value().getValue(), ui->doubleSpinBox_Y->value().getValue(), ui->doubleSpinBox_Z->value().getValue());
    activefeature->FirstPoint.setValue(lowestPoint);
    activefeature->Spacing.setValue(ui->doubleSpinBox_Spacing->value().getValue());
}

void DlgHorizontalLocationDistribution::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::HorizontalLocationDistributionDialogEdit */

HorizontalLocationDistributionDialogEdit::HorizontalLocationDistributionDialogEdit(App::PropertyVector& lowestPoint, App::PropertyLength& spacing, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgHorizontalLocationDistribution(lowestPoint, spacing, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

HorizontalLocationDistributionDialogEdit::~HorizontalLocationDistributionDialogEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons HorizontalLocationDistributionDialogEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool HorizontalLocationDistributionDialogEdit::accept()
{ 
	widget->accept();
	return true;
}

bool HorizontalLocationDistributionDialogEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgHorizontalLocationDistribution.cpp"
