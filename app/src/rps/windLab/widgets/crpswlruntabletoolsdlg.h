#ifndef CRPSWLRUNTABLETOOLSDLG_H
#define CRPSWLRUNTABLETOOLSDLG_H

#include <QDialog>

namespace Ui {
class CRPSWLRunTableToolsDlg;
}

class CRPSWLRunTableToolsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CRPSWLRunTableToolsDlg(QWidget *parent = nullptr);
    ~CRPSWLRunTableToolsDlg();

private:
    Ui::CRPSWLRunTableToolsDlg *ui;

private slots:
void comboBoxRunToolsIndexChanged(int index);
void acceptInput();
void OnBnClickedTableToolInit();

public:

     QString tableTool;

};

#endif // CRPSWLRUNTABLETOOLSDLG_H

