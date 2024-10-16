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

import os

from importlib import import_module

from PySide import QtCore
from PySide import QtGui

import LabRPSGui


class UserDefinedPhenomenonLabExamples(QtGui.QWidget):
    def __init__(self):
        super(UserDefinedPhenomenonLabExamples, self).__init__()
        self.init_ui()

    def __del__(self,):
        # need as fix for qt event error
        return

    def init_ui(self):

        # init widgets
        self.view = QtGui.QTreeWidget()

        path = os.path.dirname(os.path.realpath(__file__))
        files = [f for f in os.listdir(str(path))]
        not_files = [
            "__init__.py",
            "__pycache__",
            "examplesgui.py",
            "manager.py",
        ]

        files = [str(f) for f in files if f not in not_files]
        # Slicing the .py from every file
        files = [f[:-3] for f in files if f.endswith(".py")]
        files.sort()
        files_info = {}
        self.files_name = {}
        userdefinedphenomenonlabfeatures = set()

        for f in files:
            module = import_module("userdefinedphenomenonlabexamples." + f)
            if hasattr(module, "get_information"):
                info = getattr(module, "get_information")()
                files_info[f] = info
                self.files_name[info["name"]] = f
                userdefinedphenomenonlabfeatures.add(info["userdefinedphenomenonlabfeature"])
                                
        userdefinedphenomenonlabfeatures = sorted(userdefinedphenomenonlabfeatures)

        all_examples = QtGui.QTreeWidgetItem(self.view, ["All"])
        for example, info in files_info.items():
            QtGui.QTreeWidgetItem(all_examples, [info["name"]])
        self.view.addTopLevelItem(all_examples)

        all_userdefinedphenomenonlabfeatures = QtGui.QTreeWidgetItem(self.view, ["UserDefinedPhenomenonLabFeatures"])
        for feat in userdefinedphenomenonlabfeatures:
            feat_item = QtGui.QTreeWidgetItem(all_userdefinedphenomenonlabfeatures, [feat])
            for example, info in files_info.items():
                if info["userdefinedphenomenonlabfeature"] == feat:
                    QtGui.QTreeWidgetItem(feat_item, [info["name"]])
        self.view.addTopLevelItem(all_userdefinedphenomenonlabfeatures)

        self.view.setHeaderHidden(True)
        self.view.itemClicked.connect(self.enable_buttons)
        self.view.itemDoubleClicked.connect(self.double_clicked)

        # Ok buttons:
        self.button_box = QtGui.QDialogButtonBox(self)
        self.button_box.setOrientation(QtCore.Qt.Horizontal)
        self.setup_button = QtGui.QPushButton(QtGui.QIcon.fromTheme("document-new"), "Setup")
        self.setup_button.setEnabled(False)
        self.button_box.addButton(self.setup_button, QtGui.QDialogButtonBox.AcceptRole)
        #self.run_button = QtGui.QPushButton(QtGui.QIcon.fromTheme("system-run"), "Run")
        #self.run_button.setEnabled(False)
        #self.button_box.addButton(self.run_button, QtGui.QDialogButtonBox.ApplyRole)
        self.close_button = QtGui.QPushButton(QtGui.QIcon.fromTheme("window-close"), "Close")
        self.button_box.addButton(self.close_button, QtGui.QDialogButtonBox.RejectRole)
        self.button_box.clicked.connect(self.clicked)

        # Layout:
        layout = QtGui.QGridLayout()
        layout.addWidget(self.view, 2, 0, 1, 2)
        layout.addWidget(self.button_box, 3, 1)
        self.setLayout(layout)

    def clicked(self, button):
        if self.button_box.buttonRole(button) == QtGui.QDialogButtonBox.AcceptRole:
            self.accept()
        #elif self.button_box.buttonRole(button) == QtGui.QDialogButtonBox.ApplyRole:
        #    self.run()
        #elif self.button_box.buttonRole(button) == QtGui.QDialogButtonBox.RejectRole:
        #    self.reject()

    def accept(self):
        QtGui.QApplication.setOverrideCursor(QtCore.Qt.WaitCursor)
        item = self.view.selectedItems()[0]
        name = item.text(0)
        example = self.files_name[name]
        parent = item.parent()
        if parent is not None:
            grand_parent = parent.parent()
            if grand_parent is not None:
                grand_parent_name = grand_parent.text(0)
        # if done this way the Python commands are printed in Python console
        LabRPSGui.doCommand("from userdefinedphenomenonlabexamples.{}  import setup".format(str(example)))
        LabRPSGui.doCommand("setup()")
        QtGui.QApplication.restoreOverrideCursor()

    def reject(self):
        self.close()

    def closeEvent(self, ev):
        pw = self.parentWidget()
        if pw and pw.inherits("QDockWidget"):
            pw.deleteLater()

    #def run(self):
    #    QtGui.QApplication.setOverrideCursor(QtCore.Qt.WaitCursor)
    #    item = self.view.selectedItems()[0]
    #    name = item.text(0)
    #    example = self.files_name[name]
    #    solver = None
    #    parent = item.parent()
    #    if parent is not None:
    #        grand_parent = parent.parent()
    #        if grand_parent is not None:
    #            grand_parent_name = grand_parent.text(0)
    #            if grand_parent_name == "Solvers":
    #                solver = parent.text(0)
    #    # if done this way the Python commands are printed in Python console
    #    LabRPSGui.doCommand("from userdefinedphenomenonlabexamples.manager import run_example")
    #    if solver is not None:
    #        LabRPSGui.doCommand("run_example(\"{}\")"
    #                             .format(str(example), str(solver)))
    #    else:
    #        LabRPSGui.doCommand("run_example(\"{}\")".format(str(example)))
    #    QtGui.QApplication.restoreOverrideCursor()

    def enable_buttons(self):
        # only enable buttons if a example is selected
        sel_item_text = self.view.selectedItems()[0].text(0)
        if sel_item_text in self.files_name:
            #self.run_button.setEnabled(True)
            self.setup_button.setEnabled(True)
        else:
            #self.run_button.setEnabled(False)
            self.setup_button.setEnabled(False)

    def double_clicked(self):
        # setup an example when it is double clicked
        sel_item_text = self.view.selectedItems()[0].text(0)
        if sel_item_text in self.files_name:
            self.accept()


def show_examplegui():
    QtGui.QApplication.setOverrideCursor(QtCore.Qt.WaitCursor)
    mw = LabRPSGui.getMainWindow()
    example_widget = QtGui.QDockWidget("USERDEFINEDPHENOMENONLAB Examples", mw)
    example_widget.setWidget(UserDefinedPhenomenonLabExamples())
    mw.addDockWidget(QtCore.Qt.RightDockWidgetArea, example_widget)
    QtGui.QApplication.restoreOverrideCursor()
