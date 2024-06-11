/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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


#ifndef APP_SIMULATION_H
#define APP_SIMULATION_H

#include <list>
#include <string>
#include "DocumentObjectGroup.h"
#include <Base/SmartPtrPy.h>


namespace App {

class WindLabSimulationObserver;

enum SimulationStatus {
    Failed = 0,
    Successfull = 1,
    Running = 2,
    Completed = 3,
    Stopped = 4
};

/**
 * This is the base class for the simulation facility. Each random phenomenon can provide its own
 * simulation implementation. The simulation defines which rps objects (such as spectrum, coherence function,
 * modulation functions, ...) needed for the current simulation.
 * @author Koffi Daniel
 */
class AppExport Simulation : public App::DocumentObjectGroup
{
    PROPERTY_HEADER(App::Simulation);

public:
    /** Constructs a simulation object. */
    Simulation();
    virtual ~Simulation();

    App::PropertyBool isRunning;
    void onChanged(const App::Property* prop) override;

    /**
     * Returns the name of the simulation object.
     */
    std::string name() const;
    /**
     * Set the name to the simulation object.
     */
    void setName(const std::string&);

    /**
     * run the simulation.
     */
    virtual bool run();

    virtual bool stop();

    //// Shows a list of all rps feature groups
    std::list<std::string> listRPSFeatureGroups() const;

    /// Shows a list of all feature groups and their features
    std::list<std::pair<std::string, std::list<std::string>>> getRPSFeatures() const;

    // get the name of the random phenomenon this simulation with produice
    virtual std::string getPhenomenonName() const;

    // get the name of the workbench that implement this simulation
    virtual std::string workbenchName() const;

    /// return the status bits
    unsigned long getStatus() const { return StatusBits.to_ulong(); }
    bool testStatus(SimulationStatus pos) const { return StatusBits.test((size_t)pos); }
    void setStatus(SimulationStatus pos, bool on) { StatusBits.set((size_t)pos, on); }
    bool isRuning() { return testStatus(App::Running); }
    bool isStopped() { return testStatus(App::Stopped); }
    bool isCompleted() { return testStatus(App::Completed); }
    bool isFailed() { return testStatus(App::Failed); }
    bool isSuccessfull() { return testStatus(App::Successfull); }
    virtual bool doubleClicked(void);

    virtual const char* getViewProviderName() const {
        return "App::ViewProviderSimulation";
    }

	virtual PyObject *getPyObject(void) override;

protected:
 
    std::bitset<32> StatusBits;

public:
    std::string _name;

/// python object of this class
protected: // attributes
    Py::SmartPtr PythonObject;
};

} // namespace Gui


#endif // APP_SIMULATION_H
