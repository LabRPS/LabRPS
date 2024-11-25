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

#include "QbladeMethods.h"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Base/Console.h>
#include "WindField.h"

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::QbladeMethods, WindLabAPI::WindLabFeatureSimulationMethod)

QbladeMethods::QbladeMethods() {

     ADD_PROPERTY_TYPE(RandomPhaseSeed, (1000000), "Grid Parameter", App::Prop_None, "Random Seed");
     ADD_PROPERTY_TYPE(SimulationTime, (60), "Grid Parameter", App::Prop_None, "The simulation time");
     ADD_PROPERTY_TYPE(TimeStepSize, (0.1), "Grid Parameter", App::Prop_None, "Time discretization step size");
     ADD_PROPERTY_TYPE(GridWidth, (200000.0), "Grid Parameter", App::Prop_None, "The grid width");
     ADD_PROPERTY_TYPE(GridPointsNumber, (20), "Grid Parameter", App::Prop_None, "Grid points along the Y axis");
     ADD_PROPERTY_TYPE(HubHeight, (300000), "Grid Parameter", App::Prop_None, "The hub height");
     ADD_PROPERTY_TYPE(MeanWindSpeed, (13000), "Flow Parameter", App::Prop_None, "The mean wind speed");
    /* ADD_PROPERTY_TYPE(HorizontalInFlow, (0), "Flow Parameter", App::Prop_None, "Horizontal in flow");
     ADD_PROPERTY_TYPE(VerticalInFlow, (0), "Flow Parameter", App::Prop_None, "Vertical in flow");*/

    /* ADD_PROPERTY_TYPE(IECStandard, ((long int)1), "Flow Parameter", App::Prop_None, "ICE 61400-1Ed");
     static const char* IECStandards[] = {"61400-1Ed2", "61400-1Ed3", "61400-2", "61400-3", nullptr };
     IECStandard.setEnums(IECStandards);
    
     ADD_PROPERTY_TYPE(WindModel, ((long int)0), "Flow Parameter", App::Prop_None, "ICE 61400-1Ed");
     static const char* windModels[] = {"NTM", "ETM", "EWM1", "EWM50", nullptr };
     WindModel.setEnums(windModels);

     ADD_PROPERTY_TYPE(SpectralModel, ((long int)0), "Flow Parameter", App::Prop_None, "ICE 61400-1Ed");
     static const char* spectralModels[] = {"IECKAI", "IECVKM", "GP_LLJ", "NWTCUP", "SMOOTH", "WF_UPW" "WF_07D", "WF_14D", "TIDAL", "NONE", nullptr };
     SpectralModel.setEnums(spectralModels);

     ADD_PROPERTY_TYPE(DefaultProfileAndShear, (true), "Flow Parameter", App::Prop_None, "Default wind profile and shear");*/

     ADD_PROPERTY_TYPE(ProfileModel, ((long int)0), "Flow Parameter", App::Prop_None, "Wind profile Type");
     static const char* profileModels[] = {"PL", "LOG", "H2L", "JET", "IEC", nullptr };
     ProfileModel.setEnums(profileModels);

     ADD_PROPERTY_TYPE(ReferenceHeight, (110000), "Flow Parameter", App::Prop_None, "Reference height");
     ADD_PROPERTY_TYPE(ShearExponent, (0.2), "Flow Parameter", App::Prop_None, "Shear exponent");
     ADD_PROPERTY_TYPE(RoughnessLength, (0.01), "Flow Parameter", App::Prop_None, "Roughness length");
     //ADD_PROPERTY_TYPE(JetHeight, (100000), "Flow Parameter", App::Prop_None, "Jet height");
     //ADD_PROPERTY_TYPE(EtmcValue, (2000), "Flow Parameter", App::Prop_None, "ETMc value");

     //ADD_PROPERTY_TYPE(TurbineClass, ((long int)0), "Wind Turbine Class Parameter", App::Prop_None, "Turbine class");
     //static const char* turbineClasses[] = {"I", "II", "III", "S", nullptr};
     //TurbineClass.setEnums(turbineClasses);

     //ADD_PROPERTY_TYPE(TurbulenceClass, ((long int)0), "Wind Turbine Class Parameter", App::Prop_None, "Turbulence class");
     //static const char* turbulenceClasses[] = {"A", "B", "C", "S", nullptr};
     //TurbulenceClass.setEnums(turbulenceClasses);

     ADD_PROPERTY_TYPE(TurbulenceIntensity, (16), "Wind Turbine Class Parameter", App::Prop_None, "Turbulence intensity");
     //ADD_PROPERTY_TYPE(VRef, (50), "Wind Turbine Class Parameter", App::Prop_None, "V reference");

     ADD_PROPERTY_TYPE(RequestedVariable, ((long int)0), "Computed Variable", App::Prop_None, "Parameter");
     static const char* requestedVariables[] = {"Hub Height Velocity Abs", "Hub Height X Velocity", "Hub Height Y Velocity", "Hub Height Z Velocity", nullptr};
     RequestedVariable.setEnums(requestedVariables);

     ADD_PROPERTY_TYPE(FieldRadius, (190000), "Flow Parameter", App::Prop_None, "The radius of the field");

     ADD_PROPERTY_TYPE(GridPoints, (Base::Vector3d()), "Grid Parameter", App::Prop_None,"The list of grid points");
     ADD_PROPERTY_TYPE(Probes, (Base::Vector3d()), "Grid Parameter", App::Prop_None,"The list of probes");

}

