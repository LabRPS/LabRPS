
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

#include "RPSSeaLabAPIdefines.h"
#include "IrpsSeLCoherence.h"
#include "IrpsSeLLocationDistribution.h"
#include "IrpsSeLMeanAcceleration.h"
#include "IrpsSeLSpectrum.h"
#include "IrpsSeLSimulationMethod.h"
#include "IrpsSeLFrequencyDistribution.h"
#include "IrpsSeLRandomness.h"
#include "IrpsSeLPSDdecompositionMethod.h"
#include "IrpsSeLCorrelation.h"
#include "IrpsSeLModulation.h"
#include "IrpsSeLTableTool.h"
#include "IrpsSeLMatrixTool.h"
#include "IrpsSeLUserDefinedRPSObject.h"
#include "IrpsSeLCumulativeProbabilityDistribution.h"
#include "IrpsSeLKurtosis.h"
#include "IrpsSeLPeakFactor.h"
#include "IrpsSeLProbabilityDensityFunction.h"
#include "IrpsSeLShearVelocityOfFlow.h"
#include "IrpsSeLSkewness.h"
#include "IrpsSeLStandardDeviation.h"
#include "IrpsSeLVariance.h"
#include "IrpsSeLWavePassageEffect.h"

#include <map>
#include<vector>

#include <QString>


#include <App/RPSFeature.h>

namespace SeaLabAPI {

class RPS_CORE_API RPSSeaLabAPIInfo
{
public:

	static const char * getSeaLabAPIVersion();
};

 class RPS_CORE_API CrpsCoherenceFactory
 {
 	public:
        CrpsCoherenceFactory();
        ~CrpsCoherenceFactory();

