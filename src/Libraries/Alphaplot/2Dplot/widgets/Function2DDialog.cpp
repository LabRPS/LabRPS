#include "Precompiled.h"

#include "Function2DDialog.h"
#include "2Dplot/AxisRect2D.h"
#include "muparser/muParser.h"
//#include "ApplicationWindow.h"
#include "scripting/MyParser.h"
#include "ui_Function2DDialog.h"

#include <QMessageBox>

Function2DDialog::Function2DDialog(QWidget *parent)
    : QDialog(parent),
      ui_(new Ui_Function2DDialog),
      axisrect_(nullptr),
      plottomodify_(-1) {
  ui_->setupUi(this);
  setSizeGripEnabled(true);

  // set ranges
  ui_->normpointsSpinBox->setRange(2, 1000000);
  ui_->normpointsSpinBox->setSingleStep(100);
  ui_->parampointsSpinBox->setRange(2, 1000000);
  ui_->parampointsSpinBox->setSingleStep(100);
  ui_->polarpointsSpinBox->setRange(2, 1000000);
  ui_->polarpointsSpinBox->setSingleStep(100);

  // set default values
  ui_->normfofxTextEdit->setMinimumWidth(350);
  ui_->normfromxLineEdit->setText(QString::fromLatin1("0"));
  ui_->normtoxLineEdit->setText(QString::fromLatin1("1"));
  ui_->normpointsSpinBox->setValue(100);
  ui_->paramparameterLineEdit->setText(QString::fromLatin1("m"));
  ui_->paramfromLineEdit->setText(QString::fromLatin1("0"));
  ui_->paramtoLineEdit->setText(QString::fromLatin1("1"));
  ui_->parampointsSpinBox->setValue(100);
  ui_->polarparameterLineEdit->setText(QString::fromLatin1("t"));
  ui_->polarfromLineEdit->setText(QString::fromLatin1("0"));
  ui_->polartoLineEdit->setText(QString::fromLatin1("pi"));
  ui_->polarpointsSpinBox->setValue(100);
  ui_->dialogButtonBox->button(QDialogButtonBox::Ok)->setDefault(true);
  setFocusProxy(ui_->normfofxTextEdit);

  connect(ui_->functionComboBox, SIGNAL(activated(int)), this,
          SLOT(raiseWidget(int)));
  connect(ui_->dialogButtonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()),
          this, SLOT(accept()));
  connect(ui_->dialogButtonBox->button(QDialogButtonBox::Close),
          SIGNAL(clicked()), this, SLOT(close()));
  connect(ui_->clearfunction_pushButton, SIGNAL(clicked()), this,
          SLOT(clearList()));
}

Function2DDialog::~Function2DDialog() { delete ui_; }

void Function2DDialog::setLayout2DToModify(AxisRect2D *axisrect,
                                           int plottomidify) {
  if (!axisrect) return;
  axisrect_ = axisrect;

  plottomodify_ = plottomidify;
  if (plottomodify_ == -1) {
  }
}

void Function2DDialog::raiseWidget(const int index) const {
  (index == 0) ? ui_->clearfunction_pushButton->setText(tr("Clear list"))
               : ui_->clearfunction_pushButton->setText(tr("Clear Function"));
  ui_->functionStackedWidget->setCurrentIndex(index);
}

bool Function2DDialog::apply() {
  bool result = true;
  switch (ui_->functionComboBox->currentIndex()) {
    case 0:
      result = acceptFunction();
      break;

    case 1:
      result = acceptParametric();
      break;

    case 2:
      // result = acceptPolar();
      break;
  }
  return result;
}

void Function2DDialog::accept() {
  if (apply()) {
    /*close();*/
  }
  return QDialog::accept();
}

