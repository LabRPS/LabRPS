#include "PreCompiled.h"

#include "GeneralApplicationSettings.h"

#include <QColorDialog>
#include <QDir>
#include <QFontDialog>
#include <QSettings>
#include <QTranslator>

#include  "core/IconLoader.h"
#include "globals.h"
#include "ui_GeneralApplicationSettings.h"

#ifndef TS_PATH
#define TS_PATH (qApp->applicationDirPath() + QString::fromLatin1("/translations"))
#endif

ApplicationSettingsPage::ApplicationSettingsPage(SettingsDialog *dialog)
    : SettingsPage(dialog), ui(new Ui_ApplicationSettingsPage) {
  ui->setupUi(this);
  setWindowIcon(IconLoader::load(QString::fromLatin1("preferences-general"), IconLoader::General));
  ui->defaultsPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-column-description"), IconLoader::LightDark));
  ui->resetPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-undo"), IconLoader::LightDark));
  ui->applyPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("dialog-ok-apply"), IconLoader::LightDark));
  setWindowTitle(tr("Basic"));
  setTitle(ui->titleLabel, windowTitle());
  ui->scrollArea->setFrameShape(QFrame::NoFrame);
  ui->scrollArea->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  ui->glowIndicatorGroupBox->setCheckable(true);
  ui->glowIndicatorGroupBox->setAlignment(Qt::AlignLeft);
  ui->glowColorButton->setIcon(
      IconLoader::load(QString::fromLatin1("color-management"), IconLoader::General));
  ui->glowColorButton->setStyleSheet(QString::fromLatin1("QToolButton {border: 0px;}"));
  //ui->scriptingComboBox->addItems(ScriptingLangManager::languages());
  ui->saveSpinBox->setRange(1, 120);
  ui->saveSpinBox->setSuffix(tr(" minutes"));
  ui->undoSpinBox->setRange(1, 1000);
  ui->versionCheckBox->hide();
#ifdef SEARCH_FOR_UPDATES
  ui->versionCheckBox->show();
#endif
  connect(ui->applyPushButton, &QPushButton::clicked, this,
          &ApplicationSettingsPage::Save);
  connect(ui->resetPushButton, &QPushButton::clicked, this,
          &ApplicationSettingsPage::Load);
  connect(ui->defaultsPushButton, &QPushButton::clicked, this,
          &ApplicationSettingsPage::LoadDefault);
  connect(ui->fontToolButton, &QToolButton::clicked, this,
          &ApplicationSettingsPage::pickApplicationFont);
  connect(ui->glowColorButton, &QToolButton::clicked, this,
          &ApplicationSettingsPage::pickColor);

  insertLanguagesList();
  Load();
}

ApplicationSettingsPage::~ApplicationSettingsPage() { delete ui; }

void ApplicationSettingsPage::Load() {
  loadQsettingsValues();

  ui->fontvalueLabel->setFont(applicationfont_);
  ui->fontvalueLabel->setText(QString::fromLatin1("%1 %2")
                                  .arg(applicationfont_.family())
                                  .arg(applicationfont_.pointSize()));
  ui->glowIndicatorGroupBox->setChecked(glowstatus_);
  ui->glowThicknessSpinBox->setValue(glowradius_);
  ui->glowColorLabel->setColor(glowcolor_);
  // ToDo: language
  /*ui->scriptingComboBox->setCurrentIndex(
      ScriptingLangManager::languages().indexOf(defaultscriptinglang_));*/
  ui->saveCheckBox->setChecked(autosave_);
  ui->saveSpinBox->setValue(autosavetime_);
  ui->undoSpinBox->setValue(undolimit_);
#ifdef SEARCH_FOR_UPDATES
  ui->versionCheckBox->setChecked(autosearchupdates_);
#endif
}

void ApplicationSettingsPage::LoadDefault() {
  ui->fontvalueLabel->setFont(QFont());
  applicationfont_ = QFont();
  ui->fontvalueLabel->setText(QString::fromLatin1("%1 %2")
                                  .arg(applicationfont_.family())
                                  .arg(applicationfont_.pointSize()));
  ui->glowIndicatorGroupBox->setChecked(false);
  ui->glowThicknessSpinBox->setValue(8);
  ui->glowColorLabel->setColor(Qt::red);
  /*ui->scriptingComboBox->setCurrentIndex(
      ScriptingLangManager::languages().indexOf(QString::fromLatin1("muParser")));*/
  ui->saveCheckBox->setChecked(true);
  ui->saveSpinBox->setValue(15);
  ui->undoSpinBox->setValue(10);
#ifdef SEARCH_FOR_UPDATES
  ui->versionCheckBox->setChecked(false);
#endif
}

void ApplicationSettingsPage::Save() {
  QSettings settings;
  settings.beginGroup(QString::fromLatin1("General"));
  settings.beginGroup(QString::fromLatin1("GlowIndicator"));
  settings.setValue(QString::fromLatin1("Show"), ui->glowIndicatorGroupBox->isChecked());
  settings.setValue(QString::fromLatin1("Color"), ui->glowColorLabel->getColor());
  settings.setValue(QString::fromLatin1("Radius"), ui->glowThicknessSpinBox->value());
  settings.endGroup();
  QStringList applicationFont;
  applicationFont << ui->fontvalueLabel->font().family();
  applicationFont << QString::number(ui->fontvalueLabel->font().pointSize());
  applicationFont << QString::number(ui->fontvalueLabel->font().weight());
  applicationFont << QString::number(ui->fontvalueLabel->font().italic());
  settings.setValue(QString::fromLatin1("Font"), applicationFont);
  settings.setValue(QString::fromLatin1("Language"), ui->scriptingComboBox->currentText());
  settings.setValue(QString::fromLatin1("AutoSave"), ui->saveCheckBox->isChecked());
  settings.setValue(QString::fromLatin1("AutoSaveTime"), ui->saveSpinBox->value());
  settings.setValue(QString::fromLatin1("UndoLimit"), ui->undoSpinBox->value());
  settings.setValue(QString::fromLatin1("ScriptingLang"), defaultscriptinglang_);
#ifdef SEARCH_FOR_UPDATES
  settings.setValue(QString::fromLatin1("AutoSearchUpdates"), ui->versionCheckBox->isChecked());
#endif
  settings.endGroup();

  Q_EMIT generalapplicationsettingsupdate();
}

