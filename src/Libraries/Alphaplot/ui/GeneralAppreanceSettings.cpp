/* This file is part of AlphaPlot.
   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   AlphaPlot is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   AlphaPlot is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with AlphaPlot.  If not, see <http://www.gnu.org/licenses/>.

   Description : General appearance settings page.
*/
#include "PreCompiled.h"

#include "GeneralAppreanceSettings.h"

#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStyleFactory>
#include <QMessageBox>

#include "core/AppearanceManager.h"
#include  "core/IconLoader.h"
#include "globals.h"
#include "ui_GeneralAppreanceSettings.h"
#include "widgets/ColorLabel.h"
#include <Base/Parameter.h>
#include "Window.h"

//#include <core\AppearanceManager.h>

GeneralAppreanceSettings::GeneralAppreanceSettings(SettingsDialog *dialog)
    : SettingsPage(dialog), ui(new Ui_GeneralAppreanceSettings) {
  ui->setupUi(this);
  setWindowIcon(
      IconLoader::load(QString::fromLatin1("preferences-general-apperance"), IconLoader::General));
  ui->defaultsPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-column-description"), IconLoader::LightDark));
  ui->resetPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-undo"), IconLoader::LightDark));
  ui->applyPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("dialog-ok-apply"), IconLoader::LightDark));
  setWindowTitle(tr("Apperance"));
  setTitle(ui->titleLabel, windowTitle());
  ui->scrollArea->setFrameShape(QFrame::NoFrame);
  ui->scrollArea->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  ui->gridLayout->setContentsMargins(3, 3, 3, 3);
  QStringList styles = QStyleFactory::keys();
  styles.sort();
  ui->styleComboBox->addItems(styles);
  ui->colorSchemeComboBox->addItems(AppearanceManager::colorSchemeNames());
  ui->customColorGroupBox->setCheckable(true);
  ui->customColorGroupBox->setAlignment(Qt::AlignLeft);
  setupColorButton(ui->panelColorButton);
  setupColorButton(ui->paneltextColorButton);
  setupColorButton(ui->workspaceColorButton);
  connect(
      ui->customColorGroupBox, &QGroupBox::toggled, this,
      [=](const bool status) {
        if (status) {
          QMessageBox::StandardButton reply;
          reply = QMessageBox::warning(
              this, tr("Table custom color setting"),
              tr("This feature is highly experimental and can result in "
                 "unintended application colors. If you wish to proceed "
                 "with the same and apply the settings, make sure that you "
                 "close alphaplot and reopen again to reflect the changes.") +
                  QString::fromLatin1("\n\n") + tr("Do you wish to continue ?"),
              QMessageBox::Yes | QMessageBox::No);
          (reply == QMessageBox::Yes)
              ? ui->customColorGroupBox->setChecked(true)
              : ui->customColorGroupBox->setChecked(false);
        }
      });
  connect(ui->applyPushButton, &QPushButton::clicked, this,
          &GeneralAppreanceSettings::Save);
  connect(ui->resetPushButton, &QPushButton::clicked, this,
          &GeneralAppreanceSettings::Load);
  connect(ui->defaultsPushButton, &QPushButton::clicked, this,
          &GeneralAppreanceSettings::LoadDefault);
  connect(ui->colorSchemeComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &GeneralAppreanceSettings::colorStylePreview);
  connect(ui->styleComboBox, &QComboBox::currentTextChanged, this,
          &GeneralAppreanceSettings::stylePreview);
  connect(ui->panelColorButton, &QToolButton::clicked,
          [&]() { pickColor(ui->panelColorLabel); });
  connect(ui->paneltextColorButton, &QToolButton::clicked,
          [&]() { pickColor(ui->paneltextColorLabel); });
  connect(ui->workspaceColorButton, &QToolButton::clicked,
          [&]() { pickColor(ui->workspaceColorLabel); });
  Load();
}

GeneralAppreanceSettings::~GeneralAppreanceSettings() { delete ui; }