void QbladeMethods::onChanged(const App::Property* prop)
{
    return WindLabAPI::WindLabFeatureSimulationMethod::onChanged(prop);
}

bool QbladeMethods::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    return true;
}

bool QbladeMethods::Simulate(const WindLabAPI::WindLabSimulationData& Data, mat& dVelocityArray) {

     WindField* windField = new WindField(Data, 
        RandomPhaseSeed, SimulationTime,
        TimeStepSize, GridWidth,
        GridPointsNumber, HubHeight,
        MeanWindSpeed,
        ProfileModel, ReferenceHeight,
        ShearExponent, RoughnessLength, 
        TurbulenceIntensity, FieldRadius, false);


         int cols = min(dVelocityArray.cols(), windField->m_pointsPerSideY * windField->m_pointsPerSideZ);
         int rows = min(dVelocityArray.rows(), windField->m_numberOfTimesteps);

         if (dVelocityArray.cols() != 1 + windField->m_pointsPerSideY * windField->m_pointsPerSideZ)
         {
             Base::Console().Warning("Sorry, the computation have not been started. The number spatial locations (grid points) in your simulation must be equal to the number of points on Y axis time the number of points on Z axis.\n");
             return false;
         }

          windField->calculateWindField();

          const std::vector<Base::Vector3d> probes = Probes.getValues();

         if (RequestedVariable.getValue() == 0)
         {
             
         double time = 0.0;
         int p = 0;
         std::vector<Base::Vector3d> thePoints;
         // if probes are not specified, show wind speed at all grid points
         if (Probes.getSize() <= 0) {

             for (int i = 0; i < windField->m_pointsPerSideY; i++) {

                for (int k = 0; k < windField->m_pointsPerSideZ; k++) {
                    p = (k * windField->m_pointsPerSideY) + i;
                    thePoints.push_back(Base::Vector3d(0, windField->m_yCoordinatesNormalized[i], windField->m_zCoordinatesNormalized[k]));
                    for (int j = 0; j < rows; j++) {
                        time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                        dVelocityArray(j, p + 1) = windField->getWindspeed(Vec3(0, windField->m_yCoordinatesNormalized[i], windField->m_zCoordinatesNormalized[k]), time,false,false,0.0).x;
                    }
                }

            }
             GridPoints.setValues(thePoints);
         
         }
         else//otherwise show wind speed at probes
         {
             for (int k = 0; k < Probes.getSize(); k++) {
                    for (int j = 0; j < rows; j++) {
                        time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
                        dVelocityArray(j, k + 1) = windField->getWindspeed(Vec3(Probes.getValues()[k].x, Probes.getValues()[k].y, Probes.getValues()[k].z), time,false,false,0.0).x;
                    }
             }
         }

            for (int j = 0; j < rows; j++) {
                  dVelocityArray(j, 0) = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + j * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second); 
              }
         }

          if (dVelocityArray.rows() < windField->m_numberOfTimesteps) {
             Base::Console().Warning(
                 "The entire result data couldn't be reported. Please make sure the number of time increments is %d.\n", windField->m_numberOfTimesteps);
         }

              

        
   return true;
}

// The simulation function in large scale mode
bool QbladeMethods::SimulateInLargeScaleMode(const WindLabAPI::WindLabSimulationData& Data, QString &strFileName)
{
    return true;
}
