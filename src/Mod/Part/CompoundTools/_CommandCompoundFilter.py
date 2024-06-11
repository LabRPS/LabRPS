# ***************************************************************************
# *   Copyright (c) 2016 Victor Titov (DeepSOIC) <vv.titov@gmail.com>       *
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU Lesser General Public License (LGPL)    *
# *   as published by the Free Software Foundation; either version 2 of     *
# *   the License, or (at your option) any later version.                   *
# *   for detail see the LICENCE text file.                                 *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU Library General Public License for more details.                  *
# *                                                                         *
# *   You should have received a copy of the GNU Library General Public     *
# *   License along with this program; if not, write to the Free Software   *
# *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
# *   USA                                                                   *
# *                                                                         *
# ***************************************************************************

__title__ = "CompoundTools._CommandCompoundFilter"
__author__ = "DeepSOIC, Bernd Hahnebach"
__url__ = "http://www.labrpsweb.org"
__doc__ = "Compound Filter: remove some children from a compound (features)."


import LabRPS
if LabRPS.GuiUp:
    import LabRPSGui
    from PySide import QtGui
    from PySide import QtCore


# translation-related code
#(see forum thread "A new Part tool is being born... JoinFeatures!"
#http://forum.labrpsweb.org/viewtopic.php?f=22&t=11112&start=30#p90239 )
    try:
        _fromUtf8 = QtCore.QString.fromUtf8
    except Exception:
        def _fromUtf8(s):
            return s
    translate = LabRPS.Qt.translate


# command class
class _CommandCompoundFilter:
    "Command to create CompoundFilter feature"
    def GetResources(self):
        return {'Pixmap': "Part_CompoundFilter",
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Part_CompoundFilter", "Compound Filter"),
                'Accel': "",
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Part_CompoundFilter",
                                                    "Filter out objects from a selected compound "
                                                    "by characteristics like volume,\n"
                                                    "area, or length, or by choosing specific items.\n"
                                                    "If a second object is selected, it will be used "
                                                    "as reference, for example,\n"
                                                    "for collision or distance filtering.")}

    def Activated(self):
        if len(LabRPSGui.Selection.getSelection()) == 1 or len(LabRPSGui.Selection.getSelection()) == 2:
            cmdCreateCompoundFilter(name="CompoundFilter")
        else:
            mb = QtGui.QMessageBox()
            mb.setIcon(mb.Icon.Warning)
            mb.setText(translate("Part_CompoundFilter",
                                 "First select a shape that is a compound. "
                                 "If a second object is selected (optional) "
                                 "it will be treated as a stencil.", None))
            mb.setWindowTitle(translate("Part_CompoundFilter", "Bad selection", None))
            mb.exec_()

    def IsActive(self):
        if LabRPS.ActiveDocument:
            return True
        else:
            return False


if LabRPS.GuiUp:
    LabRPSGui.addCommand('Part_CompoundFilter', _CommandCompoundFilter())


# helper
def cmdCreateCompoundFilter(name):
    sel = LabRPSGui.Selection.getSelection()
    LabRPS.ActiveDocument.openTransaction("Create CompoundFilter")
    LabRPSGui.addModule("CompoundTools.CompoundFilter")
    LabRPSGui.doCommand("f = CompoundTools.CompoundFilter.makeCompoundFilter(name = '" + name + "')")
    LabRPSGui.doCommand("f.Base = App.ActiveDocument." + sel[0].Name)
    if len(sel) == 2:
        LabRPSGui.doCommand("f.Stencil = App.ActiveDocument." + sel[1].Name)
        LabRPSGui.doCommand("f.Stencil.ViewObject.hide()")
        LabRPSGui.doCommand("f.FilterType = 'collision-pass'")
    else:
        LabRPSGui.doCommand("f.FilterType = 'window-volume'")

    try:
        LabRPSGui.doCommand("f.Proxy.execute(f)")
        LabRPSGui.doCommand("f.purgeTouched()")
    except Exception as err:
        if hasattr(err, "message"):
            error_string = err.message
        else:
            error_string = err
        mb = QtGui.QMessageBox()
        mb.setIcon(mb.Icon.Warning)
        error_text1 = translate("Part_CompoundFilter", "Computing the result failed with an error:")
        error_text2 = translate("Part_CompoundFilter", "Click 'Continue' to create the feature anyway, or 'Abort' to cancel.")
        mb.setText(error_text1 + "\n\n" + str(err) + "\n\n" + error_text2)
        mb.setWindowTitle(translate("Part_CompoundFilter","Bad selection", None))
        btnAbort = mb.addButton(QtGui.QMessageBox.StandardButton.Abort)
        btnOK = mb.addButton(translate("Part_SplitFeatures", "Continue", None), QtGui.QMessageBox.ButtonRole.ActionRole)
        mb.setDefaultButton(btnOK)

        mb.exec_()

        if mb.clickedButton() is btnAbort:
            LabRPS.ActiveDocument.abortTransaction()
            return

    LabRPSGui.doCommand("f.Base.ViewObject.hide()")
    LabRPSGui.doCommand("f = None")

    LabRPS.ActiveDocument.commitTransaction()
