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

#ifndef USERDEFINEDPHENOMENONLABGUI_DLGUserDefinedPhenomenonLabFeaturesCreation_H
#define USERDEFINEDPHENOMENONLABGUI_DLGUserDefinedPhenomenonLabFeaturesCreation_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeature.h>
#include <Mod/UserDefinedPhenomenonLab/App/UserDefinedPhenomenonLabUtils.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace UserDefinedPhenomenonLab { class UserDefinedPhenomenonLabSimulation; }

namespace UserDefinedPhenomenonLab {
class UserDefinedPhenomenonLabFeature;
}

namespace UserDefinedPhenomenonLabGui {

class Ui_DlgUserDefinedPhenomenonLabFeaturesCreation;
class DlgUserDefinedPhenomenonLabFeaturesCreation : public QWidget
{
    Q_OBJECT

public:
    DlgUserDefinedPhenomenonLabFeaturesCreation(QWidget* parent = nullptr, UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature* feature = nullptr);
    ~DlgUserDefinedPhenomenonLabFeaturesCreation();
    void createDlgUserDefinedPhenomenonLabFeature(const QString&);
    void accept(const QString&);
    void reject();

private Q_SLOTS:
    void featureTypeComboBoxIndexChanged(int index);

private:  
    void fillFeatureComboBox(UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim, QComboBox* comboBox, int selectedFeatureType);

private:
    std::unique_ptr<Ui_DlgUserDefinedPhenomenonLabFeaturesCreation> ui;
};

class TaskUserDefinedPhenomenonLabFeatures : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskUserDefinedPhenomenonLabFeatures();
    ~TaskUserDefinedPhenomenonLabFeatures();

public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private:
    DlgUserDefinedPhenomenonLabFeaturesCreation* widget;
};

class TaskUserDefinedPhenomenonLabFeaturesEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskUserDefinedPhenomenonLabFeaturesEdit(UserDefinedPhenomenonLabAPI::UserDefinedPhenomenonLabFeature* feature);
    ~TaskUserDefinedPhenomenonLabFeaturesEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgUserDefinedPhenomenonLabFeaturesCreation* widget;

};

} // namespace UserDefinedPhenomenonLabGui

#endif // USERDEFINEDPHENOMENONLABGUI_DLGUserDefinedPhenomenonLabFeaturesCreation_H
