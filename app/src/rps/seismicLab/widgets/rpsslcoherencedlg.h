#ifndef RPSSLCOHERENCEDLG_H
#define RPSSLCOHERENCEDLG_H

#include <QDialog>

namespace Ui {
class RPSSLCoherenceDlg;
}

class RPSSLCoherenceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSLCoherenceDlg(QWidget *parent = nullptr);
    ~RPSSLCoherenceDlg();

private slots:

     void comboBoxCoherenceFnIndexChanged(int index);
     void OnBnClickedCoherenceFnInit();


private:
    Ui::RPSSLCoherenceDlg *ui;

public:
   QString coherenceFunction;
};

#endif // RPSSLCOHERENCEDLG_H
