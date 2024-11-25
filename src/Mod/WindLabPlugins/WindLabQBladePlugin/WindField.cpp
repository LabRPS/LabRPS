/**********************************************************************

    Copyright (C) 2012 David Marten <david.marten@qblade.org>

    This program is licensed under the Academic Public License
    (APL) v1.0; You can use, redistribute and/or modify it in
    non-commercial academic environments under the terms of the
    APL as published by the QBlade project; See the file 'LICENSE'
    for details; Commercial use requires a commercial license
    (contact info@qblade.org).

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

***********************************************************************/
#define NOMINMAX

#include "WindField.h"
#include <cmath>
#include <ctime>  // For time()
#include <cstdlib>  // For srand() and rand()
#include <omp.h>
#include <QDebug>
#include <QDate>
#include <limits>

#define PI_ 3.14159265358979323846

WindField::WindField(
    const WindLabAPI::WindLabSimulationData& Data, const App::PropertyInteger& RandomPhaseSeed,
    const App::PropertyTime& SimulationTime, const App::PropertyTime& TimeStepSize,
    const App::PropertyLength& GridWidth,
    const App::PropertyInteger& GridPoints, 
    const App::PropertyLength& HubHeight, const App::PropertySpeed& MeanWindSpeed,
    const App::PropertyEnumeration& ProfileModel, const App::PropertyLength& ReferenceHeight,
    const App::PropertyFloat& ShearExponent, const App::PropertyFloat& RoughnessLength,
    const App::PropertyFloat& TurbulenceIntensity, const App::PropertyLength& FieldRadius,
    bool cancelCalculation)
{
    // Grid parameters
    m_seed = RandomPhaseSeed.getValue();
    m_assignedSimulationTime = SimulationTime.getQuantityValue().getValueAs(Base::Quantity::Second);
    m_assignedTimeStep = TimeStepSize.getQuantityValue().getValueAs(Base::Quantity::Second);
    m_fieldDimensionY = GridWidth.getQuantityValue().getValueAs(Base::Quantity::Metre);
    m_fieldDimensionZ = GridWidth.getQuantityValue().getValueAs(Base::Quantity::Metre);
    m_pointsPerSideY = GridPoints.getValue();
    m_pointsPerSideZ = GridPoints.getValue();
    m_hubheight = HubHeight.getQuantityValue().getValueAs(Base::Quantity::Metre);
    
    // Flow parameters
    m_meanWindSpeed = MeanWindSpeed.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond);
    //m_hInflow = HorizontalInFlow.getQuantityValue().getValueAs(Base::Quantity::Degree);
    //m_vInflow = VerticalInFlow.getQuantityValue().getValueAs(Base::Quantity::Degree);
    //m_IEAType = IECStandard.getValue();
    //m_windModel = WindModel.getValue();
    //m_spectralModel = SpectralModel.getValue();
    //m_bDefaultShear = DefaultProfileAndShear.getValue();
    m_profileModel = ProfileModel.getValue();
    m_windSpeedMeasurementHeight = ReferenceHeight.getQuantityValue().getValueAs(Base::Quantity::Metre);
    m_shearExponent = ShearExponent.getValue();
    m_roughnessLength = RoughnessLength.getValue();
    //m_jetHeight = JetHeight.getQuantityValue().getValueAs(Base::Quantity::Metre);
    //m_ETMc = EtmcValue.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond);

    // Wind turbine class
    //m_turbineClass = TurbineClass.getValue();
    //m_turbulenceClass = TurbulenceClass.getValue();
    m_turbulenceIntensity = TurbulenceIntensity.getValue(); 
    //m_VRef = VRef.getValue();
    m_fieldRadius = FieldRadius.getQuantityValue().getValueAs(Base::Quantity::Metre);

    m_minValueX = std::numeric_limits<float>::max();
    m_maxValueX = std::numeric_limits<float>::lowest();
    m_minValueY = std::numeric_limits<float>::max();
    m_maxValueY = std::numeric_limits<float>::lowest();
    m_minValueZ = std::numeric_limits<float>::max();
    m_maxValueZ = std::numeric_limits<float>::lowest();
	m_isValid = false;
	
    m_fieldDimensionY = m_fieldRadius*2;
    m_fieldDimensionZ = m_fieldRadius*2;
    m_bottomZ = m_hubheight - m_fieldRadius;

    m_pointsPerSideZ = m_pointsPerSideY;

	m_cancelCalculation = cancelCalculation;

    /* m_meanWindSpeedAtHub */
    if (m_profileModel == LOG) {
        // calculated with log wind profile.
        m_meanWindSpeedAtHub = m_meanWindSpeed * log((m_hubheight+0) / m_roughnessLength) / log(m_windSpeedMeasurementHeight / m_roughnessLength);
    }
    else if (m_profileModel == PL) {
        // calculated with power law wind profile.
        m_meanWindSpeedAtHub = m_meanWindSpeed * pow (m_hubheight/m_windSpeedMeasurementHeight,m_shearExponent);
    }
    else {
        m_meanWindSpeedAtHub = m_meanWindSpeed;
    }

    m_simulationTime = m_assignedSimulationTime*1.05 + m_fieldDimensionY / m_meanWindSpeedAtHub;
    m_numberOfTimesteps = m_simulationTime / m_assignedTimeStep + 1;
	
    /* m_yCoordinates */
    const float deltaY = m_fieldDimensionY / (m_pointsPerSideY-1);
	//qDebug() << "deltaYZ: " << deltaYZ;
    m_yCoordinates = new float[m_pointsPerSideY];
    for (int i = 0; i < m_pointsPerSideY; ++i) {
        m_yCoordinates[i] = -m_fieldDimensionY/2 + i*deltaY;
        //qDebug() << "yzCoordinates: " << m_yCoordinates[j];
	}

    const float deltaZ = m_fieldDimensionZ / (m_pointsPerSideZ-1);
    m_zCoordinates = new float[m_pointsPerSideZ];
    for (int i = 0; i < m_pointsPerSideZ; ++i) {
        m_zCoordinates[i] = -m_fieldDimensionZ/2 + i*deltaZ;
        //qDebug() << "yzCoordinates: " << m_yCoordinates[j];
    }
	
    /* m_yCoordinatesNormalize */
    m_yCoordinatesNormalized = new float[m_pointsPerSideY];
    for (int i = 0; i < m_pointsPerSideY; ++i) {
        m_yCoordinatesNormalized[i] = m_yCoordinates[i] * 4 / m_fieldDimensionY;
	}	

    m_zCoordinatesNormalized = new float[m_pointsPerSideZ];
    for (int i = 0; i < m_pointsPerSideZ; ++i) {
        m_zCoordinatesNormalized[i] = m_zCoordinates[i] * 4 / m_fieldDimensionZ;
    }
	
	/* m_timeAtTimestep */
	const float deltaT = m_simulationTime/(m_numberOfTimesteps-1);
	//qDebug() << "delta t: " << deltaT;
	m_timeAtTimestep = new float[m_numberOfTimesteps];
	for (int i = 0; i < m_numberOfTimesteps; ++i) {
		m_timeAtTimestep[i] = i * deltaT;
	}

	/* m_meanWindSpeedAtHeigth */
    m_meanWindSpeedAtHeigth = new float[m_pointsPerSideY];
    for (int i = 0; i < m_pointsPerSideY; ++i) {
        if (m_profileModel == LOG) {
			// calculated with log wind profile. Should not be used with heigth above 100m (see wikipedia)
            m_meanWindSpeedAtHeigth[i] = m_meanWindSpeed * log((m_hubheight+m_yCoordinates[i]) / m_roughnessLength) / log(m_windSpeedMeasurementHeight / m_roughnessLength);
        }
        else if (m_profileModel == PL) {
            // calculated with power law wind profile.
            m_meanWindSpeedAtHeigth[i] = m_meanWindSpeed * pow ((m_hubheight+m_yCoordinates[i])/m_windSpeedMeasurementHeight,m_shearExponent);
        }
        else {
			m_meanWindSpeedAtHeigth[i] = m_meanWindSpeed;
		}
	}
	
	/* m_resultantVelocity */
    m_resultantVelocity = new Vec3i**[m_pointsPerSideZ];
    for (int z = 0; z < m_pointsPerSideZ; ++z) {
        m_resultantVelocity[z] = new Vec3i*[m_pointsPerSideY];
        for (int y = 0; y < m_pointsPerSideY; ++y) {
			// empty paranthesis initialize the whole new array with 0
            m_resultantVelocity[z][y] = new Vec3i[m_numberOfTimesteps] ();
		}
	}
}


