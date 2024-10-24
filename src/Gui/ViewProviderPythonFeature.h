/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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

#ifndef GUI_VIEWPROVIDERPYTHONFEATURE_H
#define GUI_VIEWPROVIDERPYTHONFEATURE_H

#include <App/AutoTransaction.h>
#include <App/PropertyPythonObject.h>
#include <App/FeaturePython.h>
#include "ViewProviderDragger.h"
#include "Document.h"

namespace Gui {

class GuiExport ViewProviderPythonFeatureImp
{
public:
    enum ValueT {
        NotImplemented = 0, // not handled
        Accepted = 1, // handled and accepted
        Rejected = 2  // handled and rejected
    };

    /// constructor.
    ViewProviderPythonFeatureImp(ViewProviderDocumentObject*, App::PropertyPythonObject &);
    /// destructor.
    ~ViewProviderPythonFeatureImp();

    // Returns the icon
    QIcon getIcon() const;
    bool claimChildren(std::vector<App::DocumentObject*>&) const;
    ValueT useNewSelectionModel() const;
    ValueT setEdit(int ModNum);
    ValueT unsetEdit(int ModNum);
    ValueT doubleClicked();
    bool setupContextMenu(QMenu* menu);

    /** @name Update data methods*/
    //@{
    void attach(App::DocumentObject *pcObject);
    void updateData(const App::Property*);
    void onChanged(const App::Property* prop);
    void startRestoring();
    void finishRestoring();
    ValueT onDelete(const std::vector<std::string> & sub);
    ValueT canDelete(App::DocumentObject *obj) const;
    //@}

    /** @name Display methods */
    //@{
    /// Returns true if the icon must always appear enabled in the tree view
    ValueT isShow() const;
    /// get the default display mode
    bool getDefaultDisplayMode(std::string &mode) const;
    /// returns a list of all possible modes
    std::vector<std::string> getDisplayModes() const;
    /// set the display mode
    std::string setDisplayMode(const char* ModeName);
    //@}

    ValueT canRemoveChildrenFromRoot() const;

    /** @name Drag and drop */
    //@{
    /// Returns true if the view provider generally supports dragging objects
    ValueT canDragObjects() const;
    /// Check whether the object can be removed from the view provider by drag and drop
    ValueT canDragObject(App::DocumentObject*) const;
    /// Starts to drag the object
    ValueT dragObject(App::DocumentObject*);
    /// Returns true if the view provider generally accepts dropping of objects
    ValueT canDropObjects() const;
    /// Check whether the object can be dropped to the view provider by drag and drop
    ValueT canDropObject(App::DocumentObject*) const;
    /// If the dropped object type is accepted the object will be added as child
    ValueT dropObject(App::DocumentObject*);
    /** Return false to force drop only operation for a give object*/
    ValueT canDragAndDropObject(App::DocumentObject*) const;
    /** Query object dropping with full qualified name */
    ValueT canDropObjectEx(App::DocumentObject *obj, App::DocumentObject *,
            const char *,const std::vector<std::string> &elements) const;
    /** Add an object with full qualified name to the view provider by drag and drop */
    bool dropObjectEx(App::DocumentObject *obj, App::DocumentObject *,
            const char *, const std::vector<std::string> &elements, std::string &ret);
    ValueT replaceObject(App::DocumentObject *, App::DocumentObject *);
    //@}

    bool getLinkedViewProvider(ViewProviderDocumentObject *&res,
            std::string *subname, bool recursive) const;

    ValueT canAddToSceneGraph() const;

    bool getDropPrefix(std::string &prefix) const;

