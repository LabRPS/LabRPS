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

#ifndef USERDEFINEDPHENOMENONLAB_DLGNEWSIMULATION_H
#define USERDEFINEDPHENOMENONLAB_DLGNEWSIMULATION_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/UserDefinedPhenomenonLabAPI/App/UserDefinedPhenomenonLabFeature.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace UserDefinedPhenomenonLab
{
class UserDefinedPhenomenonLabSimulation;
}

namespace UserDefinedPhenomenonLab {
class UserDefinedPhenomenonLabFeature;
class UserDefinedPhenomenonLabFeatureObject;
}
namespace UserDefinedPhenomenonLabGui {


class Ui_DlgNewSimulation;
class DlgNewSimulation : public QWidget
{
      Q_OBJECT

public:
      DlgNewSimulation(QWidget* parent = nullptr, UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = nullptr);
    ~DlgNewSimulation();
    void accept(const QString&);
    void reject();
    void createNewSimulation();
    void saveSimulation(App::Document* doc,  UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim);

private Q_SLOTS:
    void radioButtonStationarityToggled(bool);
    void radioButtonNonStationarityToggled(bool);
    void radioButtonUniformModulationToggled(bool);
    void radioButtonNonGeneralModulationToggled(bool);
    void radioButtonGaussianityToggled(bool);
    void radioButtonNonGaussianityToggled(bool);

private:

    std::unique_ptr<Ui_DlgNewSimulation> ui;
    App::DocumentObjectWeakPtrT userDefinedPhenomenonFeaturePtr;

    bool stationarity;
    bool uniformModulation;
    bool gaussianity;

};


class Ui_DlgUserDefinedPhenomenonLabFeatures;
class DlgUserDefinedPhenomenonLabFeatures : public QWidget
{
    Q_OBJECT

public:
    DlgUserDefinedPhenomenonLabFeatures(QWidget* parent = nullptr,  UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = nullptr);
    ~DlgUserDefinedPhenomenonLabFeatures();
    void fillRPSFeaturesComboxBoxes( UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim = nullptr);
    std::vector<QComboBox*> getAllComboBoxes();
    void setAllComboBoxesCurrentText( UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim);
    void saveLabFeatures( UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim);

private Q_SLOTS:
   
    void onInitialSettingSimulationMethod();

private:
    int mode;
    std::unique_ptr<Ui_DlgUserDefinedPhenomenonLabFeatures> ui;
};



class TaskNewSimulation : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskNewSimulation();
    ~TaskNewSimulation();

public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private:
    DlgNewSimulation* widget;
    DlgUserDefinedPhenomenonLabFeatures* dlgUserDefinedPhenomenonLabFeatures;

};

class TaskNewSimulationEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskNewSimulationEdit( UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* sim);
    ~TaskNewSimulationEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgNewSimulation* widget;
    DlgUserDefinedPhenomenonLabFeatures* dlgUserDefinedPhenomenonLabFeatures;

     UserDefinedPhenomenonLab::UserDefinedPhenomenonLabSimulation* _sim;
};

} // namespace UserDefinedPhenomenonLabGui

#endif // USERDEFINEDPHENOMENONLAB_DLGNEWSIMULATION_H
