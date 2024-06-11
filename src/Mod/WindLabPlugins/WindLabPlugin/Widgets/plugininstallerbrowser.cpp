#include "plugininstallerbrowser.h"
#include "RPSPluginsIntallerWizard.h"
#include "ui_plugininstallerbrowser.h"
#include "RPSpluginManager.h"
#include "RPSPluginsBrowser.h"
#include "rps/sealab/rpsSeaLabSimulation.h"
#include "RPSWindLabAPI.h"
#include "RPSWindLabpluginAPI.h"
#include "RPSUserDefinedPhenomenonAPI.h"
#include "RPSUserDefinedPhenomenonpluginAPI.h"

#include "globals.h"

#include <QMessageBox>
#include <QListWidgetItem>
#include <QSettings>

PluginInstallerBrowser::PluginInstallerBrowser(QWidget *parent) : QDialog(parent),
																  ui(new Ui::PluginInstallerBrowser)
{
	ui->setupUi(this);

	QStringList tableHeader;
	ui->tableWidget->setColumnCount(8);
	tableHeader << "File"
				<< "Name"
				<< "Type"
				<< "Release Date"
				<< "Authors"
				<< "Version"
				<< "Status"
				<< "Description";

	ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//	ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
//	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);

	fillLocalPluginsList();

	connect(ui->pushButtonInstall, &QPushButton::clicked, this, &PluginInstallerBrowser::install);
	connect(ui->pushButtonUninstall, &QPushButton::clicked, this, &PluginInstallerBrowser::uninstall);
	connect(ui->pushButtonClose, &QPushButton::clicked, this, &PluginInstallerBrowser::close);
	connect(ui->pushButtonRefresh, &QPushButton::clicked, this, &PluginInstallerBrowser::refresh);

}

PluginInstallerBrowser::~PluginInstallerBrowser()
{
	delete ui;
}

void PluginInstallerBrowser::updateButton()
{
	// QListWidgetItem *currentItem = ui->listWidgetLocalPlugin->currentItem();
	// QString ItemText = currentItem->text();
	// std::map<QString, PluginInstance *> map =
	// PluginManager::GetInstance().GetInstalledPluginsNameMap();

	// if (!map.empty())
	// {
	// 	if (map.find(ItemText) != map.end())
	// 	{
	// 		if(map[ItemText]->GetInstallationState())
	// 		{
	// 			ui->pushButtonInstall->setEnabled(false);
	// 			ui->pushButtonUninstall->setEnabled(true);
	// 			ui->pushButtonUpdate->setEnabled(true);
	// 		}
	// 		else
	// 		{
	// 			ui->pushButtonInstall->setEnabled(true);
	// 			ui->pushButtonUninstall->setEnabled(false);
	// 			ui->pushButtonUpdate->setEnabled(false);
	// 		}
	// 	}

	// }
}

