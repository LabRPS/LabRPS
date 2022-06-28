#include "RPSSLRandomPhasesFromFile.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>


// the path to the file 
QString mstrRPFilePath;

void CRPSSLRandomPhasesFromFile::GenerateRandomArrayFP(const CRPSSeaLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	ReadPhaseAngleFromFile(Data, mstrRPFilePath, dRandomValueArray, strInformation);

}
void CRPSSLRandomPhasesFromFile::ComputeRandomValue(const CRPSSeaLabsimuData &Data, double &dValue, QStringList &strInformation)
{

}

bool CRPSSLRandomPhasesFromFile::OnInitialSetting(const CRPSSeaLabsimuData &Data, QStringList &strInformation)
{
	GetFilePathButton();

	return true;
}


void CRPSSLRandomPhasesFromFile::GetFilePathButton()
{
  QString filter = "Text files (*.txt)";

  QString fn = QFileDialog::getOpenFileName(0,"Import random phases from file",
                                            mstrRPFilePath, filter);
  if (!fn.isEmpty()) {
    QFileInfo fi(fn);
    mstrRPFilePath = fi.absoluteFilePath();
    // return importImage(fn);

	QMessageBox::warning(
        0, "Path",
        mstrRPFilePath);
  }
}

int CRPSSLRandomPhasesFromFile::ReadPhaseAngleFromFile(const CRPSSeaLabsimuData &Data, QString file_path, mat &dRandomValueArray, QStringList &strInformation)
{
    QFile file(file_path);
    if(!file.exists()){
		strInformation.append("Couldn't find the random phase file");
		return 0;
    }else{
       
    }

    QString line;   
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        // FOR EACH ROW
	          for (int j = 0; j < Data.numberOfFrequency; j++)
	          {
				     // FOR EACH COL
		          for (int k = 0; k < Data.numberOfSpatialPosition; k++)
		          {
			          // FOR EACH ROW AND COL
			          stream >> dRandomValueArray(j, k);
		          }
	          }
    }
    file.close();

return 1;
}
