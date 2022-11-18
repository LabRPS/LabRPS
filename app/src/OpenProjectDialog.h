#ifndef OPEN_PROJECT_DIALOG_H
#define OPEN_PROJECT_DIALOG_H

#include "ui/ExtensibleFileDialog.h"

#include <QComboBox>

class OpenProjectDialog : public ExtensibleFileDialog {
  Q_OBJECT
 public:
  enum OpenMode { NewProject, NewFolder };
  OpenProjectDialog(QWidget *parent = nullptr, bool extended = true,
                    Qt::WindowFlags flags = Qt::Widget);
  OpenMode openMode() const { return (OpenMode)d_open_mode->currentIndex(); }

 private:
  QComboBox *d_open_mode;

 protected slots:
  void closeEvent(QCloseEvent *);
  //! Update which options are visible and enabled based on the output format.
  void updateAdvancedOptions(const QString &filter);
};

#endif  // OPEN_PROJECT_DIALOG_H
