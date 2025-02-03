/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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

#ifndef SEALABGUI_DlgJonswapSpectrum_H
#define SEALABGUI_DlgJonswapSpectrum_H


#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeaLabGui {

class Ui_DlgJonswapSpectrum;
class DlgJonswapSpectrum : public QWidget
{
    Q_OBJECT

public:
    DlgJonswapSpectrum(const App::PropertyLength&  SignificantWaveHeight, const App::PropertyTime&  PeakPeriod, const App::PropertyBool&  AutoGamma, const App::PropertyBool& AutoSigma, const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2, const App::PropertyString& featureName, QWidget* parent = nullptr);
    
    ~DlgJonswapSpectrum();
    void accept();
    void reject();

       

private:
    std::unique_ptr<Ui_DlgJonswapSpectrum> ui;
    std::string _featureName;
};

class DlgJonswapSpectrumEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgJonswapSpectrumEdit(const App::PropertyLength&  SignificantWaveHeight, const App::PropertyTime&  PeakPeriod, const App::PropertyBool&  AutoGamma, const App::PropertyBool& AutoSigma, const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2, const App::PropertyString& featureName);
    ~DlgJonswapSpectrumEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgJonswapSpectrum* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeaLabGui

#endif // SEALABGUI_DlgJonswapSpectrum_H
