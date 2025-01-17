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

#include "PreCompiled.h"
#ifndef _PreComp_
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <QMessageBox>
#include <QSignalMapper>
#endif

#include <App/Application.h>
#include <App/Document.h>
#include <Base/Tools.h>
#include <Base/UnitsApi.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/Command.h>
#include <Gui/TaskView/TaskView.h>

#include "DlgWindLabFeaturesCreation.h"
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>
#include <App/Simulation.h>
#include <Gui/MainWindow.h>
#include "ui_DlgWindLabFeaturesCreation.h"
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <App/AutoTransaction.h>
#include <Mod/WindLabAPI/App/WindLabFeatureDescription.h>

using namespace WindLabGui;
using namespace Gui;


/* TRANSLATOR WindLabGui::DlgWindLabFeaturesCreation */

DlgWindLabFeaturesCreation::DlgWindLabFeaturesCreation(QWidget* parent, WindLabAPI::WindLabFeature* feature)
    : QWidget(parent), ui(new Ui_DlgWindLabFeaturesCreation)
{
	ui->setupUi(this);

	connect(ui->featureTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(featureTypeComboBoxIndexChanged(int)));

	ui->nameLineEdit->setText(QString::fromLatin1("Feature"));

	std::list<std::string> simList = WindLabGui::WindLabSimulationObserver::instance()->simulations();

	for (std::list<std::string>::iterator it = simList.begin(); it != simList.end(); ++it) {
        auto sim = App::GetApplication().getActiveDocument()->getObject(it->c_str());
		if (sim)
		{
			QString itemName = QString::fromUtf8(it->c_str());
            ui->SimulationComboBox->addItem(itemName);
		}
	}

	QString simeName = ui->SimulationComboBox->currentText();
	WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(simeName.toUtf8().constData()));

	if (!sim) {
		QMessageBox::warning(this, tr("Feature Creation"), tr("No active simulation"));
		return;
	}

	ui->SimulationComboBox->setCurrentText(QString::fromUtf8(sim->Label.getValue()));

	fillFeatureComboBox(sim, ui->featureComboBox, ui->featureTypeComboBox->currentIndex());

	if (feature)//we are editting. Disable editting
	{
		ui->nameLineEdit->setText(QString::fromUtf8(feature->Label.getValue()));
		ui->nameLineEdit->setEnabled(FALSE);
		ui->featureTypeComboBox->setEnabled(FALSE);
		ui->featureComboBox->setEnabled(FALSE);
		ui->SimulationComboBox->setEnabled(FALSE);

	}

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgWindLabFeaturesCreation::~DlgWindLabFeaturesCreation()
{
}

void DlgWindLabFeaturesCreation::fillFeatureComboBox(WindLab::WindLabSimulation* sim, QComboBox* comboBox, int selectedFeatureType)
{
	comboBox->clear();
	if (sim)
	{
        QString featureGroup = ui->featureTypeComboBox->currentText();
        QStringList plugginGroupObject = sim->findAllPluggedWindLabFeatures(featureGroup);
		ui->featureComboBox->addItems(plugginGroupObject);
	}
}


