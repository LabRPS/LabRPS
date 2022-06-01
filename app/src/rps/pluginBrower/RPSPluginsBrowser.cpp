
#include <QtWidgets>
#include <QAbstractButton>

#include "rps/RPSpluginManager.h"
#include "RPSPluginsBrowser.h"
#include "RPSSeaLabAPI.h"


PlunginIntallationWizard::PlunginIntallationWizard(int installationType, QString installingPluginName, QString installingPluginFullPath, QWidget *parent)
    : QWizard(parent)
{
    addPage(new IntroPage(installationType, installingPluginName));
    addPage(new TaskSelectionPage(installationType, installingPluginName));
    addPage(new ObjectSelectionPage(installationType, installingPluginName, installingPluginFullPath));
    // addPage(new ProgressPage(installationType, installingPluginName));
    addPage(new ConclusionPage(installationType, installingPluginName));


    setPixmap(QWizard::BannerPixmap, QPixmap(":/icons/images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/icons/images/background.png"));

    setWindowTitle(tr("Plugin Installer"));

}

void PlunginIntallationWizard::accept()
{
	
    QDialog::accept();
}




IntroPage::IntroPage(int installationType, QString installingPluginName, QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Welcome to RPS Plugin Installer"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/icons/images/watermark1.png"));

    label = new QLabel(tr("This wizard will guide you through the installation "
                          "of plugins or objecs. Please, click next to continue."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

TaskSelectionPage::TaskSelectionPage(int installationType, QString installingPluginName, QWidget *parent)
    : QWizardPage(parent)
{

    setTitle(tr("Choose a tak"));
    setSubTitle(tr("From here you can choose to install or uninstal "
                   " or modify your plugins."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/icons/images/logo1.png"));


    groupBox = new QGroupBox(tr("&Tasks"));


    intallRadioButton = new QRadioButton(tr("&Intall"));
    unInstallRadioButton = new QRadioButton(tr("&Uninstall"));
    modificationRadioButton = new QRadioButton(tr("&Modigy"));

    if(1 == installationType)
    {
     intallRadioButton->setChecked(true);

    }
    else if(2 == installationType)
    {
     unInstallRadioButton->setChecked(true);
    }
    else if(3 == installationType)
    {
    modificationRadioButton->setChecked(true);

    }

    taskButtonGroup = new QButtonGroup();
    taskButtonGroup->addButton(intallRadioButton);
	taskButtonGroup->addButton(unInstallRadioButton);
    taskButtonGroup->addButton(modificationRadioButton);

    
    registerField("installOPlugin", intallRadioButton);
    registerField("uninstallPlugin", unInstallRadioButton);
    registerField("modifyPlugin", modificationRadioButton);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    
	groupBoxLayout->addWidget(intallRadioButton);
    groupBoxLayout->addWidget(unInstallRadioButton);
    groupBoxLayout->addWidget(modificationRadioButton);

    groupBox->setLayout(groupBoxLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(groupBox, 3, 0, 1, 2);

    setLayout(layout);

}

///////////////object selection starts//////////////

ObjectSelectionPage::ObjectSelectionPage(int installationType, QString installingPluginName, QString installingPluginFullPath, QWidget *parent)
    : QWizardPage(parent)
{
    InstallingPluginName = installingPluginName;
    InstallingPluginFullPath = installingPluginFullPath;
    InstallationType = installationType;

    createListWidget();
    createOtherWidgets();
    createLayout();
    createConnections();
}

void ObjectSelectionPage::createListWidget(){
    objectList = new QListWidget;
    QStringList lstObject;
    
    if(1 == InstallationType)//install
    {
        GetToBeInstalledObjectsList(lstObject, InstallingPluginName);
    }
    else if(2 == InstallationType)//uninstall
    {
        GetToBeUninstalledObjectsList(lstObject, InstallingPluginName);
    }
    else if(3 == InstallationType)//modify
    {
        GetToBeInstalledObjectsList(lstObject, InstallingPluginName);
    }
   
    objectList->addItems(lstObject);

    QListWidgetItem* item = 0;
    QString itemText;
    for(int i = 0; i < objectList->count(); ++i){
        item = objectList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        itemText = item->text();
        if(IsObjectInstalled(itemText))
        {
            item->setCheckState(Qt::Checked);
        }
        else
        {
            item->setCheckState(Qt::Unchecked);
        }
    }

}

void ObjectSelectionPage::createOtherWidgets(){
    
    viewBox = new QGroupBox(tr("Available Ojects"));
	selectAllButton = new QPushButton(tr("&Select All"));
    selectNoneButton = new QPushButton(tr("&Select None"));
    resetSelectionButton = new QPushButton(tr("&Reset"));

}

void ObjectSelectionPage::createLayout(){
    QVBoxLayout* viewLayout = new QVBoxLayout;
    viewLayout->addWidget(objectList);
    viewBox->setLayout(viewLayout);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(selectAllButton);
    horizontalLayout->addWidget(selectNoneButton);
    horizontalLayout->addWidget(resetSelectionButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(viewBox);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
}

void ObjectSelectionPage::createConnections(){
    QObject::connect(objectList, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(highlightChecked(QListWidgetItem*)));
    QObject::connect(selectAllButton, SIGNAL(clicked()), this, SLOT(selectAll()));
    QObject::connect(selectNoneButton, SIGNAL(clicked()), this, SLOT(selectNone()));
	QObject::connect(resetSelectionButton, SIGNAL(clicked()), this, SLOT(resetSelection()));
    
}

void ObjectSelectionPage::highlightChecked(QListWidgetItem *item){
    if(item->checkState() == Qt::Checked)
        item->setBackgroundColor(QColor("#ffffb2"));
    else
        item->setBackgroundColor(QColor("#ffffff"));
}

void ObjectSelectionPage::selectAll(){

int cnt = objectList->count();
    for (int i=0;i<cnt;i++) {
        QListWidgetItem *item = objectList->item(i);
        item->setCheckState(Qt::Checked);
    }
}

void ObjectSelectionPage::selectNone(){
	int cnt = objectList->count();
    for (int i=0;i<cnt;i++) {
        QListWidgetItem *item = objectList->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

void ObjectSelectionPage::resetSelection(){
    
}

  bool ObjectSelectionPage::validatePage()
 {
     QStringList checkedList;
     QStringList unCheckedList;

    int cnt = objectList->count();
    for (int i=0;i<cnt;i++) {
        QListWidgetItem *item = objectList->item(i);
		if(Qt::Checked == item->checkState())
		{
            // this object is to be installed
		}
        else if(Qt::Unchecked == item->checkState())
		{
            
            if(1 == InstallationType)
            {
                //this object shoulb be remove from the installing objects map
               UpdateToBeInstalledObjectsMap(item->text());

            }
            else if(2 == InstallationType)
            {
               //this object shoulb be remove from the list
                UpdateToBeUninstalledObjectsMap(item->text(), InstallingPluginName);

            }
            else if(3 == InstallationType)
            {
                //this object shoulb be remove from the list
                UpdateToBeInstalledObjectsMap(item->text());
            }
		}
    }

    if(1 == InstallationType)
    {
         // now the install the selected objects
    PluginManager::GetInstance().InstallPlugin(InstallingPluginFullPath);

    }
    else if(2 == InstallationType)
    {
    // now the install the selected objects
    PluginManager::GetInstance().UnInstallPlugin(InstallingPluginFullPath);

    }
    else if(3 == InstallationType)
    {
                // now the install the selected objects
    PluginManager::GetInstance().InstallPlugin(InstallingPluginFullPath);

    }

   
    return QWizardPage::validatePage();
 }
 

bool ObjectSelectionPage::GetObjects(std::map<const QString, QString>& map, QStringList& lstObject, QString pluginName)
{
		if (!map.empty())
		{
			// Iterate though the map and show all the registed objects
			for (auto it = map.begin(); it != map.end(); ++it)
			{
				if (!it->first.isEmpty())
				{
					if (it->second == pluginName)
					{
						lstObject.append(it->first);
					}
				}
			}

		}
        else
        {
            return false;
        }

		return true;
}

bool ObjectSelectionPage::GetToBeInstalledObjectsList(QStringList& lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));

	try
	{
		GetObjects(CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
	    GetObjects(CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);

	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}


bool ObjectSelectionPage::GetToBeUninstalledObjectsList(QStringList& lstObject, QString pluginName)
{
	lstObject.removeAll(QString(""));

	try
	{
		GetObjects(CrpsSeLSimulationMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLXSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLCorrelationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
	    GetObjects(CrpsSeLDirectionalSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
		GetObjects(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectAndPluginMap(), lstObject, pluginName);

	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}


bool  ObjectSelectionPage::IsObjectInstalled(QString& object)
{
	if (IsThisObjectInstalled(CrpsSeLSimulationMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLCoherenceFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLLocationDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLMeanFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLXSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLRandomnessFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLCorrelationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLModulationFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLDirectionalSpectrumFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLDirectionDistributionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	if (IsThisObjectInstalled(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectDescriptionMap(), object))
	{
		return true;
	}
	return false;
}

bool ObjectSelectionPage::UpdateObjectsMap(std::map<const QString, QString>& map, const QString& lstObject)
{
	if (!map.empty())
	{
		if (map.find(lstObject) != map.end())
		{
			map.erase(lstObject);
		}
	}

	return true;
}

bool ObjectSelectionPage::UpdateObjectToSkipMap(std::map<const QString, QString>& map, const QString name, const QString pluginName)
{
    map[name] = pluginName;
	return true;
}

bool ObjectSelectionPage::UpdateToBeInstalledObjectsMap(const QString& lstObject)
{
	try
	{
        UpdateObjectsMap(CrpsSeLSimulationMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
	    UpdateObjectsMap(CrpsSeLDirectionalSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLDirectionDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
		UpdateObjectsMap(CrpsSeLDirectionSpreadingFunctionFactory::GetTobeInstalledObjectsMap(), lstObject);

	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}

bool ObjectSelectionPage::UpdateToBeUninstalledObjectsMap(const QString name, const QString pluginName)
{
	try
	{
        UpdateObjectToSkipMap(CrpsSeLSimulationMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLXSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLCorrelationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
	    UpdateObjectToSkipMap(CrpsSeLDirectionalSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLDirectionDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
		UpdateObjectToSkipMap(CrpsSeLDirectionSpreadingFunctionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

	}
	catch (const std::exception& e)
	{
		return false;
	}

	return true;
}


bool  ObjectSelectionPage::IsThisObjectInstalled(std::map<const QString, QString>& map, QString& object)
{
	if (!map.empty())
	{
		if (map.find(object) != map.end())
		{
			return true;
		}

	}

	return false;
}

///////////objects selection end////////////////
ProgressPage::ProgressPage(int installationType, QString installingPluginName, QWidget *parent)
    : QWizardPage(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();

    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);

    layout->addWidget(progressBar);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ProgressPage::updateProgress);
    timer->start(1000);

    setWindowTitle(tr("Timer"));
    resize(200, 200);
}

void ProgressPage::updateProgress()
{
    progressBar->setValue(progressBar->value()+1);
}


ConclusionPage::ConclusionPage(int installationType, QString installingPluginName, QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Intallation Completed"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/icons/images/watermark2.png"));

    label = new QLabel;
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 to allow LabRPS to %1 your selected task.")
                   .arg(finishText));
}
