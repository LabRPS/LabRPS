/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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

#ifndef WINDLABGUI_DlgvonKarmanVerticalWindSpectrum_H
#define WINDLABGUI_DlgvonKarmanVerticalWindSpectrum_H
#define QT_NO_KEYWORDS

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace WindLabGui {

class Ui_DlgvonKarmanVerticalWindSpectrum;
class DlgvonKarmanVerticalWindSpectrum : public QWidget
{
    Q_OBJECT

public:
    DlgvonKarmanVerticalWindSpectrum(const App::PropertyFloat& Constant1, const App::PropertyFloat& Constant2, const App::PropertyFloat& IntegralLengthScale, const App::PropertyFloat& StandardDeviation, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgvonKarmanVerticalWindSpectrum();
    void accept();
    void reject();

    

private:
    std::unique_ptr<Ui_DlgvonKarmanVerticalWindSpectrum> ui;
    std::string _featureName;
};

class DlgvonKarmanVerticalWindSpectrumEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgvonKarmanVerticalWindSpectrumEdit(const App::PropertyFloat& Constant1, const App::PropertyFloat& Constant2, const App::PropertyFloat& IntegralLengthScale, const App::PropertyFloat& StandardDeviation, const App::PropertyString& featureName);
    ~DlgvonKarmanVerticalWindSpectrumEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgvonKarmanVerticalWindSpectrum* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace WindLabGui

#endif // WINDLABGUI_DlgvonKarmanVerticalWindSpectrum_H
