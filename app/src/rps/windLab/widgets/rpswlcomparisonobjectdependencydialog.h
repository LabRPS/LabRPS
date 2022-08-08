#ifndef RPSWLCOMPARISONOBJECTDEPENDENCYDIALOG_H
#define RPSWLCOMPARISONOBJECTDEPENDENCYDIALOG_H

#include <QDialog>

namespace Ui {
class RPSWLComparisonObjectDependencyDialog;
}

class RPSWLComparisonObjectDependencyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPSWLComparisonObjectDependencyDialog(QWidget *parent = nullptr);
    ~RPSWLComparisonObjectDependencyDialog();

public slots:
    void acceptInput();

private:
    Ui::RPSWLComparisonObjectDependencyDialog *ui;

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