 		typedef IrpsSeLCoherence *(*CreateCoherenceCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCoherenceCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLCoherence * BuildObject(const std::string& name);
        
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
 		typedef SeaLabAPI::IrpsSeLLocationDistribution *(*CreateLocDistrCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateLocDistrCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static  SeaLabAPI::IrpsSeLLocationDistribution * BuildObject(const std::string& name);

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

 		typedef IrpsSeLMeanAcceleration *(*CreateMeanCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMeanCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLMeanAcceleration * BuildObject(const std::string& name);

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
 		typedef IrpsSeLSpectrum *(*CreateXSpectrumCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateXSpectrumCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLSpectrum * BuildObject(const std::string& name);

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
 		typedef IrpsSeLSimulationMethod *(*CreateSimuMethodCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSimuMethodCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLSimulationMethod * BuildObject(const std::string& name);

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
 		typedef IrpsSeLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateFrequencyDistributionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLFrequencyDistribution * BuildObject(const std::string& name);

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
 		typedef IrpsSeLRandomness *(*CreateRandomnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateRandomnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLRandomness * BuildObject(const std::string& name);

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
 		typedef IrpsSeLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePSDdecomMethodCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLPSDdecompositionMethod * BuildObject(const std::string& name);

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
 		typedef IrpsSeLCorrelation *(*CreateCorrelationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCorrelationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLCorrelation * BuildObject(const std::string& name);

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
 		typedef IrpsSeLModulation *(*CreateModulationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateModulationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLModulation * BuildObject(const std::string& name);

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
 		typedef IrpsSeLTableTool *(*CreateTableToolCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateTableToolCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLTableTool * BuildObject(const std::string& name);

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
 		typedef IrpsSeLMatrixTool *(*CreateMatrixToolCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMatrixToolCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLMatrixTool * BuildObject(const std::string& name);

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
 		typedef IrpsSeLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateUserDefinedRPSObjectCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLUserDefinedRPSObject * BuildObject(const std::string& name);

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
 		typedef IrpsSeLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCumulativeProbabilityDistributionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLCumulativeProbabilityDistribution * BuildObject(const std::string& name);

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
 		typedef IrpsSeLKurtosis *(*CreateKurtosisCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateKurtosisCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLKurtosis * BuildObject(const std::string& name);

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
 		typedef IrpsSeLPeakFactor *(*CreatePeakFactorCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePeakFactorCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLPeakFactor * BuildObject(const std::string& name);

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
 		typedef IrpsSeLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateProbabilityDensityFunctionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLProbabilityDensityFunction * BuildObject(const std::string& name);

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
 		typedef IrpsSeLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateShearVelocityOfFlowCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLShearVelocityOfFlow * BuildObject(const std::string& name);

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
 		typedef IrpsSeLSkewness *(*CreateSkewnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSkewnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLSkewness * BuildObject(const std::string& name);

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
 		typedef IrpsSeLStandardDeviation *(*CreateStandardDeviationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateStandardDeviationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLStandardDeviation * BuildObject(const std::string& name);

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
 		typedef IrpsSeLVariance *(*CreateVarianceCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateVarianceCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsSeLVariance * BuildObject(const std::string& name);

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
        typedef IrpsSeLWavePassageEffect *(*CreateWavePassageEffectCallback)();

        static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

        static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateWavePassageEffectCallback cb);

        static void UnregisterObject(const std::string& name, const std::string& pluginName);

        static IrpsSeLWavePassageEffect * BuildObject(const std::string& name);

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


//#define SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(_ObjectClass_, _ObjectInterface_, _CreateCallback_) \
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
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCoherenceFactory, IrpsSeLCoherence, IrpsSeLCoherenceCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsLocationDistributionFactory, IrpsSeLLocationDistribution, IrpsSeLLocationDistributionCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMeanFactory, IrpsSeLMeanAcceleration, IrpsSeLMeanAccelerationCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSpectrumFactory, IrpsSeLSpectrum, IrpsSeLSpectrumCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsZSpectrumFactory, IrpsSeLZSpectrum, IrpsSeLZSpectrumCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsYSpectrumFactory, IrpsSeLYSpectrum, IrpsSeLYSpectrumCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSimuMethodFactory, IrpsSeLSimulationMethod, IrpsSeLSimulationMethodCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsFrequencyDistributionFactory, IrpsSeLFrequencyDistribution, IrpsSeLFrequencyDistributionCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRandomnessFactory, IrpsSeLRandomness, IrpsSeLRandomnessCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPSDdecomMethodFactory, IrpsSeLPSDdecompositionMethod, IrpsSeLPSDdecompositionMethodCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCorrelationFactory, IrpsSeLCorrelation, IrpsSeLCorrelationCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsModulationFactory, IrpsSeLModulation, IrpsSeLModulationCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTableToolFactory, IrpsSeLTableTool, IrpsSeLTableToolCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMatrixToolFactory, IrpsSeLMatrixTool, IrpsSeLMatrixToolCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsUserDefinedRPSObjectFactory, IrpsSeLUserDefinedRPSObject, IrpsSeLUserDefinedRPSObjectCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCumulativeProbabilityDistributionFactory, IrpsSeLCumulativeProbabilityDistribution, IrpsSeLCumulativeProbabilityDistributionCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsGustFactorFactory, IrpsSeLGustFactor, IrpsSeLGustFactorCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsKurtosisFactory, IrpsSeLKurtosis, IrpsSeLKurtosisCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPeakFactorFactory, IrpsSeLPeakFactor, IrpsSeLPeakFactorCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsProbabilityDensityFunctionFactory, IrpsSeLProbabilityDensityFunction, IrpsSeLProbabilityDensityFunctionCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRoughnessFactory, IrpsSeLRoughness, IrpsSeLRoughnessCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsShearVelocityOfFlowFactory, IrpsSeLShearVelocityOfFlow, IrpsSeLShearVelocityOfFlowCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSkewnessFactory, IrpsSeLSkewness, IrpsSeLSkewnessCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsStandardDeviationFactory, IrpsSeLStandardDeviation, IrpsSeLStandardDeviationCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceIntensityFactory, IrpsSeLTurbulenceIntensity, IrpsSeLTurbulenceIntensityCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceScaleFactory, IrpsSeLTurbulenceScale, IrpsSeLTurbulenceScaleCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsVarianceFactory, IrpsSeLVariance, IrpsSeLVarianceCallback)
//
//SEALAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsWavePassageEffectFactory, IrpsSeLWavePassageEffect, IrpsSeLWavePassageEffectCallback)

} //namespace SeaLabAPI

#endif
