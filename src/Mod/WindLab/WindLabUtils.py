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

__title__ = "WindLab Gui Utils"
__author__ = "Koffi Daniel"
__url__ = "https://www.labrps.com"

## \addtogroup WINDLAB
#  @{

import WindLabGui
import LabRPS as App

def showSimulationPoints():
    sim = WindLabGui.getActiveSimulation()
    simPoints = sim.computeLocationCoordinateMatrixP3()
    App.ActiveDocument.openTransaction("Sim_Points")
    group = App.ActiveDocument.addObject("App::DocumentObjectGroup", "Sim_Points")
    for i in range(sim.getSimulationData().numberOfSpatialPosition):
        vertex = App.ActiveDocument.addObject('Part::Vertex', 'Point_%d' % simPoints[i][0])
        vertex.X = simPoints[i][1]
        vertex.Y = simPoints[i][2]
        vertex.Z = simPoints[i][3]
        vertex.ViewObject.PointSize = 20.00
        vertex.ViewObject.PointColor = (255,255,255)
        group.addObject(vertex)
    sim.addObject(group)
    App.ActiveDocument.recompute()

def findAllVertexes():
    points = []
    for obj in App.ActiveDocument.Objects:
        if hasattr(obj,"Shape"):
           shape = obj.Shape
           if hasattr(shape,"Vertexes"):
              for Vertex in shape.Vertexes:
                  points.append(Vertex)
    arr = []
    rows, cols= len(points), 4
    for i in range(rows):
        row = []
        row.append(i + 1)
        row.append(points[i].X)
        row.append(points[i].Y)
        row.append(points[i].Z)
        arr.append(row)

    if App.GuiUp:
        import WindLabGui
        WindLabGui.WindLabPyTool.showArray(rows, cols, arr)
        print(arr)
##  @}