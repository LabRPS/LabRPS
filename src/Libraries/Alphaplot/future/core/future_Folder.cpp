/***************************************************************************
    File                 : Folder.cpp
    Project              : AlphaPlot
    Description          : Folder in a project
    --------------------------------------------------------------------
    Copyright            : (C) 2007 Tilman Benkert (thzs*gmx.net)
    Copyright            : (C) 2007 Knut Franke (knut.franke*gmx.de)
                           (replace * with @ in the email addresses)

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#include "Precompiled.h"

#include "future/core/future_Folder.h"
#include "future/core/column/Column.h"
#include "future/lib/XmlStreamReader.h"
#include "Project.h"
#include <QApplication>
#include <QIcon>
#include <QPluginLoader>
#include <QStyle>
#include <QXmlStreamWriter>
#include <QtDebug>
#include "future/core/interfaces.h"

namespace Gui{
FolderViewProvider::FolderViewProvider(const QString &name) : AbstractAspect(name) {}

FolderViewProvider::~FolderViewProvider() {}

QIcon FolderViewProvider::icon() const {
  QIcon result;
  result.addFile(QString::fromLatin1(":icons/common/22/folder-closed.png"), QSize(), QIcon::Normal,
                 QIcon::Off);
  result.addFile(QString::fromLatin1(":icons/common/22/folder-open.png"), QSize(), QIcon::Normal,
                 QIcon::On);
  return result;
}

QMenu *FolderViewProvider::createContextMenu() const {
  if (project()) return project()->createFolderContextMenu(this);
  return nullptr;
}

void FolderViewProvider::save(QXmlStreamWriter *writer, bool) const {
  writer->writeStartElement(QString::fromLatin1("folder"));
  writeBasicAttributes(writer);
  writeCommentElement(writer);

  int child_count = childCount();
  for (int i = 0; i < child_count; i++) {
    writer->writeStartElement(QString::fromLatin1("child_aspect"));
    child(i)->save(writer, false);
    writer->writeEndElement();  // "child_aspect"
  }
  writer->writeEndElement();  // "folder"
}

bool FolderViewProvider::load(XmlStreamReader *reader) {
  if (reader->isStartElement() && reader->name() == QString::fromLatin1("folder")) {
    setComment(QString::fromLatin1(""));
    removeAllChildAspects();

    if (!readBasicAttributes(reader)) return false;

    // read child elements
    while (!reader->atEnd()) {
      reader->readNext();

      if (reader->isEndElement()) break;

      if (reader->isStartElement()) {
        if (reader->name() == QString::fromLatin1("comment")) {
          if (!readCommentElement(reader)) return false;
        } else if (reader->name() == QString::fromLatin1("child_aspect")) {
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

bool FolderViewProvider::readChildAspectElement(XmlStreamReader *reader) {
  bool loaded = false;
  Q_ASSERT(reader->isStartElement() && reader->name() == QString::fromLatin1("child_aspect"));

  if (!reader->skipToNextTag()) return false;
  if (reader->isEndElement() && reader->name() == QString::fromLatin1("child_aspect"))
    return true;  // empty element tag
  QString element_name = reader->name().toString();
  if (element_name == QString::fromLatin1("folder")) {
      FolderViewProvider*folder = new FolderViewProvider(tr("Folder %1").arg(1));
    if (!folder->load(reader)) {
      delete folder;
      return false;
    }
    addChild(folder);
    loaded = true;
  } else if (element_name == QString::fromLatin1("column")) {
    Column *column = new Column(tr("Column %1").arg(1), AlphaPlot::Text);
    if (!column->load(reader)) {
      delete column;
      return false;
    }
    addChild(column);
    loaded = true;
  } else {
    Q_FOREACH (QObject *plugin, QPluginLoader::staticInstances()) {
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
  Q_ASSERT(reader->isEndElement() && reader->name() == QString::fromLatin1("child_aspect"));
  return !reader->hasError();

    return false;
}

}  // namespace future
