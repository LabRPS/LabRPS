#ifndef IRPSWLUSERDEFINEDRPSOBJECT_H
#define IRPSWLUSERDEFINEDRPSOBJECT_H

#include "WindLabSimuData.h"
#include <Mod/WindLabAPI/App/WindLabFeatureUserDefinedRPSObject.h>

namespace WindLabAPI {

class IrpsWLUserDefinedRPSObject : public WindLabAPI::WindLabFeatureUserDefinedRPSObject
{
public:

    virtual ~IrpsWLUserDefinedRPSObject() {};

    virtual bool UserDefinedRPSObjectCompute(const WindLabSimuData &Data, mat &dresult) = 0;

	virtual bool OnInitialSetting(const WindLabSimuData &Data) = 0;
};

} //namespace WindLabAPI


#endif  // IRPSWLUSERDEFINEDRPSOBJECT_H
