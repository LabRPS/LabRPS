/***************************************************************************
    File                 : AspectPrivate.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2007 by Knut Franke, Tilman Benkert
    Email (use @ for *)  : knut.franke*gmx.de, thzs*gmx.net
    Description          : Private data managed by AbstractAspect.

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

#include "AbstractAspect.h"
#include "AspectPrivate.h"
#include <QRegExp>
#include <QStringList>

QSettings *AbstractAspect::Private::g_settings = new QSettings();
QHash<QString, QVariant> AbstractAspect::Private::g_defaults;

AbstractAspect::Private::Private(AbstractAspect *owner, const QString &name)
    : d_name(name.isEmpty() ? QString::fromLatin1("1") : name),
      d_caption_spec(QString::fromLatin1("%n%C{ - }%c")),
      d_owner(owner),
      d_parent(0) {
  d_creation_time = QDateTime::currentDateTime();
}

AbstractAspect::Private::~Private() {
  Q_FOREACH (AbstractAspect *child, d_children)
    delete child;
}

void AbstractAspect::Private::addChild(AbstractAspect *child) {
  insertChild(d_children.count(), child);
}

void AbstractAspect::Private::insertChild(int index, AbstractAspect *child) {
  Q_EMIT d_owner->aspectAboutToBeAdded(d_owner, index);
  d_children.insert(index, child);
  // Always remove from any previous parent before adding to a new one!
  // Can't handle this case here since two undo commands have to be created.
  Q_ASSERT(child->d_aspect_private->d_parent == 0);
  child->d_aspect_private->d_parent = d_owner;
  connect(child, SIGNAL(aspectDescriptionAboutToChange(const AbstractAspect *)),
          d_owner,
          SIGNAL(aspectDescriptionAboutToChange(const AbstractAspect *)));
  connect(child, SIGNAL(aspectDescriptionChanged(const AbstractAspect *)),
          d_owner, SIGNAL(aspectDescriptionChanged(const AbstractAspect *)));
  connect(child, SIGNAL(aspectAboutToBeAdded(const AbstractAspect *, int)),
          d_owner, SIGNAL(aspectAboutToBeAdded(const AbstractAspect *, int)));
  connect(child, SIGNAL(aspectAboutToBeRemoved(const AbstractAspect *, int)),
          d_owner, SIGNAL(aspectAboutToBeRemoved(const AbstractAspect *, int)));
  connect(child, SIGNAL(aspectAdded(const AbstractAspect *, int)), d_owner,
          SIGNAL(aspectAdded(const AbstractAspect *, int)));
  connect(child, SIGNAL(aspectRemoved(const AbstractAspect *, int)), d_owner,
          SIGNAL(aspectRemoved(const AbstractAspect *, int)));
  connect(child, SIGNAL(aspectAboutToBeRemoved(const AbstractAspect *)),
          d_owner, SIGNAL(aspectAboutToBeRemoved(const AbstractAspect *)));
  connect(child, SIGNAL(aspectAdded(const AbstractAspect *)), d_owner,
          SIGNAL(aspectAdded(const AbstractAspect *)));
  connect(child, SIGNAL(statusInfo(const QString &)), d_owner,
          SIGNAL(statusInfo(const QString &)));
  Q_EMIT d_owner->aspectAdded(d_owner, index);
  Q_EMIT child->aspectAdded(child);
}

int AbstractAspect::Private::indexOfChild(const AbstractAspect *child) const {
  for (int i = 0; i < d_children.size(); i++)
    if (d_children.at(i) == child) return i;
  return -1;
}

int AbstractAspect::Private::removeChild(AbstractAspect *child) {
  int index = indexOfChild(child);
  Q_ASSERT(index != -1);
  Q_EMIT d_owner->aspectAboutToBeRemoved(d_owner, index);
  Q_EMIT child->aspectAboutToBeRemoved(child);
  d_children.removeAll(child);
  QObject::disconnect(child, 0, d_owner, 0);
  child->d_aspect_private->d_parent = 0;
  Q_EMIT d_owner->aspectRemoved(d_owner, index);
  return index;
}

int AbstractAspect::Private::childCount() const { return d_children.count(); }

AbstractAspect *AbstractAspect::Private::child(int index) {
  Q_ASSERT(index >= 0 && index <= childCount());
  return d_children.at(index);
}

QString AbstractAspect::Private::name() const { return d_name; }

void AbstractAspect::Private::setName(const QString &value) {
  Q_EMIT d_owner->aspectDescriptionAboutToChange(d_owner);
  d_name = value;
  Q_EMIT d_owner->aspectDescriptionChanged(d_owner);
}

QString AbstractAspect::Private::comment() const { return d_comment; }

void AbstractAspect::Private::setComment(const QString &value) {
  Q_EMIT d_owner->aspectDescriptionAboutToChange(d_owner);
  d_comment = value;
  Q_EMIT d_owner->aspectDescriptionChanged(d_owner);
}

QString AbstractAspect::Private::captionSpec() const { return d_caption_spec; }

void AbstractAspect::Private::setCaptionSpec(const QString &value) {
  Q_EMIT d_owner->aspectDescriptionAboutToChange(d_owner);
  d_caption_spec = value;
  Q_EMIT d_owner->aspectDescriptionChanged(d_owner);
}

void AbstractAspect::Private::setCreationTime(const QDateTime &time) {
  d_creation_time = time;
}

int AbstractAspect::Private::indexOfMatchingBrace(const QString &str,
                                                  int start) {
  int result = str.indexOf(QChar::fromLatin1('}'), start);
  if (result < 0) result = start;
  return result;
}

QString AbstractAspect::Private::caption() const {
  QString result = d_caption_spec;
  QRegExp magic(QString::fromLatin1("%(.)"));
  for (int pos = magic.indexIn(result, 0); pos >= 0;
       pos = magic.indexIn(result, pos)) {
    QString replacement;
    int length;
    switch (magic.cap(1).at(0).toLatin1()) {
      case '%':
        replacement = QString::fromLatin1("%");
        length = 2;
        break;
      case 'n':
        replacement = d_name;
        length = 2;
        break;
      case 'c':
        replacement = d_comment;
        length = 2;
        break;
      case 't':
        replacement = d_creation_time.toString();
        length = 2;
        break;
      case 'C':
        length = indexOfMatchingBrace(result, pos) - pos + 1;
        replacement = d_comment.isEmpty() ? QString::fromLatin1("")
                                                                : result.mid(pos + 3, length - 4);
        break;
    }
    result.replace(pos, length, replacement);
    pos += replacement.size();
  }
  return result;
}

QDateTime AbstractAspect::Private::creationTime() const {
  return d_creation_time;
}

QString AbstractAspect::Private::uniqueNameFor(const QString &current_name) const {
  QStringList child_names;
  Q_FOREACH (AbstractAspect *child, d_children)
    child_names << child->name();

  if (!child_names.contains(current_name)) return current_name;

  QString base = current_name;
  int last_non_digit;
  for (last_non_digit = base.size() - 1;
       last_non_digit >= 0 &&
       base[last_non_digit].category() == QChar::Number_DecimalDigit;
       --last_non_digit)
    base.chop(1);
  if (last_non_digit >= 0 &&
      base[last_non_digit].category() != QChar::Separator_Space)
    base.append(QString::fromLatin1(" "));

  int new_nr = current_name.right(current_name.size() - base.size()).toInt();
  QString new_name;
  do
    new_name = base + QString::number(++new_nr);
  while (child_names.contains(new_name));

  return new_name;
}
