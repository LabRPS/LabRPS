
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

#ifndef RPSCOREAPI_H
#define RPSCOREAPI_H

#include "RPSSeismicLabAPIdefines.h"
#include "IrpsSLCoherence.h"
#include "IrpsSLLocationDistribution.h"
#include "IrpsSLMeanAcceleration.h"
#include "IrpsSLSpectrum.h"
#include "IrpsSLSimulationMethod.h"
#include "IrpsSLFrequencyDistribution.h"
#include "IrpsSLRandomness.h"
#include "IrpsSLPSDdecompositionMethod.h"
#include "IrpsSLCorrelation.h"
#include "IrpsSLModulation.h"
#include "IrpsSLTableTool.h"
#include "IrpsSLMatrixTool.h"
#include "IrpsSLUserDefinedRPSObject.h"
#include "IrpsSLCumulativeProbabilityDistribution.h"
#include "IrpsSLKurtosis.h"
#include "IrpsSLPeakFactor.h"
#include "IrpsSLProbabilityDensityFunction.h"
#include "IrpsSLShearVelocityOfFlow.h"
#include "IrpsSLSkewness.h"
#include "IrpsSLStandardDeviation.h"
#include "IrpsSLVariance.h"
#include "IrpsSLWavePassageEffect.h"

#include <map>
#include<vector>

#include <QString>


#include <App/RPSFeature.h>

namespace SeismicLabAPI {

class RPS_CORE_API RPSSeismicLabAPIInfo
{
public:

	static const char * getSeismicLabAPIVersion();
};

 class RPS_CORE_API CrpsCoherenceFactory
 {
 	public:
        CrpsCoherenceFactory();
        ~CrpsCoherenceFactory();

 		typedef IrpsSLCoherence *(*CreateCoherenceCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCoherenceCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLCoherence * BuildObject(const std::string& name);
        
        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateCoherenceCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);

 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateCoherenceCallback> CallbackMap;
 		static CallbackMap mCoherences;
 		static std::vector<std::string> mCoherenceNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };


 	class RPS_CORE_API CrpsLocationDistributionFactory
 	{
 	public:

        CrpsLocationDistributionFactory();
        ~CrpsLocationDistributionFactory();
 		typedef SeismicLabAPI::IrpsSLLocationDistribution *(*CreateLocDistrCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateLocDistrCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static  SeismicLabAPI::IrpsSLLocationDistribution * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateLocDistrCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*> & GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();


 	private:
 		typedef std::map<const std::string, CreateLocDistrCallback> CallbackMap;
 		static CallbackMap mLocationDistributions;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;


 	};


 	class RPS_CORE_API CrpsMeanFactory
 	{
 	public:

        CrpsMeanFactory();
        ~CrpsMeanFactory();

 		typedef IrpsSLMeanAcceleration *(*CreateMeanCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMeanCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLMeanAcceleration * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);


 		static std::map<const std::string, CreateMeanCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();



 	private:
 		typedef std::map<const std::string, CreateMeanCallback> CallbackMap;
 		static CallbackMap mMeans;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;


 	};


