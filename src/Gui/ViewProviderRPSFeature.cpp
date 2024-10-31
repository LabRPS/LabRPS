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


#include "PreCompiled.h"

#ifndef _PreComp_
#endif

#include "ViewProviderRPSFeature.h"
#include "ViewProviderRPSFeaturePy.h"

#include <App/Application.h>
#include <Gui/Control.h>
#include <App/Document.h>
#include <Gui/ActionFunction.h>
#include "ViewProviderWindLabSimulation.h"
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/AlphaPlot.h>
#include <Gui/MainWindow.h>
#include <CXX/Objects.hxx>
#include <Gui/Command.h>

using namespace Gui;

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(Gui::ViewProviderRPSFeature,  Gui::ViewProviderDocumentObject)


ViewProviderRPSFeature::ViewProviderRPSFeature()
{
  
}

ViewProviderRPSFeature::~ViewProviderRPSFeature()
{

}

bool ViewProviderRPSFeature::doubleClicked(void)
{
    return Gui::ViewProviderDocumentObject::doubleClicked();
}

bool ViewProviderRPSFeature::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);

    if (ModNum == ViewProvider::Default) {

        return true;
    }
    else {
        return Gui::ViewProviderDocumentObject::setEdit(ModNum);
    }
}

void ViewProviderRPSFeature::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // when pressing ESC make sure to close the dialog
        Gui::Control().closeDialog();
    }
    else {
        Gui::ViewProviderDocumentObject::unsetEdit(ModNum);
    }
}

void ViewProviderRPSFeature::setupContextMenu(QMenu* menu, QObject*, const char*)
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);

    QAction* gtp = menu->addAction(QObject::tr("Go to Publication"));
    func->trigger(gtp, boost::bind(&ViewProviderRPSFeature::goToPublication, this));
}


bool ViewProviderRPSFeature::goToPublication()
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
        return false;
    auto obj = doc->getObject(this->getObject()->getNameInDocument());
    if (!obj)
        return false;
    auto active = static_cast<WindLabAPI::WindLabFeature*>(obj);
    if (!active)
        return false;

    Gui::Command::doCommand(Gui::Command::Doc, "import WebGui");
    Gui::Command::doCommand(Gui::Command::Doc, "WebGui.openBrowser(\"%s\")", active->LinkToPublication.getStrValue().c_str());

    return true;
}


void ViewProviderRPSFeature::onChanged(const App::Property* prop)
{
    ViewProviderDocumentObject::onChanged(prop);
}

PyObject* ViewProviderRPSFeature::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new ViewProviderRPSFeaturePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
