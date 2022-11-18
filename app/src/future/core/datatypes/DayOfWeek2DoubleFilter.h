#ifndef DAY_OF_WEEK2DOUBLE_FILTER_H
#define DAY_OF_WEEK2DOUBLE_FILTER_H

#include "../AbstractSimpleFilter.h"
#include <QDateTime>
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

//! Conversion filter QDateTime -> double, translating dates into days of the
//! week (Monday -> 1).
class DayOfWeek2DoubleFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  virtual double valueAt(int row) const {
    if (!d_inputs.value(0)) return 0;
    return double(d_inputs.value(0)->dateAt(row).dayOfWeek());
  }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDouble;
  }

 protected:
  //! Using typed ports: only date-time inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn *source) {
    return source->dataType() == LabRPS::TypeDateTime;
  }
};

#endif  // DAY_OF_WEEK2DOUBLE_FILTER_H
