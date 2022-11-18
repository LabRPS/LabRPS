#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>

class QPushButton;
class QCheckBox;
class QComboBox;
class QLabel;

//! Find dialog
class FindDialog : public QDialog {
  Q_OBJECT

 public:
  FindDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);
  ~FindDialog();

 private:
  QPushButton* buttonFind;
  QPushButton* buttonCancel;
  QPushButton* buttonReset;

  QLabel* labelStart;
  QComboBox* boxFind;

  QCheckBox* boxWindowNames;
  QCheckBox* boxWindowLabels;
  QCheckBox* boxFolderNames;

  QCheckBox* boxCaseSensitive;
  QCheckBox* boxPartialMatch;
  QCheckBox* boxSubfolders;

 public slots:

  //! Displays the project current folder path
  void setStartPath();

 protected slots:

  void accept();
};

#endif  // FINDDIALOG_H
