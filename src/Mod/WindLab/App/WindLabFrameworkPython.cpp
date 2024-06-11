/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC) <vv.titov@gmail.com>       *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/
#include "PreCompiled.h"
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include "WindLabFrameworkPython.h"
#include <Base/PyObjectBase.h>
#include <Mod/WindLabAPI/App/WindLabSimuDataPy.h>
#include <Mod/WindLabAPI/App/WindLabSimuData.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <Mod/WindLabAPI/App/RPS.h>

namespace WindLab
{
PyObject* WindLabFrameworkPython::returnResult1(vec& dVarVector, vec& dValVector)
{
    mat resArray(dVarVector.rows(), 2);
    resArray.col(0) = dVarVector;
    resArray.col(1) = dValVector;


    for (int j = 0; j < resArray.rows(); j++) {
        resArray(j, 0) = dVarVector(j);
        resArray(j, 1) = dValVector(j);
    }

    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
        Py::List row;
        for (int j = 0; j < resArray.cols(); j++) {
            row.append(Py::Float((resArray.coeff(i, j))));
        }
        activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* WindLabFrameworkPython::returnResult2(vec& dVarVector, cx_vec& dValVector)
{
    mat resArray(dVarVector.rows(), 3);

    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
    resArray(i, 0) = dVarVector(i);
    resArray(i, 1) = dValVector(i).real();
    resArray(i, 2) = dValVector(i).imag();
    Py::List row;
    for (int j = 0; j < resArray.cols(); j++) {
        row.append(Py::Float((resArray.coeff(i, j))));
    }
    activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* WindLabFrameworkPython::returnResult3(cx_mat& resArray, std::string featureName, const char* displayOption)
{
     Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
    Py::List row;
    for (int j = 0; j < resArray.cols(); j++) {

       if (strcmp(displayOption, "i") == 0) {
            row.append(Py::Float((resArray.coeff(i, j)).imag()));
       }
       else
       {
            row.append(Py::Float((resArray.coeff(i, j)).real()));
       }    
    }
    activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* WindLabFrameworkPython::returnResult4(mat& resArray)
{
    Py::List activeArray;
    for (int i = 0; i < resArray.rows(); i++) {
    Py::List row;
    for (int j = 0; j < resArray.cols(); j++) {
        row.append(Py::Float((resArray.coeff(i, j))));
    }
    activeArray.append(row);
    }
    return boost::python::incref(activeArray.ptr());
}

PyObject* WindLabFrameworkPython::returnResult5(std::complex<double>& resValue)
{
    Py::List activeArray;
    activeArray.append(Py::Float(resValue.real()));
    activeArray.append(Py::Float(resValue.imag()));

    return boost::python::incref(activeArray.ptr());
}

PyObject* WindLabFrameworkPython::returnResult6(double resValue)
{
    Py::Float activeValue(resValue);
    
    return boost::python::incref(activeValue.ptr());
}



   // coherence function
PyObject* WindLabFrameworkPython::ComputeCrossCoherenceVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeCrossCoherenceVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeCrossCoherenceMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

	// correlation function
	
    PyObject* WindLabFrameworkPython::ComputeCrossCorrelationVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeCrossCorrelationMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

   // frequency
    PyObject* WindLabFrameworkPython::ComputeFrequenciesVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}
  
    PyObject* WindLabFrameworkPython::ComputeFrequenciesMatrixFP(PyObject* self, PyObject* args)
{
     return NULL;
}

PyObject* WindLabFrameworkPython::ComputeLocationCoordinateMatrixP3(PyObject* /*self*/, PyObject* args)
{
   /*  PyObject* object = nullptr;

        if (PyArg_ParseTuple(args, "O", &(WindLabAPI::WindLabSimuDataPy::Type), &object) && object) {
            WindLabAPI::WindLabSimuData* simuData = static_cast<WindLabAPI::WindLabSimuDataPy*>(object)->getWindLabSimuDataPtr();
            if (!simuData || !simuData->getTypeId().isDerivedFrom(WindLabAPI::WindLabSimuData::getClassTypeId())) {
                throw Py::Exception(Base::PyExc_FC_GeneralError, "The simulation data object have to be of type WindLabAPI::WindLabSimuData!");
            }
             try {              
                mat resArray(simuData->numberOfSpatialPosition, 4);
                WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(*simuData, resArray);
                return returnResult4(resArray);
            }
            catch (const Py::Exception&) {
                throw;
            }
        }*/

      return NULL;

}
	// mean wind speed
    PyObject* WindLabFrameworkPython::ComputeMeanWindSpeedVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeMeanWindSpeedVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

	// modulation function
    PyObject* WindLabFrameworkPython::ComputeModulationVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeModulationVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}

	// psd decomposition
    PyObject* WindLabFrameworkPython::ComputeDecomposedCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeDecomposedCrossSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeDecomposedCrossSpectrumMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

	// randomness
    PyObject* WindLabFrameworkPython::GenerateRandomMatrixFP(PyObject* self, PyObject* args)
{
     return NULL;
}

	// X spectrum

    PyObject* WindLabFrameworkPython::ComputeXCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeXCrossSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeXCrossSpectrumMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeXAutoSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    
    PyObject* WindLabFrameworkPython::ComputeXAutoSpectrumVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeXAutoSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

	// Y spectrum
    PyObject* WindLabFrameworkPython::ComputeYCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeYCrossSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeYCrossSpectrumMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeYAutoSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    
    PyObject* WindLabFrameworkPython::ComputeYAutoSpectrumVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeYAutoSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

	// Z spectrum
    PyObject* WindLabFrameworkPython::ComputeZCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeZCrossSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeZCrossSpectrumMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeZAutoSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    
    PyObject* WindLabFrameworkPython::ComputeZAutoSpectrumVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeZAutoSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

	// spectrum X, Y, Z
    PyObject* WindLabFrameworkPython::ComputeCrossSpectrumVectorF(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeCrossSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeCrossSpectrumMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeAutoSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    
    PyObject* WindLabFrameworkPython::ComputeAutoSpectrumVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeAutoSpectrumVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

	/////
    PyObject* WindLabFrameworkPython::ComputeCrossCoherenceValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeCrossCorrelationValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeMeanWindSpeedValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeModulationValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeRandomValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeXCrossSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeYCrossSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeZCrossSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeCrossSpectrumValue(PyObject* self, PyObject* args)
{
     return NULL;
}
	  PyObject* WindLabFrameworkPython::ComputeFrequencyValue(PyObject* self, PyObject* args)
{
     return NULL;
}

	PyObject* getSpatialDistributionObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getMeanProfilObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getAlongWindSpectrumObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getVerticalWindSpectrumObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getAcrossWindSpectrumObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getDecomposedSpectrumObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getCoherenceFunctionObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getSimulationMethodObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getFrequencyDistributionObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getRandomnessProviderObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getModulationFunctionObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getCorrelationFunctionObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getTableToolObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getMatrixToolObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
	PyObject* getUserDefinedRPSObjDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getCDFDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getGustFactorDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getKurtosisDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getPeakFactorDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getPDFDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getRoughnessDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getShearVelocityOfFlowDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getSkewnessDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getStandardDeviationDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getTurbulenceIntensityDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getTurbulenceScaleDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getVarianceDescription(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* getWavePassageEffectDescription(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::TableToolCompute(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::MatrixToolCompute(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::UserDefinedRPSObjectCompute(PyObject* self, PyObject* args)
{
     return NULL;
}

    PyObject* WindLabFrameworkPython::ComputeCPDValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeCPDVectorX(PyObject* /*self*/, PyObject* args)
    {
     return NULL;
    }
    
    //gust factor
    PyObject* WindLabFrameworkPython::ComputeGustFactorValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeGustFactorVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeGustFactorVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //kurtosis
    PyObject* WindLabFrameworkPython::ComputeKurtosisValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeKurtosisVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeKurtosisVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //peak factor
    PyObject* WindLabFrameworkPython::ComputePeakFactorValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputePeakFactorVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputePeakFactorVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //pdf
    PyObject* WindLabFrameworkPython::ComputePDFValue(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputePDFVectorX(PyObject* /*self*/, PyObject* args)
{
     return NULL;
}

    //roughness
    PyObject* WindLabFrameworkPython::ComputeRoughnessValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeRoughnessVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeRoughnessVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //shear velocity
    PyObject* WindLabFrameworkPython::ComputeShearVelocityOfFlowValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeShearVelocityOfFlowVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeShearVelocityOfFlowVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //skewness
    PyObject* WindLabFrameworkPython::ComputeSkewnessValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeSkewnessVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeSkewnessVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //standard deviation
    PyObject* WindLabFrameworkPython::ComputeStandardDeviationValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeStandardDeviationVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeStandardDeviationVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //turbulence intensity
    PyObject* WindLabFrameworkPython::ComputeTurbulenceIntensityValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeTurbulenceIntensityVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeTurbulenceIntensityVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //turbulence scale
    PyObject* WindLabFrameworkPython::ComputeTurbulenceScaleValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeTurbulenceScaleVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeTurbulenceScaleVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    //variance
    PyObject* WindLabFrameworkPython::ComputeVarianceValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeVarianceVectorP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeVarianceVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}

    // wave passage effect
    PyObject* WindLabFrameworkPython::ComputeWavePassageEffectVectorF(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeWavePassageEffectVectorT(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeWavePassageEffectMatrixPP(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::ComputeWavePassageEffectValue(PyObject* self, PyObject* args)
{
     return NULL;
}
    PyObject* WindLabFrameworkPython::getLocationIndex(PyObject* self, PyObject* args)
{
     return NULL;
}

PyMethodDef WindLabFrameworkPython::Methods[] = {
    {"computeLocationCoordinateMatrixP3", (PyCFunction)WindLabFrameworkPython::ComputeLocationCoordinateMatrixP3, METH_VARARGS,
    "computeLocationCoordinateMatrixP3(simuData) - compute the location coordinate"},
    {nullptr, nullptr, 0, nullptr}  /* Sentinel */
};


} //namespace WindLabAPI
