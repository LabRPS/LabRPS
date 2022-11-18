#ifndef PROJECT_CONFIG_PAGE_H
#define PROJECT_CONFIG_PAGE_H

#include "ui_ProjectConfigPage.h"
#include "lib/ConfigPageWidget.h"

//! Helper class for Project
class ProjectConfigPage : public ConfigPageWidget {
  Q_OBJECT

 public:
  ProjectConfigPage();

 public slots:
  virtual void apply();

 private:
  Ui::ProjectConfigPage ui;
};

#endif  // PROJECT_CONFIG_PAGE_H
