#ifndef SCRIPTING_LANG_DIALOG_H
#define SCRIPTING_LANG_DIALOG_H

#include "ScriptingEnv.h"
#include "Script.h"

#include <QDialog>

class ApplicationWindow;
class QListWidget;
class QPushButton;

class ScriptingLangDialog : public QDialog, public scripted {
  Q_OBJECT

 public:
  ScriptingLangDialog(ScriptingEnv *env, ApplicationWindow *parent,
                      Qt::WindowFlags fl = Qt::Widget);

 public slots:
  void updateLangList();
  void accept();

 private:
  QListWidget *langList;
  QPushButton *btnOK, *btnCancel;
};

#endif  // SCRIPTING_LANG_DIALOG_H
