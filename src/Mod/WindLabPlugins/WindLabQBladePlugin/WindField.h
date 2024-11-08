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

#ifndef WINDFIELD_H
#define WINDFIELD_H

#include <QTextStream>
#include "Vec3f.h"
#include "Vec3.h"
#include <App/PropertyUnits.h>
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>


class WindField
{
public:

enum IEC{IEC61400_1Ed2,IEC61400_1Ed3,IEC61400_2Ed2,IEC61400_3_1Ed1,IEC61400_3_2Ed1,STEADY_POWER,PRESCRIBED_RPM};
enum SPECTRAL{IECKAI,IECVKM,GP_LLJ,NWTCUP,SMOOTH,WF_UPW,WF_07D,WF_14D,TIDAL,NONN};
enum ProfileType{PL,LOG,H2L,JET,IEC};

public:

	WindField(const WindLabAPI::WindLabSimuData& Data, const App::PropertyInteger& RandomPhaseSeed,
              const App::PropertyTime& SimulationTime, const App::PropertyTime& TimeStepSize,
              const App::PropertyLength& GridWidth,
              const App::PropertyInteger& GridPoints,
              const App::PropertyLength& HubHeight, const App::PropertySpeed& MeanWindSpeed,
              const App::PropertyEnumeration& ProfileModel,
              const App::PropertyLength& ReferenceHeight, const App::PropertyFloat& ShearExponent,
              const App::PropertyFloat& RoughnessLength,
              const App::PropertyFloat& TurbulenceIntensity, const App::PropertyLength& FieldRadius, bool cancelCalculation);

	~WindField();

    //void PrepareGraphData();
    QVector< QVector <float> > m_WindfieldGraphData;
    QStringList m_availableWindfieldVariables;
    QVector<Vec3> m_probeLocations;
	

    float convertX(qint16 x){return float(x-vinterceptX)/vslopeX;}
    float convertY(qint16 y){return float(y-vinterceptY)/vslopeY;}
    float convertZ(qint16 z){return float(z-vinterceptZ)/vslopeZ;}

    Vec3 getWindspeed(Vec3 vec, double time, bool mirror, bool isAutoFielShift, double shiftTime);
	
    float minValueX () { return m_minValueX; }
    float maxValueX () { return m_maxValueX; }
    float minValueY () { return m_minValueY; }
    float maxValueY () { return m_maxValueY; }
    float minValueZ () { return m_minValueZ; }
    float maxValueZ () { return m_maxValueZ; }
	bool isValid () { return m_isValid; }
	
	void calculateWindField();  // core method; calculates a valid windfield
	
public:

    //void AddProbe(Vec3 location);
    //void DeleteProbe(int index);
	
	float getDist(const float x1, const float y1, const float x2, const float y2);
	float getCoh(const float frequency, const float spatialDistance);
	float getPSD(const float frequency, const int zIndexOfPoint);
	
	/* control variables */

    float m_minValueX;  // the minimal velocity value that occures in the windfield over the whole time (X)
    float m_maxValueX;  // the maximal value ~ (X)

    float m_minValueY;  // the minimal velocity value that occures in the windfield over the whole time (X)
    float m_maxValueY;  // the maximal value ~ (X)

    float m_minValueZ;  // the minimal velocity value that occures in the windfield over the whole time (X)
    float m_maxValueZ;  // the maximal value ~ (X)

	bool m_isValid;  // set true, as soon as calculation is succsessfully finished
	bool m_cancelCalculation;  // a pointer to a bool that reacts on the progress dialog cancelation

    //bool m_bDefaultShear;
    /* new parameters needed for turb-sim windfields */
    int m_profileModel, m_seed;
    float m_shearExponent;
	
	/* geometric parameters */
    float m_fieldRadius;      // radius of the windfield (only used for square qblade constructed windfields) [m]
    float m_hubheight;        // hub height, shaft height of rotor [m]
    float m_fieldDimensionY;  // the y dimension [m]
    float m_fieldDimensionZ;  // the z dimension [m]
    float m_bottomZ;          // z coordinate at the bottom of the windfield [m]

	/* wind parameters */
	float m_meanWindSpeed;  // mean wind speed at reference heigth
	float m_turbulenceIntensity;  // turbulence intesity [% (0 to 100)]
	float m_roughnessLength;  // surface roughness
	float m_windSpeedMeasurementHeight;  // the heigth where the wind speed was measured
	
	/* calculation parameters */
    float m_simulationTime, m_assignedSimulationTime;  // simulation time in seconds
    float m_assignedTimeStep;
    int m_numberOfTimesteps;  // the windField is calculated for various timesteps (unsteady)
    int m_pointsPerSideY;  // number of points in y direction
    int m_pointsPerSideZ;  // number of points in z direction

	/* dynamic calculation results */
    float* m_yCoordinates;  // vector containg y values of windfield for rendering in simulations
    float* m_zCoordinates;  // vector containg x values of windfield for rendering in simulations

    float* m_yCoordinatesNormalized;  // to [-2,2] normalized coordinates for the plot
    float* m_zCoordinatesNormalized;  // to [-2,2] normalized coordinates for the plot

	float* m_timeAtTimestep;  // the discrete resolution of time
	float* m_meanWindSpeedAtHeigth;  // the windspeed for each point in heigth
	float m_meanWindSpeedAtHub;  // ~ for the hub heigth that might not be covered by a grid point
    Vec3i*** m_resultantVelocity;  // 3D array of velocity values at yz-position. Indizes: [z][y][time]

    float vslopeX, vinterceptX, vslopeY, vinterceptY, vslopeZ, vinterceptZ;

};

#endif // WINDFIELD_H
