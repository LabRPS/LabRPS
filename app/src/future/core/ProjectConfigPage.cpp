#include "ProjectConfigPage.h"
#include "Project.h"

ProjectConfigPage::ProjectConfigPage() {
  ui.setupUi(this);
  ui.default_subwindow_visibility_combobox->setCurrentIndex(
      Project::global("default_mdi_window_visibility").toInt());
  // TODO: set the ui according to the global settings in Project::Private
}

void ProjectConfigPage::apply() {
  int index = ui.default_subwindow_visibility_combobox->currentIndex();
  switch (index) {
    case 0:
    case 1:
    case 2:
      Project::setGlobal("default_mdi_window_visibility", index);
      break;
  }
  // TODO: read settings from ui and change them in Project::Private
}
