#ifndef RPSSELPSDDEFINITIONDIALOG_H
#define RPSSELPSDDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class RPSSeLPSDDefinitionDialog;
}

class RPSSeLPSDDefinitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSeLPSDDefinitionDialog(QWidget *parent = nullptr);
    ~RPSSeLPSDDefinitionDialog();

private:
    Ui::RPSSeLPSDDefinitionDialog *ui;

private slots:
    void comboBoxPSDModelIndexChanged(int index);
    void comboBoxPSDdecompIndexChanged(int index);
    void comboBoxDirSpreadingIndexChanged(int index);
    void comboBoxDirPSDIndexChanged(int index);
    void comboBoxFrequencyDistrIndexChanged(int index);
    void comboBoxDirDistrIndexChanged(int index);
    void OnBnClickedPSDModelInit();
    void OnBnClickedPSDdecompInit();
    void OnBnClickedDirSpreadingInit();
    void OnBnClickedDirPSDInit();
    void OnBnClickedFrequencyDistrInit();
    void OnBnClickedDirDistrInit();
    void acceptInput();

public:

	double numberOfFrequency;
	double minFrequency;
	double maxFrequency;
	double frequencyIncrement;
	double numberOfDirection;
	double minDirection;
	double maxDirection;
	double directionIncrement;
    QString spectrumModel;
    QString cpsdDecompositionMethod;
    QString freqencyDistribution;
    QString directionDistributionFunction;
    QString directionSpreadingFunction;
    QString directionalSpectrumFunction;
};

#endif // RPSSELPSDDEFINITIONDIALOG_H
