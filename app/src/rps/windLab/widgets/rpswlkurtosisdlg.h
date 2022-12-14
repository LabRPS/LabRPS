#ifndef RPSWLKURTOSISDLG_H
#define RPSWLKURTOSISDLG_H

#include <QDialog>

namespace Ui {
class RPSWLKurtosisDlg;
}

class RPSWLKurtosisDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLKurtosisDlg(QWidget *parent = nullptr);
    ~RPSWLKurtosisDlg();

private slots:

     void comboBoxKurtosisFnIndexChanged(int index);
     void OnBnClickedKurtosisInit();


private:
    Ui::RPSWLKurtosisDlg *ui;

public:
   QString kurtosis;
};

#endif // RPSWLKURTOSISDLG_H
