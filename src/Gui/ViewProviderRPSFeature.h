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


#ifndef WINDLABGUI_VIEWPROVIDERRPSFEATURE_H
#define WINDLABGUI_VIEWPROVIDERRPSFEATURE_H

#include <Gui/ViewProviderDocumentObject.h>
#include <Mod/WindLab/WindLabGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Mod/WindLab/Gui/WindLabAllFeaturesComputation.h>

namespace Gui {


class GuiExport ViewProviderRPSFeature: public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(Gui::ViewProviderRPSFeature);

public:
    /// constructor
    ViewProviderRPSFeature();
    /// destructor
    virtual ~ViewProviderRPSFeature();

    virtual bool doubleClicked(void);
    void setupContextMenu(QMenu*, QObject*, const char*);

    bool goToPublication();
    bool goToWiki();


public:

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);

protected:
    /// get called by the container whenever a property has been changed
    virtual void onChanged(const App::Property* prop) override;

private:

public:
    virtual PyObject* getPyObject() override;

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;

};

} // namespace Gui


#endif // WINDLABGUI_VIEWPROVIDERRPSFEATURE_H

