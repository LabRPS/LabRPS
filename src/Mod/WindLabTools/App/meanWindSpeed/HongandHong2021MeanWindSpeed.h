#ifndef HONGANDHONGMEANWINDSPEED_H
#define HONGANDHONGMEANWINDSPEED_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace WindLabTools
{

class WindLabToolsExport HongandHong2021MeanWindSpeed
{
public:
    HongandHong2021MeanWindSpeed();
    ~HongandHong2021MeanWindSpeed();

    //this computes the along wind spectrum
    double  computeMeanWindSpeed(const double &height, const double &xCoordinate, const double &time);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //POWERLAWMEANWINDSPEED_H
