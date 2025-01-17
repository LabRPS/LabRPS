#include "PreCompiled.h"
#include "plugininstallerbrowser.h"
#include "RPSPluginsInstallerWizard.h"
#include "ui_plugininstallerbrowser.h"
#include <App/RPSpluginManager.h>
//#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
//#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include "RPSGlobals.h"
#include "MainWindow.h"
#include "Application.h"

#include <QMessageBox>
#include <QListWidgetItem>
#include <QSettings>

#include "Application.h"
#include "Command.h"
#include <Workbench.h>
#include <WorkbenchManager.h>

using namespace Gui;
using namespace App;

PluginInstallerBrowser::PluginInstallerBrowser(const QString& workbenchName, QWidget *parent) : 
	                                                             _workbenchName(workbenchName),
	                                                              QDialog(parent),
																  ui(new Ui::PluginInstallerBrowser)
{
	ui->setupUi(this);

	QStringList tableHeader;
	ui->tableWidget->setColumnCount(8);
	tableHeader << QString::fromLatin1("Name")
				<< QString::fromLatin1("Location")
				<< QString::fromLatin1("Phenomenon")
				<< QString::fromLatin1("Release Date")
				<< QString::fromLatin1("Authors")
				<< QString::fromLatin1("Version")
				<< QString::fromLatin1("Status")
				<< QString::fromLatin1("Description");

	ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//	ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
//	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);

	fillLocalPluginsList(_workbenchName);

	connect(ui->pushButtonInstall, &QPushButton::clicked, this, &PluginInstallerBrowser::install);
	connect(ui->pushButtonUninstall, &QPushButton::clicked, this, &PluginInstallerBrowser::uninstall);
	connect(ui->pushButtonClose, &QPushButton::clicked, this, &PluginInstallerBrowser::close);
	connect(ui->pushButtonHelp, &QPushButton::clicked, this, &PluginInstallerBrowser::help);

}

PluginInstallerBrowser::~PluginInstallerBrowser()
{
	delete ui;
}

void PluginInstallerBrowser::updateButton()
{

}

void PluginInstallerBrowser::install()
{
	pluginInstallationType = 1; // installation

	int row = ui->tableWidget->currentRow();
	QTableWidgetItem *currentItem = ui->tableWidget->item(row, 0);

	if (NULL != currentItem)
	{
		QString ItemText = currentItem->text();

		if (!App::PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
			if (App::PluginManager::GetInstance().GetInstalledPluginsNameMap().find(ItemText) != App::PluginManager::GetInstance().GetInstalledPluginsNameMap().end())
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
		auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;

        QString info;

        //const bool result = App::PluginManager::GetInstance().InitializePlugin(InstallingPluginFullPath, pluginInstallationType, info);
		const bool result = Gui::Application::Instance->InitializePlugin(InstallingPluginFullPath, pluginInstallationType, info);

        if(!result)
        {
            if(!info.isNull())
            {
                QMessageBox::critical(0, QString::fromLatin1("Error"),
                                      info);
                return;
            }

            return;
        }

		// PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu);
		std::unique_ptr<PlunginIntallationWizard> wizard(new PlunginIntallationWizard(pluginInstallationType, ItemText, InstallingPluginFullPath, Gui::getMainWindow()));

		// QObject::connect(wizard, SIGNAL(PlunginIntallationWizard::sendListWidget(QListWidget *)）,this,SLOT(PluginInstallerBrowser::receiveListWidget(QListWidget *))）;
		wizard->exec();

		//delete InstallingPluginDescription;
		//InstallingPluginDescription = nullptr;

		//ClassWizard wizard;
  //      wizard.setWizardStyle(QWizard::ClassicStyle);
  //      wizard.exec();
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

		if (!App::PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
			if (App::PluginManager::GetInstance().GetInstalledPluginsNameMap().find(ItemText) != App::PluginManager::GetInstance().GetInstalledPluginsNameMap().end())
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
		PluginDescription *InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;

		PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, Gui::getMainWindow());

		wizard.exec();

	}
}

void PluginInstallerBrowser::modify()
{

}

void PluginInstallerBrowser::close()
{
	this->reject();
}

void PluginInstallerBrowser::help()
{
	int row = ui->tableWidget->currentRow();
	QTableWidgetItem *currentItem = ui->tableWidget->item(row, 0);

	if (NULL != currentItem)
	{
		QString ItemText = currentItem->text();
		auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString wikiLink = InstallingPluginDescription->wikiLink;
		Gui::Command::doCommand(Gui::Command::Doc, "import WebGui");
        Gui::Command::doCommand(Gui::Command::Doc, "WebGui.openBrowser(\"%s\")", wikiLink.toStdString().c_str());

    }
}

void PluginInstallerBrowser::fillLocalPluginsList(const QString& workbenchName)
{
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(workbenchName);
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(workbenchName);

	 Workbench* Wb = WorkbenchManager::instance()->active();
    if (!Wb)
        return;
    QString phenomenon = Wb->getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

	// search and find all available plugin and save their descriptions


	int i = 0;

	// clear all plugins in list control
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);

	int row = App::PluginManager::GetInstance().GetPluginDescriptionsMap().size();
	int col = 8;
	ui->tableWidget->setRowCount(row);
	ui->tableWidget->setColumnCount(col);

	PluginDescription *Descript;

	std::map<QString, PluginDescription *>::iterator it;
	for (it = App::PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != App::PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
	{
		Descript = new PluginDescription();
		Descript = it->second;

		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Descript->name));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Descript->source));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Descript->type));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(Descript->releaseDate));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Descript->authors));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Descript->version));
		ui->tableWidget->setItem(i, 7, new QTableWidgetItem(Descript->description));

        if (Gui::Application::Instance->isThisPluginInstalled(Descript->name))
        {
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromLatin1("Installed")));
        }
        else
        {
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromLatin1("Not installed")));
        }

		
		i++;
	}
}

void PluginInstallerBrowser::fillOnlinePluginsList()
{
}
