#ifndef ASCII_TABLE_IMPORT_FILTER_H
#define ASCII_TABLE_IMPORT_FILTER_H

#include <QLocale>

#include "core/AbstractImportFilter.h"

//! Import an ASCII file as Table.
/**
 * This is a complete rewrite of equivalent functionality previously found in
 * Table.
 *
 * Originally, this filter wasn't meant to handle conversion of ASCII text to
 * other
 * data types. While it's conceptually elegant and flexible to import text data
 * as
 * text columns, testing this in everyday usage revealed that, for the common
 * use case
 * of importing lots of numeric data, having to convert imported tables to
 * numeric
 * by hand is a bit of a nuisance. Therefore, AsciiTableImportFilter has an
 * option
 * for converting all columns to Numeric. Importing non-numeric data is possible
 * by
 * disabling this and (optionally) converting texts to other formats using
 * Table's
 * type control tab.
 *
 * TODO: port options GUI from ImportTableDialog
 */
class AsciiTableImportFilter : public AbstractImportFilter {
  Q_OBJECT

 public:
  AsciiTableImportFilter()
      : d_ignored_lines(0),
        d_separator("\t"),
        d_first_row_names_columns(true),
        d_trim_whitespace(false),
        d_simplify_whitespace(false),
        d_convert_to_numeric(false),
        d_numeric_locale(QLocale::c()) {}
  virtual AbstractAspect* importAspect(QIODevice& input);
  virtual QStringList fileExtensions() const;
  virtual QString name() const { return QObject::tr("ASCII table"); }

  ACCESSOR(int, ignored_lines)
  Q_PROPERTY(int ignored_lines READ ignored_lines WRITE set_ignored_lines)

  QString separator() const {
    QString result = d_separator;
    return result.replace("\t", "\\t");
  }
  void set_separator(const QString& value) {
    d_separator = value;
    d_separator.replace("\\t", "\t");
  }
  Q_PROPERTY(QString separator READ separator WRITE set_separator)

  ACCESSOR(bool, first_row_names_columns)
  Q_PROPERTY(bool first_row_names_columns READ first_row_names_columns WRITE
                 set_first_row_names_columns)

  ACCESSOR(bool, trim_whitespace)
  Q_PROPERTY(
      bool trim_whitespace READ trim_whitespace WRITE set_trim_whitespace)

  ACCESSOR(bool, simplify_whitespace)
  Q_PROPERTY(bool simplify_whitespace READ simplify_whitespace WRITE
                 set_simplify_whitespace)

  ACCESSOR(bool, convert_to_numeric)
  Q_PROPERTY(bool convert_to_numeric READ convert_to_numeric WRITE
                 set_convert_to_numeric)

  ACCESSOR(QLocale, numeric_locale)
  Q_PROPERTY(
      QLocale numeric_locale READ numeric_locale WRITE set_numeric_locale)

 private:
  int d_ignored_lines;
  QString d_separator;
  bool d_first_row_names_columns;
  bool d_trim_whitespace;
  bool d_simplify_whitespace;
  bool d_convert_to_numeric;
  QLocale d_numeric_locale;
};

#endif  // ASCII_TABLE_IMPORT_FILTER_H
