#***************************************************************************
#*   Copyright (c) 2002,2003 Jürgen Riegel <juergen.riegel@web.de>         *
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

# LabRPS gui init module
#
# Gathering all the information to start LabRPS
# This is the second one of three init scripts, the third one
# runs when the gui is up

# imports the one and only
import LabRPS, LabRPSGui
from enum import IntEnum

# shortcuts
Gui = LabRPSGui

# this is to keep old code working
Gui.listCommands = Gui.Command.listAll
Gui.isCommandActive = lambda cmd: Gui.Command.get(cmd).isActive()

# The values must match with that of the
# C++ enum class ResolveMode
class ResolveMode(IntEnum):
    NoResolve = 0
    OldStyleElement = 1
    NewStyleElement = 2
    FollowLink = 3

Gui.Selection.ResolveMode = ResolveMode

# Important definitions
class Workbench:
    """The workbench base class."""
    MenuText = ""
    ToolTip = ""
    Icon = None

    def Initialize(self):
        """Initializes this workbench."""
        App.PrintWarning(str(self) + ": Workbench.Initialize() not implemented in subclass!")
    def ContextMenu(self, recipient):
        pass
    def appendToolbar(self,name,cmds):
        self.__Workbench__.appendToolbar(name, cmds)
    def removeToolbar(self,name):
        self.__Workbench__.removeToolbar(name)
    def listToolbars(self):
        return self.__Workbench__.listToolbars()
    def getToolbarItems(self):
        return self.__Workbench__.getToolbarItems()
    def appendCommandbar(self,name,cmds):
        self.__Workbench__.appendCommandbar(name, cmds)
    def removeCommandbar(self,name):
        self.__Workbench__.removeCommandbar(name)
    def listCommandbars(self):
        return self.__Workbench__.listCommandbars()
    def appendMenu(self,name,cmds):
        self.__Workbench__.appendMenu(name, cmds)
    def removeMenu(self,name):
        self.__Workbench__.removeMenu(name)
    def listMenus(self):
        return self.__Workbench__.listMenus()
    def appendContextMenu(self,name,cmds):
        self.__Workbench__.appendContextMenu(name, cmds)
    def removeContextMenu(self,name):
        self.__Workbench__.removeContextMenu(name)
    def reloadActive(self):
        self.__Workbench__.reloadActive()
    def getAllPlugins(self):
        return self.__Workbench__.getAllPlugins()
    def getAllInstalledPlugins(self):
        return self.__Workbench__.getAllInstalledPlugins()
    def getPhenomenonName(self):
        return self.__Workbench__.getPhenomenonName()
    def installPlugin(self,name):
        return self.__Workbench__.installPlugin(name)
    def unInstallPlugin(self,name):
        return self.__Workbench__.unInstallPlugin(name)
    def createSimulation(self,name):
        return self.__Workbench__.createSimulation(name)
    def createFeature(self,simulationName, featureTypeName, featureName, featureGroup, featureType):
        return self.__Workbench__.createFeature(simulationName, featureTypeName, featureName, featureGroup, featureType)

    def name(self):
        return self.__Workbench__.name()
    def GetClassName(self):
        """Return the name of the associated C++ class."""
        # as default use this to simplify writing workbenches in Python
        return "Gui::PythonWorkbench"


class StandardWorkbench ( Workbench ):
    """A workbench defines the tool bars, command bars, menus,
context menu and dockable windows of the main window.
    """
    def Initialize(self):
        """Initialize this workbench."""
        # load the module
        Log ('Init: Loading LabRPS GUI\n')
    def GetClassName(self):
        """Return the name of the associated C++ class."""
        return "Gui::StdWorkbench"

class NoneWorkbench ( Workbench ):
    """An empty workbench."""
    MenuText = "<none>"
    ToolTip = "The default empty workbench"
    def Initialize(self):
        """Initialize this workbench."""
        # load the module
        Log ('Init: Loading LabRPS GUI\n')
    def GetClassName(self):
        """Return the name of the associated C++ class."""
        return "Gui::NoneWorkbench"

