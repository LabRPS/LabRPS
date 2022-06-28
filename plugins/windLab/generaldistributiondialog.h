#ifndef GENERALDISTRIBUTIONDIALOG_H
#define GENERALDISTRIBUTIONDIALOG_H

#include <QDialog>
#include "RPS.h"
namespace Ui {
class GeneralDistributionDialog;
}

class GeneralDistributionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneralDistributionDialog(int nomberOfPoints, mat& pointsMatrix, QWidget *parent = nullptr);
    ~GeneralDistributionDialog();
    void saveTableItemsToMatrix();
    void readTableItemsFromMatrix();


private:
    Ui::GeneralDistributionDialog *ui;

private slots:
    void acceptInput();
    void OnBnClickedTableAddRow();
    void OnBnClickedTableDeleteRow();
    void OnBnClickedTableDeleteAllRows();

public:
    mat m_pointsMatrix;
    int m_nomberOfPoint;
    QStringList m_information;

};

#endif // GENERALDISTRIBUTIONDIALOG_H
