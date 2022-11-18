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