    bool editProperty(const char *propName);

private:
    ViewProviderDocumentObject* object;
    App::PropertyPythonObject &Proxy;
    bool has__object__;

#define RPS_PY_VIEW_OBJECT \
    RPS_PY_ELEMENT(getIcon) \
    RPS_PY_ELEMENT(claimChildren) \
    RPS_PY_ELEMENT(useNewSelectionModel) \
    RPS_PY_ELEMENT(setEdit) \
    RPS_PY_ELEMENT(unsetEdit) \
    RPS_PY_ELEMENT(doubleClicked) \
    RPS_PY_ELEMENT(setupContextMenu) \
    RPS_PY_ELEMENT(attach) \
    RPS_PY_ELEMENT(updateData) \
    RPS_PY_ELEMENT(onChanged) \
    RPS_PY_ELEMENT(startRestoring) \
    RPS_PY_ELEMENT(finishRestoring) \
    RPS_PY_ELEMENT(onDelete) \
    RPS_PY_ELEMENT(canDelete) \
    RPS_PY_ELEMENT(isShow) \
    RPS_PY_ELEMENT(getDefaultDisplayMode) \
    RPS_PY_ELEMENT(getDisplayModes) \
    RPS_PY_ELEMENT(setDisplayMode) \
    RPS_PY_ELEMENT(canRemoveChildrenFromRoot) \
    RPS_PY_ELEMENT(canDragObjects) \
    RPS_PY_ELEMENT(canDragObject) \
    RPS_PY_ELEMENT(dragObject) \
    RPS_PY_ELEMENT(canDropObjects) \
    RPS_PY_ELEMENT(canDropObject) \
    RPS_PY_ELEMENT(dropObject) \
    RPS_PY_ELEMENT(canDragAndDropObject) \
    RPS_PY_ELEMENT(canDropObjectEx) \
    RPS_PY_ELEMENT(dropObjectEx) \
    RPS_PY_ELEMENT(canAddToSceneGraph) \
    RPS_PY_ELEMENT(getDropPrefix) \
    RPS_PY_ELEMENT(replaceObject) \
    RPS_PY_ELEMENT(getLinkedViewProvider) \
    RPS_PY_ELEMENT(editProperty) \

#undef RPS_PY_ELEMENT
#define RPS_PY_ELEMENT(_name) RPS_PY_ELEMENT_DEFINE(_name)

    RPS_PY_VIEW_OBJECT

#undef RPS_PY_ELEMENT
#define RPS_PY_ELEMENT(_name) RPS_PY_ELEMENT_FLAG(_name)

    enum Flag {
        RPS_PY_VIEW_OBJECT
        FlagMax,
    };
    typedef std::bitset<FlagMax> Flags;
    mutable Flags _Flags;

public:
    void init(PyObject *pyobj);
};

template <class ViewProviderT>
class ViewProviderPythonFeatureT : public ViewProviderT
{
    PROPERTY_HEADER_WITH_OVERRIDE(Gui::ViewProviderPythonFeatureT<ViewProviderT>);

public:
    /// constructor.
    ViewProviderPythonFeatureT() : _attached(false) {
        ADD_PROPERTY(Proxy,(Py::Object()));
        imp = new ViewProviderPythonFeatureImp(this,Proxy);
    }
    /// destructor.
    virtual ~ViewProviderPythonFeatureT() {
        delete imp;
    }

    // Returns the icon
    QIcon getIcon() const override {
        QIcon icon = imp->getIcon();
        if (icon.isNull())
            icon = ViewProviderT::getIcon();
        else
            icon = ViewProviderT::mergeGreyableOverlayIcons(icon);
        return icon;
    }

    std::vector<App::DocumentObject*> claimChildren() const override {
        std::vector<App::DocumentObject *> res;
        if(!imp->claimChildren(res))
            return ViewProviderT::claimChildren();
        return res;
    }

    /** @name Selection handling */
    //@{
    virtual bool useNewSelectionModel() const override {
        switch(imp->useNewSelectionModel()) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::useNewSelectionModel();
        }
    }

    //@}

    /** @name Update data methods*/
    //@{
    virtual void attach(App::DocumentObject *obj) override {
        // delay loading of the actual attach() method because the Python
        // view provider class is not attached yet
        ViewProviderT::pcObject = obj;
    }
    virtual void updateData(const App::Property* prop) override {
        imp->updateData(prop);
        ViewProviderT::updateData(prop);
    }
    virtual void getTaskViewContent(std::vector<Gui::TaskView::TaskContent*>& c) const override {
        ViewProviderT::getTaskViewContent(c);
    }
    virtual bool onDelete(const std::vector<std::string> & sub) override {
        switch(imp->onDelete(sub)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::onDelete(sub);
        }
    }
    virtual bool canDelete(App::DocumentObject *obj) const override {
        switch(imp->canDelete(obj)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDelete(obj);
        }
    }
    //@}

