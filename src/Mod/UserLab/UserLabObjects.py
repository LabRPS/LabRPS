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

__title__ = "Objects USERLAB"
__author__ = "Koffi Daniel"
__url__ = "https://www.labrps.com"

## \addtogroup USERLAB
#  @{

import LabRPS
import UserLab

# PythonFeatures from package userlabobjects
# standard object name == class name == type without 'UserLab::'

# TODO
# There are objects which use a base object. It should be tested if the base object
# is in the same document as the doc in which the obj should be created.
# Could only be happen if the make is called from Python.
# What happens ATM? Error or the obj is moved to the other doc?


# ********* simulation objects *********************************************************************
def makeSimulation(doc, name="Simulation"):
    """makeSimulation(document, [name]):
    makes a UserLab Simulation object"""
    obj = doc.addObject("UserLab::UserLabSimulation", name)
    return obj

# ********* UserLab Features *********************************************************************
def makeFeature(featureName, simulationName,  featureTypeName, featureGroup):
    """makeFeature(featureName, simulationName,  featureTypeName, featureGroup):
    makes a UserLab feature and add to the specified UserLab simulation"""
    feat = UserLab.makeFeature(featureName, simulationName,  featureTypeName, featureGroup)
    return feat
# ********* simulation objects *********************************************************************
def makeUserLabSimulationComparison(doc, name="Comparison"):
    """makeUserLabSimulationComparison(document, [name]):
    makes a UserLab Simulation comparison object"""
    obj = doc.addObject("UserLab::UserLabSimulationComparison", name)
    return obj

##  @}
