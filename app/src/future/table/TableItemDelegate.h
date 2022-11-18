#ifndef TABLE_ITEM_DELIGATE_H
#define TABLE_ITEM_DELIGATE_H

#include <QItemDelegate>
#include <QtDebug>
#include <QMetaProperty>
#include <QAbstractItemModel>

//! Item delegate for TableView
class TableItemDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  //! Standard constructor.
  TableItemDelegate(QObject *parent = 0);
  //! Custom cell painting.
  virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;
  //! Set the color for masked cells
  void setMaskingColor(const QColor &color) { d_masking_color = color; }
  //! Return the color for masked cells
  QColor maskingColor() const { return d_masking_color; }
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

 private:
  //! The color for masked cells
  QColor d_masking_color;
};

#endif  // TABLE_ITEM_DELIGATE_H