WindField::~WindField() {
//	glDeleteLists(m_glListIndex, 1);
    delete [] m_yCoordinates;
    delete [] m_yCoordinatesNormalized;
	delete [] m_timeAtTimestep;
	delete [] m_meanWindSpeedAtHeigth;
	
    for (int z = 0; z < m_pointsPerSideZ; ++z) {
        for (int y = 0; y < m_pointsPerSideY; ++y) {
			delete [] m_resultantVelocity[z][y];
		}
		delete [] m_resultantVelocity[z];
	}
	delete [] m_resultantVelocity;
}

void WindField::calculateWindField() {
	/* The turbulent windfield calculation is based on the model of Veers. To understand the following code
     * it is essential to read the Sandia report "Three-Dimensional Wind Simulation", 1988, or review
	 * Chapter 14 of "Aerodynamics of Wind Turbines 2nd edition" from M. O.L. Hansen.
	 *
	 * This functions creates a 3 dimensional matrix, where the first 2 dimensions refer to the points in
	 * space, and the third dimension is the time. The spatial distribution of the points is equidistant and
	 * square, expressed in a cartesian coordinate system with it's point of origin in the middle of the
	 * windfield.
	 * The windfield is divided into jxk (j=k) points in space. The points are numbered like this (view from
	 * the front to the turbine):
	 *   7 8 9
	 *   4 5 6
	 *   1 2 3
	 * The coordinate (so z is the heigth):
	 *  z ^
	 *    |
	 *    | --> y
	 * */
	
	int j;  // j and k refer both to all discrete points of the windfield
	int k;
	int m;  // refers to all the frequencies
	float sum;  // used for several summations
	
    const int pointsInTotal = m_pointsPerSideZ * m_pointsPerSideY;  // total number of points in windflied
	const int numberOfFrequencies = m_numberOfTimesteps / 2;  // see Hansen p. 152
	const float deltaF = 1 / m_simulationTime;  // frequency steps in [Hz]
		
	float* frequency;  // contains all calculated N/2 frequencies
	
	/* Matrix H: According to the number of points this Matrix can get very big. There shouldn't be more
	 * than around 100 points in one direction, as the size of this matrix is 100^2 x 100^2 ( /2, as the
	 * matrix is lower triangular).
	 * The Matrix H represents the weighted factors for the linear combination of N independant,
	 * unit-magnitude, white noise inputs, that will yield in N correlated outputs with the correct spectral
	 * matrix. Each row of H gives the contributions of all the inputs to the outputpoint at k.
	 * Each column gives the contributions of the j^(th) input to all of the outputs
	 * */
	float **H;
	
	/* Matrix S is the spectral matrix. The diagonals of S are the PSDs. Each off-diagonal term S_jk is
	 * the cross spectral density between points j and k.
	 * To save memory there is only need for the k inputs (columns) for each j (row). Therefore S_j is
	 * only a 1D Vector foreach current j. Additionally there are the diagonal terms needed
	 * */
	float *S_j  = NULL;
	float *S_diagonal = NULL;
	
	/* Check Hansen for additional information */
	float **amplitude = NULL;
	float **phi = NULL;
	
	/* Random matrix */
	float **random = NULL;
    srand (m_seed);
	//srand (0);  // for testing: gives always the same sequence of random numbers
	
	/* In Veers a factor deltaF/2 is used to normalize the PSD, while in Hansen the integral of
	 * the PSD over all calculated frequencys must be one. In general Hansens method should be
	 * more accurate but at all test deltaF/2 made the resultant turbulense intensity to fit better
	 * with the value in the setup
	 * */
	float *psdNormalizationFactor = NULL;
	
	
	/* * * * * * allocate thread shared memory * * * * * */
	frequency = new float[numberOfFrequencies];
	for (m = 0; m < numberOfFrequencies; ++m) {
		frequency[m] = (m+1) / m_simulationTime;
	}
	
	amplitude = new float*[pointsInTotal];
	for (j = 0; j < pointsInTotal; ++j) {
		amplitude[j] = new float[numberOfFrequencies] ();
	}
	
	phi = new float*[pointsInTotal];
	for (j = 0; j < pointsInTotal; ++j) {
		phi[j] = new float[numberOfFrequencies] ();
	}
	
	random = new float*[pointsInTotal];
	for (j = 0; j < pointsInTotal; ++j) {
		random[j] = new float[numberOfFrequencies];
		for (m = 0; m < numberOfFrequencies; ++m) {
            random[j][m] = (rand()*1.0)/RAND_MAX * 2 * PI_;  // values from 0 to 2*Pi
		}
	}
	
    psdNormalizationFactor = new float[m_pointsPerSideZ];
    for (int zIndex = 0; zIndex < m_pointsPerSideZ; ++zIndex) {
//		sum = 0;
//		for (m = 0; m < numberOfFrequencies; ++m) {
//			sum += getPSD(frequency[m], zIndex);
//		}
//		psdNormalizationFactor[zIndex] = 1 / sum;
		psdNormalizationFactor[zIndex] = deltaF / 2;
//		qDebug() << "deltaF/2: " << deltaF/2 << " factor: " << psdNormalizationFactor[zIndex];
    }

    #pragma omp parallel private (j, k, sum, S_j, S_diagonal, H) shared (frequency, random, amplitude, phi, psdNormalizationFactor)
    {
		/* * * * * * allocate thread private memory * * * * * */
		int j_y;  // the column in the windfield of point j
		int j_z;  // the row (or height) in the windfield of point j
		int k_y;
		int k_z;
		int l;  // refers to the column count within the H matrix
		float Re;
		float Im;
		
		S_j = new float[pointsInTotal] ();
		S_diagonal = new float[pointsInTotal] ();
		
		H = new float*[pointsInTotal];
		for (j = 0; j < pointsInTotal; ++j) {
			H[j] = new float[j+1] ();  // lower triangular matrix
        }

		/* * * * * * calculation * * * * * */
        #pragma omp for
		for (m = 0; m < numberOfFrequencies; ++m) {  // independent loop, therefore parallelized
			j_z = 0; j_y = 0;
			for (j = 0; j < pointsInTotal && ! m_cancelCalculation; ++j) {
				if (j_y == 0) {  // calculate new PSD only at new height
					S_diagonal[j] = getPSD(frequency[m], j_z) * psdNormalizationFactor[j_z];
				} else {  // otherwise take the last one, because it's the same
					S_diagonal[j] = S_diagonal[j-1];
				}
				
				k_z = 0; k_y = 0;
				Re = 0; Im = 0;
				for (k = 0; k <= j; ++k) {
					if (j != k) {  // calculate S_jk
                        S_j[k] = getCoh (frequency[m], getDist(m_yCoordinates[j_y], m_zCoordinates[j_z],
                                                               m_yCoordinates[k_y], m_zCoordinates[k_z] )
																	) * sqrt(S_diagonal[j] * S_diagonal[k]);
					} else {  // calculate S_kk
						S_j[k] = S_diagonal[k];
					}
					sum = 0;
					if (j != k) {  // calculate H_jk
						for (l = 0; l <= k-1; ++l) {
							sum = H[j][l]*H[k][l] + sum;
						}
						H[j][k] = (S_j[k] - sum) / H[k][k];
					} else {  // calculate H_kk
						for (l = 0; l <= k-1; ++l) {
							sum = pow(H[k][l],2) + sum;
						}
						H[k][k] = sqrt(S_j[k] - sum);
					}
					
					Re = Re + (H[j][k]*cos(random[k][m]));
					Im = Im + (H[j][k]*sin(random[k][m]));
					++k_y;
                    if (k_y == m_pointsPerSideY) {
						k_y = 0;
						++k_z;
					}
				}  // for k
				
				amplitude[j][m] = sqrt (pow(Re,2) + pow(Im,2));
				phi[j][m] = atan2 (Im, Re);
				
				++j_y;
                if (j_y == m_pointsPerSideY) {
					j_y = 0;
					++j_z;
				}
			}  // for j
		}  // for m
		
		/* * * * * * free thread private memory * * * * * */
		delete [] S_j;
		delete [] S_diagonal;
		for (j = 0; j < pointsInTotal; ++j) {
			delete [] H[j];
		}
		delete [] H;
    }  // omp parallel END


    Vec3f*** tempVelocity = new Vec3f**[m_pointsPerSideZ];
    for (int z = 0; z < m_pointsPerSideZ; ++z) {
        tempVelocity[z] = new Vec3f*[m_pointsPerSideY];
        for (int y = 0; y < m_pointsPerSideY; ++y) {
            tempVelocity[z][y] = new Vec3f[m_numberOfTimesteps];
        }
    }

	/* * * * * * superposition of frequencies * * * * * */
	if (! m_cancelCalculation)
	{
		int z = 0;  // the row (or height) in the windfield
		int y = 0;  // the column in the windfield
		int t = 0;  // refers to the timesteps
		for (j = 0; j < pointsInTotal && ! m_cancelCalculation; ++j) {  // for every point j
			for (t = 0; t < m_numberOfTimesteps; ++t) {  // for every timestep t
				sum = 0;
				for (m = 0; m < numberOfFrequencies; ++m) {  // for every frequency m
                    sum = sum + (2*amplitude[j][m]*cos(2*PI_*frequency[m]*m_timeAtTimestep[t]-phi[j][m]));
				}
                tempVelocity[z][y][t].x = m_meanWindSpeedAtHeigth[z] + sum;  // store final result
                tempVelocity[z][y][t].y = 0;
                tempVelocity[z][y][t].z = 0;
				
				/* find the max and min value for the windfield */
                if (tempVelocity[z][y][t].x < m_minValueX) {
                    m_minValueX = tempVelocity[z][y][t].x;
				}
                if (tempVelocity[z][y][t].x > m_maxValueX) {
                    m_maxValueX = tempVelocity[z][y][t].x;
				}
			}

			++y;
            if (y == m_pointsPerSideY) {
				y = 0;
				++z;
			}
		}
    }

    const float valueRangeX = m_maxValueX - m_minValueX;
    vslopeX = 65535 / valueRangeX;
    vinterceptX = -32768 - vslopeX*m_minValueX;

    m_maxValueY = 1;
    m_minValueY = -1;
    const float valueRangeY = m_maxValueY - m_minValueY;
    vslopeY = 65535 / valueRangeY;
    vinterceptY = -32768 - vslopeY*m_minValueY;

    m_maxValueZ = 1;
    m_minValueZ = -1;
    const float valueRangeZ = m_maxValueZ - m_minValueZ;
    vslopeZ = 65535 / valueRangeZ;
    vinterceptZ = -32768 - vslopeZ*m_minValueZ;

    // here we are converting the computed velocity values into the qint16 format to save memory
    if (! m_cancelCalculation)
    {
        int z = 0;  // the row (or height) in the windfield
        int y = 0;  // the column in the windfield
        int t = 0;  // refers to the timesteps
        for (j = 0; j < pointsInTotal && ! m_cancelCalculation; ++j) {  // for every point j
            for (t = 0; t < m_numberOfTimesteps; ++t) {  // for every timestep t

                m_resultantVelocity[z][y][t].x = tempVelocity[z][y][t].x*vslopeX+vinterceptX;  // store final result
                m_resultantVelocity[z][y][t].y = tempVelocity[z][y][t].y*vslopeY+vinterceptY;
                m_resultantVelocity[z][y][t].z = tempVelocity[z][y][t].z*vslopeZ+vinterceptZ;
            }

            ++y;
            if (y == m_pointsPerSideY) {
                y = 0;
                ++z;
            }
        }
    }
	
	
	/* * * * * * free thread shared memory * * * * * */
	delete [] frequency;
	delete [] psdNormalizationFactor;
	
	for (j = 0; j < pointsInTotal; ++j) {
		delete [] amplitude[j];
	}
	delete [] amplitude;
	
	for (j = 0; j < pointsInTotal; ++j) {
		delete [] phi[j];
	}
	delete [] phi;
	
	for (j = 0; j < pointsInTotal; ++j) {
		delete [] random[j];
	}
    delete [] random;

    for (int z = 0; z < m_pointsPerSideZ; ++z) {
        for (int y = 0; y < m_pointsPerSideY; ++y) {
            delete [] tempVelocity[z][y];
        }
        delete [] tempVelocity[z];
    }
    delete [] tempVelocity;

	/* * * * * * finish calculation * * * * * */
	if (! m_cancelCalculation) {
		m_isValid = true;
	}

    //if (m_isValid) PrepareGraphData();

}

