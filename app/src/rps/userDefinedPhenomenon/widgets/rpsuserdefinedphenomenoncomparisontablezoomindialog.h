#ifndef RPSUSERDEFINEDPHENOMENONCOMPARISONTABLEZOOMINDIALOG_H
#define RPSUSERDEFINEDPHENOMENONCOMPARISONTABLEZOOMINDIALOG_H

#include <QDialog>

namespace Ui {
class RPSUserDefinedPhenomenonComparisonTableZoomInDialog;
}

class RPSUserDefinedPhenomenonComparisonTableZoomInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSUserDefinedPhenomenonComparisonTableZoomInDialog(QWidget *parent = nullptr);
    ~RPSUserDefinedPhenomenonComparisonTableZoomInDialog();

private:
    Ui::RPSUserDefinedPhenomenonComparisonTableZoomInDialog *ui;
};

#endif // RPSUSERDEFINEDPHENOMENONCOMPARISONTABLEZOOMINDIALOG_H
