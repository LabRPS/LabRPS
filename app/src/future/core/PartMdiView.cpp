#include "PartMdiView.h"

#include <QCloseEvent>
#include <QMdiArea>
#include <QMenu>

#include "AbstractPart.h"

PartMdiView::PartMdiView(AbstractPart *part, QWidget *embedded_view)
    : QMdiSubWindow(0), d_part(part), d_closing(false), d_status(Closed) {
  setWindowIcon(d_part->icon());
  handleAspectDescriptionChanged(d_part);
  connect(d_part, SIGNAL(aspectDescriptionChanged(const AbstractAspect *)),
          this, SLOT(handleAspectDescriptionChanged(const AbstractAspect *)));
  connect(d_part, SIGNAL(aspectAboutToBeRemoved(const AbstractAspect *)), this,
          SLOT(handleAspectAboutToBeRemoved(const AbstractAspect *)));
  setWidget(embedded_view);
}

void PartMdiView::contextMenuEvent(QContextMenuEvent *event) {
  QMenu *menu = d_part->createContextMenu();
  menu->exec(event->globalPos());
  delete menu;
}

PartMdiView::~PartMdiView() {}

void PartMdiView::handleAspectDescriptionChanged(const AbstractAspect *aspect) {
  if (aspect != d_part) return;
  setWindowTitle(d_part->caption());
  update();
}

void PartMdiView::handleAspectAboutToBeRemoved(const AbstractAspect *aspect) {
  if (aspect != d_part) return;
  d_closing = true;
  close();
}

void PartMdiView::closeEvent(QCloseEvent *event) {
  if (!d_closing) {
    d_closing = true;
    d_part->remove();
    event->accept();
  }
  d_closing = false;

  SubWindowStatus old_status = d_status;
  d_status = Closed;
  emit statusChanged(this, old_status, d_status);
}

void PartMdiView::hideEvent(QHideEvent *event) {
  SubWindowStatus old_status = d_status;
  d_status = Hidden;
  emit statusChanged(this, old_status, d_status);
  event->accept();
}

void PartMdiView::showEvent(QShowEvent *event) {
  SubWindowStatus old_status = d_status;
  d_status = Visible;
  emit statusChanged(this, old_status, d_status);
  event->accept();
}
