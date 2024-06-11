#ifndef LOGARITHMICMEANWINDSPEED_H
#define LOGARITHMICMEANWINDSPEED_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools
{

class WindLabToolsExport LogarithmicMeanWindSpeed
{
public:
    LogarithmicMeanWindSpeed();
    ~LogarithmicMeanWindSpeed();

    //this computes the along wind spectrum
    double  computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &zeroPlanDisplacement = 0);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}


#endif //LOGARITHMICMEANWINDSPEED_H
