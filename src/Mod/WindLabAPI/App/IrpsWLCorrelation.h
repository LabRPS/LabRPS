#ifndef IRPSWLCORRELATION_H
#define IRPSWLCORRELATION_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureCorrelation.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLCorrelation : public WindLabAPI::WindLabFeatureCorrelation
{
public:
    virtual ~IrpsWLCorrelation() {};
	
    virtual bool ComputeCrossCorrelationValue(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue) = 0;
	
    virtual bool ComputeCrossCorrelationVectorT(const WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeCrossCorrelationMatrixPP(const WindLabSimuData &Data, const double &dTime, mat &dCorrelationMatrix) = 0;
	
	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLCORRELATION_H
