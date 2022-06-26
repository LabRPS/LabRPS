#ifndef THREEPARAMODULATIONDIALOG_H
#define THREEPARAMODULATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ThreeParaModulationDialog;
}

class ThreeParaModulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThreeParaModulationDialog(double alpha, double betta, double lambda, QWidget *parent = nullptr);
    ~ThreeParaModulationDialog();

private:
    Ui::ThreeParaModulationDialog *ui;

private slots:
    void acceptInput();

public:
    double m_dAlpha;
    double m_dBeta;
    double m_dLambda;

};

#endif // THREEPARAMODULATIONDIALOG_H
