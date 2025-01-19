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
    explicit PluginInstallerBrowser(const QString& workbenchName, QWidget *parent = nullptr);
    ~PluginInstallerBrowser();

private:
    Ui::PluginInstallerBrowser *ui;

private Q_SLOTS:
  void install();
  void uninstall();
  void modify();
  void close();
  void help();
  void updateButton();
  void fillLocalPluginsList(const QString& workbenchName);
  void fillOnlinePluginsList();
//   void receiveListWidget(QListWidget *list);

public:
bool pluginInstaled;
int pluginInstallationType;

private:
    QString _workbenchName;

};

#endif // PLUGININSTALLERBROWSER_H
