#ifndef CRPSWLRUNMATRIXTOOLSDLG_H
#define CRPSWLRUNMATRIXTOOLSDLG_H

#include <QDialog>

namespace Ui {
class CRPSWLRunMatrixToolsDlg;
}

class CRPSWLRunMatrixToolsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CRPSWLRunMatrixToolsDlg(QWidget *parent = nullptr);
    ~CRPSWLRunMatrixToolsDlg();

private:
    Ui::CRPSWLRunMatrixToolsDlg *ui;

private slots:
void comboBoxRunToolsIndexChanged(int index);
void acceptInput();
void OnBnClickedMatrixToolInit();

public:

     QString matrixTool;

};

#endif // CRPSWLRUNMATRIXTOOLSDLG_H

