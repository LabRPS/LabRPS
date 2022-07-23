/* This file is part of LabRPS.
   Copyright 2022, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   LabRPS is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   LabRPS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with LabRPS.  If not, see <http://www.gnu.org/licenses/>.

   Description : PluginPropertyBrowser */

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
