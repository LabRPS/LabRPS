/***************************************************************************
    File                 : globals.cpp
    Description          : Definition of global constants and enums
    --------------------------------------------------------------------
    Copyright            : (C) 2006-2009 Tilman Benkert (thzs*gmx.net)
    Copyright            : (C) 2006-2007 Ion Vasilief (ion_vasilief*yahoo.fr)
                           (replace * with @ in the email addresses)

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
#include "PreCompiled.h"

#include "globals.h"

#include <QDate>
#include <QIcon>
#include <QMessageBox>
#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>
#include <QtDebug>

const int AlphaPlot::AlphaPlot_versionNo = 1022022;
const char* AlphaPlot::AlphaPlot_version = "1.02";
const char* AlphaPlot::extra_version = "stable";
const QDate AlphaPlot::release_date =
    QDate::fromString(QString::fromLatin1("18-01-2022"), QString::fromLatin1("dd-MM-yyyy"));
const char* AlphaPlot::homepage_Uri = "https://labrps.com/";
const char* AlphaPlot::manual_Uri = "https://alphaplot.sourceforge.io/wiki";
const char* AlphaPlot::forum_Uri = "https://sourceforge.net/p/alphaplot/discussion/";
const char* AlphaPlot::bugreport_Uri = "https://github.com/narunlifescience/AlphaPlot/issues/new";
const char* AlphaPlot::download_Uri ="https://sourceforge.net/projects/alphaplot/";
const char* AlphaPlot::wiki_Uri = "https://wiki.labrps.com/";

QStringList AlphaPlot::locales_ = QStringList();

int AlphaPlot::version() { return AlphaPlot_versionNo; }

QString AlphaPlot::schemaVersion() {
  return QString::fromLatin1("AlphaPlot ") + QString::number((version() & 0xFF0000) >> 16) + QString::fromLatin1(".") +
         QString::number((version() & 0x00FF00) >> 8) + QString::fromLatin1(".") +
         QString::number(version() & 0x0000FF);
}

QString AlphaPlot::versionString() {return QString::fromLatin1(AlphaPlot_version); }

QString AlphaPlot::extraVersion() {return QString::fromLatin1(extra_version); }

QString AlphaPlot::releaseDateString() {
  return release_date.toString(QString::fromLatin1("dd-MM-yyyy"));
}

QDate AlphaPlot::releaseDate() { return release_date; }

QString AlphaPlot::originalAuthor() {return QString::fromLatin1("Arun Narayanankutty"); }

QString AlphaPlot::originalAuthorWithMail() {
  return QString::fromLatin1("Arun Narayanankutty: <n.arun.lifescience@gmail.com");
}

QStringList AlphaPlot::getLocales() { return locales_; }

void AlphaPlot::setLocales(QStringList locales) { locales_ = locales; }

QString AlphaPlot::enumValueToString(int key, const QString& enum_name) {
  int index = staticMetaObject.indexOfEnumerator(enum_name.toUtf8());
    if (index == -1) return QString::fromLatin1("invalid");
  QMetaEnum meta_enum = staticMetaObject.enumerator(index);
  return QString::fromLatin1(meta_enum.valueToKey(key));
}

int AlphaPlot::enumStringToValue(const QString& string,
                                 const QString& enum_name) {
  int index = staticMetaObject.indexOfEnumerator(enum_name.toUtf8());
  if (index == -1) return -1;
  QMetaEnum meta_enum = staticMetaObject.enumerator(index);
  return meta_enum.keyToValue(string.toUtf8());
}
