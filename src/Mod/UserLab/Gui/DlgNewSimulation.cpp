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

#include "PreCompiled.h"
#ifndef _PreComp_
#include <GC_MakeArcOfCircle.hxx>
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <QMessageBox>
#include <QSignalMapper>
#endif

#include <App/Application.h>
#include <App/Document.h>
#include <Base/Tools.h>
#include <Base/UnitsApi.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/Command.h>
#include <Gui/TaskView/TaskView.h>

#include "DlgNewSimulation.h"
#include <Mod/UserLab/Gui/UserLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/UserLab/App/UserLabSimulation.h>
#include <Mod/UserLabAPI/App/RPS.h>
#include "Ui_DlgNewSimulation.h"
#include "ui_DlgUserLabFeatures.h"
#include <App/DocumentObjectGroup.h>
#include <Mod/UserLab/App/UserLabUtils.h>
using namespace UserLabGui;

DlgNewSimulation::DlgNewSimulation(QWidget* parent,  UserLab::UserLabSimulation* sim)
	: QWidget(parent)
	, ui(new Ui_DlgNewSimulation)
	, userFeaturePtr(sim)
{
	ui->setupUi(this);

	connect(ui->stationaryRadioButton, SIGNAL(toggled(bool)),
		this, SLOT(radioButtonStationarityToggled(bool)));

	connect(ui->nonStationaryRadioButton, SIGNAL(toggled(bool)),
		this, SLOT(radioButtonNonStationarityToggled(bool)));

	connect(ui->uniformModulationRadioButton, SIGNAL(toggled(bool)),
		this, SLOT(radioButtonUniformModulationToggled(bool)));

	connect(ui->generalModulationRadioButton, SIGNAL(toggled(bool)),
		this, SLOT(radioButtonNonGeneralModulationToggled(bool)));

	connect(ui->gaussionRadioButton, SIGNAL(toggled(bool)),
		this, SLOT(radioButtonGaussianityToggled(bool)));

	connect(ui->nonGaussianRadioButton, SIGNAL(toggled(bool)),
		this, SLOT(radioButtonNonGaussianityToggled(bool)));

	int min = 1;

	UserLabAPI::UserLabSimulationData* simData = nullptr;

	if (sim)
	{
		simData = sim->getSimulationData();
		ui->NameLineEdit->setText(QString::fromLatin1(sim->Label.getValue()));
		ui->NameLineEdit->setEnabled(FALSE);
	}
	else
	{
		simData = new UserLabAPI::UserLabSimulationData();
		ui->NameLineEdit->setText(QString::fromLatin1("UserDefined"));
	}


	//number of wind process
	ui->numberOfProcessSpinBox->setMinimum(1);
	ui->numberOfProcessSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->numberOfProcessSpinBox->setValue(simData->numberOfSpatialPosition.getValue());

	//sample
	ui->numberOfSampleSpinBox->setMinimum(1);
	ui->numberOfSampleSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->numberOfSampleSpinBox->setValue(simData->numberOfSample.getValue());

	//stationarity and modulation
	if (true == simData->stationarity.getValue())
	{
		ui->stationaryRadioButton->setChecked(Qt::Checked);
		ui->uniformModulationRadioButton->setEnabled(false);
		ui->generalModulationRadioButton->setEnabled(false);

	}
	else
	{
		ui->nonStationaryRadioButton->setChecked(Qt::Checked);
		ui->uniformModulationRadioButton->setEnabled(true);
		ui->generalModulationRadioButton->setEnabled(true);
	}

	//gaussianity
	if (true == simData->uniformModulation.getValue())
	{
		ui->uniformModulationRadioButton->setChecked(Qt::Checked);
	}
	else
	{
		ui->generalModulationRadioButton->setChecked(Qt::Checked);
	}

	if (true == gaussianity)
	{
		ui->gaussionRadioButton->setChecked(Qt::Checked);
	}
	else
	{
		ui->nonGaussianRadioButton->setChecked(Qt::Checked);
	}

	//time discretization
	ui->timeNumberSpinBox->setMinimum(0);
	ui->timeNumberSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->timeNumberSpinBox->setValue(simData->numberOfTimeIncrements.getValue());

	ui->timeMinSpinBox->setMinimum(0.00);
	ui->timeMinSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->timeMinSpinBox->setValue(simData->minTime.getQuantityValue().getValueAs(Base::Quantity::Second));
	ui->timeMinSpinBox->setUnit(Base::Unit::TimeSpan);

	ui->timeMaxSpinBox->setMinimum(0.00);
	ui->timeMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->timeMaxSpinBox->setValue(simData->maxTime.getValue());
	ui->timeMaxSpinBox->setUnit(Base::Unit::TimeSpan);

	ui->timeIncrementSpinBox->setMinimum(0.00);
	ui->timeIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->timeIncrementSpinBox->setValue(simData->timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second));
	ui->timeIncrementSpinBox->setUnit(Base::Unit::TimeSpan);

	//frequency discretization
	ui->frequencyNumberSpinBox->setMinimum(1);
	ui->frequencyNumberSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->frequencyNumberSpinBox->setValue(simData->numberOfFrequency.getValue());

	ui->frequencyMinSpinBox->setMinimum(0.00);
	ui->frequencyMinSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyMinSpinBox->setValue(simData->minFrequency.getQuantityValue().getValueAs(Base::Quantity::Hertz));
	ui->frequencyMinSpinBox->setUnit(Base::Unit::Frequency);

	ui->frequencyMaxSpinBox->setMinimum(0.00);
	ui->frequencyMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyMaxSpinBox->setValue(simData->maxFrequency.getQuantityValue().getValueAs(Base::Quantity::Hertz));
	ui->frequencyMaxSpinBox->setUnit(Base::Unit::Frequency);

	ui->frequencyIncrementSpinBox->setMinimum(0.00);
	ui->frequencyIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyIncrementSpinBox->setValue(simData->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::Hertz));
	ui->frequencyIncrementSpinBox->setUnit(Base::Unit::Frequency);

	//wave length discretization
	ui->waveNumberOfIncrementSpinBox->setMinimum(1);
	ui->waveNumberOfIncrementSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->waveNumberOfIncrementSpinBox->setValue(simData->numberOfWaveLengthIncrements.getValue());

	ui->waveMinLengthSpinBox->setMinimum(0.00);
	ui->waveMinLengthSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->waveMinLengthSpinBox->setValue(simData->minWaveLength.getQuantityValue().getValueAs(Base::Quantity::Metre));
	ui->waveMinLengthSpinBox->setUnit(Base::Unit(-1));

	ui->waveMaxLengthSpinBox->setMinimum(0.00);
	ui->waveMaxLengthSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->waveMaxLengthSpinBox->setValue(simData->maxWaveLength.getQuantityValue().getValueAs(Base::Quantity::Metre));
	ui->waveMaxLengthSpinBox->setUnit(Base::Unit(-1));

	ui->waveLengthIncrementSpinBox->setMinimum(0.00);
	ui->waveLengthIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->waveLengthIncrementSpinBox->setValue(simData->waveLengthIncrement.getQuantityValue().getValueAs(Base::Quantity::Metre));
	ui->waveLengthIncrementSpinBox->setUnit(Base::Unit(-1));

	//direction discretization
	ui->directionNumberOfIncrementSpinBox->setMinimum(1);
	ui->directionNumberOfIncrementSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->directionNumberOfIncrementSpinBox->setValue(simData->numberOfDirectionIncrements.getValue());

	ui->directionMinSpinBox->setMinimum(0.00);
	ui->directionMinSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->directionMinSpinBox->setValue(simData->minDirection.getQuantityValue().getValueAs(Base::Quantity::Degree));
	ui->directionMinSpinBox->setUnit(Base::Unit::Angle);

	ui->directionMaxSpinBox->setMinimum(0.00);
	ui->directionMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->directionMaxSpinBox->setValue(simData->maxDirection.getQuantityValue().getValueAs(Base::Quantity::Degree));
	ui->directionMaxSpinBox->setUnit(Base::Unit::Angle);

	ui->directionIncrementSpinBox->setMinimum(0.00);
	ui->directionIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->directionIncrementSpinBox->setValue(simData->directionIncrement.getQuantityValue().getValueAs(Base::Quantity::Degree));
	ui->directionIncrementSpinBox->setUnit(Base::Unit::Angle);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgNewSimulation::~DlgNewSimulation()
{
}

