#ifndef KAIMALPSDSHEARVELOCITYDIALOG_H
#define KAIMALPSDSHEARVELOCITYDIALOG_H

#include <QDialog>

namespace Ui {
class KaimalPSDShearVelocityDialog;
}

class KaimalPSDShearVelocityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KaimalPSDShearVelocityDialog(double shearVelocity, QWidget *parent = nullptr);
    ~KaimalPSDShearVelocityDialog();

private:
    Ui::KaimalPSDShearVelocityDialog *ui;

private slots:
    void acceptInput();

public:

    double m_shearVelocity;
};

#endif // KAIMALPSDSHEARVELOCITYDIALOG_H
