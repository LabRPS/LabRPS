#ifndef TEX_TABLE_SETTINGS_WIDGET_H
#define TEX_TABLE_SETTINGS_WIDGET_H

#include <QWidget>

class TeXTableSettings;
class QCheckBox;
class QRadioButton;

//! TeXTableSettingsWidget class
/**
 * The TeXTableSettingsWidget is a simple widget which provides the possibility
 * to
 * choose TeX table parameters. It can be inserted into the other
 * widgets( dialogs ) layout, for example, in the TeX table export dialog.
 */
class TeXTableSettingsWidget : public QWidget {
  Q_OBJECT

 public:
  TeXTableSettingsWidget(QWidget* parent = nullptr);
  //! Return the parameters settings of the TeX table
  TeXTableSettings settings(void);
  //! Sets the all parameters settings of the TeX table
  void setSettings(TeXTableSettings& settings);

 private:
  QCheckBox* with_caption_CB;
  QCheckBox* with_labels_CB;
  QRadioButton* align_left_RB;
  QRadioButton* align_center_RB;
  QRadioButton* align_right_RB;
};

#endif  // TEX_TABLE_SETTINGS_WIDGET_H
