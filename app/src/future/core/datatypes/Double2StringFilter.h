#ifndef DOUBLE2STRING_FILTER_H
#define DOUBLE2STRING_FILTER_H

#include "../AbstractSimpleFilter.h"
#include <QLocale>
#include <QChar>
#include <QtDebug>

//! Locale-aware conversion filter double -> QString.
class Double2StringFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  //! Standard constructor.
  explicit Double2StringFilter(char format = 'e', int digits = 6)
      : d_format(format), d_digits(digits) {}
  //! Set format character as in QString::number
  void setNumericFormat(char format);
  //! Set number of displayed digits
  void setNumDigits(int digits);
  //! Get format character as in QString::number
  char numericFormat() const { return d_format; }
  //! Get number of displayed digits
  int numDigits() const { return d_digits; }

  //! Return the data type of the column
  virtual LabRPS::ColumnDataType dataType() const {
    return LabRPS::TypeString;
  }

 signals:
  void formatChanged();

 private:
  friend class Double2StringFilterSetFormatCmd;
  friend class Double2StringFilterSetDigitsCmd;
  //! Format character as in QString::number
  char d_format;
  //! Display digits or precision as in QString::number
  int d_digits;

  //! \name XML related functions
  //@{
  virtual void writeExtraAttributes(QXmlStreamWriter* writer) const;
  virtual bool load(XmlStreamReader* reader);
  //@}

 public:
  virtual QString textAt(int row) const {
    if (!d_inputs.value(0)) return QString();
    if (d_inputs.value(0)->rowCount() <= row) return QString();
    if (d_inputs.value(0)->isInvalid(row)) return QString();
    return QLocale().toString(d_inputs.value(0)->valueAt(row), d_format,
                              d_digits);
  }

 protected:
  //! Using typed ports: only double inputs are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn* source) {
    return source->dataType() == LabRPS::TypeDouble;
  }
};

class Double2StringFilterSetFormatCmd : public QUndoCommand {
 public:
  Double2StringFilterSetFormatCmd(Double2StringFilter* target, char new_format);

  virtual void redo();
  virtual void undo();

 private:
  Double2StringFilter* d_target;
  char d_other_format;
};

class Double2StringFilterSetDigitsCmd : public QUndoCommand {
 public:
  Double2StringFilterSetDigitsCmd(Double2StringFilter* target, int new_digits);

  virtual void redo();
  virtual void undo();

 private:
  Double2StringFilter* d_target;
  int d_other_digits;
};

#endif  // DOUBLE2STRING_FILTER_H
