
#include "SimulatedCorrelationTool.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Mod/GeneralTools/App/AvailableWindows.h>
#include "widgets/DlgSimulatedCorrelationTool.h"
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_statistics.h>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::SimulatedCorrelationTool, WindLabAPI::WindLabFeatureTableTool)

SimulatedCorrelationTool::SimulatedCorrelationTool()
{
    ADD_PROPERTY_TYPE(fftPointsNumber, (512), "Parameters", App::Prop_None, "The number of FFT points");

}

bool SimulatedCorrelationTool::TableToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat& inputTable, mat& outputTable)
{
	if (inputTable.rows() != Data.numberOfTimeIncrements.getValue() || inputTable.cols() != Data.numberOfSpatialPosition.getValue() + 1)
	{
		Base::Console().Warning("The computation fails. Please make sure the simulated wind velocity data table is the active window before you run this code.\n");
		outputTable.resize(0, 0);
		return false;
	}

	if (!Data.stationarity.getValue())
	{
		Base::Console().Warning("The computation fails. This tool does not work for non-stationary wind.\n");
		outputTable.resize(0, 0);
		return false;
	}

	int N = Data.numberOfFrequency.getValue();
	int T = Data.numberOfTimeIncrements.getValue();

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

	if ((fftPointsNumber.getValue() / 2 + 1) > (2 * N + 1))
	{
        outputTable.setZero(fftPointsNumber.getValue() / 2 + 1, 2);
	}
	else
	{
		outputTable.setZero(2 * N + 1, 2);
	}

	vec x2(T);//memory for the process at locationJ
	vec y2(T);//memory for the process at locationK

	x2.setZero(bb);//memory for the process at locationJ
	y2.setZero(bb);//memory for the process at locationK


	std::vector<double> simuatedCorr(2 * N + 1);//memory for the simulated psd vector
	std::vector<double> simulatedLags(2 * N + 1);//memory for the simulated psd frequency vector


	//take the processes x and y from the entire matrix
	for (int l = 0; l < T; l++) {
		x2(l) = inputTable(l, Data.locationJ.getValue() + 1);//+1 to skip the time column
		y2(l) = inputTable(l, Data.locationK.getValue() + 1);//+1 to skip the time column
	}

	ComputeSimulatedCorrelation(Data, x2, y2, simulatedLags, simuatedCorr);

	//take the computation results for the simulated psd
	for (int i = 0; i < 2 * N + 1; i++) {
		outputTable(i, 0) = simulatedLags[i];
		outputTable(i, 1) = simuatedCorr[i];
	}

	return true;
}

bool SimulatedCorrelationTool::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    // the input diolag
    WindLabGui::DlgSimulatedCorrelationToolEdit* dlg = new WindLabGui::DlgSimulatedCorrelationToolEdit(fftPointsNumber, Data.tableTool);
    Gui::Control().showDialog(dlg);
	return true;
}

bool SimulatedCorrelationTool::ComputeSimulatedCorrelation(const WindLabAPI::WindLabSimulationData& Data, const vec& x, const vec& y, std::vector<double>& tau, std::vector<double>& corr)
{
	int n = Data.numberOfSpatialPosition.getValue();
	int N = Data.numberOfFrequency.getValue();
	double dt = Data.timeIncrement.getValue();
	double wu = Data.maxFrequency.getValue();
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

	for (int l = 1; l <= 2 * N + 1; l++)//time lags for simulated cross correlation
	{
		tau[l - 1] = (-N) * dt + (l - 1) * dt;
	}


	int a = std::ceil((std::log(2 * T - 1) / std::log(2)));
	int b = std::pow(2, a);

	cx_vec xxxJ(b);
	cx_vec xxxK(b);
	cx_vec yyy(b);
	cx_vec zzz(b);

	xxxJ.setZero(b);
	xxxK.setZero(b);
	yyy.setZero(b);
	zzz.setZero(b);


	Eigen::FFT<double> fft;

	xxxJ = fft.fwd(x);
	xxxK = fft.fwd(y);

	for (int l = 1; l <= b; l++)
	{
		yyy(l - 1) = xxxJ(l - 1) * conj(xxxK(l - 1));
	}

	zzz = fft.inv(yyy);

	//// Copy values to the correlation vector symetrically R[lag] = R[-lag]
	for (int lag = 0; lag < N; lag++)
	{
		corr[lag] = zzz(N - lag).real() / T;
	}

	for (int lag = 0; lag <= N; lag++)
	{
		corr[N + lag] = zzz(lag).real() / T;
	}

	return false;
}

