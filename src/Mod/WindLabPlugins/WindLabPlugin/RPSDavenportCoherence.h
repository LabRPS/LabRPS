#ifndef WINDLAB_PLUGIN_DAVENPORTCOHERENCE_H
#define WINDLAB_PLUGIN_DAVENPORTCOHERENCE_H

#include <Mod/WindLabAPI/App/IrpsWLCoherence.h>

namespace WindLabAPI { class WindLabSimuData; }

namespace WindLab {

class CRPSDavenportCoherence : public WindLabAPI::IrpsWLCoherence
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSDavenportCoherence);

public:
    CRPSDavenportCoherence();

    ~CRPSDavenportCoherence() {};

   bool ComputeCrossCoherenceVectorF(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector) ;

   bool ComputeCrossCoherenceVectorT(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector);

   bool ComputeCrossCoherenceMatrixPP(const WindLabAPI::WindLabSimuData &Data, const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix);

   bool ComputeCrossCoherenceValue(const WindLabAPI::WindLabSimuData &Data, const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue);

   bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

public:
    // The decay coefficient Cx
    App::PropertyFloat ExponentialDecayCx;

    // The decay coefficient Cy
    App::PropertyFloat ExponentialDecayCy;

    // The decay coefficient Cy
    App::PropertyFloat ExponentialDecayCz;

};

} // namespace App

#endif // WINDLAB_PLUGIN_DAVENPORTCOHERENCE_H