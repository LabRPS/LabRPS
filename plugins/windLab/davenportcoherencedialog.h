#ifndef DAVENPORTCOHERENCEDIALOG_H
#define DAVENPORTCOHERENCEDIALOG_H

#include <QDialog>

namespace Ui {
class DavenportCoherenceDialog;
}

class DavenportCoherenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DavenportCoherenceDialog(double decayCx, double decayCy, double decayCz, QWidget *parent = nullptr);
    ~DavenportCoherenceDialog();

private:
    Ui::DavenportCoherenceDialog *ui;

private slots:
    void acceptInput();

public:

    double m_decayCx;
    double m_decayCy;
    double m_decayCz;
};

#endif // DAVENPORTCOHERENCEDIALOG_H
