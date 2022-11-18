#ifndef PROPERTYBROWSER_H
#define PROPERTYBROWSER_H

#include <QDockWidget>
#include "ApplicationWindow.h"

class Ui_PropertyBrowser;

class PropertyBrowser : public QDockWidget {
  Q_OBJECT
 public:
  PropertyBrowser(QWidget *parent = nullptr, ApplicationWindow *app = nullptr);
  ~PropertyBrowser();

 public slots:
  void populateObjectBrowser(MyWidget *widget);

private slots:
  void showObjectContextMenu(const QPoint &point);

 private:
  ApplicationWindow *app_;
  Ui_PropertyBrowser *ui_;
};

#endif  // PROPERTYBROWSER_H
