/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
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
# include <string>
# include <QAction>
# include <QMenu>
#endif

#include <App/RPSFeature.h>

#include "Application.h"
#include "BitmapFactory.h"
#include "Control.h"
#include "Document.h"
#include "TaskCSysDragger.h"
#include "ViewProviderDragger.h"


using namespace Gui;

PROPERTY_SOURCE(Gui::ViewProviderDragger,  Gui::ViewProviderDocumentObject)

ViewProviderDragger::ViewProviderDragger()
{
}

ViewProviderDragger::~ViewProviderDragger()
{
}

void ViewProviderDragger::updateData(const App::Property* prop)
{
    ViewProviderDocumentObject::updateData(prop);
}

bool ViewProviderDragger::doubleClicked()
{
    Gui::Application::Instance->activeDocument()->setEdit(this, (int)ViewProvider::Default);
    return true;
}

void ViewProviderDragger::setupContextMenu(QMenu* menu, QObject* receiver, const char* member)
{
    QIcon iconObject = mergeGreyableOverlayIcons(Gui::BitmapFactory().pixmap("Std_TransformManip.svg"));
    QAction* act = menu->addAction(iconObject, QObject::tr("Transform"), receiver, member);
    act->setData(QVariant((int)ViewProvider::Transform));
    ViewProviderDocumentObject::setupContextMenu(menu, receiver, member);
}

ViewProvider *ViewProviderDragger::startEditing(int mode) {
    _linkDragger = nullptr;
    auto ret = ViewProviderDocumentObject::startEditing(mode);
    if(!ret)
        return ret;
    return _linkDragger?_linkDragger:ret;
}

bool ViewProviderDragger::checkLink() {
    // Trying to detect if the editing request is forwarded by a link object,
    // usually by doubleClicked(). If so, we route the request back. There shall
    // be no risk of infinite recursion, as ViewProviderLink handles
    // ViewProvider::Transform request by itself.
    ViewProviderDocumentObject *vpParent = nullptr;
    std::string subname;
    auto doc = Application::Instance->editDocument();
    if(!doc)
        return false;
    doc->getInEdit(&vpParent,&subname);
    if(!vpParent)
        return false;
    auto sobj = vpParent->getObject()->getSubObject(subname.c_str());
    if(!sobj || sobj==getObject() || sobj->getLinkedObject(true)!=getObject())
        return false;
    auto vp = Application::Instance->getViewProvider(sobj);
    if(!vp)
        return false;
    _linkDragger = vp->startEditing(ViewProvider::Transform);
    if(_linkDragger)
        return true;
    return false;
}

bool ViewProviderDragger::setEdit(int ModNum)
{
  Q_UNUSED(ModNum);

  if(checkLink())
      return true;

  App::DocumentObject *genericObject = this->getObject();
  if (genericObject->isDerivedFrom(App::RPSFeature::getClassTypeId()))
  {
      App::RPSFeature* rpsFeature = static_cast<App::RPSFeature*>(genericObject);
    

    TaskCSysDragger *task = new TaskCSysDragger(this);
    Gui::Control().showDialog(task);
  }

  return true;
}

void ViewProviderDragger::unsetEdit(int ModNum)
{
  Q_UNUSED(ModNum);
  Gui::Control().closeDialog();
}
