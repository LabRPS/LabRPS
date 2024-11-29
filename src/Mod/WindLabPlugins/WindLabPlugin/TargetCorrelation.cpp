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

#include "TargetCorrelation.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Mod/GeneralTools/App/AvailableWindows.h>

#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_statistics.h>
#include <QMessageBox>
#include <QThread>
#include <Base/Console.h>
#include <Gui/Control.h>


using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::TargetCorrelation, WindLabAPI::WindLabFeatureTableTool)

TargetCorrelation::TargetCorrelation()
{
	ADD_PROPERTY_TYPE(fftPointsNumber, (512), "Parameters", App::Prop_None, "The number of FFT points");
    this->OutputUnit.setValue("Dimensionless");
}


bool TargetCorrelation::TableToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat& inputTable, mat& outputTable)
{
	int N = Data.numberOfFrequency.getValue();
	double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
	int T = Data.numberOfTimeIncrements.getValue();
	double fs = 1 / dt;

	// the computed simulated spectrum is not correct when the number of time increment of the
	// simulated wind is smaller than the number of frequency increment. The following codes will
	// prevent this. this issue should be properly resolved in the next releases
	int aa = std::ceil((std::log(2 * T - 1) / std::log(2)));
	int bb = std::pow(2, aa);
	if (N >= bb)
	{
		Base::Console().Warning("The lenght of the simulated process is too small.\n");
		outputTable.resize(0, 0);
		return false;
	}

	outputTable.setZero(N + 1, 2);

	std::vector<double> targeCorr(N+1);//memory for the target psd vector
	std::vector<double> targetLags(N+1);//memory for the simulated psd frequency vector

	ComputeTargetCorrelation(Data, targetLags, targeCorr);

	for (int i = 0; i < N + 1; i++) {
		outputTable(i, 0) = targetLags[i];
		outputTable(i, 1) = targeCorr[i];
	}

	
	return true;
}

bool TargetCorrelation::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
	return true;
}

bool TargetCorrelation::ComputeTargetCorrelation(const WindLabAPI::WindLabSimulationData& Data, std::vector<double>& tau, std::vector<double>& corr)
{
	int n = Data.numberOfSpatialPosition.getValue();
	int N = Data.numberOfFrequency.getValue();
	double dt = Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);
	double wu = Data.maxFrequency.getQuantityValue().getValueAs(Base::Quantity::RadianPerSecond);
	int T = Data.numberOfTimeIncrements.getValue();

	// the computed simulated correlation is not correct when the number of time increment of the
	// simulated wind is smaller than the number of frequency increment. The following codes will
	// prevent this. this issue should be properly resolved in the next releases
	int aa = std::ceil((std::log(2 * T - 1) / std::log(2)));
	int bb = std::pow(2, aa);
	if (N >= bb)
	{
		Base::Console().Warning("The lenght of the simulated process is too small.\n");
		return false;
	}

	for (int l = 1; l <= N + 1; l++)//time lags for target cross correlation
	{
		tau[l - 1] = (-N) * dt + (l - 1) * 2 * dt;
	}

	mat locationCoord(n, 4);
	vec frequencies(N);
    cx_vec Sij(N);
    cx_vec FFTofSij(N);


	bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, locationCoord);
	if (!returnResult)
	{
		Base::Console().Warning("The computation of the location coordinates failed.\n");
		return false;
	}

	int locationIndexJ = Data.locationJ.getValue();
    int locationIndexK = Data.locationK.getValue();

     Base::Vector3d locationJ(locationCoord(locationIndexJ, 1), locationCoord(locationIndexJ, 2), locationCoord(locationIndexJ, 3));
     Base::Vector3d locationK(locationCoord(locationIndexK, 1), locationCoord(locationIndexK, 2), locationCoord(locationIndexK, 3));
     double time = Data.minTime.getQuantityValue().getValueAs(Base::Quantity::Second) + Data.timeIndex.getValue() * Data.timeIncrement.getQuantityValue().getValueAs(Base::Quantity::Second);

	returnResult = CRPSWindLabFramework::ComputeCrossSpectrumVectorF(Data, locationJ, locationK, time, frequencies, Sij);

	Eigen::FFT<double> fft;
	FFTofSij.col(0) = fft.inv(Sij.col(0));

	// For each frequency increment
	for (int i = 1; i <= N + 1; i++)
	{
		// local variable used to arrange the correlation in symetric way
		int po = abs(i - (N / 2) - 1) + 1;

		//Arrange the correlation in symetric way
		corr[i - 1] = 2 * wu * std::real(FFTofSij(po));
	}

	return true;
}

