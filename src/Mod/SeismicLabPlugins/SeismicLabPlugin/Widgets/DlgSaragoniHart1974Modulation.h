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

#ifndef SEISMICLABGUI_DlgSaragoniHart1974Modulation_H
#define SEISMICLABGUI_DlgSaragoniHart1974Modulation_H


#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeismicLabGui {

class Ui_DlgSaragoniHart1974Modulation;
class DlgSaragoniHart1974Modulation : public QWidget
{
    Q_OBJECT

public:
    DlgSaragoniHart1974Modulation(const App::PropertyFloat& AlphaOne, const App::PropertyFloat& AlphaTow, const App::PropertyFloat& AlphaThree, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgSaragoniHart1974Modulation();
    void accept();
    void reject();

       

private:
    std::unique_ptr<Ui_DlgSaragoniHart1974Modulation> ui;
    std::string _featureName;
};

class DlgSaragoniHart1974ModulationEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgSaragoniHart1974ModulationEdit(const App::PropertyFloat& AlphaOne, const App::PropertyFloat& AlphaTow, const App::PropertyFloat& AlphaThree, const App::PropertyString& featureName);
    ~DlgSaragoniHart1974ModulationEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgSaragoniHart1974Modulation* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeismicLabGui

#endif // SEISMICLABGUI_DlgSaragoniHart1974Modulation_H
