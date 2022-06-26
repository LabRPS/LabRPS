#ifndef SINEMODULATIONDIALOG_H
#define SINEMODULATIONDIALOG_H

#include <QDialog>

namespace Ui {
class SineModulationDialog;
}

class SineModulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SineModulationDialog(double pulseDuration, QWidget *parent = nullptr);
    ~SineModulationDialog();

private:
    Ui::SineModulationDialog *ui;

private slots:
    void acceptInput();

public:
    double m_dPulseDuration;
};

#endif // SINEMODULATIONDIALOG_H
