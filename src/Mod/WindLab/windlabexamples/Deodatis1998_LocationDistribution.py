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
import matplotlib.ticker as mtick



def get_information():
    return {
        "name": "Deodatis 1998 et al Location Distribution",
        "windlabfeature": "LocationDistribution",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from windlabexamples.Deodatis1998_LocationDistribution import setup
setup()

"""


def setup(doc=None, showGui=True):
    # init LabRPS document. New document will be created if the passed document is null.
    if doc is None:
        doc = init_doc()

    #install the WindLab plugin with all its plugged features
    installResuslt1 = WindLab.installPlugin("WindLabPlugin")
    if not installResuslt1:
        LabRPS.Console.PrintError("The installation of the 'WindLabPlugin' plugin has failed.\n")
        return None
    
    installResuslt2 = WindLab.installPlugin("CorrelationErgodicityPlugin")
    if not installResuslt2:
        LabRPS.Console.PrintError("The installation of the 'CorrelationErgodicityPlugin' plugin has failed.\n")
        return None
    
    installResuslt3 = WindLab.installPlugin("PDFCheckToolPlugin")
    if not installResuslt3:
        LabRPS.Console.PrintError("The installation of the 'PDFCheckToolPlugin' plugin has failed.\n")
        return None
    
    installResuslt4 = WindLab.installPlugin("ErgodicityCheckToolPlugin")
    if not installResuslt4:
        LabRPS.Console.PrintError("The installation of the 'ErgodicityCheckToolPlugin' plugin has failed.\n")
        return None

    # create new simulation with default name "Simulation"
    sim = WindLabObjects.makeSimulation(doc)
    
    # check if the simulation is successfully created
    if not sim:
        LabRPS.Console.PrintError("The simulation does not exist.\n")
        return None
    
    # set simulation parameters
    sim.NumberOfFrequency = 2048
    sim.MaxFrequency = "0.64 Hz" # 4 rad/s;
    sim.FrequencyIncrement = "0.00031 Hz" # 0.00195 rad/s;
    sim.TimeIncrement = "0.785 s"
    sim.NumberOfTimeIncrements = 9651

    # create new location distribution in the simulation called "Simulation"
    loc = WindLabObjects.makeFeature("SimulationPoints", "Simulation",  "General Distribution", "Location Distribution")
    
    # check if the created location distribution feature is null
    if not loc:
        LabRPS.Console.PrintError("Error on creating the location distribution.\n")
        return None

    # find all the feature which are location distribution feature
    myFeatures = sim.findAllWindLabFeaturesOfThisType('WindLabAPI::WindLabFeatureLocationDistribution')

    #find all rps types
    rpsTypes = sim.getRPSTypesOfPluggableFeatures()
    print(rpsTypes)

    # change if needed the values of the properties of the feature
    v1 = vec(0, 0, 35000)
    v2 = vec(0, 0, 40000)
    v3 = vec(0, 0, 140000)
    loc.Locations = [v1, v2, v3]

    # run the method "computeLocationCoordinateMatrixP3" of the feature and store the result.
    # Note that here, this method will be called for the active location distribution feature
    locRes = sim.computeLocationCoordinateMatrixP3()

    if LabRPS.GuiUp and showGui:
        # explanation object
        # just keep the following line and change text string in get_explanation method
        manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))
        import WindLabGui
        #show the location coordinate in Alphaplot
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfSpatialPosition, 4, locRes)
        loc.ViewObject.Document.activeView().viewAxonometric()
        loc.ViewObject.Document.activeView().fitAll()

        import numpy
        import matplotlib.pyplot as plt
        arr = numpy.asarray(locRes)
        fig, ax = plt.subplots()
        fig.suptitle('Location Distribution')
        ax.plot(arr[:,0], arr[:,3], 'o-')
        ax.set_xlabel('Simulation Point Number')
        ax.set_ylabel('Height (m)')
        ax.grid(True)
        plt.show()
    
    doc.recompute()
    return doc
