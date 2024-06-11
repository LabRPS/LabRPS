#include "Precompiled.h"

#include "CustomCharacterDialog.h"

#include <QDebug>
#include <QValidator>

#include "ui_CustomCharacterDialog.h"

CustomCharacterDialog::CustomCharacterDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui_CustomCharacterDialog) {
  ui->setupUi(this);
  setWindowTitle(QString::fromLatin1("Custom Char"));
  QRegExp rxThreeHexAtTheEnd(QString::fromLatin1("(?:[0-9a-fA-F]{5})"));
  QRegExpValidator *validator = new QRegExpValidator(rxThreeHexAtTheEnd, this);
  ui->lineEdit->setValidator(validator);
  connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [=]() {
    if (!ui->lineEdit->text().trimmed().isEmpty()) {
      int value = ui->lineEdit->text().trimmed().toInt(0, 16);
      if (value && (QChar(value).category() != QChar::Other_NotAssigned)) {
        Q_EMIT customChar(value);
      } else {
        qDebug() << "unassigned unicode hex";
      }
    }
  });
}

CustomCharacterDialog::~CustomCharacterDialog() { delete ui; }
