

#ifndef RPSCOREAPI_H
#define RPSCOREAPI_H

#include "RPSWindLabAPIdefines.h"
#include "IrpsWLCoherence.h"
#include "IrpsWLLocationDistribution.h"
#include "IrpsWLMean.h"
#include "IrpsWLXSpectrum.h"
#include "IrpsWLZSpectrum.h"
#include "IrpsWLYSpectrum.h"
#include "IrpsWLSimuMethod.h"
#include "IrpsWLFrequencyDistribution.h"
#include "IrpsWLRandomness.h"
#include "IrpsWLPSDdecompositionMethod.h"
#include "IrpsWLCorrelation.h"
#include "IrpsWLModulation.h"
#include "IrpsWLTableTool.h"
#include "IrpsWLMatrixTool.h"
#include "IrpsWLUserDefinedRPSObject.h"

#include <map>
#include<vector>


///
/// A factory object in LabRPS
///

class RPS_CORE_API RPSWindLabAPIInfo
{
public:

	static const char * getWindLabAPIVersion();
};

///////////Coherence///////////////

class RPS_CORE_API CrpsCoherenceFactory
{
	public:
		typedef IrpsWLCoherence *(*CreateCoherenceCallback)();

		static void InitializeCoherence(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateCoherenceCallback cb);

		static void UnregisterCoherence(const QString &name, const QString &pluginName);

		static IrpsWLCoherence *BuildCoherence(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

};

	//////////////////////////////////Location distribution//////////////////////////////////////////////


	class RPS_CORE_API CrpsLocationDistributionFactory
	{
	public:
		typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();

		static void InitializeLocationDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateLocDistrCallback cb);

		static void UnregisterLocationDistribution(const QString &name, const QString &pluginName);

		static IrpsWLLocationDistribution *BuildLocationDistribution(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};



	//////////////////////// Mean//////////////////////////////////////////////////

	class RPS_CORE_API CrpsMeanFactory
	{
	public:
		typedef IrpsWLMean *(*CreateMeanCallback)();

