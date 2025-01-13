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
#include <Mod/SeismicLab/Gui/SeismicLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Mod/SeismicLab/App/SeismicLabSimulation.h>
#include <Mod/SeismicLabAPI/App/RPS.h>
#include "Ui_DlgNewSimulation.h"
#include "ui_DlgSeismicLabFeatures.h"
#include <App/DocumentObjectGroup.h>
#include <Mod/SeismicLab/App/SeismicLabUtils.h>
using namespace SeismicLabGui;

DlgNewSimulation::DlgNewSimulation(QWidget* parent,  SeismicLab::SeismicLabSimulation* sim)
	: QWidget(parent)
	, ui(new Ui_DlgNewSimulation)
	, seismicLabFeaturePtr(sim)
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

	SeismicLabAPI::SeismicLabSimulationData* simData = nullptr;

	if (sim)
	{
		simData = sim->getSimulationData();
		ui->NameLineEdit->setText(QString::fromLatin1(sim->Label.getValue()));
		ui->NameLineEdit->setEnabled(FALSE);
	}
	else
	{
		simData = new SeismicLabAPI::SeismicLabSimulationData();
		ui->NameLineEdit->setText(QString::fromLatin1("Ground"));
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
	ui->frequencyMinSpinBox->setValue(simData->minFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond));
	ui->frequencyMinSpinBox->setUnit(Base::Unit::Frequency);

	ui->frequencyMaxSpinBox->setMinimum(0.00);
	ui->frequencyMaxSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyMaxSpinBox->setValue(simData->maxFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond));
	ui->frequencyMaxSpinBox->setUnit(Base::Unit::Frequency);

	ui->frequencyIncrementSpinBox->setMinimum(0.00);
	ui->frequencyIncrementSpinBox->setMaximum(std::numeric_limits<double>::max());
	ui->frequencyIncrementSpinBox->setValue(simData->frequencyIncrement.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond));
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
	SeismicLab::SeismicLabSimulation* newSim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->createSimulation(uniqueName, "SeismicLab::SeismicLabSimulation"));
    Base::Interpreter().runString("import SeismicLabGui");
	Base::Interpreter().runString("SeismicLabGui.setActiveSimulation(LabRPS.ActiveDocument.ActiveObject)");
	doc->commitTransaction();
    saveSimulation(doc, newSim);
    App::GetApplication().getActiveDocument()->recompute();
}


void  DlgNewSimulation::saveSimulation(App::Document* doc,  SeismicLab::SeismicLabSimulation* sim)
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
	if (seismicLabFeaturePtr.expired())
		return;
	App::Document* doc = seismicLabFeaturePtr->getDocument();
	doc->abortTransaction();
}

// ----------------------------------------------

/* TRANSLATOR SeismicLabGui::Simulation */

DlgSeismicLabFeatures::DlgSeismicLabFeatures(QWidget * parent,  SeismicLab::SeismicLabSimulation* sim)
	: QWidget(parent)
	, ui(new Ui_DlgSeismicLabFeatures)
{
	mode = 0;
	ui->setupUi(this);
	/*if (!sim)
		return;*/

	fillRPSFeaturesComboxBoxes(sim);

	connect(ui->locationDistributionPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingLocationDistribution()));
	connect(ui->meanAccelerationProfilePushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingMeanAccelerationProfile()));
	connect(ui->spectrumPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingSpectrum()));
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
	connect(ui->shearVelocityPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingShearVelocityOfFlow()));
	connect(ui->skewnessPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingSkewness()));
	connect(ui->standardDeviationPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingStandardDeviation()));
	connect(ui->variancePushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingVariance()));
	connect(ui->wavePassageEffectPushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingWavePassageEffect()));
	connect(ui->userDefinedFeaturePushButton, SIGNAL(clicked()), this, SLOT(onInitialSettingUserDefinedRPSObject()));

}

DlgSeismicLabFeatures::~DlgSeismicLabFeatures()
{

}

void DlgSeismicLabFeatures::fillRPSFeaturesComboxBoxes( SeismicLab::SeismicLabSimulation* sim)
{

	if (!sim)
		sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());

	if (!sim)
		return;

	std::vector<Base::Type> types = sim->getRPSTypesOfPluggableFeatures();
	std::vector<QComboBox*> comboxBoxes = getAllComboBoxes();
	if (types.size() != comboxBoxes.size())
	{
		Base::Console().Warning("Fail to access the available SeismicLab Features\n");
		return;
	}

	for (int j = 0; j < types.size(); j++)
	{
		comboxBoxes[j]->addItems(sim->findAllSeismicLabFeatures(types[j]));
	}
}

