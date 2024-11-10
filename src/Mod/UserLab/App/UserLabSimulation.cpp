/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>          *
 *                         *
 *   This file is part of the LabRPS development system.      *
 *                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.          *
 *                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                *
 *                         *
 ***************************************************************************/

#include "PreCompiled.h"

#include <Base/Uuid.h>

#include "UserLabSimulation.h"
#include "UserlabUtils.h"
#include <Mod/UserLabAPI/App/UserLabFeatureDescription.h>
#include <Mod/UserLabAPI/App/RPSUserLabAPI.h>
#include <Mod/UserLabAPI/App/UserLabFeatureSimulationMethod.h>
#include <Mod/UserLab/App/UserLabSimulationPy.h>
#include <Base/Console.h>
#include <App/Application.h>
#include <App/Document.h>
#include <App/RPSpluginManager.h>

using namespace App;
using namespace UserLab;
using namespace UserLabAPI;

PROPERTY_SOURCE(UserLab::UserLabSimulation, App::Simulation)

UserLabSimulation::UserLabSimulation()
{
    _simuData = new UserLabAPI::UserLabSimulationData();
   
    Base::Uuid id;
    ADD_PROPERTY_TYPE(Uid, (id), 0, App::Prop_None, "UUID of the simulation"); //not is use yet

    static const char* datagroup = "Basic Data";
    ADD_PROPERTY_TYPE(NumberOfSample, (1), datagroup, Prop_None,"This is the number of wind field sample in a simulation.");
    ADD_PROPERTY_TYPE(NumberOfTimeLags, (512), datagroup, Prop_None,"Number of time lags need for temporal correlation");
    ADD_PROPERTY_TYPE(Stationarity, (true), datagroup, Prop_None,"This specifies whether the simulated wind is stationary or not.");
    ADD_PROPERTY_TYPE(Gaussianity, (true), datagroup, Prop_None,"This specifies whether the simulated wind is gaussian or not.");
    ADD_PROPERTY_TYPE(ComparisonMode, (false), datagroup, Prop_None,"This specifies whether we are in comparison mode or not.");
    ADD_PROPERTY_TYPE(LargeScaleSimulationMode, (false), datagroup, Prop_None,"This specifies whether we are in large scale simulation mode or not.");
    ADD_PROPERTY_TYPE(IsSimulationSuccessful, (false), datagroup, Prop_None,"This specifies whether the simulation was successful or not.");
    ADD_PROPERTY_TYPE(IsInterruptionRequested, (false), datagroup, Prop_None,"This specifies whether the simulation has been interrupted or not.");
    ADD_PROPERTY_TYPE(UniformModulation, (true), datagroup, Prop_None,"This specifies whether a non stataionary wind is uniformly modulated or not.");

    static const char* locationgroup = "Location Distribution";
    ADD_PROPERTY_TYPE(NumberOfProcess, (3), locationgroup, App::Prop_None,"The number of simulation point which is the number of wind processes in a sample");
    ADD_PROPERTY_TYPE(LocationIndexJ, (1), locationgroup, Prop_None,"The index of the a given wind process in a wind field at a location J");
    ADD_PROPERTY_TYPE(LocationIndexK, (1), locationgroup, Prop_None,"The index of the a given wind process in a wind field at a location K");

    static const char* frequencygroup = "Frequency Discretization";
    ADD_PROPERTY_TYPE(NumberOfFrequency, (1024), frequencygroup, Prop_None,"The number of frequency increments");
    ADD_PROPERTY_TYPE(FrequencyIncrement, (0.0039), frequencygroup, Prop_None,"This is the frequency increment value");
    ADD_PROPERTY_TYPE(MinFrequency, (0.00), frequencygroup, Prop_None,"This is the minimum frequency value");
    ADD_PROPERTY_TYPE(MaxFrequency, (4.00), frequencygroup, Prop_None,"This is the maximum frequency value or the cutoff frequency");
    ADD_PROPERTY_TYPE(FrequencyIndex, (1), frequencygroup, Prop_None,"Index correponding to Kth frequency increment");

    static const char* timegroup = "Time Discretization";
    ADD_PROPERTY_TYPE(NumberOfTimeIncrements, (6144), timegroup, Prop_None,"This is the number of time increments");
    ADD_PROPERTY_TYPE(TimeIncrement, (0.25), timegroup, Prop_None,"This is the time increment value");
    ADD_PROPERTY_TYPE(MinTime, (0.00), timegroup, Prop_None, "This is the minimum time value");
    ADD_PROPERTY_TYPE(MaxTime, (1536.00), timegroup, Prop_None, "This is the maximum time value");
    ADD_PROPERTY_TYPE(TimeIndex, (1), timegroup, Prop_None,"Index correponding to Kth time increment");

    static const char* directiongroup = "Direction Discretization";
    ADD_PROPERTY_TYPE(NumberOfDirectionIncrements, (1000), directiongroup, Prop_None,"The number of direction increments");
    ADD_PROPERTY_TYPE(DirectionIncrement, (0.001), directiongroup, Prop_None,"This is the direction increment value");
    ADD_PROPERTY_TYPE(MinDirection, (0.00), directiongroup, Prop_None,"This is the minimum direction value");
    ADD_PROPERTY_TYPE(MaxDirection, (4.00), directiongroup, Prop_None,"This is the maximum direction value");
    ADD_PROPERTY_TYPE(DirectionIndex, (1), directiongroup, Prop_None,"Index correponding to Kth direction increment");

    static const char* waveLengthgroup = "Wave Length Discretization";
    ADD_PROPERTY_TYPE(NumberOfWaveLengthIncrements, (1000), waveLengthgroup, Prop_None,"The number of wave length increment");
    ADD_PROPERTY_TYPE(WaveLengthIncrement, (0.001), waveLengthgroup, Prop_None,"This is the wave length value");
    ADD_PROPERTY_TYPE(MinWaveLength, (0.00), waveLengthgroup, Prop_None,"This is the minimum wave length");
    ADD_PROPERTY_TYPE(MaxWaveLength, (4.00), waveLengthgroup, Prop_None,"This is the maximum wave length");
    ADD_PROPERTY_TYPE(WaveLengthIndex, (1), waveLengthgroup, Prop_None,"Index correponding to Kth wave length increment");

    static const char* featuregroup = "Userlab Features";
    static const char* someEnums[] = {"<None>", nullptr};

    ADD_PROPERTY_TYPE(SimulationMethod, ((long int)0), featuregroup, Prop_None,"Active simulation method name");
    
    ADD_PROPERTY_TYPE(NumberOfIncrementOfVariableX, (101), "Variable X", Prop_None, "The number of increments for the variable x");
	ADD_PROPERTY_TYPE(IndexOfVariableX, (1), "Variable X", Prop_None, "This current index of the variable x.");
	ADD_PROPERTY_TYPE(IncrementOfVariableX, (0.1), "Variable X", Prop_None, "This is the variable x increment value");
	ADD_PROPERTY_TYPE(MinVariableX, (-5.00), "Variable X", Prop_None, "This is the minimum x variable value");

    ADD_PROPERTY_TYPE(Phenomenon, ("Name"), 0, Prop_None, "The random phenonenon name");
    ADD_PROPERTY_TYPE(WorkingDirectoryPath, (Application::getHomePath()), 0, Prop_None, "The working directory path.");

    SimulationMethod.setEnums(someEnums);

    static const char* directions[] = {"Along wind", "Across wind", "Vertical wind", nullptr};
    ADD_PROPERTY_TYPE(WindDirection, ((long int)0), datagroup, Prop_None, "The wind direction");
    WindDirection.setEnums(directions);
}

