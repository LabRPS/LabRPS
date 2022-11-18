#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

class QLabel;
class SettingsDialog;

class SettingsPage : public QWidget {
  Q_OBJECT

 public:
  SettingsPage(SettingsDialog* dialog = nullptr);

  // Return false to grey out the page's item in the list.
  virtual bool IsEnabled() const { return true; }

  // Load is called when the dialog is shown, Save when the user clicks
  // Apply, & Cancel when the user clicks on Cancel
  virtual void Load() = 0;
  virtual void LoadDefault() = 0;
  virtual void Save() = 0;
  virtual void Cancel() {}
  virtual bool settingsChangeCheck() = 0;

  // The dialog that this page belongs to.
  SettingsDialog* dialog() const { return dialog_; }
  void setTitle(QLabel *titleLabel, QString title);
  QString getTitle();

 protected:
  bool settingsChanged();

 private:
  SettingsDialog* dialog_;
  QString title_;
};

#endif  // SETTINGSPAGE_H