std::vector<QComboBox*> DlgSeismicLabFeatures::getAllComboBoxes()
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

void DlgSeismicLabFeatures::setAllComboBoxesCurrentText( SeismicLab::SeismicLabSimulation* sim)
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


void  DlgSeismicLabFeatures::saveLabFeatures( SeismicLab::SeismicLabSimulation* sim)
{
	sim->getSimulationData()->spatialDistribution.setValue(ui->lacationDistributionComboBox->currentText().toUtf8().constData());
	sim->MeanFunction.setValue(ui->meanAccelerationProfileComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->spectrumModel.setValue(ui->spectrumComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->cpsdDecompositionMethod.setValue(ui->spectrumDecompositionMethodComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->coherenceFunction.setValue(ui->coherenceFunctionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->simulationMethod.setValue(ui->simulationMethodComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->frequencyDistribution.setValue(ui->frequencyDistributionComboBox->currentText().toUtf8().constData());
	sim->getSimulationData()->randomnessProvider.setValue(ui->randomnessProviderComboBox->currentText().toUtf8().constData());
	sim->ModulationFunction.setValue(ui->modulationFunctionComboBox->currentText().toUtf8().constData());
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


void DlgSeismicLabFeatures::onInitialSettingLocationDistribution()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->lacationDistributionComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupLocationDistribution;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingMeanAccelerationProfile()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->meanAccelerationProfileComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupMeanAccelerationProfile;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingSpectrum()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->spectrumComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupSpectrum;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeismicLabFeatures::onInitialSettingSpectrumDecompositionMethod()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->spectrumDecompositionMethodComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupSpectrumDecompositionMethod;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingCoherenceFunction()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->coherenceFunctionComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupCoherenceFunction;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingSimulationMethod()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->simulationMethodComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupSimulationMethod;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingFrequencyDistribution()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->frequencyDistributionComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupFrequencyDistribution;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingRandomnessProvider()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->randomnessProviderComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupRandomnessProvider;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingModulationFunction()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->modulationFunctionComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupModulationFunction;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingCorrelationFunction()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->correlationFunctionComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupCorrelationFunction;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingUserDefinedRPSObject()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->userDefinedFeatureCcomboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupUserDefinedRPSObject;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingCumulativeProbabilityDistribution()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->CPDComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupCumulativeProbabilityDistribution;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeismicLabFeatures::onInitialSettingKurtosis()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->KurtosisComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupKurtosis;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingPeakFactor()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->peakFactorComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupPeakFactor;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingProbabilityDensityFunction()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->PDFComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupProbabilityDensityFunction;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeismicLabFeatures::onInitialSettingShearVelocityOfFlow()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->shearVelocityomboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupShearVelocityOfFlow;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingSkewness()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->skewnessComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupSkewness;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingStandardDeviation()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->standardDeviationComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupStandardDeviation;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}

void DlgSeismicLabFeatures::onInitialSettingVariance()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->varianceComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupVariance;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
}
void DlgSeismicLabFeatures::onInitialSettingWavePassageEffect()
{
	 SeismicLab::SeismicLabSimulation* sim = static_cast< SeismicLab::SeismicLabSimulation*>(SeismicLabGui::SeismicLabSimulationObserver::instance()->active());
	QString selectedFeature = ui->wavePassageEffectComboBox->currentText();
	QString group = SeismicLab::SeismicLabUtils::objGroupWavePassageEffect;
	sim->seismicLabFeatureInitalSetting(group, selectedFeature);
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

	dlgSeismicLabFeatures = new DlgSeismicLabFeatures();
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), dlgSeismicLabFeatures->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(dlgSeismicLabFeatures);
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
	btn->setText(QApplication::translate("SeismicLabGui::DlgNewSimulation", "&Create"));
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

TaskNewSimulationEdit::TaskNewSimulationEdit( SeismicLab::SeismicLabSimulation* sim)
	:_sim(sim)
{
	// create and show dialog for the SeismicLabFeatures
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgNewSimulation(nullptr, sim);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

	dlgSeismicLabFeatures = new DlgSeismicLabFeatures(nullptr, sim);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), dlgSeismicLabFeatures->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(dlgSeismicLabFeatures);
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
	dlgSeismicLabFeatures->saveLabFeatures(_sim);
	return true;
}

bool TaskNewSimulationEdit::reject()
{
	return true;
}

#include "moc_DlgNewSimulation.cpp"