		static void InitializeMean(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterMean(const QString &name, const QString &pluginName, const QString &description, CreateMeanCallback cb);

		static void UnregisterMean(const QString &name, const QString &pluginName);

		static IrpsWLMean *BuildMean(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};


	//////////////////////// Along wind Sepctrum//////////////////////////////////////////////////

	class RPS_CORE_API CrpsXSpectrumFactory
	{
	public:
		typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();

		static void InitializeXSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateXSpectrumCallback cb);

		static void UnregisterXSpectrum(const QString &name, const QString &pluginName);

		static IrpsWLXSpectrum *BuildXSpectrum(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};


	//////////////////////// Vertical wind Sepctrum//////////////////////////////////////////////////

	class RPS_CORE_API CrpsZSpectrumFactory
	{
	public:
		typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();

		static void InitializeZSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterZSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateZSpectrumCallback cb);

		static void UnregisterZSpectrum(const QString &name, const QString &pluginName);

		static IrpsWLZSpectrum *BuildZSpectrum(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};


	//////////////////////// Across wind Sepctrum//////////////////////////////////////////////////

	class RPS_CORE_API CrpsYSpectrumFactory
	{
	public:
		typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();

		static void InitializeYSpectrum(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterYSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateYSpectrumCallback cb);

		static void UnregisterYSpectrum(const QString &name, const QString &pluginName);

		static IrpsWLYSpectrum *BuildYSpectrum(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};




	////////////////////////Simulation Method//////////////////////////////////////////////////

	class RPS_CORE_API CrpsSimuMethodFactory
	{
	public:
		typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();

		static void InitializeSimuMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterSimuMethod(const QString &name, const QString &pluginName, const QString &description, CreateSimuMethodCallback cb);

		static void UnregisterSimuMethod(const QString &name, const QString &pluginName);

		static IrpsWLSimuMethod *BuildSimuMethod(const QString &name);

		static std::map<const QString, CreateSimuMethodCallback>& GetSimuMethodNamesMap();
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
		static std::map<const QString, QString> & GetVersionMap();

	private:
		typedef std::map<const QString, CreateSimuMethodCallback> CallbackMap;
		static CallbackMap mSimuMethods;
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
		static std::map<const QString, QString> mVersionMap;

	};


	////////////////////////Frequency distribution//////////////////////////////////////////////////

	class RPS_CORE_API CrpsFrequencyDistributionFactory
	{
	public:
		typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

		static void InitializeFrequencyDistribution(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateFrequencyDistributionCallback cb);

		static void UnregisterFrequencyDistribution(const QString &name, const QString &pluginName);

		static IrpsWLFrequencyDistribution *BuildFrequencyDistribution(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};


	////////////////////////Randomness//////////////////////////////////////////////////

	class RPS_CORE_API CrpsRandomnessFactory
	{
	public:
		typedef IrpsWLRandomness *(*CreateRandomnessCallback)();

		static void InitializeRandomness(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateRandomnessCallback cb);

		static void UnregisterRandomness(const QString &name, const QString &pluginName);

		static IrpsWLRandomness *BuildRandomness(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};


	////////////////////////psd decomposition//////////////////////////////////////////////////

	class RPS_CORE_API CrpsPSDdecomMethodFactory
	{
	public:
		typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

		static void InitializePSDdecomMethod(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreatePSDdecomMethodCallback cb);

		static void UnregisterPSDdecomMethod(const QString &name, const QString &pluginName);

		static IrpsWLPSDdecompositionMethod *BuildPSDdecomMethod(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};

	////////////////////////Correlation//////////////////////////////////////////////////

	class RPS_CORE_API CrpsCorrelationFactory
	{
	public:
		typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();

		static void InitializeCorrelation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateCorrelationCallback cb);

		static void UnregisterCorrelation(const QString &name, const QString &pluginName);

		static IrpsWLCorrelation *BuildCorrelation(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};

	////////////////////////Modulation//////////////////////////////////////////////////

	class RPS_CORE_API CrpsModulationFactory
	{
	public:
		typedef IrpsWLModulation *(*CreateModulationCallback)();

		static void InitializeModulation(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

		static void RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateModulationCallback cb);

		static void UnregisterModulation(const QString &name, const QString &pluginName);

		static IrpsWLModulation *BuildModulation(const QString &name);

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
		static std::map<const QString, QString> & GetVersionMap();

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
		static std::map<const QString, QString> mVersionMap;

	};

	///////////Table tool///////////////

class RPS_CORE_API CrpsTableToolFactory
{
	public:
		typedef IrpsWLTableTool *(*CreateTableToolCallback)();

		static void InitializeTableTool(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

        static void RegisterTableTool(const QString &name, const QString &pluginName, const QString &description, CreateTableToolCallback cb);

		static void UnregisterTableTool(const QString &name, const QString &pluginName);

		static IrpsWLTableTool *BuildTableTool(const QString &name);

		static std::vector<QString> GetNameVector();

		static std::map<const QString, CreateTableToolCallback>& GetTableToolNamesMap();

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
		static std::map<const QString, QString> & GetVersionMap();

	private:
		typedef std::map<const QString, CreateTableToolCallback> CallbackMap;
		static CallbackMap mTableTools;
		static std::vector<QString> mTableToolNames;
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
		static std::map<const QString, QString> mVersionMap;

};

///////////Matrix tool///////////////

class RPS_CORE_API CrpsMatrixToolFactory
{
	public:
		typedef IrpsWLMatrixTool *(*CreateMatrixToolCallback)();

		static void InitializeMatrixTool(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

        static void RegisterMatrixTool(const QString &name, const QString &pluginName, const QString &description, CreateMatrixToolCallback cb);

		static void UnregisterMatrixTool(const QString &name, const QString &pluginName);

		static IrpsWLMatrixTool *BuildMatrixTool(const QString &name);

		static std::vector<QString> GetNameVector();

		static std::map<const QString, CreateMatrixToolCallback>& GetMatrixToolNamesMap();

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
		static std::map<const QString, QString> & GetVersionMap();

	private:
		typedef std::map<const QString, CreateMatrixToolCallback> CallbackMap;
		static CallbackMap mMatrixTools;
		static std::vector<QString> mMatrixToolNames;
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
		static std::map<const QString, QString> mVersionMap;

};

///////////user defined rps object///////////////

class RPS_CORE_API CrpsUserDefinedRPSObjectFactory
{
	public:
		typedef IrpsWLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();

		static void InitializeUserDefinedRPSObject(const QString &name, const QString &description, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

        static void RegisterUserDefinedRPSObject(const QString &name, const QString &pluginName, const QString &description, CreateUserDefinedRPSObjectCallback cb);

		static void UnregisterUserDefinedRPSObject(const QString &name, const QString &pluginName);

		static IrpsWLUserDefinedRPSObject *BuildUserDefinedRPSObject(const QString &name);

		static std::vector<QString> GetNameVector();

		static std::map<const QString, CreateUserDefinedRPSObjectCallback>& GetUserDefinedRPSObjectNamesMap();

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
		static std::map<const QString, QString> & GetVersionMap();

	private:
		typedef std::map<const QString, CreateUserDefinedRPSObjectCallback> CallbackMap;
		static CallbackMap mUserDefinedRPSObjects;
		static std::vector<QString> mUserDefinedRPSObjectNames;
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
		static std::map<const QString, QString> mVersionMap;

};

#endif
