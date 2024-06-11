#ifndef RPSVONKARMANSPECTRUMDIALOG_H
#define RPSVONKARMANSPECTRUMDIALOG_H

#include <QDialog>

class Ui_RPSVonKarmanDialog;

class RPSVonKarmanDialog : public QDialog {
  Q_OBJECT
 public:
  explicit RPSVonKarmanDialog (double constant1, double constant2, double constant3, double integralLength, double standardDeviation, int option, QWidget *parent = nullptr);
  ~RPSVonKarmanDialog();

 private Q_SLOTS:
  void ok();
  void cancel();

 private:
  Ui_RPSVonKarmanDialog  *ui_;
  QString formulaPath;

public:
double m_constant1;
double m_constant2;
double m_constant3;
double m_integralLength;
double m_standardDeviation;

};

#endif  // RPSVONKARMANSPECTRUMDIALOG_H
