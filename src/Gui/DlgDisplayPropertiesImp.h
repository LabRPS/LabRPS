/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
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


#ifndef GUI_DIALOG_DLGDISPLAYPROPERTIES_IMP_H
#define GUI_DIALOG_DLGDISPLAYPROPERTIES_IMP_H

#include <memory>
#include <vector>
#include <QDialog>

#include <Gui/Selection.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>

namespace App
{
  class Property;
}

namespace Gui {

  class ViewProvider;
  class Command;

namespace Dialog {

/**
 * The DlgDisplayPropertiesImp class implements a dialog containing all available document
 * templates to create a new document.
 * \author Jürgen Riegel
 */
class DlgDisplayPropertiesImp : public QDialog,
                                public Gui::SelectionSingleton::ObserverType
{
    Q_OBJECT

public:
    DlgDisplayPropertiesImp(bool floating, QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::WindowFlags());
    ~DlgDisplayPropertiesImp();
    /// Observer message from the Selection
    void OnChange(Gui::SelectionSingleton::SubjectType &rCaller,
                  Gui::SelectionSingleton::MessageType Reason);
    void showDefaultButtons(bool);
    void reject();

private Q_SLOTS:


protected:
    void changeEvent(QEvent *e);

private:
    void slotChangedObject(const Gui::ViewProvider&, const App::Property& Prop);
    std::vector<ViewProvider*> getSelection() const;

private:
    class Private;
    std::unique_ptr<Private> d;
};

class TaskDisplayProperties : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskDisplayProperties();
    ~TaskDisplayProperties();

public:
    bool reject();

    bool isAllowedAlterDocument() const
    { return true; }
    bool isAllowedAlterView() const
    { return true; }
    bool isAllowedAlterSelection() const
    { return true; }
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgDisplayPropertiesImp* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGDISPLAYPROPERTIES_IMP_H
