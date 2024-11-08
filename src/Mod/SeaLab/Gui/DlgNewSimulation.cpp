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
#include <Mod/SeaLab/Gui/SeaLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/SeaLab/App/SeaLabSimulation.h>
#include <Mod/SeaLabAPI/App/RPS.h>
#include "Ui_DlgNewSimulation.h"
#include "ui_DlgSeaLabFeatures.h"
#include <App/DocumentObjectGroup.h>
#include <Mod/SeaLab/App/SeaLabUtils.h>
using namespace SeaLabGui;

DlgNewSimulation::DlgNewSimulation(QWidget* parent,  SeaLab::SeaLabSimulation* sim)
	: QWidget(parent)
	, ui(new Ui_DlgNewSimulation)
	, seaLabFeaturePtr(sim)
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

	SeaLabAPI::SeaLabSimulationData* simData = nullptr;

	if (sim)
	{
		simData = sim->getSimulationData();
		ui->NameLineEdit->setText(QString::fromLatin1(sim->Label.getValue()));
		ui->NameLineEdit->setEnabled(FALSE);
	}
	else
	{
		simData = new SeaLabAPI::SeaLabSimulationData();
		ui->NameLineEdit->setText(QString::fromLatin1("Sea"));
	}


	//number of ground motion process
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
	ui->timeMinSpinBox->setValue(simData->minTime.getValue());
	ui->timeMinSpinBox->setUnit(Base::Unit::TimeSpan);

	ui->timeMaxSpinBox->setMinimum(0.00);
	ui->timeMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->timeMaxSpinBox->setValue(simData->maxTime.getValue());
	ui->timeMaxSpinBox->setUnit(Base::Unit::TimeSpan);

	ui->timeIncrementSpinBox->setMinimum(0.00);
	ui->timeIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->timeIncrementSpinBox->setValue(simData->timeIncrement.getValue());
	ui->timeIncrementSpinBox->setUnit(Base::Unit::TimeSpan);

	//frequency discretization
	ui->frequencyNumberSpinBox->setMinimum(1);
	ui->frequencyNumberSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->frequencyNumberSpinBox->setValue(simData->numberOfFrequency.getValue());

	ui->frequencyMinSpinBox->setMinimum(0.00);
	ui->frequencyMinSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyMinSpinBox->setValue(simData->minFrequency.getValue());
	ui->frequencyMinSpinBox->setUnit(Base::Unit::Frequency);

	ui->frequencyMaxSpinBox->setMinimum(0.00);
	ui->frequencyMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyMaxSpinBox->setValue(simData->maxFrequency.getValue());
	ui->frequencyMaxSpinBox->setUnit(Base::Unit::Frequency);

	ui->frequencyIncrementSpinBox->setMinimum(0.00);
	ui->frequencyIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyIncrementSpinBox->setValue(simData->frequencyIncrement.getValue());
	ui->frequencyIncrementSpinBox->setUnit(Base::Unit::Frequency);

	//wave length discretization
	ui->waveNumberOfIncrementSpinBox->setMinimum(1);
	ui->waveNumberOfIncrementSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->waveNumberOfIncrementSpinBox->setValue(simData->numberOfWaveLengthIncrements.getValue());

	ui->waveMinLengthSpinBox->setMinimum(0.00);
	ui->waveMinLengthSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->waveMinLengthSpinBox->setValue(simData->minWaveLength.getQuantityValue().getValue());
	ui->waveMinLengthSpinBox->setUnit(Base::Unit::Length);

	ui->waveMaxLengthSpinBox->setMinimum(0.00);
	ui->waveMaxLengthSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->waveMaxLengthSpinBox->setValue(simData->maxWaveLength.getQuantityValue().getValue());
	ui->waveMaxLengthSpinBox->setUnit(Base::Unit(Base::Unit::Length));

	ui->waveLengthIncrementSpinBox->setMinimum(0.00);
	ui->waveLengthIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->waveLengthIncrementSpinBox->setValue(simData->waveLengthIncrement.getQuantityValue().getValue());
	ui->waveLengthIncrementSpinBox->setUnit(Base::Unit::Length);

	//direction discretization
	ui->directionNumberOfIncrementSpinBox->setMinimum(1);
	ui->directionNumberOfIncrementSpinBox->setMaximum(std::numeric_limits<int>::max());
	ui->directionNumberOfIncrementSpinBox->setValue(simData->numberOfDirectionIncrements.getValue());

	ui->directionMinSpinBox->setMinimum(0.00);
	ui->directionMinSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->directionMinSpinBox->setValue(simData->minDirection.getValue());
	ui->directionMinSpinBox->setUnit(Base::Unit::Angle);

	ui->directionMaxSpinBox->setMinimum(0.00);
	ui->directionMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->directionMaxSpinBox->setValue(simData->maxDirection.getValue());
	ui->directionMaxSpinBox->setUnit(Base::Unit::Angle);

	ui->directionIncrementSpinBox->setMinimum(0.00);
	ui->directionIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->directionIncrementSpinBox->setValue(simData->directionIncrement.getValue());
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
	SeaLab::SeaLabSimulation* newSim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->createSimulation(uniqueName, "SeaLab::SeaLabSimulation"));
    Base::Interpreter().runString("import SeaLabGui");
	Base::Interpreter().runString("SeaLabGui.setActiveSimulation(LabRPS.ActiveDocument.ActiveObject)");
	doc->commitTransaction();
    saveSimulation(doc, newSim);
    App::GetApplication().getActiveDocument()->recompute();
}