    /** @name Restoring view provider from document load */
    //@{
    virtual void startRestoring() override {
        ViewProviderT::startRestoring();
        imp->startRestoring();
    }
    virtual void finishRestoring() override {
        imp->finishRestoring();
        ViewProviderT::finishRestoring();
    }
    //@}

    /** @name Drag and drop */
    //@{
    /// Returns true if the view provider generally supports dragging objects
    virtual bool canDragObjects() const override {
        switch (imp->canDragObjects()) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDragObjects();
        }
    }
    /// Check whether the object can be removed from the view provider by drag and drop
    virtual bool canDragObject(App::DocumentObject* obj) const override {
        switch (imp->canDragObject(obj)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDragObject(obj);
        }
    }
    /// Starts to drag the object
    virtual void dragObject(App::DocumentObject* obj) override {
        App::AutoTransaction committer;
        switch (imp->dragObject(obj)) {
        case ViewProviderPythonFeatureImp::Accepted:
        case ViewProviderPythonFeatureImp::Rejected:
            return;
        default:
            return ViewProviderT::dragObject(obj);
        }
    }
    /// Returns true if the view provider generally accepts dropping of objects
    virtual bool canDropObjects() const override {
        switch (imp->canDropObjects()) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDropObjects();
        }
    }
    /// Check whether the object can be dropped to the view provider by drag and drop
    virtual bool canDropObject(App::DocumentObject* obj) const override {
        switch (imp->canDropObject(obj)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDropObject(obj);
        }
    }
    /// If the dropped object type is accepted the object will be added as child
    virtual void dropObject(App::DocumentObject* obj) override {
        App::AutoTransaction committer;
        switch (imp->dropObject(obj)) {
        case ViewProviderPythonFeatureImp::Accepted:
        case ViewProviderPythonFeatureImp::Rejected:
            return;
        default:
            return ViewProviderT::dropObject(obj);
        }
    }
    /** Return false to force drop only operation for a give object*/
    virtual bool canDragAndDropObject(App::DocumentObject *obj) const override {
        switch (imp->canDragAndDropObject(obj)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDragAndDropObject(obj);
        }
    }
    virtual bool canDropObjectEx(App::DocumentObject *obj, App::DocumentObject *owner,
            const char *subname, const std::vector<std::string> &elements) const override
    {
        switch (imp->canDropObjectEx(obj,owner,subname,elements)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::canDropObjectEx(obj,owner,subname,elements);
        }
    }
    /** Add an object with full qualified name to the view provider by drag and drop */
    virtual std::string dropObjectEx(App::DocumentObject *obj, App::DocumentObject *owner,
            const char *subname, const std::vector<std::string> &elements) override
    {
        App::AutoTransaction committer;
        std::string ret;
        if(!imp->dropObjectEx(obj,owner,subname,elements,ret))
            ret = ViewProviderT::dropObjectEx(obj,owner,subname,elements);
        return ret;
    }
    //@}

    /** @name Display methods */
    //@{
    /// Returns true if the icon must always appear enabled in the tree view
    virtual bool isShow() const override {
        switch(imp->isShow()) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::isShow();
        }
    }
    /// get the default display mode
    virtual const char* getDefaultDisplayMode() const override {
        defaultMode.clear();
        if(imp->getDefaultDisplayMode(defaultMode))
            return defaultMode.c_str();
        return ViewProviderT::getDefaultDisplayMode();
    }
    /// returns a list of all possible modes
    virtual std::vector<std::string> getDisplayModes() const override {
        std::vector<std::string> modes = ViewProviderT::getDisplayModes();
        std::vector<std::string> more_modes = imp->getDisplayModes();
        modes.insert(modes.end(), more_modes.begin(), more_modes.end());
        return modes;
    }
    /// set the display mode
    virtual void setDisplayMode(const char* ModeName) override {
        //std::string mask = imp->setDisplayMode(ModeName);
        //ViewProviderT::setDisplayMaskMode(mask.c_str());
        //ViewProviderT::setDisplayMode(ModeName);
    }
    //@}

    virtual bool canRemoveChildrenFromRoot() const override {
        switch(imp->canRemoveChildrenFromRoot()) {
        case ViewProviderPythonFeatureImp::NotImplemented:
            return ViewProviderT::canRemoveChildrenFromRoot();
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        default:
            return false;
        }
    }

    PyObject* getPyObject() override {
        return ViewProviderT::getPyObject();
    }

