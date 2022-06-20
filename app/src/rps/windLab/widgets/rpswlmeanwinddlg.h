#ifndef RPSWLMEANCEDLG_H
#define RPSWLMEANCEDLG_H

#include <QDialog>

namespace Ui {
class RPSWLMeanDlg;
}

class RPSWLMeanDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLMeanDlg(QWidget *parent = nullptr);
    ~RPSWLMeanDlg();

private slots:

     void comboBoxMeanFnIndexChanged(int index);
     void OnBnClickedMeanFnInit();


private:
    Ui::RPSWLMeanDlg *ui;

public:
   QString meanFunction;
};

#endif // RPSWLMEANCEDLG_H
