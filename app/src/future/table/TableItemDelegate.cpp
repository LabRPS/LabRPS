#include <QPainter>
#include <QModelIndex>
#include "TableItemDelegate.h"
#include "TableModel.h"

TableItemDelegate::TableItemDelegate(QObject *parent) : QItemDelegate(parent) {
  d_masking_color = QColor(0xff, 0, 0);
}

void TableItemDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const {
  QItemDelegate::paint(painter, option, index);
  if (!index.data(TableModel::MaskingRole).toBool()) return;
  painter->save();
  // masked cells are displayed as hatched
  painter->fillRect(option.rect, QBrush(d_masking_color, Qt::BDiagPattern));
  painter->restore();
}

void TableItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const {
  model->setData(index, editor->metaObject()->userProperty().read(editor),
                 Qt::EditRole);
}

void TableItemDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const {
  editor->metaObject()->userProperty().write(editor, index.data(Qt::EditRole));
}
