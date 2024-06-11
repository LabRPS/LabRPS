#include "Precompiled.h"

#include "FittingSettings.h"

#include <QFrame>
#include <QSettings>

#include  "core/IconLoader.h"
#include "ui_FittingSettings.h"

FittingSettings::FittingSettings(SettingsDialog *dialog)
    : SettingsPage(dialog), ui(new Ui_FittingSettings) {
  ui->setupUi(this);
  setWindowIcon(IconLoader::load(QString::fromLatin1("preferences-fitting"), IconLoader::General));
  ui->defaultsPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-column-description"), IconLoader::LightDark));
  ui->resetPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("edit-undo"), IconLoader::LightDark));
  ui->applyPushButton->setIcon(
      IconLoader::load(QString::fromLatin1("dialog-ok-apply"), IconLoader::LightDark));
  setWindowTitle(tr("Fitting"));
  setTitle(ui->titleLabel, windowTitle());
  ui->scrollArea->setFrameShape(QFrame::NoFrame);
  ui->scrollArea->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  connect(ui->uniformXRadioButton, &QRadioButton::toggled, this,
          [&](bool checked) {
            if (checked) {
              ui->pointsLabel->setVisible(true);
              ui->pointsSpinBox->setVisible(true);
              ui->linearFitCheckBox->setVisible(true);
            } else {
              ui->pointsLabel->setVisible(false);
              ui->pointsSpinBox->setVisible(false);
              ui->linearFitCheckBox->setVisible(false);
            }
          });
  connect(ui->applyPushButton, &QPushButton::clicked, this,
          &FittingSettings::Save);
  connect(ui->resetPushButton, &QPushButton::clicked, this,
          &FittingSettings::Load);
  connect(ui->defaultsPushButton, &QPushButton::clicked, this,
          &FittingSettings::LoadDefault);
  Load();
}

FittingSettings::~FittingSettings() { delete ui; }

void FittingSettings::Load() {
  loadQsettingsValues();
  ui->uniformXRadioButton->setChecked(generateUniformFitPoints_);
  ui->pointsSpinBox->setValue(fitPoints_);
  ui->linearFitCheckBox->setChecked(d_2_linear_fit_points_);
  ui->multiPeakGroupBox->setChecked(generatePeakCurves_);
  ui->peakColorComboBox->setCurrentIndex(peakCurvesColor_);
  ui->significantDigitsSpinBox->setValue(fit_output_precision_);
  ui->writetoResultCheckBox->setChecked(writeFitResultsToLog_);
  ui->pastetoPlotCheckBox->setChecked(pasteFitResultsToPlot_);
  ui->scaleCheckBox->setChecked(fit_scale_errors_);
}

void FittingSettings::LoadDefault() {
  ui->uniformXRadioButton->setChecked(true);
  ui->pointsSpinBox->setValue(100);
  ui->linearFitCheckBox->setChecked(true);
  ui->multiPeakGroupBox->setChecked(true);
  ui->peakColorComboBox->setCurrentIndex(2);
  ui->significantDigitsSpinBox->setValue(15);
  ui->writetoResultCheckBox->setChecked(true);
  ui->pastetoPlotCheckBox->setChecked(false);
  ui->scaleCheckBox->setChecked(false);
}

void FittingSettings::Save() {
  QSettings settings;
  settings.beginGroup(QString::fromLatin1("Fitting"));
  settings.setValue(QString::fromLatin1("OutputPrecision"), ui->significantDigitsSpinBox->value());
  settings.setValue(QString::fromLatin1("PasteResultsToPlot"), ui->pastetoPlotCheckBox->isChecked());
  settings.setValue(QString::fromLatin1("WriteResultsToLog"),
                    ui->writetoResultCheckBox->isChecked());
  settings.setValue(QString::fromLatin1("GenerateFunction"), ui->uniformXRadioButton->isChecked());
  settings.setValue(QString::fromLatin1("Points"), ui->pointsSpinBox->value());
  settings.setValue(QString::fromLatin1("GeneratePeakCurves"), ui->multiPeakGroupBox->isChecked());
  settings.setValue(QString::fromLatin1("PeaksColor"), ui->peakColorComboBox->currentIndex());
  settings.setValue(QString::fromLatin1("ScaleErrors"), ui->scaleCheckBox->isChecked());
  settings.setValue(QString::fromLatin1("TwoPointsLinearFit"), ui->linearFitCheckBox->isChecked());
  settings.endGroup();  // Fitting
}

bool FittingSettings::settingsChangeCheck() {
  loadQsettingsValues();
  bool result = true;
  if (generateUniformFitPoints_ != ui->uniformXRadioButton->isChecked() ||
      fitPoints_ != ui->pointsSpinBox->value() ||
      d_2_linear_fit_points_ != ui->linearFitCheckBox->isChecked() ||
      generatePeakCurves_ != ui->multiPeakGroupBox->isChecked() ||
      peakCurvesColor_ != ui->peakColorComboBox->currentIndex() ||
      fit_output_precision_ != ui->significantDigitsSpinBox->value() ||

      writeFitResultsToLog_ != ui->writetoResultCheckBox->isChecked() ||
      pasteFitResultsToPlot_ != ui->pastetoPlotCheckBox->isChecked() ||
      fit_scale_errors_ != ui->scaleCheckBox->isChecked()) {
    result = settingsChanged();
  }
  return result;
}

void FittingSettings::loadQsettingsValues() {
  QSettings settings;
  settings.beginGroup(QString::fromLatin1("Fitting"));
  fit_output_precision_ = settings.value(QString::fromLatin1("OutputPrecision"), 15).toInt();
  pasteFitResultsToPlot_ = settings.value(QString::fromLatin1("PasteResultsToPlot"), false).toBool();
  writeFitResultsToLog_ = settings.value(QString::fromLatin1("WriteResultsToLog"), true).toBool();
  generateUniformFitPoints_ = settings.value(QString::fromLatin1("GenerateFunction"), true).toBool();
  fitPoints_ = settings.value(QString::fromLatin1("Points"), 100).toInt();
  generatePeakCurves_ = settings.value(QString::fromLatin1("GeneratePeakCurves"), true).toBool();
  peakCurvesColor_ = settings.value(QString::fromLatin1("PeaksColor"), 2).toInt();  // green color
  fit_scale_errors_ = settings.value(QString::fromLatin1("ScaleErrors"), false).toBool();
  d_2_linear_fit_points_ = settings.value(QString::fromLatin1("TwoPointsLinearFit"), true).toBool();
  settings.endGroup();  // Fitting
}
