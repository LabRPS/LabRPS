#include "PreCompiled.h"
#include "SeaSurfaceSpectrum.h"
#include <Mod/SeaLabTools/App/spectrum/SeaSurfaceSpectrumPy.h>

using namespace SeaLabTools;

SeaSurfaceSpectrum::SeaSurfaceSpectrum()
{

}

SeaSurfaceSpectrum::~SeaSurfaceSpectrum()
{

}

PyObject* SeaSurfaceSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new SeaSurfaceSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}