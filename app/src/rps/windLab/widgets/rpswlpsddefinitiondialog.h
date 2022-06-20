#ifndef RPSWLPSDDEFINITIONDIALOG_H
#define RPSWLPSDDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLPSDDefinitionDialog;
}

class RPSWLPSDDefinitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLPSDDefinitionDialog(QWidget *parent = nullptr);
    ~RPSWLPSDDefinitionDialog();

private:
    Ui::RPSWLPSDDefinitionDialog *ui;

private slots:
    void comboBoxPSDModelIndexChanged(int index);
    void comboBoxPSDdecompIndexChanged(int index);
    void comboBoxFrequencyDistrIndexChanged(int index);
    void OnBnClickedPSDModelInit();
    void OnBnClickedPSDdecompInit();
    void OnBnClickedFrequencyDistrInit();
    void radioButtonAlongWindToggled(bool);
    void radioButtonCrossWindToggled(bool);
    void radioButtonVerticalWindToggled(bool);

    void acceptInput();

public:

	double numberOfFrequency;
	double minFrequency;
	double maxFrequency;
	double frequencyIncrement;
    QString spectrumModel;
    QString cpsdDecompositionMethod;
    QString freqencyDistribution;
    int windDirection;
;

};

#endif // RPSWLPSDDEFINITIONDIALOG_H
