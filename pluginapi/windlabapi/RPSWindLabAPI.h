
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
#include "IrpsWLCumulativeProbabilityDistribution.h"
#include "IrpsWLGustFactor.h"
#include "IrpsWLKurtosis.h"
#include "IrpsWLPeakFactor.h"
#include "IrpsWLProbabilityDensityFunction.h"
#include "IrpsWLRoughness.h"
#include "IrpsWLShearVelocityOfFlow.h"
#include "IrpsWLSkewness.h"
#include "IrpsWLStandardDeviation.h"
#include "IrpsWLTurbulenceIntensity.h"
#include "IrpsWLTurbulenceScale.h"
#include "IrpsWLVariance.h"
#include "IrpsWLWavePassageEffect.h"

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

// ///////////Coherence///////////////

// class RPS_CORE_API CrpsCoherenceFactory
// {
// 	public:
// 		typedef IrpsWLCoherence *(*CreateCoherenceCallback)();

// 		static void InitializeCoherence(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterCoherence(const QString &name, const QString &pluginName, const QString &description, CreateCoherenceCallback cb);

// 		static void UnregisterCoherence(const QString &name, const QString &pluginName);

// 		static IrpsWLCoherence *BuildCoherence(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateCoherenceCallback>& GetCoherenceNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateCoherenceCallback> CallbackMap;
// 		static CallbackMap mCoherences;
// 		static std::vector<QString> mCoherenceNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// 	//////////////////////////////////Location distribution//////////////////////////////////////////////


// 	class RPS_CORE_API CrpsLocationDistributionFactory
// 	{
// 	public:
// 		typedef IrpsWLLocationDistribution *(*CreateLocDistrCallback)();

// 		static void InitializeLocationDistribution(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterLocationDistribution(const QString &name, const QString &pluginName, const QString &description, CreateLocDistrCallback cb);

// 		static void UnregisterLocationDistribution(const QString &name, const QString &pluginName);

// 		static IrpsWLLocationDistribution *BuildLocationDistribution(const QString &name);

// 		static std::vector<QString> GetLocDistrNamesVector();

// 		static std::map<const QString, CreateLocDistrCallback>& GetLocDistrNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateLocDistrCallback> CallbackMap;
// 		static CallbackMap mLocationDistributions;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};



// 	//////////////////////// Mean//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsMeanFactory
// 	{
// 	public:
// 		typedef IrpsWLMean *(*CreateMeanCallback)();

// 		static void InitializeMean(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterMean(const QString &name, const QString &pluginName, const QString &description, CreateMeanCallback cb);

// 		static void UnregisterMean(const QString &name, const QString &pluginName);

// 		static IrpsWLMean *BuildMean(const QString &name);

// 		static std::map<const QString, CreateMeanCallback>& GetMeanNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateMeanCallback> CallbackMap;
// 		static CallbackMap mMeans;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};


// 	//////////////////////// Along wind Sepctrum//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsXSpectrumFactory
// 	{
// 	public:
// 		typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();

// 		static void InitializeXSpectrum(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterXSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateXSpectrumCallback cb);

// 		static void UnregisterXSpectrum(const QString &name, const QString &pluginName);

// 		static IrpsWLXSpectrum *BuildXSpectrum(const QString &name);

// 		static std::map<const QString, CreateXSpectrumCallback>& GetXSpectrumNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateXSpectrumCallback> CallbackMap;
// 		static CallbackMap mXSpectrums;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};


// 	//////////////////////// Vertical wind Sepctrum//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsZSpectrumFactory
// 	{
// 	public:
// 		typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();

// 		static void InitializeZSpectrum(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterZSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateZSpectrumCallback cb);

// 		static void UnregisterZSpectrum(const QString &name, const QString &pluginName);

// 		static IrpsWLZSpectrum *BuildZSpectrum(const QString &name);

// 		static std::map<const QString, CreateZSpectrumCallback>& GetZSpectrumNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateZSpectrumCallback> CallbackMap;
// 		static CallbackMap mZSpectrums;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};


// 	//////////////////////// Across wind Sepctrum//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsYSpectrumFactory
// 	{
// 	public:
// 		typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();

