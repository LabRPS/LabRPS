#ifndef RPSWLSKEWNESSDLG_H
#define RPSWLSKEWNESSDLG_H

#include <QDialog>

namespace Ui {
class RPSWLSkewnessDlg;
}

class RPSWLSkewnessDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLSkewnessDlg(QWidget *parent = nullptr);
    ~RPSWLSkewnessDlg();

private slots:

     void comboBoxSkewnessFnIndexChanged(int index);
     void OnBnClickedSkewnessInit();


private:
    Ui::RPSWLSkewnessDlg *ui;

public:
   QString skewness;
};

#endif // RPSWLSKEWNESSDLG_H