UserLabSimulation::~UserLabSimulation() { delete _simuData; }

void UserLabSimulation::handleChangedPropertyName(Base::XMLReader& reader, const char* TypeName,            const char* PropName)
{
    Base::Type type = Base::Type::fromName(TypeName);
    App::DocumentObjectGroup::handleChangedPropertyName(reader, TypeName, PropName);
}

void UserLabSimulation::updateSimulationData()
{
    _simuData->numberOfSpatialPosition.setValue(this->NumberOfProcess.getValue());
    _simuData->numberOfFrequency.setValue(this->NumberOfFrequency.getValue());
    _simuData->numberOfSample.setValue(this->NumberOfSample.getValue());
    _simuData->numberOfTimeIncrements.setValue(this->NumberOfTimeIncrements.getValue());
    _simuData->locationJ.setValue(this->LocationIndexJ.getValue());
    _simuData->locationK.setValue(this->LocationIndexK.getValue());
    _simuData->frequencyIndex.setValue(this->FrequencyIndex.getValue());
    _simuData->directionIndex.setValue(this->DirectionIndex.getValue());
    _simuData->timeIndex.setValue(this->TimeIndex.getValue());
    _simuData->numberOfTimeLags.setValue(this->NumberOfTimeLags.getValue());
    _simuData->numberOfWaveLengthIncrements.setValue(this->NumberOfWaveLengthIncrements.getValue());
    _simuData->numberOfDirectionIncrements.setValue(this->NumberOfDirectionIncrements.getValue());
    _simuData->workingDirPath.setValue(this->WorkingDirectoryPath.getValue());
    _simuData->waveLengthIndex.setValue(this->WaveLengthIndex.getValue());
    _simuData->stationarity.setValue(this->Stationarity.getValue());
    _simuData->gaussianity.setValue(this->Gaussianity.getValue());
    _simuData->comparisonMode.setValue(this->ComparisonMode.getValue());
    _simuData->largeScaleSimulationMode.setValue(this->LargeScaleSimulationMode.getValue());
    _simuData->isSimulationSuccessful.setValue(this->IsSimulationSuccessful.getValue());
    _simuData->isInterruptionRequested.setValue(this->IsInterruptionRequested.getValue());
    _simuData->uniformModulation.setValue(this->UniformModulation.getValue());
    _simuData->minTime.setValue(this->MinTime.getValue());
    _simuData->maxTime.setValue(this->MaxTime.getValue());
    _simuData->timeIncrement.setValue(this->TimeIncrement.getValue());
    _simuData->minFrequency.setValue(this->MinFrequency.getValue());
    _simuData->frequencyIncrement.setValue(this->FrequencyIncrement.getValue());
    _simuData->maxFrequency.setValue(this->MaxFrequency.getValue());
    _simuData->minWaveLength.setValue(this->MinWaveLength.getValue());
    _simuData->maxWaveLength.setValue(this->MaxWaveLength.getValue());
    _simuData->waveLengthIncrement.setValue(this->WaveLengthIncrement.getValue());
    _simuData->minDirection.setValue(this->MinDirection.getValue());
    _simuData->maxDirection.setValue(this->MaxDirection.getValue());
    _simuData->directionIncrement.setValue(this->DirectionIncrement.getValue());
    _simuData->simulationMethod.setValue(this->SimulationMethod.getValueAsString());
    _simuData->numberOfIncrementOfVariableX.setValue(this->NumberOfIncrementOfVariableX.getValue());
    _simuData->indexOfVariableX.setValue(this->IndexOfVariableX.getValue());
    _simuData->incrementOfVariableX.setValue(this->IncrementOfVariableX.getValue());
    _simuData->minVariableX.setValue(this->MinVariableX.getValue());
}