// 		static void InitializeYSpectrum(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterYSpectrum(const QString &name, const QString &pluginName, const QString &description, CreateYSpectrumCallback cb);

// 		static void UnregisterYSpectrum(const QString &name, const QString &pluginName);

// 		static IrpsWLYSpectrum *BuildYSpectrum(const QString &name);

// 		static std::map<const QString, CreateYSpectrumCallback>& GetYSpectrumNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateYSpectrumCallback> CallbackMap;
// 		static CallbackMap mYSpectrums;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};




// 	////////////////////////Simulation Method//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsSimuMethodFactory
// 	{
// 	public:
// 		typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();

// 		static void InitializeSimuMethod(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterSimuMethod(const QString &name, const QString &pluginName, const QString &description, CreateSimuMethodCallback cb);

// 		static void UnregisterSimuMethod(const QString &name, const QString &pluginName);

// 		static IrpsWLSimuMethod *BuildSimuMethod(const QString &name);

// 		static std::map<const QString, CreateSimuMethodCallback>& GetSimuMethodNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateSimuMethodCallback> CallbackMap;
// 		static CallbackMap mSimuMethods;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};


// 	////////////////////////Frequency distribution//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsFrequencyDistributionFactory
// 	{
// 	public:
// 		typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

// 		static void InitializeFrequencyDistribution(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterFrequencyDistribution(const QString &name, const QString &pluginName, const QString &description, CreateFrequencyDistributionCallback cb);

// 		static void UnregisterFrequencyDistribution(const QString &name, const QString &pluginName);

// 		static IrpsWLFrequencyDistribution *BuildFrequencyDistribution(const QString &name);

// 		static std::map<const QString, CreateFrequencyDistributionCallback>& GetFrequencyDistributionNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateFrequencyDistributionCallback> CallbackMap;
// 		static CallbackMap mFrequencyDistributions;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};


// 	////////////////////////Randomness//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsRandomnessFactory
// 	{
// 	public:
// 		typedef IrpsWLRandomness *(*CreateRandomnessCallback)();

// 		static void InitializeRandomness(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterRandomness(const QString &name, const QString &pluginName, const QString &description, CreateRandomnessCallback cb);

// 		static void UnregisterRandomness(const QString &name, const QString &pluginName);

// 		static IrpsWLRandomness *BuildRandomness(const QString &name);

// 		static std::map<const QString, CreateRandomnessCallback>& GetRandomnessNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateRandomnessCallback> CallbackMap;
// 		static CallbackMap mRandomness;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};


// 	////////////////////////psd decomposition//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsPSDdecomMethodFactory
// 	{
// 	public:
// 		typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

// 		static void InitializePSDdecomMethod(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterPSDdecomMethod(const QString &name, const QString &pluginName, const QString &description, CreatePSDdecomMethodCallback cb);

// 		static void UnregisterPSDdecomMethod(const QString &name, const QString &pluginName);

// 		static IrpsWLPSDdecompositionMethod *BuildPSDdecomMethod(const QString &name);

// 		static std::map<const QString, CreatePSDdecomMethodCallback>& GetPSDdecomMethodNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 		static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreatePSDdecomMethodCallback> CallbackMap;
// 		static CallbackMap mPSDdecomMethods;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};

// 	////////////////////////Correlation//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsCorrelationFactory
// 	{
// 	public:
// 		typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();

// 		static void InitializeCorrelation(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterCorrelation(const QString &name, const QString &pluginName, const QString &description, CreateCorrelationCallback cb);

// 		static void UnregisterCorrelation(const QString &name, const QString &pluginName);

// 		static IrpsWLCorrelation *BuildCorrelation(const QString &name);

// 		static std::map<const QString, CreateCorrelationCallback>& GetCorrelationNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
//     	static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateCorrelationCallback> CallbackMap;
// 		static CallbackMap mCorrelations;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};

// 	////////////////////////Modulation//////////////////////////////////////////////////

// 	class RPS_CORE_API CrpsModulationFactory
// 	{
// 	public:
// 		typedef IrpsWLModulation *(*CreateModulationCallback)();

// 		static void InitializeModulation(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

// 		static void RegisterModulation(const QString &name, const QString &pluginName, const QString &description, CreateModulationCallback cb);

