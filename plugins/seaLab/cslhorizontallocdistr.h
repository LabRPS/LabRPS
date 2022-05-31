#ifndef CSLHORIZONTALLOCDISTR_H
#define CSLHORIZONTALLOCDISTR_H

#include <QDialog>

namespace Ui {
class CSLHorizontalLocDistr;
}

class CSLHorizontalLocDistr : public QDialog
{
    Q_OBJECT

public:
    explicit CSLHorizontalLocDistr(double height, double spacing, double length, QWidget *parent = nullptr);
    ~CSLHorizontalLocDistr();

private:
    Ui::CSLHorizontalLocDistr *ui;

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
