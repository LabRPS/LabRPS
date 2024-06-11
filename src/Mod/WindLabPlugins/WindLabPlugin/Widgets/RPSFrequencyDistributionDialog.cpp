#include "RPSFrequencyDistributionDialog.h"

#include <QDebug>
#include <QSettings>
#include <cmath>
#include "IconLoader.h"
#include "ui_RPSFrequencyDistributionDialog.h"

using namespace WindLab;

RPSFrequencyDistributionDialog::RPSFrequencyDistributionDialog(int option, QWidget *parent)
    : QDialog(parent), ui_(new Ui_RPSFrequencyDistributionDialog) {
  ui_->setupUi(this);
  IconLoader::init();
  IconLoader::lumen_ = 101;
  setWindowIcon(IconLoader::load("edit-random-dist", IconLoader::LightDark));
  ui_->formulaLabel->setAlignment(Qt::AlignCenter);
  setModal(true);

  // Theaming based pixmap loading
  (IconLoader::lumen_ < 100)
      ? formulaPath = QString(":icons/dark/equations/")
      : formulaPath = QString(":icons/light/equations/");

  // Set layout margins
  ui_->gridLayout->setContentsMargins(0, 0, 0, 0);

  switch (option) {
    case 1:
      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "SingleIndexFrequency.png"));

      break;
  case 2:
      ui_->formulaLabel->setPixmap(
          QPixmap(formulaPath + "DoubleIndexFrequency.png"));

    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  }


  // Slot connections
  connect(ui_->RPSButonButtonBox, &QDialogButtonBox::accepted, this,
          &RPSFrequencyDistributionDialog::ok);
  connect(ui_->RPSButonButtonBox, &QDialogButtonBox::rejected, this,
          &RPSFrequencyDistributionDialog::cancel);
}

RPSFrequencyDistributionDialog::~RPSFrequencyDistributionDialog() { delete ui_; }

void RPSFrequencyDistributionDialog::ok() {

  QDialog::accept();
}

void RPSFrequencyDistributionDialog::cancel() { QDialog::reject(); }
