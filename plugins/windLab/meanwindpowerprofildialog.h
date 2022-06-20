#ifndef MEANWINDPOWERPROFILDIALOG_H
#define MEANWINDPOWERPROFILDIALOG_H

#include <QDialog>

namespace Ui {
class MeanWindPowerProfilDialog;
}

class MeanWindPowerProfilDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MeanWindPowerProfilDialog(double referenceHeight, double referenceSpeed, double dimensionlessPower, QWidget *parent = nullptr);
    ~MeanWindPowerProfilDialog();

private:
    Ui::MeanWindPowerProfilDialog *ui;


private slots:
    void acceptInput();

public:
    double m_referenceHeight;
    double m_referenceSpeed;
    double m_dimensionlessPower;
};

#endif // MEANWINDPOWERPROFILDIALOG_H
