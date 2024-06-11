/***************************************************************************
 *   Copyright (c) 2024 the Team <theTeam@labrps.com>              *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef ALPHATPLOT_GRAPHTYPE_H
#define ALPHATPLOT_GRAPHTYPE_H

#include <Libraries/Alphaplot/AlphaplotGlobal.h>
#include <RPSConfig.h>

  enum class AlphaplotExport Graph {
    Line = 0,
    Scatter = 1,
    LineSymbols = 2,
    VerticalBars = 3,
    Area = 4,
    Pie = 5,
    VerticalDropLines = 6,
    Spline = 7,
    HorizontalSteps = 8,
    Histogram = 9,
    HorizontalBars = 10,
    VectXYXY = 11,
    ErrorBars = 12,
    Box = 13,
    VectXYAM = 14,
    VerticalSteps = 15,
    ColorMap = 16,
    GrayMap = 17,
    ContourMap = 18,
    Function = 19,
    Channel = 20,
    VerticalStackedBars = 21,
    HorizontalStackedBars = 22,
    VerticalGroupedBars = 23,
    HorizontalGroupedBars = 24,
    ScatterYError = 25,
    ScatterXError = 26,
    ScatterXYError = 27
  };


#endif // ALPHATPLOT_GRAPHTYPE_H
