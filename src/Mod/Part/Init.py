# LabRPS init script of the part module  
# (c) 2001 Juergen Riegel

#***************************************************************************
#*   (c) Juergen Riegel (juergen.riegel@web.de) 2002                       *   
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
#*   Juergen Riegel 2002                                                   *
#***************************************************************************/


#LabRPS.addImportType("CAD formats (*.igs *.iges *.step *.stp *.brep *.brp)","Part")
#LabRPS.addExportType("CAD formats (*.igs *.iges *.step *.stp *.brep *.brp)","Part")
LabRPS.addImportType("BREP format (*.brep *.brp)","Part")
LabRPS.addExportType("BREP format (*.brep *.brp)","Part")
LabRPS.addImportType("IGES format (*.iges *.igs)","Part")
LabRPS.addExportType("IGES format (*.iges *.igs)","Part")
LabRPS.addImportType("STEP with colors (*.step *.stp)","Import")
LabRPS.addExportType("STEP with colors (*.step *.stp)","Import")

LabRPS.__unit_test__ += [ "TestPartApp" ]
