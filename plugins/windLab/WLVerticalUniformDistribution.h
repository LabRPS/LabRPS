

#include "IrpsWLLocationDistribution.h"

class CWLVerticalUniformDistribution : public IrpsWLLocationDistribution
{
public:
	~CWLVerticalUniformDistribution() {};

	bool ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

};

