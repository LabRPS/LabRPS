#ifndef KRENKCOHERENCE_H
#define KRENKCOHERENCE_H

#include <Mod/WindLabTools/WindLabToolsGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>

namespace WindLabTools {

class WindLabToolsExport KrenkCoherence
{
public:
    KrenkCoherence();
    ~KrenkCoherence();

    double computeCoherenceValue(const double &locationJxCoord,
                                                      const double &locationJyCoord,
                                                      const double &locationJzCoord,
                                                      const double &locationKxCoord,
                                                      const double &locationKyCoord,
                                                      const double &locationKzCoord,
                                                      const double &frequency,
                                                      const double &locationJMeanSpeed,
                                                      const double &locationKMeanSpeed,
                                                      const double &integralLength = 150);

  double computeCrossCoherenceValue(Base::Vector3d locationJ, Base::Vector3d locationK, 
                                                      const double &frequency,
                                                      const double &locationJMeanSpeed,
                                                      const double &locationKMeanSpeed,
                                                      const double &integralLength = 150);
virtual PyObject *getPyObject(void);

/// python object of this class
protected: // attributes
    Py::SmartPtr PythonObject;
};

}


#endif //KRENKCOHERENCE_H