//void WindField::PrepareGraphData(){
//
//    m_availableWindfieldVariables.clear();
//    m_WindfieldGraphData.clear();
//
//    m_availableWindfieldVariables.append("Time [s]");
//    m_availableWindfieldVariables.append("Hub Height Velocity Abs [m/s]");
//    m_availableWindfieldVariables.append("Hub Height X Velocity [m/s]");
//    m_availableWindfieldVariables.append("Hub Height Y Velocity [m/s]");
//    m_availableWindfieldVariables.append("Hub Height Z Velocity [m/s]");
//
//    for (int i=0;i<m_probeLocations.size();i++){
//        m_availableWindfieldVariables.append("Probe ("+QString().number(m_probeLocations.at(i).x,'f',1)+","+QString().number(m_probeLocations.at(i).y,'f',1)+","+QString().number(m_probeLocations.at(i).z,'f',1)+") Abs Velocity [m/s]");
//        m_availableWindfieldVariables.append("Probe ("+QString().number(m_probeLocations.at(i).x,'f',1)+","+QString().number(m_probeLocations.at(i).y,'f',1)+","+QString().number(m_probeLocations.at(i).z,'f',1)+") X Velocity [m/s]");
//        m_availableWindfieldVariables.append("Probe ("+QString().number(m_probeLocations.at(i).x,'f',1)+","+QString().number(m_probeLocations.at(i).y,'f',1)+","+QString().number(m_probeLocations.at(i).z,'f',1)+") Y Velocity [m/s]");
//        m_availableWindfieldVariables.append("Probe ("+QString().number(m_probeLocations.at(i).x,'f',1)+","+QString().number(m_probeLocations.at(i).y,'f',1)+","+QString().number(m_probeLocations.at(i).z,'f',1)+") Z Velocity [m/s]");
//    }
//
//    QVector<float> time, ABShubHeightVelocity,XhubHeightVelocity,YhubHeightVelocity,ZhubHeightVelocity;
//
//    for (int i=0;i<m_numberOfTimesteps;i++){
//        time.append(i*m_assignedTimeStep);
//        Vec3 velocity = getWindspeed(Vec3(0,0,m_hubheight),i*m_assignedTimeStep,false,false,0.0);
//        ABShubHeightVelocity.append(velocity.VAbs());
//        XhubHeightVelocity.append(velocity.x);
//        YhubHeightVelocity.append(velocity.y);
//        ZhubHeightVelocity.append(velocity.z);
//    }
//
//    m_WindfieldGraphData.append(time);
//    m_WindfieldGraphData.append(ABShubHeightVelocity);
//    m_WindfieldGraphData.append(XhubHeightVelocity);
//    m_WindfieldGraphData.append(YhubHeightVelocity);
//    m_WindfieldGraphData.append(ZhubHeightVelocity);
//
//    for (int j=0;j<m_probeLocations.size();j++){
//        QVector<float> abs,x,y,z;
//
//        for (int i=0;i<m_numberOfTimesteps;i++){
//
//            Vec3 velocity = getWindspeed(m_probeLocations.at(j),i*m_assignedTimeStep,false,false,0.0);
//            abs.append(velocity.VAbs());
//            x.append(velocity.x);
//            y.append(velocity.y);
//            z.append(velocity.z);
//        }
//
//        m_WindfieldGraphData.append(abs);
//        m_WindfieldGraphData.append(x);
//        m_WindfieldGraphData.append(y);
//        m_WindfieldGraphData.append(z);
//    }
//}

