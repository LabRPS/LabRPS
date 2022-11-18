#include "OpenProjectDialog.h"
#include "ApplicationWindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

OpenProjectDialog::OpenProjectDialog(QWidget *parent, bool extended,
                                     Qt::WindowFlags flags)
    : ExtensibleFileDialog(parent, extended, flags) {
  setWindowTitle(tr("Open Project"));
  setFileMode(ExistingFile);
  QStringList filters;
  filters << tr("LabRPS project") + " (*.rps)"
          << tr("Compressed LabRPS project") + " (*.rps.gz)"
          << tr("Backup files") + " (*.rps~ *.rps.gz~)"
          //<< tr("Python Source") + " (*.py *.PY)"
          << tr("All files") + " (*)";
  setNameFilters(filters);

  QWidget *advanced_options = new QWidget();
  QHBoxLayout *advanced_layout = new QHBoxLayout();
  advanced_options->setLayout(advanced_layout);
  advanced_layout->addWidget(new QLabel(tr("Open As")));
  d_open_mode = new QComboBox();
  // Important: Keep this is sync with enum OpenMode.
  d_open_mode->addItem(tr("New Project Window"));
  d_open_mode->addItem(tr("New Folder"));
  advanced_layout->addWidget(d_open_mode);
  setExtensionWidget(advanced_options);

  connect(this, &OpenProjectDialog::filterSelected, this,
          &OpenProjectDialog::updateAdvancedOptions);
  updateAdvancedOptions(selectedNameFilter());
}

void OpenProjectDialog::updateAdvancedOptions(const QString &filter) {
  if (filter.contains("*.ogm") || filter.contains("*.ogw")) {
    d_extension_toggle->setChecked(false);
    d_extension_toggle->setEnabled(false);
    return;
  }
  d_extension_toggle->setEnabled(true);
}

void OpenProjectDialog::closeEvent(QCloseEvent *e) {
  if (isExtendable()) {
    ApplicationWindow *app = (ApplicationWindow *)this->parent();
    if (app) app->d_extended_open_dialog = this->isExtended();
  }

  e->accept();
}