void  DlgNewSimulation::saveSimulation(App::Document* doc,  SeaLab::SeaLabSimulation* sim)
{
	//save number of process
	sim->getSimulationData()->numberOfSpatialPosition.setValue(ui->numberOfProcessSpinBox->value());

	//save number of sample
	sim->getSimulationData()->numberOfSample.setValue(ui->numberOfSampleSpinBox->value());

	//save stationarity
	sim->getSimulationData()->stationarity.setValue(stationarity);

	//save gaussianity
	sim->getSimulationData()->gaussianity.setValue(gaussianity);

	//save modulation
	sim->getSimulationData()->uniformModulation.setValue(uniformModulation);

	//save time discretization
	sim->getSimulationData()->numberOfTimeIncrements.setValue(ui->timeNumberSpinBox->value());
	sim->getSimulationData()->minTime.setValue(ui->timeMinSpinBox->value().getValue());
	sim->getSimulationData()->maxTime.setValue(ui->timeMaxSpinBox->value().getValue());
	sim->getSimulationData()->timeIncrement.setValue(ui->timeIncrementSpinBox->value().getValue());

	//save frequency discretization
	sim->getSimulationData()->numberOfFrequency.setValue(ui->frequencyNumberSpinBox->value());
	sim->getSimulationData()->minFrequency.setValue(ui->frequencyMinSpinBox->value().getValue());
	sim->getSimulationData()->maxFrequency.setValue(ui->frequencyMaxSpinBox->value().getValue());
	sim->getSimulationData()->frequencyIncrement.setValue(ui->frequencyIncrementSpinBox->value().getValue());

	//save wave length discretization
	sim->getSimulationData()->numberOfWaveLengthIncrements.setValue(ui->waveNumberOfIncrementSpinBox->value());
	sim->getSimulationData()->minWaveLength.setValue(ui->waveMinLengthSpinBox->value().getValue());
	sim->getSimulationData()->maxWaveLength.setValue(ui->waveMaxLengthSpinBox->value().getValue());
	sim->getSimulationData()->waveLengthIncrement.setValue(ui->waveLengthIncrementSpinBox->value().getValue());

	//save direction discretization
	sim->getSimulationData()->numberOfDirectionIncrements.setValue(ui->directionNumberOfIncrementSpinBox->value());
	sim->getSimulationData()->minDirection.setValue(ui->directionMinSpinBox->value().getValue());
	sim->getSimulationData()->maxDirection.setValue(ui->directionMaxSpinBox->value().getValue());
	sim->getSimulationData()->directionIncrement.setValue(ui->directionIncrementSpinBox->value().getValue());

	//App::GetApplication().signalCreateSimulation(sim->Label.getValue());
	doc->updateObject(sim);
}

void DlgNewSimulation::accept(const QString& simulation)
{

}

void DlgNewSimulation::reject()
{
	if (seaLabFeaturePtr.expired())
		return;
	App::Document* doc = seaLabFeaturePtr->getDocument();
	doc->abortTransaction();
}

// ----------------------------------------------

/* TRANSLATOR SeaLabGui::Simulation */

DlgSeaLabFeatures::DlgSeaLabFeatures(QWidget * parent,  SeaLab::SeaLabSimulation* sim)
	: QWidget(parent)
	, ui(new Ui_DlgSeaLabFeatures)
{
	mode = 0;
	ui->setupUi(this);
	/*if (!sim)
		return;*/

	fillRPSFeaturesComboxBoxes(sim);

	connect(ui->locationDistributionPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingLocationDistribution()));
	connect(ui->meanAccelerationProfilePushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingMeanAccelerationProfile()));
	connect(ui->spectrumPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingAlongWindSpectrum()));
	connect(ui->spectrumDecompositionPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingSpectrumDecompositionMethod()));
	connect(ui->coherenceFunctionPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingCoherenceFunction()));
	connect(ui->simulationMethodPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingSimulationMethod()));
	connect(ui->frequencyDistributionPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingFrequencyDistribution()));
	connect(ui->randomnessProviderPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingRandomnessProvider()));
	connect(ui->modulationFunctionPpushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingModulationFunction()));
	connect(ui->correlationFunctionPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingCorrelationFunction()));
	connect(ui->CPDpushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingCumulativeProbabilityDistribution()));
	connect(ui->kurtosisPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingKurtosis()));
	connect(ui->peakFactorPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingPeakFactor()));
	connect(ui->PDFPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingProbabilityDensityFunction()));
	connect(ui->shearVelocityomboBox, SIGNAL(clicked()), this, SLOT(onInitialSettingShearVelocityOfFlow()));
	connect(ui->skewnessPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingSkewness()));
	connect(ui->standardDeviationPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingStandardDeviation()));
	connect(ui->variancePushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingVariance()));
	connect(ui->wavePassageEffectPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingWavePassageEffect()));
	connect(ui->userDefinedFeaturePushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingUserDefinedRPSObject()));

}

