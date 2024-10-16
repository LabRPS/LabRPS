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
        "name": "Deodatis 1996 et al Spectrum Decomposition",
        "windlabfeature": "SpectrumDecomposition",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from windlabexamples.Deodatis1996_SpectrumDecomposition import setup
setup()

"""


def setup(doc=None, showGui=True):

    # create the corresponding mean wind speeds first in a new document
    # and get the document where a simulation is also created already with name "Simulation" 
    from windlabexamples.Deodatis1996_SpectrumModel import setup
    doc = setup(None, False)

    # get the existing simulation
    sim = WindLab.getSimulation("Simulation")
    
    # check if the simulation is really exist
    if not sim:
        LabRPS.Console.PrintError("The simulation does not exist.\n")
        return None
    
    # create new spectrum decomposition method in the simulation called "Simulation"
    spectrum = WindLabObjects.makeFeature("SpectrumDecomposition", "Simulation",  "Cholesky Decomposition", "Spectrum Decomposition Method")
    
    # check if the created spectrum decomposition method feature is null
    if not spectrum:
        LabRPS.Console.PrintError("Error on creating the spectrum decomposition method.\n")
        return None

    simPoints = sim.computeLocationCoordinateMatrixP3()

    v1 = vec(simPoints[0][1], simPoints[0][2], simPoints[0][3])
    v2 = vec(simPoints[1][1], simPoints[1][2], simPoints[1][3])
    v3 = vec(simPoints[2][1], simPoints[2][2], simPoints[2][3])

    # coherence function in this example is stationary. Meanning coherence functions are not varying in time
    # here we use time instant of 0 second.
    time = 0.0

    # compute the coherence function between point j and k for all frequencies at time instant of 0s
    psd11 = sim.computeDecomposedCrossSpectrumVectorF(v1, v1, time)
    psd22 = sim.computeDecomposedCrossSpectrumVectorF(v2, v2, time)
    psd33 = sim.computeDecomposedCrossSpectrumVectorF(v3, v3, time)
    
    # if we are Gui mode, show the stored result in Alphaplot
    if LabRPS.GuiUp and showGui:
        # explanation object
        # just keep the following line and change text string in get_explanation method
        manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))
        import WindLabGui
        #show the mean wind speeds in Alphaplot
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, 3, psd11)
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, 3, psd22)
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfFrequency, 3, psd33)

        import numpy
        import matplotlib.pyplot as plt
        arr1 = numpy.asarray(psd11)
        arr2 = numpy.asarray(psd22)       
        arr3 = numpy.asarray(psd33)       
       
        fig, ax = plt.subplots()
        fig.suptitle('Decompoosed PSD at Points 1, 2, and 3.')
        ax.plot(arr1[:,0], arr1[:,1], color='r')
        ax.plot(arr2[:,0], arr2[:,1], color='g')
        ax.plot(arr3[:,0], arr3[:,1], color='b')
        ax.set_xlabel('Frequency (rad/s)')
        ax.set_ylabel('Spectrum (m^2/s)')
        ax.grid(True)
        plt.legend(["Point 1", "Point 2", "Point 3"], loc="lower left")
        ax.set_xscale("log")
        ax.set_yscale("log")
        plt.show()

    doc.recompute()
    return doc
