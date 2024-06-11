#ifndef IRPSWLTURBULENCESCALE_H
#define IRPSWLTURBULENCESCALE_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureTurbulenceScale.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLTurbulenceScale : public WindLabAPI::WindLabFeatureTurbulenceScale
{
public:

    virtual ~IrpsWLTurbulenceScale() {};

    virtual bool ComputeTurbulenceScaleValue(const WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeTurbulenceScaleVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeTurbulenceScaleVectorT(const WindLabSimuData &Data, const Base::Vector3d &location, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLTURBULENCESCALE_H
