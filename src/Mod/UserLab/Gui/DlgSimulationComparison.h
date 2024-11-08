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

#ifndef USERLABGUI_DlgSimulationComparison_H
#define USERLABGUI_DlgSimulationComparison_H
#define QT_NO_KEYWORDS

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyGeo.h>
#include <App/PropertyUnits.h>
#include <QString>
#include <QComboBox>

class QSignalMapper;
namespace UserLab
{
class UserLabSimulation;
class UserLabSimulationComparison;
}

namespace UserLabGui {

class Ui_DlgSimulationComparison;
class DlgSimulationComparison : public QWidget
{
    Q_OBJECT

public:
    DlgSimulationComparison(UserLab::UserLabSimulationComparison* comparison, QWidget* parent = nullptr);
    ~DlgSimulationComparison();
    void accept();
    void reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

private Q_SLOTS:
    void featureGroupCandidateComboBoxIndexChanged(int index);
    void pluggedFeatureCandidate1ComboBoxIndexChanged(int index);
    void pluggedFeatureCandidate2ComboBoxIndexChanged(int index);
    void simCandidate1ComboBoxIndexChanged(int index);
    void simCandidate2ComboBoxIndexChanged(int index);

private:  
    void fillPluggedFeatureComboBox(UserLab::UserLabSimulation* sim, QComboBox* comboBox);
    void fillFeatureMethodComboBoxCandidate(UserLab::UserLabSimulation* sim, QComboBox* comboBox);    
    void fillFeatureComboBox(UserLab::UserLabSimulation* sim, QComboBox* comboBox, QString group, QString type); 


private:
    std::unique_ptr<Ui_DlgSimulationComparison> ui;

public:
    UserLab::UserLabSimulationComparison* _comparison;
};

class DlgSimulationComparisonEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgSimulationComparisonEdit(UserLab::UserLabSimulationComparison* comparison);
    ~DlgSimulationComparisonEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;
    void modifyStandardButtons(QDialogButtonBox*);

public:
    DlgSimulationComparison* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace UserLabGui

#endif // USERLABGUI_DlgSimulationComparison_H
