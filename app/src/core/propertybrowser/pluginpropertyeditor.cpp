#include "pluginpropertyeditor.h"

#include <QDebug>
#include <QSplitter>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <limits>

#include "../3rdparty/propertybrowser/qteditorfactory.h"
#include "../3rdparty/propertybrowser/qtpropertymanager.h"
#include "../3rdparty/propertybrowser/qttreepropertybrowser.h"
#include "core/IconLoader.h"
#include "core/Utilities.h"
#include "core/propertybrowser/ObjectBrowserTreeItemModel.h"
#include "ui_pluginpropertyeditor.h"

#include "rps/RPSpluginManager.h"
#include "RPSWindLabAPI.h"
#include "RPSUserDefinedPhenomenonAPI.h"
#include "globals.h"



PluginPropertyEditor::PluginPropertyEditor(QWidget *parent, ApplicationWindow *app)
    : QDockWidget(parent),
      app_(app),
      ui_(new Ui_PluginPropertyEditor),
      splitter_(new QSplitter(Qt::Vertical)),
      objectbrowser_(new MyTreeWidget(this)),
      propertybrowser_(new QtTreePropertyBrowser(this)),
      objectitems_(QList<QTreeWidgetItem *>()),
      previouswidget_(nullptr),
      // property browser Items
      groupManager_(new QtGroupPropertyManager(propertybrowser_)),
      boolManager_(new QtBoolPropertyManager(propertybrowser_)),
      intManager_(new QtIntPropertyManager(propertybrowser_)),
      doubleManager_(new QtDoublePropertyManager(propertybrowser_)),
      stringManager_(new QtStringPropertyManager(propertybrowser_)),
      enumManager_(new QtEnumPropertyManager(propertybrowser_)),
      datetimeManager_(new QtDateTimePropertyManager(propertybrowser_)),
      // Property Widget factory
      lineEditFactory_(new QtLineEditFactory(propertybrowser_)),
      checkBoxFactory_(new QtCheckBoxFactory(propertybrowser_)),
      spinBoxFactory_(new QtSpinBoxFactory(propertybrowser_)),
      doubleSpinBoxFactory_(new QtDoubleSpinBoxFactory(propertybrowser_)),
      comboBoxFactory_(new QtEnumEditorFactory(propertybrowser_)),
      datetimeFactory_(new QtDateTimeEditFactory(propertybrowser_)) {
  Q_ASSERT(app_);
  ui_->setupUi(this);
  setWindowTitle(tr("RPS Objects Browser"));
  setWindowIcon(QIcon());
  objectbrowser_->setColumnCount(1);

  ui_->dockWidgetContents->layout()->setContentsMargins(0, 0, 0, 0);
  objectbrowser_->setFrameShape(QFrame::NoFrame);
  objectbrowser_->setSelectionMode(QAbstractItemView::SingleSelection);
  splitter_->addWidget(objectbrowser_);
  splitter_->addWidget(propertybrowser_);
  setWidget(splitter_);
  propertybrowser_->setFocusPolicy(Qt::NoFocus);

  // Property browser set up appropriate widget factory
  propertybrowser_->setFactoryForManager(boolManager_, checkBoxFactory_);
  propertybrowser_->setFactoryForManager(intManager_, spinBoxFactory_);
  propertybrowser_->setFactoryForManager(doubleManager_, doubleSpinBoxFactory_);
  propertybrowser_->setFactoryForManager(enumManager_, comboBoxFactory_);
  propertybrowser_->setFactoryForManager(datetimeManager_, datetimeFactory_);
  propertybrowser_->setFactoryForManager(stringManager_, lineEditFactory_);


  // Layout Properties
  pluginfileitem_= stringManager_->addProperty("File Name");
  pluginnameitem_= stringManager_->addProperty("Plugin Name");
  plugintypeitem_= stringManager_->addProperty("Plugin Type");
  pluginreleasedateitem_= stringManager_->addProperty("Release Date");
  pluginauthorsitem_= stringManager_->addProperty("Author");
  pluginversionitem_= stringManager_->addProperty("Version");
  pluginstatusitem_= stringManager_->addProperty("Status");
  plugindescriptionitem_= stringManager_->addProperty("Description");

  // parent object
  parentobjectnameitem_= stringManager_->addProperty("Name");
  parentobjectnumberofobjectitem_= intManager_->addProperty("Number of Objects");

  // object
  // object property
  objecttypeitem_= stringManager_->addProperty("Type");
  objectnameitem_= stringManager_->addProperty("Name");
  objectselecteditem_= stringManager_->addProperty("Selected");
  objectAuthoritem_= stringManager_->addProperty("Author");
  objectdescriptionitem_= stringManager_->addProperty("Description");
  objectpublicationtitleitem_= stringManager_->addProperty("Publication Topic");
  objectlinktopublicationitem_= stringManager_->addProperty("Link to Publication");
  objectpublicationdateitem_= stringManager_->addProperty("Publication Date");
  objectpublicationauthoritem_= stringManager_->addProperty("Publication Author");
  objectversionitem_= stringManager_->addProperty("Version");
  objectpluginitem_= stringManager_->addProperty("Plugin Name");
  objectpathitem_= stringManager_->addProperty("Path");
  objectpluginversionitem_= stringManager_->addProperty("Plugin Version");
  objectLabrpsversionitem_= stringManager_->addProperty("LabRPS Version");
  objectapiversionitem_= stringManager_->addProperty("API Version");
  objectreleasedateitem_= stringManager_->addProperty("Release Date");

  // initiate property ID required for compare()
  setObjectPropertyId();

  connect(objectbrowser_,
          SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
          SLOT(selectObjectItem(QTreeWidgetItem *)));
  connect(objectbrowser_, &MyTreeWidget::activate,
          [=](MyWidget *widget) { app_->activateWindow(widget); });
//   connect(objectbrowser_, &MyTreeWidget::itemRootContextMenuRequested, app_,
//           &ApplicationWindow::showWindowTitleBarMenu);
  connect(boolManager_, SIGNAL(valueChanged(QtProperty *, bool)), this,
          SLOT(valueChange(QtProperty *, const bool &))); 
  connect(doubleManager_, SIGNAL(valueChanged(QtProperty *, double)), this,
          SLOT(valueChange(QtProperty *, const double &)));
  connect(stringManager_, SIGNAL(valueChanged(QtProperty *, QString)), this,
          SLOT(valueChange(QtProperty *, const QString &)));
  connect(intManager_, SIGNAL(valueChanged(QtProperty *, int)), this,
          SLOT(valueChange(QtProperty *, const int)));
  connect(enumManager_, SIGNAL(valueChanged(QtProperty *, int)), this,
          SLOT(enumValueChange(QtProperty *, const int)));

  connect(datetimeManager_, &QtDateTimePropertyManager::valueChanged, this,
          &PluginPropertyEditor::datetimeValueChange);

}

PluginPropertyEditor::~PluginPropertyEditor() { delete ui_; }

