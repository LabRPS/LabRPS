#include "ScriptingLangDialog.h"

#include <QLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>

#include "ApplicationWindow.h"

ScriptingLangDialog::ScriptingLangDialog(ScriptingEnv *env,
                                         ApplicationWindow *parent,
                                         Qt::WindowFlags fl)
    : QDialog(parent, fl), scripted(env) {
  setWindowTitle(tr("Select scripting language"));

  langList = new QListWidget(this);

  btnOK = new QPushButton(tr("OK"));
  btnCancel = new QPushButton(tr("Cancel"));

  QHBoxLayout *hbox1 = new QHBoxLayout();
  hbox1->addStretch();
  hbox1->addWidget(btnOK);
  hbox1->addWidget(btnCancel);

  QVBoxLayout *vl = new QVBoxLayout(this);
  vl->addWidget(langList);
  vl->addLayout(hbox1);

  connect(btnOK, &QPushButton::clicked, this, &ScriptingLangDialog::accept);
  connect(btnCancel, &QPushButton::clicked, this, &ScriptingLangDialog::close);
  connect(langList, &QListWidget::itemActivated, this,
          &ScriptingLangDialog::accept);

  updateLangList();
}

void ScriptingLangDialog::updateLangList() {
  langList->clear();
  langList->insertItems(0, ScriptingLangManager::languages());
  QListWidgetItem *current =
      langList->findItems(scriptEnv->objectName(), Qt::MatchExactly).first();
  if (current) langList->setCurrentItem(current);
}

void ScriptingLangDialog::accept() {
  ApplicationWindow *app = qobject_cast<ApplicationWindow *>(parent());
  if (app->setScriptingLang(langList->currentItem()->text()))
    close();
  else
    QMessageBox::critical(this, tr("Scripting Error"),
                          tr("Scripting language \"%1\" failed to initialize.")
                              .arg(langList->currentItem()->text()));
}
