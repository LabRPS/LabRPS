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

#ifndef SEALABGUI_DlgTorsethaugenSpectrum_H
#define SEALABGUI_DlgTorsethaugenSpectrum_H
#define QT_NO_KEYWORDS

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeaLabGui {

class Ui_DlgTorsethaugenSpectrum;
class DlgTorsethaugenSpectrum : public QWidget
{
    Q_OBJECT

public:
    DlgTorsethaugenSpectrum(const App::PropertyFrequency&  SignificantWaveHeight, const App::PropertyTime&  PeakPeriod, const App::PropertyBool&  AutoGamma, const App::PropertyBool& AutoSigma, const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2, const App::PropertyBool& DoublePeaks, const App::PropertyString& featureName, QWidget* parent = nullptr);
    
    ~DlgTorsethaugenSpectrum();
    void accept();
    void reject();

       

private:
    std::unique_ptr<Ui_DlgTorsethaugenSpectrum> ui;
    std::string _featureName;
};

class DlgTorsethaugenSpectrumEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgTorsethaugenSpectrumEdit(const App::PropertyFrequency&  SignificantWaveHeight, const App::PropertyTime&  PeakPeriod, const App::PropertyBool&  AutoGamma, const App::PropertyBool& AutoSigma, const App::PropertyFloat& Gamma, const App::PropertyFloat& Sigma1, const App::PropertyFloat& Sigma2, const App::PropertyBool& DoublePeaks, const App::PropertyString& featureName);
    ~DlgTorsethaugenSpectrumEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgTorsethaugenSpectrum* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeaLabGui

#endif // SEALABGUI_DlgTorsethaugenSpectrum_H
