#***************************************************************************
#*   Copyright (c) 2006 Werner Mayer <werner.wm.mayer@gmx.de>              *
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
#*   GNU Library General Public License for more details.                  *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with LabRPS; if not, write to the Free Software        *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#***************************************************************************/

# Workbench test module

import LabRPS, LabRPSGui, os, unittest
import tempfile

from PySide2 import QtWidgets, QtCore
from PySide2.QtWidgets import QApplication

class CallableCheckWarning:
    def __call__(self):
        diag = QApplication.activeModalWidget()
        if (diag):
            QtCore.QTimer.singleShot(0, diag, QtCore.SLOT('accept()'))

class WorkbenchTestCase(unittest.TestCase):
    def setUp(self):
        self.Active = LabRPSGui.activeWorkbench()
        LabRPS.Console.PrintLog(LabRPSGui.activeWorkbench().name())
        
    def testActivate(self):
        wbs=LabRPSGui.listWorkbenches()
        # this gives workbenches a possibility to detect that we're under test environment
        LabRPS.TestEnvironment = True
        for i in wbs:
            try:
                print ("Activate workbench '{}'".format(i))
                cobj = CallableCheckWarning()
                QtCore.QTimer.singleShot(500, cobj)
                success = LabRPSGui.activateWorkbench(i)
                LabRPS.Console.PrintLog("Active: "+LabRPSGui.activeWorkbench().name()+ " Expected: "+i+"\n")
                self.assertTrue(success, "Test on activating workbench {0} failed".format(i))
            except Exception as e:
                self.fail("Loading of workbench '{0}' failed: {1}".format(i, e))
        del LabRPS.TestEnvironment
        
    def testHandler(self):
        import __main__
        class UnitWorkbench(__main__.Workbench):
            MenuText = "Unittest"
            ToolTip = "Unittest"
            def Initialize(self):
                cmds = ["Test_Test"]
                self.appendToolbar("My Unittest",cmds)
            def GetClassName(self):
                return "Gui::PythonWorkbench"

        LabRPSGui.addWorkbench(UnitWorkbench())
        wbs=LabRPSGui.listWorkbenches()
        self.failUnless("UnitWorkbench" in wbs, "Test on adding workbench handler failed")
        LabRPSGui.activateWorkbench("UnitWorkbench")
        LabRPSGui.updateGui()
        self.failUnless(LabRPSGui.activeWorkbench().name()=="UnitWorkbench", "Test on loading workbench 'Unittest' failed")
        LabRPSGui.removeWorkbench("UnitWorkbench")
        wbs=LabRPSGui.listWorkbenches()
        self.failUnless(not "UnitWorkbench" in wbs, "Test on removing workbench handler failed")

    def testInvalidType(self):
        class MyExtWorkbench(LabRPSGui.Workbench):
            def Initialize(self):
                pass
            def GetClassName(self):
                return "App::Extension"

        LabRPSGui.addWorkbench(MyExtWorkbench())
        with self.assertRaises(TypeError):
            LabRPSGui.activateWorkbench("MyExtWorkbench")
        LabRPSGui.removeWorkbench("MyExtWorkbench")

    def tearDown(self):
        LabRPSGui.activateWorkbench(self.Active.name())
        LabRPS.Console.PrintLog(self.Active.name())

class CommandTestCase(unittest.TestCase):
    def testPR6889(self):
        # Fixes a crash
        TempPath = tempfile.gettempdir()
        macroName = TempPath + os.sep + "testmacro.py"
        macroFile = open(macroName, "w")
        macroFile.write("print ('Hello, World!')")
        macroFile.close()

        name = LabRPSGui.Command.createCustomCommand(macroName)
        cmd = LabRPSGui.Command.get(name)
        cmd.run()

class TestNavigationStyle(unittest.TestCase):
    def setUp(self):
        self.Doc = LabRPS.newDocument("CreateTest")

    def tearDown(self):
        LabRPS.closeDocument("CreateTest")
