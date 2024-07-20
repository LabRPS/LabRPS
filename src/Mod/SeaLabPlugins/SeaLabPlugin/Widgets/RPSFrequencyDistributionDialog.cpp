#include "RPSFrequencyDistributionDialog.h"

#include <QDebug>
#include <QSettings>
#include <cmath>
#include "ui_RPSFrequencyDistributionDialog.h"

RPSFrequencyDistributionDialog::RPSFrequencyDistributionDialog(int option, QWidget *parent)
    : QDialog(parent), ui_(new Ui_RPSFrequencyDistributionDialog) {
  ui_->setupUi(this);
  
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
