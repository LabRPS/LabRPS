#***************************************************************************
#*   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
#*                                                                         *
#*   This file is part of the LabRPS development system.                   *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   LabRPS is distributed in the hope that it will be useful,             *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Lesser General Public License for more details.                   *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with LabRPS; if not, write to the Free Software         *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#***************************************************************************/

import LabRPS
from LabRPS import Vector as vec

import WindLab
import WindLabObjects

from . import manager
from .manager import init_doc



def get_information():
    return {
        "name": "Deodatis 1996 et al Uniform Random Phases",
        "windlabfeature": "RandomnessProvider",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from windlabexamples.Deodatis1996_UniformRandomPhases import setup
setup()

"""


def setup(doc=None, showGui=True):
    # init LabRPS document. New document will be created if the passed document is null.
    if doc is None:
        doc = init_doc()

    #install the WindLab plugin with all its plugged features
    installResuslt = WindLab.installPlugin("WindLabPlugin")

    # create new simulation with default name "Simulation"
    sim = WindLabObjects.makeSimulation(doc)
    
    # check if the simulation is successfully created
    if not sim:
        LabRPS.Console.PrintError("The simulation does not exist.\n")
        return None

    # create new randomness provider feature in the simulation called "Simulation"
    randomness = WindLabObjects.makeFeature("RandomPhases", "Simulation",  "Uniform Random Phases", "Randomness Provider")
    
    # check if the created randomness provider feature
    if not randomness:
        LabRPS.Console.PrintError("The creation of the randomness provider was not successuful.\n")
        return None

    # compute the random phases at all simulation points at time instant of 0s
    randomnesses = sim.generateRandomMatrixFP()

    # if we are Gui mode, show the stored result in Alphaplot
    if LabRPS.GuiUp and showGui:
        # explanation object
        # just keep the following line and change text string in get_explanation method
        manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))
        import WindLabGui
        #show the mean wind speeds in Alphaplot
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, sim.getSimulationData().numberOfSpatialPosition, randomnesses)
    
    doc.recompute()
    return doc
