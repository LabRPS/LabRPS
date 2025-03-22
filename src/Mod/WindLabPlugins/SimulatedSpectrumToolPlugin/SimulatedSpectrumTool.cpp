
#include "SimulatedSpectrumTool.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <unsupported/Eigen/FFT>
#include <Mod/GeneralTools/App/AvailableWindows.h>
#include "widgets/DlgSimulatedSpectrumTool.h"
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_statistics.h>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::SimulatedSpectrumTool, WindLabAPI::WindLabFeatureTableTool)

SimulatedSpectrumTool::SimulatedSpectrumTool()
{
    ADD_PROPERTY_TYPE(fftPointsNumber, (512), "Parameters", App::Prop_None, "The number of FFT points");
    ADD_PROPERTY_TYPE(WindowLength, (256), "Parameters", App::Prop_None, "The window length");
    ADD_PROPERTY_TYPE(OverLap, (128), "Parameters", App::Prop_None, "The overlap between between two records");

	 static const char* types[] = {"Bartlett Window",
                                  "Bartlett-Hann Window",
                                  "Blackman Window",
                                  "Blackman-Harris Window",
                                  "Bohman Window",
                                  "Chebyshev Window",
                                  "Fat Top Window",
                                  "Gaussian Window",
                                  "Hamming window",
                                  "Hann Window",
                                  "Kaiser Window",
                                  "Nuttall's Blackman-Harris Window",
                                  "Parzen Window",
                                  "Rectangular Window",
                                  "Trapezed Cosine Window",
                                  "Triangular Window",
                                  nullptr};
    ADD_PROPERTY_TYPE(WindowType, ((long int)0), "Parameters", App::Prop_None, "The window type");
     WindowType.setEnums(types);
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_WindLab_SimulatedSpectrumTool#Simulated_Spectrum_Tool");

}

bool SimulatedSpectrumTool::TableToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat& inputTable, mat& outputTable)
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
	double dt = Data.timeIncrement.getValue();
	int T = Data.numberOfTimeIncrements.getValue();
	double fs = 1 / dt;
    int fftPN = fftPointsNumber.getValue() / 2 + 1;

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

	if (fftPN > N)
	{
        outputTable.setZero(fftPN, 2);
	}
	else
	{
		outputTable.setZero(N, 2);
	}



	//////////////////////////////////////////////////////////////////////////////////////////////

	vec x(T);//memory for the process at locationJ
	vec y(T);//memory for the process at locationK

	std::vector<double> simuatedPSD(fftPN);//memory for the simulated psd vector
    vec frequenciesSim(fftPN);//memory for the simulated psd frequency vector


	//take the processes x and y from the entire matrix
	for (int l = 0; l < T; l++) {
		x(l) = inputTable(l, Data.locationJ.getValue() + 1);//+1 to skip the time column
		y(l) = inputTable(l, Data.locationK.getValue() + 1);//+1 to skip the time column
	}

	//compute the simulated cross spectral density between x and y
	computeSimulatedPSD(Data, x, y, frequenciesSim, simuatedPSD, WindowType.getValue(), WindowLength.getValue(), OverLap.getValue(), fftPointsNumber.getValue(), fs);

	for (int i = 0; i < fftPN; i++) {
        outputTable(i, 0) = frequenciesSim(i);
        outputTable(i, 1) = simuatedPSD[i] * ScaleCoefficient.getValue() / 2;
	}

	return true;
}

bool SimulatedSpectrumTool::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    // the input diolag
    WindLabGui::DlgSimulatedSpectrumToolEdit* dlg = new WindLabGui::DlgSimulatedSpectrumToolEdit(fftPointsNumber, WindowLength, OverLap, WindowType, Data.tableTool);
    Gui::Control().showDialog(dlg);

	return true;
}

