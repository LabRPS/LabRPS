# -*- coding: utf-8 -*-
# LabRPS tools of the _TEMPLATEPY_ workbench
# (c) 2001 Juergen Riegel
# License LGPL

import LabRPS, LabRPSGui

class CmdHelloWorld:
    def Activated(self):
        LabRPS.Console.PrintMessage("Hello, World!\n")
    def IsActive(self):
        return True
    def GetResources(self):
        return {'Pixmap': 'labrps', 'MenuText': 'Hello World', 'ToolTip': 'Print Hello World'}

LabRPSGui.addCommand('_TEMPLATEPY__HelloWorld', CmdHelloWorld())
