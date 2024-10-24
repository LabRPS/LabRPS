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

#include "RPSImportSimulationPointsFromFile.h"
#include "Widgets/DlgImportSimulationPointsFromFile.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <Base/Console.h>
#include <Gui/Control.h>
#include <Base/Interpreter.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSImportSimulationPointsFromFile, WindLabAPI::WindLabFeatureLocationDistribution)

CRPSImportSimulationPointsFromFile::CRPSImportSimulationPointsFromFile()
{
  ADD_PROPERTY_TYPE(WorkingDirectory, (""), "Parameters", App::Prop_None, "The directory to import the simulation points from");
}


bool CRPSImportSimulationPointsFromFile::ComputeLocationCoordinateMatrixP3(const WindLabAPI::WindLabSimuData& Data, mat &dLocCoord)
{
    ReadSimulationPointsFromFile(Data, WorkingDirectory.getValue(), dLocCoord);
    return true;
}

bool CRPSImportSimulationPointsFromFile::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    WindLabGui::DlgImportSimulationPointsFromFileEdit* dlg = new WindLabGui::DlgImportSimulationPointsFromFileEdit(WorkingDirectory, Data.spatialDistribution);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CRPSImportSimulationPointsFromFile::GetFilePathButton()
{
  QString filter = "Text files (*.txt)";

  QString fn = QFileDialog::getOpenFileName(0,"Import simulation point from file", WorkingDirectory.getValue(), filter);
  if (!fn.isEmpty()) {
    QFileInfo fi(fn);
     WorkingDirectory.setValue(fi.absoluteFilePath().toUtf8().constData());
  }

  return true;
}

int CRPSImportSimulationPointsFromFile::ReadSimulationPointsFromFile(const WindLabAPI::WindLabSimuData& Data, QString file_path, mat &dPointArray)
{
    QFile inputFile(file_path);

    if (inputFile.open(QIODevice::ReadOnly)) {
     
     QString line;

     QTextStream in(&inputFile);
        for (int j = 0; j < Data.numberOfSpatialPosition.getValue(); j++)
	    {
            if (!in.atEnd()) {
                line = in.readLine();
                QStringList fields = line.split('\t');

                 // FOR EACH COL
                for (int k = 0; k < 4; k++) {

                    // FOR EACH ROW AND COL
                    dPointArray(j, k) = fields[k].toDouble();
                }
            }
	 
	    }

        inputFile.close();
    }

return 1;
}
