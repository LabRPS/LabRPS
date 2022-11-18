#ifndef DOUBLE2DAY_OF_WEEK_FILTER_H
#define DOUBLE2DAY_OF_WEEK_FILTER_H

#include "../AbstractSimpleFilter.h"
#include <QDateTime>
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

//! Conversion filter double -> QDateTime, interpreting the input numbers as
//! days of the week (1 = Monday).
class Double2DayOfWeekFilter : public AbstractSimpleFilter {
  Q_OBJECT
 public:
  virtual QDate dateAt(int row) const {
    if (!d_inputs.value(0)) return QDate();
    // Don't use Julian days here since support for years < 1 is bad
    // Use 1900-01-01 instead (a Monday)
    return QDate(1900, 1, 1)
        .addDays(qRound(d_inputs.value(0)->valueAt(row) - 1.0));
  }
  virtual QTime timeAt(int row) const {
    Q_UNUSED(row)
    return QTime(0, 0, 0, 0);
  }
  virtual QDateTime dateTimeAt(int row) const {
    return QDateTime(dateAt(row), timeAt(row));
  }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDateTime;
  }

 protected:
  //! Using typed ports: only double inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn *source) {
    return source->dataType() == LabRPS::TypeDouble;
  }
};

#endif  // DOUBLE2DAY_OF_WEEK_FILTER_H
