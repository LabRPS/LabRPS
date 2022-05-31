#ifndef SLVERTDISTRDIALOG_H
#define SLVERTDISTRDIALOG_H

#include <QDialog>

namespace Ui {
class SLVertDistrDialog;
}

class SLVertDistrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SLVertDistrDialog(double minHeight, double spacing, double length, double xCoord, QWidget *parent = nullptr);
    ~SLVertDistrDialog();

private:
    Ui::SLVertDistrDialog *ui;

private slots:
    void acceptInput();

public:
	double mspacing;
	double mpositionX;
	double mminHeightHo;
	double mlength;
};

#endif // SLVERTDISTRDIALOG_H
