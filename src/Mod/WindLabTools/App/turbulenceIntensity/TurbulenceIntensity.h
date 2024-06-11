#ifndef TURBULENCEINTENSITY_H
#define TURBULENCEINTENSITY_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>

namespace WindLabTools {

class WindLabToolsExport TurbulenceIntensity
{
public:
    TurbulenceIntensity();
    ~TurbulenceIntensity();

double computeASCETurbulenceIntensityValue(const double &height, const double &intensity10);
double computeASNZ1170TurbulenceIntensityValue(const double& height, const double& intensity10, const double& exponent);
double computeEurocodeTurbulenceIntensityValue(const double& height, const double& referenceHeight);
double computeIS875TurbulenceIntensityValue(const double& height, const double& referenceHeight);
double computeISOTurbulenceIntensityValue(const double& height, const double& referenceHeight);

virtual PyObject *getPyObject(void);

/// python object of this class
protected: // attributes
    Py::SmartPtr PythonObject;
};

}


#endif //KRENKCOHERENCE_H
