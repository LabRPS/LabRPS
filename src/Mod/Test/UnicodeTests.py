# -*- coding: utf-8 -*-
#***************************************************************************
#*   Copyright (c) 2007 Juergen Riegel <juergen.riegel@web.de>             *
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

# Open and edit only in UTF-8 !!!!!!

import LabRPS, os, unittest, tempfile


#---------------------------------------------------------------------------
# define the functions to test the LabRPS Document code
#---------------------------------------------------------------------------


class UnicodeBasicCases(unittest.TestCase):
  def setUp(self):
    self.Doc = LabRPS.newDocument("CreateTest")

  def testUnicodeLabel(self):
    L1 = self.Doc.addObject("App::FeatureTest","Label_1")
    L1.Label = u"हिन्दी"
    self.failUnless(L1.Label == u"हिन्दी")

  def tearDown(self):
    #closing doc
    LabRPS.closeDocument("CreateTest")

class DocumentSaveRestoreCases(unittest.TestCase):
  def setUp(self):
    self.Doc = LabRPS.newDocument("SaveRestoreTests")
    L1 = self.Doc.addObject("App::FeatureTest","Label_1")
    L1.Label = u"हिन्दी"
    self.TempPath = tempfile.gettempdir()
    LabRPS.Console.PrintLog( '  Using temp path: ' + self.TempPath + '\n')

  def testSaveAndRestore(self):
    # saving and restoring
    SaveName = self.TempPath + os.sep + "UnicodeTest.RPSStd"
    self.Doc.saveAs(SaveName)
    LabRPS.closeDocument("SaveRestoreTests")
    self.Doc = LabRPS.open(SaveName)
    self.failUnless(self.Doc.Label_1.Label == u"हिन्दी")
    LabRPS.closeDocument("UnicodeTest")
    LabRPS.newDocument("SaveRestoreTests")


  def tearDown(self):
    #closing doc
    LabRPS.closeDocument("SaveRestoreTests")


