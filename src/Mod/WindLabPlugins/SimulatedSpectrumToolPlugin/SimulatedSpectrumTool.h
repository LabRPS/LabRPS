

#ifndef SimulatedSpectrumTool_PLUGIN_H
#define SimulatedSpectrumTool_PLUGIN_H

#include <Mod/WindLabAPI/App/IrpsWLTableTool.h>
#include <App/PropertyUnits.h>

/// pi
static constexpr double pi = 3.14159265358979323846264338327950288;

namespace WindLab {

	class SimulatedSpectrumTool : public WindLabAPI::IrpsWLTableTool
	{
        PROPERTY_HEADER_WITH_OVERRIDE(WindLab::SimulatedSpectrumTool);

	public:
		SimulatedSpectrumTool();

		~SimulatedSpectrumTool() {};

		bool TableToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat& inputTable, mat& outputTable);

		bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);

		bool computeSimulatedPSD(const WindLabAPI::WindLabSimulationData& Data, const vec& x, const vec& y, vec& frequency, std::vector<double>& cpsd, int windowType, int windowLength, int overlap, int nfft, int fs);
public:
        App::PropertyInteger fftPointsNumber;
		App::PropertyInteger WindowLength;
        App::PropertyInteger OverLap;
        App::PropertyEnumeration WindowType;

	};

} // namespace App

#endif // SimulatedSpectrumTool_PLUGIN_H