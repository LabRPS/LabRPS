/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>          *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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

#ifndef WindLab_WindLabSimulationComparison_H
#define WindLab_WindLabSimulationComparison_H

#include <App/PropertyStandard.h>
#include <App/DocumentObject.h>
#include <Mod/WindLabAPI/App/WindLabFeature.h>
#include <App/PropertyUnits.h>
#include <Mod/WindLab/WindLabGlobal.h>
#include <Base/SmartPtrPy.h>

#include <Mod/WindLabAPI/App/WindLabSimuData.h>


namespace WindLab {

 class WindLabSimulationComparisonPy;// the python WindLabSimulationComparison class
 class WindLabSimulation;// the python WindLabSimulationComparison class

 class WindLabExport WindLabSimulationComparison: public App::DocumentObject
 {
    
    PROPERTY_HEADER(WindLab::WindLabSimulationComparison);

public:
    WindLabSimulationComparison();
    virtual ~WindLabSimulationComparison();
    void start();
    void stop();

public:
    virtual PyObject* getPyObject(void) override;

public:
    virtual bool doubleClicked(void);
    virtual void onChanged(const App::Property* prop);
    virtual const char* getViewProviderName() const
    {
        return "WindLabGui::ViewProviderWindLabSimulationComparison";
    }

public:
    App::PropertyString ComparisonGroup;
    App::PropertyString ComparisonMethod;
    App::PropertyString SimulationCandidate1;
    App::PropertyString SimulationCandidate2;
    App::PropertyString FeatureTypeCandidate1;
    App::PropertyString FeatureTypeCandidate2;
    App::PropertyString FeatureCandidate1;
    App::PropertyString FeatureCandidate2;
    App::PropertyPercent Accuracy;
    App::PropertyFloat ComputationTime1;
    App::PropertyFloat ComputationTime2;
    App::PropertyInteger MemoryUsage;


    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
	
};

} //namespace WindLab


#endif // WindLab_WindLabSimulationComparison_H