bool UserLabSimulation::run() { return false; }

bool UserLabSimulation::stop() { return false; }

std::string UserLabSimulation::getPhenomenonName() const
{
    return UserLab::UserLabUtils::rpsPhenomenonWindVelocity.toUtf8().constData();
}

std::string UserLabSimulation::workbenchName() const { return "UserLab"; }

void UserLabSimulation::setSimulationData(UserLabAPI::UserLabSimulationData* simuData)
{
    _simuData = simuData;
}

UserLabAPI::UserLabSimulationData* UserLabSimulation::getSimulationData() const { return _simuData; }

void UserLabSimulation::userFeatureInitalSetting(QString group, QString currentSelected)
{
    if (!_simuData)
        return;

    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return;

    if (group == UserLab::UserLabUtils::objGroupSimulationMethod) {
        UserLabAPI::IrpsULSimulationMethod* activefeature = static_cast<UserLabAPI::IrpsULSimulationMethod*>(
    doc->getObject(currentSelected.toUtf8().constData()));

    if (!activefeature) {
    return;
        }

    auto simuData = getSimulationData();
    if (simuData)
    activefeature->OnInitialSetting(*simuData);
    }
}

QStringList UserLabSimulation::findAllPluggedUserLabFeatures(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == UserLab::UserLabUtils::objGroupSimulationMethod) {
        typedef IrpsULSimulationMethod* (*CreateSimuMethodCallback)();
        std::map<const std::string, CreateSimuMethodCallback>::iterator simuMethIt;
        for (simuMethIt = CrpsSimulationMethodFactory::GetObjectNamesMap().begin();
             simuMethIt != CrpsSimulationMethodFactory::GetObjectNamesMap().end(); ++simuMethIt) {
            theList.append(QString::fromUtf8(simuMethIt->first.c_str()));
        }
        return theList;
    }
    
    return theList;
}



