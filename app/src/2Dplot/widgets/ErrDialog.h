
#ifndef ERRDIALOG_H
#define ERRDIALOG_H

#include <2Dplot/Graph2DCommon.h>

#include <QDialog>
#include <QList>

class ApplicationWindow;
class QLabel;
class QComboBox;
class QRadioButton;
class QLineEdit;
class QPushButton;
class QGroupBox;
class QButtonGroup;
class QWidget;
class QMdiSubWindow;
class AxisRect2D;
class Table;
class Column;

//! Add error bars dialog
class ErrDialog : public QDialog {
  Q_OBJECT

 public:
  //! Constructor
  /**
   * \param parent parent widget
   * \param fl window flags
   */
  ErrDialog(QWidget* parent, AxisRect2D* axisrect,
            Qt::WindowFlags fl = Qt::Widget);
  //! Destructor
  ~ErrDialog();

 private:
  Column* getErrorCol(Table* parent);
  QLabel* textLabel1;
  QComboBox *nameLabel, *tableNamesBox;
  QGroupBox* groupBox2;
  QGroupBox *groupBox1, *groupBox3;
  QButtonGroup *buttonGroup1, *buttonGroup2;
  QRadioButton *standardBox, *columnBox;
  QRadioButton* percentBox;
  QLineEdit* valueBox;
  QRadioButton* xErrBox;
  QRadioButton* yErrBox;
  QPushButton* buttonAdd;
  QPushButton* buttonCancel;
  QList<QMdiSubWindow*>* srcTables;

 public slots:
  //! Add a plot definition
  void add();
  //! Supply the dialog with a curves list
  void plotNames();
  void errorColumnNames();

 signals:
  //! This is usually connected to the main window's defineErrorBars() slot
  void options(const QString& curveName, int type, const QString& percent,
               int direction);
  //! This is usually connected to the main window's defineErrorBars() slot
  void options(const QString& curveName, const QString& errColumnName,
               int direction);

 private:
  AxisRect2D* axisrect_;
  ApplicationWindow* app_;
  QList<PlotData::AssociatedData> plotted_columns_;
  QList<QPair<Table*, Column*>> error_columns_;
};

#endif  // ERRDIALOG_H
