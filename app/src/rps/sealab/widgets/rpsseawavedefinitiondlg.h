#ifndef RPSSEAWAVEDEFINITIONDLG_H
#define RPSSEAWAVEDEFINITIONDLG_H

#include <QDialog>

namespace Ui {
class RPSSeaWaveDefinitionDlg;
}

class RPSSeaWaveDefinitionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSeaWaveDefinitionDlg(QWidget *parent = nullptr);
    ~RPSSeaWaveDefinitionDlg();

private slots:
void comboBoxSpatialDistrIndexChanged(int index);
void comboBoxWaveTypeIndexChanged(int index);
void radioButtonStationarityToggled(bool);
void radioButtonNonStationarityToggled(bool);
void radioButtonGaussianityToggled(bool);
void radioButtonNonGaussianityToggled(bool);
void OnBnClickedSpatialDistrInit();

private:
    Ui::RPSSeaWaveDefinitionDlg *ui;

private slots:
 void acceptInput();

public:

	 int numberOfSpatialPosition;
	 int numberOfTimeIncrements;
	 double timeIncrement;
	 double minTime;
	 double maxTime;
	 int numberOfSample;
	 bool stationarity;
	 bool gaussianity;
	 QString spatialDistribution;
	 QString waveType;

};

#endif // RPSSEAWAVEDEFINITIONDLG_H
