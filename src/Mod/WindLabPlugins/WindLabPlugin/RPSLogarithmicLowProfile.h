#ifndef RPSLOGARITHMICLOWPROFILE_H
#define RPSLOGARITHMICLOWPROFILE_H

#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

    class RPSLogarithmicLowProfile : public WindLabAPI::IrpsWLMean
    {
        PROPERTY_HEADER_WITH_OVERRIDE(WindLab::RPSLogarithmicLowProfile);

    public:

        RPSLogarithmicLowProfile();
        ~RPSLogarithmicLowProfile() {};

    bool ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);

    bool ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

    public:
        // The terrain roughness length
        App::PropertyLength TerrainRoughness;

        // The shear velocity of the flow
        App::PropertySpeed ShearVelocity;

        // 0.4 is von karman's constant
        App::PropertyFloat vonKarmanConstant;

        App::PropertyLength ZeroPlanDisplacement;

    };
}

#endif  // RPSLOGARITHMICLOWPROFILE_H