#**************************************************************************
#   Copyright (c) 2011 Juergen Riegel <LabRPS@juergen-riegel.net>        *
#   Copyright (c) 2021 Emmanuel O'Brien                                   *
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

# Broken-out test modules
from WindLabTests.TestWindLab import TestWindLab
from WindLabTests.TestWindFillet import TestWindFillet
from WindLabTests.TestWindExpression import TestWindExpression

# Path and PartDesign tests use these functions that used to live here
# but moved to WindLabTests/TestWindLab.py
from WindLabTests.TestWindLab import CreateCircleWind
from WindLabTests.TestWindLab import CreateRectangleWind
from WindLabTests.TestWindLab import CreateSlotPlateSet
