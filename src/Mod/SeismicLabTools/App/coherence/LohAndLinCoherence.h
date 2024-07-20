#ifndef LOHANDLIN_COHERENCE_H
#define LOHANDLIN_COHERENCE_H

#include <Mod/SeismicLabTools/SeismicLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>

namespace SeismicLabTools {

class SeismicLabToolsExport LohAndLinCoherence
{
public:
    LohAndLinCoherence();
    ~LohAndLinCoherence();

    double computeCoherenceValue(const double &locationJxCoord,
                                                      const double &locationJyCoord,
                                                      const double &locationJzCoord,
                                                      const double &locationKxCoord,
                                                      const double &locationKyCoord,
                                                      const double &locationKzCoord,
                                                      const double &frequency,
                                                      const double &parameterAlpha,
                                                      const double &parameterB);

  double computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK, 
                                                      const double &frequency, 
                                                      const double& parameterAlpha,
                                                      const double& parameterB);
virtual PyObject *getPyObject(void);

/// python object of this class
protected: // attributes
    Py::SmartPtr PythonObject;
};

}


#endif //LOHANDLIN_COHERENCE_H
