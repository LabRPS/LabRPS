#ifndef OBJECTBROWSERTREEITEMMODEL_H
#define OBJECTBROWSERTREEITEMMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ObjectBrowserTreeItem;

class ObjectBrowserTreeItemModel : public QAbstractItemModel {
 public:
  ObjectBrowserTreeItemModel(ObjectBrowserTreeItem *item,
                             QObject *parent = nullptr);
  ~ObjectBrowserTreeItemModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  void resetModel() { emit endResetModel(); }

 private:
  ObjectBrowserTreeItem *rootItem_;
};

#endif  // OBJECTTREEITEMMODEL_H