MyTreeWidget *PluginPropertyEditor::getObjectBrowser() { return objectbrowser_; }
void PluginPropertyEditor::valueChange(QtProperty *prop, const bool value)
{}
void PluginPropertyEditor::valueChange(QtProperty *prop, const double &value)
{}
void PluginPropertyEditor::valueChange(QtProperty *prop, const QString &value)
{}
void PluginPropertyEditor::valueChange(QtProperty *prop, const int value)
{}
void PluginPropertyEditor::enumValueChange(QtProperty *prop, const int value)
{}
void PluginPropertyEditor::datetimeValueChange(QtProperty *prop, const QDateTime &datetime)
{}

void PluginPropertyEditor::selectObjectItem(QTreeWidgetItem *item)
{
        QString selectedRandomPhenomenon = app_->rpsSimulator->getSelectedRandomPhenomenon();

        if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
        {
                windLabSelectObjectItem(item);
        }
        else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
        {
                seismicLabSelectObjectItem(item);
        }
        else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
        {
                seaLabSelectObjectItem(item);
        }
        else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonUserDefined)
        {
                userDefinedPhenomenonSelectObjectItem(item);
        }
}

void PluginPropertyEditor::windLabSelectObjectItem(QTreeWidgetItem *item)
{
        MyTreeWidget::WindLabObjectPropertyItemType bb = static_cast<MyTreeWidget::WindLabObjectPropertyItemType>(
            item->data(0, Qt::UserRole).value<int>());

        if (!item)
        {
                return;
        }
        switch (static_cast<MyTreeWidget::WindLabObjectPropertyItemType>(
            item->data(0, Qt::UserRole).value<int>()))
        {
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabPlugin:
        {
                QString selectedPluginName = item->data(0, Qt::UserRole + 1).value<QString>();
                CPluginDescription *selectedPlugin = PluginManager::GetInstance().GetPluginDescriptionsMap()[selectedPluginName];
                WindLabPluginPropertyBlock(selectedPlugin);
        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabLocationDistribution:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupLocationDistribution;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabMeanProfile:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupMeanWindProfile;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabXSpectrumModel:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupAlongWindSpectrum;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabYSpectrumModel:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupAcrossWindSpectrum;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabZSpectrumModel:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupVerticalWindSpectrum;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabSpectrumDecompositionMethod:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupSpectrumDecompositionMethod;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabCoherence:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupCoherenceFunction;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabSimulationMethod:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupSimulationMethod;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabFrequencyDistribution:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupFrequencyDistribution;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabRandomness:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupRandomnessProvider;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabModulationFunction:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupModulationFunction;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabCorrelationFunction:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupCorrelationFunction;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);     
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabTableTool:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);

                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();

                // object group
                QString itemGroup = LabRPS::objGroupTableTool;

                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;

                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabMatrixTool:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);

                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();

                // object group
                QString itemGroup = LabRPS::objGroupMatrixTool;

                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;

                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);
                }

        }
        break;
        case MyTreeWidget::WindLabObjectPropertyItemType::WindLabUserDefinedRPSObject:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);

                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();

                // object group
                QString itemGroup = LabRPS::objGroupUserDefinedRPSObject;

                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;

                // get the number of object in location distribution objects group
                int count = GetNumberOfWindLabPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            WindLabParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetWindLabPluggedObjectDescription(itemGroup, itemtext);
                   WindLabObjectPropertyBlock(itemGroup, objectDescription);
                }

        }
        break;
        }
}
void PluginPropertyEditor::seaLabSelectObjectItem(QTreeWidgetItem *item)
{

}
void PluginPropertyEditor::seismicLabSelectObjectItem(QTreeWidgetItem *item)
{

}

void PluginPropertyEditor::userDefinedPhenomenonSelectObjectItem(QTreeWidgetItem *item)
{
        MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType bb = static_cast<MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType>(
            item->data(0, Qt::UserRole).value<int>());

        if (!item)
        {
                return;
        }
        switch (static_cast<MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType>(
            item->data(0, Qt::UserRole).value<int>()))
        {
        case MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType::UserDefinedPhenomenonPlugin:
        {
                QString selectedPluginName = item->data(0, Qt::UserRole + 1).value<QString>();
                CPluginDescription *selectedPlugin = PluginManager::GetInstance().GetPluginDescriptionsMap()[selectedPluginName];
                UserDefinedPhenomenonPluginPropertyBlock(selectedPlugin);
        }
        break;
        case MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType::UserDefinedPhenomenon:
        {
                // parent text of the selected item
                QString selectedItemParentText = item->parent()->text(0);
               
                // text of the selected item
                QString itemtext = item->data(0, Qt::UserRole + 1).value<QString>();
                
                // object group 
                QString itemGroup = LabRPS::objGroupUserDefinedPhenomenonObject;
                
                // iterator to search trough the map
                std::map<const QString, QString>::iterator it;
                
                // get the number of object in location distribution objects group
                int count = GetNumberOfUserDefinedPhenomenonPlggedObject(itemGroup, selectedItemParentText);

                // check if the seclected item is the location distribution objects group
                if (itemtext == itemGroup)
                {
                        if (count > 0)
                        {
                            UserDefinedPhenomenonParentObjectPropertyBlock(itemGroup, count);
                        }
                }else if(selectedItemParentText == itemGroup) // check if the parent of the seclected item is the location distribution objects group
                {
                   ObjectDescription objectDescription = GetUserDefinedPhenomenonPluggedObjectDescription(itemGroup, itemtext);
                   UserDefinedPhenomenonObjectPropertyBlock(itemGroup, objectDescription);
                }
        }    
        break;
        }
}
void PluginPropertyEditor::objectschanged() {
  MyWidget *mywidget = app_->getactiveMyWidget();
  populateObjectBrowser(mywidget);
}

void PluginPropertyEditor::populateObjectBrowser(MyWidget *widget)
{
         QString selectedRandomPhenomenon = app_->rpsSimulator->getSelectedRandomPhenomenon();

        if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonWindVelocity)
        {
                windLabPopulateObjectBrowser(widget);
        }
        else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeismicGroundMotion)
        {
                seismicLabPopulateObjectBrowser(widget);
        }
        else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonSeaSurface)
        {
                seaLabPopulateObjectBrowser(widget);
        }
        else if (selectedRandomPhenomenon == LabRPS::rpsPhenomenonUserDefined)
        {
                userDefinedPhenomenonPopulateObjectBrowser(widget);
        }
}

