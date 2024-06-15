
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

#include <QString>


#include <App/RPSFeature.h>

namespace WindLabAPI {

class RPS_CORE_API RPSWindLabAPIInfo
{
public:

	static const char * getWindLabAPIVersion();
};

 class RPS_CORE_API CrpsCoherenceFactory
 {
 	public:
        CrpsCoherenceFactory();
        ~CrpsCoherenceFactory();

 		typedef IrpsWLCoherence *(*CreateCoherenceCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCoherenceCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLCoherence * BuildObject(const std::string& name);
        
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
 		typedef WindLabAPI::IrpsWLLocationDistribution *(*CreateLocDistrCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateLocDistrCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static  WindLabAPI::IrpsWLLocationDistribution * BuildObject(const std::string& name);

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

 		typedef IrpsWLMean *(*CreateMeanCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMeanCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLMean * BuildObject(const std::string& name);

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

 	class RPS_CORE_API CrpsXSpectrumFactory
 	{
 	public:
        CrpsXSpectrumFactory();
        ~CrpsXSpectrumFactory();
 		typedef IrpsWLXSpectrum *(*CreateXSpectrumCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateXSpectrumCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLXSpectrum * BuildObject(const std::string& name);

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


 	//////////////////////// Vertical wind Sepctrum//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsZSpectrumFactory
 	{
 	public:
        CrpsZSpectrumFactory();
        ~CrpsZSpectrumFactory();
 		typedef IrpsWLZSpectrum *(*CreateZSpectrumCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateZSpectrumCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLZSpectrum * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateZSpectrumCallback>& GetObjectNamesMap();
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
 		typedef std::map<const std::string, CreateZSpectrumCallback> CallbackMap;
 		static CallbackMap mZSpectrums;
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


 	//////////////////////// Across wind Sepctrum//////////////////////////////////////////////////

 	class RPS_CORE_API CrpsYSpectrumFactory
 	{
 	public:
        CrpsYSpectrumFactory();
        ~CrpsYSpectrumFactory();
 		typedef IrpsWLYSpectrum *(*CreateYSpectrumCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateYSpectrumCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLYSpectrum * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateYSpectrumCallback>& GetObjectNamesMap();
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
 		typedef std::map<const std::string, CreateYSpectrumCallback> CallbackMap;
 		static CallbackMap mYSpectrums;
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
 		typedef IrpsWLSimuMethod *(*CreateSimuMethodCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSimuMethodCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLSimuMethod * BuildObject(const std::string& name);

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
 		typedef IrpsWLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateFrequencyDistributionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLFrequencyDistribution * BuildObject(const std::string& name);

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
 		typedef IrpsWLRandomness *(*CreateRandomnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateRandomnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLRandomness * BuildObject(const std::string& name);

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
 		typedef IrpsWLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePSDdecomMethodCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLPSDdecompositionMethod * BuildObject(const std::string& name);

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
 		typedef IrpsWLCorrelation *(*CreateCorrelationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCorrelationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLCorrelation * BuildObject(const std::string& name);

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
 		typedef IrpsWLModulation *(*CreateModulationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 		static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateModulationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLModulation * BuildObject(const std::string& name);

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
 		typedef IrpsWLTableTool *(*CreateTableToolCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateTableToolCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLTableTool * BuildObject(const std::string& name);

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
 		typedef IrpsWLMatrixTool *(*CreateMatrixToolCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMatrixToolCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLMatrixTool * BuildObject(const std::string& name);

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
 		typedef IrpsWLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateUserDefinedRPSObjectCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLUserDefinedRPSObject * BuildObject(const std::string& name);

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
 		typedef IrpsWLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCumulativeProbabilityDistributionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLCumulativeProbabilityDistribution * BuildObject(const std::string& name);

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

 /////////////////////Gust factor////////////////////////////////////////////

 class RPS_CORE_API CrpsGustFactorFactory
 {
 	public:
        CrpsGustFactorFactory();
        ~CrpsGustFactorFactory();
 		typedef IrpsWLGustFactor *(*CreateGustFactorCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateGustFactorCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLGustFactor * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateGustFactorCallback>& GetObjectNamesMap();

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
 		typedef std::map<const std::string, CreateGustFactorCallback> CallbackMap;
 		static CallbackMap mGustFactors;
 		static std::vector<std::string> mGustFactorNames;
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
 		typedef IrpsWLKurtosis *(*CreateKurtosisCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateKurtosisCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLKurtosis * BuildObject(const std::string& name);

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
 		typedef IrpsWLPeakFactor *(*CreatePeakFactorCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePeakFactorCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLPeakFactor * BuildObject(const std::string& name);

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
 		typedef IrpsWLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateProbabilityDensityFunctionCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLProbabilityDensityFunction * BuildObject(const std::string& name);

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

 /////////////////////Roughness////////////////////////////////////////////

 class RPS_CORE_API CrpsRoughnessFactory
 {
 	public:
        CrpsRoughnessFactory();
        ~CrpsRoughnessFactory();
 		typedef IrpsWLRoughness *(*CreateRoughnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateRoughnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLRoughness * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateRoughnessCallback>& GetObjectNamesMap();

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
 		typedef std::map<const std::string, CreateRoughnessCallback> CallbackMap;
 		static CallbackMap mRoughnesss;
 		static std::vector<std::string> mRoughnessNames;
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
 		typedef IrpsWLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateShearVelocityOfFlowCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLShearVelocityOfFlow * BuildObject(const std::string& name);

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
 		typedef IrpsWLSkewness *(*CreateSkewnessCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSkewnessCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLSkewness * BuildObject(const std::string& name);

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
 		typedef IrpsWLStandardDeviation *(*CreateStandardDeviationCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateStandardDeviationCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLStandardDeviation * BuildObject(const std::string& name);

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

 /////////////////////Turbulence Intensity////////////////////////////////////////////

 class RPS_CORE_API CrpsTurbulenceIntensityFactory
 {
 	public:
        CrpsTurbulenceIntensityFactory();
        ~CrpsTurbulenceIntensityFactory();
 		typedef IrpsWLTurbulenceIntensity *(*CreateTurbulenceIntensityCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateTurbulenceIntensityCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLTurbulenceIntensity * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateTurbulenceIntensityCallback>& GetObjectNamesMap();

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
 		typedef std::map<const std::string, CreateTurbulenceIntensityCallback> CallbackMap;
 		static CallbackMap mTurbulenceIntensitys;
 		static std::vector<std::string> mTurbulenceIntensityNames;
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

 /////////////////////Turbulence scale////////////////////////////////////////////

 class RPS_CORE_API CrpsTurbulenceScaleFactory
 {
 	public:
        CrpsTurbulenceScaleFactory();
        ~CrpsTurbulenceScaleFactory();
 		typedef IrpsWLTurbulenceScale *(*CreateTurbulenceScaleCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateTurbulenceScaleCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLTurbulenceScale * BuildObject(const std::string& name);

        static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 		static std::map<const std::string, CreateTurbulenceScaleCallback>& GetObjectNamesMap();

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
 		typedef std::map<const std::string, CreateTurbulenceScaleCallback> CallbackMap;
 		static CallbackMap mTurbulenceScales;
 		static std::vector<std::string> mTurbulenceScaleNames;
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
 		typedef IrpsWLVariance *(*CreateVarianceCallback)();

 		static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

         static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateVarianceCallback cb);

 		static void UnregisterObject(const std::string& name, const std::string& pluginName);

 		static IrpsWLVariance * BuildObject(const std::string& name);

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
        typedef IrpsWLWavePassageEffect *(*CreateWavePassageEffectCallback)();

        static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

        static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateWavePassageEffectCallback cb);

        static void UnregisterObject(const std::string& name, const std::string& pluginName);

        static IrpsWLWavePassageEffect * BuildObject(const std::string& name);

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


//#define WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(_ObjectClass_, _ObjectInterface_, _CreateCallback_) \
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
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCoherenceFactory, IrpsWLCoherence, IrpsWLCoherenceCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsLocationDistributionFactory, IrpsWLLocationDistribution, IrpsWLLocationDistributionCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMeanFactory, IrpsWLMean, IrpsWLMeanCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsXSpectrumFactory, IrpsWLXSpectrum, IrpsWLXSpectrumCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsZSpectrumFactory, IrpsWLZSpectrum, IrpsWLZSpectrumCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsYSpectrumFactory, IrpsWLYSpectrum, IrpsWLYSpectrumCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSimuMethodFactory, IrpsWLSimuMethod, IrpsWLSimuMethodCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsFrequencyDistributionFactory, IrpsWLFrequencyDistribution, IrpsWLFrequencyDistributionCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRandomnessFactory, IrpsWLRandomness, IrpsWLRandomnessCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPSDdecomMethodFactory, IrpsWLPSDdecompositionMethod, IrpsWLPSDdecompositionMethodCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCorrelationFactory, IrpsWLCorrelation, IrpsWLCorrelationCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsModulationFactory, IrpsWLModulation, IrpsWLModulationCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTableToolFactory, IrpsWLTableTool, IrpsWLTableToolCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsMatrixToolFactory, IrpsWLMatrixTool, IrpsWLMatrixToolCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsUserDefinedRPSObjectFactory, IrpsWLUserDefinedRPSObject, IrpsWLUserDefinedRPSObjectCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsCumulativeProbabilityDistributionFactory, IrpsWLCumulativeProbabilityDistribution, IrpsWLCumulativeProbabilityDistributionCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsGustFactorFactory, IrpsWLGustFactor, IrpsWLGustFactorCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsKurtosisFactory, IrpsWLKurtosis, IrpsWLKurtosisCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsPeakFactorFactory, IrpsWLPeakFactor, IrpsWLPeakFactorCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsProbabilityDensityFunctionFactory, IrpsWLProbabilityDensityFunction, IrpsWLProbabilityDensityFunctionCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsRoughnessFactory, IrpsWLRoughness, IrpsWLRoughnessCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsShearVelocityOfFlowFactory, IrpsWLShearVelocityOfFlow, IrpsWLShearVelocityOfFlowCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsSkewnessFactory, IrpsWLSkewness, IrpsWLSkewnessCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsStandardDeviationFactory, IrpsWLStandardDeviation, IrpsWLStandardDeviationCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceIntensityFactory, IrpsWLTurbulenceIntensity, IrpsWLTurbulenceIntensityCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsTurbulenceScaleFactory, IrpsWLTurbulenceScale, IrpsWLTurbulenceScaleCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsVarianceFactory, IrpsWLVariance, IrpsWLVarianceCallback)
//
//WINDLAB_API_OBJECT_FACTORY_CLASS_HEADER(CrpsWavePassageEffectFactory, IrpsWLWavePassageEffect, IrpsWLWavePassageEffectCallback)

} //namespace WindLabAPI

#endif
