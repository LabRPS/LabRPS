#ifndef RPSGROUNDMOTIONDEFINITIONDLG_H
#define RPSGROUNDMOTIONDEFINITIONDLG_H

#include <QDialog>

namespace Ui {
class RPSGroundMotionDefinitionDlg;
}

class RPSGroundMotionDefinitionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSGroundMotionDefinitionDlg(QWidget *parent = nullptr);
    ~RPSGroundMotionDefinitionDlg();

private slots:
void comboBoxSpatialDistrIndexChanged(int index);
void comboBoxSoilTypeIndexChanged(int index);
void radioButtonStationarityToggled(bool);
void radioButtonNonStationarityToggled(bool);
void radioButtonGaussianityToggled(bool);
void radioButtonNonGaussianityToggled(bool);
void OnBnClickedSpatialDistrInit();

private:
    Ui::RPSGroundMotionDefinitionDlg *ui;

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
	 QString soilType;

};

#endif // RPSGROUNDMOTIONDEFINITIONDLG_H
