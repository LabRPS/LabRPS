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

__title__ = "SEISMICLAB command base class"
__author__ = "Koffi Daniel"
__url__ = "https://www.labrps.com"

## @package manager
#  \ingroup SEISMICLAB
#  \brief SEISMICLAB command base class

import LabRPS

if LabRPS.GuiUp:
    from PySide import QtCore
    import LabRPSGui
    import SeismicLabGui


class CommandManager(object):

    def __init__(self):

        self.command = "SEISMICLAB" + self.__class__.__name__
        self.pixmap = self.command
        self.menutext = self.__class__.__name__.lstrip("_")
        self.accel = ""
        self.tooltip = "Creates a {}".format(self.menutext)
        self.resources = None

        self.is_active = None
        self.do_activated = None
        self.selobj = None
        self.selobj2 = None
        self.active_simulation = None

    def GetResources(self):
        if self.resources is None:
            self.resources = {
                "Pixmap": self.pixmap,
                "MenuText": QtCore.QT_TRANSLATE_NOOP(self.command, self.menutext),
                "Accel": self.accel,
                "ToolTip": QtCore.QT_TRANSLATE_NOOP(self.command, self.tooltip)
            }
        return self.resources

    def IsActive(self):
        if not self.is_active:
            active = False
        elif self.is_active == "always":
            active = True
        elif self.is_active == "with_document":
            active = LabRPSGui.ActiveDocument is not None
        elif self.is_active == "with_simulation":
            active = (
                SeismicLabGui.getActiveSimulation() is not None
                and self.active_simulation_in_active_doc()
            )
        return active

    def Activated(self):
        if self.do_activated == "add_obj_on_gui_noset_edit":
            self.add_obj_on_gui_noset_edit(self.__class__.__name__.lstrip("_"))
        elif self.do_activated == "add_obj_on_gui_expand_noset_edit":
            self.add_obj_on_gui_expand_noset_edit(self.__class__.__name__.lstrip("_"))
        elif self.do_activated == "add_obj_on_gui_set_edit":
            self.add_obj_on_gui_set_edit(self.__class__.__name__.lstrip("_"))
        elif self.do_activated == "add_obj_on_gui_selobj_noset_edit":
            self.add_obj_on_gui_selobj_noset_edit(self.__class__.__name__.lstrip("_"))
        elif self.do_activated == "add_obj_on_gui_selobj_set_edit":
            self.add_obj_on_gui_selobj_set_edit(self.__class__.__name__.lstrip("_"))
        elif self.do_activated == "add_obj_on_gui_selobj_expand_noset_edit":
            self.add_obj_on_gui_selobj_expand_noset_edit(self.__class__.__name__.lstrip("_"))
        # in all other cases Activated is implemented it the command class

    def active_simulation_in_active_doc(self):
        simulation = SeismicLabGui.getActiveSimulation()
        if simulation.Document is LabRPS.ActiveDocument:
            self.active_simulation = simulation
            return True
        else:
            return False


    # ****************************************************************************************
    # methods to add the objects to the document in LabRPSGui mode

    def add_obj_on_gui_set_edit(self, objtype):
        LabRPS.ActiveDocument.openTransaction(
            "Create SeismicLab{}"
            .format(objtype)
        )
        LabRPSGui.addModule(
            "SeismicLabObjects"
        )
        LabRPSGui.addModule(
            "SeismicLabGui"
        )
        LabRPSGui.doCommand(
            "SeismicLabGui.getActiveSimulation().addObject(SeismicLabObjects."
            "make{}(LabRPS.ActiveDocument))"
            .format(objtype)
        )
        # no other obj should be selected if we go in task panel
        LabRPSGui.Selection.clearSelection()
        LabRPSGui.doCommand(
            "LabRPSGui.ActiveDocument.setEdit(LabRPS.ActiveDocument.ActiveObject.Name)"
        )
        LabRPS.ActiveDocument.recompute()

    def add_obj_on_gui_noset_edit(self, objtype):
        LabRPS.ActiveDocument.openTransaction(
            "Create SeismicLab{}"
            .format(objtype)
        )
        LabRPSGui.addModule(
            "SeismicLabObjects"
        )
        LabRPSGui.addModule(
            "SeismicLabGui"
        )
        LabRPSGui.doCommand(
            "SeismicLabGui.getActiveSimulation().addObject(SeismicLabObjects."
            "make{}(LabRPS.ActiveDocument))"
            .format(objtype)
        )
        # LabRPS.ActiveDocument.commitTransaction()  # solver command class had this line
        # no clear selection is done
        LabRPS.ActiveDocument.recompute()

    def add_obj_on_gui_expand_noset_edit(self, objtype):
        # like add_obj_on_gui_noset_edit but the parent object
        # is expanded in the tree to see the added obj
        # the added obj is also selected to enable direct additons to it
        LabRPS.ActiveDocument.openTransaction(
            "Create SeismicLab{}"
            .format(objtype)
        )
        LabRPSGui.addModule(
            "SeismicLabObjects"
        )
        LabRPSGui.addModule(
            "SeismicLabGui"
        )
        # expand parent obj in tree view if selected
        expandParentObject()
        # add the object
        LabRPSGui.doCommand(
            "addedObj = SeismicLabGui.getActiveSimulation().addObject(SeismicLabObjects."
            "make{}(LabRPS.ActiveDocument))[0]"
            .format(objtype)
        )
        # select only added object
        LabRPSGui.Selection.clearSelection()
        LabRPSGui.doCommand("addedObjDocObj = LabRPS.ActiveDocument.getObject(addedObj.Name)")
        LabRPSGui.doCommand("LabRPSGui.Selection.addSelection(addedObjDocObj)")
        LabRPS.ActiveDocument.recompute()

    def add_obj_on_gui_selobj_set_edit(self, objtype):
        LabRPS.ActiveDocument.openTransaction(
            "Create SeismicLab{}"
            .format(objtype)
        )
        LabRPSGui.addModule(
            "SeismicLabObjects"
        )
        LabRPSGui.doCommand(
            "SeismicLabObjects.make{}("
            "LabRPS.ActiveDocument, LabRPS.ActiveDocument.{})"
            .format(objtype, self.selobj.Name)
        )
        LabRPSGui.Selection.clearSelection()
        LabRPSGui.doCommand(
            "LabRPSGui.ActiveDocument.setEdit(LabRPS.ActiveDocument.ActiveObject.Name)"
        )
        LabRPS.ActiveDocument.recompute()

    def add_obj_on_gui_selobj_noset_edit(self, objtype):
        LabRPS.ActiveDocument.openTransaction(
            "Create SeismicLab{}"
            .format(objtype)
        )
        LabRPSGui.addModule(
            "SeismicLabObjects"
        )
        LabRPSGui.doCommand(
            "SeismicLabObjects.make{}("
            "LabRPS.ActiveDocument, LabRPS.ActiveDocument.{})"
            .format(objtype, self.selobj.Name)
        )
        LabRPSGui.Selection.clearSelection()
        LabRPS.ActiveDocument.recompute()

    def add_obj_on_gui_selobj_expand_noset_edit(self, objtype):
        # like add_obj_on_gui_selobj_noset_edit but the selection is kept
        # and the selobj is expanded in the tree to see the added obj
        LabRPS.ActiveDocument.openTransaction(
            "Create SeismicLab{}"
            .format(objtype)
        )
        LabRPSGui.addModule(
            "SeismicLabObjects"
        )
        LabRPSGui.doCommand(
            "SeismicLabObjects.make{}("
            "LabRPS.ActiveDocument, LabRPS.ActiveDocument.{})"
            .format(objtype, self.selobj.Name)
        )
        # expand selobj in tree view
        expandParentObject()
        LabRPS.ActiveDocument.recompute()
