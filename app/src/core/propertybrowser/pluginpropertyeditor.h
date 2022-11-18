#ifndef PLUGINPROPERTYEDITOR_H
#define PLUGINPROPERTYEDITOR_H

#include <QDockWidget>

#include "ApplicationWindow.h"
#include "MyTreeWidget.h"
#include "ObjectDescription.h"


class Ui_PluginPropertyEditor;
class QSplitter;
class MyWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QtAbstractPropertyBrowser;
class CPluginDescription;

// Property
class QtProperty;
class QtBoolPropertyManager;
class QtIntPropertyManager;
class QtDoublePropertyManager;
class QtStringPropertyManager;
class QtEnumPropertyManager;
class QtGroupPropertyManager;
class QtDateTimePropertyManager;
class QtCheckBoxFactory;
class QtSpinBoxFactory;
class QtDoubleSpinBoxFactory;
class QtLineEditFactory;
class QtEnumEditorFactory;
class QtDateTimeEditFactory;


class PluginPropertyEditor : public QDockWidget {
  Q_OBJECT
 public:
  PluginPropertyEditor(QWidget *parent = nullptr, ApplicationWindow *app = nullptr);
  ~PluginPropertyEditor();
  MyTreeWidget *getObjectBrowser();

 private slots:
  void valueChange(QtProperty *prop, const bool value);
  void valueChange(QtProperty *prop, const double &value);
  void valueChange(QtProperty *prop, const QString &value);
  void valueChange(QtProperty *prop, const int value);
  void enumValueChange(QtProperty *prop, const int value);
  void datetimeValueChange(QtProperty *prop, const QDateTime &datetime);

  void selectObjectItem(QTreeWidgetItem *item);
  void seaLabSelectObjectItem(QTreeWidgetItem *item);
  void seismicLabSelectObjectItem(QTreeWidgetItem *item);

  void objectschanged();

  // windLab
    void WindLabPluginPropertyBlock(CPluginDescription *description);
    void WindLabParentObjectPropertyBlock(const QString &name, const int &number);
    void WindLabObjectPropertyBlock(const QString &objectGroup, const ObjectDescription &object); 
    ObjectDescription GetWindLabPluggedObjectDescription(const QString &itemText, const QString &objectName);
    QString  GetWindLabObjectSelectionState(const QString &objectGroup, const QString &objectName, const CRPSWindLabsimuData &windLabsimuData);
    int GetNumberOfWindLabPlggedObject(const QString &objectGroup, const QString &parenttext);
    void windLabSelectObjectItem(QTreeWidgetItem *item);

// userDefinedPhenomenon
    void UserDefinedPhenomenonPluginPropertyBlock(CPluginDescription *description);
    void UserDefinedPhenomenonParentObjectPropertyBlock(const QString &name, const int &number);
    void UserDefinedPhenomenonObjectPropertyBlock(const QString &objectGroup, const ObjectDescription &object); 
    ObjectDescription GetUserDefinedPhenomenonPluggedObjectDescription(const QString &itemText, const QString &objectName);
    QString  GetUserDefinedPhenomenonObjectSelectionState(const QString &objectGroup, const QString &objectName, const CRPSUserDefinedPhenomenonSimuData &userDefinedPhenomenonSimuData);
    int GetNumberOfUserDefinedPhenomenonPlggedObject(const QString &objectGroup, const QString &parenttext);
    void userDefinedPhenomenonSelectObjectItem(QTreeWidgetItem *item);


 signals:

 public slots:
  void populateObjectBrowser(MyWidget *widget);
  
  //WindLab
  void windLabPopulateObjectBrowser(MyWidget *widget);
  
  //SeaLab
  void seaLabPopulateObjectBrowser(MyWidget *widget);
  
  //SeismicLab
  void seismicLabPopulateObjectBrowser(MyWidget *widget);

  //UserDefinedPhenomenon
  void userDefinedPhenomenonPopulateObjectBrowser(MyWidget *widget);



 private:
  void setObjectPropertyId();
  void blockManagers(bool value);

 private:
  ApplicationWindow *app_;
  Ui_PluginPropertyEditor *ui_;
  QSplitter *splitter_;
  MyTreeWidget *objectbrowser_;
  QtAbstractPropertyBrowser *propertybrowser_;
  QList<QTreeWidgetItem *> objectitems_;
  QWidget *previouswidget_;

  // Property
  QtGroupPropertyManager *groupManager_;
  QtBoolPropertyManager *boolManager_;
  QtIntPropertyManager *intManager_;
  QtDoublePropertyManager *doubleManager_;
  QtStringPropertyManager *stringManager_;
  QtEnumPropertyManager *enumManager_;
  QtDateTimePropertyManager *datetimeManager_;

  // Property Widget Factory
  QtCheckBoxFactory *checkBoxFactory_;
  QtSpinBoxFactory *spinBoxFactory_;
  QtDoubleSpinBoxFactory *doubleSpinBoxFactory_;
  QtEnumEditorFactory *comboBoxFactory_;
  QtDateTimeEditFactory *datetimeFactory_;
  QtLineEditFactory *lineEditFactory_;

  // plugin property
  QtProperty *pluginfileitem_;
  QtProperty *pluginnameitem_;
  QtProperty *plugintypeitem_;
  QtProperty *pluginreleasedateitem_;
  QtProperty *pluginauthorsitem_;
  QtProperty *pluginversionitem_;
  QtProperty *pluginstatusitem_;
  QtProperty *plugindescriptionitem_;

  // object parent
  QtProperty *parentobjectnameitem_;
  QtProperty *parentobjectnumberofobjectitem_;

  // object property
  QtProperty *objecttypeitem_;
  QtProperty *objectnameitem_;
  QtProperty *objectselecteditem_;
  QtProperty *objectpluginitem_;
  QtProperty *objectAuthoritem_;
  QtProperty *objectpathitem_;
  QtProperty *objectpluginversionitem_;
  QtProperty *objectLabrpsversionitem_;
  QtProperty *objectapiversionitem_;
  QtProperty *objectreleasedateitem_;
  QtProperty *objectdescriptionitem_;
  QtProperty *objectpublicationtitleitem_;
  QtProperty *objectlinktopublicationitem_;
  QtProperty *objectpublicationdateitem_;
  QtProperty *objectpublicationauthoritem_;
  QtProperty *objectversionitem_;

};

#endif  // PLUGINPROPERTYEDITOR_H