 	//////////////////////// Along wind Sepctrum//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsSpectrumFactory
 	{
 	public:
        CrpsSpectrumFactory();
        ~CrpsSpectrumFactory();
 		typedef IrpsSLSpectrum *(*CreateXSpectrumCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateXSpectrumCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLSpectrum * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateXSpectrumCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();


 	private:
 		typedef std::map<const std::string, CreateXSpectrumCallback> CallbackMap;
 		static CallbackMap mXSpectrums;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 	};


 	////////////////////////Simulation Method//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsSimuMethodFactory
 	{
 	public:
        CrpsSimuMethodFactory();
        ~CrpsSimuMethodFactory();
 		typedef IrpsSLSimulationMethod *(*CreateSimuMethodCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSimuMethodCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLSimulationMethod * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateSimuMethodCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateSimuMethodCallback> CallbackMap;
 		static CallbackMap mSimuMethods;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 	};


 	////////////////////////Frequency distribution//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsFrequencyDistributionFactory
 	{
 	public:
        CrpsFrequencyDistributionFactory();
        ~CrpsFrequencyDistributionFactory();
 		typedef IrpsSLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateFrequencyDistributionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLFrequencyDistribution * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateFrequencyDistributionCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateFrequencyDistributionCallback> CallbackMap;
 		static CallbackMap mFrequencyDistributions;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 	};


 	////////////////////////Randomness//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsRandomnessFactory
 	{
 	public:
        CrpsRandomnessFactory();
        ~CrpsRandomnessFactory();
 		typedef IrpsSLRandomness *(*CreateRandomnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateRandomnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLRandomness * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateRandomnessCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateRandomnessCallback> CallbackMap;
 		static CallbackMap mRandomness;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 	};


 	////////////////////////psd decomposition//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsPSDdecomMethodFactory
 	{
 	public:
        CrpsPSDdecomMethodFactory();
        ~CrpsPSDdecomMethodFactory();
 		typedef IrpsSLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePSDdecomMethodCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLPSDdecompositionMethod * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreatePSDdecomMethodCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 		static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreatePSDdecomMethodCallback> CallbackMap;
 		static CallbackMap mPSDdecomMethods;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;


 	};

 	////////////////////////Correlation//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsCorrelationFactory
 	{
 	public:
        CrpsCorrelationFactory();
        ~CrpsCorrelationFactory();
 		typedef IrpsSLCorrelation *(*CreateCorrelationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCorrelationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLCorrelation * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateCorrelationCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
     	static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateCorrelationCallback> CallbackMap;
 		static CallbackMap mCorrelations;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 	};

 	////////////////////////Modulation//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsModulationFactory
 	{
 	public:
        CrpsModulationFactory();
        ~CrpsModulationFactory();
 		typedef IrpsSLModulation *(*CreateModulationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateModulationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLModulation * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateModulationCallback>& GetObjectNamesMap();
 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateModulationCallback> CallbackMap;
 		static CallbackMap mModulations;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 	};

 	///////////Table tool///////////////

 class RPS_CORE_API CrpsTableToolFactory
 {
 	public:
        CrpsTableToolFactory();
        ~CrpsTableToolFactory();
 		typedef IrpsSLTableTool *(*CreateTableToolCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateTableToolCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLTableTool * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateTableToolCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateTableToolCallback> CallbackMap;
 		static CallbackMap mTableTools;
 		static std::vector<std::string> mTableToolNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 ///////////Matrix tool///////////////

 class RPS_CORE_API CrpsMatrixToolFactory
 {
 	public:
        CrpsMatrixToolFactory();
        ~CrpsMatrixToolFactory();
 		typedef IrpsSLMatrixTool *(*CreateMatrixToolCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMatrixToolCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLMatrixTool * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateMatrixToolCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateMatrixToolCallback> CallbackMap;
 		static CallbackMap mMatrixTools;
 		static std::vector<std::string> mMatrixToolNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 ///////////user defined rps object///////////////

 class RPS_CORE_API CrpsUserDefinedRPSObjectFactory
 {
 	public:
        CrpsUserDefinedRPSObjectFactory();
        ~CrpsUserDefinedRPSObjectFactory();
 		typedef IrpsSLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateUserDefinedRPSObjectCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLUserDefinedRPSObject * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateUserDefinedRPSObjectCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateUserDefinedRPSObjectCallback> CallbackMap;
 		static CallbackMap mUserDefinedRPSObjects;
 		static std::vector<std::string> mUserDefinedRPSObjectNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 ///////////cumulative probability distribution///////////////

 class RPS_CORE_API CrpsCumulativeProbabilityDistributionFactory
 {
 	public:
        CrpsCumulativeProbabilityDistributionFactory();
        ~CrpsCumulativeProbabilityDistributionFactory();
 		typedef IrpsSLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCumulativeProbabilityDistributionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLCumulativeProbabilityDistribution * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateCumulativeProbabilityDistributionCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateCumulativeProbabilityDistributionCallback> CallbackMap;
 		static CallbackMap mCumulativeProbabilityDistributions;
 		static std::vector<std::string> mCumulativeProbabilityDistributionNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };


 /////////////////////Kurtosis////////////////////////////////////////////

 class RPS_CORE_API CrpsKurtosisFactory
 {
 	public:
        CrpsKurtosisFactory();
        ~CrpsKurtosisFactory();
 		typedef IrpsSLKurtosis *(*CreateKurtosisCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateKurtosisCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLKurtosis * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateKurtosisCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateKurtosisCallback> CallbackMap;
 		static CallbackMap mKurtosiss;
 		static std::vector<std::string> mKurtosisNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 /////////////////////Peak Factor////////////////////////////////////////////

 class RPS_CORE_API CrpsPeakFactorFactory
 {
 	public:
        CrpsPeakFactorFactory();
        ~CrpsPeakFactorFactory();
 		typedef IrpsSLPeakFactor *(*CreatePeakFactorCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePeakFactorCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLPeakFactor * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreatePeakFactorCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreatePeakFactorCallback> CallbackMap;
 		static CallbackMap mPeakFactors;
 		static std::vector<std::string> mPeakFactorNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 /////////////////////Probability density function////////////////////////////////////////////

 class RPS_CORE_API CrpsProbabilityDensityFunctionFactory
 {
 	public:
        CrpsProbabilityDensityFunctionFactory();
        ~CrpsProbabilityDensityFunctionFactory();
 		typedef IrpsSLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateProbabilityDensityFunctionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLProbabilityDensityFunction * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateProbabilityDensityFunctionCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateProbabilityDensityFunctionCallback> CallbackMap;
 		static CallbackMap mProbabilityDensityFunctions;
 		static std::vector<std::string> mProbabilityDensityFunctionNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };


 /////////////////////Shear velocity of flow////////////////////////////////////////////

 class RPS_CORE_API CrpsShearVelocityOfFlowFactory
 {
 	public:
        CrpsShearVelocityOfFlowFactory();
        ~CrpsShearVelocityOfFlowFactory();
 		typedef IrpsSLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateShearVelocityOfFlowCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLShearVelocityOfFlow * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateShearVelocityOfFlowCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateShearVelocityOfFlowCallback> CallbackMap;
 		static CallbackMap mShearVelocityOfFlows;
 		static std::vector<std::string> mShearVelocityOfFlowNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 /////////////////////Skewness////////////////////////////////////////////

 class RPS_CORE_API CrpsSkewnessFactory
 {
 	public:
        CrpsSkewnessFactory();
        ~CrpsSkewnessFactory();
 		typedef IrpsSLSkewness *(*CreateSkewnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSkewnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLSkewness * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateSkewnessCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateSkewnessCallback> CallbackMap;
 		static CallbackMap mSkewnesss;
 		static std::vector<std::string> mSkewnessNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 /////////////////////Standard deviation////////////////////////////////////////////

 class RPS_CORE_API CrpsStandardDeviationFactory
 {
 	public:
        CrpsStandardDeviationFactory();
        ~CrpsStandardDeviationFactory();
 		typedef IrpsSLStandardDeviation *(*CreateStandardDeviationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateStandardDeviationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLStandardDeviation * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateStandardDeviationCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);

 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateStandardDeviationCallback> CallbackMap;
 		static CallbackMap mStandardDeviations;
 		static std::vector<std::string> mStandardDeviationNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

 /////////////////////Variance////////////////////////////////////////////

 class RPS_CORE_API CrpsVarianceFactory
 {
 	public:
        CrpsVarianceFactory();
        ~CrpsVarianceFactory();
 		typedef IrpsSLVariance *(*CreateVarianceCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateVarianceCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSLVariance * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateVarianceCallback>& GetObjectNamesMap();

 		static QString GetOwnerPlugin();
 		static void SetOwnerPlugin(QString ownerPlugin);
 		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
 		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
 		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
 		static std::map<const std::string, std::string> & GetTitleMap();
 		static std::map<const std::string, std::string> & GetLinkMap();
 		static std::map<const std::string, std::string> & GetAuthorMap();
 		static std::map<const std::string, std::string> & GetDateMap();
 	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
 		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

 	private:
 		typedef std::map<const std::string, CreateVarianceCallback> CallbackMap;
 		static CallbackMap mVariances;
 		static std::vector<std::string> mVarianceNames;
 		static QString mOwnerPlugin;
 		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
 		static std::map<const std::string, std::string> mOjectDescriptionMap;
 		static std::map<const std::string, std::string> mOjectAndPluginMap;
 		static std::map<const std::string, std::string> mTitleMap;
 		static std::map<const std::string, std::string> mLinkMap;
 		static std::map<const std::string, std::string> mAuthorMap;
 		static std::map<const std::string, std::string> mDateMap;
 		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
 		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;

 };

/////////////////////Wave passage effect////////////////////////////////////////////

class RPS_CORE_API CrpsWavePassageEffectFactory
{
	public:
        CrpsWavePassageEffectFactory();
        ~CrpsWavePassageEffectFactory();
        typedef IrpsSLWavePassageEffect *(*CreateWavePassageEffectCallback)();

        static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

        static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateWavePassageEffectCallback cb);

        static void UnregisterObject(const std::string& name, const std::string& pluginName);

        static IrpsSLWavePassageEffect * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

        static std::map<const std::string, CreateWavePassageEffectCallback>& GetObjectNamesMap();

		static QString GetOwnerPlugin();
		static void SetOwnerPlugin(QString ownerPlugin);
		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();
		static std::map<const std::string, std::string> & GetOjectDescriptionMap();
		static std::map<const std::string, std::string> & GetOjectAndPluginMap();
		static std::map<const std::string, std::string> & GetTitleMap();
		static std::map<const std::string, std::string> & GetLinkMap();
		static std::map<const std::string, std::string> & GetAuthorMap();
		static std::map<const std::string, std::string> & GetDateMap();
	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();
		static std::map<const std::string, std::string> & GetVersionMap();
        static std::map<const std::string, PyObject*>& GetProducerMap();
        static std::map<const std::string, bool>& GetStationarityMap();

	private:
        typedef std::map<const std::string, CreateWavePassageEffectCallback> CallbackMap;
        static CallbackMap mWavePassageEffects;
        static std::vector<std::string> mWavePassageEffectNames;
		static QString mOwnerPlugin;
		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;
		static std::map<const std::string, std::string> mOjectDescriptionMap;
		static std::map<const std::string, std::string> mOjectAndPluginMap;
		static std::map<const std::string, std::string> mTitleMap;
		static std::map<const std::string, std::string> mLinkMap;
		static std::map<const std::string, std::string> mAuthorMap;
		static std::map<const std::string, std::string> mDateMap;
		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;
		static std::map<const std::string, std::string> mVersionMap;
        static std::map<const std::string, PyObject*> mProducerMap;
        static std::map<const std::string, bool> mStationarityMap;
};


//#define SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(_ObjectClass_, _ObjectInterface_, _CreateCallback_) \
//class RPS_CORE_API _ObjectClass_\
//{\
//	public:\
//        typedef _ObjectInterface_ *(*_CreateCallback_)();\
//        static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);\
//        static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, _CreateCallback_ cb);\
//        static void UnregisterObject(const std::string& name, const std::string& pluginName);\
//        static _ObjectInterface_ *BuildObject(const std::string& name);\
//		static std::vector<std::string> GetNameVector();\
//        static std::map<const std::string, _CreateCallback_>& GetObjectNamesMap();\
//		static QString GetOwnerPlugin();\
//		static void SetOwnerPlugin(QString ownerPlugin);\
//		static std::map<const std::string, std::string> & GetTobeInstalledObjectsMap();\
//		static std::map<const std::string, std::string> & GetOjectDescriptionMap();\
//		static std::map<const std::string, std::string> & GetOjectAndPluginMap();\
//		static std::map<const std::string, std::string> & GetTitleMap();\
//		static std::map<const std::string, std::string> & GetLinkMap();\
//		static std::map<const std::string, std::string> & GetAuthorMap();\
//		static std::map<const std::string, std::string> & GetDateMap();\
//	    static std::map<const std::string, std::string> & GetOjectsSkipDuringUnintallationMap();\
//		static std::map<const std::string, std::string> & GetVersionMap();\
//	private:\
//        typedef std::map<const std::string, _CreateCallback_> CallbackMap;\
//        static CallbackMap mObjects;\
//        static std::vector<std::string> mObjectNames;\
//        static QString mOwnerPlugin;\
//		static std::map<const std::string, std::string> mTobeInstalledObjectsMap;\
//		static std::map<const std::string, std::string> mOjectDescriptionMap;\
//		static std::map<const std::string, std::string> mOjectAndPluginMap;\
//		static std::map<const std::string, std::string> mTitleMap;\
//		static std::map<const std::string, std::string> mLinkMap;\
//		static std::map<const std::string, std::string> mAuthorMap;\
//		static std::map<const std::string, std::string> mDateMap;\
//		static std::map<const std::string, std::string> mOjectsSkipDuringUnintallationMap;\
//		static std::map<const std::string, std::string> mVersionMap;\
//};
//
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCoherenceFactory, IrpsSLCoherence, IrpsSLCoherenceCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsLocationDistributionFactory, IrpsSLLocationDistribution, IrpsSLLocationDistributionCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMeanFactory, IrpsSLMeanAcceleration, IrpsSLMeanAccelerationCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSpectrumFactory, IrpsSLSpectrum, IrpsSLSpectrumCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsZSpectrumFactory, IrpsSLZSpectrum, IrpsSLZSpectrumCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsYSpectrumFactory, IrpsSLYSpectrum, IrpsSLYSpectrumCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSimuMethodFactory, IrpsSLSimulationMethod, IrpsSLSimulationMethodCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsFrequencyDistributionFactory, IrpsSLFrequencyDistribution, IrpsSLFrequencyDistributionCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRandomnessFactory, IrpsSLRandomness, IrpsSLRandomnessCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPSDdecomMethodFactory, IrpsSLPSDdecompositionMethod, IrpsSLPSDdecompositionMethodCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCorrelationFactory, IrpsSLCorrelation, IrpsSLCorrelationCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsModulationFactory, IrpsSLModulation, IrpsSLModulationCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTableToolFactory, IrpsSLTableTool, IrpsSLTableToolCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMatrixToolFactory, IrpsSLMatrixTool, IrpsSLMatrixToolCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsUserDefinedRPSObjectFactory, IrpsSLUserDefinedRPSObject, IrpsSLUserDefinedRPSObjectCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCumulativeProbabilityDistributionFactory, IrpsSLCumulativeProbabilityDistribution, IrpsSLCumulativeProbabilityDistributionCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsGustFactorFactory, IrpsSLGustFactor, IrpsSLGustFactorCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsKurtosisFactory, IrpsSLKurtosis, IrpsSLKurtosisCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPeakFactorFactory, IrpsSLPeakFactor, IrpsSLPeakFactorCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsProbabilityDensityFunctionFactory, IrpsSLProbabilityDensityFunction, IrpsSLProbabilityDensityFunctionCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRoughnessFactory, IrpsSLRoughness, IrpsSLRoughnessCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsShearVelocityOfFlowFactory, IrpsSLShearVelocityOfFlow, IrpsSLShearVelocityOfFlowCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSkewnessFactory, IrpsSLSkewness, IrpsSLSkewnessCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsStandardDeviationFactory, IrpsSLStandardDeviation, IrpsSLStandardDeviationCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceIntensityFactory, IrpsSLTurbulenceIntensity, IrpsSLTurbulenceIntensityCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceScaleFactory, IrpsSLTurbulenceScale, IrpsSLTurbulenceScaleCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsVarianceFactory, IrpsSLVariance, IrpsSLVarianceCallback)
//
//SEISMICLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsWavePassageEffectFactory, IrpsSLWavePassageEffect, IrpsSLWavePassageEffectCallback)

} //namespace SeismicLabAPI

#endif
