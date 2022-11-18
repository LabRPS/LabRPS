#ifndef DATE_TIME2DOUBLE_FILTER_H
#define DATE_TIME2DOUBLE_FILTER_H

#include "NumericDateTimeBaseFilter.h"

//! Conversion filter QDateTime -> double (using offset from selected datetime).
class DateTime2DoubleFilter : public NumericDateTimeBaseFilter {
  Q_OBJECT

 public:
  // The equivalence of one unit defaults to a day if nothing else is specified.
  // Default offset date is the noon of January 1st, 4713 BC as per Julian Day
  // Number convention. DateTime2DoubleFilter(const UnitInterval unit =
  // UnitInterval::Day, const QDateTime& date_time_0 = zeroOffsetDate) :
  DateTime2DoubleFilter(const UnitInterval unit, const QDateTime &date_time_0)
      : NumericDateTimeBaseFilter(unit, date_time_0){};

  virtual double valueAt(int row) const {
    if (!d_inputs.value(0)) return 0.0;
    QDateTime input_value = d_inputs.value(0)->dateTimeAt(row);
    return offsetToDouble(input_value);
  }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDouble;
  }

  //! Explicit conversion from base class using conversion ctor
  explicit DateTime2DoubleFilter(const NumericDateTimeBaseFilter &numeric)
      : NumericDateTimeBaseFilter(numeric){};

 protected:
  //! Using typed ports: only DateTime inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn *source) {
    return source->dataType() == LabRPS::TypeDateTime;
  }
};

#endif  // ifndef DATE_TIME2DOUBLE_FILTER_H
