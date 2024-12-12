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

#ifndef WINDLABGUI_DlgSimuAlongWindSpectrum_H
#define WINDLABGUI_DlgSimuAlongWindSpectrum_H


#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace WindLabGui {

class Ui_DlgSimuAlongWindSpectrum;
class DlgSimuAlongWindSpectrum : public QWidget
{
    Q_OBJECT

public:
    DlgSimuAlongWindSpectrum(const App::PropertySpeed& ShearVelocity, const App::PropertyFloat& Constant1, const App::PropertyFloat& Constant2, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgSimuAlongWindSpectrum();
    void accept();
    void reject();

       

private:
    std::unique_ptr<Ui_DlgSimuAlongWindSpectrum> ui;
    std::string _featureName;
};

class DlgSimuAlongWindSpectrumEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgSimuAlongWindSpectrumEdit(const App::PropertySpeed& ShearVelocity, const App::PropertyFloat& Constant1, const App::PropertyFloat& Constant2, const App::PropertyString& featureName);
    ~DlgSimuAlongWindSpectrumEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgSimuAlongWindSpectrum* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace WindLabGui

#endif // WINDLABGUI_DlgSimuAlongWindSpectrum_H
