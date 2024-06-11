# LabRPS init script of the OpenSCAD module
# (c) 2001 Juergen Riegel

#***************************************************************************
#*   Copyright (c) 2002 Juergen Riegel <juergen.riegel@web.de>             *
#*                                                                         *
#*   This file is part of the LabRPS CAx development system.              *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   LabRPS is distributed in the hope that it will be useful,            *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Lesser General Public License for more details.                   *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with LabRPS; if not, write to the Free Software        *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#***************************************************************************/

import os
import LabRPS

LabRPS.addImportType("OpenSCAD CSG Format (*.csg)", "importCSG")

param = LabRPS.ParamGet(\
        "User parameter:BaseApp/Preferences/Mod/OpenSCAD")
openscadfilename = param.GetString('openscadexecutable')
openscadbin = openscadfilename and os.path.isfile(openscadfilename)

if openscadbin:
    LabRPS.addImportType("OpenSCAD Format (*.scad)", "importCSG")
    LabRPS.__unit_test__ += ["TestOpenSCADApp"]

LabRPS.addExportType("OpenSCAD CSG Format (*.csg)", "exportCSG")
LabRPS.addExportType("OpenSCAD Format (*.scad)", "exportCSG")
