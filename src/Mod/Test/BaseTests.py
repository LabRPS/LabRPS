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

    def testVector2d(self):
        v = LabRPS.Base.Vector2d(1.0, 1.0)
        v.rotate(math.pi/2)
        self.assertAlmostEqual(v.x, -1.0)
        self.assertAlmostEqual(v.y, 1.0)

    def testAngleWithNullVector(self):
        v1 = LabRPS.Vector(0,0,0)
        v2 = LabRPS.Vector(0,1,0)
        self.assertTrue(math.isnan(v1.getAngle(v2)))
        self.assertTrue(math.isnan(v2.getAngle(v1)))

    def testMatrix(self):
        m=LabRPS.Matrix(4,2,1,0,1,1,1,0,0,0,1,0,0,0,0,1)
        u=m.multiply(m.inverse())
        self.assertEqual(u, LabRPS.Matrix(),"Invalid inverse of matrix")

    def testRotAndMoveMatrix(self):
        m1=LabRPS.Matrix()
        m1.move(10,5,-3)
        m1.rotateY(.2)
        m2=LabRPS.Matrix()
        m2.rotateY(.2)
        m2.move(10,5,-3)
        m3=LabRPS.Matrix()
        m3.move(10,5,-3)
        m4=LabRPS.Matrix()
        m4.rotateY(.2)
        self.assertNotEqual(m1, m3*m4, "Wrong multiplication order")
        self.assertEqual(m1, m4*m3   , "Wrong multiplication order")
        self.assertEqual(m2, m3*m4   , "Wrong multiplication order")
        self.assertNotEqual(m2, m4*m3, "Wrong multiplication order")

    def testRotation(self):
        r=LabRPS.Rotation(1,0,0,0) # 180 deg around (1,0,0)
        self.assertEqual(r.Axis, LabRPS.Vector(1,0,0))
        self.assertAlmostEqual(math.fabs(r.Angle), math.fabs(math.pi))

        r=r.multiply(r) # identity
        self.assertEqual(r.Axis, LabRPS.Vector(0,0,1))
        self.assertAlmostEqual(r.Angle, 0)

        r=LabRPS.Rotation(1,0,0,0)
        r.Q=(0,0,0,1) # update axis and angle
        s=LabRPS.Rotation(0,0,0,1)
        self.assertEqual(r.Axis, s.Axis)
        self.assertAlmostEqual(r.Angle, s.Angle)
        self.assertTrue(r.isSame(s))

        r=LabRPS.Rotation(1,0,0,0)
        r.Matrix=LabRPS.Matrix() # update axis and angle
        s=LabRPS.Rotation(0,0,0,1)
        self.assertEqual(r.Axis, s.Axis)
        self.assertAlmostEqual(r.Angle, s.Angle)
        self.assertTrue(r.isSame(s))

        r=LabRPS.Rotation(1,0,0,0)
        r.Axes=(LabRPS.Vector(0,0,1),LabRPS.Vector(0,0,1)) # update axis and angle
        s=LabRPS.Rotation(0,0,0,1)
        self.assertEqual(r.Axis, s.Axis)
        self.assertAlmostEqual(r.Angle, s.Angle)
        self.assertTrue(r.isSame(s))

        #add 360 deg to angle
        r=LabRPS.Rotation(LabRPS.Vector(1,0,0),270)
        s=LabRPS.Rotation(LabRPS.Vector(1,0,0),270+360)
        self.assertEqual(r.Axis, s.Axis)
        #self.assertAlmostEqual(r.Angle, s.Angle + 2*math.pi)
        self.assertTrue(r.isSame(s))

        #subtract 360 deg from angle using Euler angles
        r=LabRPS.Rotation(0,0,180)
        r.invert()
        s=LabRPS.Rotation(0,0,-180)
        self.assertTrue(r.isSame(s))

        #subtract 360 deg from angle using quaternion
        r=LabRPS.Rotation(1,0,0,0)
        s=LabRPS.Rotation(-1,0,0,0)
        #angles have the same sign
        if r.Angle * s.Angle > 0:
            self.assertEqual(r.Axis, s.Axis*(-1))
        else:
            self.assertAlmostEqual(r.Angle, -s.Angle)
        self.assertTrue(r.isSame(s))
        r.invert()
        self.assertTrue(r.isSame(s))

        # gimbal lock (north pole)
        r=LabRPS.Rotation()
        r.setYawPitchRoll(20, 90, 10)
        a=r.getYawPitchRoll()
        s=LabRPS.Rotation()
        s.setYawPitchRoll(*a)
        self.assertAlmostEqual(a[0], 0.0)
        self.assertAlmostEqual(a[1], 90.0)
        self.assertAlmostEqual(a[2], -10.0)
        self.assertTrue(r.isSame(s, 1e-12))

        # gimbal lock (south pole)
        r=LabRPS.Rotation()
        r.setYawPitchRoll(20, -90, 10)
        a=r.getYawPitchRoll()
        s=LabRPS.Rotation()
        s.setYawPitchRoll(*a)
        self.assertAlmostEqual(a[0], 0.0)
        self.assertAlmostEqual(a[1], -90.0)
        self.assertAlmostEqual(a[2], 30.0)
        self.assertTrue(r.isSame(s, 1e-12))

    def testInverted(self):
        p = LabRPS.Placement()
        p.Rotation.Angle = math.pi / 2
        self.assertEqual(abs(p.inverse().Rotation.Angle), p.Rotation.Angle)

    def testYawPitchRoll(self):
        def getYPR1(yaw, pitch, roll):
            r = LabRPS.Rotation()
            r.setYawPitchRoll(yaw, pitch, roll)
            return r
        def getYPR2(yaw, pitch, roll):
            rx = LabRPS.Rotation()
            ry = LabRPS.Rotation()
            rz = LabRPS.Rotation()

            rx.Axis = LabRPS.Vector(1,0,0)
            ry.Axis = LabRPS.Vector(0,1,0)
            rz.Axis = LabRPS.Vector(0,0,1)

            rx.Angle = math.radians(roll)
            ry.Angle = math.radians(pitch)
            rz.Angle = math.radians(yaw)

            return rz.multiply(ry).multiply(rx)

        angles = []
        angles.append((10,10,10))
        angles.append((13,45,-24))
        angles.append((10,-90,20))

        for i in angles:
            r = getYPR1(*i)
            s = getYPR2(*i)
            self.assertTrue(r.isSame(s, 1e-12))

    def testBounding(self):
        b=LabRPS.BoundBox()
        b.setVoid()
        self.assertFalse(b.isValid(),"Bbox is not invalid")
        b.add(0,0,0)
        self.assertTrue(b.isValid(), "Bbox is invalid")
        self.assertEqual(b.XLength, 0, "X length > 0")
        self.assertEqual(b.YLength, 0, "Y length > 0")
        self.assertEqual(b.ZLength, 0, "Z length > 0")
        self.assertEqual(b.Center, LabRPS.Vector(0,0,0), "Center is not at (0,0,0)")
        self.assertTrue(b.isInside(b.Center), "Center is not inside Bbox")
        b.add(2,2,2)
        self.assertTrue(b.isInside(b.getIntersectionPoint(b.Center,LabRPS.Vector(0,1,0))),"Intersection point is not inside Bbox")
        self.assertTrue(b.intersect(b),"Bbox doesn't intersect with itself")
        self.assertFalse(b.intersected(LabRPS.BoundBox(4,4,4,6,6,6)).isValid(),"Bbox should not intersect with Bbox outside")
        self.assertEqual(b.intersected(LabRPS.BoundBox(-2,-2,-2,2,2,2)).Center, b.Center,"Bbox is not a full subset")

