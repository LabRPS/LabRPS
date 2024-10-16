#   (c) Juergen Riegel (LabRPS@juergen-riegel.net) 2011      LGPL        *
#                                                                         *
#   This file is part of the LabRPS development system.              *
#                                                                         *
#   This program is free software; you can redistribute it and/or modify  *
#   it under the terms of the GNU Lesser General Public License (LGPL)    *
#   as published by the Free Software Foundation; either version 2 of     *
#   the License, or (at your option) any later version.                   *
#   for detail see the LICENCE text file.                                 *
#                                                                         *
#   LabRPS is distributed in the hope that it will be useful,            *
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#   GNU Library General Public License for more details.                  *
#                                                                         *
#   You should have received a copy of the GNU Library General Public     *
#   License along with LabRPS; if not, write to the Free Software        *
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#   USA                                                                   *
#**************************************************************************


import LabRPS, os, sys, unittest, Part, UserDefinedPhenomenonLab
App = LabRPS

#---------------------------------------------------------------------------
# define the test cases to test the LabRPS UserDefinedPhenomenonLab module
#---------------------------------------------------------------------------


class TestUserDefinedPhenomenonLab(unittest.TestCase):
    def setUp(self):
        self.Doc = LabRPS.newDocument("UserDefinedPhenomenonLabSimulationTest")

    def tearDown(self):
        #closing doc
        LabRPS.closeDocument("UserDefinedPhenomenonLabSimulationTest")
        #print ("omit closing document for debugging")
