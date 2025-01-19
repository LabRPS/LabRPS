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

#ifndef CRPSUSERLABDATA_H
#define CRPSUSERLABDATA_H

#include "RPSUserLabAPIdefines.h"
#include <Mod/UserLabAPI/App/UserLabFeature.h>
#include <App/PropertyContainer.h>
#include <App/PropertyStandard.h>
#include <Mod/UserLabAPI/UserLabAPIGlobal.h>
#include <Base/SmartPtrPy.h>
#include <App/PropertyUnits.h>
#include "RPS.h"

#include <QString>

namespace UserLabAPI
{
class RPS_CORE_API UserLabSimulationData : public UserLabAPI::UserLabFeature
{
	PROPERTY_HEADER_WITH_OVERRIDE(UserLabAPI::UserLabFeature);

 public:

	// Constructor
	UserLabSimulationData();

	// Destructor
	~UserLabSimulationData();

	// The Number of process
	App::PropertyInteger numberOfSpatialPosition;

	// The number of frequency increments
	App::PropertyInteger numberOfFrequency;

	// The Number of sample
	App::PropertyInteger numberOfSample;
    App::PropertyInteger sampleIndex;

	// Nunber of time instant
	App::PropertyInteger numberOfTimeIncrements;

	App::PropertyInteger locationJ;

	App::PropertyInteger locationK;

	App::PropertyInteger frequencyIndex;

	App::PropertyInteger directionIndex;

	App::PropertyInteger timeIndex;

	App::PropertyInteger numberOfTimeLags;

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

	// Selected simulation method
	App::PropertyString simulationMethod;

   App::PropertyPath workingDirectoryPath;

   App::PropertyString fileName;

   App::PropertyLength spatialCoordinateIncrement;
   App::PropertyLength spatialCoordinateMinimum;
   App::PropertyLength spatialCoordinatetMaximum;
   App::PropertyInteger numberOfSpatialCoordinateIncrement;
   App::PropertyInteger spatialCoordinateIndex;

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

} //namespace UserLabAPI

#endif  // CRPSUSERLABDATA_H



