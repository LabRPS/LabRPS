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
    explicit MeanWindLogProfilDialog(double terrainRoughness, double shearVelocity, QWidget *parent = nullptr);
    ~MeanWindLogProfilDialog();

private:
    Ui::MeanWindLogProfilDialog *ui;

private slots:
    void acceptInput();
    
public:
    double m_terrainRoughness;
    double m_shearVelocity;
};

#endif // MEANWINDLOGPROFILDIALOG_H
