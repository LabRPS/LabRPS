#ifndef PLUGINBRWOSER_H
#define PLUGINBRWOSER_H

#include <QDialog>

namespace Ui {
class PluginBrwoser;
}

class PluginBrwoser : public QDialog
{
    Q_OBJECT

public:
    explicit PluginBrwoser(QWidget *parent = nullptr);
    ~PluginBrwoser();

private:
    Ui::PluginBrwoser *ui;
};

#endif // PLUGINBRWOSER_H
