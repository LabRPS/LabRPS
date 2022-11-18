#include "pluginpropertybrowser.h"

#include <QDebug>

#include "MyWidget.h"
#include "core/propertybrowser/ObjectBrowserTreeItemModel.h"
#include "ui_pluginpropertybrowser.h"

PluginPropertyBrowser::PluginPropertyBrowser(QWidget *parent, ApplicationWindow *app)
    : QDockWidget(parent), app_(app), ui_(new Ui_PluginPropertyBrowser) {
  Q_ASSERT(app_);
  ui_->setupUi(this);
  setWindowTitle(tr("Property Browser"));
  setWindowIcon(QIcon());

  ui_->dockWidgetContents->layout()->setContentsMargins(0, 0, 0, 0);
  ui_->objectView->setFrameShape(QFrame::NoFrame);
  ui_->propertyView->setFrameShape(QFrame::NoFrame);
  ui_->objectView->setContextMenuPolicy(Qt::CustomContextMenu);
  ui_->objectView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui_->propertyView->setSelectionMode(QAbstractItemView::SingleSelection);

  ui_->propertyView->setFocusPolicy(Qt::NoFocus);
  connect(ui_->objectView, &QTreeView::customContextMenuRequested, this,
          &PluginPropertyBrowser::showObjectContextMenu);
}

PluginPropertyBrowser::~PluginPropertyBrowser() { delete ui_; }

void PluginPropertyBrowser::populateObjectBrowser(MyWidget *widget) {
  
}

void PluginPropertyBrowser::showObjectContextMenu(const QPoint &point) {
  QModelIndex index = ui_->objectView->indexAt(point);
}
