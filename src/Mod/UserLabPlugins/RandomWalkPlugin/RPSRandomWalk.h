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

#ifndef USERLAB_PLUGIN_SIMUMETHOD_RANDOM_WALK_H
#define USERLAB_PLUGIN_SIMUMETHOD_RANDOM_WALK_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
// JSON for Modern C++ single-include header

#include <Mod/UserLabAPI/App/IrpsULSimulationMethod.h>
#include <App/PropertyUnits.h>

namespace UserLabAPI { class UserLabSimulationData; }

namespace UserLab {

class CRPSRandomWalk: public UserLabAPI::IrpsULSimulationMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(UserLab::CRPSRandomWalk);

public:
	CRPSRandomWalk();

	~CRPSRandomWalk() {};

	bool OnInitialSetting(const UserLabAPI::UserLabSimulationData& Data);

    bool Simulate(const UserLabAPI::UserLabSimulationData& Data, cube &dPhenomenon);

    const char* GetPhenomenonName();

public:

    App::PropertyInteger TotalSteps;
    App::PropertyInteger NumberOfWalker;
    App::PropertyBool MovePattern;
    App::PropertyBool RandomStart;
};

} // namespace UserLab

#endif // #ifndef USERLAB_PLUGIN_SIMUMETHOD_RANDOM_WALK_H

//
//utilities::JsonObject::JsonObject()
//{
//    // This is constructed here to ensure the JSON member is stored as an object
//    json_object_ = json::object();
//}
//
//utilities::JsonObject::JsonObject(json library_json) : JsonObject::JsonObject()
//{
//    json_object_ = library_json;
//}
//
//bool utilities::JsonObject::delete_key(const std::string& key)
//{
//    bool status = true;
//
//    int erased = json_object_.erase(key);
//
//    if (erased != 1) {
//        status = false;
//        throw std::runtime_error(
//            "\nWARNING: In utilities::JsonObject::delete_key: Key not present, so "
//            "no values were erased\n");
//    }
//
//    return status;
//}
//
//bool utilities::JsonObject::write_to_file(const std::string& output_location) const
//{
//    bool status = true;
//    std::ofstream output_file;
//    output_file.open(output_location);
//
//    if (!output_file.is_open()) {
//        status = false;
//        throw std::runtime_error(
//            "\nERROR: In utilities::JsonObject::write_to_file(): Could not open "
//            "output location\n");
//    }
//
//    // Write prettyfied JSON to file
//    output_file << std::setw(4) << json_object_ << std::endl;
//
//    output_file.close();
//
//    if (output_file.fail()) {
//        status = false;
//        throw std::runtime_error("\nERROR: In utilities::JsonObject::write_to_file(): Error when "
//                                 "closing output location\n");
//    }
//
//    return status;
//}
//
//void utilities::JsonObject::clear() { json_object_.clear(); }
//
//bool utilities::JsonObject::is_empty() const { return json_object_.empty(); }
//
//unsigned int utilities::JsonObject::get_size() const { return json_object_.size(); }
