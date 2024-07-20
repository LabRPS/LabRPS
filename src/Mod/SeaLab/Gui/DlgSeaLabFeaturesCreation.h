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

#ifndef SEALABGUI_DLGSeaLabFeaturesCreation_H
#define SEALABGUI_DLGSeaLabFeaturesCreation_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/SeaLabAPI/App/SeaLabFeature.h>
#include <Mod/SeaLab/App/SeaLabUtils.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace SeaLab { class SeaLabSimulation; }

namespace SeaLab {
class SeaLabFeature;
}

namespace SeaLabGui {

class Ui_DlgSeaLabFeaturesCreation;
class DlgSeaLabFeaturesCreation : public QWidget
{
    Q_OBJECT

public:
    DlgSeaLabFeaturesCreation(QWidget* parent = nullptr, SeaLabAPI::SeaLabFeature* feature = nullptr);
    ~DlgSeaLabFeaturesCreation();
    void createDlgSeaLabFeature(const QString&);
    void accept(const QString&);
    void reject();

private Q_SLOTS:
    void featureTypeComboBoxIndexChanged(int index);

private:  
    void fillFeatureComboBox(SeaLab::SeaLabSimulation* sim, QComboBox* comboBox, int selectedFeatureType);

private:
    std::unique_ptr<Ui_DlgSeaLabFeaturesCreation> ui;
};

class TaskSeaLabFeatures : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSeaLabFeatures();
    ~TaskSeaLabFeatures();

public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private:
    DlgSeaLabFeaturesCreation* widget;
};

class TaskSeaLabFeaturesEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSeaLabFeaturesEdit(SeaLabAPI::SeaLabFeature* feature);
    ~TaskSeaLabFeaturesEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgSeaLabFeaturesCreation* widget;

};

} // namespace SeaLabGui

#endif // SEALABGUI_DLGSeaLabFeaturesCreation_H