bool Function2DDialog::acceptFunction() {
  QString from = ui_->normfromxLineEdit->text().toLower();
  QString to = ui_->normtoxLineEdit->text().toLower();
  // QString points = ui_->normpointsSpinBox->text().toLower();

  double start, end;
  try {
    MyParser parser;
    parser.SetExpr(from.toUtf8().constData());
    start = parser.Eval();
  }
  catch (mu::ParserError& error) {
    QMessageBox::critical(nullptr, tr("Start limit error"), QString::fromStdString(error.GetMsg()));
    ui_->normfromxLineEdit->setFocus();
    return false;
  }
  try {
    MyParser parser;
    parser.SetExpr(to.toUtf8().constData());
    end = parser.Eval();
  }
  catch (mu::ParserError& error) {
    QMessageBox::critical(nullptr, tr("End limit error"), QString::fromStdString(error.GetMsg()));
    ui_->normtoxLineEdit->setFocus();
    return false;
  }

  if (start >= end) {
    QMessageBox::critical(nullptr, tr("Input error"),
                          tr("Please enter x limits that satisfy: from < end!"));
    ui_->normtoxLineEdit->setFocus();
    return false;
  }

  QString formula = ui_->normfofxTextEdit->toPlainText().replace(QChar::ParagraphSeparator, QString::fromLatin1("\n"));

  // Collecting all the information
  this->type = ui_->functionComboBox->currentIndex();
  formulas += formula;
  ranges += start;
  ranges += end;
  points = ui_->normpointsSpinBox->value();
  return true;
}

bool Function2DDialog::acceptParametric() {
  QString from = ui_->paramfromLineEdit->text().toLower();
  QString to = ui_->paramtoLineEdit->text().toLower();
  // QString points = ui_->parampointsSpinBox->text().toLower();

  double start, end;
  try {
    MyParser parser;
    parser.SetExpr(from.toUtf8().constData());
    start = parser.Eval();
  }
  catch (mu::ParserError& error) {
    QMessageBox::critical(nullptr, tr("Start limit error"), QString::fromStdString(error.GetMsg()));
    ui_->paramfromLineEdit->setFocus();
    return false;
  }

  try {
    MyParser parser;
    parser.SetExpr(to.toUtf8().constData());
    end = parser.Eval();
  }
  catch (mu::ParserError& error) {
    QMessageBox::critical(nullptr, tr("End limit error"), QString::fromStdString(error.GetMsg()));
    ui_->paramtoLineEdit->setFocus();
    return false;
  }

  if (start >= end) {
    QMessageBox::critical(nullptr, tr("Input error"),
                          tr("Please enter parameter limits that satisfy: from < end!"));
    ui_->paramtoLineEdit->setFocus();
    return false;
  }

  QString xformula = ui_->paramxLineEdit->text().replace(QChar::ParagraphSeparator, QString::fromLatin1("\n"));
  QString yformula = ui_->paramyLineEdit->text().replace(QChar::ParagraphSeparator,QString::fromLatin1( "\n"));

  // Collecting all the information
  type = ui_->functionComboBox->currentIndex();
  formulas += xformula;
  formulas += yformula;
  ranges += start;
  ranges += end;
  theText = ui_->paramparameterLineEdit->text();
  return true;
}

void Function2DDialog::clearList() {
  switch (ui_->functionComboBox->currentIndex()) {
    case 0:
      ui_->normfofxTextEdit->clear();
      break;

    case 1:
      ui_->paramxLineEdit->clear();
      ui_->paramyLineEdit->clear();
      Q_EMIT clearParamFunctionsList();
      break;

    case 2:
      ui_->polarxLineEdit->clear();
      ui_->polaryLineEdit->clear();
      Q_EMIT clearPolarFunctionsList();
      break;
  }
}

void Function2DDialog::insertParamFunctionsList(const QStringList &xList,
                                                const QStringList &yList) {
  if (xList.size() > 0) {
    ui_->paramxLineEdit->setText(xList.at(0));
  }
  if (yList.size() > 0) {
    ui_->paramyLineEdit->setText(yList.at(0));
  }
}

void Function2DDialog::insertPolarFunctionsList(const QStringList &rList,
                                                const QStringList &thetaList) {
  if (rList.size() > 0) {
    ui_->polarxLineEdit->setText(rList.at(0));
  }
  if (thetaList.size() > 0) {
    ui_->polaryLineEdit->setText(thetaList.at(0));
  }
}
