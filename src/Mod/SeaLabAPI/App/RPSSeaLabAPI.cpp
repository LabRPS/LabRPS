
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

#include "PreCompiled.h"
#include "RPSSeaLabAPI.h"
#include <iostream>
#include <CXX/Objects.hxx>
#include <Base/Interpreter.h>
#include <App/Application.h>

using namespace SeaLabAPI;

 typedef IrpsSeLLocationDistribution *(*CreateLocDistrCallback)();
 typedef IrpsSeLMeanAcceleration *(*CreateMeanCallback)();
 typedef IrpsSeLCoherence *(*CreateCoherenceCallback)();
 typedef IrpsSeLSimulationMethod *(*CreateSimuMethodCallback)();
 typedef IrpsSeLFrequencyDistribution *(*CreateFrequencyDistributionCallback)();
 typedef IrpsSeLRandomness *(*CreateRandomnessCallback)();
 typedef IrpsSeLPSDdecompositionMethod *(*CreatePSDdecomMethodCallback)();
 typedef IrpsSeLCorrelation *(*CreateCorrelationCallback)();
 typedef IrpsSeLModulation *(*CreateModulationCallback)();
 typedef IrpsSeLTableTool *(*CreateTableToolCallback)();
 typedef IrpsSeLMatrixTool *(*CreateMatrixToolCallback)();
 typedef IrpsSeLUserDefinedRPSObject *(*CreateUserDefinedRPSObjectCallback)();
 typedef IrpsSeLCumulativeProbabilityDistribution *(*CreateCumulativeProbabilityDistributionCallback)();
 typedef IrpsSeLKurtosis *(*CreateKurtosisCallback)();
 typedef IrpsSeLPeakFactor *(*CreatePeakFactorCallback)();
 typedef IrpsSeLProbabilityDensityFunction *(*CreateProbabilityDensityFunctionCallback)();
 typedef IrpsSeLShearVelocityOfFlow *(*CreateShearVelocityOfFlowCallback)();
 typedef IrpsSeLSkewness *(*CreateSkewnessCallback)();
 typedef IrpsSeLStandardDeviation *(*CreateStandardDeviationCallback)();
 typedef IrpsSeLVariance *(*CreateVarianceCallback)();
 typedef IrpsSeLWavePassageEffect *(*CreateWavePassageEffectCallback)();
 typedef IrpsSeLFrequencySpectrum *(*CreateFrequencySpectrumCallback)();
 typedef IrpsSeLDirectionalSpectrum *(*CreateDirectionalSpectrumCallback)();
 typedef IrpsSeLDirectionalSpreadingFunction *(*CreateDirectionalSpreadingFunctionCallback)();


const char * RPSSeaLabAPIInfo::getSeaLabAPIVersion()
{
	return "0.1";
}

 	CrpsCoherenceFactory::CallbackMap CrpsCoherenceFactory::mCoherences;
 	std::vector<std::string> CrpsCoherenceFactory::mCoherenceNames;
 	QString CrpsCoherenceFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mOjectAndPluginMap;
    std::map<const std::string, std::string> CrpsCoherenceFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsCoherenceFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsCoherenceFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsCoherenceFactory::mProducerMap;
    std::map<const std::string, bool> CrpsCoherenceFactory::mStationarityMap;

    CrpsCoherenceFactory::CrpsCoherenceFactory() {}
    CrpsCoherenceFactory::~CrpsCoherenceFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsCoherenceFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsCoherenceFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
     void CrpsCoherenceFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
        mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version; 
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsCoherenceFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCoherenceCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mCoherences[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsCoherenceFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mCoherences.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLCoherence *CrpsCoherenceFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mCoherences.find(name);
 		if (it != mCoherences.end())
 		{
 			// call the creation callback to construct this derived name
 			return (it->second)();
 		}

 		return NULL;
 	}

     PyObject* CrpsCoherenceFactory::produceFeature(const std::string& newFeatureName,
                                                   const std::string& simulationName,
                                                   const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        // now run the method
        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));


        //args.setItem(0, dict);
        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
    }

 	std::map<const std::string, CreateCoherenceCallback>& CrpsCoherenceFactory::GetObjectNamesMap()
 	{
 		return mCoherences;
 	}

 	std::map<const std::string, std::string> & CrpsCoherenceFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsCoherenceFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}


     std::map<const std::string, std::string> &  CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsCoherenceFactory::GetProducerMap()
     {
        return mProducerMap;
     }

     std::map<const std::string, bool>& CrpsCoherenceFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsLocationDistributionFactory::CallbackMap CrpsLocationDistributionFactory::mLocationDistributions;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mOjectAndPluginMap;
    std::map<const std::string, std::string> CrpsLocationDistributionFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsLocationDistributionFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsLocationDistributionFactory::mProducerMap;
    std::map<const std::string, bool> CrpsLocationDistributionFactory::mStationarityMap;

 	QString CrpsLocationDistributionFactory::mOwnerPlugin;

