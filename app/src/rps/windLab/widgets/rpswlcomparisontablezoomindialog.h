#ifndef RPSWLCOMPARISONTABLEZOOMINDIALOG_H
#define RPSWLCOMPARISONTABLEZOOMINDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLComparisonTableZoomInDialog;
}

class RPSWLComparisonTableZoomInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLComparisonTableZoomInDialog(QWidget *parent = nullptr);
    ~RPSWLComparisonTableZoomInDialog();

private:
    Ui::RPSWLComparisonTableZoomInDialog *ui;
};

#endif // RPSWLCOMPARISONTABLEZOOMINDIALOG_H
