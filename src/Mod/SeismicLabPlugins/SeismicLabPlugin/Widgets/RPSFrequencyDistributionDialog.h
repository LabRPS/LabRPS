#ifndef RPSSEISMICLABFREQUENCYDISTRIBUTIONDIALOG_H
#define RPSSEISMICLABFREQUENCYDISTRIBUTIONDIALOG_H

#include <QDialog>

class Ui_RPSFrequencyDistributionDialog;

class RPSFrequencyDistributionDialog : public QDialog {
  Q_OBJECT
 public:
  explicit RPSFrequencyDistributionDialog (int option, QWidget *parent = nullptr);
  ~RPSFrequencyDistributionDialog();

 private Q_SLOTS:
  void ok();
  void cancel();

 private:
  Ui_RPSFrequencyDistributionDialog  *ui_;
  QString formulaPath;

};

#endif  // RPSSEISMICLABFREQUENCYDISTRIBUTIONDIALOG_H
