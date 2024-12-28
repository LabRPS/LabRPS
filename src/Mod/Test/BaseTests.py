#***************************************************************************
#*   Copyright (c) 2004 Juergen Riegel <juergen.riegel@web.de>             *
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

import LabRPS, os, unittest, tempfile, math

class ConsoleTestCase(unittest.TestCase):
    def setUp(self):
        self.count = 0

    def testPrint(self):
        LabRPS.Console.PrintMessage("   Printing message\n")
        LabRPS.Console.PrintError("   Printing error\n")
        LabRPS.Console.PrintWarning("   Printing warning\n")
        LabRPS.Console.PrintLog("   Printing Log\n")

    def testSynchronPrintFromThread(self):
        # http://python-kurs.eu/threads.php
        try:
            import _thread as thread, time
        except Exception:
            import thread, time
        def adder():
            lock.acquire()
            self.count=self.count+1
            # call of Console method is thread-safe
            LabRPS.Console.PrintMessage("Call from Python thread: count="+str(self.count)+"\n")
            lock.release()

        lock=thread.allocate_lock()
        for i in range(10):
            thread.start_new(adder,())

        time.sleep(3)
        self.assertEqual(self.count, 10, "Synchronization of threads failed")
        LabRPS.Console.PrintMessage(str(self.count)+"\n")

    def testAsynchronPrintFromThread(self):
        # http://python-kurs.eu/threads.php
        try:
            import _thread as thread, time
        except Exception:
            import thread, time
        def adder():
            self.count=self.count+1
            # call of Console method is thread-safe
            LabRPS.Console.PrintMessage("Call from Python thread (not synchronized): count="+str(self.count)+"\n")

        lock=thread.allocate_lock()
        for i in range(10):
            thread.start_new(adder,())

        time.sleep(3)
        LabRPS.Console.PrintMessage(str(self.count)+"\n")

#    def testStatus(self):
#        SLog = LabRPS.GetStatus("Console","Log")
#        SErr = LabRPS.GetStatus("Console","Err")
#        SWrn = LabRPS.GetStatus("Console","Wrn")
#        SMsg = LabRPS.GetStatus("Console","Msg")
#        LabRPS.SetStatus("Console","Log",1)
#        LabRPS.SetStatus("Console","Err",1)
#        LabRPS.SetStatus("Console","Wrn",1)
#        LabRPS.SetStatus("Console","Msg",1)
#        self.assertEqual(LabRPS.GetStatus("Console","Msg"),1,"Set and read status failed (Console,Msg)")
#        self.assertEqual(LabRPS.GetStatus("Console","Err"),1,"Set and read status failed (Console,Err)")
#        self.assertEqual(LabRPS.GetStatus("Console","Wrn"),1,"Set and read status failed (Console,Wrn)")
#        self.assertEqual(LabRPS.GetStatus("Console","Log"),1,"Set and read status failed (Console,Log)")
#        LabRPS.SetStatus("Console","Log",0)
#        LabRPS.SetStatus("Console","Err",0)
#        LabRPS.SetStatus("Console","Wrn",0)
#        LabRPS.SetStatus("Console","Msg",0)
#        self.assertEqual(LabRPS.GetStatus("Console","Msg"),0,"Set and read status failed (Console,Msg)")
#        self.assertEqual(LabRPS.GetStatus("Console","Err"),0,"Set and read status failed (Console,Err)")
#        self.assertEqual(LabRPS.GetStatus("Console","Wrn"),0,"Set and read status failed (Console,Wrn)")
#        self.assertEqual(LabRPS.GetStatus("Console","Log"),0,"Set and read status failed (Console,Log)")
#        LabRPS.SetStatus("Console","Log",SLog)
#        LabRPS.SetStatus("Console","Err",SErr)
#        LabRPS.SetStatus("Console","Wrn",SWrn)
#        LabRPS.SetStatus("Console","Msg",SMsg)

    def tearDown(self):
        pass