bool ApplicationSettingsPage::settingsChangeCheck() {
  loadQsettingsValues();
  bool result = true;
  if (glowstatus_ != ui->glowIndicatorGroupBox->isChecked() ||
      glowcolor_ != ui->glowColorLabel->getColor() ||
      glowradius_ != ui->glowThicknessSpinBox->value() ||
      // these fonts donot match for some unknown reason so check each values
      applicationfont_.family() != ui->fontvalueLabel->font().family() ||
      applicationfont_.pointSize() != ui->fontvalueLabel->font().pointSize() ||
      applicationfont_.weight() != ui->fontvalueLabel->font().weight() ||
      applicationfont_.italic() != ui->fontvalueLabel->font().italic() ||
      defaultscriptinglang_.toLower() !=
          ui->scriptingComboBox->currentText().toLower() ||
      autosave_ != ui->saveCheckBox->isChecked() ||
      autosavetime_ != ui->saveSpinBox->value() ||
      undolimit_ != ui->undoSpinBox->value() ||
      autosearchupdates_ != ui->versionCheckBox->isChecked()) {
    result = settingsChanged();
  }
  return result;
}

void ApplicationSettingsPage::loadQsettingsValues() {
  QSettings settings;
  settings.beginGroup(QString::fromLatin1("General"));
  settings.beginGroup(QString::fromLatin1("GlowIndicator"));
  glowstatus_ = settings.value(QString::fromLatin1("Show"), false).toBool();
  glowcolor_ = settings.value(QString::fromLatin1("Color"), QString::fromLatin1("red")).value<QColor>();
  glowradius_ = settings.value(QString::fromLatin1("Radius"), 8).toDouble();
  settings.endGroup();
  applanguage_ =
      settings.value(QString::fromLatin1("Language"), QLocale::system().name().section(QChar::fromLatin1('_'), 0, 0))
          .toString();
  defaultscriptinglang_ =
      settings.value(QString::fromLatin1("ScriptingLang"), QString::fromLatin1("muParser"))
          .toString();
  autosave_ = settings.value(QString::fromLatin1("AutoSave"), true).toBool();
  autosavetime_ = settings.value(QString::fromLatin1("AutoSaveTime"), 15).toInt();
  undolimit_ = settings.value(QString::fromLatin1("UndoLimit"), 10).toInt();
  QStringList applicationFont = settings.value(QString::fromLatin1("Font")).toStringList();
  if (applicationFont.size() == 4)
    applicationfont_ =
        QFont(applicationFont.at(0), applicationFont.at(1).toInt(),
              applicationFont.at(2).toInt(), applicationFont.at(3).toInt());
#ifdef SEARCH_FOR_UPDATES
  autosearchupdates_ = settings.value("AutoSearchUpdates", false).toBool();
#endif
  settings.endGroup();
}

void ApplicationSettingsPage::pickColor() {
  QColor color =
      QColorDialog::getColor(ui->glowColorLabel->getColor(), this, tr("Colors"),
                             QColorDialog::ColorDialogOption::ShowAlphaChannel);
  if (!color.isValid() || color == ui->glowColorLabel->getColor()) return;
  ui->glowColorLabel->setColor(color);
}

void ApplicationSettingsPage::pickApplicationFont() {
  bool ok;
  QFont font = QFontDialog::getFont(&ok, applicationfont_, this);
  if (ok)
    applicationfont_ = font;
  else
    return;
  ui->fontvalueLabel->setFont(applicationfont_);
  ui->fontvalueLabel->setText(QString::fromLatin1("%1 %2")
                                  .arg(applicationfont_.family())
                                  .arg(applicationfont_.pointSize()));
}

void ApplicationSettingsPage::insertLanguagesList() {
  ui->languageComboBox->clear();
  QDir dir(TS_PATH);
  QStringList locales = AlphaPlot::getLocales();
  QStringList languages;
  int lang = 0;
  QSettings settings;
  for (int i = 0; i < locales.size(); i++) {
    if (locales.at(i) == QString::fromLatin1("en"))
      languages.push_back(QString::fromLatin1("English"));
    else {
      QTranslator translator;
      translator.load(QString::fromLatin1("alphaplot_") + locales.at(i), TS_PATH);

      QString language = translator.translate("Gui::MainWindow", "English",
                                              "translate this to the language "
                                              "of the translation file, NOT to "
                                              "the meaning of English!");
      if (!language.isEmpty())
        languages.push_back(language);
      else
        languages.push_back(locales.at(i));
    }

    if (locales.at(i) ==
        settings.value(QString::fromLatin1("Language"), QLocale::system().name().section(QChar::fromLatin1('_'), 0, 0))
            .toString())
      lang = i;
  }
  ui->languageComboBox->addItems(languages);
  ui->languageComboBox->setCurrentIndex(lang);
}
