
#include "IrpsWLLocationDistribution.h"

class CWLHorizontalUniformDistribution : public IrpsWLLocationDistribution
{
public:
	~CWLHorizontalUniformDistribution() {};

	bool ComputeLocationCoordinateMatrixP3(const CRPSWindLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	//Initial setting
	bool OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation);

	//
public:
	//spacing between two adjacent points
	double mdSpacing;

	//Height
	double mdHeight;

	//Length
	double mdLength;
};


