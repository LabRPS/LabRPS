#ifndef RPSSELCOHERENCEDLG_H
#define RPSSELCOHERENCEDLG_H

#include <QDialog>

namespace Ui {
class RPSSeLCoherenceDlg;
}

class RPSSeLCoherenceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSSeLCoherenceDlg(QWidget *parent = nullptr);
    ~RPSSeLCoherenceDlg();

private slots:

     void comboBoxCoherenceFnIndexChanged(int index);
     void OnBnClickedCoherenceFnInit();


private:
    Ui::RPSSeLCoherenceDlg *ui;

public:
   QString coherenceFunction;
};

#endif // RPSSELCOHERENCEDLG_H
