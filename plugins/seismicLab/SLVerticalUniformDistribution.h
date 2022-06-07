
#include "IrpsSLLocationDistribution.h"

class CSLVerticalUniformDistribution : public IrpsSLLocationDistribution
{
public:
	~CSLVerticalUniformDistribution() {};

	void ComputeLocationCoordinateMatrixP3(const CRPSSeismicLabsimuData &Data, mat &dLocCoord, QStringList &strInformation);

	//Initial setting
	bool OnInitialSetting(const CRPSSeismicLabsimuData &Data, QStringList &strInformation);

};