QStringList UserLabSimulation::findAllFeatureMethods(QString group)
{
    QStringList theList;
    theList.append(QString::fromLatin1("<None>"));
    if (group == UserLab::UserLabUtils::objGroupSimulationMethod) {
        theList.append(UserLab::UserLabUtils::Simulate);
        theList.append(UserLab::UserLabUtils::SimulateInLargeScaleMode);
        return theList;
    }
    
    return theList;
}

UserLabAPI::UserLabFeature* UserLabSimulation::createFeature(Base::Type type, std::string pluggedObjectTypeName, std::string name)
{
    //get the active document
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    //make unique name for this new feature in the active document (its parent document)
    std::string uniqueName = doc->getUniqueObjectName(name.c_str());

    if (type == UserLabAPI::UserLabFeatureSimulationMethod::getClassTypeId()) {
        UserLabAPI::UserLabFeatureSimulationMethod* newFeature = CrpsSimulationMethodFactory::BuildObject(pluggedObjectTypeName);

        if (NULL == newFeature) {
    return nullptr;
        }
        App::GetApplication().getActiveDocument()->addObject(newFeature, uniqueName.c_str());

        return newFeature;
    }
}

void UserLabSimulation::setEnums(Base::Type type)
{

    if (type == UserLabAPI::UserLabFeatureSimulationMethod::getClassTypeId()) {
        SimulationMethod.setEnums(findAllUserLabFeaturesOfThisType(type));
    }
}

void UserLabSimulation::resetAllEnums()
{
  SimulationMethod.setEnums(findAllUserLabFeaturesOfThisType(UserLabAPI::UserLabFeatureSimulationMethod::getClassTypeId()));
}

QStringList UserLabSimulation::findAllUserLabFeatures(Base::Type type)
{
    QStringList featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) return featureList;
    auto features = doc->getObjectsOfType(type);
    for (auto& feat : features) {
       featureList.append(QString::fromUtf8(feat->getNameInDocument()));
    }
    return featureList;
}

QStringList UserLabSimulation::findAllUserLabFeaturesByGoupAndType(QString group, QString type)
{
    QStringList featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) return featureList;
    auto features = this->getAllChildren();
    for (auto& feat : features) {
       auto myFeat = static_cast<UserLabAPI::UserLabFeature*>(feat);
       if (myFeat && myFeat->FeatureType.getStrValue() == type.toUtf8().constData() && myFeat->FeatureGroup.getStrValue() == group.toUtf8().constData())
    featureList.append(QString::fromUtf8(myFeat->getNameInDocument()));
    }
    return featureList;
}

std::vector<std::string> UserLabSimulation::findAllUserLabFeaturesOfThisType(Base::Type type)
{
    std::vector<std::string> featureList;
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc)return featureList;
    auto features = doc->getObjectsOfType(type);
    for (auto& feat : features) {
       App::DocumentObjectGroup* group = feat->getGroup();
       if (group)
       {
    if (this->getNameInDocument() == feat->getGroup()->getNameInDocument())
        featureList.emplace_back(feat->getNameInDocument());
       }
    }
    if (featureList.empty())
        featureList.emplace_back("<None>");

    return featureList;
}

