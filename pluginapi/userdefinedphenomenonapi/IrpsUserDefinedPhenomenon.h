#ifndef IRPSUSERDEFINEDPHENOMENON_H
#define IRPSUSERDEFINEDPHENOMENON_H

# include "RPS.h"
# include "RPSUserDefinedPhenomenonSimuData.h"

class IrpsUserDefinedPhenomenon 
{
public:

    virtual ~IrpsUserDefinedPhenomenon() {};

    //Initial setting
    virtual bool OnInitialSetting(const CRPSUserDefinedPhenomenonSimuData &Data, QStringList &strInformation) = 0;

	// The simulation function 
    virtual bool Simulate(const CRPSUserDefinedPhenomenonSimuData &Data, mat &dVelocityArray, QStringList &strInformation) = 0;

	// The simulation function in large scale mode 
    virtual bool SimulateInLargeScaleMode(const CRPSUserDefinedPhenomenonSimuData &Data, QString &strFileName, QStringList &strInformation) = 0;

	// The simulation function in Comparision mode 
    virtual bool SimulateInComparisonMode(const CRPSUserDefinedPhenomenonSimuData &Data, mat &dRandomPhaseArray, mat &dVelocityArray, QStringList &strInformation) = 0;
};

#endif  // IRPSUSERDEFINEDPHENOMENON_H
