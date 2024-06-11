#ifndef POWERLAWMEANWINDSPEED_H
#define POWERLAWMEANWINDSPEED_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools
{

class WindLabToolsExport PowerLawMeanWindSpeed
{
public:
    PowerLawMeanWindSpeed();
    ~PowerLawMeanWindSpeed();

    //this computes the along wind spectrum
    double  computeMeanWindSpeed(const double &height, const double &referenceHeight, const double &referenceMeanSpeed, const double &zeroPlanDisplacement = 0, const double &dimensionlessPower = 0.12);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //POWERLAWMEANWINDSPEED_H