Base::Type UserLabSimulation::getRPSType(QString group)
{

    if (group == UserLab::UserLabUtils::objGroupSimulationMethod) {
        return UserLabAPI::IrpsULSimulationMethod::getClassTypeId();
    }
}

std::vector<Base::Type> UserLabSimulation::getRPSTypesOfPluggableFeatures()
{
    std::vector<Base::Type> types;
    types.emplace_back(UserLabAPI::UserLabFeatureSimulationMethod::getClassTypeId());
    return types;
}

std::vector<QString> UserLabSimulation::getUserLabPluggableFeatures()
{
    std::vector<QString> groups;
    groups.emplace_back(UserLab::UserLabUtils::objGroupSimulationMethod);
    return groups;
}

bool UserLabSimulation::doubleClicked(void) 
{
    return true;
}

void UserLabSimulation::onChanged(const App::Property* prop)
{
    if (prop == &LocationIndexJ) {
        if (LocationIndexJ.getValue() < 0)
    LocationIndexJ.setValue(0);
        if (LocationIndexJ.getValue() > NumberOfProcess.getValue() - 1)
    LocationIndexJ.setValue(NumberOfProcess.getValue() - 1);
    }
    else if (prop == &LocationIndexK) {
        if (LocationIndexK.getValue() < 0)
    LocationIndexK.setValue(0);
        if (LocationIndexK.getValue() > NumberOfProcess.getValue() - 1)
    LocationIndexK.setValue(NumberOfProcess.getValue() - 1);
    }
    else if (prop == &FrequencyIndex) {
        if (FrequencyIndex.getValue() < 0)
    FrequencyIndex.setValue(0);
        if (FrequencyIndex.getValue() > NumberOfFrequency.getValue() - 1)
    FrequencyIndex.setValue(NumberOfFrequency.getValue() - 1);
    }
    else if (prop == &TimeIndex) {
        if (TimeIndex.getValue() < 0)
    TimeIndex.setValue(0);
        if (TimeIndex.getValue() > NumberOfTimeIncrements.getValue() - 1)
    TimeIndex.setValue(NumberOfTimeIncrements.getValue() - 1);
    }
    else if (prop == &DirectionIndex) {
        if (DirectionIndex.getValue() < 0)
    DirectionIndex.setValue(0);
        if (DirectionIndex.getValue() > NumberOfDirectionIncrements.getValue() - 1)
    DirectionIndex.setValue(NumberOfDirectionIncrements.getValue() - 1);
    }
    else if (prop == &NumberOfSample) {

        if (NumberOfSample.getValue() < 1) {
    NumberOfSample.setValue(1);
        }

        if (NumberOfSample.getValue() > 1)
        {
    LargeScaleSimulationMode.setValue(true);
        }
        else {

    LargeScaleSimulationMode.setValue(false);
        }
    }
    else if ((prop == &NumberOfProcess)
     || (prop == &NumberOfFrequency)
     || (prop == &NumberOfTimeIncrements) 
     || (prop == &NumberOfDirectionIncrements)
     || (prop == &NumberOfIncrementOfVariableX)) {

        ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/UserLab/General");
        int limitAutoAct = hGrp->GetBool("AutomaticLargeScaleModeActivation", true);
    
        hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/Mod/UserLab/Limit");
        int numberOfProcessLimit = hGrp->GetInt("MaxSPN", 300);
        int numberOfFrequencyLimit = hGrp->GetInt("MaxFIN", 102400);
        int numberOfTimeIncrementsLimit = hGrp->GetInt("MaxTIN", 61400);
        int numberOfDirectionIncrementsLimit = hGrp->GetInt("MaxDIN", 100000);
        int numberOfIncrementOfVariableXLimit = hGrp->GetInt("MaxXIN", 100000);

        if (limitAutoAct)
        {
    if ((NumberOfProcess.getValue() > numberOfProcessLimit)
        || (NumberOfFrequency.getValue() > numberOfFrequencyLimit)
        || (NumberOfTimeIncrements.getValue() > numberOfTimeIncrementsLimit)
        || (NumberOfDirectionIncrements.getValue() > numberOfDirectionIncrementsLimit)
        || (NumberOfIncrementOfVariableX.getValue() > numberOfIncrementOfVariableXLimit)) {

        LargeScaleSimulationMode.setValue(true);
    }
    else {
        LargeScaleSimulationMode.setValue(false);
    }
        }
       

    }
   
    updateSimulationData();

    Simulation::onChanged(prop);
}


