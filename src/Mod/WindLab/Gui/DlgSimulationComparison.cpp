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



#include "PreCompiled.h"

#include "DlgSimulationComparison.h"
#include "ui_DlgSimulationComparison.h"
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>
#include "WindLabSimulationObserver.h"
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLab/App/WindLabSimulationComparison.h>



using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgSimulationComparison */

DlgSimulationComparison::DlgSimulationComparison(WindLab::WindLabSimulationComparison* comparison, QWidget* parent)
    : QWidget(parent), ui(new Ui_DlgSimulationComparison), _comparison(comparison)
{
	ui->setupUi(this);
	connect(ui->comboBox_FeatureGroup, SIGNAL(currentIndexChanged(int)),this, SLOT(featureGroupCandidateComboBoxIndexChanged(int)));
	connect(ui->comboBox_PlggedFeature_Candidate1, SIGNAL(currentIndexChanged(int)),this, SLOT(pluggedFeatureCandidate1ComboBoxIndexChanged(int)));
    connect(ui->comboBox_PlggedFeature_Candidate2, SIGNAL(currentIndexChanged(int)),this, SLOT(pluggedFeatureCandidate2ComboBoxIndexChanged(int)));
	connect(ui->comboBox_Sim_Candidate1, SIGNAL(currentIndexChanged(int)),this, SLOT(simCandidate1ComboBoxIndexChanged(int)));
    connect(ui->comboBox_Sim_Candidate2, SIGNAL(currentIndexChanged(int)),this, SLOT(simCandidate2ComboBoxIndexChanged(int)));

	std::list<std::string> simList = WindLabGui::WindLabSimulationObserver::instance()->simulations();
    if (simList.empty())
        return;
	for (std::list<std::string>::iterator it = simList.begin(); it != simList.end(); ++it) {
        auto sim = App::GetApplication().getActiveDocument()->getObject(it->c_str());
		if (sim)
		{
 			QString itemName = QString::fromUtf8(it->c_str());
            ui->comboBox_Sim_Candidate1->addItem(itemName);
            ui->comboBox_Sim_Candidate2->addItem(itemName);
		}
	}

	QString simeName1 = ui->comboBox_Sim_Candidate1->currentText();
	WindLab::WindLabSimulation* sim1 = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(simeName1.toUtf8().constData()));

	QString simeName2 = ui->comboBox_Sim_Candidate2->currentText();
	WindLab::WindLabSimulation* sim2 = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(simeName2.toUtf8().constData()));

	//ui->SimulationComboBox->setCurrentText(QString::fromUtf8(sim->Label.getValue()));
    
	std::vector<QString> groups = sim1->getWindLabPluggableFeatures();

    for (std::vector<QString>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        ui->comboBox_FeatureGroup->addItem((*i));

	fillPluggedFeatureComboBox(sim1, ui->comboBox_PlggedFeature_Candidate1);
    fillPluggedFeatureComboBox(sim1, ui->comboBox_PlggedFeature_Candidate1);

	if (_comparison)
	{
        ui->lineEdit_Name->hide();
        ui->comboBox_FeatureGroup->setCurrentText(QString::fromLatin1(comparison->ComparisonGroup.getValue()));
		ui->comboBox_Method->setCurrentText(QString::fromLatin1(comparison->ComparisonMethod.getValue()));
		ui->comboBox_Sim_Candidate1->setCurrentText(QString::fromLatin1(comparison->SimulationCandidate1.getValue()));
		ui->comboBox_Sim_Candidate2->setCurrentText(QString::fromLatin1(comparison->SimulationCandidate2.getValue()));
	    ui->comboBox_PlggedFeature_Candidate1->setCurrentText(QString::fromLatin1(comparison->FeatureTypeCandidate1.getValue()));
		ui->comboBox_PlggedFeature_Candidate2->setCurrentText(QString::fromLatin1(comparison->FeatureTypeCandidate2.getValue()));
		ui->comboBox_Feature_Candidate1->setCurrentText(QString::fromLatin1(comparison->FeatureCandidate1.getValue()));
		ui->comboBox_Feature_Candidate2->setCurrentText(QString::fromLatin1(comparison->FeatureCandidate2.getValue()));
	}

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgSimulationComparison::~DlgSimulationComparison()
{
}

void DlgSimulationComparison::featureGroupCandidateComboBoxIndexChanged(int index)
{
	WindLab::WindLabSimulation* sim1 = static_cast<WindLab::WindLabSimulation*> (WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->comboBox_Sim_Candidate1->currentText().toUtf8().constData()));
	WindLab::WindLabSimulation* sim2 = static_cast<WindLab::WindLabSimulation*> (WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->comboBox_Sim_Candidate2->currentText().toUtf8().constData()));

	if (!sim1 || !sim2) {
		return;
	}

	fillPluggedFeatureComboBox(sim1, ui->comboBox_PlggedFeature_Candidate1);
	fillPluggedFeatureComboBox(sim2, ui->comboBox_PlggedFeature_Candidate2);
    fillFeatureMethodComboBoxCandidate(sim1, ui->comboBox_Method);
	fillFeatureComboBox(sim1, ui->comboBox_Feature_Candidate1, ui->comboBox_FeatureGroup->currentText(), ui->comboBox_PlggedFeature_Candidate1->currentText());
	fillFeatureComboBox(sim2, ui->comboBox_Feature_Candidate2, ui->comboBox_FeatureGroup->currentText(), ui->comboBox_PlggedFeature_Candidate2->currentText());
}

