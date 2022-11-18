#ifndef TABLE_STATISTICS_H
#define TABLE_STATISTICS_H

#include "Table.h"

/*!\brief Table that computes and displays statistics on another Table.
 *
 * \section tablestats_future Future Plans
 * Make it possible to add new columns/rows to be monitored.
 */
class TableStatistics : public Table {
  Q_OBJECT

 public:
  //! supported statistics types
  enum Type { StatRow, StatColumn };
  TableStatistics(ScriptingEnv *env, QWidget *parent, Table *base, Type,
                  QList<int> targets);
  //! return the type of statistics
  Type type() const { return d_type; }
  //! return the base table of which statistics are displayed
  Table *base() const { return d_base; }

 public slots:
  //! update statistics after a column has changed (to be connected with
  //! Table::modifiedData)
  void update(Table *, const QString &colName);
  //! handle renaming of columns (to be connected with Table::changedColHeader)
  void renameCol(const QString &, const QString &);
  //! remove statistics of removed columns (to be connected with
  //! Table::removedCol)
  void removeCol(const QString &);

 protected:
  bool eventFilter(QObject *watched, QEvent *event);

 private:
  Table *d_base;
  Type d_type;
  QList<int> d_targets;
};

#endif  // TABLE_STATISTICS_H