// 		static void UnregisterModulation(const QString &name, const QString &pluginName);

// 		static IrpsWLModulation *BuildModulation(const QString &name);

// 		static std::map<const QString, CreateModulationCallback>& GetModulationNamesMap();
// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateModulationCallback> CallbackMap;
// 		static CallbackMap mModulations;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// 	};

// 	///////////Table tool///////////////

// class RPS_CORE_API CrpsTableToolFactory
// {
// 	public:
// 		typedef IrpsWLTableTool *(*CreateTableToolCallback)();

// 		static void InitializeTableTool(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterTableTool(const QString &name, const QString &pluginName, const QString &description, CreateTableToolCallback cb);

// 		static void UnregisterTableTool(const QString &name, const QString &pluginName);

// 		static IrpsWLTableTool *BuildTableTool(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateTableToolCallback>& GetTableToolNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateTableToolCallback> CallbackMap;
// 		static CallbackMap mTableTools;
// 		static std::vector<QString> mTableToolNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// ///////////Matrix tool///////////////

// class RPS_CORE_API CrpsMatrixToolFactory
// {
// 	public:
// 		typedef IrpsWLMatrixTool *(*CreateMatrixToolCallback)();

// 		static void InitializeMatrixTool(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterMatrixTool(const QString &name, const QString &pluginName, const QString &description, CreateMatrixToolCallback cb);

// 		static void UnregisterMatrixTool(const QString &name, const QString &pluginName);

// 		static IrpsWLMatrixTool *BuildMatrixTool(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateMatrixToolCallback>& GetMatrixToolNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateMatrixToolCallback> CallbackMap;
// 		static CallbackMap mMatrixTools;
// 		static std::vector<QString> mMatrixToolNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// ///////////user defined rps object///////////////

// class RPS_CORE_API CrpsUserDefinedRPSObjectFactory
// {
// 	public:
// 		typedef IrpsWLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();

// 		static void InitializeUserDefinedRPSObject(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterUserDefinedRPSObject(const QString &name, const QString &pluginName, const QString &description, CreateUserDefinedRPSObjectCallback cb);

// 		static void UnregisterUserDefinedRPSObject(const QString &name, const QString &pluginName);

// 		static IrpsWLUserDefinedRPSObject *BuildUserDefinedRPSObject(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateUserDefinedRPSObjectCallback>& GetUserDefinedRPSObjectNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateUserDefinedRPSObjectCallback> CallbackMap;
// 		static CallbackMap mUserDefinedRPSObjects;
// 		static std::vector<QString> mUserDefinedRPSObjectNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// ///////////cumulative probability distribution///////////////
// class RPS_CORE_API CrpsCumulativeProbabilityDistributionFactory
// {
// 	public:
// 		typedef IrpsWLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();

// 		static void InitializeCumulativeProbabilityDistribution(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterCumulativeProbabilityDistribution(const QString &name, const QString &pluginName, const QString &description, CreateCumulativeProbabilityDistributionCallback cb);

// 		static void UnregisterCumulativeProbabilityDistribution(const QString &name, const QString &pluginName);

// 		static IrpsWLCumulativeProbabilityDistribution *BuildCumulativeProbabilityDistribution(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateCumulativeProbabilityDistributionCallback>& GetCumulativeProbabilityDistributionNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateCumulativeProbabilityDistributionCallback> CallbackMap;
// 		static CallbackMap mCumulativeProbabilityDistributions;
// 		static std::vector<QString> mCumulativeProbabilityDistributionNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Gust factor////////////////////////////////////////////

// class RPS_CORE_API CrpsGustFactorFactory
// {
// 	public:
// 		typedef IrpsWLGustFactor *(*CreateGustFactorCallback)();

// 		static void InitializeGustFactor(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterGustFactor(const QString &name, const QString &pluginName, const QString &description, CreateGustFactorCallback cb);

// 		static void UnregisterGustFactor(const QString &name, const QString &pluginName);

// 		static IrpsWLGustFactor *BuildGustFactor(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateGustFactorCallback>& GetGustFactorNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateGustFactorCallback> CallbackMap;
// 		static CallbackMap mGustFactors;
// 		static std::vector<QString> mGustFactorNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Kurtosis////////////////////////////////////////////

