#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

#include <QAbstractItemModel>
#include <QColor>
#include <QVector>

namespace future {
class Matrix;
}

//! Model for the access to a Matrix
/**
        This is a model in the sense of Qt4 model/view framework which is used
        to access a Matrix object from any of Qt4s view classes, typically a
   QMatrixView.
        Its main purposes are translating Matrix signals into QAbstractItemModel
   signals
        and translating calls to the QAbstractItemModel read/write API into
   calls
        in the public API of Matrix.
*/
class MatrixModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  //! Constructor
  explicit MatrixModel(future::Matrix *matrix);
  //! Destructor
  ~MatrixModel();

  //! \name Overloaded functions from QAbstractItemModel
  //@{
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex &child) const;
  //@}

 private slots:
  //! \name Handlers for events from Matrix
  //@{
  void handleColumnsAboutToBeInserted(int before, int count);
  void handleColumnsInserted(int first, int count);
  void handleColumnsAboutToBeRemoved(int first, int count);
  void handleColumnsRemoved(int first, int count);
  void handleRowsAboutToBeInserted(int before, int count);
  void handleRowsInserted(int first, int count);
  void handleRowsAboutToBeRemoved(int first, int count);
  void handleRowsRemoved(int first, int count);
  void handleDataChanged(int top, int left, int bottom, int right);
  void handleCoordinatesChanged();
  void handleFormatChanged();
  //@}

 private:
  future::Matrix *d_matrix;
};

#endif  // MATRIXMODEL_H
