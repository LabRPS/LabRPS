#ifndef TEX_TABLE_EXPORT_DIALOG_H
#define TEX_TABLE_EXPORT_DIALOG_H

#include "ui/ExtensibleFileDialog.h"

class TeXTableSettingsWidget;
class TeXTableSettings;

//! TeXTableExportDialog
/*
 * The TeXTableExportDialog class is a dialog window which that allow users to
 * select
 * the TeX table parameters and file in wich the table data will be exported in
 * the TeX format.
 */
class TeXTableExportDialog : public ExtensibleFileDialog {
  Q_OBJECT

 public:
  TeXTableExportDialog(QWidget* parent = nullptr);
  //! Returns the TeX table settings choosed by the user
  TeXTableSettings tex_TableSettings(void);

 private:
  //! tex_settings_Widget is a pointer to the a TeX table settings widget.
  /**
   *  The TeX table settings widget is inserted in the current layout.
   */
  TeXTableSettingsWidget* tex_settings_Widget;
};

#endif  // TEX_TABLE_EXPORT_DIALOG_H
