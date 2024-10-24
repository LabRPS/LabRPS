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

#ifndef GUI_VIEWPROVIDER_H
#define GUI_VIEWPROVIDER_H

#include <bitset>
#include <map>
#include <string>
#include <vector>
#include <QIcon>
#include <boost_signals2.hpp>

#include <App/TransactionalObject.h>
#include <Base/Vector3D.h>


class QString;
class QMenu;
class QObject;


namespace Gui {
    namespace TaskView {
        class TaskContent;
    }
class ViewProviderPy;
class ObjectItem;
class MDIView;

enum ViewStatus {
    UpdateData = 0,
    Detach = 1,
    isRestoring = 2,
    UpdatingView = 3,
    TouchDocument = 4,
};



/** General interface for all visual stuff in LabRPS
  * This class is used to generate and handle all around
  * visualizing and presenting objects from the LabRPS
  * App layer to the user. This class and its descendents
  * have to be implemented for any object type in order to
  * show them in the 3DView and TreeView.
  */
class GuiExport ViewProvider : public App::TransactionalObject
{
    PROPERTY_HEADER(Gui::ViewProvider);

public:
    /// constructor.
    ViewProvider();

    /// destructor.
    virtual ~ViewProvider();


    /** @name Selection handling
      * This group of methods do the selection handling.
      * Here you can define how the selection for your ViewProfider
      * works.
     */
    //@{

    /// indicates if the ViewProvider use the new Selection model
    virtual bool useNewSelectionModel() const;
    virtual bool isSelectable() const {return true;}

  

    /**
     * Get called if the object is about to get deleted.
     * Here you can delete other objects, switch their visibility or prevent the deletion of the object.
     * @param subNames  list of selected subelements
     * @return          true if the deletion is approved by the view provider.
     */
    virtual bool onDelete(const std::vector<std::string> &subNames);
    /** Called before deletion
     *
     * Unlike onDelete(), this function is guaranteed to be called before
     * deletion, either by Document::remObject(), or on document deletion.
     */
    virtual void beforeDelete();
    /**
     * @brief Asks the view provider if the given object that is part of its
     * outlist can be removed from there without breaking it.
     * @param obj is part of the outlist of the object associated to the view provider
     * @return true if the removal is approved by the view provider.
     */
    virtual bool canDelete(App::DocumentObject* obj) const;
    //@}


    /** @name Methods used by the Tree
      * If you want to take control over the
      * appearance of your object in the tree you
      * can reimplement these methods.
     */
    //@{
    /// deliver the icon shown in the tree view
    virtual QIcon getIcon() const;

     /** @name Methods used by the Tree
     * If you want to take control over the
     * viewprovider specific overlay icons that will be drawn with color
     * regardless of whether the icon is greyed out or not, such as status, you
     * can reimplement this method.
     */
    virtual QIcon mergeColorfulOverlayIcons (const QIcon & orig) const;

    /** deliver the children belonging to this object
      * this method is used to deliver the objects to
      * the tree framework which should be grouped under its
      * label. Obvious is the usage in the group but it can
      * be used for any kind of grouping needed for a special
      * purpose.
      */
    virtual std::vector<App::DocumentObject*> claimChildren() const;
    //@}

