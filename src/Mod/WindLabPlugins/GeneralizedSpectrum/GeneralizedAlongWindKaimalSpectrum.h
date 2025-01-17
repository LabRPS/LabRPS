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

#ifndef GENERALIZEDPSD_PLUGIN_KAIMALXPSD_H
#define GENERALIZEDPSD_PLUGIN_KAIMALXPSD_H

#include <Mod/WindLabAPI/App/IrpsWLXSpectrum.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

class CRPSGeneralizedAlongWindKaimalSpectrum : public WindLabAPI::IrpsWLXSpectrum
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSGeneralizedAlongWindKaimalSpectrum);

public:
	CRPSGeneralizedAlongWindKaimalSpectrum();
	
	~CRPSGeneralizedAlongWindKaimalSpectrum() {};

    bool ComputeXCrossSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool ComputeXCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeXCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeXCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix);

    bool ComputeXAutoSpectrumValue(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue);
    
    bool ComputeXAutoSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeXAutoSpectrumVectorT(const WindLabAPI::WindLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

public:
    App::PropertyFloat ParameterA;
    App::PropertyFloat ParameterB;
    App::PropertyFloat ParameterC;
    App::PropertyFloat ParameterD;
    App::PropertyFloat ParameterE;
    App::PropertyFloat ParameterF;
    App::PropertyFloat ParameterG;
    App::PropertyFloat ParameterH;
    App::PropertyFloat ParameterI;
    App::PropertyFloat ParameterJ;
    App::PropertySpeed ShearVelocity;
};

} // namespace App

#endif // GENERALIZEDPSD_PLUGIN_KAIMALXPSD_H