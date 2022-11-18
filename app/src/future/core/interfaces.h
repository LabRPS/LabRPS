#ifndef INTERFACES_H
#define INTERFACES_H

#include "lib/ConfigPageWidget.h"
#include "core/AbstractAspect.h"
#include "lib/XmlStreamReader.h"

#include <QtPlugin>

class AbstractPart;
class QAction;
class QMenu;
class ProjectWindow;
class AbstractFilter;
class AbstractImportFilter;
class AbstractExportFilter;
class ActionManager;

//! Factory for AbstractPart objects.
class PartMaker {
 public:
  virtual ~PartMaker() {}
  //! The factory method.
  virtual AbstractPart *makePart() = 0;
  //! The action to be used for making new parts.
  /**
   * The caller takes care of connecting the action. If the parent argument is
   * zero, it
   * also recieves ownership of the action.
   * Implementations should only set things like name and icon.
   */
  virtual QAction *makeAction(QObject *parent) = 0;
};

Q_DECLARE_INTERFACE(PartMaker, "net.sf.LabRPS.partmaker/0.1")

//! Factory for filters.
/**
 * A FilterMaker introduces one or more filters to the kernel.
 */
class FilterMaker {
 public:
  virtual ~FilterMaker() {}
  virtual AbstractFilter *makeFilter(int id = 0) = 0;
  virtual int filterCount() const { return 1; }
  virtual QAction *makeAction(QObject *parent, int id = 0) = 0;
};

Q_DECLARE_INTERFACE(FilterMaker, "net.sf.LabRPS.filtermaker/0.1")

//! Factory for import/export filters.
class FileFormat {
 public:
  virtual ~FileFormat() {}
  virtual AbstractImportFilter *makeImportFilter() = 0;
  virtual AbstractExportFilter *makeExportFilter() = 0;
};

Q_DECLARE_INTERFACE(FileFormat, "net.sf.LabRPS.fileformat/0.1")

//! A module (typically a PartMaker) that has an ActionManager
class ActionManagerOwner {
 public:
  //! Return the action manager of the module
  virtual ActionManager *actionManager() = 0;
  //! Method that contains initialization that has to be done after loading the
  //! plugin
  virtual void initActionManager() {}
};

Q_DECLARE_INTERFACE(ActionManagerOwner,
                    "net.sf.LabRPS.actionmanagerowner/0.1")

//! A module with application-wide settings
class ConfigPageMaker {
 public:
  virtual ConfigPageWidget *makeConfigPage() = 0;
  virtual QString configPageLabel() = 0;
  virtual void loadSettings() = 0;
  virtual void saveSettings() = 0;
  // TODO (maybe): icons instead of tabs to select the pages
  //		virtual QIcon icon() = 0;
};

Q_DECLARE_INTERFACE(ConfigPageMaker, "net.sf.LabRPS.configpagemaker/0.1")

//! Factory that creates an aspect out of an XML element.
class XmlElementAspectMaker {
 public:
  virtual ~XmlElementAspectMaker() {}
  //! Determine whether the loader can handle the given element.
  virtual bool canCreate(const QString &element_name) = 0;
  //! The factory method.
  virtual AbstractAspect *createAspectFromXml(XmlStreamReader *reader) = 0;
};

Q_DECLARE_INTERFACE(XmlElementAspectMaker,
                    "net.sf.LabRPS.xmlelementaspectmaker/0.1")

#endif  // INTERFACES_H
