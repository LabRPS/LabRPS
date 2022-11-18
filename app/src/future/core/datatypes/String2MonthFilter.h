#ifndef STRING2MONTH_FILTER_H
#define STRING2MONTH_FILTER_H

#include "../AbstractSimpleFilter.h"
#include <QDateTime>
#include <math.h>
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

//! Conversion filter String -> QDateTime, interpreting the input as months of
//! the year (either numeric or "Jan" etc).
class String2MonthFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  virtual QDate dateAt(int row) const { return dateTimeAt(row).date(); }

  virtual QTime timeAt(int row) const { return dateTimeAt(row).time(); }

  virtual QDateTime dateTimeAt(int row) const {
    if (!d_inputs.value(0)) return QDateTime();

    QString input_value = d_inputs.value(0)->textAt(row);
    bool ok;
    int month_value = input_value.toInt(&ok);
    if (!ok) {
      QDate temp = QDate::fromString(input_value, "MMM");
      if (!temp.isValid()) temp = QDate::fromString(input_value, "MMMM");
      if (!temp.isValid())
        return QDateTime();
      else
        month_value = temp.month();
    }

    // Don't use Julian days here since support for years < 1 is bad
    // Use 1900-01-01 instead
    QDate result_date = QDate(1900, 1, 1).addMonths(month_value - 1);
    QTime result_time = QTime(0, 0, 0, 0);
    return QDateTime(result_date, result_time);
  }
  virtual bool isInvalid(int row) const {
    const AbstractColumn *col = d_inputs.value(0);
    if (!col) return false;
    return !(dateTimeAt(row).isValid()) || col->isInvalid(row);
  }
  virtual bool isInvalid(Interval<int> i) const {
    if (!d_inputs.value(0)) return false;
    for (int row = i.start(); row <= i.end(); row++) {
      if (!isInvalid(row)) return false;
    }
    return true;
  }
  virtual QList<Interval<int> > invalidIntervals() const {
    IntervalAttribute<bool> validity;
    if (d_inputs.value(0)) {
      int rows = d_inputs.value(0)->rowCount();
      for (int i = 0; i < rows; i++) validity.setValue(i, isInvalid(i));
    }
    return validity.intervals();
  }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDateTime;
  }

 protected:
  virtual bool inputAcceptable(int, const AbstractColumn *source) {
    return source->dataType() == LabRPS::TypeString;
  }
};

#endif  // STRING2MONTH_FILTER_H