// class RPS_CORE_API CrpsKurtosisFactory
// {
// 	public:
// 		typedef IrpsWLKurtosis *(*CreateKurtosisCallback)();

// 		static void InitializeKurtosis(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterKurtosis(const QString &name, const QString &pluginName, const QString &description, CreateKurtosisCallback cb);

// 		static void UnregisterKurtosis(const QString &name, const QString &pluginName);

// 		static IrpsWLKurtosis *BuildKurtosis(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateKurtosisCallback>& GetKurtosisNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateKurtosisCallback> CallbackMap;
// 		static CallbackMap mKurtosiss;
// 		static std::vector<QString> mKurtosisNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Peak Factor////////////////////////////////////////////

// class RPS_CORE_API CrpsPeakFactorFactory
// {
// 	public:
// 		typedef IrpsWLPeakFactor *(*CreatePeakFactorCallback)();

// 		static void InitializePeakFactor(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterPeakFactor(const QString &name, const QString &pluginName, const QString &description, CreatePeakFactorCallback cb);

// 		static void UnregisterPeakFactor(const QString &name, const QString &pluginName);

// 		static IrpsWLPeakFactor *BuildPeakFactor(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreatePeakFactorCallback>& GetPeakFactorNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreatePeakFactorCallback> CallbackMap;
// 		static CallbackMap mPeakFactors;
// 		static std::vector<QString> mPeakFactorNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Probability density function////////////////////////////////////////////

// class RPS_CORE_API CrpsProbabilityDensityFunctionFactory
// {
// 	public:
// 		typedef IrpsWLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();

// 		static void InitializeProbabilityDensityFunction(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterProbabilityDensityFunction(const QString &name, const QString &pluginName, const QString &description, CreateProbabilityDensityFunctionCallback cb);

// 		static void UnregisterProbabilityDensityFunction(const QString &name, const QString &pluginName);

// 		static IrpsWLProbabilityDensityFunction *BuildProbabilityDensityFunction(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateProbabilityDensityFunctionCallback>& GetProbabilityDensityFunctionNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateProbabilityDensityFunctionCallback> CallbackMap;
// 		static CallbackMap mProbabilityDensityFunctions;
// 		static std::vector<QString> mProbabilityDensityFunctionNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Roughness////////////////////////////////////////////

// class RPS_CORE_API CrpsRoughnessFactory
// {
// 	public:
// 		typedef IrpsWLRoughness *(*CreateRoughnessCallback)();

// 		static void InitializeRoughness(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterRoughness(const QString &name, const QString &pluginName, const QString &description, CreateRoughnessCallback cb);

// 		static void UnregisterRoughness(const QString &name, const QString &pluginName);

// 		static IrpsWLRoughness *BuildRoughness(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateRoughnessCallback>& GetRoughnessNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);

// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateRoughnessCallback> CallbackMap;
// 		static CallbackMap mRoughnesss;
// 		static std::vector<QString> mRoughnessNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;
// };

// /////////////////////Shear velocity of flow////////////////////////////////////////////

// class RPS_CORE_API CrpsShearVelocityOfFlowFactory
// {
// 	public:
// 		typedef IrpsWLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();

// 		static void InitializeShearVelocityOfFlow(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterShearVelocityOfFlow(const QString &name, const QString &pluginName, const QString &description, CreateShearVelocityOfFlowCallback cb);

// 		static void UnregisterShearVelocityOfFlow(const QString &name, const QString &pluginName);

// 		static IrpsWLShearVelocityOfFlow *BuildShearVelocityOfFlow(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateShearVelocityOfFlowCallback>& GetShearVelocityOfFlowNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateShearVelocityOfFlowCallback> CallbackMap;
// 		static CallbackMap mShearVelocityOfFlows;
// 		static std::vector<QString> mShearVelocityOfFlowNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Skewness////////////////////////////////////////////

// class RPS_CORE_API CrpsSkewnessFactory
// {
// 	public:
// 		typedef IrpsWLSkewness *(*CreateSkewnessCallback)();

