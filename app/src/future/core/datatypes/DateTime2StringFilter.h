#ifndef DATE_TIME2STRING_FILTER_H
#define DATE_TIME2STRING_FILTER_H

#include <QDateTime>
#include <QRegExp>

#include "core/AbstractSimpleFilter.h"

class DateTime2StringFilterSetFormatCmd;

//! Conversion filter QDateTime -> QString.
class DateTime2StringFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  //! Standard constructor.
  explicit DateTime2StringFilter(QString format = "yyyy-MM-dd hh:mm:ss.zzz")
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
    return LabRPS::TypeString;
  }

 signals:
  void formatChanged();

 private:
  friend class DateTime2StringFilterSetFormatCmd;
  //! The format string.
  QString d_format;

 public:
  virtual QString textAt(int row) const {
    if (!d_inputs.value(0)) return QString();
    QDateTime input_value = d_inputs.value(0)->dateTimeAt(row);
    if (!input_value.date().isValid() && input_value.time().isValid())
      input_value.setDate(QDate(1900, 1, 1));
    return input_value.toString(d_format);
  }

  //! \name XML related functions
  //@{
  virtual void writeExtraAttributes(QXmlStreamWriter* writer) const;
  virtual bool load(XmlStreamReader* reader);
  //@}

 protected:
  //! Using typed ports: only DateTime inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn* source) {
    return source->dataType() == LabRPS::TypeDateTime;
  }
};

class DateTime2StringFilterSetFormatCmd : public QUndoCommand {
 public:
  DateTime2StringFilterSetFormatCmd(DateTime2StringFilter* target,
                                    const QString& new_format);

  virtual void redo();
  virtual void undo();

 private:
  DateTime2StringFilter* d_target;
  QString d_other_format;
};

#endif  // DATE_TIME2STRING_FILTER_H
