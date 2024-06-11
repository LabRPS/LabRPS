

#ifndef correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H
#define correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H

#include <Mod/WindLabAPI/App/IrpsWLTableTool.h>
#include <App/PropertyUnits.h>


/// pi
static constexpr double pi = 3.14159265358979323846264338327950288;

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

	class TargetCorrelation: public WindLabAPI::IrpsWLTableTool
	{
        PROPERTY_HEADER_WITH_OVERRIDE(WindLab::TargetCorrelation);

	public:
		TargetCorrelation();

		~TargetCorrelation() {};

		bool TableToolCompute(const WindLabAPI::WindLabSimuData& Data, const mat& inputTable, mat& outputTable);

		bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

		bool ComputeTargetCorrelation(const WindLabAPI::WindLabSimuData& Data, std::vector<double>& tau, std::vector<double>& corr);

public:
        App::PropertyInteger fftPointsNumber;

	};

} // namespace App

#endif // correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H