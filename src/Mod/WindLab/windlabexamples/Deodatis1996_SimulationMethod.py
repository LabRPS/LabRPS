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
        "name": "Deodatis 1996 et al Wind Speed Simulation",
        "windlabfeature": "SimulationMethod",
    }


def get_explanation(header=""):
    return header + """

To run the example from Python console use:
from windlabexamples.Deodatis1996_SimulationMethod import setup
setup()

"""


def setup(doc=None, showGui=True, location = 1):

    # create the corresponding mean wind speeds first in a new document
    # and get the document where a simulation is also created already with name "Simulation" 
    from windlabexamples.Deodatis1996_SpectrumDecomposition import setup
    doc = setup(None, False)

    # get the existing simulation
    sim = WindLab.getSimulation("Simulation")
    
    # check if the simulation is really exist
    if not sim:
        LabRPS.Console.PrintError("The simulation does not exist.\n")
        return None
    
    # create new simulation method in the simulation called "Simulation"
    simMethod = WindLabObjects.makeFeature("SimulationMethod", "Simulation",  "Deodatis 1996", "Simulation Method")
    
    # check if the created simulation method feature is null
    if not simMethod:
        LabRPS.Console.PrintError("Error on creating the simulation method.\n")
        return None
    
    # create new randomness provider feature in the simulation called "Simulation"
    randomness = WindLabObjects.makeFeature("RandomPhases", "Simulation",  "Uniform Random Phases", "Randomness Provider")
    
    # check if the created randomness provider feature
    if not randomness:
        LabRPS.Console.PrintError("The creation of the randomness provider was not successuful.\n")
        return None

    velocities = sim.simulate()

    if not velocities:
        LabRPS.Console.PrintError("The simulation was not successuful.\n")
        return None

    # create new table tool
    CorrelationErgo = WindLabObjects.makeFeature("CorrelationErgo", "Simulation",  "Correlation Ergodicity Check Tool", "Table Tool")
    
    # check if the created randomness provider feature
    if not CorrelationErgo:
        LabRPS.Console.PrintError("The creation of the table tool was not successuful.\n")
        return None
        
    velocities = sim.simulate()
    sim.LocationIndexJ = location - 1 # user input lower bound is 1, code experts low bound of 0
    sim.LocationIndexK = location - 1
    CorrelationErgoRest = sim.tableToolCompute(velocities)
    
    # create new table tool
    pdfCheck = WindLabObjects.makeFeature("pdfCheck", "Simulation",  "PDF Check Tool", "Table Tool")
    
    # check if the created randomness provider feature
    if not pdfCheck:
        LabRPS.Console.PrintError("The creation of the table tool was not successuful.\n")
        return None
    pdfCheck.MeanSpeedIncrement = '0.50 m/s'
    pdfCheck.WeibulParametersEstimationMethod = "Density Power Method"
    pdfCheck.NumberOfBins = 10
    sim.setActiveFeature(pdfCheck)
    pdfCheckRest = sim.tableToolCompute(velocities)

    # create new table tool
    psdErgo = WindLabObjects.makeFeature("psdErgo", "Simulation", "Ergodicity Check Tool", "Table Tool")
    
    # check if the created randomness provider feature
    if not psdErgo:
        LabRPS.Console.PrintError("The creation of the table tool was not successuful.\n")
        return None
    psdErgo.WindowType = "Hamming window"
    sim.setActiveFeature(psdErgo)
    psdErgoRest = sim.tableToolCompute(velocities)

    # if we are Gui mode, show the stored result in Alphaplot
    if LabRPS.GuiUp and showGui:
        # explanation object
        # just keep the following line and change text string in get_explanation method
        manager.add_explanation_obj(doc, get_explanation(manager.get_header(get_information())))
        import WindLabGui
        #show the mean wind speeds in Alphaplot
        WindLabGui.WindLabPyTool.showArray(sim.getSimulationData().numberOfTimeIncrements, sim.getSimulationData().numberOfSpatialPosition + 1, velocities)
        
        # # 3D stacked line plot
        # import numpy
        # import matplotlib.pyplot as plt
        # from mpl_toolkits.mplot3d import Axes3D 
        # arr = numpy.asarray(velocities)
        # ax = plt.gca(projection='3d')
        # rows = arr.shape[0]
        # y1  = numpy.ones(rows)
        # ax.plot(arr[:,0], 1*y1, arr[:,1], color='r')
        # ax.plot(arr[:,0], 2*y1, arr[:,2], color='g')
        # ax.plot(arr[:,0], 3*y1, arr[:,3], color='b')
        # plt.show()

        # vertical subplots
        import numpy
        import matplotlib.pyplot as plt
        arr = numpy.asarray(velocities)       
        fig, axs = plt.subplots(3)
        # fig.suptitle('Simulated Wind Velocity at Points 1, 2, and 3.')
        axs[0].plot(arr[:,0], arr[:,1], color='r')
        axs[1].plot(arr[:,0], arr[:,2], color='g')
        axs[2].plot(arr[:,0], arr[:,3], color='b')
        axs[0].set_ylabel('Velocity 1 (m/s)')
        axs[1].set_ylabel('Velocity 2 (m/s)')
        axs[2].set_ylabel('Velocity 3 (m/s)')
        axs[2].set_xlabel('Time (s)')
        axs[0].grid(True)
        axs[1].grid(True)
        axs[2].grid(True)
        plt.show()


        arr1 = numpy.asarray(CorrelationErgoRest)       
        fig1, ax1 = plt.subplots()
        fig1.suptitle('Simulated VS Target Correlation')
        f = sim.getSimulationData().numberOfFrequency - 1
        ax1.plot(arr1[0:f,0], arr1[0:f,1], color='red')
        ax1.plot(arr1[:,2], arr1[:,3], color='blue', linestyle='dashed')
        ax1.set_xlabel('Time Lags (s)')
        ax1.set_ylabel('Correlation')
        ax1.grid(True)
        plt.legend(["Target", "Simulated"], loc="upper right")
        plt.show()

        fig2 = plt.figure()
        axs = fig2.subplot_mosaic([["velocity", "velocity"],
                          ["correlation", "pdf"]])

        # plot velocity:
        str = "Velocity {:d}".format(location)
        axs["velocity"].set_title(str)
        axs["velocity"].plot(arr[:,0], arr[:,1])
        axs["velocity"].set_xlabel("Time (s)")
        axs["velocity"].set_ylabel("Velocity(m/s)")
        
        # plot for correlation
        axs["correlation"].plot(arr1[0:f,0], arr1[0:f,1], color='red')
        axs["correlation"].plot(arr1[:,2], arr1[:,3], linestyle='dashed')
        axs["correlation"].set_xlabel('Time Lags (s)')
        axs["correlation"].set_ylabel('Correlation')
        # axs["correlation"].grid(True)
        axs["correlation"].legend(["Target", "Simulated"], loc="upper right")

        # plot for PDF
        # arr2 = numpy.asarray(pdfCheckRest) 
        # pl = pdfCheck.pdfLength - 1      
        # axs["pdf"].plot(arr2[0:pl,2], arr2[0:pl,3], color='red')
        # axs["pdf"].hist(arr2[:,1], bins = pdfCheck.NumberOfBins, density = 1)
        # axs["pdf"].set_xlabel('Velocity (m/s)')
        # axs["pdf"].set_ylabel('Probability Density')
        # # axs["pdf"].grid(True)
        # fig2.tight_layout()
        # axs["pdf"].legend(["Weibull fit", "Velocity"], loc="upper left")

        # power spectral density
        arr3 = numpy.asarray(psdErgoRest) 
        fftl = psdErgo.fftPointsNumber//2
        print(fftl)    
        axs["pdf"].plot(arr3[0:f,0], arr3[0:f,1], color='red')
        axs["pdf"].plot(arr3[0:fftl,2], arr3[0:fftl,3], linestyle='dashed')
        axs["pdf"].set_xlabel('Frequency (rad/s)')
        axs["pdf"].set_ylabel('Power Spectrum Density (m^2/s)')
        # axs["pdf"].grid(True)
        axs["pdf"].legend(["Target", "Simulated"], loc="upper right")
        axs["pdf"].set_xscale("log")
        axs["pdf"].set_yscale("log")
        fig2.tight_layout()
        plt.show()

        # plot for PDF
        arr2 = numpy.asarray(pdfCheckRest)
        fig3, ax2 = plt.subplots()
        fig3.suptitle('Probability Density') 
        pl = pdfCheck.pdfLength - 1      
        ax2.plot(arr2[0:pl,2], arr2[0:pl,3], color='red')
        ax2.hist(arr2[:,1], bins = pdfCheck.NumberOfBins, density = 1)
        ax2.set_xlabel('Velocity (m/s)')
        ax2.set_ylabel('Probability Density')
        ax2.legend(["Weibull fit", "Velocity"], loc="upper left")
        plt.show()

    doc.recompute()
    return doc
