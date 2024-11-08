#include "PreCompiled.h"
#include "BaseDesignResponseSpectrum.h"
#include <Mod/SeismicLabTools/App/ResponseSpectrum/BaseDesignResponseSpectrumPy.h>

using namespace SeismicLabTools;

BaseDesignResponseSpectrum::BaseDesignResponseSpectrum()
{

}

BaseDesignResponseSpectrum::~BaseDesignResponseSpectrum()
{

}

PyObject* BaseDesignResponseSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new BaseDesignResponseSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}