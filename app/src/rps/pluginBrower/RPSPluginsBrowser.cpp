
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
    addPage(new ObjectSelectionPage(installationType, installingPluginName, installingPluginFullPath, parent));
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

    if (1 == installationType)
    {
        intallRadioButton->setChecked(true);
    }
    else if (2 == installationType)
    {
        unInstallRadioButton->setChecked(true);
    }
    else if (3 == installationType)
    {
        modificationRadioButton->setChecked(true);
    }

    taskButtonGroup = new QButtonGroup();
    taskButtonGroup->addButton(intallRadioButton);
    taskButtonGroup->addButton(unInstallRadioButton);
    taskButtonGroup->addButton(modificationRadioButton);

    registerField("installPlugin", intallRadioButton);
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

    rpsSimulator = (RPSSimulation *)parent;

    createListWidget(rpsSimulator);
    createOtherWidgets();
    createLayout();
    createConnections();
}

ObjectSelectionPage::~ObjectSelectionPage()
{
}

void ObjectSelectionPage::createListWidget(RPSSimulation *rpsSimu)
{
    objectList = new QListWidget;
    QStringList lstObject;

    if (1 == InstallationType) // install
    {
        rpsSimu->GetToBeInstalledObjectsList(lstObject, InstallingPluginName);
    }
    else if (2 == InstallationType) // uninstall
    {
        rpsSimu->GetToBeUninstalledObjectsList(lstObject, InstallingPluginName);
    }
    else if (3 == InstallationType) // modify
    {
        rpsSimu->GetToBeInstalledObjectsList(lstObject, InstallingPluginName);
    }

    objectList->addItems(lstObject);

    QListWidgetItem *item = 0;
    QString itemText;
    for (int i = 0; i < objectList->count(); ++i)
    {
        item = objectList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        itemText = item->text();
        if (rpsSimu->IsObjectInstalled(itemText))
        {
            item->setCheckState(Qt::Checked);
        }
        else
        {
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void ObjectSelectionPage::createOtherWidgets()
{

    viewBox = new QGroupBox(tr("Available Ojects"));
    selectAllButton = new QPushButton(tr("&Select All"));
    selectNoneButton = new QPushButton(tr("&Select None"));
    resetSelectionButton = new QPushButton(tr("&Reset"));
}

void ObjectSelectionPage::createLayout()
{
    QVBoxLayout *viewLayout = new QVBoxLayout;
    viewLayout->addWidget(objectList);
    viewBox->setLayout(viewLayout);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(selectAllButton);
    horizontalLayout->addWidget(selectNoneButton);
    horizontalLayout->addWidget(resetSelectionButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(viewBox);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
}

void ObjectSelectionPage::createConnections()
{
    QObject::connect(objectList, SIGNAL(itemChanged(QListWidgetItem *)),
                     this, SLOT(highlightChecked(QListWidgetItem *)));
    QObject::connect(selectAllButton, SIGNAL(clicked()), this, SLOT(selectAll()));
    QObject::connect(selectNoneButton, SIGNAL(clicked()), this, SLOT(selectNone()));
    QObject::connect(resetSelectionButton, SIGNAL(clicked()), this, SLOT(resetSelection()));
}

void ObjectSelectionPage::highlightChecked(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
        item->setBackgroundColor(QColor("#ffffb2"));
    else
        item->setBackgroundColor(QColor("#ffffff"));
}

void ObjectSelectionPage::selectAll()
{

    int cnt = objectList->count();
    for (int i = 0; i < cnt; i++)
    {
        QListWidgetItem *item = objectList->item(i);
        item->setCheckState(Qt::Checked);
    }
}

void ObjectSelectionPage::selectNone()
{
    int cnt = objectList->count();
    for (int i = 0; i < cnt; i++)
    {
        QListWidgetItem *item = objectList->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

void ObjectSelectionPage::resetSelection()
{
}

bool ObjectSelectionPage::validatePage()
{
    QStringList checkedList;
    QStringList unCheckedList;
    
    bool remove = true;

    int cnt = objectList->count();
    for (int i = 0; i < cnt; i++)
    {
        QListWidgetItem *item = objectList->item(i);
        if (Qt::Checked == item->checkState())
        {
            // this object is to be installed or uninstalled
            remove = false; // mean don't delete plugin instance because there are still objects in the plugin
        }
        else if (Qt::Unchecked == item->checkState())
        {

            if (1 == InstallationType)
            {
                // this object shoulb be remove from the installing objects map
                rpsSimulator->UpdateToBeInstalledObjectsMap(item->text());
            }
            else if (2 == InstallationType)
            {
                // this object shoulb be remove from the uninstalling objects map
                rpsSimulator->UpdateToBeUninstalledObjectsMap(item->text(), InstallingPluginName);
            }
            else if (3 == InstallationType)
            {
                // this object shoulb be remove from the installing objects map
                rpsSimulator->UpdateToBeInstalledObjectsMap(item->text());
            }
        }
    }

    if (1 == InstallationType)
    {
        // now the install the selected objects
        PluginManager::GetInstance().InstallPlugin(InstallingPluginFullPath);
    }
    else if (2 == InstallationType)
    {
        // now the install the selected objects
        PluginManager::GetInstance().UnInstallPlugin(InstallingPluginFullPath, remove);
    }
    else if (3 == InstallationType)
    {
        // now the install the selected objects
        PluginManager::GetInstance().InstallPlugin(InstallingPluginFullPath);
    }

    return QWizardPage::validatePage();
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
    progressBar->setValue(progressBar->value() + 1);
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
