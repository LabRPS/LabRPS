#ifndef GENERALAPPREANCESETTINGS_H
#define GENERALAPPREANCESETTINGS_H

#include "SettingsPage.h"

class Ui_GeneralAppreanceSettings;
class QLabel;
class QToolButton;
class ColorLabel;

class GeneralAppreanceSettings : public SettingsPage {
  Q_OBJECT

 public:
  explicit GeneralAppreanceSettings(SettingsDialog *dialog);
  ~GeneralAppreanceSettings();

  void Load();
  void LoadDefault();
  void Save();
  bool settingsChangeCheck();

 signals:
  void generalappreancesettingsupdate();

 private:
  void setupColorButton(QToolButton *button);
  void pickColor(ColorLabel *label);
  void loadQsettingsValues();
  Ui_GeneralAppreanceSettings *ui;
  QString appstyle_;
  int colorscheme_;
  bool customcolors_;
  QColor workspacecolor_;
  QColor panelcolor_;
  QColor paneltextcolor_;

 private slots:
  void stylePreview(const QString &style);
  void colorStylePreview(int index);
};

#endif  // GENERALAPPREANCESETTINGS_H
