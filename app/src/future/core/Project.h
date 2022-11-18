#ifndef PROJECT_H
#define PROJECT_H

#include "core/future_Folder.h"
#include "core/interfaces.h"

class QString;
class ProjectWindow;
class QAction;
class AbstractScriptingEngine;

//! Represents a LabRPS project.
/**
 * Project manages an undo stack and is responsible for creating ProjectWindow
 * instances
 * as views on itself.
 */
class Project : public future::Folder {
  Q_OBJECT

 public:
  //! MDI subwindow visibility setting
  enum MdiWindowVisibility { folderOnly, folderAndSubfolders, allMdiWindows };

 public:
  Project();
  ~Project();

  //!\name Reimplemented from AbstractAspect
  //@{
  virtual const Project *project() const { return this; }
  virtual Project *project() { return this; }
  virtual QUndoStack *undoStack() const;
  virtual QString path() const { return ""; }
#ifndef LEGACY_CODE_0_2_x
  virtual ProjectWindow *view();
#else
  virtual void *view();
#endif
  virtual QMenu *createContextMenu() const;
  //@}
  virtual QMenu *createFolderContextMenu(const future::Folder *folder) const;

  AbstractScriptingEngine *scriptingEngine() const;

  void setMdiWindowVisibility(MdiWindowVisibility visibility);
  MdiWindowVisibility mdiWindowVisibility() const;
  void setFileName(const QString &file_name);
  QString fileName() const;

  static ConfigPageWidget *makeConfigPage();
  static QString configPageLabel();

  //! \name serialize/deserialize
  //@{
  //! Save as XML
  virtual void save(QXmlStreamWriter *) const;
  //! Load from XML
  virtual bool load(XmlStreamReader *);
  //@}

 private:
  class Private;
  Private *d;

  friend class ProjectConfigPage;
};

#endif  // PROJECT_H