protected:
    virtual void onChanged(const App::Property* prop) override {
        if (prop == &Proxy) {
            imp->init(Proxy.getValue().ptr());
            if (ViewProviderT::pcObject && !Proxy.getValue().is(Py::_None())) {
                if (!_attached) {
                    _attached = true;
                    imp->attach(ViewProviderT::pcObject);
                    ViewProviderT::attach(ViewProviderT::pcObject);
                    // needed to load the right display mode after they're known now
                    ViewProviderT::DisplayMode.touch();
                    ViewProviderT::setOverrideMode(viewerMode);
                }
                ViewProviderT::updateView();
            }
        }

        imp->onChanged(prop);
        ViewProviderT::onChanged(prop);
    }
    /// is called by the document when the provider goes in edit mode
    virtual bool setEdit(int ModNum) override
    {
        switch (imp->setEdit(ModNum)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::setEdit(ModNum);
        }
    }
    /// is called when you lose the edit mode
    virtual void unsetEdit(int ModNum) override
    {
        switch (imp->unsetEdit(ModNum)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return;
        case ViewProviderPythonFeatureImp::Rejected:
        default:
            return ViewProviderT::unsetEdit(ModNum);
        }
    }

    virtual std::string getDropPrefix() const override {
        std::string prefix;
        if(!imp->getDropPrefix(prefix))
            return ViewProviderT::getDropPrefix();
        return prefix;
    }

    virtual int replaceObject(App::DocumentObject *oldObj, App::DocumentObject *newObj) override {
        App::AutoTransaction committer;
        switch (imp->replaceObject(oldObj,newObj)) {
        case ViewProviderPythonFeatureImp::Accepted:
            return 1;
        case ViewProviderPythonFeatureImp::Rejected:
            return 0;
        default:
            return ViewProviderT::replaceObject(oldObj,newObj);
        }
    }

    virtual ViewProviderDocumentObject *getLinkedViewProvider(
            std::string *subname=nullptr, bool recursive=false) const override{
        ViewProviderDocumentObject *res = nullptr;
        if(!imp->getLinkedViewProvider(res, subname, recursive))
            res = ViewProviderT::getLinkedViewProvider(subname,recursive);
        return res;
    }

    virtual void editProperty(const char *propName) override {
        if (!imp->editProperty(propName))
            ViewProviderT::editProperty(propName);
    }

public:
    virtual void setupContextMenu(QMenu* menu, QObject* recipient, const char* member) override
    {
        if(!imp->setupContextMenu(menu))
            ViewProviderT::setupContextMenu(menu, recipient, member);
    }

protected:
    virtual bool doubleClicked() override
    {
        App::AutoTransaction committer;
        switch (imp->doubleClicked()) {
        case ViewProviderPythonFeatureImp::Accepted:
            return true;
        case ViewProviderPythonFeatureImp::Rejected:
            return false;
        default:
            return ViewProviderT::doubleClicked();
        }
    }
    virtual void setOverrideMode(const std::string &mode) override
    {
        ViewProviderT::setOverrideMode(mode);
        viewerMode = mode;
    }

private:
    ViewProviderPythonFeatureImp* imp;
    App::PropertyPythonObject Proxy;
    mutable std::string defaultMode;
    std::string viewerMode;
    bool _attached;
};

// Special Feature-Python classes
typedef ViewProviderPythonFeatureT<ViewProviderDocumentObject> ViewProviderPythonFeature;

} // namespace Gui

#endif // GUI_VIEWPROVIDERPYTHONFEATURE_H

