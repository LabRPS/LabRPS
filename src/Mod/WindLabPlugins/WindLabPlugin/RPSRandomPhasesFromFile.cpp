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

#include "RPSRandomPhasesFromFile.h"
#include "Widgets/DlgRandomPhasesFromFile.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace WindLab;
using namespace WindLabAPI;

PROPERTY_SOURCE(WindLab::CRPSRandomPhasesFromFile, WindLabAPI::WindLabFeatureRandomness)

CRPSRandomPhasesFromFile::CRPSRandomPhasesFromFile()
{
  ADD_PROPERTY_TYPE(FilePath, (""), "Parameters", App::Prop_None, "The directory to import the random phase angles from");
}

bool CRPSRandomPhasesFromFile::GenerateRandomCubeFPS(const WindLabAPI::WindLabSimulationData &Data, cube &dRandomValueCube)
{
    mat randomPhaseMatrix(dRandomValueCube.dimension(0), dRandomValueCube.dimension(1));
    GenerateRandomMatrixFP(Data, randomPhaseMatrix);
    for (int k = 0; k < dRandomValueCube.dimension(2);
         ++k) {// Iterate over the first dimension (depth)
        for (int i = 0; i < dRandomValueCube.dimension(0);
             ++i) {// Iterate over the second dimension (rows)
            for (int j = 0; j < dRandomValueCube.dimension(1);
                 ++j) {// Iterate over the third dimension (columns)
                dRandomValueCube(i, j, k) = randomPhaseMatrix(i, j);
            }
        }
    } 

  return true;
}

bool CRPSRandomPhasesFromFile::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimulationData& Data, mat &dRandomValueArray)
{
  int errorCode = ReadPhaseAngleFromFile(Data, FilePath.getValue(), dRandomValueArray);
    if (errorCode != 1)
        return false;
  return true;

}
bool CRPSRandomPhasesFromFile::ComputeRandomValue(const WindLabAPI::WindLabSimulationData& Data, double &dValue)
{
return false;
}

bool CRPSRandomPhasesFromFile::OnInitialSetting(const WindLabAPI::WindLabSimulationData& Data)
{
    WindLabGui::DlgRandomPhasesFromFileEdit* dlg = new WindLabGui::DlgRandomPhasesFromFileEdit(FilePath, Data.randomnessProvider);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CRPSRandomPhasesFromFile::GetFilePathButton()
{
  QString filter = "Text files (*.txt)";

  QString fn = QFileDialog::getOpenFileName(0,"Import random phases from file", FilePath.getValue(), filter);
  if (!fn.isEmpty()) {
    QFileInfo fi(fn);
      FilePath.setValue(fi.absoluteFilePath().toUtf8().constData());
  }

  return true;
}

int CRPSRandomPhasesFromFile::ReadPhaseAngleFromFile(const WindLabAPI::WindLabSimulationData& Data, QString file_path, mat &dRandomValueArray)
{
    QFile file(file_path);
    if(!file.exists()){
		Base::Console().Warning("Couldn't find the random phase file\n");
		return 0;
    }else{
       
    }

    if (dRandomValueArray.rows() != Data.numberOfFrequency.getValue())
    {
        Base::Console().Error("The random phase angles importing has failed because the number of rows in the files does not match the number of simulation points.\n");
        return 0;
    }
    if (dRandomValueArray.cols() != Data.numberOfSpatialPosition.getValue())
    {
        Base::Console().Error("The random phase angles importing has failed because the number of rows in the files does not match the number of simulation points.\n");
        return 0;
    }

 QFile inputFile(file_path);

    if (inputFile.open(QIODevice::ReadOnly)) {
     
     QString line;

     QTextStream in(&inputFile);
        for (int j = 0; j < Data.numberOfFrequency.getValue(); j++)
	    {
            if (!in.atEnd()) {
                line = in.readLine();
                QStringList fields = line.split('\t');
                if (fields.size() != Data.numberOfSpatialPosition.getValue())
                {
                    Base::Console().Error("The number of columns in the file does not match the number of the simulation points.\n");
                    return 0;
                }

                 // FOR EACH COL
                for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++) {

                    // FOR EACH ROW AND COL
                    dRandomValueArray(j, k) = fields[k].toDouble();
                }
            }
	 
	    }

        inputFile.close();
    }

return 1;
}