void DlgNewSimulation::radioButtonStationarityToggled(bool)
{
	stationarity = true;
	ui->uniformModulationRadioButton->setEnabled(false);
	ui->generalModulationRadioButton->setEnabled(false);
}

void DlgNewSimulation::radioButtonNonStationarityToggled(bool)
{
	stationarity = false;
	ui->uniformModulationRadioButton->setEnabled(true);
	ui->generalModulationRadioButton->setEnabled(true);
}

void DlgNewSimulation::radioButtonUniformModulationToggled(bool)
{
	uniformModulation = true;
}

void DlgNewSimulation::radioButtonNonGeneralModulationToggled(bool)
{
	uniformModulation = false;
}

void DlgNewSimulation::radioButtonGaussianityToggled(bool)
{
	gaussianity = true;
}

void DlgNewSimulation::radioButtonNonGaussianityToggled(bool)
{
	gaussianity = false;
}

void DlgNewSimulation::createNewSimulation()
{
	auto doc = App::GetApplication().getActiveDocument();
	if(!doc)
	return;
	
	std::string uniqueName = doc->getUniqueObjectName(ui->NameLineEdit->text().toUtf8().constData());
	doc->openTransaction("Create Simulation");
	UserLab::UserLabSimulation* newSim = static_cast< UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->createSimulation(uniqueName, "UserLab::UserLabSimulation"));
    Base::Interpreter().runString("import UserLabGui");
	Base::Interpreter().runString("UserLabGui.setActiveSimulation(LabRPS.ActiveDocument.ActiveObject)");
	doc->commitTransaction();
    saveSimulation(doc, newSim);
    App::GetApplication().getActiveDocument()->recompute();
}


