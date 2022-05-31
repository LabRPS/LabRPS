#pragma once

#ifndef RPSSESCOREAPI_H
#define RPSSESCOREAPI_H

#include "RPSSeaLabAPIdefines.h"
#include "IrpsSeLSimulationMethod.h"
#include "IrpsSeLCoherence.h"
#include "IrpsSeLLocationDistribution.h"
#include "IrpsSeLSpectrum.h"
#include "IrpsSeLFrequencyDistribution.h"
#include "IrpsSeLRandomness.h"
#include "IrpsSeLPSDdecompositionMethod.h"
#include "IrpsSeLCorrelation.h"
#include "IrpsSeLModulation.h"
#include "IrpsSeLMean.h"
#include "IrpsSeLDirectionSpreadingFunction.h"
#include "IrpsSeLDirectionDistribution.h"
#include "IrpsSeLDirectionalSpectrum.h"
#include <map>
#include<vector>


///
/// A factory object in LabRPS
///

class RPS_CORE_API  CrpsSeLSimulationMethodFactory
{
public:
	typedef IrpsSeLSimulationMethod *(*CreateSLSimulationMethodCallback)();

	static void InitializeSLSimulationMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterSLSimulationMethod(const QString &name, const QString &pluginName, const QString &description, CreateSLSimulationMethodCallback cb);

	static void UnregisterSLSimulationMethod(const QString &name, const QString &pluginName);

	static IrpsSeLSimulationMethod *BuildSLSimulationMethod(const QString &name);

	static std::map<const QString, CreateSLSimulationMethodCallback>& GetSLSimulationMethodNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateSLSimulationMethodCallback> CallbackMap;
	static CallbackMap mSLSimulationMethods;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};


///////////Coherence///////////////

class RPS_CORE_API  CrpsSeLCoherenceFactory
{
public:
	typedef IrpsSeLCoherence *(*CreateCoherenceCallback)();

	static void InitializeCoherence(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateCoherenceCallback cb);

	static void UnregisterCoherence(const QString &name, const QString &pluginName);

	static IrpsSeLCoherence *BuildCoherence(const QString &name);

	static std::vector<QString> GetNameVector();

	static std::map<const QString, CreateCoherenceCallback>& GetCoherenceNamesMap();

	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateCoherenceCallback> CallbackMap;
	static CallbackMap mCoherences;
	static std::vector<QString> mCoherenceNames;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};

//////////////////////////////////Location distribution//////////////////////////////////////////////


class RPS_CORE_API  CrpsSeLLocationDistributionFactory
{
public:
	typedef IrpsSeLLocationDistribution *(*CreateLocDistrCallback)();

	static void InitializeLocationDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateLocDistrCallback cb);

	static void UnregisterLocationDistribution(const QString &name, const QString &pluginName);

	static IrpsSeLLocationDistribution *BuildLocationDistribution(const QString &name);

	static std::vector<QString> GetLocDistrNamesVector();

	static std::map<const QString, CreateLocDistrCallback>& GetLocDistrNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateLocDistrCallback> CallbackMap;
	static CallbackMap mLocationDistributions;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};

//////////////////////// Mean//////////////////////////////////////////////////

class RPS_CORE_API CrpsSeLMeanFactory
{
public:
	typedef IrpsSeLMean *(*CreateMeanCallback)();

	static void InitializeMean(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterMean(const QString &name, const QString &pluginName, const QString &description, CreateMeanCallback cb);

	static void UnregisterMean(const QString &name, const QString &pluginName);

	static IrpsSeLMean *BuildMean(const QString &name);

	static std::map<const QString, CreateMeanCallback>& GetMeanNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateMeanCallback> CallbackMap;
	static CallbackMap mMeans;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};


//////////////////////// Along wind Sepctrum//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLXSpectrumFactory
{
public:
	typedef IrpsSeLSpectrum *(*CreateXSpectrumCallback)();

	static void InitializeXSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateXSpectrumCallback cb);

	static void UnregisterXSpectrum(const QString &name, const QString &pluginName);

	static IrpsSeLSpectrum *BuildXSpectrum(const QString &name);

	static std::map<const QString, CreateXSpectrumCallback>& GetXSpectrumNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateXSpectrumCallback> CallbackMap;
	static CallbackMap mXSpectrums;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
};


////////////////////////Frequency distribution//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLFrequencyDistributionFactory
{
public:
	typedef IrpsSeLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

	static void InitializeFrequencyDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateFrequencyDistributionCallback cb);

	static void UnregisterFrequencyDistribution(const QString &name, const QString &pluginName);

	static IrpsSeLFrequencyDistribution *BuildFrequencyDistribution(const QString &name);

	static std::map<const QString, CreateFrequencyDistributionCallback>& GetFrequencyDistributionNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateFrequencyDistributionCallback> CallbackMap;
	static CallbackMap mFrequencyDistributions;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
};


////////////////////////Randomness//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLRandomnessFactory
{
public:
	typedef IrpsSeLRandomness *(*CreateRandomnessCallback)();

	static void InitializeRandomness(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateRandomnessCallback cb);

	static void UnregisterRandomness(const QString &name, const QString &pluginName);

	static IrpsSeLRandomness *BuildRandomness(const QString &name);

	static std::map<const QString, CreateRandomnessCallback>& GetRandomnessNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateRandomnessCallback> CallbackMap;
	static CallbackMap mRandomness;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};


