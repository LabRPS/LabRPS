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

#ifndef SEISMICLAB_DLGNEWSIMULATION_H
#define SEISMICLAB_DLGNEWSIMULATION_H

#include <memory>
#include <QEventLoop>
#include <QPointer>
#include <App/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Mod/SeismicLabAPI/App/SeismicLabFeature.h>

class QSignalMapper;

namespace App { class Document; }
namespace Gui { class Document; }
namespace SeismicLab
{
class SeismicLabSimulation;
}

namespace SeismicLab {
class SeismicLabFeature;
class SeismicLabFeatureObject;
}
namespace SeismicLabGui {


class Ui_DlgNewSimulation;
class DlgNewSimulation : public QWidget
{
      Q_OBJECT

public:
      DlgNewSimulation(QWidget* parent = nullptr, SeismicLab::SeismicLabSimulation* sim = nullptr);
    ~DlgNewSimulation();
    void accept(const QString&);
    void reject();
    void createNewSimulation();
    void saveSimulation(App::Document* doc,  SeismicLab::SeismicLabSimulation* sim);

private Q_SLOTS:
    void radioButtonStationarityToggled(bool);
    void radioButtonNonStationarityToggled(bool);
    void radioButtonUniformModulationToggled(bool);
    void radioButtonNonGeneralModulationToggled(bool);
    void radioButtonGaussianityToggled(bool);
    void radioButtonNonGaussianityToggled(bool);

private:

    std::unique_ptr<Ui_DlgNewSimulation> ui;
    App::DocumentObjectWeakPtrT seismicLabFeaturePtr;

    bool stationarity;
    bool uniformModulation;
    bool gaussianity;

};


class Ui_DlgSeismicLabFeatures;
class DlgSeismicLabFeatures : public QWidget
{
    Q_OBJECT

public:
    DlgSeismicLabFeatures(QWidget* parent = nullptr,  SeismicLab::SeismicLabSimulation* sim = nullptr);
    ~DlgSeismicLabFeatures();
    void fillRPSFeaturesComboxBoxes( SeismicLab::SeismicLabSimulation* sim = nullptr);
    std::vector<QComboBox*> getAllComboBoxes();
    void setAllComboBoxesCurrentText( SeismicLab::SeismicLabSimulation* sim);
    void saveLabFeatures( SeismicLab::SeismicLabSimulation* sim);

private Q_SLOTS:
    void onInitialSettingLocationDistribution();
    void onInitialSettingMeanAccelerationProfile();
    void onInitialSettingSpectrum();
    void onInitialSettingSpectrumDecompositionMethod();
    void onInitialSettingCoherenceFunction();
    void onInitialSettingSimulationMethod();
    void onInitialSettingFrequencyDistribution();
    void onInitialSettingRandomnessProvider();
    void onInitialSettingModulationFunction();
    void onInitialSettingCorrelationFunction();
    void onInitialSettingUserDefinedRPSObject();
    void onInitialSettingCumulativeProbabilityDistribution();
    void onInitialSettingKurtosis();
    void onInitialSettingPeakFactor();
    void onInitialSettingProbabilityDensityFunction();
    void onInitialSettingShearVelocityOfFlow();
    void onInitialSettingSkewness();
    void onInitialSettingStandardDeviation();
    void onInitialSettingVariance();
    void onInitialSettingWavePassageEffect();

private:
    int mode;
    std::unique_ptr<Ui_DlgSeismicLabFeatures> ui;
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
    DlgSeismicLabFeatures* dlgSeismicLabFeatures;

};

class TaskNewSimulationEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskNewSimulationEdit( SeismicLab::SeismicLabSimulation* sim);
    ~TaskNewSimulationEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

private:
    DlgNewSimulation* widget;
    DlgSeismicLabFeatures* dlgSeismicLabFeatures;

     SeismicLab::SeismicLabSimulation* _sim;
};

} // namespace SeismicLabGui

#endif // SEISMICLAB_DLGNEWSIMULATION_H
