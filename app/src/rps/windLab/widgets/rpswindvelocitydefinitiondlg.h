#ifndef RPSWINDVELOCITYDEFINITIONDLG_H
#define RPSWINDVELOCITYDEFINITIONDLG_H

#include <QDialog>

namespace Ui {
class RPSWindVelocityDefinitionDlg;
}

class RPSWindVelocityDefinitionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWindVelocityDefinitionDlg(QWidget *parent = nullptr);
    ~RPSWindVelocityDefinitionDlg();

    private slots:
void comboBoxSpatialDistrIndexChanged(int index);
void radioButtonStationarityToggled(bool);
void radioButtonNonStationarityToggled(bool);
void radioButtonGaussianityToggled(bool);
void radioButtonNonGaussianityToggled(bool);
void OnBnClickedSpatialDistrInit();

private:
    Ui::RPSWindVelocityDefinitionDlg *ui;

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
};

#endif // RPSWINDVELOCITYDEFINITIONDLG_H
