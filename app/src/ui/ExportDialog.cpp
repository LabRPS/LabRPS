#include "ExportDialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QPushButton>

ExportDialog::ExportDialog(QWidget *parent, Qt::WindowFlags fl)
    : QDialog(parent, fl) {
  setWindowTitle(tr("Export ASCII"));
  setSizeGripEnabled(true);

  QGridLayout *gl1 = new QGridLayout();
  gl1->addWidget(new QLabel(tr("Table")), 0, 0);
  boxTable = new QComboBox();
  boxTable->setSizePolicy(
      QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
  gl1->addWidget(boxTable, 0, 1);

  boxAllTables = new QCheckBox(tr("&All"));
  boxAllTables->setChecked(false);
  gl1->addWidget(boxAllTables, 0, 2);

  QLabel *sepText = new QLabel(tr("Separator"));
  gl1->addWidget(sepText, 1, 0);

  boxSeparator = new QComboBox();
  boxSeparator->addItem(tr("TAB"));
  boxSeparator->addItem(tr("SPACE"));
  boxSeparator->addItem(";" + tr("TAB"));
  boxSeparator->addItem("," + tr("TAB"));
  boxSeparator->addItem(";" + tr("SPACE"));
  boxSeparator->addItem("," + tr("SPACE"));
  boxSeparator->addItem(";");
  boxSeparator->addItem(",");
  boxSeparator->setSizePolicy(
      QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
  boxSeparator->setEditable(true);
  gl1->addWidget(boxSeparator, 1, 1);

  QString help =
      tr("The column separator can be customized. The following special codes "
         "can be used:\n\\t for a TAB character \n\\s for a SPACE");
  help +=
      "\n" +
      tr("The separator must not contain the following characters: 0-9eE.+-");

  boxSeparator->setWhatsThis(help);
  sepText->setWhatsThis(help);
  boxSeparator->setToolTip(help);
  sepText->setToolTip(help);

  boxNames = new QCheckBox(tr("Include Column &Names"));
  boxNames->setChecked(true);

  boxSelection = new QCheckBox(tr("Export &Selection"));
  boxSelection->setChecked(false);

  QVBoxLayout *vl1 = new QVBoxLayout();
  vl1->addLayout(gl1);
  vl1->addWidget(boxNames);
  vl1->addWidget(boxSelection);

  QHBoxLayout *hbox3 = new QHBoxLayout();
  buttonOk = new QPushButton(tr("&OK"));
  buttonOk->setDefault(true);
  hbox3->addWidget(buttonOk);
  buttonCancel = new QPushButton(tr("&Cancel"));
  hbox3->addWidget(buttonCancel);
  buttonHelp = new QPushButton(tr("&Help"));
  hbox3->addWidget(buttonHelp);
  hbox3->addStretch();

  QVBoxLayout *vl = new QVBoxLayout(this);
  vl->addLayout(vl1);
  vl->addStretch();
  vl->addLayout(hbox3);

  // signals and slots connections
  connect(buttonOk, &QPushButton::clicked, this, &ExportDialog::accept);
  connect(buttonCancel, &QPushButton::clicked, this, &ExportDialog::reject);
  connect(buttonHelp, &QPushButton::clicked, this, &ExportDialog::help);
  connect(boxAllTables, &QCheckBox::toggled, this,
          &ExportDialog::enableTableName);
}

void ExportDialog::help() {
  QString s =
      tr("The column separator can be customized. The following special codes "
         "can be used:\n\\t for a TAB character \n\\s for a SPACE");
  s += "\n" +
       tr("The separator must not contain the following characters: 0-9eE.+-");
  QMessageBox::about(0, tr("Help"), s);
}

void ExportDialog::setTableNames(const QStringList &names) {
  boxTable->addItems(names);
}

void ExportDialog::setActiveTableName(const QString &name) {
  boxTable->setCurrentIndex(boxTable->findText(name));
}

void ExportDialog::enableTableName(bool ok) { boxTable->setEnabled(!ok); }

void ExportDialog::accept() {
  QString sep = boxSeparator->currentText();
  sep.replace(tr("TAB"), "\t", Qt::CaseInsensitive);
  sep.replace(tr("SPACE"), " ");
  sep.replace("\\s", " ");
  sep.replace("\\t", "\t");

  if (sep.contains(QRegExp("[0-9.eE+-]"))) {
    QMessageBox::warning(0, tr("Import options error"),
                         tr("The separator must not contain the following "
                            "characters: 0-9eE.+-"));
    return;
  }

  hide();
  if (boxAllTables->isChecked())
    emit exportAllTables(sep, boxNames->isChecked(), boxSelection->isChecked());
  else
    emit exportTable(boxTable->currentText(), sep, boxNames->isChecked(),
                     boxSelection->isChecked());
  close();
}

void ExportDialog::setColumnSeparator(const QString &sep) {
  if (sep == "\t")
    boxSeparator->setCurrentIndex(0);
  else if (sep == " ")
    boxSeparator->setCurrentIndex(1);
  else if (sep == ";\t")
    boxSeparator->setCurrentIndex(2);
  else if (sep == ",\t")
    boxSeparator->setCurrentIndex(3);
  else if (sep == "; ")
    boxSeparator->setCurrentIndex(4);
  else if (sep == ", ")
    boxSeparator->setCurrentIndex(5);
  else if (sep == ";")
    boxSeparator->setCurrentIndex(6);
  else if (sep == ",")
    boxSeparator->setCurrentIndex(7);
  else {
    QString separator = sep;
    boxSeparator->setEditText(
        separator.replace(" ", "\\s").replace("\t", "\\t"));
  }
}

ExportDialog::~ExportDialog() {}
