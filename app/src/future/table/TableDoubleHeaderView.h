#ifndef TABLEDOUBLEHEADERVIEW_H
#define TABLEDOUBLEHEADERVIEW_H

#include <QHeaderView>
#include "TableModel.h"

//! Slave header for TableDoubleHeaderView
/**
 * This class is only to be used by TableDoubleHeaderView.
 * It allows for displaying two horizontal headers in a TableView.
 * A TableCommentsHeaderView displays the column comments
 * in a second header below the normal header. It is completely
 * controlled by a TableDoubleHeaderView object and thus has
 * a master-slave relationship to it. This would be an inner class
 * of TableDoubleHeaderView if Qt allowed this.
 */
class TableCommentsHeaderView : public QHeaderView {
  Q_OBJECT

 public:
  TableCommentsHeaderView(QWidget *parent = 0);
  virtual ~TableCommentsHeaderView();

  virtual void setModel(QAbstractItemModel *model);
  virtual QSize sizeHint() const;

  friend class TableDoubleHeaderView;  // access to paintSection (protected)
};

//! Horizontal header for TableView displaying comments in a second header
/*
 * This class is only to be used by TableView.
 * It allows for displaying two horizontal headers.
 * A TableDoubleHeaderView displays the column name, plot designation, and
 * type icon in a normal QHeaderView and below that a second header
 * which displays the column comments.
 *
 * \sa TableCommentsHeaderView
 * \sa QHeaderView
 */
class TableDoubleHeaderView : public QHeaderView {
  Q_OBJECT

 private:
  TableCommentsHeaderView *d_slave;
  static int tableHeaderHeight;

 public:
  TableDoubleHeaderView(QWidget *parent = 0);
  ~TableDoubleHeaderView();

  virtual void setModel(QAbstractItemModel *model);
  virtual QSize sizeHint() const;
  //! Show or hide (if on = false) the column comments
  void showComments(bool on = true);
  //! Return whether comments are show currently
  bool areCommentsShown() const;

 protected:
  //void mouseMoveEvent(QMouseEvent *event);

 public slots:
  // adjust geometry and repaint header
  void refresh();
  // React to a header data change
  void headerDataChanged(Qt::Orientation orientation, int logicalFirst,
                         int logicalLast);

 protected slots:
  void sectionsInserted(const QModelIndex &parent, int logicalFirst,
                        int logicalLast);

 protected:
  virtual void paintSection(QPainter *painter, const QRect &rect,
                            int logicalIndex) const;

  //! Flag: show/high column comments
  bool d_show_comments;
};

#endif  // TABLEDOUBLEHEADERVIEW_H