bool SimulatedSpectrumTool::computeSimulatedPSD(const WindLabAPI::WindLabSimulationData& Data, const vec& x, const vec& y, vec& frequency, std::vector<double>& cpsd, int windowType, int windowLength, int overlap, int nfft, int fs)
{
	//memory for the window
	vec win(windowLength);

	rps::General::AvailableWindows availaibleWindows;

	//computing the window
	switch (windowType)
	{
	case 0:// Window type: Bartlett window

		availaibleWindows.BartlettWindow(win, windowLength);

		break;
	case 1:// Window type:Bartlett-Hann Window

		availaibleWindows.BartlettHannWindow(win, windowLength);

		break;
	case 2: // Window type: Blackman Window

		availaibleWindows.BlackmanWindow(win, windowLength);

		break;
	case 3: // Window type: Blackman-Harris Window

		availaibleWindows.BlackmanHarrisWindow(win, windowLength);

		break;
	case 4: // Window type: Bohman Window

		availaibleWindows.BohmanWindow(win, windowLength);

		break;
	case 5:// Window type: Chebyshev Window

		availaibleWindows.ChebyshevWindow(win, windowLength);

		break;
	case 6:// Window type: Fat Top Window

		availaibleWindows.FatTopWindow(win, windowLength);

		break;
	case 7: // Window type: Gaussian Window

		availaibleWindows.GaussianWindow(win, windowLength);

		break;
	case 8: // Window type: Hamming Window

		availaibleWindows.HammingWindow(win, windowLength);

		break;
	case 9: // Window type: Hann Window

		availaibleWindows.HannWindow(win, windowLength);

		break;

	case 10:// Window type: Kaiser Window

		availaibleWindows.KaiserWindow(win, windowLength);

		break;
	case 11:// Window type: Nuttall's Blackman-Harris Window

		availaibleWindows.NuttallBlackmanHarrisWindow(win, windowLength);

		break;
	case 12: // Window type: Parzen Window

		availaibleWindows.ParzenWindow(win, windowLength);

		break;
	case 13: // Window type: Rectangular Window

		availaibleWindows.RectangularWindow(win, windowLength);

		break;
	case 14: // Window type: Trapezed Cosine Window

		availaibleWindows.TrapezedCosineWindow(win, windowLength);

		break;
	case 15:// Window type: Triangular Window

		availaibleWindows.TriangularWindow(win, windowLength);

		break;

	}// end switch

	//    cout << win << endl;

	int k = (overlap - windowLength + x.rows()) / overlap;

	//compute the normalizing factor that will be used later
	double winSum = 0.0;

	for (int loop = 0; loop < windowLength; loop++)
	{
		winSum = winSum + win(loop) * win(loop);
	}

	double scale = 1 / (fs * winSum);

	//preallocate memory for vectors and matrices
	vec realTemp1;
	vec realTemp2;

	realTemp1.setZero(nfft);
	realTemp2.setZero(nfft);

	cx_vec complexTemp1;
	cx_vec complexTemp2;

	complexTemp1.setZero(nfft);
	complexTemp2.setZero(nfft);

	cx_mat mycpsd(nfft / 2 + 1, k);

	Eigen::FFT<double> fft;

	// iterate window segments
	for (int i = 0; i < k; i++) {

		//apply the selected window
		for (int j = 0; j < windowLength; j++) {
			const int idx = overlap * i + j;
			realTemp1(j) = x(idx) * win(j);
			realTemp2(j) = y(idx) * win(j);
		}

		//compute the fft and take only the first half
		complexTemp1 = fft.fwd(realTemp1);
		complexTemp2 = fft.fwd(realTemp2);

		//compute the periodogram
		for (int j = 0; j < nfft; j++) {
			complexTemp2(j) = complexTemp1(j) * conj(complexTemp2(j));
		}

		//store the result
		for (int j = 0; j < nfft / 2 + 1; j++) {
			mycpsd(j, i) = complexTemp2(j);
		}

	}

	//take the average of all the periodogram
	cx_vec mycpsd2(nfft / 2 + 1);

	for (int j = 0; j < nfft / 2 + 1; j++) {
		mycpsd2(j) = mycpsd.row(j).mean();
	}

	//normalization
	mycpsd2 = mycpsd2 * scale;

	//ignore the DC and Nyquist value
	for (int j = 1; j < nfft / 2; j++) {
		mycpsd2(j) = mycpsd2(j) * 2.0;
	}

	//save the cross psd result

	for (int j = 0; j < nfft / 2 + 1; j++) {
		cpsd[j] = abs(mycpsd2(j)) / (2 * pi);
	}

	//compute and save the frequencies
	const double df = (2 * pi) * fs / (double)nfft;
	for (int i = 0; i < nfft / 2 + 1; i++) {
		frequency(i) = (i + 1) * df;
	}

	return true;
}