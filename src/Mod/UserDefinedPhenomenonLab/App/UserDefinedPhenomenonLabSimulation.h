/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
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

#ifndef UserDefinedPhenomenonLab_UserDefinedPhenomenonLabSimulation_H
#define UserDefinedPhenomenonLab_UserDefinedPhenomenonLabSimulation_H

#include <App/PropertyStandard.h>
#include <App/Simulation.h>
#include <App/PropertyUnits.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>
#include <Mod/UserDefinedPhenomenonLab/UserDefinedPhenomenonLabGlobal.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabSimulationData.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeature.h>

namespace UserDefinedPhenomenonLabAPI
{
	class UserDefinedPhenomenonLabFeatureDescription;
}

namespace UserDefinedPhenomenonLab {
 class UserDefinedPhenomenonLabSimulationPy; // the python UserDefinedPhenomenonLabSimulation class

/**
 * @brief Container of objects relevant to one simulation.
 *
 * @details
 *  A Simulation contains all objects necessary for a complete specification
 *  of a simulation. After computing it also contains the result of the
 *  simulation. The Simulation object is a container but also offers ways to run the UserDefinedPhenomenonLab features in the simulation.
 *
 *  The Simulation class is essentially a App::DocumentObjectGroup. It handles
 *  all the container stuff. The difference is that the Simulation document
 *  object uses a different ViewProvider, has a Uid property and does some
 *  compatibility handling via handleChangedPropertyName.
 *
 *  This implies that it is not checked which objects are put into the
 *  Simulation object. Every document object of LabRPS can be part of a
 *  Simulation.
 */
 class UserDefinedPhenomenonLabExport UserDefinedPhenomenonLabSimulation: public App::Simulation
 {
    
    PROPERTY_HEADER(UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation);

public:

    UserDefinedPhenomenonLabSimulation();
    virtual ~UserDefinedPhenomenonLabSimulation();

    App::PropertyString Phenomenon;
	App::PropertyInteger NumberOfProcess;
	App::PropertyInteger NumberOfFrequency;
	App::PropertyInteger NumberOfSample;
	App::PropertyInteger NumberOfTimeIncrements;
	App::PropertyInteger LocationIndexJ;
	App::PropertyInteger LocationIndexK;
	App::PropertyInteger FrequencyIndex;
	App::PropertyInteger DirectionIndex;
	App::PropertyInteger TimeIndex;
	App::PropertyInteger NumberOfTimeLags;
	App::PropertyInteger NumberOfWaveLengthIncrements;
	App::PropertyInteger NumberOfDirectionIncrements;
	App::PropertyInteger WaveLengthIndex;
	App::PropertyBool Stationarity;
	App::PropertyBool Gaussianity;
	App::PropertyBool  ComparisonMode;
	App::PropertyBool  LargeScaleSimulationMode;
	App::PropertyBool IsSimulationSuccessful;
	App::PropertyBool IsInterruptionRequested;
	App::PropertyBool UniformModulation;
	App::PropertyTime MinTime;
	App::PropertyTime MaxTime;
	App::PropertyTime TimeIncrement;
	App::PropertyFrequency MinFrequency;
	App::PropertyFrequency FrequencyIncrement;
	App::PropertyFrequency MaxFrequency;
	App::PropertyLength MinWaveLength;
	App::PropertyLength MaxWaveLength;
	App::PropertyLength WaveLengthIncrement;
	App::PropertyAngle MinDirection;
	App::PropertyAngle MaxDirection;
	App::PropertyAngle DirectionIncrement;
    App::PropertyString WorkingDirectoryPath;
	App::PropertyEnumeration WindDirection;
	App::PropertyInteger NumberOfIncrementOfVariableX;
    App::PropertyInteger IndexOfVariableX;
    App::PropertyFloat IncrementOfVariableX;
    App::PropertyFloat MinVariableX;

    App::PropertyEnumeration SimulationMethod;

    App::PropertyUUID    Uid;

    virtual const char* getViewProviderName() const {
        return "UserDefinedPhenomenonLabGui::ViewProviderUserDefinedPhenomenonLabSimulation";
    }

protected:

    virtual void handleChangedPropertyName(
        Base::XMLReader &reader, const char * TypeName, const char *PropName);
public:
    /**
  * run the simulation.
  */
    virtual bool run();

    virtual bool stop();

    // get the name of the random phenomenon this simulation with produice
    virtual std::string getPhenomenonName() const;

    // get the name of the workbench that implement this simulation
    virtual std::string workbenchName() const;

    void setSimulationData(UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabSimulationData* simuData);
    UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabSimulationData* getSimulationData() const;

    UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature* createFeature(Base::Type type, std::string pluggedObjectTypeName,
                                       std::string name);
	void setEnums(Base::Type type);
    void resetAllEnums();

    void userDefinedPhenomenonFeatureInitalSetting(QString group, QString currentSelected);
    static QStringList findAllPluggedUserDefinedPhenomenonLabFeatures(QString group);
    static QStringList findAllFeatureMethods(QString group);

    QStringList findAllUserDefinedPhenomenonLabFeatures(Base::Type type);
	std::vector<std::string> findAllUserDefinedPhenomenonLabFeaturesOfThisType(Base::Type type);
    QStringList findAllUserDefinedPhenomenonLabFeaturesByGoupAndType(QString group, QString type);
    std::vector<QString> getUserDefinedPhenomenonLabPluggableFeatures();
    std::vector<Base::Type> getRPSTypesOfPluggableFeatures();
    Base::Type getRPSType(QString group);

	void updateSimulationData();

	UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeatureDescription* GetUserDefinedPhenomenonLabFeatureDescription(const QString& objectGroup, const QString& objName);

    virtual bool doubleClicked(void);
	virtual void onChanged(const App::Property* prop);

	void createNewSimulation();

	virtual PyObject *getPyObject(void) override;

public:

    App::DocumentObject* getActiveSimulationMethod();
   
    void setActiveFeature(App::RPSFeature* feature);
    App::RPSFeature* getActiveFeature(const QString group);
    std::vector <App::RPSFeature*> getAllFeatures(const QString group);

    bool simulate(mat &dVelocityArray, std::string& featureName);
    bool simulateInLargeScaleMode(std::string& featureName);
    App::DocumentObject* addFeature(const std::string featureName, const std::string simulationName, const std::string featureTypeName, const std::string featureGroup);

private:
    UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabSimulationData* _simuData;

protected: 
    Py::SmartPtr PythonObject;
};

} //namespace UserDefinedPhenomenonLab


#endif // UserDefinedPhenomenonLab_UserDefinedPhenomenonLabSimulation_H
