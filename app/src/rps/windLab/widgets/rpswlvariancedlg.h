#ifndef RPSWLVARIANCEDLG_H
#define RPSWLVARIANCEDLG_H

#include <QDialog>

namespace Ui {
class RPSWLVarianceDlg;
}

class RPSWLVarianceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLVarianceDlg(QWidget *parent = nullptr);
    ~RPSWLVarianceDlg();

private slots:

     void comboBoxVarianceFnIndexChanged(int index);
     void OnBnClickedVarianceInit();


private:
    Ui::RPSWLVarianceDlg *ui;

public:
   QString variance;
};

#endif // RPSWLVARIANCEDLG_H
