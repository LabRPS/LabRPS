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

#ifndef WINDLAB_PLUGIN_CHOLESKYDECOMP_H
#define WINDLAB_PLUGIN_CHOLESKYDECOMP_H

#include <Mod/WindLabAPI/App/IrpsWLPSDdecompositionMethod.h>

namespace WindLabAPI { class WindLabSimulationData; }

namespace WindLab {

class CCholeskyDecomposition : public WindLabAPI::IrpsWLPSDdecompositionMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CCholeskyDecomposition);

public:
    CCholeskyDecomposition();

    ~CCholeskyDecomposition() {};

     bool ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCPSDDecomMatrix);


    bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

};

} // namespace App

#endif // WINDLAB_PLUGIN_CHOLESKYDECOMP_H