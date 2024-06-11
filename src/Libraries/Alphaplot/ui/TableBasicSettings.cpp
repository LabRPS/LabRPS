#include "Precompiled.h"

#include "TableBasicSettings.h"

#include <QDebug>
#include <QSettings>

#include  "core/IconLoader.h"
#include "ui_TableBasicSettings.h"

TableBasicSettings::TableBasicSettings(SettingsDialog *dialog)
    : SettingsPage(dialog), ui(new Ui_TableBasicSettings) {
  ui->setupUi(this);
  setWindowIcon(IconLoader::load(QString::fromLatin1("table-properties"), IconLoader::General));
  ui->defaultsPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-column-description"), IconLoader::LightDark));
  ui->resetPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-undo"), IconLoader::LightDark));
  ui->applyPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("dialog-ok-apply"), IconLoader::LightDark));
  setWindowTitle(tr("Preference"));
  setTitle(ui->titleLabel, windowTitle());
  ui->scrollArea->setFrameShape(QFrame::NoFrame);
  ui->scrollArea->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  ui->rowHeightSpinBox->setRange(3, 200);
  ui->columnSeparatorComboBox->clear();
  ui->columnSeparatorComboBox->addItem(tr("TAB"));
  ui->columnSeparatorComboBox->addItem(tr("SPACE"));
  ui->columnSeparatorComboBox->addItem(QString::fromLatin1(";") + tr("TAB"));
  ui->columnSeparatorComboBox->addItem(QString::fromLatin1(",") + tr("TAB"));
  ui->columnSeparatorComboBox->addItem(QString::fromLatin1(";") + tr("SPACE"));
  ui->columnSeparatorComboBox->addItem(QString::fromLatin1(",") + tr("SPACE"));
  ui->columnSeparatorComboBox->addItem(QString::fromLatin1(";"));
  ui->columnSeparatorComboBox->addItem(QString::fromLatin1(","));
  connect(ui->applyPushButton, &QPushButton::clicked, this,
          &TableBasicSettings::Save);
  connect(ui->resetPushButton, &QPushButton::clicked, this,
          &TableBasicSettings::Load);
  connect(ui->defaultsPushButton, &QPushButton::clicked, this,
          &TableBasicSettings::LoadDefault);
  Load();
}

TableBasicSettings::~TableBasicSettings() { delete ui; }

void TableBasicSettings::Load() {
  loadQsettingsValues();
  ui->commentsCheckBox->setChecked(show_table_comments_);
  setColumnSeparator(columnseparator_);
}

void TableBasicSettings::LoadDefault() {
  ui->commentsCheckBox->setChecked(false);
  setColumnSeparator(QString::fromLatin1("\t"));
}

void TableBasicSettings::Save() {
  QSettings settings;
  settings.beginGroup(QString::fromLatin1("Tables"));
  settings.setValue(QString::fromLatin1("DisplayComments"), ui->commentsCheckBox->isChecked());
  settings.endGroup();
  settings.beginGroup(QString::fromLatin1("ImportASCII"));
  settings.setValue(QString::fromLatin1("ColumnSeparator"),
                    ui->columnSeparatorComboBox->currentText()
                        .replace(tr("TAB"), QString::fromLatin1("\t"))
                        .replace(tr("SPACE"), QString::fromLatin1(" ")));
  settings.endGroup();

  Q_EMIT tablebasicsettingsupdate();
}

bool TableBasicSettings::settingsChangeCheck() {
  loadQsettingsValues();
  bool result = true;
  if (show_table_comments_ != ui->commentsCheckBox->isChecked() ||
      columnseparator_ != ui->columnSeparatorComboBox->currentText()
                              .replace(tr("TAB"), QString::fromLatin1("\t"))
                              .replace(tr("SPACE"), QString::fromLatin1(" "))) {
    result = settingsChanged();
  }
  return result;
}

void TableBasicSettings::loadQsettingsValues() {
  QSettings settings;
  settings.beginGroup(QString::fromLatin1("Tables"));
  show_table_comments_ = settings.value(QString::fromLatin1("DisplayComments"), false).toBool();
  settings.endGroup();
  settings.beginGroup(QString::fromLatin1("ImportASCII"));
  columnseparator_ =
      settings.value(QString::fromLatin1("ColumnSeparator"), QString::fromLatin1("\\t")).toString();
  columnseparator_.replace(tr("TAB"), QString::fromLatin1("\t").replace(tr("SPACE"), QString::fromLatin1(" ")));
  settings.endGroup();
}

void TableBasicSettings::setColumnSeparator(const QString &sep) {
  if (sep == QString::fromLatin1("\t"))
    ui->columnSeparatorComboBox->setCurrentIndex(0);
  else if (sep == QString::fromLatin1(" "))
    ui->columnSeparatorComboBox->setCurrentIndex(1);
  else if (sep == QString::fromLatin1(";\t"))
    ui->columnSeparatorComboBox->setCurrentIndex(2);
  else if (sep == QString::fromLatin1(",\t"))
    ui->columnSeparatorComboBox->setCurrentIndex(3);
  else if (sep == QString::fromLatin1("; "))
    ui->columnSeparatorComboBox->setCurrentIndex(4);
  else if (sep == QString::fromLatin1(", "))
    ui->columnSeparatorComboBox->setCurrentIndex(5);
  else if (sep == QString::fromLatin1(";"))
    ui->columnSeparatorComboBox->setCurrentIndex(6);
  else if (sep == QString::fromLatin1(","))
    ui->columnSeparatorComboBox->setCurrentIndex(7);
  else {
    QString separator = sep;
    ui->columnSeparatorComboBox->setEditText(
        separator.replace(QString::fromLatin1(" "), QString::fromLatin1("\\s")).replace(QString::fromLatin1("\t"), QString::fromLatin1("\\t")));
  }
}
