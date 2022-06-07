#include "rpsSeismicLabSimulation.h"

#include "RPSSeismicLabAPI.h"
#include "rps/RPSpluginManager.h"
#include "rps/seismicLab/widgets/prsslsimuoptionsdlg.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>

RPSSeismicLabSimulation::RPSSeismicLabSimulation(QWidget *parent) :
    QWidget(parent)
{
	// initialized seismicLab simulation data
	seismicLabDataInitialize();

	// read install seismicLab from registry if any
	SLReadAllTobeInstallObjectsFromRegistry();
	SLClearAllTobeInstallObjectsFromRegistry();
}

RPSSeismicLabSimulation::~RPSSeismicLabSimulation()
{
	SLWriteAllTobeInstallObjectsToRegistry();
}


void RPSSeismicLabSimulation::groundMotion()
{
	QMessageBox::warning(0, "seimicLab", "intput ground motion");

}
void RPSSeismicLabSimulation::spectrumSeismic()
{
	QMessageBox::warning(0, "seimicLab", "intput spectrum");
}

void RPSSeismicLabSimulation::coherenceSeismic()
{
	QMessageBox::warning(0, "seimicLab", "intput coherence");
}
void RPSSeismicLabSimulation::correlationSeismic()
{
	QMessageBox::warning(0, "seimicLab", "intput correlation");
}
void RPSSeismicLabSimulation::modulationSeismic()
{
	QMessageBox::warning(0, "seimicLab", "intput modulation");
}

void RPSSeismicLabSimulation::groundMotionOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output ground motion");
}
void RPSSeismicLabSimulation::spectrumSeismicOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output spectrum");
}
void RPSSeismicLabSimulation::coherenceSeismicOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output coherence");
}
void RPSSeismicLabSimulation::correlationSeismicOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output correlation");
}
void RPSSeismicLabSimulation::modulationSeismicOutput()
{
	QMessageBox::warning(0, "seimicLab", "Output modulation");
}
CRPSSeismicLabsimuData &RPSSeismicLabSimulation::GetSeismicLabData()
{
	return seimicLabData;
}

void RPSSeismicLabSimulation::seismicLabDataInitialize()
{
	seimicLabData.numberOfSpatialPosition = 3;
	seimicLabData.numberOfSample = 1;
	seimicLabData.numberOfFrequency = 1024;
	seimicLabData.minFrequency = 0;
	seimicLabData.maxFrequency = 4;
	seimicLabData.numberOfTimeIncrements = 2 * seimicLabData.numberOfFrequency*seimicLabData.numberOfSpatialPosition;
	seimicLabData.timeIncrement = 0.25;
	seimicLabData.frequencyIncrement = seimicLabData.maxFrequency / seimicLabData.numberOfFrequency;
	seimicLabData.stationarity = true;
	seimicLabData.gaussianity = true;
	seimicLabData.minTime = 0;
	seimicLabData.simulationMethod = ("Deodatis et al 1996");
	seimicLabData.spatialDistribution = ("Horizontal Distribution");
	seimicLabData.coherenceFunction = ("Abrahamson Coherence");
	seimicLabData.randomnessProvider = ("Uniform Random Phases");
	seimicLabData.spectrumModel = ("Clough-Penzien Spectrum");
	seimicLabData.cpsdDecompositionMethod = ("RPS Cholesky Decomposition");
	seimicLabData.freqencyDistribution = ("Double Index Frequency");
	seimicLabData.modulationFunction = ("Bogdanoff-Goldberg-Bernard Modulation function");
	seimicLabData.direction = 1;

}

void RPSSeismicLabSimulation::WriteMapToRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{

	if (map.empty())
	{
		return;
	}

	QStringList mapkeylst;
	QStringList mapvaluelst;

	// Iterate though the map
	for (auto it1 = map.begin(); it1 != map.end(); ++it1)
	{
		mapkeylst.append(it1->first);
		mapvaluelst.append(it1->second);
	}

	QSettings settings;

	settings.beginGroup(settingsGroup);
	settings.setValue("mapkey", mapkeylst);
	settings.setValue("mapValue", mapvaluelst);
	settings.endGroup();

	count++;
}

