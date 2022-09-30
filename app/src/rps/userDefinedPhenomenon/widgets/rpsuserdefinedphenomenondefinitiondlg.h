#ifndef RPSUSERDEFINEDPHENOMENONDEFINITIONDLG_H
#define RPSUSERDEFINEDPHENOMENONDEFINITIONDLG_H

#include <QDialog>

namespace Ui {
class RPSUserDefinedPhenomenonDefinitionDlg;
}

class RPSUserDefinedPhenomenonDefinitionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSUserDefinedPhenomenonDefinitionDlg(QWidget *parent = nullptr);
    ~RPSUserDefinedPhenomenonDefinitionDlg();

private slots:
void comboBoxUserDefinedPhenomenonChanged(int index);
void radioButtonStationarityToggled(bool);
void radioButtonNonStationarityToggled(bool);
void radioButtonGaussianityToggled(bool);
void radioButtonNonGaussianityToggled(bool);
void OnBnClickedUserDefinedPhenomenonInit();

private:
    Ui::RPSUserDefinedPhenomenonDefinitionDlg *ui;

private slots:
 void acceptInput();

public:

	 int numberOfProcess;
	 int indexSetSize;
	 double indexIncrement;
	 double minIndexSetValue;
	 double maxIndexSetValue;
	 int numberOfSample;
	 bool stationarity;
	 bool gaussianity;
	 QString userDefinedPhenomenon;
};

#endif // RPSUSERDEFINEDPHENOMENONDEFINITIONDLG_H
