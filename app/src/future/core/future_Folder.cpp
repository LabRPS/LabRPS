#include "core/future_Folder.h"
#include "core/Project.h"
#include "core/column/Column.h"
#include "lib/XmlStreamReader.h"

#include <QApplication>
#include <QIcon>
#include <QPluginLoader>
#include <QStyle>
#include <QXmlStreamWriter>
#include <QtDebug>

namespace future {
Folder::Folder(const QString &name) : AbstractAspect(name) {}

Folder::~Folder() {}

QIcon Folder::icon() const {
  QIcon result;
  result.addFile(":icons/common/22/folder-closed.png", QSize(), QIcon::Normal,
                 QIcon::Off);
  result.addFile(":icons/common/22/folder-open.png", QSize(), QIcon::Normal,
                 QIcon::On);
  return result;
}

QMenu *Folder::createContextMenu() const {
  if (project()) return project()->createFolderContextMenu(this);
  return nullptr;
}

void Folder::save(QXmlStreamWriter *writer, bool) const {
  writer->writeStartElement("folder");
  writeBasicAttributes(writer);
  writeCommentElement(writer);

  int child_count = childCount();
  for (int i = 0; i < child_count; i++) {
    writer->writeStartElement("child_aspect");
    child(i)->save(writer, false);
    writer->writeEndElement();  // "child_aspect"
  }
  writer->writeEndElement();  // "folder"
}

bool Folder::load(XmlStreamReader *reader) {
  if (reader->isStartElement() && reader->name() == "folder") {
    setComment("");
    removeAllChildAspects();

    if (!readBasicAttributes(reader)) return false;

    // read child elements
    while (!reader->atEnd()) {
      reader->readNext();

      if (reader->isEndElement()) break;

      if (reader->isStartElement()) {
        if (reader->name() == "comment") {
          if (!readCommentElement(reader)) return false;
        } else if (reader->name() == "child_aspect") {
          if (!readChildAspectElement(reader)) return false;
        } else  // unknown element
        {
          reader->raiseWarning(
              tr("unknown element '%1'").arg(reader->name().toString()));
          if (!reader->skipToEndElement()) return false;
        }
      }
    }
  } else  // no folder element
    reader->raiseError(tr("no folder element found"));

  return !reader->hasError();
}

bool Folder::readChildAspectElement(XmlStreamReader *reader) {
  bool loaded = false;
  Q_ASSERT(reader->isStartElement() && reader->name() == "child_aspect");

  if (!reader->skipToNextTag()) return false;
  if (reader->isEndElement() && reader->name() == "child_aspect")
    return true;  // empty element tag
  QString element_name = reader->name().toString();
  if (element_name == "folder") {
    Folder *folder = new Folder(tr("Folder %1").arg(1));
    if (!folder->load(reader)) {
      delete folder;
      return false;
    }
    addChild(folder);
    loaded = true;
  } else if (element_name == "column") {
    Column *column = new Column(tr("Column %1").arg(1), LabRPS::Text);
    if (!column->load(reader)) {
      delete column;
      return false;
    }
    addChild(column);
    loaded = true;
  } else {
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
      XmlElementAspectMaker *maker =
          qobject_cast<XmlElementAspectMaker *>(plugin);
      if (maker && maker->canCreate(element_name)) {
        AbstractAspect *aspect = maker->createAspectFromXml(reader);
        if (aspect) {
          addChild(aspect);
          loaded = true;
          break;
        } else {
          reader->raiseError(tr("creation of aspect from element '%1' failed")
                                 .arg(element_name));
          return false;
        }
      }
    }
  }
  if (!loaded) {
    reader->raiseWarning(
        tr("no plugin to load element '%1' found").arg(element_name));
    if (!reader->skipToEndElement()) return false;
  }
  if (!reader->skipToNextTag()) return false;
  Q_ASSERT(reader->isEndElement() && reader->name() == "child_aspect");
  return !reader->hasError();
}

}  // namespace future
