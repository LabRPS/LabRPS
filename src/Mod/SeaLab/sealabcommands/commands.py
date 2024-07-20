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

__title__ = "SEALAB command definitions"
__author__ = "Koffi Daniel"
__url__ = "https://www.labrps.com"

## @package commands
#  \ingroup SEALAB
#  \brief SEALAB command definitions

import LabRPS
import LabRPSGui
from LabRPS import Qt

from .manager import CommandManager

# Python command definitions:
# for C++ command definitions see src/Mod/SeaLab/Command.cpp
# TODO, may be even more generic class creation
# with type() and identifier instead of class for
# the commands which add new document objects.
# see https://www.python-course.eu/python3_classes_and_type.php
# Translation:
# some information in the regard of translation can be found in forum post
# https://forum.labrps.com/viewtopic.php?f=18&t=62449&p=543845#p543593


class _Simulation(CommandManager):
    "The SeaLab_Simulation command definition"

    def __init__(self):
        super(_Simulation, self).__init__()
        self.menutext = Qt.QT_TRANSLATE_NOOP("SeaLab_Simulation", "Simulation")
        self.pixmap = "SeaLab_NewSimulation"
        self.accel = "W, S"
        self.tooltip = Qt.QT_TRANSLATE_NOOP(
            "SeaLab_Simulation",
            "Creates a simulation with default simulation data"
        )
        self.is_active = "with_document"

    def Activated(self):
        LabRPS.ActiveDocument.openTransaction("Create Simulation")
        LabRPSGui.addModule("SeaLabGui")
        LabRPSGui.addModule("SeaLabObjects")
        LabRPSGui.doCommand("SeaLabObjects.makeSimulation(LabRPS.ActiveDocument, 'Simulation')")
        LabRPSGui.doCommand("SeaLabGui.setActiveSimulation(LabRPS.ActiveDocument.ActiveObject)")
        LabRPS.ActiveDocument.commitTransaction()

class _Comparison(CommandManager):
    "The SeaLab_Comparison command definition"

    def __init__(self):
        super(_Comparison, self).__init__()
        self.menutext = Qt.QT_TRANSLATE_NOOP("SeaLab_Comparison", "Comparison")
        self.accel = "S, C"
        self.tooltip = Qt.QT_TRANSLATE_NOOP(
            "SeaLab_Comparison",
            "Creates a simulation comparison"
        )
        self.is_active = "with_document"

    def Activated(self):
        LabRPS.ActiveDocument.openTransaction("Create Comparison")
        LabRPSGui.addModule("SeaLabGui")
        LabRPSGui.addModule("SeaLabObjects")
        LabRPSGui.doCommand("SeaLabObjects.makeSeaLabSimulationComparison(LabRPS.ActiveDocument, 'Comparison')")
        LabRPS.ActiveDocument.commitTransaction()

class _Examples(CommandManager):
    "The SeaLab_Examples command definition"

    def __init__(self):
        super(_Examples, self).__init__()
        self.pixmap = "SeaLab_Examples"
        self.menutext = Qt.QT_TRANSLATE_NOOP(
            "SeaLab_Examples",
            "Open SeaLab examples"
        )
        self.tooltip = Qt.QT_TRANSLATE_NOOP(
            "SeaLab_Examples",
            "Open SeaLab examples"
        )
        self.is_active = "always"

    def Activated(self):
        LabRPSGui.addModule("sealabexamples.examplesgui")
        LabRPSGui.doCommand("sealabexamples.examplesgui.show_examplegui()")


# the string in add command will be the page name on LabRPS wiki
LabRPSGui.addCommand(
    "SeaLab_Simulation",
    _Simulation()
)

# LabRPSGui.addCommand(
#     "SeaLab_Comparison",
#     _Comparison()
# )

LabRPSGui.addCommand(
    "SeaLab_Examples",
    _Examples()
)
