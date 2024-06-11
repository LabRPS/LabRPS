#ifndef RPSWINDLABMODULATIONDIALOG_H
#define RPSWINDLABMODULATIONDIALOG_H

#include <QDialog>

class Ui_RPSModulationDialog;

class RPSModulationDialog : public QDialog {
  Q_OBJECT
 public:
  explicit RPSModulationDialog (double para1, double para2, double para3, int option, QWidget *parent = nullptr);
  ~RPSModulationDialog();

 private Q_SLOTS:
  void ok();
  void cancel();

 private:
  Ui_RPSModulationDialog  *ui_;
  QString formulaPath;

public:
double m_para1;
double m_para2;
double m_para3;

};

#endif  // RPSWINDLABMODULATIONDIALOG_H