void PluginPropertyEditor::windLabPopulateObjectBrowser(MyWidget *widget)
{
         // delete all TreeWidgetItems
        objectbrowser_->blockSignals(true);
        while (objectbrowser_->topLevelItemCount())
        {
                QTreeWidgetItemIterator itr(objectbrowser_,
                                            QTreeWidgetItemIterator::NoChildren);
                while (*itr)
                {
                        delete (*itr);
                        ++itr;
                }
        }
        objectbrowser_->clear();
        objectitems_.clear();
        propertybrowser_->clear();
        objectbrowser_->blockSignals(false);

        /////////////*********rps********///////////////////////////
        objectbrowser_->setHeaderLabel("Plugins");
        objectbrowser_->headerItem()->setIcon(
            0, IconLoader::load("simulation-plugins", IconLoader::General));
        // installed plugins
        {
                // get the path to the plugin folder
                QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();

                // search and find all available plugin and save their descriptions
                PluginManager::GetInstance().SearchForAllPlugins(strPath);

                if (PluginManager::GetInstance().GetPluginDescriptionsMap().size() <= 0)
                {
                        objectbrowser_->setHeaderLabel("(none)");
                        objectbrowser_->headerItem()->setIcon(
                            0, IconLoader::load("clear-loginfo", IconLoader::General));
                        return;
                }

                // an iterator
                std::map<QString, CPluginDescription *>::iterator it;
                
                // iterate through all plugins
                for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
                {
                        // the name of the plugin
                        QString installedpluginitemtext = it->second->name;

                        // create the plugin note item
                        QTreeWidgetItem *installedpluginitem = new QTreeWidgetItem(
                            static_cast<QTreeWidget *>(nullptr), QStringList(installedpluginitemtext));
                        
                        // set tooltip and icon
                        installedpluginitem->setToolTip(0, installedpluginitemtext);
                        installedpluginitem->setIcon(0,
                                                     IconLoader::load("goto-cell", IconLoader::LightDark));
                        // set firt data to the item
                        installedpluginitem->setData(
                            0, Qt::UserRole,
                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabPlugin));
                        
                        // set second data to the item
                        installedpluginitem->setData(0, Qt::UserRole + 1,
                                                     QVariant(installedpluginitemtext));
                        
                        // add the plugin node item to the tree
                        objectitems_.append(installedpluginitem);

                        //////////////////Location Distribution////////////////////////////////////////////////////////////
                        // an iterator to iterate through the map
                        std::map<const QString, QString>::iterator it;
                        
                        // location distribution
                        if (!CrpsLocationDistributionFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupLocationDistribution;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabLocationDistribution));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsLocationDistributionFactory::GetOjectAndPluginMap().begin(); it != CrpsLocationDistributionFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabLocationDistribution));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // mean profile
                        if (!CrpsMeanFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupMeanWindProfile;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabMeanProfile));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsMeanFactory::GetOjectAndPluginMap().begin(); it != CrpsMeanFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabMeanProfile));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // along wind spectrum
                        if (!CrpsXSpectrumFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupAlongWindSpectrum;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabXSpectrumModel));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsXSpectrumFactory::GetOjectAndPluginMap().begin(); it != CrpsXSpectrumFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabXSpectrumModel));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // accross wind spectrum
                        if (!CrpsYSpectrumFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupAcrossWindSpectrum;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabYSpectrumModel));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsYSpectrumFactory::GetOjectAndPluginMap().begin(); it != CrpsYSpectrumFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabYSpectrumModel));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // vertical wind spectrum
                        if (!CrpsZSpectrumFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupVerticalWindSpectrum;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabZSpectrumModel));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsZSpectrumFactory::GetOjectAndPluginMap().begin(); it != CrpsZSpectrumFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabZSpectrumModel));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                         // spectrum decomposition method
                        if (!CrpsPSDdecomMethodFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupSpectrumDecompositionMethod;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabSpectrumDecompositionMethod));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsPSDdecomMethodFactory::GetOjectAndPluginMap().begin(); it != CrpsPSDdecomMethodFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabSpectrumDecompositionMethod));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // coherence function
                        if (!CrpsCoherenceFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupCoherenceFunction;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabCoherence));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsCoherenceFactory::GetOjectAndPluginMap().begin(); it != CrpsCoherenceFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabCoherence));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // simulation method
                        if (!CrpsSimuMethodFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupSimulationMethod;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabSimulationMethod));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsSimuMethodFactory::GetOjectAndPluginMap().begin(); it != CrpsSimuMethodFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabSimulationMethod));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // frequency distribution
                        if (!CrpsFrequencyDistributionFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupFrequencyDistribution;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabFrequencyDistribution));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsFrequencyDistributionFactory::GetOjectAndPluginMap().begin(); it != CrpsFrequencyDistributionFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabFrequencyDistribution));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // randomness provider
                        if (!CrpsRandomnessFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupRandomnessProvider;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabRandomness));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsRandomnessFactory::GetOjectAndPluginMap().begin(); it != CrpsRandomnessFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabRandomness));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                         // modulation funcion
                        if (!CrpsModulationFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupModulationFunction;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabModulationFunction));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsModulationFactory::GetOjectAndPluginMap().begin(); it != CrpsModulationFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabModulationFunction));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                         // correlation function
                        if (!CrpsCorrelationFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupCorrelationFunction;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabCorrelationFunction));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsCorrelationFactory::GetOjectAndPluginMap().begin(); it != CrpsCorrelationFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabCorrelationFunction));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // table tool
                        if (!CrpsTableToolFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupTableTool;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabTableTool));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsTableToolFactory::GetOjectAndPluginMap().begin(); it != CrpsTableToolFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabTableTool));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // table tool
                        if (!CrpsMatrixToolFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupMatrixTool;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabMatrixTool));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsMatrixToolFactory::GetOjectAndPluginMap().begin(); it != CrpsMatrixToolFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabMatrixTool));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }

                        // user defined rps object
                        if (!CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupUserDefinedRPSObject;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabCoherence));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));
   
                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap().begin(); it != CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::WindLabObjectPropertyItemType::WindLabUserDefinedRPSObject));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }
                                
                        }
                }

                // add to Tree
                objectbrowser_->addTopLevelItems(objectitems_);
                objectbrowser_->insertTopLevelItems(0, objectitems_);
                // objectbrowser_->expandAll();
        }
        // tableConnections(table);
}
void PluginPropertyEditor::seaLabPopulateObjectBrowser(MyWidget *widget)
{
        // delete all TreeWidgetItems
        objectbrowser_->blockSignals(true);
        while (objectbrowser_->topLevelItemCount())
        {
                QTreeWidgetItemIterator itr(objectbrowser_,
                                            QTreeWidgetItemIterator::NoChildren);
                while (*itr)
                {
                        delete (*itr);
                        ++itr;
                }
        }
        objectbrowser_->clear();
        objectitems_.clear();
        propertybrowser_->clear();
        objectbrowser_->blockSignals(false);

        /////////////*********rps********///////////////////////////
        objectbrowser_->setHeaderLabel("Plugins");
        objectbrowser_->headerItem()->setIcon(
            0, IconLoader::load("simulation-plugins", IconLoader::General));
        // installed plugins
        {
                // get the path to the plugin folder
                QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();

                // search and find all available plugin and save their descriptions
                PluginManager::GetInstance().SearchForAllPlugins(strPath);

                if (PluginManager::GetInstance().GetPluginDescriptionsMap().size() <= 0)
                {
                        objectbrowser_->setHeaderLabel("(none)");
                        objectbrowser_->headerItem()->setIcon(
                            0, IconLoader::load("clear-loginfo", IconLoader::General));
                        return;
                }

                // an iterator
                std::map<QString, CPluginDescription *>::iterator it;

                // iterate through all plugins
                for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
                {
                        // the name of the plugin
                        QString installedpluginitemtext = it->second->name;

                        // create the plugin note item
                        QTreeWidgetItem *installedpluginitem = new QTreeWidgetItem(
                            static_cast<QTreeWidget *>(nullptr), QStringList(installedpluginitemtext));

                        // set tooltip and icon
                        installedpluginitem->setToolTip(0, installedpluginitemtext);
                        installedpluginitem->setIcon(0,
                                                     IconLoader::load("goto-cell", IconLoader::LightDark));
                        // set firt data to the item
                        installedpluginitem->setData(
                            0, Qt::UserRole,
                            static_cast<int>(MyTreeWidget::SeaLabObjectPropertyItemType::SeaLabPlugin));

                        // set second data to the item
                        installedpluginitem->setData(0, Qt::UserRole + 1,
                                                     QVariant(installedpluginitemtext));

                        // add the plugin node item to the tree
                        objectitems_.append(installedpluginitem);
                }

                // add to Tree
                objectbrowser_->addTopLevelItems(objectitems_);
                objectbrowser_->insertTopLevelItems(0, objectitems_);
                // objectbrowser_->expandAll();
        }
}
void PluginPropertyEditor::seismicLabPopulateObjectBrowser(MyWidget *widget)
{
        // delete all TreeWidgetItems
        objectbrowser_->blockSignals(true);
        while (objectbrowser_->topLevelItemCount())
        {
                QTreeWidgetItemIterator itr(objectbrowser_,
                                            QTreeWidgetItemIterator::NoChildren);
                while (*itr)
                {
                        delete (*itr);
                        ++itr;
                }
        }
        objectbrowser_->clear();
        objectitems_.clear();
        propertybrowser_->clear();
        objectbrowser_->blockSignals(false);

        /////////////*********rps********///////////////////////////
        objectbrowser_->setHeaderLabel("Plugins");
        objectbrowser_->headerItem()->setIcon(
            0, IconLoader::load("simulation-plugins", IconLoader::General));
        // installed plugins
        {
                // get the path to the plugin folder
                QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();

                // search and find all available plugin and save their descriptions
                PluginManager::GetInstance().SearchForAllPlugins(strPath);

                if (PluginManager::GetInstance().GetPluginDescriptionsMap().size() <= 0)
                {
                        objectbrowser_->setHeaderLabel("(none)");
                        objectbrowser_->headerItem()->setIcon(
                            0, IconLoader::load("clear-loginfo", IconLoader::General));
                        return;
                }

                // an iterator
                std::map<QString, CPluginDescription *>::iterator it;

                // iterate through all plugins
                for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
                {
                        // the name of the plugin
                        QString installedpluginitemtext = it->second->name;

                        // create the plugin note item
                        QTreeWidgetItem *installedpluginitem = new QTreeWidgetItem(
                            static_cast<QTreeWidget *>(nullptr), QStringList(installedpluginitemtext));

                        // set tooltip and icon
                        installedpluginitem->setToolTip(0, installedpluginitemtext);
                        installedpluginitem->setIcon(0,
                                                     IconLoader::load("goto-cell", IconLoader::LightDark));
                        // set firt data to the item
                        installedpluginitem->setData(
                            0, Qt::UserRole,
                            static_cast<int>(MyTreeWidget::SeismicLabObjectPropertyItemType::SeismicLabPlugin));

                        // set second data to the item
                        installedpluginitem->setData(0, Qt::UserRole + 1,
                                                     QVariant(installedpluginitemtext));

                        // add the plugin node item to the tree
                        objectitems_.append(installedpluginitem);
                }

                // add to Tree
                objectbrowser_->addTopLevelItems(objectitems_);
                objectbrowser_->insertTopLevelItems(0, objectitems_);
                // objectbrowser_->expandAll();
        }
}
void PluginPropertyEditor::userDefinedPhenomenonPopulateObjectBrowser(MyWidget *widget)
{
         // delete all TreeWidgetItems
        objectbrowser_->blockSignals(true);
        while (objectbrowser_->topLevelItemCount())
        {
                QTreeWidgetItemIterator itr(objectbrowser_,
                                            QTreeWidgetItemIterator::NoChildren);
                while (*itr)
                {
                        delete (*itr);
                        ++itr;
                }
        }
        objectbrowser_->clear();
        objectitems_.clear();
        propertybrowser_->clear();
        objectbrowser_->blockSignals(false);

        /////////////*********rps********///////////////////////////
        objectbrowser_->setHeaderLabel("Plugins");
        objectbrowser_->headerItem()->setIcon(
            0, IconLoader::load("simulation-plugins", IconLoader::General));
        // installed plugins
        {
                // get the path to the plugin folder
                QString strPath = PluginManager::GetInstance().GetPluginLacotionPath();

                // search and find all available plugin and save their descriptions
                PluginManager::GetInstance().SearchForAllPlugins(strPath);

                if (PluginManager::GetInstance().GetPluginDescriptionsMap().size() <= 0)
                {
                        objectbrowser_->setHeaderLabel("(none)");
                        objectbrowser_->headerItem()->setIcon(
                            0, IconLoader::load("clear-loginfo", IconLoader::General));
                        return;
                }

                // an iterator
                std::map<QString, CPluginDescription *>::iterator it;

                // iterate through all plugins
                for (it = PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it)
                {
                        // the name of the plugin
                        QString installedpluginitemtext = it->second->name;

                        // create the plugin note item
                        QTreeWidgetItem *installedpluginitem = new QTreeWidgetItem(
                            static_cast<QTreeWidget *>(nullptr), QStringList(installedpluginitemtext));

                        // set tooltip and icon
                        installedpluginitem->setToolTip(0, installedpluginitemtext);
                        installedpluginitem->setIcon(0,
                                                     IconLoader::load("goto-cell", IconLoader::LightDark));
                        // set firt data to the item
                        installedpluginitem->setData(
                            0, Qt::UserRole,
                            static_cast<int>(MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType::UserDefinedPhenomenonPlugin));

                        // set second data to the item
                        installedpluginitem->setData(0, Qt::UserRole + 1,
                                                     QVariant(installedpluginitemtext));

                        // add the plugin node item to the tree
                        objectitems_.append(installedpluginitem);

                        //////////////////UserDefinedPhenomenon////////////////////////////////////////////////////////////
                        // an iterator to iterate through the map
                        std::map<const QString, QString>::iterator it;

                        // location distribution
                        if (!CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap().empty())
                        {
                                QString itemtext = LabRPS::objGroupUserDefinedPhenomenonObject;

                                // create a new node that will be added under the plugin node
                                QTreeWidgetItem *groupItem = new QTreeWidgetItem(
                                    static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                // set tooltip and icon
                                groupItem->setToolTip(0, itemtext);
                                groupItem->setIcon(0,
                                              IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                groupItem->setData(
                                    0, Qt::UserRole,
                                    static_cast<int>(MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType::UserDefinedPhenomenon));
                                groupItem->setData(0, Qt::UserRole + 1, QVariant(itemtext));

                                // Iterate though the map and show all the registed location distribution in the combo box
                                for (it = CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap().begin(); it != CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap().end(); ++it)
                                {
                                       if(it->second == installedpluginitemtext)
                                       {
                                        QString itemtext = it->first;
                                        QTreeWidgetItem *item = new QTreeWidgetItem(
                                            static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));

                                        item->setToolTip(0, itemtext);
                                        item->setIcon(0,
                                                      IconLoader::load("graph2d-layout", IconLoader::LightDark));
                                        item->setData(
                                            0, Qt::UserRole,
                                            static_cast<int>(MyTreeWidget::UserDefinedPhenomenonObjectPropertyItemType::UserDefinedPhenomenon));
                                        item->setData(0, Qt::UserRole + 1, QVariant(itemtext));
                                        installedpluginitem->addChild(groupItem);
                                        groupItem->addChild(item);
                                       }
                                }

                        }
                }

                // add to Tree
                objectbrowser_->addTopLevelItems(objectitems_);
                objectbrowser_->insertTopLevelItems(0, objectitems_);
                // objectbrowser_->expandAll();
        }
        // tableConnections(table);
}
void PluginPropertyEditor::setObjectPropertyId()
{}

void PluginPropertyEditor::blockManagers(bool value) {
  groupManager_->blockSignals(value);
  boolManager_->blockSignals(value);
  intManager_->blockSignals(value);
  doubleManager_->blockSignals(value);
  stringManager_->blockSignals(value);
  enumManager_->blockSignals(value);
}

void PluginPropertyEditor::WindLabPluginPropertyBlock(CPluginDescription *description)
{
        propertybrowser_->clear();
        propertybrowser_->addProperty(pluginfileitem_);
        propertybrowser_->addProperty(pluginnameitem_);
        propertybrowser_->addProperty(plugintypeitem_);
        propertybrowser_->addProperty(pluginreleasedateitem_);
        propertybrowser_->addProperty(pluginauthorsitem_);
        propertybrowser_->addProperty(pluginversionitem_);
        propertybrowser_->addProperty(pluginstatusitem_);
        propertybrowser_->addProperty(plugindescriptionitem_);

        stringManager_->setValue(pluginfileitem_, description->fileName);
        stringManager_->setValue(pluginnameitem_, description->name);
        stringManager_->setValue(plugintypeitem_, description->type);
        stringManager_->setValue(pluginreleasedateitem_, description->releaseDate);
        stringManager_->setValue(pluginauthorsitem_, description->authors);
        stringManager_->setValue(pluginversionitem_, description->version);
        stringManager_->setValue(plugindescriptionitem_, description->description);

        if (app_->rpsSimulator->rpsWindLabSimulator->isThisPluginInstalled(description->name))
        {
                stringManager_->setValue(pluginstatusitem_, "Installed");
        }
        else
        {
                stringManager_->setValue(pluginstatusitem_, "Not installed");
        }
}

void PluginPropertyEditor::WindLabParentObjectPropertyBlock(const QString &name, const int &number)
{
        propertybrowser_->clear();
        propertybrowser_->addProperty(parentobjectnameitem_);
        propertybrowser_->addProperty(parentobjectnumberofobjectitem_);

        stringManager_->setValue(parentobjectnameitem_, name);
        intManager_->setValue(parentobjectnumberofobjectitem_, number);

}

void PluginPropertyEditor::WindLabObjectPropertyBlock(const QString &objectGroup, const ObjectDescription &object)
{
 propertybrowser_->clear();
 propertybrowser_->addProperty(objecttypeitem_);
 propertybrowser_->addProperty(objectnameitem_);
 propertybrowser_->addProperty(objectselecteditem_);
 propertybrowser_->addProperty(objectpluginitem_);
 propertybrowser_->addProperty(objectAuthoritem_);
 propertybrowser_->addProperty(objectpathitem_);
 propertybrowser_->addProperty(objectpluginversionitem_);
 propertybrowser_->addProperty(objectLabrpsversionitem_);
 propertybrowser_->addProperty(objectapiversionitem_);
 propertybrowser_->addProperty(objectreleasedateitem_);
 propertybrowser_->addProperty(objectdescriptionitem_);
 propertybrowser_->addProperty(objectpublicationtitleitem_);
 propertybrowser_->addProperty(objectlinktopublicationitem_);
 propertybrowser_->addProperty(objectpublicationdateitem_);
 propertybrowser_->addProperty(objectpublicationauthoritem_);
 propertybrowser_->addProperty(objectversionitem_);


QString isSelected = GetWindLabObjectSelectionState(objectGroup, object.m_objectName, app_->rpsSimulator->rpsWindLabSimulator->GetWindLabData());
stringManager_->setValue(objecttypeitem_, "Object");
stringManager_->setValue(objectnameitem_, object.m_objectName);
stringManager_->setValue(objectselecteditem_, isSelected);
stringManager_->setValue(objectAuthoritem_, object.m_author);
stringManager_->setValue(objectpathitem_, object.m_path);
stringManager_->setValue(objectpluginversionitem_, object.m_pluginVersion);
stringManager_->setValue(objectapiversionitem_, object.m_apiVersion);
stringManager_->setValue(objectreleasedateitem_, object.m_releaseDate);
stringManager_->setValue(objectdescriptionitem_, object.m_description);
stringManager_->setValue(objectpublicationtitleitem_, object.m_publicationTitle);
stringManager_->setValue(objectlinktopublicationitem_, object.m_publicationLink);
stringManager_->setValue(objectpublicationdateitem_, object.m_publicationDate);
stringManager_->setValue(objectpluginitem_, object.m_pluginName);
stringManager_->setValue(objectpublicationauthoritem_, object.m_publicationAuthor);
stringManager_->setValue(objectversionitem_, object.m_version);
stringManager_->setValue(objectLabrpsversionitem_, object.m_labRPSVersion);


}

ObjectDescription PluginPropertyEditor::GetWindLabPluggedObjectDescription(const QString &objectGroup, const QString &objectName)
{
	ObjectDescription pluggedObjectDescription;

	QString pluginName = QString("");
	QString descrip = QString("");
	QString pubTitle = QString("");
	QString pubLink = QString("");
	QString pubAuthor = QString("");
	QString pubDate = QString("");
        QString version = QString("");


        if (objectGroup == LabRPS::objGroupLocationDistribution)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsLocationDistributionFactory::GetOjectDescriptionMap()[objectName];
			
			pubTitle = CrpsLocationDistributionFactory::GetTitleMap()[objectName];
			pubLink = CrpsLocationDistributionFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsLocationDistributionFactory::GetAuthorMap()[objectName];
			pubDate = CrpsLocationDistributionFactory::GetDateMap()[objectName];
			version = CrpsLocationDistributionFactory::GetVersionMap()[objectName];
		}
	}
	else if (objectGroup == LabRPS::objGroupMeanWindProfile)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsMeanFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsMeanFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsMeanFactory::GetTitleMap()[objectName];
			pubLink = CrpsMeanFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsMeanFactory::GetAuthorMap()[objectName];
			pubDate = CrpsMeanFactory::GetDateMap()[objectName];
			version = CrpsMeanFactory::GetVersionMap()[objectName];
		}
	}
	else if (objectGroup == LabRPS::objGroupAlongWindSpectrum)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsXSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsXSpectrumFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsXSpectrumFactory::GetTitleMap()[objectName];
			pubLink = CrpsXSpectrumFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsXSpectrumFactory::GetAuthorMap()[objectName];
			pubDate = CrpsXSpectrumFactory::GetDateMap()[objectName];
			version = CrpsXSpectrumFactory::GetVersionMap()[objectName];
		}
	}
	else if (objectGroup == LabRPS::objGroupAcrossWindSpectrum)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsYSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsYSpectrumFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsYSpectrumFactory::GetTitleMap()[objectName];
			pubLink = CrpsYSpectrumFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsYSpectrumFactory::GetAuthorMap()[objectName];
			pubDate = CrpsYSpectrumFactory::GetDateMap()[objectName];
			version = CrpsYSpectrumFactory::GetVersionMap()[objectName];
		}
	}
	else if (objectGroup == LabRPS::objGroupVerticalWindSpectrum)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsZSpectrumFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsZSpectrumFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsZSpectrumFactory::GetTitleMap()[objectName];
			pubLink = CrpsZSpectrumFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsZSpectrumFactory::GetAuthorMap()[objectName];
			pubDate = CrpsZSpectrumFactory::GetDateMap()[objectName];
			version = CrpsZSpectrumFactory::GetVersionMap()[objectName];

		}
	}
	else if (objectGroup == LabRPS::objGroupSpectrumDecompositionMethod)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsPSDdecomMethodFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsPSDdecomMethodFactory::GetTitleMap()[objectName];
			pubLink = CrpsPSDdecomMethodFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsPSDdecomMethodFactory::GetAuthorMap()[objectName];
			pubDate = CrpsPSDdecomMethodFactory::GetDateMap()[objectName];
			version = CrpsPSDdecomMethodFactory::GetVersionMap()[objectName];

		}
	}
	else if (objectGroup == LabRPS::objGroupCoherenceFunction)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsCoherenceFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsCoherenceFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsCoherenceFactory::GetTitleMap()[objectName];
			pubLink = CrpsCoherenceFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsCoherenceFactory::GetAuthorMap()[objectName];
			pubDate = CrpsCoherenceFactory::GetDateMap()[objectName];
			version = CrpsCoherenceFactory::GetVersionMap()[objectName];
		}
	}
	else if (objectGroup == LabRPS::objGroupSimulationMethod)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsSimuMethodFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsSimuMethodFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsSimuMethodFactory::GetTitleMap()[objectName];
			pubLink = CrpsSimuMethodFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsSimuMethodFactory::GetAuthorMap()[objectName];
			pubDate = CrpsSimuMethodFactory::GetDateMap()[objectName];
			version = CrpsSimuMethodFactory::GetVersionMap()[objectName];

		}
	}
	else if (objectGroup == LabRPS::objGroupFrequencyDistribution)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsFrequencyDistributionFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsFrequencyDistributionFactory::GetTitleMap()[objectName];
			pubLink = CrpsFrequencyDistributionFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsFrequencyDistributionFactory::GetAuthorMap()[objectName];
			pubDate = CrpsFrequencyDistributionFactory::GetDateMap()[objectName];
			version = CrpsFrequencyDistributionFactory::GetVersionMap()[objectName];

		}
	}
	else if (objectGroup == LabRPS::objGroupRandomnessProvider)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsRandomnessFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsRandomnessFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsRandomnessFactory::GetTitleMap()[objectName];
			pubLink = CrpsRandomnessFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsRandomnessFactory::GetAuthorMap()[objectName];
			pubDate = CrpsRandomnessFactory::GetDateMap()[objectName];
			version = CrpsRandomnessFactory::GetVersionMap()[objectName];

		}
	}
	else if (objectGroup == LabRPS::objGroupModulationFunction)
	{
		if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
		{
            pluginName = CrpsModulationFactory::GetTobeInstalledObjectsMap()[objectName];
			descrip = CrpsModulationFactory::GetOjectDescriptionMap()[objectName];

			pubTitle = CrpsModulationFactory::GetTitleMap()[objectName];
			pubLink = CrpsModulationFactory::GetLinkMap()[objectName];
			pubAuthor = CrpsModulationFactory::GetAuthorMap()[objectName];
			pubDate = CrpsModulationFactory::GetDateMap()[objectName];
			version = CrpsModulationFactory::GetVersionMap()[objectName];

		}
	}
        else if (objectGroup == LabRPS::objGroupTableTool)
        {
            if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
            {
                pluginName = CrpsTableToolFactory::GetTobeInstalledObjectsMap()[objectName];
                descrip = CrpsTableToolFactory::GetOjectDescriptionMap()[objectName];

                pubTitle = CrpsTableToolFactory::GetTitleMap()[objectName];
                pubLink = CrpsTableToolFactory::GetLinkMap()[objectName];
                pubAuthor = CrpsTableToolFactory::GetAuthorMap()[objectName];
                pubDate = CrpsTableToolFactory::GetDateMap()[objectName];
                version = CrpsTableToolFactory::GetVersionMap()[objectName];

            }
        }
        else if (objectGroup == LabRPS::objGroupMatrixTool)
        {
            if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
            {
                pluginName = CrpsMatrixToolFactory::GetTobeInstalledObjectsMap()[objectName];
                descrip = CrpsMatrixToolFactory::GetOjectDescriptionMap()[objectName];

                pubTitle = CrpsMatrixToolFactory::GetTitleMap()[objectName];
                pubLink = CrpsMatrixToolFactory::GetLinkMap()[objectName];
                pubAuthor = CrpsMatrixToolFactory::GetAuthorMap()[objectName];
                pubDate = CrpsMatrixToolFactory::GetDateMap()[objectName];
                version = CrpsMatrixToolFactory::GetVersionMap()[objectName];

            }
        }
        else if (objectGroup == LabRPS::objGroupUserDefinedRPSObject)
        {
            if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
            {
                pluginName = CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap()[objectName];
                descrip = CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap()[objectName];

                pubTitle = CrpsUserDefinedRPSObjectFactory::GetTitleMap()[objectName];
                pubLink = CrpsUserDefinedRPSObjectFactory::GetLinkMap()[objectName];
                pubAuthor = CrpsUserDefinedRPSObjectFactory::GetAuthorMap()[objectName];
                pubDate = CrpsUserDefinedRPSObjectFactory::GetDateMap()[objectName];
                version = CrpsUserDefinedRPSObjectFactory::GetVersionMap()[objectName];

            }
        }

	if (PluginManager::GetInstance().GetInstalledPluginsNameMap().find(pluginName) != PluginManager::GetInstance().GetInstalledPluginsNameMap().end())
	{
		pluggedObjectDescription.m_pluginName = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetDisplayName();
		pluggedObjectDescription.m_releaseDate = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginReleaseDate();
		pluggedObjectDescription.m_path = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginSubFolder();
		pluggedObjectDescription.m_author = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginAuthor();
		pluggedObjectDescription.m_pluginVersion = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginVersion();
		pluggedObjectDescription.m_labRPSVersion = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetLabRPSVersion();
		pluggedObjectDescription.m_apiVersion = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetAPIVersion();
		pluggedObjectDescription.m_objectName = objectName;
        pluggedObjectDescription.m_version = version;
		pluggedObjectDescription.m_description = descrip;
		pluggedObjectDescription.m_publicationTitle = pubTitle;
		pluggedObjectDescription.m_publicationLink = pubLink;
		pluggedObjectDescription.m_publicationAuthor = pubAuthor;
		pluggedObjectDescription.m_publicationDate = pubDate;

	}
	
        return pluggedObjectDescription;
}

