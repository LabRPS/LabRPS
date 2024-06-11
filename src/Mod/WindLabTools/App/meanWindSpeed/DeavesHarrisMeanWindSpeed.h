#ifndef DHMEANWINDSPEED_H
#define DHMEANWINDSPEED_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools
{
class WindLabToolsExport DeavesHarrisMeanWindSpeed
{
public:
    DeavesHarrisMeanWindSpeed();
    ~DeavesHarrisMeanWindSpeed();

    //this computes the along wind spectrum
    double computeMeanWindSpeed(const double &height, const double &terrainRoughness, const double &shearVelocity, const double &zeroPlanDisplacement, const double &latitude, const double &earthAngularVelocity = 0.0000729, const double &beta = 6);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //DHMEANWINDSPEED_H
