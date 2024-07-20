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

# SeismicLab gui init module
#
# Gathering all the information to start LabRPS
# This is the second one of three init scripts, the third one
# runs when the gui is up
class SeismicLabWorkbench ( Workbench ):
    "SeismicLab workbench object"
    def __init__(self):
        self.__class__.Icon = LabRPS.getResourceDir() + "Mod/SeismicLab/Resources/icons/SeismicLabWorkbench.svg"
        self.__class__.MenuText = "SeismicLab"
        self.__class__.ToolTip = "SeismicLab workbench"

    def Initialize(self):
        # load the module
        import SeismicLabGui
        import SeismicLab
        import seismiclabcommands.commands

            
    def GetClassName(self):
        return "SeismicLabGui::Workbench"

Gui.addWorkbench(SeismicLabWorkbench())

LabRPS.__unit_test__ += [ "TestSeismicLabGui" ]
