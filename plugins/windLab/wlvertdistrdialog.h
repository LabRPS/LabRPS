#ifndef WLVERTDISTRDIALOG_H
#define WLVERTDISTRDIALOG_H

#include <QDialog>

namespace Ui {
class WLVertDistrDialog;
}

class WLVertDistrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WLVertDistrDialog(double minHeight, double spacing, double length, double xCoord, QWidget *parent = nullptr);
    ~WLVertDistrDialog();

private:
    Ui::WLVertDistrDialog *ui;

private slots:
    void acceptInput();

public:
	double mspacing;
	double mpositionX;
	double mminHeightHo;
	double mlength;
};

#endif // SLVERTDISTRDIALOG_H
