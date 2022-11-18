#ifndef NUMERIC_DATETIME_BASE_FILTER_H
#define NUMERIC_DATETIME_BASE_FILTER_H

#include <QDate>
#include <QDateTime>
#include <QTime>

#include "../AbstractSimpleFilter.h"

/**
 * \brief Base for conversion filters double <-> QDateTime.
 * This class is intended to hold all logic for conversion between double to
 * QDateTime and vice versa.
 */

class NumericDateTimeBaseFilter : public AbstractSimpleFilter {
  Q_OBJECT
 public:
  // default offset date (zero offset) - the noon of January 1st, 4713 BC as per
  // Julian Day Number convention
  static const QDateTime zeroOffsetDate;
  // scoped enumeration to prevent potential mixing with many other similiar
  // names
  enum class UnitInterval : int {
    Year,
    Month,
    Day,
    Hour,
    Minute,
    Second,
    Millisecond
  };

  NumericDateTimeBaseFilter(const UnitInterval unit = UnitInterval::Day,
                            const QDateTime &date_time_0 = zeroOffsetDate)
      : m_unit_interval(unit),
        m_date_time_0(
            (date_time_0.isValid())
                ? (date_time_0)
                : (zeroOffsetDate)){};  // default to zeroOffsetDate if invalid
                                        // datetime provided

  NumericDateTimeBaseFilter(const NumericDateTimeBaseFilter &other)
      : m_unit_interval(other.m_unit_interval),
        m_date_time_0(other.m_date_time_0){};

  //! Save to XML
  void writeExtraAttributes(QXmlStreamWriter *writer) const override;

  bool load(XmlStreamReader *reader) override;

  UnitInterval getUnitInterval() const { return m_unit_interval; }
  QDateTime getBaseDateTime() const { return m_date_time_0; }

 protected:
  // convert the given date to double wrt unit, offset and base date
  double offsetToDouble(const QDateTime &m_offset) const;
  // convert the given numerical offset to DateTime wrt unit and base date
  QDateTime makeDateTime(double input_value) const;

 private:
  UnitInterval m_unit_interval;
  QDateTime m_date_time_0;

  void setUnitInterval(const UnitInterval unit);
  void setBaseDateTime(const QDateTime &date);
};

#endif  // ifndef NUMERIC_DATETIME_BASE_FILTER_H
