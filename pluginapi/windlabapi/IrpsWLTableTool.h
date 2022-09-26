#ifndef IRPSWLTABLETOOL_H
#define IRPSWLTABLETOOL_H

#include "RPSWindLabsimuData.h"

class IrpsWLTableTool 
{
public:

    virtual ~IrpsWLTableTool() {};

	virtual void TableToolComputePFT(const CRPSWindLabsimuData &Data, const mat &inputTable, mat &outputTable, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;
};

#endif  // IRPSWLTABLETOOL_H
