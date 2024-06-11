#ifndef IRPSWLZSPECTRUM_H
#define IRPSWLZSPECTRUM_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureZSpectrum.h>
#include <Base/Vector3D.h>

namespace WindLabAPI {

class IrpsWLZSpectrum : public WindLabAPI::WindLabFeatureZSpectrum
{
public:
    virtual ~IrpsWLZSpectrum() {};

    virtual bool ComputeZCrossSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue) = 0;

    virtual bool ComputeZCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeZCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector) = 0;

    virtual bool ComputeZCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &psdMatrix) = 0;

    virtual bool ComputeZAutoSpectrumValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue) = 0;
    
    virtual bool ComputeZAutoSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector) = 0;

    virtual bool ComputeZAutoSpectrumVectorT(const WindLabAPI::WindLabSimuData& Data, const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;

};

} //namespace WindLabAPI

#endif  // IRPSWLZSPECTRUM_H
