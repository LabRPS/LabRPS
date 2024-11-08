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
#include "VlachosEtAl.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
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

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::VlachosEtAl, SeismicLabAPI::SeismicLabFeatureSimulationMethod)

VlachosEtAl::VlachosEtAl() {

    ADD_PROPERTY_TYPE(MomentMagnitude, (6.5), "Parameter", App::Prop_None, "Moment magnitude of earthquake");
    ADD_PROPERTY_TYPE(RuptureDistance, (30000000.0), "Parameter", App::Prop_None, "Closest distance from the site to the fault rupture");
    ADD_PROPERTY_TYPE(ShearVelocity30, (500000.0), "Parameter", App::Prop_None, "Soil shear wave velocity averaged over top 30 meters");
    ADD_PROPERTY_TYPE(Orientation, (30.0), "Parameter", App::Prop_None, "Orientation of acceleration relative to global coordinates. Represents counter-clockwise angle away from x-axis rotating around z-axis in right-handed coordinate system");
    ADD_PROPERTY_TYPE(SimulationNumber, (2), "Parameter", App::Prop_None, "Number of simulated ground motion time histories that should be generated per evolutionary power");
    ADD_PROPERTY_TYPE(SpectraNumber, (2), "Parameter", App::Prop_None, "Number of evolutionary power spectra that should be generated");
    ADD_PROPERTY_TYPE(SeedNumber, (10), "Parameter", App::Prop_None, "Value to seed random variables with to ensure repeatability");
    ADD_PROPERTY_TYPE(EventIndex, (0), "Output Parameter", App::Prop_None, "The index of the event whose time history should be shown");
    ADD_PROPERTY_TYPE(EventName, ("my event"), "Parameter", App::Prop_None, "Name to assign to event");

}

void VlachosEtAl::onChanged(const App::Property* prop)
{
    if (prop == &EventIndex) {
        int indexTot = SimulationNumber.getValue() * SpectraNumber.getValue();
        if (EventIndex.getValue() < 0) {
            EventIndex.setValue(0);
        }
        else if (EventIndex.getValue() > indexTot) {
            EventIndex.setValue(indexTot);
        }
    }
}

bool VlachosEtAl::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    return true;
}

bool VlachosEtAl::Simulate(const SeismicLabAPI::SeismicLabSimulationData& Data, mat& dVelocityArray)
{
    // Initialize the factories
    config::initialize();

  double moment_magnitude = MomentMagnitude.getValue();
  double rupture_dist = RuptureDistance.getQuantityValue().getValueAs(Base::Quantity::KiloMetre);
  double vs30 = ShearVelocity30.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond);
  double orientation = Orientation.getQuantityValue().getValueAs(Base::Quantity::Degree);
  unsigned int num_sims = SimulationNumber.getValue();
  unsigned int num_spectra = SpectraNumber.getValue();
  int seed = SeedNumber.getValue();
  int eventIndex = EventIndex.getValue();
  std::string eventName = EventName.getValue();

    auto test_model_factory = Factory<stochastic::StochasticModel, double, double, double, double,
                     unsigned int, unsigned int, int>::instance()
                     ->create("VlachosSiteSpecificEQ", std::move(moment_magnitude),
                     std::move(rupture_dist), std::move(vs30),
                     std::move(orientation), std::move(num_spectra),
                     std::move(num_sims), std::move(seed));

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
bool VlachosEtAl::SimulateInLargeScaleMode(const SeismicLabAPI::SeismicLabSimulationData& Data, QString &strFileName)
{
    return true;
}
