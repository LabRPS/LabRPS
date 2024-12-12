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

#ifndef SEISMICLABGUI_DlgHuZhouSpectrum_H
#define SEISMICLABGUI_DlgHuZhouSpectrum_H


#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeismicLabGui {

class Ui_DlgHuZhouSpectrum;
class DlgHuZhouSpectrum : public QWidget
{
    Q_OBJECT

public:
    DlgHuZhouSpectrum(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFrequency& LowFrequencyControlFactor, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgHuZhouSpectrum();
    void accept();
    void reject();

       

private:
    std::unique_ptr<Ui_DlgHuZhouSpectrum> ui;
    std::string _featureName;
};

class DlgHuZhouSpectrumEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgHuZhouSpectrumEdit(const App::PropertyFrequency& GroundNaturalFrequency, const App::PropertyFloat& GroundDampingRatio, const App::PropertyFrequency& LowFrequencyControlFactor, const App::PropertyFloat& ConstantSpectralIntensity, const App::PropertyString& featureName);
    ~DlgHuZhouSpectrumEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgHuZhouSpectrum* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeismicLabGui

#endif // SEISMICLABGUI_DlgHuZhouSpectrum_H
