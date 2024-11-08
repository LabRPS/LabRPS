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

#define _USE_MATH_DEFINES
#include "WittigSinhaEqualFloors.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Libraries/smelt/include/wittig_sinha.h>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include <Libraries/smelt/include/dabaghi_der_kiureghian.h>
#include <Libraries/smelt/include/factory.h>
#include <Libraries/smelt/include/configure.h>

#include <unsupported/Eigen/FFT>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::WittigSinhaEqualFloors, WindLabAPI::WindLabFeatureSimulationMethod)

WittigSinhaEqualFloors::WittigSinhaEqualFloors() {

    ADD_PROPERTY_TYPE(ExposureCategory, ((long int)0), "Parameter", App::Prop_None, "Exposure category based on ASCE-7");
    static const char* exposureCategories[] = {"A", "B", "C", "D", nullptr};
    ExposureCategory.setEnums(exposureCategories);

    ADD_PROPERTY_TYPE(GustSpeed, (30000.0), "Parameter", App::Prop_None, "Gust speed of wind");
    ADD_PROPERTY_TYPE(Height, (200000.0), "Parameter", App::Prop_None, "Building height");
    ADD_PROPERTY_TYPE(SeedNumber, (10.0), "Parameter", App::Prop_None, "Value to seed random variables with to ensure repeatability");
    ADD_PROPERTY_TYPE(EventIndex, (0), "Output Parameter", App::Prop_Hidden, "The index of the event whose time history should be shown");
    ADD_PROPERTY_TYPE(EventName, ("my event"), "Parameter", App::Prop_None, "Name to assign to event");
}

void WittigSinhaEqualFloors::onChanged(const App::Property* prop)
{
    if (prop == &EventIndex) {
       
    }
}

bool WittigSinhaEqualFloors::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    return true;
}

bool WittigSinhaEqualFloors::Simulate(const WindLabAPI::WindLabSimuData& Data, mat& dVelocityArray) {
 
  // Initialize the factories
  config::initialize();

  std::string exposure_category = ExposureCategory.getValueAsString();
  double gust_speed = GustSpeed.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond);
  double height = Height.getQuantityValue().getValueAs(Base::Quantity::Metre);
  int seed = 10;
  int eventIndex = EventIndex.getValue();
  unsigned int num_floors = Data.numberOfSpatialPosition.getValue();
  double total_time = Data.numberOfTimeIncrements.getValue();
  std::string eventName = EventName.getValue();

  auto run = Factory<stochastic::StochasticModel, std::string, double, double, unsigned int, double, int>::instance()
                                ->create("WittigSinhaDiscreteFreqWind",
                                 std::move(exposure_category),
                                 std::move(gust_speed), std::move(height),
                                 std::move(num_floors), std::move(total_time), std::move(seed));
  auto time_histories_json = run->generate(eventName);


   for (int j = 0; j < num_floors && false == Data.isInterruptionRequested.getValue(); j++)
   {
       auto run_data = time_histories_json.get_library_json()["Events"][eventIndex]["timeSeries"][j]["data"].get<std::vector<double>>();

       for (int i = 0; i < total_time && false == Data.isInterruptionRequested.getValue(); i++)
       {
         dVelocityArray(i, j + 1) = run_data[i];
       }
   }

   double dt = time_histories_json.get_library_json()["dT"];

   for (int i = 0; i < total_time && false == Data.isInterruptionRequested.getValue(); i++)
   {
     dVelocityArray(i, 0) = dt * i;
   }

   return true;
}

// The simulation function in large scale mode
bool WittigSinhaEqualFloors::SimulateInLargeScaleMode(const WindLabAPI::WindLabSimuData& Data, QString &strFileName)
{
    return true;
}
