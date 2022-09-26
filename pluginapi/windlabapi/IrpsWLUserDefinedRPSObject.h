#ifndef IRPSWLUSERDEFINEDRPSOBJECT_H
#define IRPSWLUSERDEFINEDRPSOBJECT_H

#include "RPSWindLabsimuData.h"

class IrpsWLUserDefinedRPSObject 
{
public:

    virtual ~IrpsWLUserDefinedRPSObject() {};

	virtual void UserDefinedRPSObjectComputePFT(const CRPSWindLabsimuData &Data, cube &dresultCube, QStringList &strInformation) = 0;

	virtual bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation) = 0;
};

#endif  // IRPSWLUSERDEFINEDRPSOBJECT_H