// 		static void InitializeSkewness(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterSkewness(const QString &name, const QString &pluginName, const QString &description, CreateSkewnessCallback cb);

// 		static void UnregisterSkewness(const QString &name, const QString &pluginName);

// 		static IrpsWLSkewness *BuildSkewness(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateSkewnessCallback>& GetSkewnessNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateSkewnessCallback> CallbackMap;
// 		static CallbackMap mSkewnesss;
// 		static std::vector<QString> mSkewnessNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Standard deviation////////////////////////////////////////////

// class RPS_CORE_API CrpsStandardDeviationFactory
// {
// 	public:
// 		typedef IrpsWLStandardDeviation *(*CreateStandardDeviationCallback)();

// 		static void InitializeStandardDeviation(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterStandardDeviation(const QString &name, const QString &pluginName, const QString &description, CreateStandardDeviationCallback cb);

// 		static void UnregisterStandardDeviation(const QString &name, const QString &pluginName);

// 		static IrpsWLStandardDeviation *BuildStandardDeviation(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateStandardDeviationCallback>& GetStandardDeviationNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);

// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateStandardDeviationCallback> CallbackMap;
// 		static CallbackMap mStandardDeviations;
// 		static std::vector<QString> mStandardDeviationNames;
// 		static QString mOwnerPlugin;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Turbulence Intensity////////////////////////////////////////////

// class RPS_CORE_API CrpsTurbulenceIntensityFactory
// {
// 	public:
// 		typedef IrpsWLTurbulenceIntensity *(*CreateTurbulenceIntensityCallback)();

// 		static void InitializeTurbulenceIntensity(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterTurbulenceIntensity(const QString &name, const QString &pluginName, const QString &description, CreateTurbulenceIntensityCallback cb);

// 		static void UnregisterTurbulenceIntensity(const QString &name, const QString &pluginName);

// 		static IrpsWLTurbulenceIntensity *BuildTurbulenceIntensity(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateTurbulenceIntensityCallback>& GetTurbulenceIntensityNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);

// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateTurbulenceIntensityCallback> CallbackMap;
// 		static CallbackMap mTurbulenceIntensitys;
// 		static std::vector<QString> mTurbulenceIntensityNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// /////////////////////Turbulence scale////////////////////////////////////////////

// class RPS_CORE_API CrpsTurbulenceScaleFactory
// {
// 	public:
// 		typedef IrpsWLTurbulenceScale *(*CreateTurbulenceScaleCallback)();

// 		static void InitializeTurbulenceScale(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterTurbulenceScale(const QString &name, const QString &pluginName, const QString &description, CreateTurbulenceScaleCallback cb);

// 		static void UnregisterTurbulenceScale(const QString &name, const QString &pluginName);

// 		static IrpsWLTurbulenceScale *BuildTurbulenceScale(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateTurbulenceScaleCallback>& GetTurbulenceScaleNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateTurbulenceScaleCallback> CallbackMap;
// 		static CallbackMap mTurbulenceScales;
// 		static std::vector<QString> mTurbulenceScaleNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

// WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsWavePassageEffectFactory, IrpsWLWavePassageEffect)

// /////////////////////Variance////////////////////////////////////////////

// class RPS_CORE_API CrpsVarianceFactory
// {
// 	public:
// 		typedef IrpsWLVariance *(*CreateVarianceCallback)();

// 		static void InitializeVariance(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//         static void RegisterVariance(const QString &name, const QString &pluginName, const QString &description, CreateVarianceCallback cb);

// 		static void UnregisterVariance(const QString &name, const QString &pluginName);

// 		static IrpsWLVariance *BuildVariance(const QString &name);

// 		static std::vector<QString> GetNameVector();

// 		static std::map<const QString, CreateVarianceCallback>& GetVarianceNamesMap();

// 		static QString GetOwnerPlugin();
// 		static void SetOwnerPlugin(QString ownerPlugin);
// 		/*static QString GetDescription();
// 		static void SetDescription(QString description);*/
// 		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
// 		static std::map<const QString, QString> & GetOjectDescriptionMap();
// 		static std::map<const QString, QString> & GetOjectAndPluginMap();
// 		static std::map<const QString, QString> & GetTitleMap();
// 		static std::map<const QString, QString> & GetLinkMap();
// 		static std::map<const QString, QString> & GetAuthorMap();
// 		static std::map<const QString, QString> & GetDateMap();
// 	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
// 		static std::map<const QString, QString> & GetVersionMap();

