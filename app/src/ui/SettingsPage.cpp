#include "SettingsPage.h"

#include <QLabel>
#include <QMessageBox>

#include "SettingsDialog.h"

SettingsPage::SettingsPage(SettingsDialog* dialog)
    : QWidget(dialog), dialog_(dialog) {}

void SettingsPage::setTitle(QLabel* titleLabel, QString title) {
  if (!titleLabel) return;

  title_ = title;
  QFont font = titleLabel->font();
  font.setItalic(true);

  titleLabel->setStyleSheet(
      "QLabel {padding-left: 5px;"
      " padding-right: 5px;"
      " padding-top: 5px;"
      " padding-bottom: 5px }");
  titleLabel->setFont(font);
  titleLabel->setText(title_);
}

bool SettingsPage::settingsChanged() {
  bool result = true;
  int ret = QMessageBox::warning(
      this, tr("Apply Sttings"),
      tr("Settings of current module have changed. Do you want to apply the "
         "changes or discard them?"),
      QMessageBox::Apply | QMessageBox::Discard | QMessageBox::Cancel);
  switch (ret) {
    case QMessageBox::Apply:
      Save();
      break;
    case QMessageBox::Discard:
      Load();
      break;
    case QMessageBox::Cancel:
      result = false;
      break;
    default:
      Load();
      break;
  }
  return result;
}
