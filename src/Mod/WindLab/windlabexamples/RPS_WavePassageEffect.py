# ***************************************************************************
# *   Copyright (c) 2019 Bernd Hahnebach <bernd@bimstatik.org>              *
# *   Copyright (c) 2020 Sudhanshu Dubey <sudhanshu.thethunder@gmail.com    *
# *                                                                         *
# *   This file is part of the LabRPS CAx development system.              *
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU Lesser General Public License (LGPL)    *
# *   as published by the Free Software Foundation; either version 2 of     *
# *   the License, or (at your option) any later version.                   *
# *   for detail see the LICENCE text file.                                 *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU Library General Public License for more details.                  *
# *                                                                         *
# *   You should have received a copy of the GNU Library General Public     *
# *   License along with this program; if not, write to the Free Software   *
# *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
# *   USA                                                                   *
# *                                                                         *
# ***************************************************************************

import LabRPS
from LabRPS import Vector as vec

import WindLab
import WindLabObjects

from . import manager
from .manager import init_doc



def get_information():
    return {
        "name": "RPS Wave Passage Effect",
        "windlabfeature": "WavePassageEffect",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from windlabexamples.RPS_WavePassageEffect import setup
setup()

"""


def setup(doc=None, showGui=True):
# init LabRPS document. New document will be created if the passed document is null.
    if doc is None:
        doc = init_doc()

    #install the WindLab plugin with all its plugged features
    installResuslt = WindLab.installPlugin("WindLabPlugin")

    # explanation object
    # just keep the following line and change text string in get_explanation method
    manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))

    # create new simulation with default name "Simulation"
    sim = WindLabObjects.makeSimulation(doc)
    
    # check if the simulation is successfully created
    if not sim:
        LabRPS.Console.PrintError("The simulation does not exist.\n")
        return None

    # create new location distribution in the simulation called "Simulation"
    loc = WindLabObjects.makeFeature("SimulationPoints", "Simulation", "Location Distribution",  "Horizontal Distribution")
    
    # check if the created location distribution feature is null
    if not loc:
        LabRPS.Console.PrintError("Error on creating the location distribution.\n")
        return None

    # create new mean wind profile feature in the simulation called "Simulation"
    mean = WindLabObjects.makeFeature("MeanSpeed", "Simulation", "Mean Wind Profile",  "RPS Logarithmic Low")
    
    # check if the created mean wind feature
    if not mean:
        LabRPS.Console.PrintError("The creation of the mean wind profile was not successuful.\n")
        return None

    mean.TerrainRoughness = '0.001266 m' 
    mean.ShearVelocity = '1.76 m/s' 

    # create new frequency distribution in the simulation called "Simulation"
    frequency = WindLabObjects.makeFeature("Frequencies", "Simulation", "Frequency Distribution",  "Double Index Frequency")
    
    # check if the created frequency distribution feature is null
    if not frequency:
        LabRPS.Console.PrintError("Error on creating the frequency distribution.\n")
        return None

    # create new wave passage effect function feature in the simulation called "Simulation"
    wavepassageEff = WindLabObjects.makeFeature("WavePassageEffect", "Simulation", "Wave Passage Effect",  "RPS Wave Passage Effect")
    
    # check if the created mean wind feature
    if not wavepassageEff:
        LabRPS.Console.PrintError("The creation of the wave passage effect was not successuful.\n")

    simPoints = sim.computeLocationCoordinateMatrixP3()

    v1 = vec(simPoints[0][1], simPoints[0][2], simPoints[0][3])
    v2 = vec(simPoints[1][1], simPoints[1][2], simPoints[1][3])
    v3 = vec(simPoints[2][1], simPoints[2][2], simPoints[2][3])

    time = 0.0

    # compute the wave passage effect function between point j and k for all frequencies at time instant of 0s
    wpe12 = sim.computeWavePassageEffectVectorF(v1, v2, time)
    wpe13 = sim.computeWavePassageEffectVectorF(v1, v3, time)
    wpe23 = sim.computeWavePassageEffectVectorF(v2, v3, time)

    # check the computed wave passage effect
    if not wpe13:
        LabRPS.Console.PrintError("The computation of the wave  passage effect has failed.\n")
        return None

    # if we are Gui mode, show the stored result in Alphaplot
    if LabRPS.GuiUp and showGui:
        import WindLabGui
        #show the mean wind speeds in Alphaplot
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, 3, wpe12)
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, 3, wpe13)
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, 3, wpe23)

        import numpy
        import matplotlib.pyplot as plt
        arr1 = numpy.asarray(wpe12)   
        arr2 = numpy.asarray(wpe13)   
        arr3 = numpy.asarray(wpe23)   

        fig, ax = plt.subplots()
        fig.suptitle('Real Part of Wave Passage Effect between Points 1 and 2.')
        ax.plot(arr1[:,0], arr1[:,1], color='r')
        ax.set_xlabel('Frequency (rad/s)')
        ax.set_ylabel('Wave Passage Effect')
        ax.grid(True)
        plt.legend(["Effect 12", "Effect 13", "Effect 23"], loc="lower left")
        ax.set_xscale("log")
        ax.set_yscale("log")
        plt.show()
    doc.recompute()
    return doc