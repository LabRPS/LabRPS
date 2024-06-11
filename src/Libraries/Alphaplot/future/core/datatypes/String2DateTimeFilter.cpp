/***************************************************************************
    File                 : String2DateTimeFilter.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2007 by Tilman Benkert,
                           Knut Franke
    Email (use @ for *)  : thzs*gmx.net, knut.franke*gmx.de
    Description          : Conversion filter QString -> QDateTime.

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

#include "String2DateTimeFilter.h"

#include <QStringList>
#include <QXmlStreamWriter>

#include "future/lib/XmlStreamReader.h"

const QStringList String2DateTimeFilter::date_formats = {
    QString::fromLatin1("yyyy-M-d"),  // ISO 8601 w/ and w/o leading zeros
    QString::fromLatin1("yyyy/M/d"),
    QString::fromLatin1("d/M/yyyy"),  // European style day/month order (this order seems to be used
                 // in more countries than the US style M/d/yyyy)
    QString::fromLatin1("d/M/yy"), QString::fromLatin1("d-M-yyyy"), QString::fromLatin1("d-M-yy"),
    QString::fromLatin1("d.M.yyyy"),  // German style
    QString::fromLatin1("d.M.yy"), QString::fromLatin1("M/yyyy"),
    QString::fromLatin1("d.M."),  // German form w/o year
    QString::fromLatin1("yyyyMMdd")};

const QStringList String2DateTimeFilter::time_formats = {
    QString::fromLatin1("h"),           QString::fromLatin1("h ap"),        QString::fromLatin1("h:mm"),      QString::fromLatin1("h:mm ap"), QString::fromLatin1("h:mm:ss"),
    QString::fromLatin1("h:mm:ss.zzz"), QString::fromLatin1("h:mm:ss:zzz"), QString::fromLatin1("mm:ss.zzz"), QString::fromLatin1("hmmss")};

QDateTime String2DateTimeFilter::dateTimeAt(int row) const {
  if (!d_inputs.value(0)) return QDateTime();
  QString input_value = d_inputs.value(0)->textAt(row);
  if (input_value.isEmpty()) return QDateTime();

  // first try the selected format string d_format
  QDateTime result = QDateTime::fromString(input_value, d_format);
  if (result.isValid()) return result;

  // fallback:
  // try other format strings built from date_formats and time_formats
  // comma and space are valid separators between date and time
  QStringList strings =
      input_value.simplified().split(QString::fromLatin1(","), QString::SkipEmptyParts);
  if (strings.size() == 1)
    strings = strings.at(0).split(QString::fromLatin1(" "), QString::SkipEmptyParts);

  if (strings.size() < 1)
    return result;  // invalid date/time from first attempt

  QDate date_result;
  QTime time_result;

  QString date_string = strings.at(0).trimmed();
  QString time_string;
  if (strings.size() > 1)
    time_string = strings.at(1).trimmed();
  else
    time_string = date_string;

  // try to find a valid date
  for (const auto &format : date_formats) {
    date_result = QDate::fromString(date_string, format);
    if (date_result.isValid()) break;
  }

  // try to find a valid time
  for (const auto &format : time_formats) {
    time_result = QTime::fromString(time_string, format);
    if (time_result.isValid()) break;
  }

  if (!date_result.isValid() && time_result.isValid())
    date_result.setDate(1900, 1, 1);  // this is what QDateTime does e.g. for
                                      // QDateTime::fromString("00:00","hh:mm");
  return QDateTime(date_result, time_result);
}

void String2DateTimeFilter::writeExtraAttributes(
    QXmlStreamWriter *writer) const {
  writer->writeAttribute(QString::fromLatin1("format"), format());
}

bool String2DateTimeFilter::load(XmlStreamReader *reader) {
  QXmlStreamAttributes attribs = reader->attributes();
  QString str =
      attribs.value(reader->namespaceUri().toString(), QString::fromLatin1("format")).toString();

  if (AbstractSimpleFilter::load(reader))
    setFormat(str);
  else
    return false;

  return !reader->hasError();
}

void String2DateTimeFilter::setFormat(const QString &format) {
  exec(new String2DateTimeFilterSetFormatCmd(this, format));
}

String2DateTimeFilterSetFormatCmd::String2DateTimeFilterSetFormatCmd(
    String2DateTimeFilter *target, const QString &new_format)
    : d_target(target), d_other_format(new_format) {
  if (d_target->parentAspect())
    setText(QObject::tr("%1: set date-time format to %2")
                .arg(d_target->parentAspect()->name(), new_format));
  else
    setText(QObject::tr("set date-time format to %1").arg(new_format));
}

void String2DateTimeFilterSetFormatCmd::redo() {
  QString tmp = d_target->d_format;
  d_target->d_format = d_other_format;
  d_other_format = tmp;
  Q_EMIT d_target->formatChanged();
}

void String2DateTimeFilterSetFormatCmd::undo() { redo(); }
