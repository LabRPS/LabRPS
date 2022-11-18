#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
class QPushButton;
class QCheckBox;
class QComboBox;

//! Export ASCII dialog
class ExportDialog : public QDialog {
  Q_OBJECT

 public:
  //! Constructor
  /**
   * \param parent parent widget
   * \param fl window flags
   */
  ExportDialog(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::Widget);
  //! Destructor
  ~ExportDialog();

 private:
  QPushButton* buttonOk;
  QPushButton* buttonCancel;
  QPushButton* buttonHelp;
  QCheckBox* boxNames;
  QCheckBox* boxSelection;
  QCheckBox* boxAllTables;
  QComboBox* boxSeparator;
  QComboBox* boxTable;

 public slots:
  //! Set the column delimiter
  void setColumnSeparator(const QString& sep);
  //! Set the list of tables
  void setTableNames(const QStringList& names);
  //! Select a table
  void setActiveTableName(const QString& name);

 private slots:
  //! Enable/disable the tables combox box
  /**
   * The tables combo box is disabled when
   * the checkbox "all" is selected.
   */
  void enableTableName(bool ok);

 protected slots:
  //! Accept changes
  void accept();
  //! Display help
  void help();

 signals:
  //! Export one table
  /**
   * \param tableName name of the table to export
   * \param separator separator to be put between the columns
   * \param exportColumnNames flag: column names in the first line or not
   * \param exportSelection flag: export only selection or all cells
   */
  void exportTable(const QString& tableName, const QString& separator,
                   bool exportColumnNames, bool exportSelection);
  //! Export all tables
  /**
   * \param separator separator to be put between the columns
   * \param exportColumnNames flag: column names in the first line or not
   * \param exportSelection flag: export only selection or all cells
   */
  void exportAllTables(const QString& separator, bool exportColumnNames,
                       bool exportSelection);
};

#endif  // ExportDialog_H
