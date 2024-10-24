/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
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

#include <Base/Console.h>
#include <Base/Exception.h>

#include "ViewProvider.h"
#include "ActionFunction.h"
#include "Application.h"
#include "BitmapFactory.h"
#include "Document.h"
#include "ViewParams.h"
#include "ViewProviderExtension.h"
#include "ViewProviderLink.h"
#include "ViewProviderPy.h"


RPS_LOG_LEVEL_INIT("ViewProvider", true, true)

using namespace std;
using namespace Gui;


//**************************************************************************
//**************************************************************************
// ViewProvider
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PROPERTY_SOURCE_ABSTRACT(Gui::ViewProvider, App::TransactionalObject)

ViewProvider::ViewProvider()
    : pyViewObject(nullptr)
    , overrideMode("As Is")
    , _iActualMode(-1)
    , _iEditMode(-1)
    , viewOverrideMode(-1)
{
    setStatus(UpdateData, true);

    sPixmap = "px";
}

ViewProvider::~ViewProvider()
{
    if (pyViewObject) {
        Base::PyGILStateLocker lock;
        pyViewObject->setInvalid();
        pyViewObject->DecRef();
    }
}

ViewProvider *ViewProvider::startEditing(int ModNum)
{
    if(setEdit(ModNum)) {
        _iEditMode = ModNum;
        return this;
    }
    return nullptr;
}

int ViewProvider::getEditingMode() const
{
    return _iEditMode;
}

bool ViewProvider::isEditing() const
{
    return getEditingMode() > -1;
}

void ViewProvider::finishEditing()
{
    unsetEdit(_iEditMode);
    _iEditMode = -1;
}

bool ViewProvider::setEdit(int ModNum)
{
    Q_UNUSED(ModNum);
    return true;
}

void ViewProvider::unsetEdit(int ModNum)
{
    Q_UNUSED(ModNum);
}

bool ViewProvider::isUpdatesEnabled () const
{
    return testStatus(UpdateData);
}

void ViewProvider::setUpdatesEnabled (bool enable)
{
    setStatus(UpdateData, enable);
}

void highlight(const HighlightMode& high)
{
    Q_UNUSED(high);
}


void ViewProvider::update(const App::Property* prop)
{
    // Hide the object temporarily to speed up the update
    if (!isUpdatesEnabled())
        return;
    bool vis = ViewProvider::isShow();
    if (vis) ViewProvider::hide();
    updateData(prop);
    if (vis) ViewProvider::show();
}

QIcon ViewProvider::getIcon() const
{
    return mergeGreyableOverlayIcons (Gui::BitmapFactory().pixmap(sPixmap));
}

QIcon ViewProvider::mergeGreyableOverlayIcons (const QIcon & orig) const
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();

    QIcon overlayedIcon = orig;

    for (Gui::ViewProviderExtension* ext : vector) {
        if (!ext->ignoreOverlayIcon())
            overlayedIcon = ext->extensionMergeGreyableOverlayIcons(overlayedIcon);
    }

    return overlayedIcon;
}

QIcon ViewProvider::mergeColorfulOverlayIcons (const QIcon & orig) const
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();

    QIcon overlayedIcon = orig;

    for (Gui::ViewProviderExtension* ext : vector) {
        if (!ext->ignoreOverlayIcon())
            overlayedIcon = ext->extensionMergeColorfullOverlayIcons(overlayedIcon);
    }

    return overlayedIcon;
}

/**
 * If you add new viewing modes in @ref getDisplayModes() then you need to reimplement
 * also seDisplaytMode() to handle these new modes by setting the appropriate display
 * mode.
 */
void ViewProvider::setDisplayMode(const char* ModeName)
{
    _sCurrentMode = ModeName;

    //infom the exteensions
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector)
        ext->extensionSetDisplayMode(ModeName);
}

const char* ViewProvider::getDefaultDisplayMode() const {

    return nullptr;
}

vector<std::string> ViewProvider::getDisplayModes() const {

    std::vector< std::string > modes;
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        auto extModes = ext->extensionGetDisplayModes();
        modes.insert( modes.end(), extModes.begin(), extModes.end() );
    }
    return modes;
}

std::string ViewProvider::getActiveDisplayMode() const
{
    return _sCurrentMode;
}

void ViewProvider::hide()
{
    auto exts = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();

    //tell extensions that we hide
    for (Gui::ViewProviderExtension* ext : exts)
        ext->extensionHide();
}

void ViewProvider::show()
{
    setModeSwitch();

    //tell extensions that we show
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector)
        ext->extensionShow();
}

bool ViewProvider::isShow() const
{
    return true;
}

void ViewProvider::setVisible(bool s)
{
    s ? show() : hide();
}

bool ViewProvider::isVisible() const
{
    return isShow();
}

void ViewProvider::setOverrideMode(const std::string &mode)
{
    if (mode == "As Is") {
        viewOverrideMode = -1;
        overrideMode = mode;
    }
    else {
        std::map<std::string, int>::const_iterator it = _sDisplayMaskModes.find(mode);
        if (it == _sDisplayMaskModes.end())
            return; //view style not supported
        viewOverrideMode = (*it).second;
        overrideMode = mode;
    }

        for(auto ext : getExtensionsDerivedFromType<Gui::ViewProviderExtension>())
            ext->extensionModeSwitchChange();
}

const string ViewProvider::getOverrideMode() {
    return overrideMode;
}


void ViewProvider::setModeSwitch()
{
    
}


void ViewProvider::onBeforeChange(const App::Property* prop)
{
    Application::Instance->signalBeforeChangeObject(*this, *prop);

    App::TransactionalObject::onBeforeChange(prop);
}

bool ViewProvider::keyPressed(bool pressed, int key)
{
    (void)pressed;
    (void)key;
    return false;
}

