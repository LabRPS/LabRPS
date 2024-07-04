/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

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
