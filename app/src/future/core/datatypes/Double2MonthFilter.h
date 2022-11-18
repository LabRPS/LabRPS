#ifndef DOUBLE2MONTH_FILTER_H
#define DOUBLE2MONTH_FILTER_H

#include "../AbstractSimpleFilter.h"
#include <QDateTime>
#include <math.h>
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

//! Conversion filter double -> QDateTime, interpreting the input numbers as
//! months of the year.
class Double2MonthFilter : public AbstractSimpleFilter {
  Q_OBJECT
 public:
  virtual QDate dateAt(int row) const { return dateTimeAt(row).date(); }
  virtual QTime timeAt(int row) const { return dateTimeAt(row).time(); }
  virtual QDateTime dateTimeAt(int row) const {
    if (!d_inputs.value(0)) return QDateTime();
    double input_value = d_inputs.value(0)->valueAt(row);
    // Don't use Julian days here since support for years < 1 is bad
    // Use 1900-01-01 instead
    QDate result_date = QDate(1900, 1, 1).addMonths(qRound(input_value - 1.0));
    QTime result_time = QTime(0, 0, 0, 0);
    return QDateTime(result_date, result_time);
  }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDateTime;
  }

 protected:
  virtual bool inputAcceptable(int, const AbstractColumn *source) {
    return source->dataType() == LabRPS::TypeDouble;
  }
};

#endif  // DOUBLE2MONTH_FILTER_H