UserLabAPI::UserLabFeatureDescription* UserLabSimulation::GetUserLabFeatureDescription(const QString& objectGroup, const QString& objName)
{
    UserLabFeatureDescription* pluggedUserLabFeatureDescription = new UserLabFeatureDescription();
    std::string pluginName;
    std::string descrip;
    std::string pubTitle;
    std::string pubLink;
    std::string pubAuthor;
    std::string pubDate;
    std::string version;
    bool stationarity;
    std::string objectName = objName.toUtf8().constData();

   if (objectGroup == UserLab::UserLabUtils::objGroupSimulationMethod) {
        pluginName = CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap()[objectName];
        descrip = CrpsSimulationMethodFactory::GetOjectDescriptionMap()[objectName];
        pubTitle = CrpsSimulationMethodFactory::GetTitleMap()[objectName];
        pubLink = CrpsSimulationMethodFactory::GetLinkMap()[objectName];
        pubAuthor = CrpsSimulationMethodFactory::GetAuthorMap()[objectName];
        pubDate = CrpsSimulationMethodFactory::GetDateMap()[objectName];
        version = CrpsSimulationMethodFactory::GetVersionMap()[objectName]; 
        stationarity = CrpsSimulationMethodFactory::GetStationarityMap()[objectName];
    }

    pluggedUserLabFeatureDescription->PluginName.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginName().toUtf8().constData());
    pluggedUserLabFeatureDescription->ReleaseDate.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())] ->GetPluginReleaseDate().toUtf8().constData());
    pluggedUserLabFeatureDescription->Path.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginSubFolder().toUtf8().constData());
    pluggedUserLabFeatureDescription->Author.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginAuthor().toUtf8().constData());
    pluggedUserLabFeatureDescription->PluginVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetPluginVersion().toUtf8().constData());
    pluggedUserLabFeatureDescription->LabRPSVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetLabRPSVersion().toUtf8().constData());
    pluggedUserLabFeatureDescription->APIVersion.setValue(App::PluginManager::GetInstance().GetInstalledPluginsNameMap()[QString::fromUtf8(pluginName.c_str())]->GetAPIVersion().toUtf8().constData());
    pluggedUserLabFeatureDescription->ObjectName.setValue(objectName);
    pluggedUserLabFeatureDescription->Version.setValue(version);
    pluggedUserLabFeatureDescription->Stationarity.setValue(stationarity);
    pluggedUserLabFeatureDescription->Description.setValue(descrip);
    pluggedUserLabFeatureDescription->PublicationTitle.setValue(pubTitle);
    pluggedUserLabFeatureDescription->PublicationLink.setValue(pubLink);
    pluggedUserLabFeatureDescription->PublicationAuthor.setValue(pubAuthor);
    pluggedUserLabFeatureDescription->PublicationDate.setValue(pubDate);

    return pluggedUserLabFeatureDescription;
}

void UserLabSimulation::createNewSimulation() {}

PyObject* UserLabSimulation::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        PythonObject = Py::Object(new UserLabSimulationPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}