    /** @name Drag and drop
     * To enable drag and drop you have to re-implement \ref canDragObjects() and
     * \ref canDropObjects() to return true. For finer control you can also re-implement
     * \ref canDragObject() or \ref canDropObject() to filter certain object types, by
     * default these methods don't filter any types.
     * To take action of drag and drop the method \ref dragObject() and \ref dropObject()
     * must be re-implemented, too.
     */
    //@{
    /** Check whether children can be removed from the view provider by drag and drop */
    virtual bool canDragObjects() const;
    /** Check whether the object can be removed from the view provider by drag and drop */
    virtual bool canDragObject(App::DocumentObject*) const;
    /** Remove a child from the view provider by drag and drop */
    virtual void dragObject(App::DocumentObject*);
    /** Check whether objects can be added to the view provider by drag and drop or drop only */
    virtual bool canDropObjects() const;
    /** Check whether the object can be dropped to the view provider by drag and drop or drop only*/
    virtual bool canDropObject(App::DocumentObject*) const;
    /** Return false to force drop only operation for a given object*/
    virtual bool canDragAndDropObject(App::DocumentObject*) const;
    /** Add an object to the view provider by drag and drop */
    virtual void dropObject(App::DocumentObject*);
    /** Query object dropping with full qualified name
     *
     * Tree view now calls this function instead of canDropObject(), and may
     * query for objects from other document. The default implementation
     * (actually in ViewProviderDocumentObject) inhibites cross document
     * dropping, and calls canDropObject(obj) for the rest. Override this
     * function to enable cross document linking.
     *
     * @param obj: the object being dropped
     *
     * @param owner: the (grand)parent object of the dropping object. Maybe
     * null. This may not be the top parent object, as tree view will try to
     * find a parent of the dropping object relative to this object to avoid
     * cyclic dependency
     *
     * @param subname: subname reference to the dropping object
     *
     * @param elements: non-object sub-elements, e.g. Faces, Edges, selected
     * when the object is being dropped
     *
     * @return Return whether the dropping action is allowed.
     * */
    virtual bool canDropObjectEx(App::DocumentObject *obj, App::DocumentObject *owner,
            const char *subname, const std::vector<std::string> &elements) const;

    /// return a subname referencing the sub-object holding the dropped objects
    virtual std::string getDropPrefix() const { return std::string(); }

    /** Add an object with full qualified name to the view provider by drag and drop
     *
     * @param obj: the object being dropped
     *
     * @param owner: the (grand)parent object of the dropping object. Maybe
     * null. This may not be the top parent object, as tree view will try to
     * find a parent of the dropping object relative to this object to avoid
     * cyclic dependency
     *
     * @param subname: subname reference to the dropping object
     *
     * @param elements: non-object sub-elements, e.g. Faces, Edges, selected
     * when the object is being dropped
     *
     * @return Optionally returns a subname reference locating the dropped
     * object, which may or may not be the actual dropped object, e.g. it may be
     * a link.
     */
    virtual std::string dropObjectEx(App::DocumentObject *obj, App::DocumentObject *owner,
            const char *subname, const std::vector<std::string> &elements);
    /** Replace an object to the view provider by drag and drop
     *
     * @param oldObj: object to be replaced
     * @param newObj: object to replace with
     *
     * @return Returns 0 if not found, 1 if succeeded, -1 if not supported
     */
    virtual int replaceObject(App::DocumentObject *oldObj, App::DocumentObject *newObj);
    //@}

    /** Tell the tree view if this object should appear there */
    virtual bool showInTree() const { return true; }
    /** Tell the tree view to remove children items from the tree root*/
    virtual bool canRemoveChildrenFromRoot() const {return true;}

    /** @name Signals of the view provider */
    //@{
    /// signal on icon change
    boost::signals2::signal<void ()> signalChangeIcon;
    /// signal on tooltip change
    boost::signals2::signal<void (const QString&)> signalChangeToolTip;
    /// signal on status tip change
    boost::signals2::signal<void (const QString&)> signalChangeStatusTip;
    //@}

    /** update the content of the ViewProvider
     * this method have to implement the recalculation
     * of the ViewProvider. There are different reasons to
     * update. E.g. only the view attribute has changed, or
     * the data has manipulated.
     */
    virtual void update(const App::Property*);
    virtual void updateData(const App::Property*);
    bool isUpdatesEnabled () const;
    void setUpdatesEnabled (bool enable);

    /// return the status bits
    unsigned long getStatus() const {return StatusBits.to_ulong();}
    bool testStatus(ViewStatus pos) const {return StatusBits.test((size_t)pos);}
    void setStatus(ViewStatus pos, bool on) {StatusBits.set((size_t)pos, on);}

    std::string toString() const;
    PyObject* getPyObject();

