#include "PreCompiled.h"
#include "WindSpectrum.h"
#include <Mod/WindLabTools/App/spectrum/WindSpectrumPy.h>

using namespace WindLabTools;

WindSpectrum::WindSpectrum()
{

}

WindSpectrum::~WindSpectrum()
{

}

PyObject* WindSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new WindSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}