void  DlgNewSimulation::saveSimulation(App::Document* doc,  UserLab::UserLabSimulation* sim)
{
	//save number of process
	sim->NumberOfProcess.setValue(ui->numberOfProcessSpinBox->value());

	//save number of sample
	sim->NumberOfSample.setValue(ui->numberOfSampleSpinBox->value());

	//save stationarity
	sim->Stationarity.setValue(stationarity);

	//save gaussianity
	sim->Gaussianity.setValue(gaussianity);

	//save modulation
	sim->UniformModulation.setValue(uniformModulation);

	//save time discretization
	sim->NumberOfTimeIncrements.setValue(ui->timeNumberSpinBox->value());
	sim->MinTime.setValue(ui->timeMinSpinBox->value().getValue());
	sim->MaxTime.setValue(ui->timeMaxSpinBox->value().getValue());
	sim->TimeIncrement.setValue(ui->timeIncrementSpinBox->value().getValue());

	//save frequency discretization
	sim->NumberOfFrequency.setValue(ui->frequencyNumberSpinBox->value());
	sim->MinFrequency.setValue(ui->frequencyMinSpinBox->value().getValue());
	sim->MaxFrequency.setValue(ui->frequencyMaxSpinBox->value().getValue());
	sim->FrequencyIncrement.setValue(ui->frequencyIncrementSpinBox->value().getValue());

	//save wave length discretization
	sim->NumberOfWaveLengthIncrements.setValue(ui->waveNumberOfIncrementSpinBox->value());
	sim->MinWaveLength.setValue(ui->waveMinLengthSpinBox->value().getValue());
	sim->MaxWaveLength.setValue(ui->waveMaxLengthSpinBox->value().getValue());
	sim->WaveLengthIncrement.setValue(ui->waveLengthIncrementSpinBox->value().getValue());

	//save direction discretization
	sim->NumberOfDirectionIncrements.setValue(ui->directionNumberOfIncrementSpinBox->value());
	sim->MinDirection.setValue(ui->directionMinSpinBox->value().getValue());
	sim->MaxDirection.setValue(ui->directionMaxSpinBox->value().getValue());
	sim->DirectionIncrement.setValue(ui->directionIncrementSpinBox->value().getValue());

	//App::GetApplication().signalCreateSimulation(sim->Label.getValue());
	doc->updateObject(sim);
}

void DlgNewSimulation::accept(const QString& simulation)
{

}

void DlgNewSimulation::reject()
{
	if (userFeaturePtr.expired())
		return;
	App::Document* doc = userFeaturePtr->getDocument();
	doc->abortTransaction();
}

// ----------------------------------------------

/* TRANSLATOR UserLabGui::Simulation */