bool UserLabSimulation::simulate(mat &dVelocityArray, std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    UserLabAPI::IrpsULSimulationMethod* activefeature = static_cast<UserLabAPI::IrpsULSimulationMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    dVelocityArray.resize(this->getSimulationData()->numberOfTimeIncrements.getValue(), this->getSimulationData()->numberOfSpatialPosition.getValue() + 1);
    dVelocityArray.setZero();

    bool returnResult = activefeature->Simulate(*this->getSimulationData(), dVelocityArray);

    if (!returnResult) {
     Base::Console().Error("The computation of the wind velocity matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();

    return true;

}

bool UserLabSimulation::simulateInLargeScaleMode(std::string& featureName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return false;
    UserLabAPI::IrpsULSimulationMethod* activefeature = static_cast<UserLabAPI::IrpsULSimulationMethod*>(doc->getObject(_simuData->simulationMethod.getValue()));
    if (!activefeature) {
        Base::Console().Error("No valid active simulation method feature found.\n");
        return false;
    }
    QString fineName = QString::fromLatin1("WindVelocity");
    bool returnResult = activefeature->SimulateInLargeScaleMode(*this->getSimulationData(), fineName);
    if (!returnResult) {
     Base::Console().Error("The computation of the wind velocity matrix has failed.\n");
     return false;
    }
    featureName = activefeature->Label.getStrValue();
    return true;
}


void UserLabSimulation::setActiveFeature(App::RPSFeature* feature)
{
    if (feature->getTypeId().isDerivedFrom(UserLabAPI::UserLabFeatureSimulationMethod::getClassTypeId())) {
        _simuData->simulationMethod.setValue(feature->getNameInDocument());  
    }
}

App::RPSFeature* UserLabSimulation::getActiveFeature(const QString group)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;

    if (group == UserLab::UserLabUtils::objGroupSimulationMethod) {
        return static_cast<App::RPSFeature*>(doc->getObject(_simuData->simulationMethod.getValue()));  
    }
}

std::vector<App::RPSFeature*> UserLabSimulation::getAllFeatures(const QString group)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return std::vector<App::RPSFeature*>();
    std::vector<DocumentObject*> docObjects = doc->getObjects();
    std::vector<App::RPSFeature*> featureList;
    for (std::vector<DocumentObject*>::iterator j = docObjects.begin(); j != docObjects.end(); ++j) {
        if ((*j)->getTypeId().isDerivedFrom(getRPSType(group))) {
            featureList.push_back(static_cast<App::RPSFeature*>(*j));
        }
    }
    return featureList;
}

App::DocumentObject* UserLabSimulation::getActiveSimulationMethod()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return nullptr;
    App::DocumentObject* activeFeature = doc->getObject(_simuData->simulationMethod.getValue());
    return activeFeature;
}

App::DocumentObject*  UserLabSimulation::addFeature(const std::string featureName, const std::string simulationName, const std::string featureTypeName, const std::string featureGroup)
{
    Base::Type type = getRPSType(QString::fromStdString(featureGroup));
    
    //create the feature
	UserLabAPI::UserLabFeature* newFeature = this->createFeature(type, featureTypeName, featureName);

	if (!newFeature)
		return nullptr;

	//set the feature properties
	auto featureProperties = this->GetUserLabFeatureDescription(QString::fromLatin1(featureGroup.c_str()), QString::fromLatin1(featureTypeName.c_str()));
    newFeature->FeatureGroup.setValue(featureGroup);
    newFeature->FeatureType.setValue(featureTypeName);
    newFeature->Author.setValue(featureProperties->Author.getValue());
    newFeature->PublicationTopic.setValue(featureProperties->PublicationTitle.getValue());
    newFeature->PublicationDate.setValue(featureProperties->PublicationDate.getValue());
    newFeature->LinkToPublication.setValue(featureProperties->PublicationLink.getValue());
    newFeature->PublicationAuthor.setValue(featureProperties->PublicationAuthor.getValue());
    newFeature->Version.setValue(featureProperties->Version.getValue());
    newFeature->IsStationary.setValue(featureProperties->Stationarity.getValue());
    newFeature->PluginName.setValue(featureProperties->PluginName.getValue());
    newFeature->PluginVersion.setValue(featureProperties->PluginVersion.getValue());
    newFeature->APIVersion.setValue(featureProperties->APIVersion.getValue());
    newFeature->ReleaseDate.setValue(featureProperties->ReleaseDate.getValue());
	newFeature->Simulation.setValue(this->getNameInDocument());

    this->setActiveFeature(newFeature);
	App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(static_cast<App::DocumentObject*>(this));
    newFeature->recomputeFeature();
	group->addObject(newFeature);
    this->setEnums(type);
    App::GetApplication().getActiveDocument()->recompute();

    return newFeature;
}