DlgSeaLabFeatures::~DlgSeaLabFeatures()
{

}

void DlgSeaLabFeatures::fillRPSFeaturesComboxBoxes( SeaLab::SeaLabSimulation* sim)
{

	if (!sim)
		sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());

	if (!sim)
		return;

	std::vector<Base::Type> types = sim->getRPSTypesOfPluggableFeatures();
	std::vector<QComboBox*> comboxBoxes = getAllComboBoxes();
	if (types.size() != comboxBoxes.size())
	{
		Base::Console().Warning("Fail to access the available SeaLab Features\n");
		return;
	}

	for (int j = 0; j < types.size(); j++)
	{
		comboxBoxes[j]->addItems(sim->findAllSeaLabFeatures(types[j]));
	}
}

std::vector<QComboBox*> DlgSeaLabFeatures::getAllComboBoxes()
{
	std::vector<QComboBox*> comboBoxes;
	comboBoxes.emplace_back(ui->lacationDistributionComboBox);
	comboBoxes.emplace_back(ui->meanAccelerationProfileComboBox);
	comboBoxes.emplace_back(ui->spectrumComboBox);
	comboBoxes.emplace_back(ui->spectrumDecompositionMethodComboBox);
	comboBoxes.emplace_back(ui->coherenceFunctionComboBox);
	comboBoxes.emplace_back(ui->simulationMethodComboBox);
	comboBoxes.emplace_back(ui->frequencyDistributionComboBox);
	comboBoxes.emplace_back(ui->randomnessProviderComboBox);
	comboBoxes.emplace_back(ui->modulationFunctionComboBox);
	comboBoxes.emplace_back(ui->correlationFunctionComboBox);
	comboBoxes.emplace_back(ui->tableToolComboBox);
	comboBoxes.emplace_back(ui->matrixToolComboBox);
	comboBoxes.emplace_back(ui->CPDComboBox);
	comboBoxes.emplace_back(ui->KurtosisComboBox);
	comboBoxes.emplace_back(ui->peakFactorComboBox);
	comboBoxes.emplace_back(ui->PDFComboBox);
	comboBoxes.emplace_back(ui->shearVelocityomboBox);
	comboBoxes.emplace_back(ui->skewnessComboBox);
	comboBoxes.emplace_back(ui->standardDeviationComboBox);
	comboBoxes.emplace_back(ui->varianceComboBox);
	comboBoxes.emplace_back(ui->wavePassageEffectComboBox);
	comboBoxes.emplace_back(ui->userDefinedFeatureCcomboBox);

	return comboBoxes;
}

void DlgSeaLabFeatures::setAllComboBoxesCurrentText( SeaLab::SeaLabSimulation* sim)
{
	ui->lacationDistributionComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->spatialDistribution.getValue()));
	ui->meanAccelerationProfileComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->meanFunction.getValue()));
	ui->spectrumComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->spectrumModel.getValue()));
	ui->spectrumDecompositionMethodComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->cpsdDecompositionMethod.getValue()));
	ui->coherenceFunctionComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->coherenceFunction.getValue()));
	ui->simulationMethodComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->simulationMethod.getValue()));
	ui->frequencyDistributionComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->frequencyDistribution.getValue()));
	ui->randomnessProviderComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->randomnessProvider.getValue()));
	ui->modulationFunctionComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->modulationFunction.getValue()));
	ui->correlationFunctionComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->correlationFunction.getValue()));
	ui->CPDComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->cumulativeProbabilityDistribution.getValue()));
	ui->KurtosisComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->kurtosis.getValue()));
	ui->peakFactorComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->peakFactor.getValue()));
	ui->PDFComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->probabilityDensityFunction.getValue()));
	ui->shearVelocityomboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->shearVelocityOfFlow.getValue()));
	ui->skewnessComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->skewness.getValue()));
	ui->standardDeviationComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->standardDeviation.getValue()));
	ui->varianceComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->variance.getValue()));
	ui->wavePassageEffectComboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->wavePassageEffect.getValue()));
	ui->userDefinedFeatureCcomboBox->setCurrentText(QString::fromUtf8(sim->getSimulationData()->userDefinedRPSObject.getValue()));
}


