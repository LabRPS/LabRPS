#ifndef BOGDANOFGOLDBERNARD_MODULATION_H
#define BOGDANOFGOLDBERNARD_MODULATION_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>

namespace SeismicLabTools {

class SeismicLabToolsExport BogdanoffGoldbergBernardModulation
{
public:
    BogdanoffGoldbergBernardModulation();
    ~BogdanoffGoldbergBernardModulation();

    double computeModulation(const double& time, const double& coefficientOne, const double& coefficientTwo);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //BOGDANOFGOLDBERNARD_MODULATION_H
