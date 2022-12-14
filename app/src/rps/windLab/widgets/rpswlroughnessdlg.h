#ifndef RPSWLROUGHNESSDLG_H
#define RPSWLROUGHNESSDLG_H

#include <QDialog>

namespace Ui {
class RPSWLRoughnessDlg;
}

class RPSWLRoughnessDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLRoughnessDlg(QWidget *parent = nullptr);
    ~RPSWLRoughnessDlg();

private slots:

     void comboBoxRoughnessFnIndexChanged(int index);
     void OnBnClickedRoughnessInit();


private:
    Ui::RPSWLRoughnessDlg *ui;

public:
   QString roughness;
};

#endif // RPSWLROUGHNESSDLG_H
