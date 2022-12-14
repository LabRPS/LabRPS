#ifndef RPSWLWAVEPASSAGEEFFECTDLG_H
#define RPSWLWAVEPASSAGEEFFECTDLG_H

#include <QDialog>

namespace Ui {
class RPSWLWavePassageEffectDlg;
}

class RPSWLWavePassageEffectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLWavePassageEffectDlg(QWidget *parent = nullptr);
    ~RPSWLWavePassageEffectDlg();

private slots:

     void comboBoxWavePassageEffectFnIndexChanged(int index);
     void OnBnClickedWavePassageEffectInit();


private:
    Ui::RPSWLWavePassageEffectDlg *ui;

public:
   QString wavePassageEffect;
};

#endif // RPSWLWAVEPASSAGEEFFECTDLG_H
