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


#ifndef USERLABGUI_VIEWPROVIDERUSERLABSIMULATIONCOMPARISON_H
#define USERLABGUI_VIEWPROVIDERUSERLABSIMULATIONCOMPARISON_H

#include <Gui/ViewProviderRPSFeature.h>
#include <Libraries/Alphaplot/Table.h>
#include <Mod/UserLab/UserLabGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Mod/UserLab/Gui/UserLabComparisonStarter.h>
namespace UserLabGui {


class UserLabGuiExport ViewProviderUserLabSimulationComparison: public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(UserLabGui::ViewProviderUserLabSimulationComparison);

public:
    /// constructor
    ViewProviderUserLabSimulationComparison();
    /// destructor
    virtual ~ViewProviderUserLabSimulationComparison();

    virtual bool doubleClicked(void);
    void setupContextMenu(QMenu*, QObject*, const char*);

    bool start();
    bool stop();

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);

public:
    virtual PyObject* getPyObject() override;

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;

public:
    UserLabComparisonStarter* userComparisonStarter = nullptr;
};

} // namespace PartGui


#endif // USERLABGUI_VIEWPROVIDERUSERLABFEATUREZSPECTRUM_H

