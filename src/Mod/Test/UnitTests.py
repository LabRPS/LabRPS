# -*- coding: utf-8 -*-
#***************************************************************************
#*   Copyright (c) 2010 Juergen Riegel <juergen.riegel@web.de>             *
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

import LabRPS
import unittest
import math

def tu(str):
    return LabRPS.Units.Quantity(str).Value

def ts(q):
    return q.UserString

def ts2(q):
    return LabRPS.Units.Quantity(q.UserString).UserString


#---------------------------------------------------------------------------
# define the functions to test the LabRPS UnitApi code
#---------------------------------------------------------------------------


def compare(x, y):
    return math.fabs(x - y) < 0.00001


class UnitBasicCases(unittest.TestCase):
    def setUp(self):
        par = LabRPS.ParamGet("User parameter:BaseApp/Preferences/Units")
        dec = par.GetInt("Decimals")
        self.delta = math.pow(10,-dec)

    def testConversions(self):
        #tu = LabRPS.Units.translateUnit
        self.failUnless(compare(tu('10 m'), 10000.0))
        self.failUnless(compare(tu('3/8 in'), 9.525))
        self.failUnless(compare(tu('100 km/h'), 27777.77777777))
        self.failUnless(compare(tu('m^2*kg*s^-3*A^-2'), 1000000.0))
        self.failUnless(compare(tu('(m^2*kg)/(A^2*s^3)'), 1000000.0))
        self.failUnless(compare(tu('2*pi rad'), 360.0))
        self.failUnless(compare(tu('2*pi rad') / tu('gon'), 400.0))
        self.failUnless(compare(tu('999 kg') / tu('1 m^3'), 0.000009999))

    def testImperial(self):
        #tu = LabRPS.Units.translateUnit
        self.failUnless(compare(tu('3/8in'), 9.525))
        #self.failUnless(compare(tu('1fo(3+7/16)in'),392.112500))thisgivesaparsersyntaxerror!!!
        self.failUnless(compare(tu('1\'(3+7/16)"'), 392.112500))

        psi = LabRPS.Units.parseQuantity("1psi")
        mpa = psi.getValueAs("MPa").Value
        self.assertAlmostEqual(0.006894744825, mpa, delta=self.delta)
        kpa = psi.getValueAs("kPa").Value
        self.assertAlmostEqual(6.894744825494, kpa, delta=self.delta)

        ksi = LabRPS.Units.parseQuantity("1ksi")
        mpa = ksi.getValueAs("MPa").Value
        self.assertAlmostEqual(6.894744825494, mpa, delta=self.delta)
        kpa = ksi.getValueAs("kPa").Value
        self.assertAlmostEqual(6894.744825494, kpa, delta=self.delta)

    def testSelfConsistency(self):
        qu = LabRPS.Units.Quantity("0.23 W/m/K")
        self.assertTrue(ts(qu), ts2(qu))
        qu = LabRPS.Units.Quantity("237 mm*kg/(s^3*K)")
        self.assertTrue(ts(qu), ts2(qu))
        qu = LabRPS.Units.Quantity("237.000 W/mm/K")
        self.assertTrue(ts(qu), ts2(qu))

    def testDivide(self):
        qu1 = LabRPS.Units.Quantity("1 m/s")
        qu2 = LabRPS.Units.Quantity("m/s")
        self.assertTrue(qu1/qu2, 1)

    def testSchemes(self):
        schemes = LabRPS.Units.listSchemas()
        num = len(schemes)

        psi = LabRPS.Units.parseQuantity("1psi")
        for i in range(num):
            t = LabRPS.Units.schemaTranslate(psi, i)
            v = LabRPS.Units.parseQuantity(t[0]).getValueAs("psi")
            self.assertAlmostEqual(1, v.Value, msg="Failed with \"{0}\" scheme: {1} != 1 (delta: {2})".format(schemes[i], v.Value, self.delta), delta=self.delta)

        ksi = LabRPS.Units.parseQuantity("1ksi")
        for i in range(num):
            t = LabRPS.Units.schemaTranslate(ksi, i)
            v = LabRPS.Units.parseQuantity(t[0]).getValueAs("ksi")
            self.assertAlmostEqual(1, v.Value, msg="Failed with \"{0}\" scheme: {1} != 1 (delta: {2})".format(schemes[i], v.Value, self.delta), delta=self.delta)

    def testSchemeTranslation(self):
        quantities = []
        for i in dir(LabRPS.Units):
            if issubclass(type(getattr(LabRPS.Units, i)), LabRPS.Units.Quantity):
                quantities.append(i)

        schemes = LabRPS.Units.listSchemas()
        for i in quantities:
            q1 = getattr(LabRPS.Units, i)
            q1 = LabRPS.Units.Quantity(q1)
            q1.Format = {'Precision': 16}
            for idx, val in enumerate(schemes):
                [t, amountPerUnit, unit] = LabRPS.Units.schemaTranslate(q1, idx)
                try:
                    q2 = LabRPS.Units.Quantity(t)
                    if math.fabs(q1.Value - q2.Value) > 0.01:
                        print (" {} : {} : {} : {} : {}".format(q1, q2, t, i, val).encode("utf-8").strip())
                except Exception as e:
                    print ("{} : {} : {} : {}".format(q1, i, val, e).encode("utf-8").strip())

    def testVoltage(self):
        q1 = LabRPS.Units.Quantity("1e20 V")
        t = LabRPS.Units.schemaTranslate(q1, 0) # Standard
        q2 = LabRPS.Units.Quantity(t[0])
        self.assertAlmostEqual(q1.Value, q2.Value, delta=self.delta)

    def testEnergy(self):
        q1 = LabRPS.Units.Quantity("1e20 J")
        t = LabRPS.Units.schemaTranslate(q1, 0) # Standard
        q2 = LabRPS.Units.Quantity(t[0])
        self.assertAlmostEqual(q1.Value, q2.Value, delta=self.delta)

    def testTrigonometric(self):
        #tu=LabRPS.Units.translateUnit
        self.failUnless(compare(tu('sin(pi)'), math.sin(math.pi)))
        self.failUnless(compare(tu('cos(pi)'), math.cos(math.pi)))
        self.failUnless(compare(tu('tan(pi)'), math.tan(math.pi)))

    def testQuantity(self):
        length = LabRPS.Units.Quantity(1, "m")
        self.assertEqual(length.Value, 1000)
        self.assertEqual(length.Unit, LabRPS.Units.Length)

    def testToString(self):
        value = LabRPS.Units.toNumber(1023, 'g', 2)
        self.assertEqual(float(value), 1000)

        value = LabRPS.Units.toNumber(1023, 'g', 3)
        self.assertEqual(float(value), 1020)

        value = LabRPS.Units.toNumber(1023, 'f', 2)
        self.assertEqual(float(value), 1023)

        value = LabRPS.Units.toNumber(1023, 'e', 1)
        self.assertEqual(float(value), 1000)

        value = LabRPS.Units.toNumber(1023, 'e', 2)
        self.assertEqual(float(value), 1020)

        value = LabRPS.Units.toNumber(1023, 'e', 3)
        self.assertEqual(float(value), 1023)

        q = LabRPS.Units.Quantity("1023")
        value = LabRPS.Units.toNumber(q, 'f', 2)
        self.assertEqual(float(value), 1023)

        with self.assertRaises(TypeError):
            LabRPS.Units.toNumber("1023", 'g', 2)
        with self.assertRaises(ValueError):
            LabRPS.Units.toNumber(1023, 'gg', 2)
        with self.assertRaises(ValueError):
            LabRPS.Units.toNumber(1023, 's', 2)

    def testIssue6735(self):
        LabRPS.Units.Quantity("1400.0 N/mm^2")
