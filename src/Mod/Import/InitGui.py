# -*- coding: utf8 -*-
# Import gui init module
# (c) 2003 Juergen Riegel
#
# Gathering all the information to start LabRPS
# This is the second one of three init scripts, the third one
# runs when the gui is up

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


# Registered in Part's Init.py file
LabRPS.changeImportModule("STEP with colors (*.step *.stp)","Import","ImportGui")
LabRPS.changeExportModule("STEP with colors (*.step *.stp)","Import","ImportGui")
LabRPS.addExportType("glTF (*.gltf *.glb)","ImportGui")

"""
class ImportWorkbench ( Workbench ):
	"Import workbench object"
	def Activate(self):
		# load the module
		try:
			Log ('Loading ImportGui module')
			import Import
			import ImportGui
		except ImportError:
			Err('Cannot load ImportGui')
			raise
	def GetIcon(self):
		# returns an icon for the workbench
		return ["/* XPM */\n"
			"static const char *fileopen[] = {\n"
			"\"16 13 5 1\",\n"
			"\". c #040404\",\n"
			"\"# c #808304\",\n"
			"\"a c None\",\n"
			"\"b c #f3f704\",\n"
			"\"c c #f3f7f3\",\n"
			"\"aaaaaaaaa...aaaa\",\n"
			"\"aaaaaaaa.aaa.a.a\",\n"
			"\"aaaaaaaaaaaaa..a\",\n"
			"\"a...aaaaaaaa...a\",\n"
			"\".bcb.......aaaaa\",\n"
			"\".cbcbcbcbc.aaaaa\",\n"
			"\".bcbcbcbcb.aaaaa\",\n"
			"\".cbcb...........\",\n"
			"\".bcb.#########.a\",\n"
			"\".cb.#########.aa\",\n"
			"\".b.#########.aaa\",\n"
			"\"..#########.aaaa\",\n"
			"\"...........aaaaa\"};\n"]

Gui.addWorkbench("Import",ImportWorkbench())
"""
# See https://forum.labrpsweb.org/viewtopic.php?f=3&t=26782
#import Import_rc
#LabRPSGui.addPreferencePage(":/ui/preferences-import.ui","Import-Export")
