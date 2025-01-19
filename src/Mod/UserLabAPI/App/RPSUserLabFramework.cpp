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
#include "RPSUserLabFramework.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <fstream>				
#include <Mod/UserLabAPI/App/RPSUserLabAPI.h>
#include <App/Application.h>
#include <App/Document.h>

using namespace std;
using namespace UserLabAPI;

CRPSUserLabFramework::CRPSUserLabFramework()
{
}

CRPSUserLabFramework::~CRPSUserLabFramework()
{
}

UserLabAPI::UserLabFeatureDescription* CRPSUserLabFramework::getUserLabFeatureDescription(const std::string& name)
{
     auto doc = App::GetApplication().getActiveDocument();

     if (!doc)
     {
         return nullptr;
     }

     UserLabAPI::UserLabFeature* feature = static_cast<UserLabAPI::UserLabFeature*>(doc->getObject(name.c_str()));

     if (!feature)
     {
         return nullptr;
     }

     UserLabAPI::UserLabFeatureDescription* information = new UserLabAPI::UserLabFeatureDescription();

     information->PluginName.setValue(feature->PluginName.getValue());
     information->PublicationTitle.setValue(feature->PublicationTopic.getValue());
     information->PublicationLink.setValue(feature->LinkToPublication.getValue());
     information->PublicationAuthor.setValue(feature->PublicationAuthor.getValue());
     information->PublicationDate.setValue(feature->PublicationDate.getValue());
     information->ReleaseDate.setValue(feature->ReleaseDate.getValue());
     information->Version.setValue(feature->Version.getValue());
     information->Author.setValue(feature->Author.getValue());
     information->APIVersion.setValue(feature->APIVersion.getValue());
     information->PluginVersion.setValue(feature->PluginVersion.getValue());
     information->Stationarity.setValue(feature->IsStationary.getValue());
     information->type.setValue(feature->FeatureType.getValue());
     information->group.setValue(feature->FeatureGroup.getValue());
     information->LabRPSVersion.setValue(feature->LabrpsVersion.getValue());
     information->Description.setValue(feature->Description.getValue());
     information->IsUniformModulationFeature.setValue(feature->IsUniformModulationFeature.getValue());
     information->OutputUnitString.setValue(feature->OutputUnitString.getValue());
     information->ApplicationFields.setValue(feature->ApplicationFields.getValue());
     
	return information;
}

std::string CRPSUserLabFramework::getCurrentDateTime()
{
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure
    std::tm local_time;
    localtime_s(&local_time, &now_time);// Use localtime_s for safety (Windows)

    // Format the date and time into a string using strftime
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &local_time);

    return std::string(buffer);
}