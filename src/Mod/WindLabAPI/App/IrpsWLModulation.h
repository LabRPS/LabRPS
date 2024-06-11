#ifndef IRPSWLMODULATION_H
#define IRPSWLMODULATION_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureModulation.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLModulation : public WindLabAPI::WindLabFeatureModulation
{
public:
    virtual ~IrpsWLModulation() {};

    virtual bool ComputeModulationValue(const WindLabSimuData &Data, Base::Vector3d location, const double &dTime, double &dValue) = 0;

    virtual bool ComputeModulationVectorP(const WindLabSimuData &Data, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeModulationVectorT(const WindLabSimuData &Data, Base::Vector3d location, vec &dVarVector, vec &dValVector) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLMODULATION_H
