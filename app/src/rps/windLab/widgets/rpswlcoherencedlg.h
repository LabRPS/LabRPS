#ifndef RPSWLCOHERENCEDLG_H
#define RPSWLCOHERENCEDLG_H

#include <QDialog>

namespace Ui {
class RPSWLCoherenceDlg;
}

class RPSWLCoherenceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLCoherenceDlg(QWidget *parent = nullptr);
    ~RPSWLCoherenceDlg();

private slots:

     void comboBoxCoherenceFnIndexChanged(int index);
     void OnBnClickedCoherenceFnInit();


private:
    Ui::RPSWLCoherenceDlg *ui;

public:
   QString coherenceFunction;
};

#endif // RPSWLCOHERENCEDLG_H
