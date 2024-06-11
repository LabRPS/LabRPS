#ifndef WWYANG1997INDINPUTDLG_H
#define WWYANG1997INDINPUTDLG_H

#include <QDialog>

namespace Ui {
class WWYang1997IndInputDlg;
}

class WWYang1997IndInputDlg : public QDialog
{
    Q_OBJECT

public:
    explicit WWYang1997IndInputDlg(int numberOfLocation,
                                   int numberOfFrequencies,
                                   double locationHeight,
                                   double locationSpacing,
                                   double meanSpeed,
                                   double shearVelocity,
                                   double upperCutoffFrequency,
                                   int numberOfTimeIncrements,
                                   QWidget *parent = nullptr);
    ~WWYang1997IndInputDlg();

private:
    Ui::WWYang1997IndInputDlg *ui;

private Q_SLOTS:
    void acceptInput();
    
public:
    int m_numberOfLocation;
    int m_numberOfFrequencies;
	double m_locationHeight;
	double m_locationSpacing;
	double m_meanSpeed;
	double m_shearVelocity;
	double m_upperCutoffFrequency;
    int m_numberOfTimeIncrements;
};

#endif // WWYANG1997INDINPUTDLG_H