class ParameterTestCase(unittest.TestCase):
    def setUp(self):
        self.TestPar = LabRPS.ParamGet("System parameter:Test")

    def testGroup(self):
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testGroup\n")
        # check on Group creation
        Temp = self.TestPar.GetGroup("44")
        self.assertTrue(self.TestPar.HasGroup("44"),"Test on created group failed")
        # check on Deletion
        self.TestPar.RemGroup("44")
        self.assertTrue(self.TestPar.HasGroup("44"),"A referenced group must not be deleted")
        Temp = 0

    def testGroupNames(self):
        with self.assertRaises(ValueError):
            # no empty groups allowed
            self.TestPar.GetGroup("")
        grp1 = self.TestPar.GetGroup("////Sub1/////Sub2/////")
        grp2 = self.TestPar.GetGroup("Sub1/Sub2")
        self.assertEqual(grp1.GetGroupName(), "Sub2")
        self.assertEqual(grp2.GetGroupName(), "Sub2")

    # check on special conditions
    def testInt(self):
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testInt\n")
        #Temp = LabRPS.ParamGet("System parameter:Test/44")
        # check on Int
        self.TestPar.SetInt("44",4711)
        self.assertEqual(self.TestPar.GetInt("44"), 4711,"In and out error at Int")
        # check on Deletion
        self.TestPar.RemInt("44")
        self.assertEqual(self.TestPar.GetInt("44",1), 1,"Deletion error at Int")


    def testBool(self):
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testBool\n")
        # check on Int
        self.TestPar.SetBool("44",1)
        self.assertEqual(self.TestPar.GetBool("44"), 1,"In and out error at Bool")
        # check on Deletion
        self.TestPar.RemBool("44")
        self.assertEqual(self.TestPar.GetBool("44",0), 0,"Deletion error at Bool")

    def testFloat(self):
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testFloat\n")
        #Temp = LabRPS.ParamGet("System parameter:Test/44")
        # check on Int
        self.TestPar.SetFloat("44",4711.4711)
        self.assertEqual(self.TestPar.GetFloat("44"), 4711.4711,"In and out error at Float")
        # check on Deletion
        self.TestPar.RemFloat("44")
        self.assertEqual(self.TestPar.GetFloat("44",1.1), 1.1,"Deletion error at Float")

    def testString(self):
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testFloat\n")
        #Temp = LabRPS.ParamGet("System parameter:Test/44")
        # check on Int
        self.TestPar.SetString("44","abcdefgh")
        self.assertEqual(self.TestPar.GetString("44"), "abcdefgh","In and out error at String")
        # check on Deletion
        self.TestPar.RemString("44")
        self.assertEqual(self.TestPar.GetString("44","hallo"), "hallo","Deletion error at String")

    def testNesting(self):
        # Parameter testing
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testNesting\n")
        for i in range(50):
            self.TestPar.SetFloat(str(i),4711.4711)
            self.TestPar.SetInt(str(i),4711)
            self.TestPar.SetBool(str(i),1)
            Temp = self.TestPar.GetGroup(str(i))
            for l in range(50):
                Temp.SetFloat(str(l),4711.4711)
                Temp.SetInt(str(l),4711)
                Temp.SetBool(str(l),1)
        Temp = 0

    def testExportImport(self):
        # Parameter testing
        #LabRPS.Console.PrintLog("Base::ParameterTestCase::testNesting\n")
        self.TestPar.SetFloat("ExTest",4711.4711)
        self.TestPar.SetInt("ExTest",4711)
        self.TestPar.SetString("ExTest","4711")
        self.TestPar.SetBool("ExTest",1)
        Temp = self.TestPar.GetGroup("ExTest")
        Temp.SetFloat("ExTest",4711.4711)
        Temp.SetInt("ExTest",4711)
        Temp.SetString("ExTest","4711")
        Temp.SetBool("ExTest",1)
        TempPath = tempfile.gettempdir() + os.sep + "ExportTest.FCExport"

        self.TestPar.Export(TempPath)
        Temp = self.TestPar.GetGroup("ImportTest")
        Temp.Import(TempPath)
        self.assertEqual(Temp.GetFloat("ExTest"), 4711.4711,"ExportImport error")
        Temp = 0

    def tearDown(self):
        #remove all
        TestPar = LabRPS.ParamGet("System parameter:Test")
        TestPar.Clear()

class AlgebraTestCase(unittest.TestCase):
    def setUp(self):
        pass

    def testAngle(self):
        v1 = LabRPS.Vector(0,0,0.000001)
        v2 = LabRPS.Vector(0,0.000001,0)
        self.assertAlmostEqual(v1.getAngle(v2), math.pi/2)
        self.assertAlmostEqual(v2.getAngle(v1), math.pi/2)

    def testAngleWithNullVector(self):
        v1 = LabRPS.Vector(0,0,0)
        v2 = LabRPS.Vector(0,1,0)
        self.assertTrue(math.isnan(v1.getAngle(v2)))
        self.assertTrue(math.isnan(v2.getAngle(v1)))
