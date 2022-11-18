#ifndef STRING2DATE_TIME_FILTER_H
#define STRING2DATE_TIME_FILTER_H

#include "core/AbstractSimpleFilter.h"
#include <QDateTime>
#include <QDate>
#include <QTime>

/**
 * \brief Conversion filter QString -> QDateTime.
 *
 * The standard use of this filter is explicitly specifiying the date/time
 * format of the strings
 * on the input, either in the constructor or via setFormat().
 * However, if the input fails to comply to this format, String2DateTimeFilter
 * tries to guess the format, using internal lists of common date and time
 * formats (#date_formats
 * and #time_formats).
 */
class String2DateTimeFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  //! Standard constructor.
  explicit String2DateTimeFilter(QString format = "yyyy-MM-dd hh:mm:ss.zzz")
      : d_format(format) {}
  //! Set the format string to be used for conversion.
  void setFormat(const QString& format);
  //! Return the format string
  /**
   * The default format string is "yyyy-MM-dd hh:mm:ss.zzz".
   * \sa QDate::toString()
   */
  QString format() const { return d_format; }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeDateTime;
  }

  //! \name XML related functions
  //@{
  virtual void writeExtraAttributes(QXmlStreamWriter* writer) const;
  virtual bool load(XmlStreamReader* reader);
  //@}

 signals:
  void formatChanged();

 private:
  friend class String2DateTimeFilterSetFormatCmd;
  //! The format string.
  QString d_format;

  static const QStringList date_formats;
  static const QStringList time_formats;

 public:
  virtual QDateTime dateTimeAt(int row) const;
  virtual QDate dateAt(int row) const { return dateTimeAt(row).date(); }
  virtual QTime timeAt(int row) const { return dateTimeAt(row).time(); }
  virtual bool isInvalid(int row) const {
    const AbstractColumn* col = d_inputs.value(0);
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

 protected:
  //! Using typed ports: only string inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn* source) {
    return source->dataType() == LabRPS::TypeString;
  }
};

class String2DateTimeFilterSetFormatCmd : public QUndoCommand {
 public:
  String2DateTimeFilterSetFormatCmd(String2DateTimeFilter* target,
                                    const QString& new_format);

  virtual void redo();
  virtual void undo();

 private:
  String2DateTimeFilter* d_target;
  QString d_other_format;
};

#endif  // STRING2DATE_TIME_FILTER_H
