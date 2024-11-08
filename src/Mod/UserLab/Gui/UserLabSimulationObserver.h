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


#ifndef APP_USERLABSIMULATIONOBSERVER_H
#define APP_USERLABSIMULATIONOBSERVER_H

#include <list>
#include <App/DocumentObserver.h>
#include <Gui/Tree.h>
#include <Mod/UserLab/UserLabGlobal.h>

namespace Gui
{
class Document;
class ViewProviderDocumentObject;
}// namespace Gui


namespace App
{
class Simulation;
}
namespace UserLabGui {


/**
 * The UserLabSimulationObserver class manages all simulation objects.
 * @author Werner Mayer
 */
class UserLabGuiExport UserLabSimulationObserver: public App::DocumentObserver
{
public:
    /** Creates the only instance of the UserLabSimulationObserver. */
    static UserLabSimulationObserver* instance();
    static void destruct();

    /** Searches for and returns an existing simulation object with name \a name. If no
     * such simulation exists then a simulation of class \a className gets created, if possible.
     * If the simulation cannot be created 0 is returned.
     */
    App::Simulation* createSimulation(const std::string& name, const std::string& className);
    /** Removes the simulation with name \a name. If there is no such
     * simulation exists nothing happens.
     */
    //void removeSimulation(const std::string& name);
    /** Returns an instance of the simulation with name \a name. If there is
     * no such simulation 0 is returned.
     */
    App::Simulation* getSimulation(const std::string& name) const;
    /** run the simulation with name \a name. */
    bool run(const std::string& name);
    /** stop the simulation with name \a name. */
    bool stop(const std::string& name);
    /** Returns the active simulation. */
    App::Simulation* active() const;
    /** Set the active simulation. */
    void setActiveSimulation(App::Simulation* sim);
    /** Returns a list of all created simulation objects. */
    std::list<std::string> simulations() const;

    std::vector<App::Simulation*> getAllSimulations() const;
    //void addSimulation(Simulation* sim);
    //void addToSimulationDocumentMap(std::string simName, std::string docName);
    //std::string getDocNameFromSimulationDocumentMap(const std::string& simulationName) const;
    bool hasActiveObject() const;
    void highlightActiveObject(const Gui::HighlightMode&, bool);

private:
    UserLabSimulationObserver();
    ~UserLabSimulationObserver();

    void slotDeletedDocument(const App::Document& Doc) override;
    void slotDeletedObject(const App::DocumentObject& Obj) override;

private:
    static UserLabSimulationObserver* _instance;
    App::Simulation* _activeSimulation;
    Gui::ViewProviderDocumentObject* activeView;
    Gui::Document* activeDocument;


};

} // namespace Gui


#endif // APP_SIMULATIONMANAGER_H
