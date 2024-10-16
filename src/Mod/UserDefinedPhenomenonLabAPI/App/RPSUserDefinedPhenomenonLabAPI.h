
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

#ifndef RPSCOREAPI_UL_H
#define RPSCOREAPI_UL_H

#include "RPSUserDefinedPhenomenonLabAPIdefines.h"
#include "IrpsULSimulationMethod.h"

#include <map>
#include<vector>
#include <QString>
#include <App/RPSFeature.h>

namespace UserDefinedPhenomenonLabAPI {

class RPS_CORE_API RPSUserDefinedPhenomenonLabAPIInfo
{
public:

	static const char * getUserDefinedPhenomenonLabAPIVersion();
};

class RPS_CORE_API CrpsSimulationMethodFactory
{
 	public:
    CrpsSimulationMethodFactory();
    ~CrpsSimulationMethodFactory();
 	typedef IrpsULSimulationMethod *(*CreateSimulationMethodCallback)();

 	static void InitializeObject(const std::string& name, const std::string& pluginName, const std::string& publicationTitle, const std::string& publicationLink, const std::string& publicationAuthor, const std::string& publicationDate, const std::string& version, const bool& stationarity);

 	static void RegisterObject(const std::string& name, const std::string& pluginName, const std::string& description, CreateSimulationMethodCallback cb);

 	static void UnregisterObject(const std::string& name, const std::string& pluginName);

 	static IrpsULSimulationMethod * BuildObject(const std::string& name);

    static PyObject* produceFeature(const std::string& newFeatureName, const std::string& simulationName, const std::string& pluggedFeatureName);

 	static std::map<const std::string, CreateSimulationMethodCallback>& GetObjectNamesMap();
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
 	typedef std::map<const std::string, CreateSimulationMethodCallback> CallbackMap;
 	static CallbackMap mSimulationMethods;
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

} //namespace UserDefinedPhenomenonLabAPI

#endif //RPSCOREAPI_UL_H