def InitApplications():
    import sys,os,traceback
    try:
        # Python3
        import io as cStringIO
    except ImportError:
        # Python2
        import cStringIO
    # Searching modules dirs +++++++++++++++++++++++++++++++++++++++++++++++++++
    # (additional module paths are already cached)
    ModDirs = LabRPS.__ModDirs__
    #print ModDirs
    Log('Init:   Searching modules...\n')

    def RunInitGuiPy(Dir) -> bool:
        InstallFile = os.path.join(Dir,"InitGui.py")
        if (os.path.exists(InstallFile)):
            try:
                with open(file=InstallFile, encoding="utf-8") as f:
                    exec(f.read())
            except Exception as inst:
                Log('Init:      Initializing ' + Dir + '... failed\n')
                Log('-'*100+'\n')
                Log(traceback.format_exc())
                Log('-'*100+'\n')
                Err('During initialization the error "' + str(inst) + '" occurred in ' + InstallFile + '\n')
                Err('Please look into the log file for further information\n')
            else:
                Log('Init:      Initializing ' + Dir + '... done\n')
                return True
        else:
            Log('Init:      Initializing ' + Dir + '(InitGui.py not found)... ignore\n')
        return False

    for Dir in ModDirs:
        if ((Dir != '') & (Dir != 'CVS') & (Dir != '__init__.py')):
            stopFile = os.path.join(Dir, "ADDON_DISABLED")
            if os.path.exists(stopFile):
                Msg(f'NOTICE: Addon "{Dir}" disabled by presence of ADDON_DISABLED stopfile\n')
                continue
            MetadataFile = os.path.join(Dir, "package.xml")
            if os.path.exists(MetadataFile):
                meta = LabRPS.Metadata(MetadataFile)
                if not meta.supportsCurrentLabRPS():
                    continue
                content = meta.Content
                if "workbench" in content:
                    LabRPS.Gui.addIconPath(Dir)
                    workbenches = content["workbench"]
                    for workbench_metadata in workbenches:
                        if not workbench_metadata.supportsCurrentLabRPS():
                            continue
                        subdirectory = workbench_metadata.Name if not workbench_metadata.Subdirectory else workbench_metadata.Subdirectory
                        subdirectory = subdirectory.replace("/",os.path.sep)
                        subdirectory = os.path.join(Dir, subdirectory)
                        ran_init = RunInitGuiPy(subdirectory)

                        if ran_init:
                            # Try to generate a new icon from the metadata-specified information
                            classname = workbench_metadata.Classname
                            if classname:
                                try:
                                    wb_handle = LabRPS.Gui.getWorkbench(classname)
                                except Exception:
                                    Log(f"Failed to get handle to {classname} -- no icon can be generated, check classname in package.xml\n")
                                else:
                                    GeneratePackageIcon(dir, subdirectory, workbench_metadata, wb_handle)
                else:
                    continue # The package content says there are no workbenches here, so just skip
            else:
                RunInitGuiPy(Dir)
    Log("All modules with GUIs using InitGui.py are now initialized\n")

    try:
        import pkgutil
        import importlib
        import labrps
        labrps.gui = LabRPSGui
        for _, labrps_module_name, labrps_module_ispkg in pkgutil.iter_modules(labrps.__path__, "labrps."):
            # Check for a stopfile
            stopFile = os.path.join(LabRPS.getUserAppDataDir(), "Mod", labrps_module_name[8:], "ADDON_DISABLED")
            if os.path.exists(stopFile):
                continue

            # Make sure that package.xml (if present) does not exclude this version of LabRPS
            MetadataFile = os.path.join(LabRPS.getUserAppDataDir(), "Mod", labrps_module_name[8:], "package.xml")
            if os.path.exists(MetadataFile):
                meta = LabRPS.Metadata(MetadataFile)
                if not meta.supportsCurrentLabRPS():
                    continue

            if labrps_module_ispkg:
                Log('Init: Initializing ' + labrps_module_name + '\n')
                try:
                    labrps_module = importlib.import_module(labrps_module_name)
                    if any (module_name == 'init_gui' for _, module_name, ispkg in pkgutil.iter_modules(labrps_module.__path__)):
                        importlib.import_module(labrps_module_name + '.init_gui')
                        Log('Init: Initializing ' + labrps_module_name + '... done\n')
                    else:
                        Log('Init: No init_gui module found in ' + labrps_module_name + ', skipping\n')
                except Exception as inst:
                    Err('During initialization the error "' + str(inst) + '" occurred in ' + labrps_module_name + '\n')
                    Err('-'*80+'\n')
                    Err(traceback.format_exc())
                    Err('-'*80+'\n')
                    Log('Init:      Initializing ' + labrps_module_name + '... failed\n')
                    Log('-'*80+'\n')
                    Log(traceback.format_exc())
                    Log('-'*80+'\n')
    except ImportError as inst:
        Err('During initialization the error "' + str(inst) + '" occurred\n')

    Log("All modules with GUIs initialized using pkgutil are now initialized\n")

def GeneratePackageIcon(dir:str, subdirectory:str, workbench_metadata:LabRPS.Metadata, wb_handle:Workbench) -> None:
    relative_filename = workbench_metadata.Icon
    if not relative_filename:
        # Although a required element, this content item does not have an icon. Just bail out
        return
    absolute_filename = os.path.join(subdirectory, relative_filename)
    if hasattr(wb_handle, "Icon") and wb_handle.Icon:
        Log(f"Init:      Packaged workbench {workbench_metadata.Name} specified icon in class {workbench_metadata.Classname}") 
        Log(f" ... replacing with icon from package.xml data.\n")
    wb_handle.__dict__["Icon"] = absolute_filename


Log ('Init: Running LabRPSGuiInit.py start script...\n')



# init the gui

# signal that the gui is up
App.GuiUp = 1
App.Gui = LabRPSGui
LabRPSGui.Workbench = Workbench

Gui.addWorkbench(NoneWorkbench())

# init modules
InitApplications()

# set standard workbench (needed as fallback)
Gui.activateWorkbench("NoneWorkbench")

# Register .py, .RPSScript and .RPSMacro
LabRPS.addImportType("Python (*.py *.RPSMacro *.RPSScript)","LabRPSGui")
LabRPS.addExportType("Portable Document Format (*.pdf)","LabRPSGui")

del(InitApplications)
del(NoneWorkbench)
del(StandardWorkbench)


Log ('Init: Running LabRPSGuiInit.py start script... done\n')