//void WindField::AddProbe(Vec3 location){
//
//    bool found = false;
//    for (int i=0;i<m_probeLocations.size();i++)
//        if (m_probeLocations[i] == location) found = true;
//
//    if (!found) m_probeLocations.append(location);
//
//    PrepareGraphData();
//
//
//}

//void WindField::DeleteProbe(int index){
//
//    if (index < m_probeLocations.size()) m_probeLocations.removeAt(index);
//
//    PrepareGraphData();
//
//}

Vec3 WindField::getWindspeed(Vec3 vec, double time, bool mirror, bool isAutoFielShift, double shiftTime){
    double z,y;
    z = vec.z;
    y = vec.y;

    z -= m_bottomZ;
    y += m_fieldDimensionY/2;

    //here the windfield is marched trhough the domain with the hub height wind speed. initially it is marched through the domain for half a windfield diameter

    if (isAutoFielShift) time += (m_fieldDimensionY/2.0 - vec.x) / m_meanWindSpeedAtHub;
    else time += shiftTime;

    if (time < 0) time = 0;

    //mirror windfield, windfields are mirrored at the ends and then pieced together

    if (mirror){
        time = fabs(time);

        while (time > 2.0*m_simulationTime)
            time -= 2.0*m_simulationTime;


        if (time > m_simulationTime)
            time = 2.0*m_simulationTime - time;

    }
    else{
        while (time > m_simulationTime)
            time -= m_simulationTime;

    }

    //z is constant above and below the field dimensions
    if ( z > m_fieldDimensionZ) z = m_fieldDimensionZ;
    if ( z < 0) z = 0;

    //y is mirrored at the bounds
    y = fabs(y);

    while (y > 2.0*m_fieldDimensionY){
        y -= 2.0*m_fieldDimensionY;
    }

    if (y > m_fieldDimensionY){
        y = 2.0*m_fieldDimensionY - y;
    }


    {

        // start interpolation
        double spatialwidthY = m_fieldDimensionY / (m_pointsPerSideY-1);
        double spatialwidthZ = m_fieldDimensionZ / (m_pointsPerSideZ-1);
        double temporalwidth = m_simulationTime / (m_numberOfTimesteps-1);

        int zindex = floor(z / spatialwidthZ);
        int yindex = floor(y / spatialwidthY);
        int tindex = floor(time / temporalwidth);
        
        if (tindex > (m_numberOfTimesteps-2)){
            time = m_simulationTime;
            tindex = (m_numberOfTimesteps-2);
        }

        if (zindex > (m_pointsPerSideZ-2)){
            zindex = (m_pointsPerSideZ-2);
        }

        if (yindex > (m_pointsPerSideY-2)){
            yindex = (m_pointsPerSideY-2);
        }
        
        Vec3f mZYfloorTfloor, mZYceiltTfloor, mZYfloorTceil, mZYceiltTceil;
        
        mZYfloorTfloor.x = convertX(m_resultantVelocity[zindex][yindex][tindex].x)+(convertX(m_resultantVelocity[zindex+1][yindex][tindex].x)-convertX(m_resultantVelocity[zindex][yindex][tindex].x))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYfloorTfloor.y = convertY(m_resultantVelocity[zindex][yindex][tindex].y)+(convertY(m_resultantVelocity[zindex+1][yindex][tindex].y)-convertY(m_resultantVelocity[zindex][yindex][tindex].y))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYfloorTfloor.z = convertZ(m_resultantVelocity[zindex][yindex][tindex].z)+(convertZ(m_resultantVelocity[zindex+1][yindex][tindex].z)-convertZ(m_resultantVelocity[zindex][yindex][tindex].z))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        
        mZYceiltTfloor.x = convertX(m_resultantVelocity[zindex][yindex+1][tindex].x)+(convertX(m_resultantVelocity[zindex+1][yindex+1][tindex].x)-convertX(m_resultantVelocity[zindex][yindex+1][tindex].x))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYceiltTfloor.y = convertY(m_resultantVelocity[zindex][yindex+1][tindex].y)+(convertY(m_resultantVelocity[zindex+1][yindex+1][tindex].y)-convertY(m_resultantVelocity[zindex][yindex+1][tindex].y))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYceiltTfloor.z = convertZ(m_resultantVelocity[zindex][yindex+1][tindex].z)+(convertZ(m_resultantVelocity[zindex+1][yindex+1][tindex].z)-convertZ(m_resultantVelocity[zindex][yindex+1][tindex].z))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        
        Vec3f meanTfloor = mZYfloorTfloor+Vec3f(mZYceiltTfloor-mZYfloorTfloor)*(y-spatialwidthY*yindex)/spatialwidthY;
        
        mZYfloorTceil.x = convertX(m_resultantVelocity[zindex][yindex][tindex+1].x)+(convertX(m_resultantVelocity[zindex+1][yindex][tindex+1].x)-convertX(m_resultantVelocity[zindex][yindex][tindex+1].x))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYfloorTceil.y = convertY(m_resultantVelocity[zindex][yindex][tindex+1].y)+(convertY(m_resultantVelocity[zindex+1][yindex][tindex+1].y)-convertY(m_resultantVelocity[zindex][yindex][tindex+1].y))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYfloorTceil.z = convertZ(m_resultantVelocity[zindex][yindex][tindex+1].z)+(convertZ(m_resultantVelocity[zindex+1][yindex][tindex+1].z)-convertZ(m_resultantVelocity[zindex][yindex][tindex+1].z))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        
        mZYceiltTceil.x = convertX(m_resultantVelocity[zindex][yindex+1][tindex+1].x)+(convertX(m_resultantVelocity[zindex+1][yindex+1][tindex+1].x)-convertX(m_resultantVelocity[zindex][yindex+1][tindex+1].x))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYceiltTceil.y = convertY(m_resultantVelocity[zindex][yindex+1][tindex+1].y)+(convertY(m_resultantVelocity[zindex+1][yindex+1][tindex+1].y)-convertY(m_resultantVelocity[zindex][yindex+1][tindex+1].y))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        mZYceiltTceil.z = convertZ(m_resultantVelocity[zindex][yindex+1][tindex+1].z)+(convertZ(m_resultantVelocity[zindex+1][yindex+1][tindex+1].z)-convertZ(m_resultantVelocity[zindex][yindex+1][tindex+1].z))*(z-spatialwidthZ*zindex)/spatialwidthZ;
        
        Vec3f meanTceil = mZYfloorTceil+Vec3f(mZYceiltTceil-mZYfloorTceil)*(y-spatialwidthY*yindex)/spatialwidthY;
        
        
        Vec3f Vint = meanTfloor+Vec3f(meanTceil-meanTfloor)*(time-temporalwidth*tindex)/temporalwidth;
        
        return Vec3(Vint.x,Vint.y,Vint.z);
    }
}

