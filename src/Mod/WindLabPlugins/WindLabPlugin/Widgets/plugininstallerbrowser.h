#ifndef PLUGININSTALLERBROWSER_H
#define PLUGININSTALLERBROWSER_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class PluginInstallerBrowser;
}

class PluginInstallerBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit PluginInstallerBrowser(QWidget *parent = nullptr);
    ~PluginInstallerBrowser();

private:
    Ui::PluginInstallerBrowser *ui;

private Q_SLOTS:
  void install();
  void uninstall();
  void modify();
  void close();
  void refresh();
  void updateButton();
  void fillLocalPluginsList();
  void fillOnlinePluginsList();
//   void receiveListWidget(QListWidget *list);

public:
bool pluginInstaled;
int pluginInstallationType;

};

#endif // PLUGININSTALLERBROWSER_H
