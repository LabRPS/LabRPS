
#include "RPSRandomPhasesFromFile.h"
#include <iostream>
#include <fstream>

using namespace std;

// the path to the file onta
QString mstrRPFilePath;

bool CRPSRandomPhasesFromFile::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
	// GetFilePathButton();

	return true;
}

void CRPSRandomPhasesFromFile::GenerateRandomArrayFP(const CRPSWindLabsimuData &Data, mat &dRandomValueArray, QStringList &strInformation)
{
	// ReadPhaseAngleFromFile(Data, mstrRPFilePath, dRandomValueArray);

}



void CRPSRandomPhasesFromFile::GetFilePathButton()
{
	// int btnSel;																// button selection
	// ifstream fin;															// infile stream
	// ofstream fout;															// outfile stream
	// BOOL dlgType = FALSE;													// TRUE => File Open dlg, FALSE => File Save dlg
	// QString sCaption = ("Phase Angle - Overwrite");							// message box caption
	// QString strDefExt = ("txt");											// default file extension
	// QString strFileName = ("Phase_Angle.txt");							// file name		
	// QString strFilePath;													// local file path var
	// QString strReturnFileExt;													// local file extention
	// QString strFilter = ("All Files (*.*)|*.*|Plain Text (*.txt)|*.txt||");	// string pairs specifying filters for file list box
	// QString sMsg;															// main msg string
	// QString sMsgTemp;														// temp msg string
	// CWnd l_wnd;																// local CWnd
	// DWORD dwFlags = OFN_ENABLESIZING | OFN_HIDEREADONLY;					// customization flags
	// UINT nType = MB_OK;														// style of msg. box
	// UINT nIDhelp = 0;                                                       // help context ID for the msg.

	// // Create a CFileDialog wnd
	// CFileDialog dlgFile(!dlgType, strDefExt, strFileName, dwFlags, strFilter, NULL);

	// if (dlgFile.DoModal() == IDOK)
	// {
	// 	strFilePath = dlgFile.GetPathName();		// get the path name including file name and location
	// 	strReturnFileExt = dlgFile.GetFileExt();    // Get the extension of the file ( it should be ".txt")
	// 	//SetTitle(strFilePath);					// set the title of the document window

	// 	// Check if the file extension is right
		
	// 	if (strReturnFileExt != ("txt")) // If the extension of the selected file is different to ".txt" then tell the user that the selected file is invalid
	// 	{
	// 		sMsgTemp.Format((" Invalid file extension.  \n"));
	// 		sMsg += sMsgTemp;
	// 		nType = MB_OK;
	// 		btnSel = l_wnd.MessageBox(sMsg, sCaption, nType);
	// 	}

	// 	mstrRPFilePath = strFilePath;
	// }
}

int CRPSRandomPhasesFromFile::ReadPhaseAngleFromFile(const CRPSWindLabsimuData &Data, QString file_path, mat &dRandomValueArray)
{
	// int file_flag = 0;		// (0) no error, (1) error
	// ifstream fin;			// infile stream
	// QString sMsg;			// main msg string
	// QString sMsgTemp;		// temp msg string
	// UINT nType = MB_OK;		// style of msg. box
	// UINT nIDhelp = 0;		// help context ID for the msg

	// 						// Open file for reading
	// fin.open(file_path, ios::in);

	// if (!fin)		// if(!false) then execute
	// {
	// 	sMsg.Format((""));
	// 	sMsgTemp.Format((""));
	// 	sMsg += sMsgTemp;
	// 	sMsgTemp.Format(("\n Unable to open the file: %s\n"), file_path);
	// 	sMsg += sMsgTemp;
	// 	sMsgTemp.Format((" Aborting file opening.\n"));
	// 	sMsg += sMsgTemp;
	// 	AfxMessageBox(sMsg, nType, nIDhelp);

	// 	fin.close();
	// 	fin.clear();

	// 	file_flag = 1;		// error
	// 	return file_flag;
	// }

	// // Allocate memory
	// dRandomValueArray.set_size(Data.m_iNumberOfSpatialPosition, Data.m_iNumberOfFrequency);


	// // FOR EACH ROW
	// for (int j = 0; j < Data.m_iNumberOfSpatialPosition; j++)
	// {
	// 	// FOR EACH COL
	// 	for (int k = 0; k < Data.m_iNumberOfFrequency; k++)
	// 	{
	// 		// FOR EACH ROW AND COL
	// 		fin >> dRandomValueArray(j, k);
	// 	}
	// }

	// // Close the infile stream and clear fail flag
	// fin.close();

	// // clears fail flag setting from previous file i/o.
	// fin.clear();

	// return file_flag;

	return 0;
}

void CRPSRandomPhasesFromFile::ComputeRandomValue(const CRPSWindLabsimuData &Data, double &dValue, QStringList &strInformation)
{

}