void ViewProvider::onChanged(const App::Property* prop)
{
    Application::Instance->signalChangedObject(*this, *prop);
    Application::Instance->updateActions();

    App::TransactionalObject::onChanged(prop);
}

std::string ViewProvider::toString() const
{ return "koffa"; }

PyObject* ViewProvider::getPyObject()
{
    if (!pyViewObject)
        pyViewObject = new ViewProviderPy(this);
    pyViewObject->IncRef();
    return pyViewObject;
}


void ViewProvider::setupContextMenu(QMenu* menu, QObject* receiver, const char* method)
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector)
        ext->extensionSetupContextMenu(menu, receiver, method);
}

bool ViewProvider::onDelete(const vector< string >& subNames)
{
    bool del = true;
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector)
        del &= ext->extensionOnDelete(subNames);

    return del;
}

bool ViewProvider::canDelete(App::DocumentObject*) const
{
    return false;
}

bool ViewProvider::canDragObject(App::DocumentObject* obj) const
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        if (ext->extensionCanDragObject(obj))
            return true;
    }

    return false;
}

bool ViewProvider::canDragObjects() const
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        if (ext->extensionCanDragObjects())
            return true;
    }

    return false;
}

void ViewProvider::dragObject(App::DocumentObject* obj)
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        if (ext->extensionCanDragObject(obj)) {
            ext->extensionDragObject(obj);
            return;
        }
    }

    throw Base::RuntimeError("ViewProvider::dragObject: no extension for dragging given object available.");
}

bool ViewProvider::canDropObject(App::DocumentObject* obj) const
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
#if RPS_DEBUG
    Base::Console().Log("Check extensions for drop\n");
#endif
    for (Gui::ViewProviderExtension* ext : vector){
#if RPS_DEBUG
        Base::Console().Log("Check extensions %s\n", ext->name().c_str());
#endif
        if (ext->extensionCanDropObject(obj))
            return true;
    }

    return false;
}

bool ViewProvider::canDropObjects() const {

    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for(Gui::ViewProviderExtension* ext : vector)
        if(ext->extensionCanDropObjects())
            return true;

    return false;
}

bool ViewProvider::canDragAndDropObject(App::DocumentObject* obj) const {

    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for(Gui::ViewProviderExtension* ext : vector){
        if(!ext->extensionCanDragAndDropObject(obj))
            return false;
    }

    return true;
}

void ViewProvider::dropObject(App::DocumentObject* obj) {
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        if (ext->extensionCanDropObject(obj)) {
            ext->extensionDropObject(obj);
            return;
        }
    }

    throw Base::RuntimeError("ViewProvider::dropObject: no extension for dropping given object available.");
}

bool ViewProvider::canDropObjectEx(App::DocumentObject* obj, App::DocumentObject *owner,
        const char *subname, const std::vector<std::string> &elements) const
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for(Gui::ViewProviderExtension* ext : vector){
        if(ext->extensionCanDropObjectEx(obj,owner,subname, elements))
            return true;
    }
    return canDropObject(obj);
}

std::string ViewProvider::dropObjectEx(App::DocumentObject* obj, App::DocumentObject *owner,
        const char *subname, const std::vector<std::string> &elements)
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for(Gui::ViewProviderExtension* ext : vector) {
        if(ext->extensionCanDropObjectEx(obj, owner, subname, elements))
            return ext->extensionDropObjectEx(obj, owner, subname, elements);
    }
    dropObject(obj);
    return std::string();
}

int ViewProvider::replaceObject(App::DocumentObject* oldValue, App::DocumentObject* newValue)
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        if (ext->extensionCanDropObject(newValue)) {
            int ret = ext->extensionReplaceObject(oldValue, newValue);
            if(ret>=0)
                return !!ret;
        }
    }
    return -1;
}

void ViewProvider::Restore(Base::XMLReader& reader) {
    // Because some PropertyLists type properties are stored in a separate file,
    // and is thus restored outside this function. So we rely on Gui::Document
    // to set the isRestoring flags for us.
    //
    // setStatus(Gui::isRestoring, true);

    TransactionalObject::Restore(reader);

    // setStatus(Gui::isRestoring, false);
}

void ViewProvider::updateData(const App::Property* prop)
{
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector)
        ext->extensionUpdateData(prop);
}



std::vector< App::DocumentObject* > ViewProvider::claimChildren() const
{
    std::vector< App::DocumentObject* > vec;
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for (Gui::ViewProviderExtension* ext : vector) {
        std::vector< App::DocumentObject* > nvec = ext->extensionClaimChildren();
        if (!nvec.empty())
            vec.insert(std::end(vec), std::begin(nvec), std::end(nvec));
    }
    return vec;
}

const std::string &ViewProvider::hiddenMarker() {
    return App::DocumentObject::hiddenMarker();
}

const char *ViewProvider::hasHiddenMarker(const char *subname) {
    return App::DocumentObject::hasHiddenMarker(subname);
}

bool ViewProvider::useNewSelectionModel() const {
    return ViewParams::instance()->getUseNewSelection();
}

void ViewProvider::beforeDelete() {
    auto vector = getExtensionsDerivedFromType<Gui::ViewProviderExtension>();
    for(Gui::ViewProviderExtension* ext : vector)
        ext->extensionBeforeDelete();
}

bool ViewProvider::isLinkVisible() const {
    auto ext = getExtensionByType<ViewProviderLinkObserver>(true);
    if(!ext)
        return true;
    return ext->isLinkVisible();
}

void ViewProvider::setLinkVisible(bool visible) {
    auto ext = getExtensionByType<ViewProviderLinkObserver>(true);
    if(ext)
        ext->setLinkVisible(visible);
}
