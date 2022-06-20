#ifndef RPSSLPSDDEFINITIONDIALOG_H
#define RPSSLPSDDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class RPSSLPSDDefinitionDialog;
}

class RPSSLPSDDefinitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSLPSDDefinitionDialog(QWidget *parent = nullptr);
    ~RPSSLPSDDefinitionDialog();

private:
    Ui::RPSSLPSDDefinitionDialog *ui;

private slots:
    void comboBoxPSDModelIndexChanged(int index);
    void comboBoxPSDdecompIndexChanged(int index);
    void comboBoxFrequencyDistrIndexChanged(int index);
    void OnBnClickedPSDModelInit();
    void OnBnClickedPSDdecompInit();
    void OnBnClickedFrequencyDistrInit();
    void radioButtonXDirectionToggled(bool);
    void radioButtonYDirectionToggled(bool);
    void radioButtonZDirectionToggled(bool);

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

#endif // RPSSLPSDDEFINITIONDIALOG_H