void RPSSeismicLabSimulation::ReadMapFromRegistry(std::map<const QString, QString> &map, QString &settingsGroup, int &count)
{
	QSettings settings;

	settings.beginGroup(settingsGroup);
	QStringList mapkeylst = settings.value("mapkey").toStringList();
	QStringList mapvaluelst = settings.value("mapValue").toStringList();
	settings.endGroup();

	if (mapkeylst.isEmpty())
	{
		return;
	}

	for (int i = 0; i < mapkeylst.size(); ++i)
	{
		QString key = mapkeylst.at(i);
		QString value = mapvaluelst.at(i);

		map[key] = value;
		PluginManager::GetInstance().GetAllPlugedObjectsMap()[key] = value;
	}

	count++;
}

void RPSSeismicLabSimulation::SLWriteAllTobeInstallObjectsToRegistry()
{
	int count = 1;
	QString settingsGroup;

	settingsGroup = ("SLSimMethod"), count = 1;
	WriteMapToRegistry(CrpsSLSimulationMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLLoc"), count = 1;
	WriteMapToRegistry(CrpsSLLocationDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLXPSD"), count = 1;
	WriteMapToRegistry(CrpsSLXSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);
	
	settingsGroup = ("SLYPSD"), count = 1;
	WriteMapToRegistry(CrpsSLYSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);
	
	settingsGroup = ("SLZPSD"), count = 1;
	WriteMapToRegistry(CrpsSLZSpectrumFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLCoh"), count = 1;
	WriteMapToRegistry(CrpsSLCoherenceFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLDecomp"), count = 1;
	WriteMapToRegistry(CrpsSLPSDdecomMethodFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLFreq"), count = 1;
	WriteMapToRegistry(CrpsSLFrequencyDistributionFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLRand"), count = 1;
	WriteMapToRegistry(CrpsSLRandomnessFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLMod"), count = 1;
	WriteMapToRegistry(CrpsSLModulationFactory::GetOjectDescriptionMap(), settingsGroup, count);

	settingsGroup = ("SLDirSpec"), count = 1;
	WriteMapToRegistry(CrpsSLCorrelationFactory::GetOjectDescriptionMap(), settingsGroup, count);

	}

void RPSSeismicLabSimulation::SLReadAllTobeInstallObjectsFromRegistry()
{
	int count = 1;

	QString settingsGroup;

    settingsGroup = ("SLSimMethod"), count = 1;
	ReadMapFromRegistry(CrpsSLSimulationMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLLoc"), count = 1;
	ReadMapFromRegistry(CrpsSLLocationDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLXPSD"), count = 1;
	ReadMapFromRegistry(CrpsSLXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);
	
	settingsGroup = ("SLYPSD"), count = 1;
	ReadMapFromRegistry(CrpsSLYSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);
	
	settingsGroup = ("SLZPSD"), count = 1;
	ReadMapFromRegistry(CrpsSLZSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLCoh"), count = 1;
	ReadMapFromRegistry(CrpsSLCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLDecomp"), count = 1;
	ReadMapFromRegistry(CrpsSLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLFreq"), count = 1;
	ReadMapFromRegistry(CrpsSLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLRand"), count = 1;
	ReadMapFromRegistry(CrpsSLRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLMod"), count = 1;
	ReadMapFromRegistry(CrpsSLModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

	settingsGroup = ("SLDirSpec"), count = 1;
	ReadMapFromRegistry(CrpsSLCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);


}

void RPSSeismicLabSimulation::SLClearAllTobeInstallObjectsFromRegistry()
{
	QString settingsGroup;

	settingsGroup = ("SLSimMethod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLLoc");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLXPSD");
	ClearMapFromRegistry(settingsGroup);
	
	settingsGroup = ("SLYPSD");
	ClearMapFromRegistry(settingsGroup);
	
	settingsGroup = ("SLZPSD");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLCoh");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLDecomp");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLFreq");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLRand");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLMod");
	ClearMapFromRegistry(settingsGroup);

	settingsGroup = ("SLDirSpec");
	ClearMapFromRegistry(settingsGroup);

}

void RPSSeismicLabSimulation::ClearMapFromRegistry(QString &settingsGroup)
{
	QSettings settings;

	settings.beginGroup(settingsGroup);
	settings.remove(""); // removes the group, and all it keys
	settings.endGroup();
}

bool RPSSeismicLabSimulation::GetObjects(std::map<const QString, QString> &map, QStringList &lstObject, QString pluginName)
{
	if (!map.empty())
	{
		// Iterate though the map and show all the registed objects
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			if (!it->first.isEmpty())
			{
				if (it->second == pluginName)
				{
					lstObject.append(it->first);
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool RPSSeismicLabSimulation::GetToBeInstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));
	try
	{
		GetObjects(CrpsSLSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSLCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeismicLabSimulation::GetToBeUninstalledObjectsList(QStringList &lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));
	
	try
	{
		GetObjects(CrpsSLSimulationMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLXSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLYSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLZSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSLCorrelationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeismicLabSimulation::IsObjectInstalled(QString &object)
{
	if (IsThisObjectInstalled(CrpsSLSimulationMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLLocationDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLXSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLYSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLZSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLCoherenceFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLRandomnessFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLModulationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSLCorrelationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	
	return false;
}

bool RPSSeismicLabSimulation::UpdateObjectsMap(std::map<const QString, QString> &map, const QString &lstObject)
{
	if (!map.empty())
	{
		if (map.find(lstObject) != map.end())
		{
			map.erase(lstObject);
		}
	}

	return true;
}

bool RPSSeismicLabSimulation::UpdateObjectToSkipMap(std::map<const QString, QString> &map, const QString name, const QString pluginName)
{
	map[name] = pluginName;
	return true;
}

bool RPSSeismicLabSimulation::UpdateToBeInstalledObjectsMap(const QString &lstObject)
{
	try
	{
		UpdateObjectsMap(CrpsSLSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSLCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeismicLabSimulation::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
	try
	{
		UpdateObjectToSkipMap(CrpsSLSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLXSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLYSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLZSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSLCorrelationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
	}
	catch (const std::exception &e)
	{
		return false;
	}

	return true;
}

bool RPSSeismicLabSimulation::IsThisObjectInstalled(std::map<const QString, QString> &map, QString &object)
{
	if (!map.empty())
	{
		if (map.find(object) != map.end())
		{
			return true;
		}
	}

	return false;
}


void RPSSeismicLabSimulation::runSimulation()
{
  //   // Build an object
  // 	IrpsSeLRandomness* currentRndProvider = CrpsSeLRandomnessFactory::BuildRandomness(GetSeaLabData().randomnessProvider);

  // 	// Check whether good object
  // 	if (NULL == currentRndProvider) { return; }

  //   mat randomValueArray(GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

  // 	// Apply iniatial setting
  // 	currentRndProvider->GenerateRandomArrayFP(GetSeaLabData(), randomValueArray, information);

  //   QMessageBox::warning(
  //         this, ("sim"),
  //         QString::number(randomValueArray(0,0)));

  //   logInfo = ("hahahahahahaha");
  //   showResults(true);

  //   QString arrayName = ("Random Phase (%1,%2)").arg( GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

  //   Table *table = newTable(arrayName, GetSeaLabData().numberOfFrequency, GetSeaLabData().numberOfSpatialPosition);

  //   for (int j = 0; j < GetSeaLabData().numberOfSpatialPosition; j++) {
  //     for (int i = 0; i < GetSeaLabData().numberOfFrequency; i++) {
  //     table->setCellValue(i, j, randomValueArray(i,j));
  //       table->showNormal();

  //     // t->column(i)->setTextAt(i, randomValueArray(i,j));
  //   }  }
}
void RPSSeismicLabSimulation::pauseSimulation()
{
  
}
void RPSSeismicLabSimulation::stopSimulation()
{

}
void RPSSeismicLabSimulation::simulationOptions()
{
  std::unique_ptr<PRSSLSimuOptionsDlg> dlg(new PRSSLSimuOptionsDlg(this));
  if (dlg->exec() == QDialog::Accepted)
  {
      GetSeismicLabData().simulationMethod = dlg->currentsimulationMethod;
      GetSeismicLabData().randomnessProvider = dlg->currentRandomnessProvider;
      GetSeismicLabData().comparisonMode = dlg->comparisonMode;
      GetSeismicLabData().largeScaleSimulationMode = dlg->largeScaleMode;

  }
}