// 	private:
// 		typedef std::map<const QString, CreateVarianceCallback> CallbackMap;
// 		static CallbackMap mVariances;
// 		static std::vector<QString> mVarianceNames;
// 		static QString mOwnerPlugin;
// 		//static QString mDescription;
// 		static std::map<const QString, QString> mTobeInstalledObjectsMap;
// 		static std::map<const QString, QString> mOjectDescriptionMap;
// 		static std::map<const QString, QString> mOjectAndPluginMap;
// 		static std::map<const QString, QString> mTitleMap;
// 		static std::map<const QString, QString> mLinkMap;
// 		static std::map<const QString, QString> mAuthorMap;
// 		static std::map<const QString, QString> mDateMap;
// 		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
// 		static std::map<const QString, QString> mVersionMap;

// };

///////////////////////Wave passage effect////////////////////////////////////////////

//class RPS_CORE_API CrpsWavePassageEffectFactory
//{
//	public:
//        typedef IrpsWLWavePassageEffect *(*CreateWavePassageEffectCallback)();

//        static void InitializeWavePassageEffect(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);

//        static void RegisterWavePassageEffect(const QString &name, const QString &pluginName, const QString &description, CreateWavePassageEffectCallback cb);

//        static void UnregisterWavePassageEffect(const QString &name, const QString &pluginName);

//        static IrpsWLWavePassageEffect *BuildWavePassageEffect(const QString &name);

//		static std::vector<QString> GetNameVector();

//        static std::map<const QString, CreateWavePassageEffectCallback>& GetWavePassageEffectNamesMap();

//		static QString GetOwnerPlugin();
//		static void SetOwnerPlugin(QString ownerPlugin);
//		/*static QString GetDescription();
//		static void SetDescription(QString description);*/
//		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();
//		static std::map<const QString, QString> & GetOjectDescriptionMap();
//		static std::map<const QString, QString> & GetOjectAndPluginMap();
//		static std::map<const QString, QString> & GetTitleMap();
//		static std::map<const QString, QString> & GetLinkMap();
//		static std::map<const QString, QString> & GetAuthorMap();
//		static std::map<const QString, QString> & GetDateMap();
//	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();
//		static std::map<const QString, QString> & GetVersionMap();

//	private:
//        typedef std::map<const QString, CreateWavePassageEffectCallback> CallbackMap;
//        static CallbackMap mWavePassageEffects;
//        static std::vector<QString> mWavePassageEffectNames;
//		static QString mOwnerPlugin;
//		//static QString mDescription;
//		static std::map<const QString, QString> mTobeInstalledObjectsMap;
//		static std::map<const QString, QString> mOjectDescriptionMap;
//		static std::map<const QString, QString> mOjectAndPluginMap;
//		static std::map<const QString, QString> mTitleMap;
//		static std::map<const QString, QString> mLinkMap;
//		static std::map<const QString, QString> mAuthorMap;
//		static std::map<const QString, QString> mDateMap;
//		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;
//		static std::map<const QString, QString> mVersionMap;

//};


