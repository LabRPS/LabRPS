#ifndef MEANWINDLOGPROFILDIALOG_H
#define MEANWINDLOGPROFILDIALOG_H

#include <QDialog>

namespace Ui {
class MeanWindLogProfilDialog;
}

class MeanWindLogProfilDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MeanWindLogProfilDialog(double terrainRoughness, double shearVelocity, double zeroPlanDisplacement, QWidget *parent = nullptr);
    ~MeanWindLogProfilDialog();

private:
    Ui::MeanWindLogProfilDialog *ui;

private slots:
    void acceptInput();
    
public:
    double m_terrainRoughness;
    double m_shearVelocity;
    double m_zeroPlanDisplacement;
};

#endif // MEANWINDLOGPROFILDIALOG_H
