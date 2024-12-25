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
        "name": "Deodatis 1996 et al Mean Wind Profile",
        "windlabfeature": "MeanWindProfile",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from windlabexamples.Deodatis1996_MeanWind import setup
setup()

"""


def setup(doc=None, showGui=True):

    # run create the corresponding location distribution first in a new document
    # and get the document where a simulation is also created already with name "Simulation" 
    from windlabexamples.Deodatis1996_LocationDistribution import setup
    doc = setup(showGui=False)

    # get the existing simulation
    sim = WindLab.getSimulation("Simulation")
    
    # check if the simulation is really exist
    if not sim:
        LabRPS.Console.PrintError("The creation of the simulation was not successuful.\n")
        return None

    # create new mean wind profile feature in the simulation called "Simulation"
    mean = WindLabObjects.makeFeature("MeanSpeed", "Simulation",  "Logarithmic Law Profile", "Mean Wind Profile")
    
    # check if the created mean wind feature
    if not mean:
        LabRPS.Console.PrintError("The creation of the mean wind profile was not successuful.\n")
        return None

    mean.TerrainRoughness = '0.001266 m' 
    mean.ShearVelocity = '1.76 m/s' 

    # wind velocity in this example is stationary. Meanning wind speed means are not varying in time
    # here we use time instant of 0 second.
    time = 0.0

    # compute the mean wind speed at all simulation points at time instant of 0s
    meanValues = sim.computeMeanWindSpeedVectorP(time)

    # if we are Gui mode, show the stored result in Alphaplot
    if LabRPS.GuiUp and showGui:
        # explanation object
        # just keep the following line and change text string in get_explanation method
        manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))
        import GeneralToolsGui
        #show the mean wind speeds in Alphaplot
        GeneralToolsGui.GeneralToolsPyTool.showArray(sim.getSimulationData().numberOfSpatialPosition, 2, meanValues, False)
    
    # show the result as text in the python console
    print(meanValues)

    doc.recompute()
    return doc
