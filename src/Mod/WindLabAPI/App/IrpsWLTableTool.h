#ifndef IRPSWLTABLETOOL_H
#define IRPSWLTABLETOOL_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureTableTool.h>

namespace WindLabAPI {

class IrpsWLTableTool : public WindLabAPI::WindLabFeatureTableTool
{
public:

    virtual ~IrpsWLTableTool() {};

    virtual bool TableToolCompute(const WindLabSimuData &Data, const mat &inputTable, mat &outputTable) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;
};

} //namespace WindLabAPI


#endif  // IRPSWLTABLETOOL_H
