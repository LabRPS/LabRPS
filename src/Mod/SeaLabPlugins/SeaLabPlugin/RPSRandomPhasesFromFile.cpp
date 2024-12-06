

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
  ReadPhaseAngleFromFile(Data, WorkingDirectory.getValue(), dRandomValueArray);
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
    if(!file.exists()){
		Base::Console().Warning("Couldn't find the random phase file\n");
		return 0;
    }else{
       
    }

    QString line;   
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        // FOR EACH ROW
	          for (int j = 0; j < Data.numberOfFrequency.getValue(); j++)
	          {
				     // FOR EACH COL
		          for (int k = 0; k < Data.numberOfSpatialPosition.getValue(); k++)
		          {
			          // FOR EACH ROW AND COL
			          stream >> dRandomValueArray(j, k);
		          }
	          }
    }
    file.close();

return 1;
}

