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
import sys
import math
from math import sqrt
import unittest
import LabRPS
import tempfile
from LabRPS import Base
from LabRPS import Units

v = Base.Vector

# ----------------------------------------------------------------------------------
# define the functions to test the LabRPS WindLab module and expression engine
# ----------------------------------------------------------------------------------


class WindLabCases(unittest.TestCase):
    def setUp(self):
        self.doc = LabRPS.newDocument()
        self.TempPath = tempfile.gettempdir()
        LabRPS.Console.PrintLog("  Using temp path: " + self.TempPath + "\n")

    def testAggregates(self):
        """Test all aggregate functions"""
        wind = self.doc.addObject("WindLab::WindLabSimulation", "Wind")
        wind.TimeIncrement = "0.785 s"

        self.doc.recompute()
        self.assertEqual(wind.TimeIncrement.Value, 0.785)
        self.assertEqual(wind.TimeIncrement.Unit, LabRPS.Units.TimeSpan)

    def testUnits(self):
        """Units -- test unit calculations."""
        wind = self.doc.addObject("WindLab::WindLabSimulation", "Wind")
        # wind.set("A1", "=2mm + 3mm")
        self.doc.recompute()
        # self.assertEqual(wind.A1, Units.Quantity("5mm"))

    def tearDown(self):
        # closing doc
        LabRPS.closeDocument(self.doc.Name)
