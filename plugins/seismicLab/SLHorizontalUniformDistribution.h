
#include "IrpsSLLocationDistribution.h"

class CWLHorizontalUniformDistribution : public IrpsSLLocationDistribution
{
public:
	~CWLHorizontalUniformDistribution() {};

	void ComputeLocationCoordinateMatrixP3(const CRPSSeismicLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	//Initial setting
	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

	//
public:
	//spacing between two adjacent points
	double mdSpacing;

	//Height
	double mdHeight;

	//Length
	double mdLength;
};