QString  PluginPropertyEditor::GetWindLabObjectSelectionState(const QString &objectGroup, const QString &objectName, const CRPSWindLabsimuData &windLabsimuData)
{
	QString yesResult = QString("Yes");
	QString noResult = QString("No");

	if (objectGroup == LabRPS::objGroupLocationDistribution)
	{
		return objectName == windLabsimuData.spatialDistribution ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupMeanWindProfile)
	{
		return objectName == windLabsimuData.meanFunction ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupAlongWindSpectrum)
	{
		return objectName == windLabsimuData.spectrumModel ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupAcrossWindSpectrum)
	{
		return objectName == windLabsimuData.spectrumModel ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupAcrossWindSpectrum)
	{
		return objectName == windLabsimuData.spectrumModel ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupSpectrumDecompositionMethod)
	{
        return objectName == windLabsimuData.cpsdDecompositionMethod ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupCoherenceFunction)
	{
		return objectName == windLabsimuData.coherenceFunction ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupSimulationMethod)
	{
		return objectName == windLabsimuData.simulationMethod ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupFrequencyDistribution)
	{
		return objectName == windLabsimuData.freqencyDistribution ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupRandomnessProvider)
	{
		return objectName == windLabsimuData.randomnessProvider ? yesResult : noResult;
	}
	else if (objectGroup == LabRPS::objGroupModulationFunction)
	{
		return objectName == windLabsimuData.modulationFunction ? yesResult : noResult;
	}
    else if (objectGroup == LabRPS::objGroupTableTool)
    {
        return objectName == windLabsimuData.tableTool ? yesResult : noResult;
    }
    else if (objectGroup == LabRPS::objGroupMatrixTool)
    {
        return objectName == windLabsimuData.matrixTool ? yesResult : noResult;
    }
    else if (objectGroup == LabRPS::objGroupUserDefinedRPSObject)
    {
        return objectName == windLabsimuData.userDefinedRPSObject ? yesResult : noResult;
    }

	return noResult;
}