#define WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(_ObjectClass_, _ObjectInterface_, _CreateCallback_) \
class RPS_CORE_API _ObjectClass_\
{\
	public:\
        typedef _ObjectInterface_ *(*_CreateCallback_)();\
        static void InitializeObject(const QString &name, const QString &pluginName, const QString &publicationTitle, const QString &publicationLink, const QString &publicationAuthor, const QString &publicationDate, const QString &version);\
        static void RegisterObject(const QString &name, const QString &pluginName, const QString &description, _CreateCallback_ cb);\
        static void UnregisterObject(const QString &name, const QString &pluginName);\
        static _ObjectInterface_ *BuildObject(const QString &name);\
		static std::vector<QString> GetNameVector();\
        static std::map<const QString, _CreateCallback_>& GetObjectNamesMap();\
		static QString GetOwnerPlugin();\
		static void SetOwnerPlugin(QString ownerPlugin);\
		static std::map<const QString, QString> & GetTobeInstalledObjectsMap();\
		static std::map<const QString, QString> & GetOjectDescriptionMap();\
		static std::map<const QString, QString> & GetOjectAndPluginMap();\
		static std::map<const QString, QString> & GetTitleMap();\
		static std::map<const QString, QString> & GetLinkMap();\
		static std::map<const QString, QString> & GetAuthorMap();\
		static std::map<const QString, QString> & GetDateMap();\
	    static std::map<const QString, QString> & GetOjectsSkipDuringUnintallationMap();\
		static std::map<const QString, QString> & GetVersionMap();\
	private:\
        typedef std::map<const QString, _CreateCallback_> CallbackMap;\
        static CallbackMap mObjects;\
        static std::vector<QString> mObjectNames;\
        static QString mOwnerPlugin;\
		static std::map<const QString, QString> mTobeInstalledObjectsMap;\
		static std::map<const QString, QString> mOjectDescriptionMap;\
		static std::map<const QString, QString> mOjectAndPluginMap;\
		static std::map<const QString, QString> mTitleMap;\
		static std::map<const QString, QString> mLinkMap;\
		static std::map<const QString, QString> mAuthorMap;\
		static std::map<const QString, QString> mDateMap;\
		static std::map<const QString, QString> mOjectsSkipDuringUnintallationMap;\
		static std::map<const QString, QString> mVersionMap;\
};


WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCoherenceFactory, IrpsWLCoherence, IrpsWLCoherenceCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsLocationDistributionFactory, IrpsWLLocationDistribution, IrpsWLLocationDistributionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMeanFactory, IrpsWLMean, IrpsWLMeanCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsXSpectrumFactory, IrpsWLXSpectrum, IrpsWLXSpectrumCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsZSpectrumFactory, IrpsWLZSpectrum, IrpsWLZSpectrumCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsYSpectrumFactory, IrpsWLYSpectrum, IrpsWLYSpectrumCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSimuMethodFactory, IrpsWLSimuMethod, IrpsWLSimuMethodCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsFrequencyDistributionFactory, IrpsWLFrequencyDistribution, IrpsWLFrequencyDistributionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRandomnessFactory, IrpsWLRandomness, IrpsWLRandomnessCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPSDdecomMethodFactory, IrpsWLPSDdecompositionMethod, IrpsWLPSDdecompositionMethodCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCorrelationFactory, IrpsWLCorrelation, IrpsWLCorrelationCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsModulationFactory, IrpsWLModulation, IrpsWLModulationCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTableToolFactory, IrpsWLTableTool, IrpsWLTableToolCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMatrixToolFactory, IrpsWLMatrixTool, IrpsWLMatrixToolCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsUserDefinedRPSObjectFactory, IrpsWLUserDefinedRPSObject, IrpsWLUserDefinedRPSObjectCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCumulativeProbabilityDistributionFactory, IrpsWLCumulativeProbabilityDistribution, IrpsWLCumulativeProbabilityDistributionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsGustFactorFactory, IrpsWLGustFactor, IrpsWLGustFactorCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsKurtosisFactory, IrpsWLKurtosis, IrpsWLKurtosisCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPeakFactorFactory, IrpsWLPeakFactor, IrpsWLPeakFactorCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsProbabilityDensityFunctionFactory, IrpsWLProbabilityDensityFunction, IrpsWLProbabilityDensityFunctionCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRoughnessFactory, IrpsWLRoughness, IrpsWLRoughnessCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsShearVelocityOfFlowFactory, IrpsWLShearVelocityOfFlow, IrpsWLShearVelocityOfFlowCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSkewnessFactory, IrpsWLSkewness, IrpsWLSkewnessCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsStandardDeviationFactory, IrpsWLStandardDeviation, IrpsWLStandardDeviationCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceIntensityFactory, IrpsWLTurbulenceIntensity, IrpsWLTurbulenceIntensityCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceScaleFactory, IrpsWLTurbulenceScale, IrpsWLTurbulenceScaleCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsVarianceFactory, IrpsWLVariance, IrpsWLVarianceCallback)

WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsWavePassageEffectFactory, IrpsWLWavePassageEffect, IrpsWLWavePassageEffectCallback)


#endif