void GeneralAppreanceSettings::Load() {
  loadQsettingsValues();
  ui->styleComboBox->setCurrentIndex(
      ui->styleComboBox->findText(appstyle_, Qt::MatchWildcard));
  ui->colorSchemeComboBox->setCurrentIndex(colorscheme_);
  ui->customColorGroupBox->setChecked(customcolors_);
  ui->workspaceColorLabel->setColor(workspacecolor_);
  ui->panelColorLabel->setColor(panelcolor_);
  ui->paneltextColorLabel->setColor(paneltextcolor_);
}

void GeneralAppreanceSettings::LoadDefault() {
  ui->styleComboBox->setCurrentIndex(0);
  ui->colorSchemeComboBox->setCurrentIndex(0);
  ui->customColorGroupBox->setChecked(false);
  ui->workspaceColorLabel->setColor(palette().base().color());
  ui->panelColorLabel->setColor(palette().window().color());
  ui->paneltextColorLabel->setColor(palette().windowText().color());
}

void GeneralAppreanceSettings::Save() {

    ParameterGrp::handle wGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("General");
  
    QString styleIndex = ui->styleComboBox->currentText();
    wGrp->SetASCII("Style", styleIndex.toLatin1().constData());

    int colorIndex = ui->colorSchemeComboBox->currentIndex();
    wGrp->SetInt("ColorScheme", colorIndex);

    wGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("General")->GetGroup("Colors");
    
    bool customColor = ui->customColorGroupBox->isChecked();
    wGrp->SetBool("Custom", customColor);

    QColor workspaceColor = ui->workspaceColorLabel->getColor();
    wGrp->SetUnsigned("Workspace", workspaceColor.rgba() << 8);

    QColor panelsColor = ui->panelColorLabel->getColor();
    wGrp->SetUnsigned("Panels", panelsColor.rgba() << 8);

    QColor panelsTextColor = ui->paneltextColorLabel->getColor();
    wGrp->SetUnsigned("PanelsText", panelsTextColor.rgba() << 8);

  //QSettings settings;
  //settings.beginGroup(QString::fromLatin1("General"));
  //settings.setValue(QString::fromLatin1("Style"), ui->styleComboBox->currentText());
  //settings.setValue(QString::fromLatin1("ColorScheme"), ui->colorSchemeComboBox->currentIndex());
  //settings.beginGroup(QString::fromLatin1("Colors"));
  //settings.setValue(QString::fromLatin1("Custom"), ui->customColorGroupBox->isChecked());
  /*settings.setValue(QString::fromLatin1("Workspace"), ui->workspaceColorLabel->getColor());
  settings.setValue(QString::fromLatin1("Panels"), ui->panelColorLabel->getColor());
  settings.setValue(QString::fromLatin1("PanelsText"), ui->paneltextColorLabel->getColor());
  settings.endGroup();
  settings.endGroup();*/

  Q_EMIT generalappreancesettingsupdate();
}

bool GeneralAppreanceSettings::settingsChangeCheck() {
  loadQsettingsValues();
  bool result = true;
  if (appstyle_.toLower() != ui->styleComboBox->currentText().toLower() ||
      colorscheme_ != ui->colorSchemeComboBox->currentIndex() ||
      customcolors_ != ui->customColorGroupBox->isChecked() ||
      workspacecolor_ != ui->workspaceColorLabel->getColor() ||
      panelcolor_ != ui->panelColorLabel->getColor() ||
      paneltextcolor_ != ui->paneltextColorLabel->getColor()) {
    result = settingsChanged();
  }
  return result;
}

void GeneralAppreanceSettings::setupColorButton(QToolButton *button) {
  button->setIcon(IconLoader::load(QString::fromLatin1("color-management"), IconLoader::General));
  button->setStyleSheet(QString::fromLatin1("QToolButton {border: 0px;}"));
}

void GeneralAppreanceSettings::pickColor(ColorLabel *label) {
  QColor color =
      QColorDialog::getColor(label->getColor(), this, tr("Colors"),
                             QColorDialog::ColorDialogOption::ShowAlphaChannel);
  if (!color.isValid() || color == label->getColor()) return;
  label->setColor(color);
}

