/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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



#include "DlgUniformDistributionLocation.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgUniformDistributionLocation.h>
#include <Mod/WindLabPlugins/WindLabPlugin/WLUniformDistributionLocations.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgUniformLocationDistribution */

DlgUniformLocationDistribution::DlgUniformLocationDistribution(App::PropertyVector& lowestPoint, App::PropertyLength& spacing, const App::PropertyString& featureName, const App::PropertyEnumeration& direction, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui_DlgUniformLocationDistribution), _featureName(featureName.getStrValue())
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

    ui->label_Image->setPixmap(QPixmap(":icons/UniformPointsDistribution0.png"));

    int currentIndex = 0;
    const char** enums = direction.getEnums();
    for (int i = 0; i <= direction.getEnum().maxValue(); ++i) {
        ui->comboBox->addItem(QString::fromUtf8(enums[i]));

        if (QString::fromUtf8(enums[i]) == direction.getValueAsString())
            currentIndex = i;
    }

    ui->comboBox->setCurrentIndex(currentIndex);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgUniformLocationDistribution::~DlgUniformLocationDistribution()
{
}

void DlgUniformLocationDistribution::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    //auto feature = doc->getObject(_featureName.c_str());
    WindLab::WLUniformDistributionLocations* activefeature = static_cast<WindLab::WLUniformDistributionLocations*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    Base::Vector3d lowestPoint(ui->doubleSpinBox_X->value().getValue(), ui->doubleSpinBox_Y->value().getValue(), ui->doubleSpinBox_Z->value().getValue());
    activefeature->FirstPoint.setValue(lowestPoint);
    activefeature->Spacing.setValue(ui->doubleSpinBox_Spacing->value().getValue());
    activefeature->Directions.setValue(ui->comboBox->currentText().toUtf8().constData());
}

void DlgUniformLocationDistribution::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::UniformLocationDistributionDialogEdit */

UniformLocationDistributionDialogEdit::UniformLocationDistributionDialogEdit(App::PropertyVector& lowestPoint, App::PropertyLength& spacing, const App::PropertyString& featureName, const App::PropertyEnumeration& direction)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgUniformLocationDistribution(lowestPoint, spacing, featureName, direction, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

UniformLocationDistributionDialogEdit::~UniformLocationDistributionDialogEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons UniformLocationDistributionDialogEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool UniformLocationDistributionDialogEdit::accept()
{ 
	widget->accept();
	return true;
}

bool UniformLocationDistributionDialogEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgUniformLocationDistribution.cpp"