class MatrixTestCase(unittest.TestCase):
    def setUp(self):
        self.mat = LabRPS.Matrix()

    def testOrder(self):
        self.mat = LabRPS.Matrix(1.0,2.0,3.0,4.0)
        self.assertEqual(self.mat.A11, 1.0)
        self.assertEqual(self.mat.A12, 2.0)
        self.assertEqual(self.mat.A13, 3.0)
        self.assertEqual(self.mat.A14, 4.0)

    def testScalar(self):
        res = self.mat * 0.0
        for i in range(16):
            self.assertEqual(res.A[i], 0.0)

    def testAddition(self):
        res1 = self.mat * 2.0
        res2 = self.mat + self.mat
        for i in range(16):
            self.assertEqual(res1.A[i], res2.A[i])

    def testMinus(self):
        res = self.mat - self.mat
        for i in range(16):
            self.assertEqual(res.A[i], 0.0)

    def testVector(self):
        vec = LabRPS.Vector(1, 1, 1)
        vec = self.mat * vec
        self.assertEqual(vec.x, 1.0)
        self.assertEqual(vec.y, 1.0)
        self.assertEqual(vec.z, 1.0)

    def testVectorMult(self):
        vec = LabRPS.Vector(1, 1, 1)
        with self.assertRaises(TypeError):
            vec * "string"

    def testRotation(self):
        rot = LabRPS.Rotation()
        res = self.mat * rot
        self.assertEqual(type(res), LabRPS.Matrix)

    def testPlacement(self):
        plm = LabRPS.Placement()
        res = self.mat * plm
        self.assertEqual(type(res), LabRPS.Matrix)

    def testMatrix(self):
        mat = LabRPS.Matrix()
        res = self.mat * mat
        self.assertEqual(type(res), LabRPS.Matrix)

    def testMatrixPlacementMatrix(self):
        # Example taken from https://forum.freecadweb.org/viewtopic.php?f=3&t=61000
        mat = LabRPS.Matrix(-0.470847778020266,
                             0.8150598976807029,
                             0.3376088628746235,
                             -11.25290913640202,
                             -0.8822144756796808,
                             -0.4350066260577338,
                             -0.180185641360483,
                             -2876.45492562325,
                             1.955470978815492e-9,
                             -0.3826834326750831,
                             0.923879538425552,
                             941.3822018176414)
        plm = LabRPS.Placement(mat)
        mat = plm.toMatrix()
        self.assertEqual(mat.hasScale(), LabRPS.ScaleType.NoScaling)

    def testAnything(self):
        with self.assertRaises(NotImplementedError):
            self.mat * "string"

    def testUnity(self):
        mat = LabRPS.Matrix(2,0,0,0, 0,1,0,0, 0,0,2,0, 0,0,0,-1)
        self.assertFalse(mat.isUnity())
        mat.unity()
        self.assertTrue(mat.isUnity())

    def testPower(self):
        mat = LabRPS.Matrix(2,0,0,0, 0,1,0,0, 0,0,2,0, 0,0,0,-1)
        with self.assertRaises(NotImplementedError):
            mat ** "string"

        mat2 = mat ** 0
        self.assertTrue(mat2.isUnity())
        self.assertEqual(mat ** -1, mat.inverse())
        self.assertEqual(mat ** 1, mat)
        self.assertEqual(mat ** 2, mat * mat)
        self.assertEqual(mat ** 3, mat * mat * mat)
        mat.nullify()
        with self.assertRaises(RuntimeError):
            mat ** -1

    def testScale(self):
        self.mat.scale(1., 2., 3.)
        self.assertEqual(self.mat.determinant(), 6.0)
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.NonUniformLeft)
        self.mat.unity()
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.NoScaling)
        self.mat.scale(2., 2., 2.)
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.Uniform)
        self.mat.rotateX(1.0)
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.Uniform)
        self.mat.scale(1., 2., 3.)
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.NonUniformLeft)
        self.mat.unity()
        self.mat.scale(1., 2., 3.)
        self.mat.rotateX(1.0)
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.NonUniformRight)
        self.mat.unity()
        self.mat.setCol(0, LabRPS.Vector(1,2,3))
        self.mat.setCol(1, LabRPS.Vector(1,2,3))
        self.mat.setCol(2, LabRPS.Vector(1,2,3))
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.Other)
        self.mat.unity()
        self.mat.setRow(0, LabRPS.Vector(1,2,3))
        self.mat.setRow(1, LabRPS.Vector(1,2,3))
        self.mat.setRow(2, LabRPS.Vector(1,2,3))
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.Other)

    def testShearing(self):
        self.mat.setRow(1, LabRPS.Vector(0,1,1))
        self.assertEqual(self.mat.hasScale(), LabRPS.ScaleType.Other)

    def testMultLeftOrRight(self):
        mat1 = LabRPS.Matrix()
        mat1.rotateX(1.0)

        mat2 = LabRPS.Matrix()
        mat2.scale(1., 2., 3.)
        self.assertEqual((mat1 * mat2).hasScale(), LabRPS.ScaleType.NonUniformRight)
        self.assertEqual((mat2 * mat1).hasScale(), LabRPS.ScaleType.NonUniformLeft)

    def testNull(self):
        self.assertFalse(self.mat.isNull())
        self.mat.nullify()
        self.assertTrue(self.mat.isNull())

    def testUnity(self):
        self.assertTrue(self.mat.isUnity())
        self.mat.nullify()
        self.assertFalse(self.mat.isUnity())
        self.mat.unity()
        self.assertTrue(self.mat.isUnity())

    def testColRow(self):
        with self.assertRaises(TypeError):
            self.mat.col("string")
        with self.assertRaises(TypeError):
            self.mat.row("string")
        self.assertEqual(type(self.mat.col(0)), LabRPS.Vector)
        self.assertEqual(type(self.mat.row(0)), LabRPS.Vector)
        self.mat.setCol(0, LabRPS.Vector(1,0,0))
        self.mat.setRow(0, LabRPS.Vector(1,0,0))

    def testTrace(self):
        self.mat.scale(2., 2., 2.)
        self.assertEqual(self.mat.trace(), LabRPS.Vector(2., 2., 2.))

    def testNumberProtocol(self):
        with self.assertRaises(NotImplementedError):
            self.mat / 2.0
        with self.assertRaises(NotImplementedError):
            self.mat % 2.0
        with self.assertRaises(NotImplementedError):
            divmod(self.mat, 2.0)
        with self.assertRaises(NotImplementedError):
            float(self.mat)
        with self.assertRaises(NotImplementedError):
            int(self.mat)
        with self.assertRaises(NotImplementedError):
            self.mat | self.mat
        with self.assertRaises(NotImplementedError):
            self.mat & self.mat
        with self.assertRaises(NotImplementedError):
            self.mat ^ self.mat
        with self.assertRaises(NotImplementedError):
            self.mat << 2
        with self.assertRaises(NotImplementedError):
            self.mat >> 2
        with self.assertRaises(NotImplementedError):
            ~self.mat
        with self.assertRaises(NotImplementedError):
            abs(self.mat)
        self.assertEqual(+self.mat, self.mat)
        self.assertEqual(-self.mat, self.mat * -1)
        self.assertTrue(bool(self.mat))
