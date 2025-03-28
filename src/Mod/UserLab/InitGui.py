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

# UserLab gui init module
#
# Gathering all the information to start LabRPS
# This is the second one of three init scripts, the third one
# runs when the gui is up
class UserLabWorkbench ( Workbench ):
    "UserLab workbench object"
    def __init__(self):
        self.__class__.Icon = LabRPS.getResourceDir() + "Mod/UserLab/Resources/icons/UserLabWorkbench.svg"
        self.__class__.MenuText = "UserLab"
        self.__class__.ToolTip = "UserLab workbench"

    def Initialize(self):
        # load the module
        import UserLabGui
        import UserLab
            
    def GetClassName(self):
        return "UserLabGui::Workbench"

Gui.addWorkbench(UserLabWorkbench())

LabRPS.__unit_test__ += [ "TestUserLabGui" ]
