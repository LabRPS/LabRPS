#include "PreCompiled.h"
#include "SeismicGroundMotionSpectrum.h"
#include <Mod/SeismicLabTools/App/spectrum/SeismicGroundMotionSpectrumPy.h>

using namespace SeismicLabTools;

SeismicGroundMotionSpectrum::SeismicGroundMotionSpectrum()
{

}

SeismicGroundMotionSpectrum::~SeismicGroundMotionSpectrum()
{

}

PyObject* SeismicGroundMotionSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new SeismicGroundMotionSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}