void DlgSimulationComparison::pluggedFeatureCandidate1ComboBoxIndexChanged(int index)
{
	WindLab::WindLabSimulation* sim1 = static_cast<WindLab::WindLabSimulation*> (WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->comboBox_Sim_Candidate1->currentText().toUtf8().constData()));

	if (!sim1) {
		return;
	}

	fillFeatureComboBox(sim1, ui->comboBox_Feature_Candidate1, ui->comboBox_FeatureGroup->currentText(), ui->comboBox_PlggedFeature_Candidate1->currentText());

}
void DlgSimulationComparison::pluggedFeatureCandidate2ComboBoxIndexChanged(int index)
{
	WindLab::WindLabSimulation* sim2 = static_cast<WindLab::WindLabSimulation*> (WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->comboBox_Sim_Candidate2->currentText().toUtf8().constData()));

	if (!sim2) {
		return;
	}

	fillFeatureComboBox(sim2, ui->comboBox_Feature_Candidate2, ui->comboBox_FeatureGroup->currentText(), ui->comboBox_PlggedFeature_Candidate2->currentText());

}

void DlgSimulationComparison::simCandidate1ComboBoxIndexChanged(int index)
{
	WindLab::WindLabSimulation* sim1 = static_cast<WindLab::WindLabSimulation*> (WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->comboBox_Sim_Candidate1->currentText().toUtf8().constData()));

	if (!sim1) {
		return;
	}

	fillFeatureComboBox(sim1, ui->comboBox_Feature_Candidate1, ui->comboBox_FeatureGroup->currentText(), ui->comboBox_PlggedFeature_Candidate1->currentText());

}

void DlgSimulationComparison::simCandidate2ComboBoxIndexChanged(int index)
{
	WindLab::WindLabSimulation* sim2 = static_cast<WindLab::WindLabSimulation*> (WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->comboBox_Sim_Candidate2->currentText().toUtf8().constData()));

	if (!sim2) {
		return;
	}

	fillFeatureComboBox(sim2, ui->comboBox_Feature_Candidate2, ui->comboBox_FeatureGroup->currentText(), ui->comboBox_PlggedFeature_Candidate2->currentText());

}


void DlgSimulationComparison::fillPluggedFeatureComboBox(WindLab::WindLabSimulation* sim, QComboBox* comboBox)
{
	comboBox->clear();
	if (sim)
	{
		QString windLabGroup = ui->comboBox_FeatureGroup->currentText();
		QStringList plugginGroupObject = sim->findAllPluggedWindLabFeatures(windLabGroup);
        comboBox->addItems(plugginGroupObject);

	}
}

void DlgSimulationComparison::fillFeatureMethodComboBoxCandidate(WindLab::WindLabSimulation* sim, QComboBox* comboBox)
{
	comboBox->clear();
	if (sim)
	{
		QString windLabGroup = ui->comboBox_FeatureGroup->currentText();
		QStringList plugginGroupObject = sim->findAllFeatureMethods(windLabGroup);
        comboBox->addItems(plugginGroupObject);

	}
}

