/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef CRPSSEALABDATA_H
#define CRPSSEALABDATA_H

#include "RPSSeaLabAPIdefines.h"
#include <Mod/SeaLabAPI/App/SeaLabFeature.h>
#include <App/PropertyContainer.h>
#include <App/PropertyStandard.h>
#include <Mod/SeaLabAPI/SeaLabAPIGlobal.h>
#include <Base/SmartPtrPy.h>
#include <App/PropertyUnits.h>

#include "RPS.h"

#include <QString>

namespace SeaLabAPI
{
class RPS_CORE_API SeaLabSimulationData : public SeaLabAPI::SeaLabFeature
{
	PROPERTY_HEADER_WITH_OVERRIDE(SeaLabAPI::SeaLabFeature);

 public:

	// Constructor
	SeaLabSimulationData();

	// Destructor
	~SeaLabSimulationData();

	// The Number of process
	App::PropertyInteger numberOfSpatialPosition;

	// The number of frequency increments
	App::PropertyInteger numberOfFrequency;

	// The Number of sample
	App::PropertyInteger numberOfSample;
    App::PropertyInteger sampleIndex;

	// motion Direction
    App::PropertyEnumeration direction;

	// Nunber of time instant
	App::PropertyInteger numberOfTimeIncrements;

	App::PropertyInteger locationJ;

	App::PropertyInteger locationK;

	App::PropertyInteger frequencyIndex;

	App::PropertyInteger directionIndex;

	App::PropertyInteger timeIndex;

	// Nunber of time lags
	App::PropertyInteger numberOfTimeLags;

	//comparison type: 1 for accuracy, 2 for time and 3 for memory
	App::PropertyInteger comparisonType;

	App::PropertyInteger numberOfWaveLengthIncrements;

	App::PropertyInteger numberOfDirectionIncrements;

	App::PropertyInteger waveLengthIndex;

    App::PropertyInteger numberOfIncrementOfVariableX;

    App::PropertyInteger indexOfVariableX;

	// Stationarity
	App::PropertyBool stationarity;

	// Stationarity
	App::PropertyBool gaussianity;

	// whether we are doing comparison or not
	App::PropertyBool  comparisonMode;

	// simulation successfull or not flag
	App::PropertyBool isSimulationSuccessful;

	App::PropertyBool isInterruptionRequested;
	
	App::PropertyBool uniformModulation;

	App::PropertyTime minTime;
    App::PropertyTime maxTime;
    App::PropertyTime timeIncrement;
    App::PropertyFrequency minFrequency;
    App::PropertyFrequency frequencyIncrement;
    App::PropertyFrequency maxFrequency;
    App::PropertyLength minWaveLength;
    App::PropertyLength maxWaveLength;
    App::PropertyLength waveLengthIncrement;
    App::PropertyAngle minDirection;
    App::PropertyAngle maxDirection;
    App::PropertyAngle directionIncrement;

	App::PropertyFloat incrementOfVariableX;

    App::PropertyFloat minVariableX;

	// The selected spatial distribution
	App::PropertyString spatialDistribution;

	// The selected shear velocity
	App::PropertyString shearVelocity;

	// The selected mean wind profile
	App::PropertyString meanFunction;

	// The selected frequency spectrum
	App::PropertyString frequencySpectrum;

	// The selected directional spectrum
	App::PropertyString directionalSpectrum;

	// The selected directional spreading function
	App::PropertyString directionalSpreadingFunction;

	// The selected coherence function
	App::PropertyString coherenceFunction;

	// Selected simulation method
	App::PropertyString simulationMethod;

	// Selected Simulation
	App::PropertyString frequencyDistribution;

	// Selected CPSD Decomposition Method
	App::PropertyString cpsdDecompositionMethod;

	// Selected randomness
	App::PropertyString randomnessProvider;

	// Selected Modulation function model
	App::PropertyString modulationFunction;

	// Selected correlation function model
	App::PropertyString correlationFunction;

	// Selected variance model
	App::PropertyString varianceFunction;

	// table tool name
	App::PropertyString tableTool;

	// matrix tool name
	App::PropertyString matrixTool;

	// user defined feature name
	App::PropertyString userDefinedRPSObject;

	// Selected comparison category
	App::PropertyString comparisonCategory;

   App::PropertyString cumulativeProbabilityDistribution;
   App::PropertyString kurtosis;
   App::PropertyString peakFactor;
   App::PropertyString probabilityDensityFunction;
   App::PropertyString shearVelocityOfFlow;
   App::PropertyString skewness;
   App::PropertyString standardDeviation;
   App::PropertyString variance;
   App::PropertyString wavePassageEffect;
   App::PropertyPath workingDirectoryPath;
   App::PropertyString fileName;
   App::PropertyInteger numberOfGridPointsAlongX;
   App::PropertyInteger numberOfGridPointsAlongY;
   App::PropertyLength gridSpacingAlongX;
   App::PropertyLength gridSpacingAlongY;
   App::PropertyLength gridLengthAlongX;
   App::PropertyLength gridLengthAlongY;

   /** @name methods override feature */
//@{
   virtual short mustExecute() const override;
   //@}
    virtual PyObject* getPyObject() override;

   /// python object of this class
   protected:// attributes
   Py::SmartPtr PythonObject;

   protected:
	/// recompute only this object
	virtual App::DocumentObjectExecReturn* recompute() override;
	/// recalculate the feature
	virtual App::DocumentObjectExecReturn* execute() override;
	virtual void onChanged(const App::Property* prop) override;

};

} //namespace SeaLabAPI

#endif  // CRPSSEALABDATA_H



