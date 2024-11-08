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
#include "DabaghiDerKiureghian.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
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

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::DabaghiDerKiureghian, SeismicLabAPI::SeismicLabFeatureSimulationMethod)

DabaghiDerKiureghian::DabaghiDerKiureghian() {

    ADD_PROPERTY_TYPE(FaultingType, ((long int)0), "Parameter", App::Prop_None, "Type of faulting");
    static const char* faultingTypes[] = {"Strike-slip fault", "Reverse or reverse-oblique fault", nullptr};
    FaultingType.setEnums(faultingTypes);
    
    ADD_PROPERTY_TYPE(SimulationType, ((long int)0), "Parameter", App::Prop_None, "Pulse-type of simulation");
    static const char* simulationTypes[] = {"Pulse-like and non-pulse-like motions", "Only pulse-like", "Only non-pulse-like", nullptr};
    SimulationType.setEnums(simulationTypes);
    
    ADD_PROPERTY_TYPE(MomentMagnitude, (6.5), "Parameter", App::Prop_None, "Moment magnitude of earthquake");
    ADD_PROPERTY_TYPE(DephToRupture, (0.0), "Parameter", App::Prop_None, "Depth to the top of the rupture plane");
    ADD_PROPERTY_TYPE(RuptureDistance, (10000000.0), "Parameter", App::Prop_None, "Closest distance from the site to the fault rupture");
    ADD_PROPERTY_TYPE(ShearVelocity30, (760000.0), "Parameter", App::Prop_None, "Soil shear wave velocity averaged over top 30 meters");
    ADD_PROPERTY_TYPE(DirectivityParameter, (26000000.0), "Parameter", App::Prop_None, "Directivity parameter s or d --input the larger of the two");
    ADD_PROPERTY_TYPE(DirectivityAnge, (0.0), "Parameter", App::Prop_None, "Directivity ange parameter theta or phi --input corresponding value to s or d");
    ADD_PROPERTY_TYPE(SimulationNumber, (2), "Parameter", App::Prop_None, "Number of simulated ground motion time histories that should be generated (number of different model parameter realizations)");
    ADD_PROPERTY_TYPE(RealizationNumber, (2), "Parameter", App::Prop_None, "Number of realizations of non-stationary, modulated, filtered white noise per set of model parameters");
    ADD_PROPERTY_TYPE(Truncate, (true), "Parameter", App::Prop_None, "Boolean indicating whether to truncate and baseline correct synthetic motion");
    ADD_PROPERTY_TYPE(SeedNumber, (10), "Parameter", App::Prop_None, "Value to seed random variables with to ensure repeatability");
    ADD_PROPERTY_TYPE(EventIndex, (0), "Output Parameter", App::Prop_None, "The index of the event whose time history should be shown");
    ADD_PROPERTY_TYPE(EventName, ("my event"), "Parameter", App::Prop_None, "Name to assign to event");

}

void DabaghiDerKiureghian::onChanged(const App::Property* prop)
{
    if (prop == &EventIndex) {
        int indexTot = SimulationNumber.getValue() * RealizationNumber.getValue();
        if (EventIndex.getValue() < 0) {
            EventIndex.setValue(0);
        }
        else if (EventIndex.getValue() > indexTot) {
            EventIndex.setValue(indexTot);
        }
    }
}

bool DabaghiDerKiureghian::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    return true;
}

bool DabaghiDerKiureghian::Simulate(const SeismicLabAPI::SeismicLabSimulationData& Data, mat& dVelocityArray) {
 
  // Initialize the factories
  config::initialize();

  stochastic::FaultType faulting = static_cast<stochastic::FaultType>(FaultingType.getValue());
  stochastic::SimulationType simulation_type = static_cast<stochastic::SimulationType>(SimulationType.getValue());
  double moment_magnitude = MomentMagnitude.getValue();
  double depth_to_rupt = DephToRupture.getQuantityValue().getValueAs(Base::Quantity::KiloMetre);
  double rupture_dist = RuptureDistance.getQuantityValue().getValueAs(Base::Quantity::KiloMetre);
  double vs30 = ShearVelocity30.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond);
  double s_or_d = DirectivityParameter.getQuantityValue().getValueAs(Base::Quantity::KiloMetre);
  double theta_or_phi = DirectivityAnge.getQuantityValue().getValueAs(Base::Quantity::Degree);
  unsigned int num_sims = SimulationNumber.getValue();
  unsigned int num_realizations = RealizationNumber.getValue();
  bool truncate = Truncate.getValue();
  int seed = SeedNumber.getValue();
  int eventIndex = EventIndex.getValue();
  std::string eventName = EventName.getValue();

    auto test_model_factory =
      Factory<stochastic::StochasticModel, stochastic::FaultType, stochastic::SimulationType,  
        double, double, double, double, double, double,unsigned int, unsigned int, bool, int>::instance()
                     ->create("DabaghiDerKiureghianNFGM", std::move(faulting), std::move(simulation_type),
                   std::move(moment_magnitude), std::move(depth_to_rupt), std::move(rupture_dist),
                   std::move(vs30), std::move(s_or_d), std::move(theta_or_phi), std::move(num_sims),
                   std::move(num_realizations), std::move(truncate), std::move(seed));

    auto result = test_model_factory->generate(eventName);
    int num_time_steps = result.get_library_json()["Events"][eventIndex]["numSteps"];
    double dt = result.get_library_json()["Events"][eventIndex]["dT"];
    
    int cols = min(dVelocityArray.cols(), num_sims);
  
    for (int j = 0; j < cols && false == Data.isInterruptionRequested.getValue(); j++)
   {
        auto run_data = result.get_library_json()["Events"][eventIndex]["timeSeries"][j]["data"]
                            .get<std::vector<double>>();
       int rows = min(dVelocityArray.rows(), num_time_steps);
       for (int i = 0; i < rows && false == Data.isInterruptionRequested.getValue(); i++)
       {
         dVelocityArray(i, j + 1) = run_data[i];
         dVelocityArray(i, 0) = dt * i;

       }
   }

   if (dVelocityArray.cols() < num_sims || dVelocityArray.rows() < num_time_steps)
   {
       Base::Console().Warning("The entire result data couldn't be reported. Please make sure the number of spatial location is %d and the number of time increments is %d.\n", num_sims, num_time_steps);
   }

   return true;
}

// The simulation function in large scale mode
bool DabaghiDerKiureghian::SimulateInLargeScaleMode(const SeismicLabAPI::SeismicLabSimulationData& Data, QString &strFileName)
{
    return true;
}
