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

#ifndef IRPSSELDIRECTIONALSPECTRUM_H
#define IRPSSELDIRECTIONALSPECTRUM_H

#include "SeaLabSimulationData.h"
#include <Mod/SeaLabAPI/App/SeaLabFeatureDirectionalSpectrum.h>
#include <Base/Vector3D.h>

namespace SeaLabAPI {

class IrpsSeLDirectionalSpectrum : public SeaLabAPI::SeaLabFeatureDirectionalSpectrum
{
public:
    virtual ~IrpsSeLDirectionalSpectrum() {};

    virtual bool ComputeCrossDirectionalSpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, const double &dDirection, std::complex<double> &dValue) = 0;

    virtual bool ComputeCrossDirectionalSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, const double &dDirection, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeCrossDirectionalSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dDirection, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeCrossDirectionalSpectrumVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeCrossDirectionalSpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, const double &dDirection, cx_mat &psdMatrix) = 0;

    virtual bool ComputeAutoDirectionalSpectrumValue(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, const double &dDirection, double &dValue) = 0;
    
    virtual bool ComputeAutoDirectionalSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &location, const double &dTime, const double &dDirection, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeAutoDirectionalSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, const double &dDirection, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeAutoDirectionalSpectrumVectorD(const SeaLabAPI::SeaLabSimulationData& Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

	virtual bool OnInitialSetting(const SeaLabSimulationData &Data) = 0;

};

} //namespace SeaLabAPI

#endif  // IRPSSELDIRECTIONALSPECTRUM_H
