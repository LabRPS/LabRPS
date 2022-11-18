#ifndef DOUBLE2DATE_TIME_FILTER_H
#define DOUBLE2DATE_TIME_FILTER_H

#include "NumericDateTimeBaseFilter.h"

/**
 * \brief Conversion filter double -> QDateTime.
 *
 * The equivalence of one unit defaults to a day if nothing else is specified.
 * The default reference date/time if none is specified, or an invalid one is
 * given, is the noon of January 1st, 4713 BC as per Julian Day Number
 * convention.
 */
class Double2DateTimeFilter : public NumericDateTimeBaseFilter {
  Q_OBJECT

 public:
  // The equivalence of one unit defaults to a day if nothing else is specified.
  // Default offset date is the noon of January 1st, 4713 BC as per Julian Day
  // Number convention. Double2DateTimeFilter(const UnitInterval unit =
  // UnitInterval::Day, const QDateTime& date_time_0 = zeroOffsetDate) :
  Double2DateTimeFilter(const UnitInterval unit, const QDateTime &date_time_0)
      : NumericDateTimeBaseFilter(unit, date_time_0){};

  virtual QDate dateAt(int row) const { return dateTimeAt(row).date(); }
  virtual QTime timeAt(int row) const { return dateTimeAt(row).time(); }
  virtual QDateTime dateTimeAt(int row) const {
    if (!d_inputs.value(0)) return QDateTime();
    double input_value = d_inputs.value(0)->valueAt(row);
    return makeDateTime(input_value);
  }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDateTime;
  }

  //! Explicit conversion from base class using conversion ctor
  explicit Double2DateTimeFilter(const NumericDateTimeBaseFilter &numeric)
      : NumericDateTimeBaseFilter(numeric){};

 protected:
  //! Using typed ports: only double inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn *source) {
    return source->dataType() == LabRPS::TypeDouble;
  }
};

#endif  // ifndef DOUBLE2DATE_TIME_FILTER_H
