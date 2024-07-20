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

#ifndef SEALABGUI_DlgGridPoints_H
#define SEALABGUI_DlgGridPoints_H
#define QT_NO_KEYWORDS

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;
namespace App
{
    class PropertyPosition;
    class PropertyLength;
    class PropertyEnumeration;
}
namespace SeaLabGui {

class Ui_DlgGridPoints;
class DlgGridPoints : public QWidget
{
    Q_OBJECT

public:
    DlgGridPoints(const App::PropertyPosition& centerPoint, const App::PropertyLength& spacing1, const App::PropertyLength& spacing2, const App::PropertyLength& length1, const App::PropertyLength& length2, const App::PropertyEnumeration& locationPlan, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgGridPoints();
    void accept();
    void reject();

private:
    std::unique_ptr<Ui_DlgGridPoints> ui;
    std::string _featureName;
};

class GridPointsDialogEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    GridPointsDialogEdit(const App::PropertyPosition& centerPoint, const App::PropertyLength& spacing1, const App::PropertyLength& spacing2, const App::PropertyLength& length1, const App::PropertyLength& length2, const App::PropertyEnumeration& locationPlan, const App::PropertyString& featureName);
    ~GridPointsDialogEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgGridPoints* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeaLabGui

#endif // SEALABGUI_DlgGridPoints_H
