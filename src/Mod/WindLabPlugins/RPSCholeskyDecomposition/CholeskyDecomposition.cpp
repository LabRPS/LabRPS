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

#include "CholeskyDecomposition.h"
#include <Mod/GeneralTools/App/CholeskyDecomposition.h>

using namespace WindLab;
using namespace WindLabAPI;

CholeskyDecomposition::CholeskyDecomposition()
{
	this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab_RPSCholeskyDecomposition#RPS_Cholesky_Decomposition");
}

bool CholeskyDecomposition::MatrixToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat &inputMatrix, mat &outputMatrix)
{
    rps::General::CholeskyDecomposition decomposition;
    decomposition.computeCholeskyDecomposition(inputMatrix, outputMatrix);
    return true;
}

bool CholeskyDecomposition::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    return true;
}


