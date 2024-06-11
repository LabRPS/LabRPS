#***************************************************************************
#*   Copyright (c) 2011 Yorik van Havre <yorik@uncreated.net>              *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Library General Public License for more details.                  *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with this program; if not, write to the Free Software   *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#***************************************************************************

__title__  = "WindLab Mean Wind Profile"
__author__ = "Koffi Daniel"
__url__    = "https://www.labrps.com"

## \defgroup ARCH Arch
#  \ingroup PYTHONWORKBENCHES
#  \brief Architecture and BIM tools
#
#  This module provides tools specialized in Building Information Modeling (BIM).
#  such as convenience tools to build walls, windows or structures, and
#  IFC import/export capabilities.

'''The WindLabTools provide tools for the calculation involved in WindLab. This is where all the computations happen in all WindLab built-in features'''


import LabRPS
if LabRPS.GuiUp:
	import LabRPSGui
	LabRPSGui.updateLocale()

# from LocationDistribution import *



