#include "table/AsciiTableImportFilter.h"

#include <QLocale>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <vector>

#include "core/column/Column.h"
#include "core/datatypes/String2DoubleFilter.h"
#include "lib/IntervalAttribute.h"
#include "table/future_Table.h"
using namespace std;

QStringList AsciiTableImportFilter::fileExtensions() const {
  return QStringList() << "txt"
                       << "csv"
                       << "tsv"
                       << "dat";
}

namespace {
// redirect to QIODevice's readLine so that we can override it to handle '\r'
// line terminators
struct LabRPSTextStream {
  QIODevice& input;
  bool good;
  operator bool() const { return good; }
  enum { none, simplify, trim } whiteSpaceTreatment;
  QString separator;
  LabRPSTextStream(QIODevice& inp, const QString& sep)
      : input(inp), good(true), whiteSpaceTreatment(none), separator(sep) {}

  QStringList readRow() {
    char c;
    QString r;

    while ((good = input.getChar(&c))) switch (c) {
        case '\r':
          if (input.getChar(&c) && c != '\n')  // eat \n following \r
            input.ungetChar(c);
          goto breakLoop;
        case '\n':
          goto breakLoop;
        default:
          r += c;
      };
  breakLoop:
    switch (whiteSpaceTreatment) {
      case none:
        return r.split(separator);
      case simplify:
        return r.simplified().split(separator);
      case trim:
        return r.trimmed().split(separator);
      default:
        return QStringList();
    }
  }
};

template <class C>
C conv(const QString& x, const QLocale locale);
template <>
QString conv<QString>(const QString& x, const QLocale locale) {
  Q_UNUSED(locale)
  return x;
}
template <>
double conv<double>(const QString& x, const QLocale locale) {
  return locale.toDouble(x);
}
// we are not using float for now
/*template <>
float conv<float>(const QString& x) {
  return x.toFloat();
}*/

template <class T>
struct AP : public std::unique_ptr<T> {
  AP() : std::unique_ptr<T>(new T) {}
  AP(const AP& x) : std::unique_ptr<T>(new T(*x)) {}
};

template <class C>
void readCols(QList<Column*>& cols, LabRPSTextStream& stream,
              bool readColNames, QLocale locale) {
  QStringList row, column_names;
  int i = 0;

  // read first row
  row = stream.readRow();

  int dataSize = row.size();
  vector<AP<C> > data(dataSize);
  vector<IntervalAttribute<bool> > invalid_cells(row.size());

  if (readColNames)
    column_names = row;
  else
    for (i = 0; i < row.size(); ++i) {
      column_names << QString::number(i + 1);
      *data[i] << conv<typename C::value_type>(row[i], locale);
    }

  // read rest of data
  while (stream) {
    row = stream.readRow();
    if (stream || (row != QStringList(""))) {
      for (i = 0; i < row.size() && i < dataSize; ++i)
        *data[i] << conv<typename C::value_type>(row[i], locale);
      // some rows might have too few columns (re-use value of i from above
      // loop)
      for (; i < dataSize; ++i) {
        invalid_cells[i].setValue(data[i]->size(), true);
        *data[i] << conv<typename C::value_type>("", locale);
      }
    }
  }

  for (i = 0; i < dataSize; ++i) {
    cols << new Column(std::move(column_names[i]),
                       unique_ptr<C>(std::move(data[i])),
                       std::move(invalid_cells[i]));
    if (i == 0)
      cols.back()->setPlotDesignation(LabRPS::X);
    else
      cols.back()->setPlotDesignation(LabRPS::Y);
  }
}
}  // namespace

AbstractAspect* AsciiTableImportFilter::importAspect(QIODevice& input) {
  LabRPSTextStream stream(input, d_separator);
  if (d_simplify_whitespace)
    stream.whiteSpaceTreatment = LabRPSTextStream::simplify;
  else if (d_trim_whitespace)
    stream.whiteSpaceTreatment = LabRPSTextStream::trim;

  // skip ignored lines
  for (int i = 0; i < d_ignored_lines; i++) stream.readRow();

  // build a Table from the gathered data
  QList<Column*> cols;
  if (d_convert_to_numeric)
    readCols<QVector<qreal> >(cols, stream, d_first_row_names_columns,
                              d_numeric_locale);
  else
    readCols<QStringList>(cols, stream, d_first_row_names_columns,
                          d_numeric_locale);

  // renaming will be done by the kernel
  future::Table* result = new future::Table(0, 0, 0, tr("Table"));
  result->appendColumns(cols);
  return result;
}
