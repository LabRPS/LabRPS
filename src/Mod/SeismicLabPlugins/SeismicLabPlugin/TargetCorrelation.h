

#ifndef correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H
#define correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H

#include <Mod/SeismicLabAPI/App/IrpsSLTableTool.h>
#include <App/PropertyUnits.h>


/// pi
static constexpr double pi = 3.14159265358979323846264338327950288;

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

	class TargetCorrelation: public SeismicLabAPI::IrpsSLTableTool
	{
        PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::TargetCorrelation);

	public:
		TargetCorrelation();

		~TargetCorrelation() {};

		bool TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData& Data, const mat& inputTable, mat& outputTable);

		bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

		bool ComputeTargetCorrelation(const SeismicLabAPI::SeismicLabSimulationData& Data, std::vector<double>& tau, std::vector<double>& corr);

public:
        App::PropertyInteger fftPointsNumber;

	};

} // namespace App

#endif // correlationErgodicityPlugin_PLUGIN_TargetCorrelation_H