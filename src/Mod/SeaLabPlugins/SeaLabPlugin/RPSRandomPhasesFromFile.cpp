

#include "RPSRandomPhasesFromFile.h"
#include "Widgets/DlgRandomPhasesFromFile.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <Base/Console.h>
#include <Gui/Control.h>

using namespace SeaLab;
using namespace SeaLabAPI;

PROPERTY_SOURCE(SeaLab::CRPSRandomPhasesFromFile, SeaLabAPI::SeaLabFeatureRandomness)

CRPSRandomPhasesFromFile::CRPSRandomPhasesFromFile()
{
  ADD_PROPERTY_TYPE(WorkingDirectory, (""), "Parameters", App::Prop_None, "The directory to import the random phase angles from");
   this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_SeaLab#Uniform_Random_Phases_Import");

}

bool CRPSRandomPhasesFromFile::GenerateRandomCubeFPS(const SeaLabAPI::SeaLabSimulationData& Data, cube& dRandomValueCube)
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


bool CRPSRandomPhasesFromFile::GenerateRandomMatrixFP(const SeaLabAPI::SeaLabSimulationData& Data, mat &dRandomValueArray)
{
  int errorCode = ReadPhaseAngleFromFile(Data, WorkingDirectory.getValue(), dRandomValueArray);
  if (errorCode != 1)
      return false;
  return true;

}
bool CRPSRandomPhasesFromFile::ComputeRandomValue(const SeaLabAPI::SeaLabSimulationData& Data, double &dValue)
{
return false;
}

bool CRPSRandomPhasesFromFile::OnInitialSetting(const SeaLabAPI::SeaLabSimulationData& Data)
{
    SeaLabGui::DlgRandomPhasesFromFileEdit* dlg = new SeaLabGui::DlgRandomPhasesFromFileEdit(WorkingDirectory, Data.randomnessProvider);
	Gui::Control().showDialog(dlg);
    return true;
}


bool CRPSRandomPhasesFromFile::GetFilePathButton()
{
  QString filter = "Text files (*.txt)";

  QString fn = QFileDialog::getOpenFileName(0,"Import random phases from file", WorkingDirectory.getValue(), filter);
  if (!fn.isEmpty()) {
    QFileInfo fi(fn);
      WorkingDirectory.setValue(fi.absoluteFilePath().toUtf8().constData());
  }

  return true;
}

int CRPSRandomPhasesFromFile::ReadPhaseAngleFromFile(const SeaLabAPI::SeaLabSimulationData& Data, QString file_path, mat &dRandomValueArray)
{
    QFile file(file_path);
    if (!file.exists()) {
        Base::Console().Warning("Couldn't find the random phase file\n");
        return 0;
    }
    else {}

    if (dRandomValueArray.rows() != Data.numberOfFrequency.getValue()) {
        Base::Console().Warning(
            "The random phase angles importing has failed because the number of rows in the files "
            "does not match the number of simulation points.\n");
        return 0;
    }
    if (dRandomValueArray.cols() != Data.numberOfSpatialPosition.getValue()) {
        Base::Console().Warning(
            "The random phase angles importing has failed because the number of rows in the files "
            "does not match the number of simulation points.\n");
        return 0;
    }

    QFile inputFile(file_path);

    if (inputFile.open(QIODevice::ReadOnly)) {

        QString line;

        QTextStream in(&inputFile);
        for (int j = 0; j < Data.numberOfFrequency.getValue(); j++) {
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

