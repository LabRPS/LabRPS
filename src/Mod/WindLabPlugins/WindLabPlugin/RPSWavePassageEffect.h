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


#ifndef WINDLAB_PLUGIN_WAVEPASSAGEEFFECT_H
#define WINDLAB_PLUGIN_WAVEPASSAGEEFFECT_H

#include <Mod/WindLabAPI/App/IrpsWLWavePassageEffect.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CRPSWavePassageEffect: public WindLabAPI::IrpsWLWavePassageEffect
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSWavePassageEffect);
public:
	CRPSWavePassageEffect();
	
	~CRPSWavePassageEffect() {};

    bool ComputeWavePassageEffectVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

    bool ComputeWavePassageEffectVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

    bool ComputeWavePassageEffectMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

    bool ComputeWavePassageEffectValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:

    App::PropertySpeed ApparentWaveVelocity;
    App::PropertyFloat Coefficient;


};

} // namespace App

#endif // WINDLAB_PLUGIN_CHOLESKYDECOMP_H