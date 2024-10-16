
#ifndef SEALAB_PLUGIN_CHOLESKYDECOMP_H
#define SEALAB_PLUGIN_CHOLESKYDECOMP_H

#include <Mod/SeaLabAPI/App/IrpsSeLPSDdecompositionMethod.h>

namespace SeaLabAPI { class SeaLabSimulationData; }

namespace SeaLab {

class CCholeskyDecomposition : public SeaLabAPI::IrpsSeLPSDdecompositionMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLab::CCholeskyDecomposition);

public:
    CCholeskyDecomposition();

    ~CCholeskyDecomposition() {};

     bool ComputeDecomposedCrossSpectrumVectorF(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumVectorT(const SeaLabAPI::SeaLabSimulationData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

     bool ComputeDecomposedCrossSpectrumMatrixPP(const SeaLabAPI::SeaLabSimulationData &Data, const double &dFrequency, const double &dTime, cx_mat &dCPSDDecomMatrix);


    bool OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data);

};

} // namespace App

#endif // SEALAB_PLUGIN_CHOLESKYDECOMP_H