////////////////////////psd decomposition//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLPSDdecomMethodFactory
{
public:
	typedef IrpsSeLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

	static void InitializePSDdecomMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreatePSDdecomMethodCallback cb);

	static void UnregisterPSDdecomMethod(const QString &name, const QString &pluginName);

	static IrpsSeLPSDdecompositionMethod *BuildPSDdecomMethod(const QString &name);

	static std::map<const QString, CreatePSDdecomMethodCallback>& GetPSDdecomMethodNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreatePSDdecomMethodCallback> CallbackMap;
	static CallbackMap mPSDdecomMethods;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};

////////////////////////Correlation//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLCorrelationFactory
{
public:
	typedef IrpsSeLCorrelation *(*CreateCorrelationCallback)();

	static void InitializeCorrelation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateCorrelationCallback cb);

	static void UnregisterCorrelation(const QString &name, const QString &pluginName);

	static IrpsSeLCorrelation *BuildCorrelation(const QString &name);

	static std::map<const QString, CreateCorrelationCallback>& GetCorrelationNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateCorrelationCallback> CallbackMap;
	static CallbackMap mCorrelations;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};

////////////////////////Modulation//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLModulationFactory
{
public:
	typedef IrpsSeLModulation *(*CreateModulationCallback)();

	static void InitializeModulation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateModulationCallback cb);

	static void UnregisterModulation(const QString &name, const QString &pluginName);

	static IrpsSeLModulation *BuildModulation(const QString &name);

	static std::map<const QString, CreateModulationCallback>& GetModulationNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();


private:
	typedef std::map<const QString, CreateModulationCallback> CallbackMap;
	static CallbackMap mModulations;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};

////////////////////////Directional spectrum//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLDirectionalSpectrumFactory
{
public:
	typedef IrpsSeLDirectionalSpectrum *(*CreateSLDirectionalSpectrumCallback)();

	static void InitializeDirectionalSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterDirectionalSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateSLDirectionalSpectrumCallback cb);

	static void UnregisterDirectionalSpectrum(const QString &name, const QString &pluginName);

	static IrpsSeLDirectionalSpectrum *BuildDirectionalSpectrum(const QString &name);

	static std::map<const QString, CreateSLDirectionalSpectrumCallback>& GetDirectionalSpectrumNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateSLDirectionalSpectrumCallback> CallbackMap;
	static CallbackMap mDirectionalSpectrums;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};


////////////////////////DirectionDistribution//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLDirectionDistributionFactory
{
public:
	typedef IrpsSeLDirectionDistribution *(*CreateSLDirectionDistributionCallback)();

	static void InitializeDirectionDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterDirectionDistribution(const QString &name, const QString &pluginName, const QString &description, CreateSLDirectionDistributionCallback cb);

	static void UnregisterDirectionDistribution(const QString &name, const QString &pluginName);

	static IrpsSeLDirectionDistribution *BuildDirectionDistribution(const QString &name);

	static std::map<const QString, CreateSLDirectionDistributionCallback>& GetDirectionDistributionNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateSLDirectionDistributionCallback> CallbackMap;
	static CallbackMap mDirectionDistributions;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};

////////////////////////DirectionSpreadingFunction//////////////////////////////////////////////////

class RPS_CORE_API  CrpsSeLDirectionSpreadingFunctionFactory
{
public:
	typedef IrpsSeLDirectionSpreadingFunction *(*CreateSLDirectionSpreadingFunctionCallback)();

	static void InitializeDirectionSpreadingFunction(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterDirectionSpreadingFunction(const QString &name, const QString &pluginName, const QString &description, CreateSLDirectionSpreadingFunctionCallback cb);

	static void UnregisterDirectionSpreadingFunction(const QString &name, const QString &pluginName);

	static IrpsSeLDirectionSpreadingFunction *BuildDirectionSpreadingFunction(const QString &name);

	static std::map<const QString, CreateSLDirectionSpreadingFunctionCallback>& GetDirectionSpreadingFunctionNamesMap();
	static QString GetOwnerPlugin();
	static void SetOwnerPlugin(QString ownerPlugin);
	/*static QString GetDescription();
	static void SetDescription(QString description);*/
	static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
	static std::map<const QString, QString> & GetOjectDescriptionMap();
	static std::map<const QString, QString> & GetOjectAndPluginMap();
	static std::map<const QString, QString> & GetTitleMap();
	static std::map<const QString, QString> & GetLinkMap();
	static std::map<const QString, QString> & GetAuthorMap();
	static std::map<const QString, QString> & GetDateMap();
	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();

private:
	typedef std::map<const QString, CreateSLDirectionSpreadingFunctionCallback> CallbackMap;
	static CallbackMap mDirectionSpreadingFunctions;
	static QString mOwnerPlugin;
	//static QString mDescription;
	static std::map<const QString, QString> mTobeInstalledObjectsMap;
	static std::map<const QString, QString> mOjectDescriptionMap;
	static std::map<const QString, QString> mOjectAndPluginMap;
	static std::map<const QString, QString> mTitleMap;
	static std::map<const QString, QString> mLinkMap;
	static std::map<const QString, QString> mAuthorMap;
	static std::map<const QString, QString> mDateMap;
	static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;

};
#endif