int PluginPropertyEditor::GetNumberOfWindLabPlggedObject(const QString &itemText, const QString &parenttext)
{
        std::map<const QString, QString>::iterator it;
        int count = 0;
    
	if (itemText == LabRPS::objGroupLocationDistribution)
	{
                 for (it = CrpsLocationDistributionFactory::GetOjectAndPluginMap().begin(); it != CrpsLocationDistributionFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupMeanWindProfile)
	{
                 for (it = CrpsMeanFactory::GetOjectAndPluginMap().begin(); it != CrpsMeanFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupAlongWindSpectrum)
	{
                 for (it = CrpsXSpectrumFactory::GetOjectAndPluginMap().begin(); it != CrpsXSpectrumFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupAcrossWindSpectrum)
	{
                 for (it = CrpsYSpectrumFactory::GetOjectAndPluginMap().begin(); it != CrpsYSpectrumFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupVerticalWindSpectrum)
	{
                 for (it = CrpsZSpectrumFactory::GetOjectAndPluginMap().begin(); it != CrpsZSpectrumFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupSpectrumDecompositionMethod)
	{
                 for (it = CrpsPSDdecomMethodFactory::GetOjectAndPluginMap().begin(); it != CrpsPSDdecomMethodFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
		return CrpsPSDdecomMethodFactory::GetPSDdecomMethodNamesMap().size();
	}
	else if (itemText == LabRPS::objGroupCoherenceFunction)
	{
                 for (it = CrpsCoherenceFactory::GetOjectAndPluginMap().begin(); it != CrpsCoherenceFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupSimulationMethod)
	{
                 for (it = CrpsSimuMethodFactory::GetOjectAndPluginMap().begin(); it != CrpsSimuMethodFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
		return CrpsSimuMethodFactory::GetSimuMethodNamesMap().size();
	}
	else if (itemText == LabRPS::objGroupFrequencyDistribution)
	{
                 for (it = CrpsFrequencyDistributionFactory::GetOjectAndPluginMap().begin(); it != CrpsFrequencyDistributionFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupRandomnessProvider)
	{
                 for (it = CrpsRandomnessFactory::GetOjectAndPluginMap().begin(); it != CrpsRandomnessFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
	else if (itemText == LabRPS::objGroupModulationFunction)
	{
                 for (it = CrpsModulationFactory::GetOjectAndPluginMap().begin(); it != CrpsModulationFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
	}
    else if (itemText == LabRPS::objGroupTableTool)
    {
                 for (it = CrpsTableToolFactory::GetOjectAndPluginMap().begin(); it != CrpsTableToolFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
    }
    else if (itemText == LabRPS::objGroupMatrixTool)
    {
                 for (it = CrpsMatrixToolFactory::GetOjectAndPluginMap().begin(); it != CrpsMatrixToolFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
    }
    else if (itemText == LabRPS::objGroupUserDefinedRPSObject)
    {
                 for (it = CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap().begin(); it != CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
    }

	return 0;
}

//userDefinedPhenomenon

void PluginPropertyEditor::UserDefinedPhenomenonPluginPropertyBlock(CPluginDescription *description)
{
        propertybrowser_->clear();
        propertybrowser_->addProperty(pluginfileitem_);
        propertybrowser_->addProperty(pluginnameitem_);
        propertybrowser_->addProperty(plugintypeitem_);
        propertybrowser_->addProperty(pluginreleasedateitem_);
        propertybrowser_->addProperty(pluginauthorsitem_);
        propertybrowser_->addProperty(pluginversionitem_);
        propertybrowser_->addProperty(pluginstatusitem_);
        propertybrowser_->addProperty(plugindescriptionitem_);

        stringManager_->setValue(pluginfileitem_, description->fileName);
        stringManager_->setValue(pluginnameitem_, description->name);
        stringManager_->setValue(plugintypeitem_, description->type);
        stringManager_->setValue(pluginreleasedateitem_, description->releaseDate);
        stringManager_->setValue(pluginauthorsitem_, description->authors);
        stringManager_->setValue(pluginversionitem_, description->version);
        stringManager_->setValue(plugindescriptionitem_, description->description);

        if (!PluginManager::GetInstance().GetInstalledPluginsMap().empty())
        {
                if (PluginManager::GetInstance().GetInstalledPluginsMap().find(description->fullPath) != PluginManager::GetInstance().GetInstalledPluginsMap().end())
                {
                        stringManager_->setValue(pluginstatusitem_, "Installed");
                }
                else
                {
                        stringManager_->setValue(pluginstatusitem_, "Not installed");
                }
        }
        else
        {
                stringManager_->setValue(pluginstatusitem_, "Not installed");
        }
}

void PluginPropertyEditor::UserDefinedPhenomenonParentObjectPropertyBlock(const QString &name, const int &number)
{
        propertybrowser_->clear();
        propertybrowser_->addProperty(parentobjectnameitem_);
        propertybrowser_->addProperty(parentobjectnumberofobjectitem_);

        stringManager_->setValue(parentobjectnameitem_, name);
        intManager_->setValue(parentobjectnumberofobjectitem_, number);

}

void PluginPropertyEditor::UserDefinedPhenomenonObjectPropertyBlock(const QString &objectGroup, const ObjectDescription &object)
{
 propertybrowser_->clear();
 propertybrowser_->addProperty(objecttypeitem_);
 propertybrowser_->addProperty(objectnameitem_);
 propertybrowser_->addProperty(objectselecteditem_);
 propertybrowser_->addProperty(objectpluginitem_);
 propertybrowser_->addProperty(objectAuthoritem_);
 propertybrowser_->addProperty(objectpathitem_);
 propertybrowser_->addProperty(objectpluginversionitem_);
 propertybrowser_->addProperty(objectLabrpsversionitem_);
 propertybrowser_->addProperty(objectapiversionitem_);
 propertybrowser_->addProperty(objectreleasedateitem_);
 propertybrowser_->addProperty(objectdescriptionitem_);
 propertybrowser_->addProperty(objectpublicationtitleitem_);
 propertybrowser_->addProperty(objectlinktopublicationitem_);
 propertybrowser_->addProperty(objectpublicationdateitem_);
 propertybrowser_->addProperty(objectpublicationauthoritem_);
 propertybrowser_->addProperty(objectversionitem_);


QString isSelected = GetUserDefinedPhenomenonObjectSelectionState(objectGroup, object.m_objectName, app_->rpsSimulator->rpsUserDefinedPhenomenonSimulator->GetUserDefinedPhenomenonSimulationData());
stringManager_->setValue(objecttypeitem_, "Object");
stringManager_->setValue(objectnameitem_, object.m_objectName);
stringManager_->setValue(objectselecteditem_, isSelected);
stringManager_->setValue(objectAuthoritem_, object.m_author);
stringManager_->setValue(objectpathitem_, object.m_path);
stringManager_->setValue(objectpluginversionitem_, object.m_pluginVersion);
stringManager_->setValue(objectapiversionitem_, object.m_apiVersion);
stringManager_->setValue(objectreleasedateitem_, object.m_releaseDate);
stringManager_->setValue(objectdescriptionitem_, object.m_description);
stringManager_->setValue(objectpublicationtitleitem_, object.m_publicationTitle);
stringManager_->setValue(objectlinktopublicationitem_, object.m_publicationLink);
stringManager_->setValue(objectpublicationdateitem_, object.m_publicationDate);
stringManager_->setValue(objectpluginitem_, object.m_pluginName);
stringManager_->setValue(objectpublicationauthoritem_, object.m_publicationAuthor);
stringManager_->setValue(objectversionitem_, object.m_version);
stringManager_->setValue(objectLabrpsversionitem_, object.m_labRPSVersion);


}

ObjectDescription PluginPropertyEditor::GetUserDefinedPhenomenonPluggedObjectDescription(const QString &objectGroup, const QString &objectName)
{
    ObjectDescription pluggedObjectDescription;

    QString pluginName = QString("");
    QString descrip = QString("");
    QString pubTitle = QString("");
    QString pubLink = QString("");
    QString pubAuthor = QString("");
    QString pubDate = QString("");
    QString version = QString("");


    if (objectGroup == LabRPS::objGroupUserDefinedPhenomenonObject)
    {
        if (!PluginManager::GetInstance().GetInstalledPluginsNameMap().empty())
        {
            pluginName = CrpsUserDefinedPhenomenonFactory::GetTobeInstalledObjectsMap()[objectName];
            descrip = CrpsUserDefinedPhenomenonFactory::GetOjectDescriptionMap()[objectName];

            pubTitle = CrpsUserDefinedPhenomenonFactory::GetTitleMap()[objectName];
            pubLink = CrpsUserDefinedPhenomenonFactory::GetLinkMap()[objectName];
            pubAuthor = CrpsUserDefinedPhenomenonFactory::GetAuthorMap()[objectName];
            pubDate = CrpsUserDefinedPhenomenonFactory::GetDateMap()[objectName];
            version = CrpsUserDefinedPhenomenonFactory::GetVersionMap()[objectName];
        }
    }


    if (PluginManager::GetInstance().GetInstalledPluginsNameMap().find(pluginName) != PluginManager::GetInstance().GetInstalledPluginsNameMap().end())
    {
        pluggedObjectDescription.m_pluginName = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetDisplayName();
        pluggedObjectDescription.m_releaseDate = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginReleaseDate();
        pluggedObjectDescription.m_path = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginSubFolder();
        pluggedObjectDescription.m_author = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginAuthor();
        pluggedObjectDescription.m_pluginVersion = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetPluginVersion();
        pluggedObjectDescription.m_labRPSVersion = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetLabRPSVersion();
        pluggedObjectDescription.m_apiVersion = PluginManager::GetInstance().GetInstalledPluginsNameMap()[pluginName]->GetAPIVersion();
        pluggedObjectDescription.m_objectName = objectName;
        pluggedObjectDescription.m_version = version;
        pluggedObjectDescription.m_description = descrip;
        pluggedObjectDescription.m_publicationTitle = pubTitle;
        pluggedObjectDescription.m_publicationLink = pubLink;
        pluggedObjectDescription.m_publicationAuthor = pubAuthor;
        pluggedObjectDescription.m_publicationDate = pubDate;

    }

        return pluggedObjectDescription;
}

QString  PluginPropertyEditor::GetUserDefinedPhenomenonObjectSelectionState(const QString &objectGroup, const QString &objectName, const CRPSUserDefinedPhenomenonSimuData &userDefinedPhenomenonSimuData)
{
    QString yesResult = QString("Yes");
    QString noResult = QString("No");

    if (objectGroup == LabRPS::objGroupUserDefinedPhenomenonObject)
    {
        return objectName == userDefinedPhenomenonSimuData.userDefinedPhenomenon ? yesResult : noResult;
    }

    return noResult;
}

int PluginPropertyEditor::GetNumberOfUserDefinedPhenomenonPlggedObject(const QString &itemText, const QString &parenttext)
{
        std::map<const QString, QString>::iterator it;
        int count = 0;

    if (itemText == LabRPS::objGroupUserDefinedPhenomenonObject)
    {
                 for (it = CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap().begin(); it != CrpsUserDefinedPhenomenonFactory::GetOjectAndPluginMap().end(); ++it)
                {
                        if (it->second == parenttext)
                        {
                                count++;
                        }
                }
                return count;
    }

    return 0;
}