void DlgWindLabFeaturesCreation::createDlgWindLabFeature(const QString& simulation)
{
    auto docApp = App::GetApplication().getActiveDocument();
    if (!docApp)
        return;

    docApp->openTransaction("Create WindLab Feature");

	//get the simulation for which this feature will created
	WindLab::WindLabSimulation* simParent = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->SimulationComboBox->currentText().toUtf8().constData()));
	if (!simParent)
		return;
	//get all WindLab feature type
	std::vector<Base::Type> types = simParent->getRPSTypesOfPluggableFeatures();

	//get the type of the creating feature
	Base::Type type = types[ui->featureTypeComboBox->currentIndex()];
    int aa = ui->featureTypeComboBox->currentIndex();
	//create the feature
	WindLabAPI::WindLabFeature* newFeature = simParent->createFeature(type, ui->featureComboBox->currentText().toUtf8().constData(), ui->nameLineEdit->text().toUtf8().constData());

	if (!newFeature)
		return;

	//set the feature properties
	auto featureProperties = simParent->GetWindLabPluggedWindLabFeatureDescription(ui->featureTypeComboBox->currentText(), ui->featureComboBox->currentText());
	//App::PropertyBool IsActive;
	newFeature->FeatureGroup.setValue(ui->featureTypeComboBox->currentText().toUtf8().constData());
    newFeature->FeatureType.setValue(ui->featureComboBox->currentText().toUtf8().constData());
    newFeature->Author.setValue(featureProperties->Author.getValue());
    newFeature->PublicationTopic.setValue(featureProperties->PublicationTitle.getValue());
    newFeature->PublicationDate.setValue(featureProperties->PublicationDate.getValue());
    newFeature->LinkToPublication.setValue(featureProperties->PublicationLink.getValue());
    newFeature->PublicationAuthor.setValue(featureProperties->PublicationAuthor.getValue());
    newFeature->Version.setValue(featureProperties->Version.getValue());
    newFeature->IsStationary.setValue(featureProperties->Stationarity.getValue());
    newFeature->PluginName.setValue(featureProperties->PluginName.getValue());
    newFeature->PluginVersion.setValue(featureProperties->PluginVersion.getValue());
    newFeature->APIVersion.setValue(featureProperties->APIVersion.getValue());
    newFeature->ReleaseDate.setValue(featureProperties->ReleaseDate.getValue());
	newFeature->Simulation.setValue(simParent->Label.getValue());
    newFeature->Description.setValue(featureProperties->Description.getValue());
    newFeature->LabrpsVersion.setValue(featureProperties->LabRPSVersion.getValue());
    newFeature->Path.setValue(featureProperties->Path.getValue());

	//convert the parent simulation to a group object
	App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(static_cast<App::DocumentObject*>(simParent));

    newFeature->recomputeFeature();

	//add the created feature under its simulation
	group->addObject(newFeature);

	//show change in the property editor
    simParent->setEnums(type);

	Gui::Document* doc = Gui::Application::Instance->activeDocument();

    docApp->commitTransaction();

	App::AutoTransaction trans("Recompute");
    Command::doCommand(Command::Doc, "App.getDocument(\"%s\").recompute()", doc->getDocument()->getName());
	
}

void DlgWindLabFeaturesCreation::featureTypeComboBoxIndexChanged(int index)
{
	WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(ui->SimulationComboBox->currentText().toUtf8().constData()));
	if (!sim) {
		QMessageBox::warning(this, tr("Feature Creation"), tr("No active simulation"));
		return;
	}

	ui->SimulationComboBox->setCurrentText(QString::fromUtf8(sim->Label.getValue()));
	fillFeatureComboBox(sim, ui->featureComboBox, ui->featureTypeComboBox->currentIndex());
}

void DlgWindLabFeaturesCreation::accept(const QString& placement)
{

}

void DlgWindLabFeaturesCreation::reject()
{

}



/* TRANSLATOR PartGui::TaskWindLabFeatures */

TaskWindLabFeatures::TaskWindLabFeatures()
{
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgWindLabFeaturesCreation();
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
}

TaskWindLabFeatures::~TaskWindLabFeatures()
{
	
}

QDialogButtonBox::StandardButtons TaskWindLabFeatures::getStandardButtons() const
{
	return QDialogButtonBox::Close |
		QDialogButtonBox::Ok;
}

void TaskWindLabFeatures::modifyStandardButtons(QDialogButtonBox* box)
{
	QPushButton* btn = box->button(QDialogButtonBox::Ok);
	btn->setText(QApplication::translate("WindLabGui::DlgWindLabFeaturesCreation", "&Create"));
}

bool TaskWindLabFeatures::accept()
{
	widget->createDlgWindLabFeature(QString::fromLatin1(""));
	return true;
}

bool TaskWindLabFeatures::reject()
{
	return true;
}

// ----------------------------------------------

/* TRANSLATOR PartGui::TaskWindLabFeaturesEdit */

TaskWindLabFeaturesEdit::TaskWindLabFeaturesEdit(WindLabAPI::WindLabFeature* feature)
{
	// create and show dialog for the WindLabFeatures
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgWindLabFeaturesCreation(nullptr, feature);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
}

TaskWindLabFeaturesEdit::~TaskWindLabFeaturesEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons TaskWindLabFeaturesEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel /*|
		QDialogButtonBox::Ok*/;
}

bool TaskWindLabFeaturesEdit::accept()
{
	//cannot modify featues
	return true;
}

bool TaskWindLabFeaturesEdit::reject()
{
	widget->reject();
	return true;
}

#include "moc_DlgWindLabFeaturesCreation.cpp"
