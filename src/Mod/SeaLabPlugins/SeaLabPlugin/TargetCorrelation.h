

#ifndef correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H
#define correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H

#include <Mod/SeaLabAPI/App/IrpsSeLTableTool.h>
#include <App/PropertyUnits.h>


/// pi
static constexpr double pi = 3.14159265358979323846264338327950288;

namespace SeaLabAPI { class SeaLabSimulationData; }

namespace SeaLab {

	class TargetCorrelation: public SeaLabAPI::IrpsSeLTableTool
	{
        PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::TargetCorrelation);

	public:
		TargetCorrelation();

		~TargetCorrelation() {};

		bool TableToolCompute(const SeaLabAPI::SeaLabSimulationData& Data, const mat& inputTable, mat& outputTable);

		bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

		bool ComputeTargetCorrelation(const SeaLabAPI::SeaLabSimulationData& Data, std::vector<double>& tau, std::vector<double>& corr);

public:
        App::PropertyInteger fftPointsNumber;

	};

} // namespace App

#endif // correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H