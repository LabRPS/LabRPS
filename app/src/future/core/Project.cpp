#include "core/Project.h"
#ifndef LEGACY_CODE_0_2_x
#include "core/ProjectWindow.h"
#include "core/ScriptingEngineManager.h"
#endif
#include "core/interfaces.h"
#include "globals.h"
#include "lib/XmlStreamReader.h"
#include "core/ProjectConfigPage.h"
#include <QUndoStack>
#include <QString>
#include <QKeySequence>
#include <QMenu>
#include <QSettings>
#include <QPluginLoader>
#include <QComboBox>
#include <QFile>
#include <QXmlStreamWriter>
#include <QtDebug>

#define NOT_IMPL (QMessageBox::information(0, "info", "not yet implemented"))

class Project::Private {
 public:
  Private()
      : mdi_window_visibility(static_cast<MdiWindowVisibility>(
            Project::global("default_mdi_window_visibility").toInt())),
        primary_view(0),
        scripting_engine(0) {}
  ~Private() {
#ifndef LEGACY_CODE_0_2_x
    delete primary_view;
#endif
  }
  QUndoStack undo_stack;
  MdiWindowVisibility mdi_window_visibility;
#ifndef LEGACY_CODE_0_2_x
  ProjectWindow *primary_view;
#else
  void *primary_view;
#endif
  AbstractScriptingEngine *scripting_engine;
  QString file_name;
};

Project::Project() : future::Folder(tr("Unnamed")), d(new Private()) {
#ifndef LEGACY_CODE_0_2_x
  // TODO: intelligent engine choosing
  Q_ASSERT(ScriptingEngineManager::instance()->engineNames().size() > 0);
  QString engine_name = ScriptingEngineManager::instance()->engineNames()[0];
  d->scripting_engine = ScriptingEngineManager::instance()->engine(engine_name);
#endif
}

Project::~Project() { delete d; }

QUndoStack *Project::undoStack() const { return &d->undo_stack; }

#ifndef LEGACY_CODE_0_2_x
ProjectWindow *Project::view() {
  if (!d->primary_view) d->primary_view = new ProjectWindow(this);
  return d->primary_view;
#else
void *Project::view() {
  return NULL;
#endif
}

QMenu *Project::createContextMenu() const {
#ifndef LEGACY_CODE_0_2_x
  return const_cast<Project *>(this)->view()->createContextMenu();
#else
  return NULL;
#endif
}

QMenu *Project::createFolderContextMenu(const future::Folder *folder) const {
#ifndef LEGACY_CODE_0_2_x
  return const_cast<Project *>(this)->view()->createFolderContextMenu(folder);
#else
  Q_UNUSED(folder)
  return NULL;
#endif
}

void Project::setMdiWindowVisibility(MdiWindowVisibility visibility) {
  d->mdi_window_visibility = visibility;
#ifndef LEGACY_CODE_0_2_x
  view()->updateMdiWindowVisibility();
#endif
}

Project::MdiWindowVisibility Project::mdiWindowVisibility() const {
  return d->mdi_window_visibility;
}

AbstractScriptingEngine *Project::scriptingEngine() const {
  return d->scripting_engine;
}

/* ================== static methods ======================= */
ConfigPageWidget *Project::makeConfigPage() { return new ProjectConfigPage(); }

QString Project::configPageLabel() { return QObject::tr("General"); }

void Project::setFileName(const QString &file_name) {
  d->file_name = file_name;
}

QString Project::fileName() const { return d->file_name; }

void Project::save(QXmlStreamWriter *writer) const {
  writer->writeStartDocument();
  writer->writeStartElement("LabRPS_project");
  writer->writeAttribute("version", QString::number(LabRPS::version()));
  // TODO: write project attributes
  writer->writeStartElement("project_root");
  future::Folder::save(writer, false);
  writer->writeEndElement();  // "project_root"
  writer->writeEndElement();  // "LabRPS_project"
  writer->writeEndDocument();
}

bool Project::load(XmlStreamReader *reader) {
  while (!(reader->isStartDocument() || reader->atEnd())) reader->readNext();
  if (!(reader->atEnd())) {
    if (!reader->skipToNextTag()) return false;

    if (reader->name() == "LabRPS_project") {
      bool ok = true;
      // int version = reader->readAttributeInt("version", &ok);
      if (!ok) {
        reader->raiseError(tr("invalid or missing project version"));
        return false;
      }

      // version dependent staff goes here

      while (!reader->atEnd()) {
        reader->readNext();

        if (reader->isEndElement()) break;

        if (reader->isStartElement()) {
          if (reader->name() == "project_root") {
            if (!reader->skipToNextTag()) return false;
            if (!future::Folder::load(reader)) return false;
            if (!reader->skipToNextTag()) return false;
            Q_ASSERT(reader->isEndElement() &&
                     reader->name() == "project_root");
          } else  // unknown element
          {
            reader->raiseWarning(
                tr("unknown element '%1'").arg(reader->name().toString()));
            if (!reader->skipToEndElement()) return false;
          }
        }
      }
    } else  // no project element
      reader->raiseError(tr("no LabRPS_project element found"));
  } else  // no start document
    reader->raiseError(tr("no valid XML document found"));

  return !reader->hasError();
}
