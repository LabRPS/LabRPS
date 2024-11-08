/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *                *
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

#ifndef USERLABGUI_DLGUserLabFeaturesCreation_H
#define USERLABGUI_DLGUserLabFeaturesCreation_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/UserLabAPI/App/UserLabFeature.h>
#include <Mod/UserLab/App/UserLabUtils.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace UserLab { class UserLabSimulation; }

namespace UserLab {
class UserLabFeature;
}

namespace UserLabGui {

class Ui_DlgUserLabFeaturesCreation;
class DlgUserLabFeaturesCreation : public QWidget
{
    Q_OBJECT

public:
    DlgUserLabFeaturesCreation(QWidget* parent = nullptr, UserLabAPI::UserLabFeature* feature = nullptr);
    ~DlgUserLabFeaturesCreation();
    void createDlgUserLabFeature(const QString&);
    void accept(const QString&);
    void reject();

private Q_SLOTS:
    void featureTypeComboBoxIndexChanged(int index);

private:  
    void fillFeatureComboBox(UserLab::UserLabSimulation* sim, QComboBox* comboBox, int selectedFeatureType);

private:
    std::unique_ptr<Ui_DlgUserLabFeaturesCreation> ui;
};

class TaskUserLabFeatures : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskUserLabFeatures();
    ~TaskUserLabFeatures();

public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private:
    DlgUserLabFeaturesCreation* widget;
};

class TaskUserLabFeaturesEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskUserLabFeaturesEdit(UserLabAPI::UserLabFeature* feature);
    ~TaskUserLabFeaturesEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgUserLabFeaturesCreation* widget;

};

} // namespace UserLabGui

#endif // USERLABGUI_DLGUserLabFeaturesCreation_H
