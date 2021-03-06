#include "plugininstallerbrowser.h"
#include "RPSPluginsBrowser.h"

#include "ui_plugininstallerbrowser.h"

#include "rps/RPSpluginManager.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include "RPSPluginsBrowser.h"
#include "rps/sealab/rpsSeaLabSimulation.h"


PluginInstallerBrowser::PluginInstallerBrowser(QWidget *parent) :
    QDialog(parent),
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
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui->tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
	
	fillLocalPluginsList();
	
	connect(ui->pushButtonInstall, &QPushButton::clicked, this, &PluginInstallerBrowser::install);
	connect(ui->pushButtonUninstall, &QPushButton::clicked, this, &PluginInstallerBrowser::uninstall);
	connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &PluginInstallerBrowser::modify);
	connect(ui->pushButtonClose, &QPushButton::clicked, this, &PluginInstallerBrowser::close);

    //__git.downloadFile("https://raw.githubusercontent.com/LabRPS/LabRPS-plugins/master/.gitmodules", "C:/Users/KOFFI/Desktop/", "hehehe", 4000);
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
	  
	  int row = ui->tableWidget->currentRow();
	  QTableWidgetItem * currentItem =	ui->tableWidget->item(row, 0);
	  
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

        RPSSimulation *rpsSimu = (RPSSimulation *)this->parent();
        
		//PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu);
       	std::unique_ptr<PlunginIntallationWizard> wizard(new PlunginIntallationWizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu));

	    // QObject::connect(wizard, SIGNAL(PlunginIntallationWizard::sendListWidget(QListWidget *)???,this,SLOT(PluginInstallerBrowser::receiveListWidget(QListWidget *))???;
 	    wizard->exec();

	   // installing plugin
	

	  }

  }

  void PluginInstallerBrowser::uninstall(){

	  pluginInstallationType = 2; //installation

	  int row = ui->tableWidget->currentRow();
	  QTableWidgetItem * currentItem =	ui->tableWidget->item(row, 0);

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
		CPluginDescription* InstallingPluginDescription = PluginManager::GetInstance().GetPluginDescriptionsMap()[ItemText];
		QString InstallingPluginFullPath = InstallingPluginDescription->m_strFullPath;
       
	    RPSSimulation *rpsSimu = (RPSSimulation *)this->parent();

        PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu);
       
 	    wizard.exec();

	   // installing plugin
	

	  }

  }

  void PluginInstallerBrowser::modify(){

	 pluginInstallationType = 3; //installation

	 int row = ui->tableWidget->currentRow();
	 QTableWidgetItem * currentItem =	ui->tableWidget->item(row, 0);

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

	    RPSSimulation *rpsSimu = (RPSSimulation *)this->parent();

        PlunginIntallationWizard wizard(pluginInstallationType, ItemText, InstallingPluginFullPath, rpsSimu);
       
	    // QObject::connect(wizard, SIGNAL(PlunginIntallationWizard::sendListWidget(QListWidget *)???,this,SLOT(PluginInstallerBrowser::receiveListWidget(QListWidget *))???;
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

		  ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Descript->m_strFileName));
		  ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Descript->m_strName));
		  ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Descript->m_strType));
		  ui->tableWidget->setItem(i, 3, new QTableWidgetItem(Descript->m_strReleaseDate));
		  ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Descript->m_strAuthors));
		  ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Descript->m_strVersion));
		  ui->tableWidget->setItem(i, 7, new QTableWidgetItem(Descript->m_strDescription));

		  if (!PluginManager::GetInstance().GetInstalledPluginsMap().empty())
		  {
			  if (PluginManager::GetInstance().GetInstalledPluginsMap().find(Descript->m_strFullPath) != PluginManager::GetInstance().GetInstalledPluginsMap().end())
			  {
				  ui->tableWidget->setItem(i, 6, new QTableWidgetItem("Installed"));
			  }
			  else
			  {
				  ui->tableWidget->setItem(i, 6, new QTableWidgetItem("Not installed"));
			  }
		  }
		  else
		  {
			  ui->tableWidget->setItem(i, 6, new QTableWidgetItem("Not installed"));
		  }

		  i++;
	  }
  }

  void PluginInstallerBrowser::fillOnlinePluginsList(){

  }