CrpsLocationDistributionFactory::CrpsLocationDistributionFactory()
{
}
CrpsLocationDistributionFactory::~CrpsLocationDistributionFactory()
{
   Base::PyGILStateLocker lock;
  for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin(); it != mProducerMap.end(); ++it) {

       Py_DECREF(it->second);           
  }
}

 	QString CrpsLocationDistributionFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsLocationDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsLocationDistributionFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;



 	}

 	void CrpsLocationDistributionFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateLocDistrCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mLocationDistributions[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsLocationDistributionFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mLocationDistributions.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}		
 	}

    IrpsSeLLocationDistribution *CrpsLocationDistributionFactory::BuildObject(const std::string& name)
 	{
        CallbackMap::iterator it = mLocationDistributions.find(name);
        if (it != mLocationDistributions.end()) {
            return (it->second)();
        }
 		return NULL;
 	}

    PyObject* CrpsLocationDistributionFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
    }


 	std::map<const std::string, CreateLocDistrCallback>& CrpsLocationDistributionFactory::GetObjectNamesMap()
 	{
 		return mLocationDistributions;
 	}

 	std::map<const std::string, std::string> & CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsLocationDistributionFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }
     std::map<const std::string, PyObject*>& CrpsLocationDistributionFactory::GetProducerMap()
    {
        return mProducerMap;
    }

     std::map<const std::string, bool>& CrpsLocationDistributionFactory::GetStationarityMap()
    {
        return mStationarityMap;
    }

 	CrpsMeanFactory::CallbackMap CrpsMeanFactory::mMeans;
 	QString CrpsMeanFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsMeanFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsMeanFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsMeanFactory::mOjectAndPluginMap;
    std::map<const std::string, std::string> CrpsMeanFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsMeanFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsMeanFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsMeanFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsMeanFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsMeanFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsMeanFactory::mProducerMap;
    std::map<const std::string, bool> CrpsMeanFactory::mStationarityMap;

 	QString CrpsMeanFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsMeanFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

    CrpsMeanFactory::CrpsMeanFactory() {}
    CrpsMeanFactory::~CrpsMeanFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	void CrpsMeanFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version; 
        mStationarityMap[name] = stationarity;

 	}

 	void CrpsMeanFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMeanCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mMeans[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsMeanFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mMeans.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}


 	}

 	IrpsSeLMeanAcceleration *CrpsMeanFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mMeans.find(name);
 		if (it != mMeans.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

     PyObject* CrpsMeanFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
		return Py::new_reference_to(res);
    }

 	std::map<const std::string, CreateMeanCallback>& CrpsMeanFactory::GetObjectNamesMap()
 	{
 		return mMeans;
 	}

 	std::map<const std::string, std::string> & CrpsMeanFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsMeanFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}
 	std::map<const std::string, std::string>& CrpsMeanFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsMeanFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsMeanFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsMeanFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsMeanFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsMeanFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

      std::map<const std::string, PyObject*>& CrpsMeanFactory::GetProducerMap()
     {
        return mProducerMap;
     }

           std::map<const std::string, bool>& CrpsMeanFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsSimuMethodFactory::CallbackMap CrpsSimuMethodFactory::mSimuMethods;
 	QString CrpsSimuMethodFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsSimuMethodFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsSimuMethodFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsSimuMethodFactory::mProducerMap;
    std::map<const std::string, bool> CrpsSimuMethodFactory::mStationarityMap;

    CrpsSimuMethodFactory::CrpsSimuMethodFactory() {}
    CrpsSimuMethodFactory::~CrpsSimuMethodFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsSimuMethodFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsSimuMethodFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsSimuMethodFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsSimuMethodFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSimuMethodCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mSimuMethods[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsSimuMethodFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mSimuMethods.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLSimulationMethod *CrpsSimuMethodFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mSimuMethods.find(name);
 		if (it != mSimuMethods.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

     PyObject* CrpsSimuMethodFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));


        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

 	std::map<const std::string, CreateSimuMethodCallback>& CrpsSimuMethodFactory::GetObjectNamesMap()
 	{
 		return mSimuMethods;
 	}

 	std::map<const std::string, std::string> & CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsSimuMethodFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}


 	std::map<const std::string, std::string> &  CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

    std::map<const std::string, PyObject*>& CrpsSimuMethodFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsSimuMethodFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsFrequencyDistributionFactory::CallbackMap CrpsFrequencyDistributionFactory::mFrequencyDistributions;
 	QString CrpsFrequencyDistributionFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsFrequencyDistributionFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsFrequencyDistributionFactory::mProducerMap;
    std::map<const std::string, bool> CrpsFrequencyDistributionFactory::mStationarityMap;

    CrpsFrequencyDistributionFactory::CrpsFrequencyDistributionFactory() {}
    CrpsFrequencyDistributionFactory::~CrpsFrequencyDistributionFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsFrequencyDistributionFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsFrequencyDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsFrequencyDistributionFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsFrequencyDistributionFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateFrequencyDistributionCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mFrequencyDistributions[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsFrequencyDistributionFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mFrequencyDistributions.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLFrequencyDistribution *CrpsFrequencyDistributionFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mFrequencyDistributions.find(name);
 		if (it != mFrequencyDistributions.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsFrequencyDistributionFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
    }

 	std::map<const std::string, CreateFrequencyDistributionCallback>& CrpsFrequencyDistributionFactory::GetObjectNamesMap()
 	{
 		return mFrequencyDistributions;
 	}

 	std::map<const std::string, std::string> & CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencyDistributionFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}
	
 	std::map<const std::string, std::string> &  CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsFrequencyDistributionFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsFrequencyDistributionFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsRandomnessFactory::CallbackMap CrpsRandomnessFactory::mRandomness;
 	QString CrpsRandomnessFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsRandomnessFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsRandomnessFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsRandomnessFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsRandomnessFactory::mProducerMap;
    std::map<const std::string, bool> CrpsRandomnessFactory::mStationarityMap;

    CrpsRandomnessFactory::CrpsRandomnessFactory() {}
    CrpsRandomnessFactory::~CrpsRandomnessFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsRandomnessFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsRandomnessFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsRandomnessFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsRandomnessFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateRandomnessCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mRandomness[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsRandomnessFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mRandomness.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLRandomness *CrpsRandomnessFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mRandomness.find(name);
 		if (it != mRandomness.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsRandomnessFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

 	std::map<const std::string, CreateRandomnessCallback>& CrpsRandomnessFactory::GetObjectNamesMap()
 	{
 		return mRandomness;
 	}

 	std::map<const std::string, std::string> & CrpsRandomnessFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsRandomnessFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

    std::map<const std::string, PyObject*>& CrpsRandomnessFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsRandomnessFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsPSDdecomMethodFactory::CallbackMap CrpsPSDdecomMethodFactory::mPSDdecomMethods;
 	QString CrpsPSDdecomMethodFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsPSDdecomMethodFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsPSDdecomMethodFactory::mProducerMap;
    std::map<const std::string, bool> CrpsPSDdecomMethodFactory::mStationarityMap;

    CrpsPSDdecomMethodFactory::CrpsPSDdecomMethodFactory() {}
    CrpsPSDdecomMethodFactory::~CrpsPSDdecomMethodFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsPSDdecomMethodFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsPSDdecomMethodFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsPSDdecomMethodFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;


 	}

 	void CrpsPSDdecomMethodFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePSDdecomMethodCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mPSDdecomMethods[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsPSDdecomMethodFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mPSDdecomMethods.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}	
 	}

 	IrpsSeLPSDdecompositionMethod *CrpsPSDdecomMethodFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mPSDdecomMethods.find(name);
 		if (it != mPSDdecomMethods.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsPSDdecomMethodFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));


        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

 	std::map<const std::string, CreatePSDdecomMethodCallback>& CrpsPSDdecomMethodFactory::GetObjectNamesMap()
 	{
 		return mPSDdecomMethods;
 	}

 	std::map<const std::string, std::string> & CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsPSDdecomMethodFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

    std::map<const std::string, PyObject*>& CrpsPSDdecomMethodFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsPSDdecomMethodFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsCorrelationFactory::CallbackMap CrpsCorrelationFactory::mCorrelations;
 	QString CrpsCorrelationFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsCorrelationFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsCorrelationFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsCorrelationFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsCorrelationFactory::mProducerMap;
    std::map<const std::string, bool> CrpsCorrelationFactory::mStationarityMap;

    CrpsCorrelationFactory::CrpsCorrelationFactory() {}
    CrpsCorrelationFactory::~CrpsCorrelationFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsCorrelationFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsCorrelationFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsCorrelationFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;



 	}

 	void CrpsCorrelationFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCorrelationCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mCorrelations[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;

 	}

 	void CrpsCorrelationFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mCorrelations.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLCorrelation *CrpsCorrelationFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mCorrelations.find(name);
 		if (it != mCorrelations.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsCorrelationFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));


        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

 	std::map<const std::string, CreateCorrelationCallback>& CrpsCorrelationFactory::GetObjectNamesMap()
 	{
 		return mCorrelations;
 	}

 	std::map<const std::string, std::string> & CrpsCorrelationFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsCorrelationFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsCorrelationFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

    std::map<const std::string, PyObject*>& CrpsCorrelationFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsCorrelationFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsModulationFactory::CallbackMap CrpsModulationFactory::mModulations;
 	QString CrpsModulationFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsModulationFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsModulationFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsModulationFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsModulationFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsModulationFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsModulationFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsModulationFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsModulationFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsModulationFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsModulationFactory::mProducerMap;
    std::map<const std::string, bool> CrpsModulationFactory::mStationarityMap;

    CrpsModulationFactory::CrpsModulationFactory() {}
    CrpsModulationFactory::~CrpsModulationFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsModulationFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsModulationFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsModulationFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsModulationFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateModulationCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mModulations[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsModulationFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mModulations.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLModulation *CrpsModulationFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mModulations.find(name);
 		if (it != mModulations.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsModulationFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));


        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

 	std::map<const std::string, CreateModulationCallback>& CrpsModulationFactory::GetObjectNamesMap()
 	{
 		return mModulations;
 	}

 	std::map<const std::string, std::string> & CrpsModulationFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsModulationFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsModulationFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsModulationFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsModulationFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsModulationFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsModulationFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsModulationFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

    std::map<const std::string, PyObject*>& CrpsModulationFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsModulationFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsTableToolFactory::CallbackMap CrpsTableToolFactory::mTableTools;
 	std::vector<std::string> CrpsTableToolFactory::mTableToolNames;
 	QString CrpsTableToolFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsTableToolFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsTableToolFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsTableToolFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsTableToolFactory::mProducerMap;
    std::map<const std::string, bool> CrpsTableToolFactory::mStationarityMap;

    CrpsTableToolFactory::CrpsTableToolFactory() {}
    CrpsTableToolFactory::~CrpsTableToolFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsTableToolFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsTableToolFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsTableToolFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsTableToolFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateTableToolCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mTableTools[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsTableToolFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mTableTools.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLTableTool *CrpsTableToolFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mTableTools.find(name);
 		if (it != mTableTools.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsTableToolFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateTableToolCallback>& CrpsTableToolFactory::GetObjectNamesMap()
 	{
 		return mTableTools;
 	}

 	std::map<const std::string, std::string> & CrpsTableToolFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsTableToolFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}


     std::map<const std::string, std::string> &  CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsTableToolFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsTableToolFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsMatrixToolFactory::CallbackMap CrpsMatrixToolFactory::mMatrixTools;
 	std::vector<std::string> CrpsMatrixToolFactory::mMatrixToolNames;
 	QString CrpsMatrixToolFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsMatrixToolFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsMatrixToolFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsMatrixToolFactory::mProducerMap;
    std::map<const std::string, bool> CrpsMatrixToolFactory::mStationarityMap;

    CrpsMatrixToolFactory::CrpsMatrixToolFactory() {}
    CrpsMatrixToolFactory::~CrpsMatrixToolFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsMatrixToolFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsMatrixToolFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsMatrixToolFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsMatrixToolFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateMatrixToolCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mMatrixTools[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
 	}

 	void CrpsMatrixToolFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mMatrixTools.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLMatrixTool *CrpsMatrixToolFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mMatrixTools.find(name);
 		if (it != mMatrixTools.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsMatrixToolFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateMatrixToolCallback>& CrpsMatrixToolFactory::GetObjectNamesMap()
 	{
 		return mMatrixTools;
 	}

 	std::map<const std::string, std::string> & CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	
 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsMatrixToolFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}


     std::map<const std::string, std::string> &  CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsMatrixToolFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsMatrixToolFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsUserDefinedRPSObjectFactory::CallbackMap CrpsUserDefinedRPSObjectFactory::mUserDefinedRPSObjects;
 	std::vector<std::string> CrpsUserDefinedRPSObjectFactory::mUserDefinedRPSObjectNames;
 	QString CrpsUserDefinedRPSObjectFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsUserDefinedRPSObjectFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsUserDefinedRPSObjectFactory::mProducerMap;
    std::map<const std::string, bool> CrpsUserDefinedRPSObjectFactory::mStationarityMap;

    CrpsUserDefinedRPSObjectFactory::CrpsUserDefinedRPSObjectFactory() {}
    CrpsUserDefinedRPSObjectFactory::~CrpsUserDefinedRPSObjectFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsUserDefinedRPSObjectFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsUserDefinedRPSObjectFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsUserDefinedRPSObjectFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsUserDefinedRPSObjectFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateUserDefinedRPSObjectCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mUserDefinedRPSObjects[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsUserDefinedRPSObjectFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mUserDefinedRPSObjects.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLUserDefinedRPSObject *CrpsUserDefinedRPSObjectFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mUserDefinedRPSObjects.find(name);
 		if (it != mUserDefinedRPSObjects.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsUserDefinedRPSObjectFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateUserDefinedRPSObjectCallback>& CrpsUserDefinedRPSObjectFactory::GetObjectNamesMap()
 	{
 		return mUserDefinedRPSObjects;
 	}


 	std::map<const std::string, std::string> & CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsUserDefinedRPSObjectFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsUserDefinedRPSObjectFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsUserDefinedRPSObjectFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsCumulativeProbabilityDistributionFactory::CallbackMap CrpsCumulativeProbabilityDistributionFactory::mCumulativeProbabilityDistributions;
 	std::vector<std::string> CrpsCumulativeProbabilityDistributionFactory::mCumulativeProbabilityDistributionNames;
 	QString CrpsCumulativeProbabilityDistributionFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsCumulativeProbabilityDistributionFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsCumulativeProbabilityDistributionFactory::mProducerMap;
    std::map<const std::string, bool> CrpsCumulativeProbabilityDistributionFactory::mStationarityMap;

    CrpsCumulativeProbabilityDistributionFactory::CrpsCumulativeProbabilityDistributionFactory() {}
    CrpsCumulativeProbabilityDistributionFactory::~CrpsCumulativeProbabilityDistributionFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsCumulativeProbabilityDistributionFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsCumulativeProbabilityDistributionFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsCumulativeProbabilityDistributionFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsCumulativeProbabilityDistributionFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateCumulativeProbabilityDistributionCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mCumulativeProbabilityDistributions[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsCumulativeProbabilityDistributionFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mCumulativeProbabilityDistributions.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLCumulativeProbabilityDistribution *CrpsCumulativeProbabilityDistributionFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mCumulativeProbabilityDistributions.find(name);
 		if (it != mCumulativeProbabilityDistributions.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsCumulativeProbabilityDistributionFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateCumulativeProbabilityDistributionCallback>& CrpsCumulativeProbabilityDistributionFactory::GetObjectNamesMap()
 	{
 		return mCumulativeProbabilityDistributions;
 	}

 	std::map<const std::string, std::string> & CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	
 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsCumulativeProbabilityDistributionFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsCumulativeProbabilityDistributionFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsCumulativeProbabilityDistributionFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }
	
 	CrpsKurtosisFactory::CallbackMap CrpsKurtosisFactory::mKurtosiss;
 	std::vector<std::string> CrpsKurtosisFactory::mKurtosisNames;
 	QString CrpsKurtosisFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsKurtosisFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsKurtosisFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsKurtosisFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsKurtosisFactory::mProducerMap;
    std::map<const std::string, bool> CrpsKurtosisFactory::mStationarityMap;

    CrpsKurtosisFactory::CrpsKurtosisFactory() {}
    CrpsKurtosisFactory::~CrpsKurtosisFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsKurtosisFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsKurtosisFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsKurtosisFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsKurtosisFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateKurtosisCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mKurtosiss[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsKurtosisFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mKurtosiss.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLKurtosis *CrpsKurtosisFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mKurtosiss.find(name);
 		if (it != mKurtosiss.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsKurtosisFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateKurtosisCallback>& CrpsKurtosisFactory::GetObjectNamesMap()
 	{
 		return mKurtosiss;
 	}

 	std::map<const std::string, std::string> & CrpsKurtosisFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsKurtosisFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsKurtosisFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsKurtosisFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }
	
 	CrpsPeakFactorFactory::CallbackMap CrpsPeakFactorFactory::mPeakFactors;
 	std::vector<std::string> CrpsPeakFactorFactory::mPeakFactorNames;
 	QString CrpsPeakFactorFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsPeakFactorFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsPeakFactorFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsPeakFactorFactory::mProducerMap;
    std::map<const std::string, bool> CrpsPeakFactorFactory::mStationarityMap;

    CrpsPeakFactorFactory::CrpsPeakFactorFactory() {}
    CrpsPeakFactorFactory::~CrpsPeakFactorFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsPeakFactorFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsPeakFactorFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsPeakFactorFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsPeakFactorFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreatePeakFactorCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mPeakFactors[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsPeakFactorFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mPeakFactors.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLPeakFactor *CrpsPeakFactorFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mPeakFactors.find(name);
 		if (it != mPeakFactors.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsPeakFactorFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreatePeakFactorCallback>& CrpsPeakFactorFactory::GetObjectNamesMap()
 	{
 		return mPeakFactors;
 	}

 	std::map<const std::string, std::string> & CrpsPeakFactorFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsPeakFactorFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsPeakFactorFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsPeakFactorFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }
	
 	CrpsProbabilityDensityFunctionFactory::CallbackMap CrpsProbabilityDensityFunctionFactory::mProbabilityDensityFunctions;
 	std::vector<std::string> CrpsProbabilityDensityFunctionFactory::mProbabilityDensityFunctionNames;
 	QString CrpsProbabilityDensityFunctionFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsProbabilityDensityFunctionFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsProbabilityDensityFunctionFactory::mProducerMap;
    std::map<const std::string, bool> CrpsProbabilityDensityFunctionFactory::mStationarityMap;

    CrpsProbabilityDensityFunctionFactory::CrpsProbabilityDensityFunctionFactory() {}
    CrpsProbabilityDensityFunctionFactory::~CrpsProbabilityDensityFunctionFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsProbabilityDensityFunctionFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsProbabilityDensityFunctionFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsProbabilityDensityFunctionFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsProbabilityDensityFunctionFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateProbabilityDensityFunctionCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mProbabilityDensityFunctions[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsProbabilityDensityFunctionFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mProbabilityDensityFunctions.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLProbabilityDensityFunction *CrpsProbabilityDensityFunctionFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mProbabilityDensityFunctions.find(name);
 		if (it != mProbabilityDensityFunctions.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsProbabilityDensityFunctionFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));


        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateProbabilityDensityFunctionCallback>& CrpsProbabilityDensityFunctionFactory::GetObjectNamesMap()
 	{
 		return mProbabilityDensityFunctions;
 	}

 	std::map<const std::string, std::string> & CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	
 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsProbabilityDensityFunctionFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsProbabilityDensityFunctionFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsProbabilityDensityFunctionFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsShearVelocityOfFlowFactory::CallbackMap CrpsShearVelocityOfFlowFactory::mShearVelocityOfFlows;
 	std::vector<std::string> CrpsShearVelocityOfFlowFactory::mShearVelocityOfFlowNames;
 	QString CrpsShearVelocityOfFlowFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsShearVelocityOfFlowFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsShearVelocityOfFlowFactory::mProducerMap;
    std::map<const std::string, bool> CrpsShearVelocityOfFlowFactory::mStationarityMap;

    CrpsShearVelocityOfFlowFactory::CrpsShearVelocityOfFlowFactory() {}
    CrpsShearVelocityOfFlowFactory::~CrpsShearVelocityOfFlowFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsShearVelocityOfFlowFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsShearVelocityOfFlowFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsShearVelocityOfFlowFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsShearVelocityOfFlowFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateShearVelocityOfFlowCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mShearVelocityOfFlows[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsShearVelocityOfFlowFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mShearVelocityOfFlows.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLShearVelocityOfFlow *CrpsShearVelocityOfFlowFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mShearVelocityOfFlows.find(name);
 		if (it != mShearVelocityOfFlows.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsShearVelocityOfFlowFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateShearVelocityOfFlowCallback>& CrpsShearVelocityOfFlowFactory::GetObjectNamesMap()
 	{
 		return mShearVelocityOfFlows;
 	}

 	std::map<const std::string, std::string> & CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsShearVelocityOfFlowFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsShearVelocityOfFlowFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsShearVelocityOfFlowFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }
	

 	CrpsSkewnessFactory::CallbackMap CrpsSkewnessFactory::mSkewnesss;
 	std::vector<std::string> CrpsSkewnessFactory::mSkewnessNames;
 	QString CrpsSkewnessFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsSkewnessFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsSkewnessFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsSkewnessFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsSkewnessFactory::mProducerMap;
    std::map<const std::string, bool> CrpsSkewnessFactory::mStationarityMap;

    CrpsSkewnessFactory::CrpsSkewnessFactory() {}
    CrpsSkewnessFactory::~CrpsSkewnessFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsSkewnessFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsSkewnessFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsSkewnessFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsSkewnessFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSkewnessCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mSkewnesss[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsSkewnessFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mSkewnesss.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLSkewness *CrpsSkewnessFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mSkewnesss.find(name);
 		if (it != mSkewnesss.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsSkewnessFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateSkewnessCallback>& CrpsSkewnessFactory::GetObjectNamesMap()
 	{
 		return mSkewnesss;
 	}

 	std::map<const std::string, std::string> & CrpsSkewnessFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsSkewnessFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsSkewnessFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsSkewnessFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

	
 	CrpsStandardDeviationFactory::CallbackMap CrpsStandardDeviationFactory::mStandardDeviations;
 	std::vector<std::string> CrpsStandardDeviationFactory::mStandardDeviationNames;
 	QString CrpsStandardDeviationFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsStandardDeviationFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsStandardDeviationFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsStandardDeviationFactory::mProducerMap;
    std::map<const std::string, bool> CrpsStandardDeviationFactory::mStationarityMap;

    CrpsStandardDeviationFactory::CrpsStandardDeviationFactory() {}
    CrpsStandardDeviationFactory::~CrpsStandardDeviationFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsStandardDeviationFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsStandardDeviationFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsStandardDeviationFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsStandardDeviationFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateStandardDeviationCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mStandardDeviations[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsStandardDeviationFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mStandardDeviations.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLStandardDeviation *CrpsStandardDeviationFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mStandardDeviations.find(name);
 		if (it != mStandardDeviations.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsStandardDeviationFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateStandardDeviationCallback>& CrpsStandardDeviationFactory::GetObjectNamesMap()
 	{
 		return mStandardDeviations;
 	}

 	std::map<const std::string, std::string> & CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsStandardDeviationFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsStandardDeviationFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsStandardDeviationFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

 	CrpsVarianceFactory::CallbackMap CrpsVarianceFactory::mVariances;
 	std::vector<std::string> CrpsVarianceFactory::mVarianceNames;
 	QString CrpsVarianceFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsVarianceFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsVarianceFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsVarianceFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsVarianceFactory::mProducerMap;
    std::map<const std::string, bool> CrpsVarianceFactory::mStationarityMap;

    CrpsVarianceFactory::CrpsVarianceFactory() {}
    CrpsVarianceFactory::~CrpsVarianceFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsVarianceFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsVarianceFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsVarianceFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsVarianceFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateVarianceCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mVariances[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsVarianceFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mVariances.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLVariance *CrpsVarianceFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mVariances.find(name);
 		if (it != mVariances.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsVarianceFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateVarianceCallback>& CrpsVarianceFactory::GetObjectNamesMap()
 	{
 		return mVariances;
 	}

 	std::map<const std::string, std::string> & CrpsVarianceFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsVarianceFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsVarianceFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsVarianceFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }


 	CrpsWavePassageEffectFactory::CallbackMap CrpsWavePassageEffectFactory::mWavePassageEffects;
 	std::vector<std::string> CrpsWavePassageEffectFactory::mWavePassageEffectNames;
 	QString CrpsWavePassageEffectFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mOjectAndPluginMap;
     std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsWavePassageEffectFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsWavePassageEffectFactory::mProducerMap;
    std::map<const std::string, bool> CrpsWavePassageEffectFactory::mStationarityMap;

    CrpsWavePassageEffectFactory::CrpsWavePassageEffectFactory() {}
    CrpsWavePassageEffectFactory::~CrpsWavePassageEffectFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }

 	QString CrpsWavePassageEffectFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsWavePassageEffectFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}
	
 	void CrpsWavePassageEffectFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{		
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;
 	}

 	void CrpsWavePassageEffectFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateWavePassageEffectCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}
 		mWavePassageEffects[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;
		
 	}

 	void CrpsWavePassageEffectFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mWavePassageEffects.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}

 	}

 	IrpsSeLWavePassageEffect *CrpsWavePassageEffectFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mWavePassageEffects.find(name);
 		if (it != mWavePassageEffects.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

    PyObject* CrpsWavePassageEffectFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
     {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
     }

     std::map<const std::string, CreateWavePassageEffectCallback>& CrpsWavePassageEffectFactory::GetObjectNamesMap()
 	{
 		return mWavePassageEffects;
 	}

 	std::map<const std::string, std::string> & CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsWavePassageEffectFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

     std::map<const std::string, std::string> &  CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap()
     {
 	    return mOjectsSkipDuringUnintallationMap;
     }

     std::map<const std::string, PyObject*>& CrpsWavePassageEffectFactory::GetProducerMap()
     {
        return mProducerMap;
     }
     std::map<const std::string, bool>& CrpsWavePassageEffectFactory::GetStationarityMap()
     {
        return mStationarityMap;
     }

// frequency spectrum
 	CrpsFrequencySpectrumFactory::CallbackMap CrpsFrequencySpectrumFactory::mFrequencySpectrums;
 	QString CrpsFrequencySpectrumFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mOjectAndPluginMap;
    std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsFrequencySpectrumFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsFrequencySpectrumFactory::mProducerMap;
    std::map<const std::string, bool> CrpsFrequencySpectrumFactory::mStationarityMap;

    CrpsFrequencySpectrumFactory::CrpsFrequencySpectrumFactory() {}
    CrpsFrequencySpectrumFactory::~CrpsFrequencySpectrumFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }


 	QString CrpsFrequencySpectrumFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsFrequencySpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsFrequencySpectrumFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;

 	}

 	void CrpsFrequencySpectrumFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateFrequencySpectrumCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mFrequencySpectrums[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;

 	}

 	void CrpsFrequencySpectrumFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mFrequencySpectrums.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLFrequencySpectrum *CrpsFrequencySpectrumFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mFrequencySpectrums.find(name);
 		if (it != mFrequencySpectrums.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

     PyObject* CrpsFrequencySpectrumFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
    }

 	std::map<const std::string, CreateFrequencySpectrumCallback>& CrpsFrequencySpectrumFactory::GetObjectNamesMap()
 	{
 		return mFrequencySpectrums;
 	}

 	std::map<const std::string, std::string> & CrpsFrequencySpectrumFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsFrequencySpectrumFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsFrequencySpectrumFactory::GetOjectsSkipDuringUnintallationMap()
    {
 	    return mOjectsSkipDuringUnintallationMap;
    }

    std::map<const std::string, PyObject*>& CrpsFrequencySpectrumFactory::GetProducerMap()
    {
        return mProducerMap;
    }

    std::map<const std::string, bool>& CrpsFrequencySpectrumFactory::GetStationarityMap()
    {
        return mStationarityMap;
    }

// directional spectrum
 	CrpsDirectionalSpectrumFactory::CallbackMap CrpsDirectionalSpectrumFactory::mDirectionalSpectrums;
 	QString CrpsDirectionalSpectrumFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mOjectAndPluginMap;
    std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpectrumFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsDirectionalSpectrumFactory::mProducerMap;
    std::map<const std::string, bool> CrpsDirectionalSpectrumFactory::mStationarityMap;

    CrpsDirectionalSpectrumFactory::CrpsDirectionalSpectrumFactory() {}
    CrpsDirectionalSpectrumFactory::~CrpsDirectionalSpectrumFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }


 	QString CrpsDirectionalSpectrumFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsDirectionalSpectrumFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsDirectionalSpectrumFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;

 	}

 	void CrpsDirectionalSpectrumFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateDirectionalSpectrumCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mDirectionalSpectrums[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;

 	}

 	void CrpsDirectionalSpectrumFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mDirectionalSpectrums.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLDirectionalSpectrum *CrpsDirectionalSpectrumFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mDirectionalSpectrums.find(name);
 		if (it != mDirectionalSpectrums.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

     PyObject* CrpsDirectionalSpectrumFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
    }

 	std::map<const std::string, CreateDirectionalSpectrumCallback>& CrpsDirectionalSpectrumFactory::GetObjectNamesMap()
 	{
 		return mDirectionalSpectrums;
 	}

 	std::map<const std::string, std::string> & CrpsDirectionalSpectrumFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpectrumFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsDirectionalSpectrumFactory::GetOjectsSkipDuringUnintallationMap()
    {
 	    return mOjectsSkipDuringUnintallationMap;
    }

    std::map<const std::string, PyObject*>& CrpsDirectionalSpectrumFactory::GetProducerMap()
    {
        return mProducerMap;
    }

    std::map<const std::string, bool>& CrpsDirectionalSpectrumFactory::GetStationarityMap()
    {
        return mStationarityMap;
    }

// directional spreading function
 	CrpsDirectionalSpreadingFunctionFactory::CallbackMap CrpsDirectionalSpreadingFunctionFactory::mDirectionalSpreadingFunctions;
 	QString CrpsDirectionalSpreadingFunctionFactory::mOwnerPlugin;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mTobeInstalledObjectsMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mOjectDescriptionMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mOjectAndPluginMap;
    std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mOjectsSkipDuringUnintallationMap;

 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mTitleMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mLinkMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mAuthorMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mDateMap;
 	std::map<const std::string, std::string> CrpsDirectionalSpreadingFunctionFactory::mVersionMap;
    std::map<const std::string, PyObject*> CrpsDirectionalSpreadingFunctionFactory::mProducerMap;
    std::map<const std::string, bool> CrpsDirectionalSpreadingFunctionFactory::mStationarityMap;

    CrpsDirectionalSpreadingFunctionFactory::CrpsDirectionalSpreadingFunctionFactory() {}
    CrpsDirectionalSpreadingFunctionFactory::~CrpsDirectionalSpreadingFunctionFactory()
    {
        Base::PyGILStateLocker lock;
        for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
             it != mProducerMap.end(); ++it) {

            Py_DECREF(it->second);
        }
    }


 	QString CrpsDirectionalSpreadingFunctionFactory::GetOwnerPlugin()
 	{
 		return mOwnerPlugin;
 	}

 	void CrpsDirectionalSpreadingFunctionFactory::SetOwnerPlugin(QString ownerPlugin)
 	{
 		mOwnerPlugin = ownerPlugin;
 	}

 	void CrpsDirectionalSpreadingFunctionFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
 	{
 		mTobeInstalledObjectsMap[name] = pluginName;
 		mTitleMap[name] = publicationTitle;
 		mLinkMap[name] = publicationLink;
 		mAuthorMap[name] = publicationAuthor;
 		mDateMap[name] = publicationDate;
 		mVersionMap[name] = version;
        mStationarityMap[name] = stationarity;

 	}

 	void CrpsDirectionalSpreadingFunctionFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateDirectionalSpreadingFunctionCallback cb)
 	{
 		if (mTobeInstalledObjectsMap[name] != pluginName)
 		{
 			return;
 		}

 		mDirectionalSpreadingFunctions[name] = cb;
 		mOjectDescriptionMap[name] = description;
 		mOjectAndPluginMap[name] = pluginName;

 	}

 	void CrpsDirectionalSpreadingFunctionFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
 	{
 		if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
 		{
 			mDirectionalSpreadingFunctions.erase(name);
 			mOjectDescriptionMap.erase(name);
 			mOjectAndPluginMap.erase(name);

 		}
		
 	}

 	IrpsSeLDirectionalSpreadingFunction *CrpsDirectionalSpreadingFunctionFactory::BuildObject(const std::string& name)
 	{
 		CallbackMap::iterator it = mDirectionalSpreadingFunctions.find(name);
 		if (it != mDirectionalSpreadingFunctions.end())
 		{
 			return (it->second)();
 		}

 		return NULL;
 	}

     PyObject* CrpsDirectionalSpreadingFunctionFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
    {
        PyObject* producer = mProducerMap[pluggedFeatureName];

        Py::Callable method(producer);
        Py::Tuple args(2);
        args.setItem(0, Py::String(newFeatureName));
        args.setItem(1, Py::String(simulationName));

        Py::Object res = method.apply(args);
        return Py::new_reference_to(res);
    }

 	std::map<const std::string, CreateDirectionalSpreadingFunctionCallback>& CrpsDirectionalSpreadingFunctionFactory::GetObjectNamesMap()
 	{
 		return mDirectionalSpreadingFunctions;
 	}

 	std::map<const std::string, std::string> & CrpsDirectionalSpreadingFunctionFactory::GetTobeInstalledObjectsMap()
 	{
 		return mTobeInstalledObjectsMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetOjectDescriptionMap()
 	{
 		return mOjectDescriptionMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetOjectAndPluginMap()
 	{
 		return mOjectAndPluginMap;
 	}

 	///
 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetTitleMap()
 	{
 		return mTitleMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetLinkMap()
 	{
 		return mLinkMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetAuthorMap()
 	{
 		return mAuthorMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetDateMap()
 	{
 		return mDateMap;
 	}

 	std::map<const std::string, std::string>& CrpsDirectionalSpreadingFunctionFactory::GetVersionMap()
 	{
 		return mVersionMap;
 	}

 	std::map<const std::string, std::string> &  CrpsDirectionalSpreadingFunctionFactory::GetOjectsSkipDuringUnintallationMap()
    {
 	    return mOjectsSkipDuringUnintallationMap;
    }

    std::map<const std::string, PyObject*>& CrpsDirectionalSpreadingFunctionFactory::GetProducerMap()
    {
        return mProducerMap;
    }

    std::map<const std::string, bool>& CrpsDirectionalSpreadingFunctionFactory::GetStationarityMap()
    {
        return mStationarityMap;
    }