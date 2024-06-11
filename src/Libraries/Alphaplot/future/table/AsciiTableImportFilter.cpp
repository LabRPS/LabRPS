/***************************************************************************
    File                 : AsciiTableImportFilter.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2008-2009 Knut Franke
    Email (use @ for *)  : Knut.Franke*gmx.net
    Description          : Import an ASCII file as Table.

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#include "Precompiled.h"

#include "future/table/AsciiTableImportFilter.h"

#include <QLocale>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <vector>

#include "future/core/column/Column.h"
#include "future/core/datatypes/String2DoubleFilter.h"
#include "future/lib/IntervalAttribute.h"
#include "future/table/future_Table.h"
//using namespace std;

QStringList AsciiTableImportFilter::fileExtensions() const {
  return QStringList() << QString::fromLatin1("txt")
                       << QString::fromLatin1("csv")
                       << QString::fromLatin1("tsv")
                       << QString::fromLatin1("dat");
}

namespace {
// redirect to QIODevice's readLine so that we can override it to handle '\r'
// line terminators
struct AlphaPlotTextStream {
  QIODevice& input;
  bool good;
  operator bool() const { return good; }
  enum { none, simplify, trim } whiteSpaceTreatment;
  QString separator;
  AlphaPlotTextStream(QIODevice& inp, const QString& sep)
      : input(inp), good(true), whiteSpaceTreatment(none), separator(sep) {}

  QStringList readRow() {
    char c;
    QString r;

    while ((good = input.getChar(&c))) switch (c) {
        case '\r':
          if (input.getChar(&c) && QChar::fromLatin1(c) != QChar::fromLatin1('\n'))  // eat \n following \r
            input.ungetChar(c);
          goto breakLoop;
        case '\n':
          goto breakLoop;
        default:
          r += QChar::fromLatin1(c);
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
void readCols(QList<Column*>& cols, AlphaPlotTextStream& stream,
              bool readColNames, QLocale locale) {
  QStringList row, column_names;
  int i = 0;

  // read first row
  row = stream.readRow();

  int dataSize = row.size();
  std::vector<AP<C> > data(dataSize);
  std::vector<IntervalAttribute<bool>> invalid_cells(row.size());

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
    if (stream || (row != QStringList(QString::fromLatin1("")))) {
      for (i = 0; i < row.size() && i < dataSize; ++i)
        *data[i] << conv<typename C::value_type>(row[i], locale);
      // some rows might have too few columns (re-use value of i from above
      // loop)
      for (; i < dataSize; ++i) {
        invalid_cells[i].setValue(data[i]->size(), true);
        *data[i] << conv<typename C::value_type>(QString::fromLatin1(""), locale);
      }
    }
  }

  for (i = 0; i < dataSize; ++i) {
    cols << new Column(std::move(column_names[i]),
                       std::unique_ptr<C>(std::move(data[i])),
                       std::move(invalid_cells[i]));
    if (i == 0)
      cols.back()->setPlotDesignation(AlphaPlot::X);
    else
      cols.back()->setPlotDesignation(AlphaPlot::Y);
  }
}
}  // namespace

AbstractAspect* AsciiTableImportFilter::importAspect(QIODevice& input) {
  AlphaPlotTextStream stream(input, d_separator);
  if (d_simplify_whitespace)
    stream.whiteSpaceTreatment = AlphaPlotTextStream::simplify;
  else if (d_trim_whitespace)
    stream.whiteSpaceTreatment = AlphaPlotTextStream::trim;

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
  Gui::TableViewProvider* result = new Gui::TableViewProvider(0, 0, 0, tr("Table"));
  result->appendColumns(cols);
  return result;
}
