#include "TeXTableSettings.h"
#include "TeXTableSettingsWidget.h"
#include "TeXTableExportDialog.h"

TeXTableExportDialog::TeXTableExportDialog(QWidget* parent)
    : ExtensibleFileDialog(parent) {
  setWindowTitle(tr("TeX table export dialog"));
  setAcceptMode(QFileDialog::AcceptSave);

  // Create the TeX table settigns widget
  tex_settings_Widget = new TeXTableSettingsWidget(this);

  // Insert the TeX table settigns widget in the dialog layout
  setExtensionWidget(tex_settings_Widget);
}

TeXTableSettings TeXTableExportDialog::tex_TableSettings(void) {
  return tex_settings_Widget->settings();
}
