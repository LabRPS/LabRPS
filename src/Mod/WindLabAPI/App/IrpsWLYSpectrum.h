#ifndef IRPSWLYSPECTRUM_H
#define IRPSWLYSPECTRUM_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureYSpectrum.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLYSpectrum : public WindLabAPI::WindLabFeatureYSpectrum
{
public:
    virtual ~IrpsWLYSpectrum() {};

    virtual bool ComputeYCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

    virtual bool ComputeYCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeYCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeYCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix) = 0;

    virtual bool ComputeYAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue) = 0;
    
    virtual bool ComputeYAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeYAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI


#endif  // IRPSWLYSPECTRUM_H
