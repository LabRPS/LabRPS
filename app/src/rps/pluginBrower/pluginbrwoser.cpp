#include "pluginbrwoser.h"
#include "ui_pluginbrwoser.h"

PluginBrwoser::PluginBrwoser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginBrwoser)
{
    ui->setupUi(this);
}

PluginBrwoser::~PluginBrwoser()
{
    delete ui;
}
