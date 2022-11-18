#ifndef MONTH2DOUBLE_FILTER_H
#define MONTH2DOUBLE_FILTER_H

#include "../AbstractSimpleFilter.h"
#include <QDateTime>
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

/**
 * \brief Conversion filter QDateTime -> double, translating dates into months
 * (January -> 1).
 *
 * \sa QDate::month()
 */
class Month2DoubleFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  virtual double valueAt(int row) const {
    if (!d_inputs.value(0)) return 0;
    return double(d_inputs.value(0)->dateAt(row).month());
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

#endif  // MONTH2DOUBLE_FILTER_H
