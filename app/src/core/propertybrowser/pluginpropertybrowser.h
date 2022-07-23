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

#ifndef PLUGINPROPERTYBROWSER_H
#define PLUGINPROPERTYBROWSER_H

#include <QDockWidget>
#include "ApplicationWindow.h"

class Ui_PluginPropertyBrowser;

class PluginPropertyBrowser : public QDockWidget {
  Q_OBJECT
 public:
  PluginPropertyBrowser(QWidget *parent = nullptr, ApplicationWindow *app = nullptr);
  ~PluginPropertyBrowser();

 public slots:
  void populateObjectBrowser(MyWidget *widget);

private slots:
  void showObjectContextMenu(const QPoint &point);

 private:
  ApplicationWindow *app_;
  Ui_PluginPropertyBrowser *ui_;
};

#endif  // PLUGINPROPERTYBROWSER_H
