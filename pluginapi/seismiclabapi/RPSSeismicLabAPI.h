#ifndef RPSWSCOREAPI_H
#define RPSWSCOREAPI_H

#include "RPSSeismicLabAPIdefines.h"
#include "IrpsSLSimulationMethod.h"
#include "IrpsSLCoherence.h"
#include "IrpsSLLocationDistribution.h"
#include "IrpsSLXSpectrum.h"
#include "IrpsSLZSpectrum.h"
#include "IrpsSLYSpectrum.h"
#include "IrpsSLFrequencyDistribution.h"
#include "IrpsSLRandomness.h"
#include "IrpsSLPSDdecompositionMethod.h"
#include "IrpsSLCorrelation.h"
#include "IrpsSLModulation.h"

#include <map>
#include<vector>


///
/// A factory object in LabRPS
///

class RPS_CORE_API CrpsSLSimulationMethodFactory
{
public:
	typedef IrpsSLSimulationMethod *(*CreateSLSimulationMethodCallback)();

	static void InitializeSLSimulationMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterSLSimulationMethod(const QString &name, const QString &pluginName, const QString &description, CreateSLSimulationMethodCallback cb);

	static void UnregisterSLSimulationMethod(const QString &name, const QString &pluginName);

	static IrpsSLSimulationMethod *BuildSLSimulationMethod(const QString &name);

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

class RPS_CORE_API CrpsSLCoherenceFactory
{
public:
	typedef IrpsSLCoherence *(*CreateCoherenceCallback)();

	static void InitializeCoherence(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateCoherenceCallback cb);

	static void UnregisterCoherence(const QString &name, const QString &pluginName);

	static IrpsSLCoherence *BuildCoherence(const QString &name);

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


class RPS_CORE_API CrpsSLLocationDistributionFactory
{
public:
	typedef IrpsSLLocationDistribution *(*CreateLocDistrCallback)();

	static void InitializeLocationDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateLocDistrCallback cb);

	static void UnregisterLocationDistribution(const QString &name, const QString &pluginName);

	static IrpsSLLocationDistribution *BuildLocationDistribution(const QString &name);

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


//////////////////////// Along wind Sepctrum//////////////////////////////////////////////////

class RPS_CORE_API CrpsSLXSpectrumFactory
{
public:
	typedef IrpsSLXSpectrum *(*CreateXSpectrumCallback)();

	static void InitializeXSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateXSpectrumCallback cb);

	static void UnregisterXSpectrum(const QString &name, const QString &pluginName);

	static IrpsSLXSpectrum *BuildXSpectrum(const QString &name);

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


//////////////////////// Vertical wind Sepctrum//////////////////////////////////////////////////

class RPS_CORE_API CrpsSLZSpectrumFactory
{
public:
	typedef IrpsSLZSpectrum *(*CreateZSpectrumCallback)();

	static void InitializeZSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterZSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateZSpectrumCallback cb);

	static void UnregisterZSpectrum(const QString &name, const QString &pluginName);

	static IrpsSLZSpectrum *BuildZSpectrum(const QString &name);

	static std::map<const QString, CreateZSpectrumCallback>& GetZSpectrumNamesMap();
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
	typedef std::map<const QString, CreateZSpectrumCallback> CallbackMap;
	static CallbackMap mZSpectrums;
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


//////////////////////// Across wind Sepctrum//////////////////////////////////////////////////

class RPS_CORE_API CrpsSLYSpectrumFactory
{
public:
	typedef IrpsSLYSpectrum *(*CreateYSpectrumCallback)();

	static void InitializeYSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterYSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateYSpectrumCallback cb);

	static void UnregisterYSpectrum(const QString &name, const QString &pluginName);

	static IrpsSLYSpectrum *BuildYSpectrum(const QString &name);

	static std::map<const QString, CreateYSpectrumCallback>& GetYSpectrumNamesMap();
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
	typedef std::map<const QString, CreateYSpectrumCallback> CallbackMap;
	static CallbackMap mYSpectrums;
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

class RPS_CORE_API CrpsSLFrequencyDistributionFactory
{
public:
	typedef IrpsSLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

	static void InitializeFrequencyDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateFrequencyDistributionCallback cb);

	static void UnregisterFrequencyDistribution(const QString &name, const QString &pluginName);

	static IrpsSLFrequencyDistribution *BuildFrequencyDistribution(const QString &name);

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

class RPS_CORE_API CrpsSLRandomnessFactory
{
public:
	typedef IrpsSLRandomness *(*CreateRandomnessCallback)();

	static void InitializeRandomness(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateRandomnessCallback cb);

	static void UnregisterRandomness(const QString &name, const QString &pluginName);

	static IrpsSLRandomness *BuildRandomness(const QString &name);

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

class RPS_CORE_API CrpsSLPSDdecomMethodFactory
{
public:
	typedef IrpsSLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

	static void InitializePSDdecomMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreatePSDdecomMethodCallback cb);

	static void UnregisterPSDdecomMethod(const QString &name, const QString &pluginName);

	static IrpsSLPSDdecompositionMethod *BuildPSDdecomMethod(const QString &name);

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

class RPS_CORE_API CrpsSLCorrelationFactory
{
public:
	typedef IrpsSLCorrelation *(*CreateCorrelationCallback)();

	static void InitializeCorrelation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateCorrelationCallback cb);

	static void UnregisterCorrelation(const QString &name, const QString &pluginName);

	static IrpsSLCorrelation *BuildCorrelation(const QString &name);

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

class RPS_CORE_API CrpsSLModulationFactory
{
public:
	typedef IrpsSLModulation *(*CreateModulationCallback)();

	static void InitializeModulation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate);

	static void RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateModulationCallback cb);

	static void UnregisterModulation(const QString &name, const QString &pluginName);

	static IrpsSLModulation *BuildModulation(const QString &name);

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


#endif
