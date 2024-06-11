/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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

#ifndef WINDLAB_DLGNEWSIMULATION_H
#define WINDLAB_DLGNEWSIMULATION_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/WindLabAPI/App/WindLabFeature.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace WindLab
{
class WindLabSimulation;
}

namespace WindLab {
class WindLabFeature;
class WindLabFeatureObject;
}
namespace WindLabGui {


class Ui_DlgNewSimulation;
class DlgNewSimulation : public QWidget
{
      Q_OBJECT

public:
      DlgNewSimulation(QWidget* parent = nullptr, WindLab::WindLabSimulation* sim = nullptr);
    ~DlgNewSimulation();
    void accept(const QString&);
    void reject();
    void createNewSimulation();
    void saveSimulation(App::Document* doc,  WindLab::WindLabSimulation* sim);

private Q_SLOTS:
    void radioButtonStationarityToggled(bool);
    void radioButtonNonStationarityToggled(bool);
    void radioButtonUniformModulationToggled(bool);
    void radioButtonNonGeneralModulationToggled(bool);
    void radioButtonGaussianityToggled(bool);
    void radioButtonNonGaussianityToggled(bool);

private:

    std::unique_ptr<Ui_DlgNewSimulation> ui;
    App::DocumentObjectWeakPtrT windLabFeaturePtr;

    bool stationarity;
    bool uniformModulation;
    bool gaussianity;

};


class Ui_DlgWindLabFeatures;
class DlgWindLabFeatures : public QWidget
{
    Q_OBJECT

public:
    DlgWindLabFeatures(QWidget* parent = nullptr,  WindLab::WindLabSimulation* sim = nullptr);
    ~DlgWindLabFeatures();
    void fillRPSFeaturesComboxBoxes( WindLab::WindLabSimulation* sim = nullptr);
    std::vector<QComboBox*> getAllComboBoxes();
   /* void fillRPSFeaturesComboxBoxes(WindLabApp::Simulation* sim = nullptr);
    std::vector<QComboBox*> getAllComboBoxes();*/
    void setAllComboBoxesCurrentText( WindLab::WindLabSimulation* sim);
    void saveLabFeatures( WindLab::WindLabSimulation* sim);

private Q_SLOTS:
    void onInitialSettingLocationDistribution();
    void onInitialSettingMeanWindProfile();
    void onInitialSettingAlongWindSpectrum();
    void onInitialSettingVerticalWindSpectrum();
    void onInitialSettingAcrossWindSpectrum();
    void onInitialSettingSpectrumDecompositionMethod();
    void onInitialSettingCoherenceFunction();
    void onInitialSettingSimulationMethod();
    void onInitialSettingFrequencyDistribution();
    void onInitialSettingRandomnessProvider();
    void onInitialSettingModulationFunction();
    void onInitialSettingCorrelationFunction();
    void onInitialSettingUserDefinedRPSObject();
    void onInitialSettingCumulativeProbabilityDistribution();
    void onInitialSettingGustFactor();
    void onInitialSettingKurtosis();
    void onInitialSettingPeakFactor();
    void onInitialSettingProbabilityDensityFunction();
    void onInitialSettingRoughness();
    void onInitialSettingShearVelocityOfFlow();
    void onInitialSettingSkewness();
    void onInitialSettingStandardDeviation();
    void onInitialSettingTurbulenceIntensity();
    void onInitialSettingTurbulenceScale();
    void onInitialSettingVariance();
    void onInitialSettingWavePassageEffect();

private:
    int mode;
    std::unique_ptr<Ui_DlgWindLabFeatures> ui;
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
    DlgWindLabFeatures* dlgWindLabFeatures;

};

class TaskNewSimulationEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskNewSimulationEdit( WindLab::WindLabSimulation* sim);
    ~TaskNewSimulationEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgNewSimulation* widget;
    DlgWindLabFeatures* dlgWindLabFeatures;

     WindLab::WindLabSimulation* _sim;
};

} // namespace WindLabGui

#endif // WINDLAB_DLGNEWSIMULATION_H
