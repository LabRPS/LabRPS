#ifndef WAVEPASSAGEEFFECT_H
#define WAVEPASSAGEEFFECT_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>
#include <complex>

namespace WindLabTools {

class WindLabToolsExport WavePassageEffect
{
public:
    WavePassageEffect();
    ~WavePassageEffect();

    std::complex<double>  computeWavePassageEffect(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &frequency, const double &apparentWaveVelocity);

    double  computeApparentWaveVelocity(const double &velocityJ, const double &velocityK, const double &coefficient);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //SINEMODULATION_H
