#ifndef RESPONSE_SPECTRUM_H
#define RESPONSE_SPECTRUM_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include "BaseDesignResponseSpectrum.h"
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport DesignResponseSpectrum : public BaseDesignResponseSpectrum
{
public:
    DesignResponseSpectrum();
    ~DesignResponseSpectrum();

    double compute_Euro_EN1998_1_2004_Hori_Elastic_Response_Spectrum(const double &time, 
    const int &nationalAnnex = 1, 
    const double &damping = 5, const double & pga = 0.16, 
    const int &spectrumType = 1, const int &groundType = 1, 
    const int &importanceClass = 2);

    double compute_Euro_EN1998_1_2004_Hori_Design_Response_Spectrum(const double &time, 
    const int &nationalAnnex = 1, 
    const double &damping = 5, const double & pga = 0.16, 
    const int &spectrumType = 1, const int &groundType = 1, 
    const int &importanceClass = 2, const double &behaviorFactor = 1.00,
    const double &lowerBoundFactor = 0.20);

    double compute_Euro_EN1998_1_2004_Vert_Elastic_Response_Spectrum(const double &time, 
    const int &nationalAnnex = 1, 
    const double &damping = 5, const double & pga = 0.16, 
    const int &spectrumType = 1, const int &groundType = 1, 
    const int &importanceClass = 2);

    double compute_Euro_EN1998_1_2004_Vert_Design_Response_Spectrum(const double &time, 
    const int &nationalAnnex = 1, 
    const double &damping = 5, const double & pga = 0.16, 
    const int &spectrumType = 1, const int &groundType = 1, 
    const int &importanceClass = 2, const double &behaviorFactor = 1.00,
    const double &lowerBoundFactor = 0.20);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //RESPONSE_SPECTRUM_H
