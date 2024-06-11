#ifndef CUSTOMCHARACTERDIALOG_H
#define CUSTOMCHARACTERDIALOG_H

#include <QDialog>

class Ui_CustomCharacterDialog;

class AlphaplotExport CustomCharacterDialog : public QDialog
{
  Q_OBJECT

public:
  explicit CustomCharacterDialog(QWidget *parent = nullptr);
  ~CustomCharacterDialog();

Q_SIGNALS:
  void customChar(int value);

private:
  Ui_CustomCharacterDialog *ui;
};

#endif // CUSTOMCHARACTERDIALOG_H