    /** @name Display mode methods
     */
    //@{
    std::string getActiveDisplayMode() const;
    /// set the display mode
    virtual void setDisplayMode(const char* ModeName);
    /// get the default display mode
    virtual const char* getDefaultDisplayMode() const;
    /// returns a list of all possible display modes
    virtual std::vector<std::string> getDisplayModes() const;
    /// Hides the view provider
    virtual void hide();
    /// Shows the view provider
    virtual void show();
    /// checks whether the view provider is visible or not
    virtual bool isShow() const;
    void setVisible(bool);
    bool isVisible() const;
    void setLinkVisible(bool);
    bool isLinkVisible() const;
    /// Overrides the display mode with mode.
    virtual void setOverrideMode(const std::string &mode);
    const std::string getOverrideMode();
    //@}

    /** @name Color management methods
     */
    //@{
    //virtual std::map<std::string, App::Color> getElementColors(const char *element=nullptr) const {
    //    (void)element;
    //    return {};
    //}
    //virtual void setElementColors(const std::map<std::string, App::Color> &colors) {
    //    (void)colors;
    //}
    static const std::string &hiddenMarker();
    static const char *hasHiddenMarker(const char *subname);
    //@}

    /** @name Edit methods
     * if the Viewprovider goes in edit mode
     * you can handle most of the events in the viewer by yourself
     */
    //@{
    // the below enum is reflected in 'userEditModes' std::map in Application.h
    // so it is possible for the user to choose a default one through GUI
    // if you add a mode here, consider to make it accessible there too
    enum EditMode {Default = 0,
                   Transform,
                   Cutting,
                   Color,
    };
protected:
    /// is called by the document when the provider goes in edit mode
    virtual bool setEdit(int ModNum);
    /// is called when you lose the edit mode
    virtual void unsetEdit(int ModNum);
    /// return the edit mode or -1 if nothing is being edited
    int getEditingMode() const;

public:
    virtual ViewProvider *startEditing(int ModNum=0);
    bool isEditing() const;
    void finishEditing();

    //@}

    /** @name Task panel
     * With this interface the ViewProvider can steer the
     * appearance of widgets in the task view
     */
    //@{
    /// get a list of TaskBoxes associated with this object
    virtual void getTaskViewContent(std::vector<Gui::TaskView::TaskContent*>&) const {}
    //@}

    /// is called when the provider is in edit and a key event occurs. Only ESC ends edit.
    virtual bool keyPressed(bool pressed, int key);
    /// Is called by the tree if the user double clicks on the object. It returns the string
    /// for the transaction that will be shown in the undo/redo dialog.
    /// If null is returned then no transaction will be opened.
    virtual const char* getTransactionText() const { return nullptr; }
    /// is called by the tree if the user double clicks on the object
    virtual bool doubleClicked() { return false; }
    /// set up the context-menu with the supported edit modes
    virtual void setupContextMenu(QMenu*, QObject*, const char*);

    virtual MDIView *getMDIView() const {
        return nullptr;
    }

public:

    //restoring the object from document:
    //this may be of interest to extensions, hence call them
    virtual void Restore(Base::XMLReader& reader);
    bool isRestoring() {return testStatus(Gui::isRestoring);}

protected:
   
    /// Reimplemented from subclass
    void onBeforeChange(const App::Property* prop);
    /// Reimplemented from subclass
    void onChanged(const App::Property* prop);

    /** @name Methods used by the Tree
     * If you want to take control over the
     * viewprovider specific overlay icons, that will be grayed out together
     * with the base icon, you can reimplement this method.
     */
    virtual QIcon mergeGreyableOverlayIcons (const QIcon & orig) const;

    /// Turn on mode switch
    virtual void setModeSwitch();

protected:
    const char* sPixmap;
    ViewProviderPy* pyViewObject;
    std::string overrideMode;
    std::bitset<32> StatusBits;

private:
    int _iActualMode;
    int _iEditMode;
    int viewOverrideMode;
    std::string _sCurrentMode;
    std::map<std::string, int> _sDisplayMaskModes;
};

} // namespace Gui

#endif // GUI_VIEWPROVIDER_H
