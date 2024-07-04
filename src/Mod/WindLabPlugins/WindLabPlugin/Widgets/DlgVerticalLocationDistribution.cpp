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

#include "DlgVerticalLocationDistribution.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgVerticalLocationDistribution.h>
#include <Mod/WindLabPlugins/WindLabPlugin/WLVerticalUniformDistribution.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgVerticalLocationDistribution */

DlgVerticalLocationDistribution::DlgVerticalLocationDistribution(App::PropertyVector& lowestPoint, App::PropertyLength& spacing, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui_DlgVerticalLocationDistribution), _featureName(featureName.getStrValue())
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

    int w = ui->label_Image->width ();
    int h = ui->label_Image->height ();
    QPixmap pix(":icons/PowerMeanProfil.svg");// load pixmap
    //ui->label_Image->setPixmap(QPixmap(":icons/VerticalPointsDistribution1.png"));
    ui->label_Image->setPixmap (pix.scaled (200,60,Qt::KeepAspectRatio));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgVerticalLocationDistribution::~DlgVerticalLocationDistribution()
{
}

void DlgVerticalLocationDistribution::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::CWLVerticalUniformDistribution* activefeature = static_cast<WindLab::CWLVerticalUniformDistribution*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    Base::Vector3d lowestPoint(ui->doubleSpinBox_X->value().getValue(), ui->doubleSpinBox_Y->value().getValue(), ui->doubleSpinBox_Z->value().getValue());
    activefeature->LowestPoint.setValue(lowestPoint);
    activefeature->Spacing.setValue(ui->doubleSpinBox_Spacing->value().getValue());
}

void DlgVerticalLocationDistribution::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::VerticalLocationDistributionDialogEdit */

VerticalLocationDistributionDialogEdit::VerticalLocationDistributionDialogEdit(App::PropertyVector& lowestPoint, App::PropertyLength& spacing, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgVerticalLocationDistribution(lowestPoint, spacing, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

VerticalLocationDistributionDialogEdit::~VerticalLocationDistributionDialogEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons VerticalLocationDistributionDialogEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool VerticalLocationDistributionDialogEdit::accept()
{ 
	widget->accept();
	return true;
}

bool VerticalLocationDistributionDialogEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgVerticalLocationDistribution.cpp"
