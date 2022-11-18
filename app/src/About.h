#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include "ui_About.h"

class About : public QDialog {
  Q_OBJECT
 public:
  About(QWidget* parent = nullptr);

 private:
  Ui_About ui_;
};

#endif  // ABOUT_H
