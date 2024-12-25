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

import SeismicLab
import SeismicLabObjects

from . import manager
from .manager import init_doc



def get_information():
    return {
        "name": "Deodatis 1996 et al Frequency Distribution",
        "seismiclabfeature": "FrequencyDistribution",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from seismiclabexamples.Deodatis1996_FrequencyDistribution import setup
setup()

"""


def setup(doc=None, showGui=True):
    # run create the corresponding location distribution first in a new document
    # and get the document where a simulation is also created already with name "Simulation" 
    from seismiclabexamples.Deodatis1996_LocationDistribution import setup
    doc = setup(showGui=False)

    #install the SeismicLab plugin with all its plugged features
    installResuslt = SeismicLab.installPlugin("SeismicLabPlugin")

    # get the existing simulation
    sim = SeismicLab.getSimulation("Simulation")
    
    # check if the simulation is successfully created
    if not sim:
        LabRPS.Console.PrintError("The simulation does not exist.\n")
        return None

    # create new frequency distribution in the simulation called "Simulation"
    frequency = SeismicLabObjects.makeFeature("Frequencies", "Simulation",  "Double Index Frequency Discretization", "Frequency Distribution")
    
    # check if the created frequency distribution feature is null
    if not frequency:
        LabRPS.Console.PrintError("Error on creating the frequency distribution.\n")
        return None

    frequencies = sim.computeFrequenciesMatrixFP()
    if not frequencies:
        LabRPS.Console.PrintError("The computation of the frequency distribution fails.\n")
        return None
    
    # if we are Gui mode, show the stored result in Alphaplot and adjust the scene for better view
    if LabRPS.GuiUp and showGui:
        # explanation object
        # just keep the following line and change text string in get_explanation method
        manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))
        
        import GeneralToolsGui
        #show the frequency coordinate in Alphaplot
        GeneralToolsGui.GeneralToolsPyTool.showArray(sim.getSimulationData().numberOfFrequency, sim.getSimulationData().numberOfSpatialPosition, frequencies, False)

    doc.recompute()
    return doc