void PluginInstallerBrowser::install()
{
	QMessageBox::critical(0, "Error111","Error");

	QSettings settings;

	QString selectedRandomPhenomenon = settings.value("rpsPhenomenon", LabRPS::rpsPhenomenonWindVelocity).toString();

	if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
	{
        if (RPSWindLabAPIInfo::getWindLabAPIVersion() != LabRPS::windLabAPIVersionString())
        {
            QMessageBox::critical(0, "Error",
                                  "Sorry, couldn't install the plugin. Your plugin was developed with a core api whose version is not compatible with the one in the current version of LabRPS.");
            return;
        }

        if (RPSWindLabPluginAPIInfo::getWindLabPluginAPIVersion() != LabRPS::windLabPluginAPIVersionString())
        {
            QMessageBox::critical(0, "Error",
                                  "Sorry, couldn't install the plugin. Your plugin was developed with a plugin api whose version is not compatible with the one in the current version of LabRPS.");
            return;
        }
	}
	else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
	{
	}
	else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
	{
	}
	else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonUserDefined)
	{
        if (RPSUserDefinedPhenomenonAPIInfo::getUserDefinedPhenomenonAPIVersion() != LabRPS::userDefinedPhenomenonAPIVersionString())
        {
            QMessageBox::critical(0, "Error",
                                  "Sorry, couldn't install the plugin. Your plugin was developed with a core api whose version is not compatible with the one in the current version of LabRPS.");
            return;
        }

        if (RPSUserDefinedPhenomenonPluginAPIInfo::getUserDefinedPhenomenonPluginAPIVersion() != LabRPS::userDefinedPhenomenonPluginAPIVersionString())
        {
            QMessageBox::critical(0, "Error",
                                  "Sorry, couldn't install the plugin. Your plugin was developed with a plugin api whose version is not compatible with the one in the current version of LabRPS.");
            return;
        }
    }

	pluginInstallationType = 1; // installation

	int row = ui->tableWidget->currentRow();
	QTableWidgetItem *currentItem = ui->tableWidget->item(row, 0);

	if (NULL != currentItem)
	{
		QString ItemText = currentItem->text();

		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
			if (PluginManager::GetInstance().GetInstalledPluginsNameMap().find(ItemText) != PluginManager::GetInstance().GetInstalledPluginsNameMap().end())
			{
				pluginInstaled = true;
			}
			else
			{
				pluginInstaled = false;
			}
		}
		else
		{
			pluginInstaled = false;
		}

		// initialize the plugin
		CPluginDescription *InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;

        QString info;

        const bool result = PluginManager::GetInstance().InitializePlugin(InstallingPluginFullPath, pluginInstallationType, info);

        if(!result)
        {
            if(!info.isNull())
            {
                QMessageBox::critical(0, "Error",
                                      info);
                return;
            }

            return;
        }

		RPSSimulation *rpsSimu = (RPSSimulation *)this->parent();

		// PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu);
		std::unique_ptr<PlunginIntallationWizard> wizard(new PlunginIntallationWizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu));

		// QObject::connect(wizard, SIGNAL(PlunginIntallationWizard::sendListWidget(QListWidget *)）,this,SLOT(PluginInstallerBrowser::receiveListWidget(QListWidget *))）;
		wizard->exec();

		// installing plugin
	}
}

void PluginInstallerBrowser::uninstall()
{

	pluginInstallationType = 2; // installation

	int row = ui->tableWidget->currentRow();
	QTableWidgetItem *currentItem = ui->tableWidget->item(row, 0);

	if (NULL != currentItem)
	{
		QString ItemText = currentItem->text();

		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
			if (PluginManager::GetInstance().GetInstalledPluginsNameMap().find(ItemText) != PluginManager::GetInstance().GetInstalledPluginsNameMap().end())
			{
				pluginInstaled = true;
			}
			else
			{
				pluginInstaled = false;
				// QMessageBox::critical(0, tr("error"),
				// tr("%1 has not been previously installed.").arg(ItemText));
				// return;
			}
		}
		else
		{
			pluginInstaled = false;
			// QMessageBox::critical(0, tr("error"),
			// 	tr("%1 has not been previously installed.").arg(ItemText));
			// 	return;
		}

		// initialize the plugin
		CPluginDescription *InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;

		RPSSimulation *rpsSimu = (RPSSimulation *)this->parent();

		PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu);

		wizard.exec();

		// installing plugin
	}
}

void PluginInstallerBrowser::modify()
{

}

void PluginInstallerBrowser::close()
{
	this->reject();
}

void PluginInstallerBrowser::refresh()
{
	fillLocalPluginsList();
}

void PluginInstallerBrowser::fillLocalPluginsList()
{

	// get the path the plugin folder
	QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();

	// search and find all available plugin and save their descriptions
	PluginManager::GetInstance().SearchForAllPlugins(strPath);

	int i = 0;

	// clear all plugins in list control
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);

	int row = PluginManager::GetInstance().GetPluginDescriptionsMap().size();
	int col = 8;
	ui->tableWidget->setRowCount(row);
	ui->tableWidget->setColumnCount(col);

	CPluginDescription *Descript;

	std::map<QString, CPluginDescription *>::iterator it;
	for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
	{
		Descript = new CPluginDescription();
		Descript = it->second;

		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Descript->fileName));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Descript->name));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Descript->type));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(Descript->releaseDate));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Descript->authors));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Descript->version));
		ui->tableWidget->setItem(i, 7, new QTableWidgetItem(Descript->description));

        RPSSimulation *rpsSimu = (RPSSimulation *)this->parent();

        if (rpsSimu->rpsWindLabSimulator->isThisPluginInstalled(Descript->name))
        {
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem("Installed"));
        }
        else
        {
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem("Not installed"));
        }

		
		i++;
	}
}

void PluginInstallerBrowser::fillOnlinePluginsList()
{
}
