#ifndef IRPSWLTURBULENCEINTENSITY_H
#define IRPSWLTURBULENCEINTENSITY_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceIntensity.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLTurbulenceIntensity : public WindLabAPI::WindLabFeatureTurbulenceIntensity
{
public:

    virtual ~IrpsWLTurbulenceIntensity() {};
    
    virtual bool ComputeTurbulenceIntensityValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeTurbulenceIntensityVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeTurbulenceIntensityVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLTURBULENCEINTENSITY_H
