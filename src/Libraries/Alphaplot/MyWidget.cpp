/***************************************************************************
    File                 : MyWidget.cpp
    Project              : AlphaPlot
    Description          : MDI window widget
    --------------------------------------------------------------------
    Copyright            : (C) 2006-2009 Knut Franke (knut.franke*gmx.de)
    Copyright            : (C) 2006-2009 Tilman Benkert (thzs*gmx.net)
    Copyright            : (C) 2006-2007 by Ion Vasilief (ion_vasilief*yahoo.fr)
                           (replace * with @ in the email address)

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
#include "PreCompiled.h"

#include "MyWidget.h"

#include <QCloseEvent>
#include <QEvent>
#include <QLocale>
#include <QMessageBox>
#include <QString>
#include <QtDebug>

//#include "Folder.h"

MyWidget::MyWidget(const QString &label, QWidget *parent, const QString name,
                   Qt::WindowFlags f)
    : QMdiSubWindow(parent, f) {
  w_label = label;
  caption_policy = Both;
  askOnClose = true;
  w_status = Normal;
  setObjectName(QString(name));
}

void MyWidget::updateCaption() {
  switch (caption_policy) {
    case Name:
      setWindowTitle(name());
      break;

    case Label:
      if (!windowLabel().isEmpty())
        setWindowTitle(windowLabel());
      else
        setWindowTitle(name());
      break;

    case Both:
      if (!windowLabel().isEmpty())
        setWindowTitle(name() + QString::fromLatin1(" - ") + windowLabel());
      else
        setWindowTitle(name());
      break;
  }
}

void MyWidget::changeEvent(QEvent *event) {
  if (!isHidden() && event->type() == QEvent::WindowStateChange) {
    if (static_cast<QWindowStateChangeEvent *>(event)->oldState() ==
        windowState())
      return;
    if (windowState() & Qt::WindowMinimized)
      w_status = Minimized;
    else if (windowState() & Qt::WindowMaximized)
      w_status = Maximized;
    else
      w_status = Normal;
    Q_EMIT statusChanged(this);
  }
  QMdiSubWindow::changeEvent(event);
}

void MyWidget::closeEvent(QCloseEvent *e) {
  if (askOnClose) {
    switch (QMessageBox::information(this, QString::fromLatin1("AlphaPlot"),
                                     tr("Do you want to hide or delete") +
                                         QString::fromLatin1("<p><b>'") + objectName() + QString::fromLatin1("'</b> ?"),
                                     tr("Delete"), tr("Hide"), tr("Cancel"), 0,
                                     2)) {
      case 0:
        Q_EMIT closedWindow(this);
        e->accept();
        break;

      case 1:
        e->ignore();
        Q_EMIT hiddenWindow(this);
        break;

      case 2:
        e->ignore();
        break;
    }
  } else {
    Q_EMIT closedWindow(this);
    e->accept();
  }
}

QString MyWidget::aspect() {
  QString status = tr("Normal");
  switch (w_status) {
    case Hidden:
      return tr("Hidden");

    case Normal:
      break;

    case Minimized:
      return tr("Minimized");

    case Maximized:
      return tr("Maximized");
  }
  return status;
}

void MyWidget::contextMenuEvent(QContextMenuEvent *event) {
  if (!this->widget()->geometry().contains(event->pos())) {
    Q_EMIT showTitleBarMenu();
    event->accept();
  }
}

void MyWidget::resizeEvent(QResizeEvent *resizeEvent) {
  Q_EMIT geometrychange(this);
  QMdiSubWindow::resizeEvent(resizeEvent);
}

void MyWidget::moveEvent(QMoveEvent *moveEvent) {
  Q_EMIT geometrychange(this);
  QMdiSubWindow::moveEvent(moveEvent);
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
  Q_EMIT mousepressevent(this);
  QMdiSubWindow::mousePressEvent(event);
}

void MyWidget::setStatus(Status status) {
  if (w_status == status) return;

  w_status = status;
  Q_EMIT statusChanged(this);
}

void MyWidget::setHidden() {
  w_status = Hidden;
  Q_EMIT statusChanged(this);
  hide();
}

void MyWidget::setNormal() {
  showNormal();
  w_status = Normal;
  Q_EMIT statusChanged(this);
}

void MyWidget::setMinimized() {
  showMinimized();
  w_status = Minimized;
  Q_EMIT statusChanged(this);
}

void MyWidget::setMaximized() {
  showMaximized();
  w_status = Maximized;
  Q_EMIT statusChanged(this);
}
