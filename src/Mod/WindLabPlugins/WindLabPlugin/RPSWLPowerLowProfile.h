#ifndef RPSWLPOWERLOWPROFILE_H
#define RPSWLPOWERLOWPROFILE_H

#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
#include <App/PropertyUnits.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class RPSWLPowerLowProfile : public WindLabAPI::IrpsWLMean
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::RPSWLPowerLowProfile);

    public:
    RPSWLPowerLowProfile();

    ~RPSWLPowerLowProfile() {};

    bool ComputeMeanWindSpeedValue(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue);

    bool ComputeMeanWindSpeedVectorP(const WindLabAPI::WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector);

    bool ComputeMeanWindSpeedVectorT(const WindLabAPI::WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector);

    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

    public:

        // The mean speed reference height
        App::PropertyLength ReferenceHeight;

        // The mean speed reference speed
        App::PropertySpeed ReferenceSpeed;

        // The dimensionless power
        App::PropertyFloat DimensionlessPower;

        App::PropertyLength ZeroPlanDisplacement;

    };

}

#endif  // RPSWLPOWERLOWPROFILE_H
