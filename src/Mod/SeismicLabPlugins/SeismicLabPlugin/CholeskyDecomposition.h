
#ifndef SEISMICLAB_PLUGIN_CHOLESKYDECOMP_H
#define SEISMICLAB_PLUGIN_CHOLESKYDECOMP_H

#include <Mod/SeismicLabAPI/App/IrpsSLPSDdecompositionMethod.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CCholeskyDecomposition : public SeismicLabAPI::IrpsSLPSDdecompositionMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CCholeskyDecomposition);

public:
    CCholeskyDecomposition();

    ~CCholeskyDecomposition() {};

     bool ComputeDecomposedCrossSpectrumVectorF(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumVectorT(const SeismicLabAPI::SeismicLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumMatrixPP(const SeismicLabAPI::SeismicLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCPSDDecomMatrix);


    bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

};

} // namespace App

#endif // SEISMICLAB_PLUGIN_CHOLESKYDECOMP_H