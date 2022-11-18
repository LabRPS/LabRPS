#include "AbstractPart.h"
#include "PartMdiView.h"
#include <QMenu>
#include <QStyle>

PartMdiView* AbstractPart::mdiSubWindow() {
  if (!d_mdi_window) d_mdi_window = new PartMdiView(this, view());
  return d_mdi_window;
}

QMenu* AbstractPart::createContextMenu() const {
  QMenu* menu = AbstractAspect::createContextMenu();
  Q_ASSERT(menu);
  const QStyle* widget_style = d_mdi_window->style();

  QAction* action_temp;
  if (d_mdi_window->windowState() &
      (Qt::WindowMinimized | Qt::WindowMaximized)) {
    action_temp =
        menu->addAction(tr("&Restore"), d_mdi_window, SLOT(showNormal()));
    action_temp->setIcon(
        widget_style->standardIcon(QStyle::SP_TitleBarNormalButton));
  }
  if (!(d_mdi_window->windowState() & Qt::WindowMinimized)) {
    action_temp =
        menu->addAction(tr("Mi&nimize"), d_mdi_window, SLOT(showMinimized()));
    action_temp->setIcon(
        widget_style->standardIcon(QStyle::SP_TitleBarMinButton));
  }
  if (!(d_mdi_window->windowState() & Qt::WindowMaximized)) {
    action_temp =
        menu->addAction(tr("Ma&ximize"), d_mdi_window, SLOT(showMaximized()));
    action_temp->setIcon(
        widget_style->standardIcon(QStyle::SP_TitleBarMaxButton));
  }

  return menu;
}
