

#ifndef SimulatedCorrelationTool_PLUGIN_H
#define SimulatedCorrelationTool_PLUGIN_H

#include <Mod/WindLabAPI/App/IrpsWLTableTool.h>
#include <App/PropertyUnits.h>

/// pi
static constexpr double pi = 3.14159265358979323846264338327950288;

namespace WindLab {

	class SimulatedCorrelationTool : public WindLabAPI::IrpsWLTableTool
	{
        PROPERTY_HEADER_WITH_OVERRIDE(WindLab::SimulatedCorrelationTool);

	public:
		SimulatedCorrelationTool();

		~SimulatedCorrelationTool() {};

		bool TableToolCompute(const WindLabAPI::WindLabSimulationData& Data, const mat& inputTable, mat& outputTable);

		bool OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data);
		
		bool ComputeSimulatedCorrelation(const WindLabAPI::WindLabSimulationData& Data, const vec& x, const vec& y, std::vector<double>& tau, std::vector<double>& corr);

public:
        App::PropertyInteger fftPointsNumber;


	};

} // namespace App

#endif // SimulatedCorrelationTool_PLUGIN_H