void DlgSimulationComparison::fillFeatureComboBox(WindLab::WindLabSimulation* sim, QComboBox* comboBox, QString group, QString type)
{
	comboBox->clear();
	if (sim)
	{

		QStringList plugginGroupObject = sim->findAllWindLabFeaturesByGoupAndType(group, type);
        comboBox->addItems(plugginGroupObject);

	}
}

QDialogButtonBox::StandardButtons DlgSimulationComparison::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

void DlgSimulationComparison::modifyStandardButtons(QDialogButtonBox* box)
{
    QPushButton* btn = box->button(QDialogButtonBox::Ok);
    btn->setText(QApplication::translate("WindLabGui::DlgSimulationComparison", "&Create"));
}

void DlgSimulationComparison::accept()
{
    if (!_comparison)
	{
		auto doc = App::GetApplication().getActiveDocument();
	if(!doc)
	return;
	
	std::string uniqueName = doc->getUniqueObjectName(ui->lineEdit_Name->text().toUtf8().constData());
	doc->openTransaction("Create Simulation Comparison");
    auto obj = doc->addObject("WindLab::WindLabSimulationComparison", uniqueName.c_str());
	doc->commitTransaction();
	WindLab::WindLabSimulationComparison* comparison = static_cast<WindLab::WindLabSimulationComparison*>(obj);
    App::GetApplication().getActiveDocument()->recompute();
 
    comparison->ComparisonGroup.setValue(ui->comboBox_FeatureGroup->currentText().toUtf8().constData());
    comparison->ComparisonMethod.setValue(ui->comboBox_Method->currentText().toUtf8().constData());
    comparison->SimulationCandidate1.setValue(ui->comboBox_Sim_Candidate1->currentText().toUtf8().constData());
	comparison->SimulationCandidate2.setValue(ui->comboBox_Sim_Candidate2->currentText().toUtf8().constData());
	comparison->FeatureTypeCandidate1.setValue(ui->comboBox_PlggedFeature_Candidate1->currentText().toUtf8().constData());
	comparison->FeatureTypeCandidate2.setValue(ui->comboBox_PlggedFeature_Candidate2->currentText().toUtf8().constData());
	comparison->FeatureCandidate1.setValue(ui->comboBox_Feature_Candidate1->currentText().toUtf8().constData());
	comparison->FeatureCandidate2.setValue(ui->comboBox_Feature_Candidate2->currentText().toUtf8().constData());
	}
	else
	{
	_comparison->ComparisonGroup.setValue(ui->comboBox_FeatureGroup->currentText().toUtf8().constData());
    _comparison->ComparisonMethod.setValue(ui->comboBox_Method->currentText().toUtf8().constData());
    _comparison->SimulationCandidate1.setValue(ui->comboBox_Sim_Candidate1->currentText().toUtf8().constData());
	_comparison->SimulationCandidate2.setValue(ui->comboBox_Sim_Candidate2->currentText().toUtf8().constData());
	_comparison->FeatureTypeCandidate1.setValue(ui->comboBox_PlggedFeature_Candidate1->currentText().toUtf8().constData());
	_comparison->FeatureTypeCandidate2.setValue(ui->comboBox_PlggedFeature_Candidate2->currentText().toUtf8().constData());
	_comparison->FeatureCandidate1.setValue(ui->comboBox_Feature_Candidate1->currentText().toUtf8().constData());
	_comparison->FeatureCandidate2.setValue(ui->comboBox_Feature_Candidate2->currentText().toUtf8().constData());
	}
    
  }

void DlgSimulationComparison::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgSimulationComparisonEdit */

DlgSimulationComparisonEdit::DlgSimulationComparisonEdit(WindLab::WindLabSimulationComparison* comparison)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgSimulationComparison(comparison, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgSimulationComparisonEdit::~DlgSimulationComparisonEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgSimulationComparisonEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

void DlgSimulationComparisonEdit::modifyStandardButtons(QDialogButtonBox* box)
{
	if (widget->_comparison)
	{
    QPushButton* btn = box->button(QDialogButtonBox::Ok);
    btn->setText(QApplication::translate("WindLabGui::DlgSimulationComparisonEdit", "&Save"));
	}
	else
	{
    QPushButton* btn = box->button(QDialogButtonBox::Ok);
    btn->setText(QApplication::translate("WindLabGui::DlgSimulationComparisonEdit", "&Create"));
	}
   
}

bool DlgSimulationComparisonEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgSimulationComparisonEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgSimulationComparison.cpp"
