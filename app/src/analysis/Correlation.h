#ifndef CORRELATION_H
#define CORRELATION_H

#include "Filter.h"

class Correlation : public Filter {
  Q_OBJECT

 public:
  Correlation(ApplicationWindow* parent, Table* t, const QString& colName1,
              const QString& colName2);

  void setDataFromTable(Table* t, const QString& colName1,
                        const QString& colName2);

 protected:
  //! Handles the graphical output
  void addResultCurve();

 private:
  virtual void output();
};

#endif  // CORRELATION_H
