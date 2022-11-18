#include "MyWidget.h"

#include <QCloseEvent>
#include <QEvent>
#include <QLocale>
#include <QMessageBox>
#include <QString>
#include <QtDebug>

#include "Folder.h"

MyWidget::MyWidget(const QString &label, QWidget *parent, const QString name,
                   Qt::WindowFlags f)
    : QMdiSubWindow(parent, f) {
  w_label = label;
  caption_policy = Both;
  askOnClose = true;
  w_status = Normal;
  setObjectName(QString(name));
}

MyWidget::~MyWidget() {}

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
        setWindowTitle(name() + " - " + windowLabel());
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
    emit statusChanged(this);
  }
  QMdiSubWindow::changeEvent(event);
}

void MyWidget::closeEvent(QCloseEvent *e) {
  if (askOnClose) {
    switch (QMessageBox::information(this, "LabRPS",
                                     tr("Do you want to hide or delete") +
                                         "<p><b>'" + objectName() + "'</b> ?",
                                     tr("Delete"), tr("Hide"), tr("Cancel"), 0,
                                     2)) {
      case 0:
        emit closedWindow(this);
        e->accept();
        break;

      case 1:
        e->ignore();
        emit hiddenWindow(this);
        break;

      case 2:
        e->ignore();
        break;
    }
  } else {
    emit closedWindow(this);
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
    emit showTitleBarMenu();
    event->accept();
  }
}

void MyWidget::resizeEvent(QResizeEvent *resizeEvent) {
  emit geometrychange(this);
  QMdiSubWindow::resizeEvent(resizeEvent);
}

void MyWidget::moveEvent(QMoveEvent *moveEvent) {
  emit geometrychange(this);
  QMdiSubWindow::moveEvent(moveEvent);
}

void MyWidget::mousePressEvent(QMouseEvent *event) {
  emit mousepressevent(this);
  QMdiSubWindow::mousePressEvent(event);
}

void MyWidget::setStatus(Status status) {
  if (w_status == status) return;

  w_status = status;
  emit statusChanged(this);
}

void MyWidget::setHidden() {
  w_status = Hidden;
  emit statusChanged(this);
  hide();
}

void MyWidget::setNormal() {
  showNormal();
  w_status = Normal;
  emit statusChanged(this);
}

void MyWidget::setMinimized() {
  showMinimized();
  w_status = Minimized;
  emit statusChanged(this);
}

void MyWidget::setMaximized() {
  showMaximized();
  w_status = Maximized;
  emit statusChanged(this);
}
