/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
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

#ifndef WINDLAB_PLUGIN_IMPORTSIMULATIONPOINTSFROMFILE_H
#define WINDLAB_PLUGIN_IMPORTSIMULATIONPOINTSFROMFILE_H

#include <Mod/WindLabAPI/App/IrpsWLLocationDistribution.h>

namespace WindLabAPI { class WindLabSimuData; }

class QStringList;

namespace WindLab {

class CRPSImportSimulationPointsFromFile : public WindLabAPI::IrpsWLLocationDistribution
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLab::CRPSImportSimulationPointsFromFile);

public:

	CRPSImportSimulationPointsFromFile();

	~CRPSImportSimulationPointsFromFile() {};
	
	bool ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord);
	
	bool OnInitialSetting(const WindLabAPI::WindLabSimuData& Data);

	int ReadSimulationPointsFromFile(const WindLabAPI::WindLabSimuData& Data, QString strFilePath, mat &dRandomValueArray);
	
	bool GetFilePathButton();

public:
    App::PropertyString WorkingDirectory;

};

}

#endif  // WINDLAB_PLUGIN_IMPORTSIMULATIONPOINTSFROMFILE_H