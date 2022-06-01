#include "plugininstallerbrowser.h"
#include "RPSPluginsBrowser.h"

#include "ui_plugininstallerbrowser.h"

#include "rps/RPSpluginManager.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include "RPSPluginsBrowser.h"




PluginInstallerBrowser::PluginInstallerBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginInstallerBrowser)
{
    ui->setupUi(this);
    fillLocalPluginsList();
	connect(ui->pushButtonInstall, &QPushButton::clicked, this, &PluginInstallerBrowser::install);
	connect(ui->pushButtonUninstall, &QPushButton::clicked, this, &PluginInstallerBrowser::uninstall);
	connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &PluginInstallerBrowser::modify);
	connect(ui->pushButtonClose, &QPushButton::clicked, this, &PluginInstallerBrowser::close);
	connect(ui->listWidgetLocalPlugin, &QListWidget::itemSelectionChanged, this, &PluginInstallerBrowser::updateButton);


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

  void PluginInstallerBrowser::install(){
	  pluginInstallationType = 1; //installation
	  QListWidgetItem *currentItem = ui->listWidgetLocalPlugin->currentItem();
	  if(NULL != currentItem){
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
		CPluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->m_strFullPath;

		PluginManager::GetInstance().InitializePlugin(InstallingPluginFullPath, pluginInstallationType);

        PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath);
       
	    // QObject::connect(wizard, SIGNAL(PlunginIntallationWizard::sendListWidget(QListWidget *)）,this,SLOT(PluginInstallerBrowser::receiveListWidget(QListWidget *))）;
 	    wizard.exec();

	   // installing plugin
	

	  }

  }

  void PluginInstallerBrowser::uninstall(){

	  pluginInstallationType = 2; //installation
	  QListWidgetItem *currentItem = ui->listWidgetLocalPlugin->currentItem();
	  if(NULL != currentItem){
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
				QMessageBox::critical(0, tr("error"), 
				tr("%1 has not been previously installed.").arg(ItemText));
				return;
			}

		}
		else
		{
			pluginInstaled = false;
			QMessageBox::critical(0, tr("error"), 
				tr("%1 has not been previously installed.").arg(ItemText));
				return;
		}

		// initialize the plugin
		CPluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->m_strFullPath;

        PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath);
       
 	    wizard.exec();

	   // installing plugin
	

	  }

  }

  void PluginInstallerBrowser::modify(){

	 pluginInstallationType = 3; //installation
	  QListWidgetItem *currentItem = ui->listWidgetLocalPlugin->currentItem();
	  if(NULL != currentItem){
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
		CPluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->m_strFullPath;

		PluginManager::GetInstance().InitializePlugin(InstallingPluginFullPath, pluginInstallationType);

        PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath);
       
	    // QObject::connect(wizard, SIGNAL(PlunginIntallationWizard::sendListWidget(QListWidget *)）,this,SLOT(PluginInstallerBrowser::receiveListWidget(QListWidget *))）;
 	    wizard.exec();

	   // installing plugin
	

	  }

  }

  void PluginInstallerBrowser::close(){
	  this->reject();
  }

  void PluginInstallerBrowser::configure(){

  }

  void PluginInstallerBrowser::fillLocalPluginsList(){
  
  // get the path the plugin folder
  QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();
  
  // search and find all available plugin and save their descriptions
  PluginManager::GetInstance().SearchForAllPlugins(strPath);

	std::map<QString, CPluginDescription *>::iterator it;
	for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
	{
		ui->listWidgetLocalPlugin->addItem(it->second->m_strFileName);      
    }
  
  }

  void PluginInstallerBrowser::fillOnlinePluginsList(){

  }

//   void PluginInstallerBrowser::receiveListWidget(QListWidget *list){
//    QMessageBox::warning(
//         0, "ooo",
//         "can receive");
//   }