DlgUserLabFeatures::DlgUserLabFeatures(QWidget * parent,  UserLab::UserLabSimulation* sim)
	: QWidget(parent)
	, ui(new Ui_DlgUserLabFeatures)
{
	mode = 0;
	ui->setupUi(this);
	/*if (!sim)
		return;*/

	fillRPSFeaturesComboxBoxes(sim);

	connect(ui->simulationMethodPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingSimulationMethod()));
	
}

DlgUserLabFeatures::~DlgUserLabFeatures()
{

}

void DlgUserLabFeatures::fillRPSFeaturesComboxBoxes( UserLab::UserLabSimulation* sim)
{

	if (!sim)
		sim = static_cast< UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->active());

	if (!sim)
		return;

	std::vector<Base::Type> types = sim->getRPSTypesOfPluggableFeatures();
	std::vector<QComboBox*> comboxBoxes = getAllComboBoxes();
	if (types.size() != comboxBoxes.size())
	{
		Base::Console().Warning("Fail to access the available UserLab Features\n");
		return;
	}

	for (int j = 0; j < types.size(); j++)
	{
		comboxBoxes[j]->addItems(sim->findAllUserLabFeatures(types[j]));
	}
}

std::vector<QComboBox*> DlgUserLabFeatures::getAllComboBoxes()
{
	std::vector<QComboBox*> comboBoxes;
	comboBoxes.emplace_back(ui->simulationMethodComboBox);
	return comboBoxes;
}

void DlgUserLabFeatures::setAllComboBoxesCurrentText( UserLab::UserLabSimulation* sim)
{
	ui->simulationMethodComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->simulationMethod.getValue()));
}


void  DlgUserLabFeatures::saveLabFeatures( UserLab::UserLabSimulation* sim)
{
	sim->getSimulationData()->simulationMethod.setValue(ui->simulationMethodComboBox->currentText().toUtf8().constData());
	fillRPSFeaturesComboxBoxes(sim);
}


void DlgUserLabFeatures::onInitialSettingSimulationMethod()
{
	 UserLab::UserLabSimulation* sim = static_cast< UserLab::UserLabSimulation*>(UserLabGui::UserLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->simulationMethodComboBox->currentText();
	QString group = UserLab::UserLabUtils::objGroupSimulationMethod;
	sim->userFeatureInitalSetting(group, selectedFeature);
}

// ----------------------------------------------

// ----------------------------------------------

/* TRANSLATOR PartGui::TaskNewSimulation */

TaskNewSimulation::TaskNewSimulation()
{
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgNewSimulation();
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

	dlgUserLabFeatures = new DlgUserLabFeatures();
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), dlgUserLabFeatures->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(dlgUserLabFeatures);
	Content.push_back(taskbox);
}

TaskNewSimulation::~TaskNewSimulation()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons TaskNewSimulation::getStandardButtons() const
{
	return QDialogButtonBox::Close |
		QDialogButtonBox::Ok;
}

void TaskNewSimulation::modifyStandardButtons(QDialogButtonBox* box)
{
	QPushButton* btn = box->button(QDialogButtonBox::Ok);
	btn->setText(QApplication::translate("UserLabGui::DlgNewSimulation", "&Create"));
}

bool TaskNewSimulation::accept()
{
	widget->createNewSimulation();
	return true;
}

bool TaskNewSimulation::reject()
{
	return true;
}

// ----------------------------------------------

/* TRANSLATOR PartGui::TaskNewSimulationEdit */

TaskNewSimulationEdit::TaskNewSimulationEdit( UserLab::UserLabSimulation* sim)
	:_sim(sim)
{
	// create and show dialog for the UserLabFeatures
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgNewSimulation(nullptr, sim);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

	dlgUserLabFeatures = new DlgUserLabFeatures(nullptr, sim);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), dlgUserLabFeatures->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(dlgUserLabFeatures);
	Content.push_back(taskbox);
}

TaskNewSimulationEdit::~TaskNewSimulationEdit()
{
	
}

QDialogButtonBox::StandardButtons TaskNewSimulationEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel |
		QDialogButtonBox::Ok;
}

bool TaskNewSimulationEdit::accept()
{
	auto doc = App::GetApplication().getActiveDocument();
	if(!doc)
	return false;
	widget->saveSimulation(doc, _sim);
	dlgUserLabFeatures->saveLabFeatures(_sim);
	return true;
}

bool TaskNewSimulationEdit::reject()
{
	return true;
}

#include "moc_DlgNewSimulation.cpp"
