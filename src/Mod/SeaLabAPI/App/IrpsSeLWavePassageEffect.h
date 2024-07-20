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

#ifndef IRPSSELWAVEPASSAGEEFFECT_H
#define IRPSSELWAVEPASSAGEEFFECT_H

#include "SeaLabSimulationData.h"
#include <Mod/SeaLabAPI/App/SeaLabFeatureWavePassageEffect.h>
#include <Base/Vector3D.h>

namespace SeaLabAPI {

class IrpsSeLWavePassageEffect : public SeaLabAPI::SeaLabFeatureWavePassageEffect
{
public:

    virtual ~IrpsSeLWavePassageEffect() {};

    virtual bool ComputeWavePassageEffectVectorF(const SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeWavePassageEffectVectorT(const SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeWavePassageEffectMatrixPP(const SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix) = 0;

    virtual bool ComputeWavePassageEffectValue(const SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

	virtual bool OnInitialSetting(const SeaLabSimulationData &Data) = 0;

};

} //namespace SeaLabAPI


#endif  // IRPSSELWAVEPASSAGEEFFECT_H
