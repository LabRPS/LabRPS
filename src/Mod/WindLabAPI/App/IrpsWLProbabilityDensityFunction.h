#ifndef IRPSWLPDF_H
#define IRPSWLPDF_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureProbabilityDensityFunction.h>

namespace WindLabAPI {

class IrpsWLProbabilityDensityFunction : public WindLabAPI::WindLabFeatureProbabilityDensityFunction
{
public:

    virtual ~IrpsWLProbabilityDensityFunction() {};

    virtual bool ComputePDFValue(const WindLabSimuData &Data, const double &x, double &dValue) = 0;

    virtual bool ComputePDFVectorX(const WindLabSimuData &Data, vec &dVarVector, vec &dValVector) = 0;

    virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLPDF_H
