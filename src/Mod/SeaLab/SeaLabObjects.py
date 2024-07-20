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

__title__ = "Objects SEALAB"
__author__ = "Koffi Daniel"
__url__ = "https://www.labrps.org"

## \addtogroup SEALAB
#  @{

import LabRPS
import SeaLab

# PythonFeatures from package sealabobjects
# standard object name == class name == type without 'SeaLab::'

# TODO
# There are objects which use a base object. It should be tested if the base object
# is in the same document as the doc in which the obj should be created.
# Could only be happen if the make is called from Python.
# What happens ATM? Error or the obj is moved to the other doc?


# ********* simulation objects *********************************************************************
def makeSimulation(doc, name="Simulation"):
    """makeSimulation(document, [name]):
    makes a SeaLab Simulation object"""
    obj = doc.addObject("SeaLab::SeaLabSimulation", name)
    return obj

# ********* SeaLab Features *********************************************************************
def makeFeature(featureName, simulationName,  featureTypeName, featureGroup):
    """makeFeature(featureName, simulationName,  featureTypeName, featureGroup):
    makes a SeaLab feature and add to the specified SeaLab simulation"""
    feat = SeaLab.makeFeature(featureName, simulationName,  featureTypeName, featureGroup)
    return feat
# ********* simulation objects *********************************************************************
def makeSeaLabSimulationComparison(doc, name="Comparison"):
    """makeSeaLabSimulationComparison(document, [name]):
    makes a SeaLab Simulation comparison object"""
    obj = doc.addObject("SeaLab::SeaLabSimulationComparison", name)
    return obj

##  @}
