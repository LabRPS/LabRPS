
#ifndef RPSDHLOWPROFILE_H
#define RPSDHLOWPROFILE_H

#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {


	class CRPSDHLowProfile : public  WindLabAPI::IrpsWLMean
	{
        PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSDHLowProfile);

	public:
		CRPSDHLowProfile();

		~CRPSDHLowProfile() {};

    bool ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);

    bool ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	public:
		 App::PropertyLength TerrainRoughness;
		 App::PropertySpeed ShearVelocity;
         App::PropertyLength ZeroPlanDisplacement;
		 App::PropertyAngle Latitude;
		 App::PropertyFrequency EarthAngularVelocity;
		 App::PropertyFloat Betta;

	};

}

#endif  // RPSDHLOWPROFILE_H