float WindField::getDist (const float y1, const float z1, const float y2, const float z2) {
	const float dy = (y1-y2);
	const float dz = (z1-z2);
	
	if (dy != 0 && dz != 0) {
		return sqrt(dy*dy + dz*dz);
	} else if (dz != 0) {  // therefore dy must be 0
		return dz;
	} else if (dy != 0) {
		return dy;
	} else {
		return 0;
	}
}

float WindField::getCoh(const float frequency, const float spatialDistance) {
	/* Coherence function according to Frost.
	 * The coherence decrement C is set to 12 as Hansen suggested.
	 * */
	return exp(-12 * frequency * spatialDistance / m_meanWindSpeed);  // meanWindSpeed not depending on height?
}

float WindField::getPSD (const float frequency, const int zIndexOfPoint) {
    const float heigthAboveGround = m_hubheight + m_zCoordinates[zIndexOfPoint];
	float l;
	if (heigthAboveGround <= 30) {
		l = heigthAboveGround*20;
	} else {
		l = 600;
	}
	
	/* PSD function after Kaimal as in Hansen p. 149 */
	const float turbulenceDecimal = m_turbulenceIntensity / 100;
	return ( turbulenceDecimal*turbulenceDecimal * m_meanWindSpeedAtHeigth[zIndexOfPoint] * l ) /
			( pow((1 + frequency * 1.5 * l / m_meanWindSpeedAtHeigth[zIndexOfPoint]), (5.0/3.0)) );
}
