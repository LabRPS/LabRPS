#ifndef RPSWLACCURACYCOMPARISONOBJECTDEPENDENCYDIALOG_H
#define RPSWLACCURACYCOMPARISONOBJECTDEPENDENCYDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLAccuracyComparisonObjectDependencyDialog;
}

class RPSWLAccuracyComparisonObjectDependencyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLAccuracyComparisonObjectDependencyDialog(QWidget *parent = nullptr);
    ~RPSWLAccuracyComparisonObjectDependencyDialog();

public slots:
    void acceptInput();

private:
    Ui::RPSWLAccuracyComparisonObjectDependencyDialog *ui;

public:
    QString noSelection;

    QString coherence;
    QString correlation;
    QString frequency;
    QString mean;
    QString modulation;
    QString decomposition;
    QString simulation;
    QString spatial;
    QString randomness;
    QString spectrum;
};

#endif // RPSWLCOMPARISONOBJECTDEPENDENCYDIALOG_H
