#ifndef EXPOMODULATIONDIALOG_H
#define EXPOMODULATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ExpoModulationDialog;
}

class ExpoModulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpoModulationDialog(double timeOfMax, double stormLength, QWidget *parent = nullptr);
    ~ExpoModulationDialog();

private:
    Ui::ExpoModulationDialog *ui;

private slots:
    void acceptInput();

public:
    double m_dTimeOfMax;
	double m_dStormLength;
};

#endif // EXPOMODULATIONDIALOG_H
