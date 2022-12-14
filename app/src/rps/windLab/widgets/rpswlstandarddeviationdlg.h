#ifndef RPSWLSTANDARDDEVIATIONDLG_H
#define RPSWLSTANDARDDEVIATIONDLG_H

#include <QDialog>

namespace Ui {
class RPSWLStandardDeviationDlg;
}

class RPSWLStandardDeviationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLStandardDeviationDlg(QWidget *parent = nullptr);
    ~RPSWLStandardDeviationDlg();

private slots:

     void comboBoxStandardDeviationFnIndexChanged(int index);
     void OnBnClickedStandardDeviationInit();


private:
    Ui::RPSWLStandardDeviationDlg *ui;

public:
   QString standardDeviation;
};

#endif // RPSWLSTANDARDDEVIATIONDLG_H
