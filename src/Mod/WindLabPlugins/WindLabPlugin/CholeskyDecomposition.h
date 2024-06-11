
#ifndef WINDLAB_PLUGIN_CHOLESKYDECOMP_H
#define WINDLAB_PLUGIN_CHOLESKYDECOMP_H

#include <Mod/WindLabAPI/App/IrpsWLPSDdecompositionMethod.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CCholeskyDecomposition : public WindLabAPI::IrpsWLPSDdecompositionMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CCholeskyDecomposition);

public:
    CCholeskyDecomposition();

    ~CCholeskyDecomposition() {};

     bool ComputeDecomposedCrossSpectrumVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCPSDDecomMatrix);


    bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

};

} // namespace App

#endif // WINDLAB_PLUGIN_CHOLESKYDECOMP_H