void  DlgSeaLabFeatures::saveLabFeatures( SeaLab::SeaLabSimulation* sim)
{
	sim->getSimulationData()->spatialDistribution.setValue(ui->lacationDistributionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->meanFunction.setValue(ui->meanAccelerationProfileComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->spectrumModel.setValue(ui->spectrumComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->cpsdDecompositionMethod.setValue(ui->spectrumDecompositionMethodComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->coherenceFunction.setValue(ui->coherenceFunctionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->simulationMethod.setValue(ui->simulationMethodComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->frequencyDistribution.setValue(ui->frequencyDistributionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->randomnessProvider.setValue(ui->randomnessProviderComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->modulationFunction.setValue(ui->modulationFunctionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->correlationFunction.setValue(ui->correlationFunctionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->userDefinedRPSObject.setValue(ui->userDefinedFeatureCcomboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->cumulativeProbabilityDistribution.setValue(ui->CPDComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->kurtosis.setValue(ui->KurtosisComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->peakFactor.setValue(ui->peakFactorComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->probabilityDensityFunction.setValue(ui->PDFComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->shearVelocityOfFlow.setValue(ui->shearVelocityomboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->skewness.setValue(ui->skewnessComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->standardDeviation.setValue(ui->standardDeviationComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->varianceFunction.setValue(ui->varianceComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->wavePassageEffect.setValue(ui->wavePassageEffectComboBox->currentText().toUtf8().constData());

	fillRPSFeaturesComboxBoxes(sim);
}


void DlgSeaLabFeatures::onInitialSettingLocationDistribution()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->lacationDistributionComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupLocationDistribution;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingMeanAccelerationProfile()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->meanAccelerationProfileComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupMeanAccelerationProfile;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingSpectrum()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->spectrumComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupSpectrum;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeaLabFeatures::onInitialSettingSpectrumDecompositionMethod()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->spectrumDecompositionMethodComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupSpectrumDecompositionMethod;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingCoherenceFunction()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->coherenceFunctionComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupCoherenceFunction;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingSimulationMethod()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->simulationMethodComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupSimulationMethod;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingFrequencyDistribution()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->frequencyDistributionComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupFrequencyDistribution;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingRandomnessProvider()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->randomnessProviderComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupRandomnessProvider;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingModulationFunction()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->modulationFunctionComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupModulationFunction;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingCorrelationFunction()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->correlationFunctionComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupCorrelationFunction;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingUserDefinedRPSObject()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->userDefinedFeatureCcomboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupUserDefinedRPSObject;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingCumulativeProbabilityDistribution()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->CPDComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupCumulativeProbabilityDistribution;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeaLabFeatures::onInitialSettingKurtosis()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->KurtosisComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupKurtosis;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingPeakFactor()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->peakFactorComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupPeakFactor;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingProbabilityDensityFunction()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->PDFComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupProbabilityDensityFunction;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeaLabFeatures::onInitialSettingShearVelocityOfFlow()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->shearVelocityomboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupShearVelocityOfFlow;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingSkewness()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->skewnessComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupSkewness;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingStandardDeviation()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->standardDeviationComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupStandardDeviation;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeaLabFeatures::onInitialSettingVariance()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->varianceComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupVariance;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeaLabFeatures::onInitialSettingWavePassageEffect()
{
	 SeaLab::SeaLabSimulation* sim = static_cast< SeaLab::SeaLabSimulation*>(SeaLabGui::SeaLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->wavePassageEffectComboBox->currentText();
	QString group = SeaLab::SeaLabUtils::objGroupWavePassageEffect;
	sim->seaLabFeatureInitalSetting(group, selectedFeature);
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

	dlgSeaLabFeatures = new DlgSeaLabFeatures();
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), dlgSeaLabFeatures->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(dlgSeaLabFeatures);
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
	btn->setText(QApplication::translate("SeaLabGui::DlgNewSimulation", "&Create"));
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

TaskNewSimulationEdit::TaskNewSimulationEdit( SeaLab::SeaLabSimulation* sim)
	:_sim(sim)
{
	// create and show dialog for the SeaLabFeatures
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgNewSimulation(nullptr, sim);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

	dlgSeaLabFeatures = new DlgSeaLabFeatures(nullptr, sim);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), dlgSeaLabFeatures->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(dlgSeaLabFeatures);
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
	dlgSeaLabFeatures->saveLabFeatures(_sim);
	return true;
}

bool TaskNewSimulationEdit::reject()
{
	return true;
}

#include "moc_DlgNewSimulation.cpp"
