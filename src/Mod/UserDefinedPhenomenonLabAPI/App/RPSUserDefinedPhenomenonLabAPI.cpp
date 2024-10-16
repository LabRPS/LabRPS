
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
#include "RPSUserDefinedPhenomenonLabAPI.h"
#include <iostream>
#include <CXX/Objects.hxx>
#include <Base/Interpreter.h>
#include <App/Application.h>

using namespace UserDefinedPhenomenonLabAPI;

 typedef IrpsULSimulationMethod *(*CreateSimulationMethodCallback)();
 
const char * RPSUserDefinedPhenomenonLabAPIInfo::getUserDefinedPhenomenonLabAPIVersion()
{
	return "0.1";
}

CrpsSimulationMethodFactory::CallbackMap CrpsSimulationMethodFactory::mSimulationMethods;
QString CrpsSimulationMethodFactory::mOwnerPlugin;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mTobeInstalledObjectsMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mOjectDescriptionMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mOjectAndPluginMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mOjectsSkipDuringUnintallationMap;

std::map<const std::string, std::string> CrpsSimulationMethodFactory::mTitleMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mLinkMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mAuthorMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mDateMap;
std::map<const std::string, std::string> CrpsSimulationMethodFactory::mVersionMap;
std::map<const std::string, PyObject*> CrpsSimulationMethodFactory::mProducerMap;
std::map<const std::string, bool> CrpsSimulationMethodFactory::mStationarityMap;

CrpsSimulationMethodFactory::CrpsSimulationMethodFactory() {}
CrpsSimulationMethodFactory::~CrpsSimulationMethodFactory()
{
    Base::PyGILStateLocker lock;
    for (std::map<const std::string, PyObject*>::const_iterator it = mProducerMap.begin();
          it != mProducerMap.end(); ++it) {
          Py_DECREF(it->second);
    }
}

QString CrpsSimulationMethodFactory::GetOwnerPlugin()
{
	return mOwnerPlugin;
}

void CrpsSimulationMethodFactory::SetOwnerPlugin(QString ownerPlugin)
{
	mOwnerPlugin = ownerPlugin;
}

void CrpsSimulationMethodFactory::InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity)
{
	mTobeInstalledObjectsMap[name] = pluginName;
	mTitleMap[name] = publicationTitle;
	mLinkMap[name] = publicationLink;
	mAuthorMap[name] = publicationAuthor;
	mDateMap[name] = publicationDate;
	mVersionMap[name] = version;
    mStationarityMap[name] = stationarity;
}

void CrpsSimulationMethodFactory::RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSimulationMethodCallback cb)
{
	if (mTobeInstalledObjectsMap[name] != pluginName)
	{
		return;
	}

	mSimulationMethods[name] = cb;
	mOjectDescriptionMap[name] = description;
	mOjectAndPluginMap[name] = pluginName;
}

void CrpsSimulationMethodFactory::UnregisterObject(const std::string& name, const std::string& pluginName)
{
	if (pluginName == mOjectAndPluginMap[name] && mOjectsSkipDuringUnintallationMap.find(name) == mOjectsSkipDuringUnintallationMap.end())
	{
		mSimulationMethods.erase(name);
		mOjectDescriptionMap.erase(name);
		mOjectAndPluginMap.erase(name);
	}
	
}

IrpsULSimulationMethod *CrpsSimulationMethodFactory::BuildObject(const std::string& name)
{
	CallbackMap::iterator it = mSimulationMethods.find(name);
	if (it != mSimulationMethods.end())
	{
		return (it->second)();
	}
	return NULL;
}

PyObject* CrpsSimulationMethodFactory::produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName)
{
    PyObject* producer = mProducerMap[pluggedFeatureName];

    Py::Callable method(producer);
    Py::Tuple args(2);
    args.setItem(0, Py::String(newFeatureName));
    args.setItem(1, Py::String(simulationName));

    Py::Object res = method.apply(args);
    return Py::new_reference_to(res);
}

std::map<const std::string, CreateSimulationMethodCallback>& CrpsSimulationMethodFactory::GetObjectNamesMap()
{
	return mSimulationMethods;
}

std::map<const std::string, std::string> & CrpsSimulationMethodFactory::GetTobeInstalledObjectsMap()
{
	return mTobeInstalledObjectsMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetOjectDescriptionMap()
{
	return mOjectDescriptionMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetOjectAndPluginMap()
{
	return mOjectAndPluginMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetTitleMap()
{
	return mTitleMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetLinkMap()
{
	return mLinkMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetAuthorMap()
{
	return mAuthorMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetDateMap()
{
	return mDateMap;
}

std::map<const std::string, std::string>& CrpsSimulationMethodFactory::GetVersionMap()
{
	return mVersionMap;
}

std::map<const std::string, std::string> &  CrpsSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap()
{
    return mOjectsSkipDuringUnintallationMap;
}

std::map<const std::string, PyObject*>& CrpsSimulationMethodFactory::GetProducerMap()
{
    return mProducerMap;
}

std::map<const std::string, bool>& CrpsSimulationMethodFactory::GetStationarityMap()
{
    return mStationarityMap;
}
