# ***************************************************************************
# *   Copyright (c) 2019 Bernd Hahnebach <bernd@bimstatik.org>              *
# *   Copyright (c) 2020 Sudhanshu Dubey <sudhanshu.thethunder@gmail.com>   *
# *                                                                         *
# *   This file is part of the LabRPS CAx development system.              *
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

import LabRPS


# ************************************************************************************************
# setup and run examples by Python

# TODO: use method from examples gui to collect all examples in run_all method
# LabRPS Gui update between the examples would makes sense too

"""
# setup all examples
from userlabexamples.manager import *
setup_all()


# run all examples
from userlabexamples.manager import *
run_all()


# one special example
from userlabexamples.manager import run_example as run

doc = run("Deodatis1996_LocationDistribution")
doc = run("Deodatis1996_MeanWind")

"""

def setup_all():
    run_example("Deodatis1996_LocationDistribution")
    run_example("Deodatis1996_MeanWind")



def run_simulation(doc, base_name, filepath=""):

    from os.path import join, exists
    from os import makedirs
    from tempfile import gettempdir as gettmp

    # recompute
    doc.recompute()

    # print(doc.Objects)
    # print([obj.Name for obj in doc.Objects])

    # filepath
    if filepath == "":
        filepath = join(gettmp(), "USERLAB_examples")
    if not exists(filepath):
        makedirs(filepath)

    # a file name is needed for the besides dir to work
    save_rps_file = join(filepath, (base_name + ".rps"))
    LabRPS.Console.PrintMessage(
        "Save LabRPS file for {} analysis to {}\n.".format(base_name, save_rps_file)
    )
    doc.saveAs(save_rps_file)

    # save doc once again with results
    doc.save()


def run_example(example, base_name=None):

    from importlib import import_module
    module = import_module("userlabexamples." + example)
    if not hasattr(module, "setup"):
        LabRPS.Console.PrintError("Setup method not found in {}\n".format(example))
        return None

    doc = getattr(module, "setup")()

    if base_name is None:
        base_name = example
    run_simulation(doc, base_name)
    doc.recompute()

    return doc


# ************************************************************************************************
# helper used from examples
def init_doc(doc=None):
    if doc is None:
        doc = LabRPS.newDocument()
    return doc


def get_header(information):
    return """{name}

{information}""".format(name=information["name"], information=print_info_dict(information))


def print_info_dict(information):
    the_text = ""
    for k, v in information.items():
        value_text = ""
        if isinstance(v, list):
            for j in v:
                value_text += "{}, ".format(j)
            value_text = value_text.rstrip(", ")
        else:
            value_text = v
        the_text += "{} --> {}\n".format(k, value_text)
    # print(the_text)
    return the_text


def add_explanation_obj(doc, the_text):
    text_obj = doc.addObject("App::TextDocument", "Explanation_Report")
    text_obj.Text = the_text
    text_obj.setPropertyStatus("Text", "ReadOnly")  # set property editor readonly
    if LabRPS.GuiUp:
        text_obj.ViewObject.ReadOnly = True  # set editor view readonly
    return text_obj
