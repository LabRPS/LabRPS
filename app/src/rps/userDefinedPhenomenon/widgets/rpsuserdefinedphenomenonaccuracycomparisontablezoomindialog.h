#ifndef RPSUSERDEFINEDPHENOMENONACCURACYCOMPARISONTABLEZOOMINDIALOG_H
#define RPSUSERDEFINEDPHENOMENONACCURACYCOMPARISONTABLEZOOMINDIALOG_H

#include <QDialog>

namespace Ui {
class RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog;
}

class RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog(QWidget *parent = nullptr);
    ~RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog();

private:
    Ui::RPSUserDefinedPhenomenonAccuracyComparisonTableZoomInDialog *ui;
};

#endif // RPSUSERDEFINEDPHENOMENONACCURACYCOMPARISONTABLEZOOMINDIALOG_H
