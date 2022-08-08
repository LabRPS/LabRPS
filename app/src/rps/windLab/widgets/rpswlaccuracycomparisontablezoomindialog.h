#ifndef RPSWLACCURACYCOMPARISONTABLEZOOMINDIALOG_H
#define RPSWLACCURACYCOMPARISONTABLEZOOMINDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLAccuracyComparisonTableZoomInDialog;
}

class RPSWLAccuracyComparisonTableZoomInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLAccuracyComparisonTableZoomInDialog(QWidget *parent = nullptr);
    ~RPSWLAccuracyComparisonTableZoomInDialog();

private:
    Ui::RPSWLAccuracyComparisonTableZoomInDialog *ui;
};

#endif // RPSWLACCURACYCOMPARISONTABLEZOOMINDIALOG_H
