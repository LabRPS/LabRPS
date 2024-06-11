/***************************************************************************
    File                 : ActionManager.cpp
    Project              : AlphaPlot
    Description          : Manages QActions and their shortcuts
    --------------------------------------------------------------------
    Copyright            : (C) 2008-2009 Tilman Benkert (thzs*gmx.net)
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

#include "ActionManager.h"
#include <QMutableMapIterator>

ActionManager::ActionManager() {}

ActionManager::~ActionManager() {
  QMutableMapIterator<QString, QList<QAction *> *> it(d_action_registry);
  while (it.hasNext()) delete it.next().value();
}

void ActionManager::addAction(QAction *action, const QString &internal_name) {
  if (!action) return;
  if (!d_action_registry.contains(internal_name))  // new internal name
  {
    QList<QAction *> *list = new QList<QAction *>();
    list->append(action);
    d_action_registry.insert(internal_name, list);
    d_action_shortcuts.insert(internal_name, action->shortcuts());
    connect(action, SIGNAL(destroyed(QObject *)), this,
            SLOT(removeAction(QObject *)));
  } else {
    QList<QAction *> *list = d_action_registry.value(internal_name);
    if (!list->contains(action)) {
      list->append(action);
      connect(action, SIGNAL(destroyed(QObject *)), this,
              SLOT(removeAction(QObject *)));
    }
    QList<QKeySequence> sequences = d_action_shortcuts.value(internal_name);
    action->setShortcuts(sequences);
  }
  d_action_texts.insert(internal_name, action->text());
}

QList<QKeySequence> ActionManager::shortcuts(
    const QString &internal_name) const {
  if (!d_action_shortcuts.contains(internal_name)) return QList<QKeySequence>();

  return d_action_shortcuts.value(internal_name);
}

void ActionManager::setShortcuts(const QString &internal_name,
                                 const QList<QKeySequence> &sequences) {
  if (!d_action_registry.contains(internal_name))  // new internal name
  {
    QList<QAction *> *list = new QList<QAction *>();
    d_action_registry.insert(internal_name, list);
    d_action_shortcuts.insert(internal_name, sequences);
  } else {
    QList<QAction *> *list = d_action_registry.value(internal_name);
    Q_FOREACH (QAction *action, *list)
      action->setShortcuts(sequences);
    d_action_shortcuts.insert(internal_name, sequences);
  }
}

QString ActionManager::actionText(const QString &internal_name) const {
  if (!d_action_registry.contains(internal_name)) return QString();

  QList<QAction *> *list = d_action_registry.value(internal_name);
  if (list->isEmpty()) {
    if (d_action_texts.contains(internal_name))
      return d_action_texts.value(internal_name);
    else
      return internal_name;
  }
  return list->last()->text();
}

QList<QString> ActionManager::internalNames() const {
  return d_action_registry.keys();
}

void ActionManager::removeAction(QObject *action) {
  removeAction(static_cast<QAction *>(action));
}

void ActionManager::removeAction(QAction *action) {
  if (!action) return;

  disconnect(action, SIGNAL(destroyed(QObject *)), this,
             SLOT(removeAction(QObject *)));

  QMutableMapIterator<QString, QList<QAction *> *> it(d_action_registry);
  while (it.hasNext()) {
    it.next();
    if (it.value()->contains(action)) {
      d_action_texts.insert(it.key(), action->text());
      it.value()->removeAll(action);
    }
  }
}