void GeneralAppreanceSettings::loadQsettingsValues() {

    ParameterGrp::handle hGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("General");
    
    appstyle_ = QString::fromUtf8(hGrp->GetASCII("Style", qApp->style()->objectName().toLatin1().constData()).c_str());
   
    colorscheme_ = hGrp->GetInt("ColorScheme", 0);

    hGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("General")->GetGroup("Colors");

    customcolors_ = hGrp->GetBool("Custom", false);
  
    unsigned long col = hGrp->GetUnsigned("Workspace", palette().base().color().rgba() >> 8);
    workspacecolor_.setRgb(col);

    col = hGrp->GetUnsigned("Panels", palette().window().color().rgba() >> 8);
    panelcolor_.setRgb(col);

    col = hGrp->GetUnsigned("PanelsText", palette().windowText().color().rgba() >> 8);
    paneltextcolor_.setRgb(col);


  /*QSettings settings;
  settings.beginGroup(QString::fromLatin1("General"));*/
  //appstyle_ = settings.value(QString::fromLatin1("Style"), qApp->style()->objectName()).toString();
  //colorscheme_ = settings.value(QString::fromLatin1("ColorScheme"), 0).toInt();
  //settings.beginGroup(QString::fromLatin1("Colors"));
 /* customcolors_ = settings.value(QString::fromLatin1("Custom"), false).toBool();
  workspacecolor_ =
      settings.value(QString::fromLatin1("Workspace"), palette().base().color()).value<QColor>();
  panelcolor_ =
      settings.value(QString::fromLatin1("Panels"), palette().window().color()).value<QColor>();
  paneltextcolor_ = settings.value(QString::fromLatin1("PanelsText"), palette().windowText().color())
                        .value<QColor>();
  settings.endGroup();
  settings.endGroup();*/
}

void GeneralAppreanceSettings::stylePreview(const QString &style) {
  QStyle *stylefinal = QStyleFactory::create(style.toLower());

  if (!stylefinal) {
    return;
  }

  ui->groupBox->setStyle(stylefinal);
  ui->previewTabWidget->setStyle(stylefinal);
  ui->previewTab->setStyle(stylefinal);
  ui->previewGroupBox->setStyle(stylefinal);
  ui->previewRadioButton1->setStyle(stylefinal);
  ui->previewRadioButton2->setStyle(stylefinal);
  ui->previewLine->setStyle(stylefinal);
  ui->previewCheckBox->setStyle(stylefinal);
  ui->previewComboBox->setStyle(stylefinal);
  ui->previewProgressBar->setStyle(stylefinal);
  ui->previewSlider->setStyle(stylefinal);
  ui->previewSpinBox->setStyle(stylefinal);
  ui->previewPushButton->setStyle(stylefinal);
  ui->previewScrollBar->setStyle(stylefinal);
  ui->previewTableWidget->setStyle(stylefinal);
}

void GeneralAppreanceSettings::colorStylePreview(int index) {
  switch (index) {
    case 0: {
      ui->groupBox->setStyleSheet(styleSheet());
    } break;
    case 1: {
      QFile schemefile(QString::fromLatin1(":style/alpha/dark.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    case 2: {
      QFile schemefile(QString::fromLatin1(":style/smooth/dark-blue.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    case 3: {
      QFile schemefile(QString::fromLatin1(":style/smooth/dark-green.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    case 4: {
      QFile schemefile(QString::fromLatin1(":style/smooth/dark-orange.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    case 5: {
      QFile schemefile(QString::fromLatin1(":style/smooth/light-blue.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    case 6: {
      QFile schemefile(QString::fromLatin1(":style/smooth/light-green.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    case 7: {
      QFile schemefile(QString::fromLatin1(":style/smooth/light-orange.qss"));
      schemefile.open(QFile::ReadOnly | QFile::Text);
      QTextStream schemeFileStream(&schemefile);
      ui->groupBox->setStyleSheet(schemeFileStream.readAll());
    } break;
    default:
      // should not reach
      qDebug() << "color scheme index out of range";
      break;
  }
}
