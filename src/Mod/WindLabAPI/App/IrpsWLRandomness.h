#ifndef IRPSWLRANDOMNESS_H
#define IRPSWLRANDOMNESS_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureRandomness.h>

namespace WindLabAPI {

class IrpsWLRandomness : public WindLabAPI::WindLabFeatureRandomness
{
public:
    virtual ~IrpsWLRandomness() {};

    virtual bool ComputeRandomValue(const WindLabSimuData &Data, double &dValue) = 0;

    virtual bool GenerateRandomMatrixFP(const WindLabSimuData &Data, mat &dRandomValueArray) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLRANDOMNESS_H
