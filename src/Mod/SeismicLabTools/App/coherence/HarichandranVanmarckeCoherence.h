#ifndef HARICHANDRANVANMARCKECOHERENCE_H
#define HARICHANDRANVANMARCKECOHERENCE_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>

namespace SeismicLabTools {

class SeismicLabToolsExport HarichandranVanmarckeCoherence
{
public:
    HarichandranVanmarckeCoherence();
    ~HarichandranVanmarckeCoherence();

    double computeCoherenceValue(const double &locationJxCoord,
                                                  const double &locationJyCoord,
                                                  const double &locationJzCoord,
                                                  const double &locationKxCoord,
                                                  const double &locationKyCoord,
                                                  const double &locationKzCoord,
                                                  const double &frequency,
                                                  const double &parameterA,
                                                  const double &parameterAlpha,
                                                  const double &parameterK,
                                                  const double &parameterOmegaZero,
                                                  const double &parameterB);

  double computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK, 
                                                 const double &frequency,
                                                  const double &parameterA,
                                                  const double &parameterAlpha,
                                                  const double &parameterK,
                                                  const double &parameterOmegaZero,
                                                  const double &parameterB);
virtual PyObject *getPyObject(void);

/// python object of this class
protected: // attributes
    Py::SmartPtr PythonObject;
};

}


#endif //HARICHANDRANVANMARCKECOHERENCE_H
