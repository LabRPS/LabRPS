#ifndef IRPSWLMATRIXTOOL_H
#define IRPSWLMATRIXTOOL_H

#include "RPSWindLabsimuData.h"

class IrpsWLMatrixTool 
{
public:

    virtual ~IrpsWLMatrixTool() {};

    virtual bool MatrixToolCompute(const CRPSWindLabsimuData &Data, const mat &inputMatrix, mat &outputMatrix, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;
};

#endif  // IRPSWLMATRIXTOOL_H
