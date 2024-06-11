#ifndef IRPSWLMATRIXTOOL_H
#define IRPSWLMATRIXTOOL_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureMatrixTool.h>

namespace WindLabAPI {

class IrpsWLMatrixTool : public WindLabAPI::WindLabFeatureMatrixTool
{
public:

    virtual ~IrpsWLMatrixTool() {};

    virtual bool MatrixToolCompute(const WindLabSimuData &Data, const mat &inputMatrix, mat &outputMatrix) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;
};

} //namespace WindLabAPI

#endif  // IRPSWLMATRIXTOOL_H
