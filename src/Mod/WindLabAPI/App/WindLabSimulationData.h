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

#ifndef CRPSWINDLABDATA_H
#define CRPSWINDLABDATA_H

#include "RPSWindLabAPIdefines.h"
#include <Mod/WindLabAPI/App/WindLabFeature.h>
#include <App/PropertyContainer.h>
#include <App/PropertyStandard.h>
#include <Mod/WindLabAPI/WindLabAPIGlobal.h>
#include <Base/SmartPtrPy.h>
#include <App/PropertyUnits.h>

#include "RPS.h"

#include <QString>

namespace WindLabAPI
{

/// The WindLab simulation data for random wind velocity
class RPS_CORE_API WindLabSimulationData : public WindLabAPI::WindLabFeature
{
	PROPERTY_HEADER_WITH_OVERRIDE(WindLabAPI::WindLabFeature);

 public:

    /// Construction
	WindLabSimulationData();

    /// Destruction
	~WindLabSimulationData();

 /** @name Properties */
    //@{
    /// The number of process (number of simulation)
	App::PropertyInteger numberOfSpatialPosition;

	/// The number of frequency increments
	App::PropertyInteger numberOfFrequency;

	/// The Number of sample
	App::PropertyInteger numberOfSample;

	/// Wind Direction
    App::PropertyEnumeration WindDirection;

	/// Nunber of time instant
	App::PropertyInteger numberOfTimeIncrements;

	/// A given location J among all the locations (simulation points)
	App::PropertyInteger locationJ;

	/// A given location K among all the locations (simulation points)
	App::PropertyInteger locationK;

	/// A given frequency increment index among all the frequency increments
	App::PropertyInteger frequencyIndex;

	/// A given direction increment index among all the direction increments
	App::PropertyInteger directionIndex;

	/// A given time increment index among all the time increments
	App::PropertyInteger timeIndex;

	/// Nunber of time lags for the computation of correlation
	App::PropertyInteger numberOfTimeLags;

	/// The comparison type: 1 for accuracy, 2 for compuation time and 3 for memory usage
	App::PropertyInteger comparisonType;

    /// Number of wave lengh increments
	App::PropertyInteger numberOfWaveLengthIncrements;

    /// Number of direction increments
	App::PropertyInteger numberOfDirectionIncrements;

	/// A given wave length increment index among all the wave length increments
	App::PropertyInteger waveLengthIndex;

    /// Number of increment for variable x 
    App::PropertyInteger numberOfIncrementOfVariableX;

	/// A given variable x increment index among all the variable x increments
    App::PropertyInteger indexOfVariableX;

	/// Specifies whether the stationary or non-stationary wind velocity is desired
	App::PropertyBool stationarity;

	/// Specifies whether the gaussian or non-gaussian wind velocity is desired
	App::PropertyBool gaussianity;

	/// Specifies whether we are in comparison  mode or not
	App::PropertyBool  comparisonMode;

	/// Specifies whether we are doing large scale simulation or not
	App::PropertyBool  largeScaleSimulationMode;

	/// The flag specfies simulation successfull or not
	App::PropertyBool isSimulationSuccessful;

	/// This flag tells whether simulation or computation should be interrupted.
	App::PropertyBool isInterruptionRequested;
	
	/// It tells whether non-stationarity should be acheived by time modulation.
	App::PropertyBool uniformModulation;

	/// Minimum time from which incrementation should start
	App::PropertyTime minTime;

    /// Maximum time allowed after all incrementation
    App::PropertyTime maxTime;

    /// the time increment value
    App::PropertyTime timeIncrement;
	
	/// Minimum frequency from which incrementation should start
    App::PropertyFrequency minFrequency;

    /// The frequency increment value
    App::PropertyFrequency frequencyIncrement;

    /// Maximum freqency allowed after all incrementation. The cutoff frequency.
    App::PropertyFrequency maxFrequency;

	/// Minimum wave length from which incrementation should start
    App::PropertyLength minWaveLength;

	/// Maximum wave length allowed after all incrementation.
    App::PropertyLength maxWaveLength;

	/// The wave length increment value
    App::PropertyLength waveLengthIncrement;

	/// Initial direction from which incrementation should start
    App::PropertyAngle minDirection;

	/// Maximum direction allowed after all incrementation.
    App::PropertyAngle maxDirection;

    /// The direction increment value
    App::PropertyAngle directionIncrement;

    /// The variable x increment value
	App::PropertyFloat incrementOfVariableX;

	/// Minimum value from which incrementation should start
    App::PropertyFloat minVariableX;

	/// The active spatial distribution name
	App::PropertyString spatialDistribution;

	/// The active shear velocity name
	App::PropertyString shearVelocity;

	/// The active mean wind profile name
	App::PropertyString meanFunction;

	/// The active along wind spectrum model name
	App::PropertyString alongWindSpectrumModel;

	/// The active vertical wind spectrum model name
	App::PropertyString verticalWindSpectrumModel;

	/// The active across wind spectrum model name
	App::PropertyString acrossWindSpectrumModel;

	// The active coherence function name
	App::PropertyString coherenceFunction;

	/// The active simulation method name
	App::PropertyString simulationMethod;

	/// The active frequency distribution name
	App::PropertyString frequencyDistribution;

	/// The active CPSD Decomposition Method name
	App::PropertyString cpsdDecompositionMethod;

	/// The active randomness provider name
	App::PropertyString randomnessProvider;

	/// The active Modulation function name
	App::PropertyString modulationFunction;

	/// The active correlation function name
	App::PropertyString correlationFunction;

	/// The active variance model name
	App::PropertyString varianceFunction;

	/// The active table tool name
	App::PropertyString tableTool;

	/// The active matrix tool name
	App::PropertyString matrixTool;

	/// The active user defined feature name
	App::PropertyString userDefinedRPSObject;

	/// The current comparison category
	App::PropertyString comparisonCategory;

	/// The active cumulative probability distribution
   App::PropertyString cumulativeProbabilityDistribution;

   	/// The active gust factor 
   App::PropertyString gustFactor;

   	/// The active kurtosis
   App::PropertyString kurtosis;

   	/// The active peak factor
   App::PropertyString peakFactor;

   	/// The active probability density function
   App::PropertyString probabilityDensityFunction;

   	/// The active terrain roughness
   App::PropertyString roughness;

   	/// The active flow shear velocity
   App::PropertyString shearVelocityOfFlow;

   	/// The active skewness
   App::PropertyString skewness;

   	/// The active standard deviation
   App::PropertyString standardDeviation;

   	/// The active turbulence intensity
   App::PropertyString turbulenceIntensity;

   	/// The active turbulence scale
   App::PropertyString turbulenceScale;

   	/// The active variance
   App::PropertyString variance;

   	/// The active wave passage effect
   App::PropertyString wavePassageEffect;

   /// The working directory. Wind velocity file generated in large scale mode is expected to be saved here. 
   App::PropertyPath workingDirectoryPath;

   /// The file name for the wind velocity file generated in large scale mode.
   App::PropertyString fileName;
    //@}

   /** @name methods override feature */
   //@{
   virtual short mustExecute() const override;
   virtual PyObject* getPyObject() override;
   //@}

   protected:// attributes

   /// python object of this class
   Py::SmartPtr PythonObject;

   protected:
	/// recompute only this object
	virtual App::DocumentObjectExecReturn* recompute() override;
	/// recalculate the feature
	virtual App::DocumentObjectExecReturn* execute() override;
	virtual void onChanged(const App::Property* prop) override;

};

} //namespace WindLabAPI

#endif  // CRPSWINDLABDATA_H



