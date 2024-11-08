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




#include "DlgDesignResponseSpectrum.h"
#include <Mod/SeismicLabPlugins/DesignResponseSpectrumPlugin/ui_DlgDesignResponseSpectrum.h>
#include <Mod/SeismicLabPlugins/DesignResponseSpectrumPlugin/DesignResponseSpectrum.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgDesignResponseSpectrum */

DlgDesignResponseSpectrum::DlgDesignResponseSpectrum(const App::PropertySpeed& MeanSpeedIncrement,
                                 const App::PropertyInteger& NumberOfBins,
                                 const App::PropertyFloat& ShapeParameter,
                                 const App::PropertyFloat& ScaleParameter,
                                 const App::PropertyBool& UserDefinedWeibullParameters,
                                 const App::PropertyEnumeration& WeibulParametersEstimationMethod,
                                 const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgDesignResponseSpectrum), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_MeanSpeedIncrement->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_NumberOfBins->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ShapeParameter->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_ScaleParameter->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_MeanSpeedIncrement->setValue(MeanSpeedIncrement.getQuantityValue());
    ui->doubleSpinBox_NumberOfBins->setValue(NumberOfBins.getValue());
    ui->doubleSpinBox_ShapeParameter->setValue(ShapeParameter.getValue());
    ui->doubleSpinBox_ScaleParameter->setValue(ScaleParameter.getValue());

    ui->GroupBox_UserDefined->setChecked(UserDefinedWeibullParameters.getValue());

    int currentIndex = 0;
    const char** enums = WeibulParametersEstimationMethod.getEnums();
    for (int i = 0; i <= WeibulParametersEstimationMethod.getEnum().maxValue(); ++i) {
        ui->comboBox->addItem(QString::fromUtf8(enums[i]));

        if (QString::fromUtf8(enums[i]) == WeibulParametersEstimationMethod.getValueAsString())
            currentIndex = i;
    }

    ui->comboBox->setCurrentIndex(currentIndex);
    if (ui->GroupBox_UserDefined->isChecked())
    {
        ui->doubleSpinBox_ShapeParameter->setEnabled(true);
        ui->doubleSpinBox_ScaleParameter->setEnabled(true);
    }
    else
    {
        ui->doubleSpinBox_ShapeParameter->setEnabled(false);
        ui->doubleSpinBox_ScaleParameter->setEnabled(false);
    }

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));

    connect(ui->GroupBox_UserDefined, &QGroupBox::toggled, this, &DlgDesignResponseSpectrum::slotEnableUserDefinedWeibullParameters);

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgDesignResponseSpectrum::~DlgDesignResponseSpectrum()
{
}

void DlgDesignResponseSpectrum::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    SeismicLab::DesignResponseSpectrum* activefeature = static_cast<SeismicLab::DesignResponseSpectrum*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    //activefeature->MeanSpeedIncrement.setValue(ui->doubleSpinBox_MeanSpeedIncrement->value().getValue());
    //activefeature->NumberOfBins.setValue(ui->doubleSpinBox_NumberOfBins->value().getValue());
    //activefeature->ShapeParameter.setValue(ui->doubleSpinBox_ShapeParameter->value().getValue());
    //activefeature->ScaleParameter.setValue(ui->doubleSpinBox_ScaleParameter->value().getValue());
    //activefeature->UserDefinedWeibullParameters.setValue(ui->GroupBox_UserDefined->isChecked());
    //activefeature->WeibulParametersEstimationMethod.setValue(ui->comboBox->currentText().toUtf8().constData());

  }

void DlgDesignResponseSpectrum::reject()
{

}

void DlgDesignResponseSpectrum::slotEnableUserDefinedWeibullParameters() {
    if (ui->GroupBox_UserDefined->isChecked()) {
        ui->doubleSpinBox_ShapeParameter->setEnabled(true);
        ui->doubleSpinBox_ScaleParameter->setEnabled(true);
    }
    else {
        ui->doubleSpinBox_ShapeParameter->setEnabled(false);
        ui->doubleSpinBox_ScaleParameter->setEnabled(false);
    }
}
// ----------------------------------------------

/* TRANSLATOR PartGui::DlgDesignResponseSpectrumEdit */

DlgDesignResponseSpectrumEdit::DlgDesignResponseSpectrumEdit(
    const App::PropertySpeed& MeanSpeedIncrement, const App::PropertyInteger& NumberOfBins,
    const App::PropertyFloat& ShapeParameter, const App::PropertyFloat& ScaleParameter,
    const App::PropertyBool& UserDefinedWeibullParameters,
    const App::PropertyEnumeration& WeibulParametersEstimationMethod,
    const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgDesignResponseSpectrum(
       MeanSpeedIncrement, NumberOfBins,
        ShapeParameter, ScaleParameter,
        UserDefinedWeibullParameters,
        WeibulParametersEstimationMethod, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgDesignResponseSpectrumEdit::~DlgDesignResponseSpectrumEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgDesignResponseSpectrumEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgDesignResponseSpectrumEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgDesignResponseSpectrumEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgDesignResponseSpectrum.cpp"
