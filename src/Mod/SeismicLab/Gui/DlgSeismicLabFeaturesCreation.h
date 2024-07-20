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

#ifndef SEISMICLABGUI_DLGSeismicLabFeaturesCreation_H
#define SEISMICLABGUI_DLGSeismicLabFeaturesCreation_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeature.h>
#include <Mod/SeismicLab/App/SeismicLabUtils.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace SeismicLab { class SeismicLabSimulation; }

namespace SeismicLab {
class SeismicLabFeature;
}

namespace SeismicLabGui {

class Ui_DlgSeismicLabFeaturesCreation;
class DlgSeismicLabFeaturesCreation : public QWidget
{
    Q_OBJECT

public:
    DlgSeismicLabFeaturesCreation(QWidget* parent = nullptr, SeismicLabAPI::SeismicLabFeature* feature = nullptr);
    ~DlgSeismicLabFeaturesCreation();
    void createDlgSeismicLabFeature(const QString&);
    void accept(const QString&);
    void reject();

private Q_SLOTS:
    void featureTypeComboBoxIndexChanged(int index);

private:  
    void fillFeatureComboBox(SeismicLab::SeismicLabSimulation* sim, QComboBox* comboBox, int selectedFeatureType);

private:
    std::unique_ptr<Ui_DlgSeismicLabFeaturesCreation> ui;
};

class TaskSeismicLabFeatures : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSeismicLabFeatures();
    ~TaskSeismicLabFeatures();

public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private:
    DlgSeismicLabFeaturesCreation* widget;
};

class TaskSeismicLabFeaturesEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSeismicLabFeaturesEdit(SeismicLabAPI::SeismicLabFeature* feature);
    ~TaskSeismicLabFeaturesEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgSeismicLabFeaturesCreation* widget;

};

} // namespace SeismicLabGui

#endif // SEISMICLABGUI_DLGSeismicLabFeaturesCreation_H
