#ifndef CWLHORIZONTALLOCDISTR_H
#define CWLHORIZONTALLOCDISTR_H

#include <QDialog>

namespace Ui {
class CWLHorizontalLocDistr;
}

class CWLHorizontalLocDistr : public QDialog
{
    Q_OBJECT

public:
    explicit CWLHorizontalLocDistr(double height, double spacing, double length, QWidget *parent = nullptr);
    ~CWLHorizontalLocDistr();

private:
    Ui::CWLHorizontalLocDistr *ui;

private slots:
    void acceptInput();
    void rejectInput();

public:
	//spacing between two adjacent points
	double mdSpacing;

	//Height
	double mdHeight;

	//Length
	double mdLength;
};

#endif // CSLHORIZONTALLOCDISTR_H
