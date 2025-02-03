#include "PreCompiled.h"
#include "DirectionalSpreadingFunction.h"
#include <Mod/SeaLabTools/App/DirectionalSpreadingFunction/DirectionalSpreadingFunctionPy.h>

using namespace SeaLabTools;

DirectionalSpreadingFunction::DirectionalSpreadingFunction()
{

}

DirectionalSpreadingFunction::~DirectionalSpreadingFunction()
{

}

PyObject* DirectionalSpreadingFunction::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DirectionalSpreadingFunctionPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}