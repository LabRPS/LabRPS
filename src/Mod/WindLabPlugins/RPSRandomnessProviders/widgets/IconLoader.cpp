/* This file is part of AlphaPlot.

   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   AlphaPlot is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   AlphaPlot is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with AlphaPlot.  If not, see <http://www.gnu.org/licenses/>.

   Description : AlphaPlot icon loader
*/
//#include "PreCompiled.h"

#include "IconLoader.h"

#include <QFile>
#include <QtDebug>

using namespace WindLab;

int IconLoader::lumen_;
QList<int> IconLoader::sizes_;
QList<QString> IconLoader::icon_path_;

void IconLoader::init() {
  sizes_.clear();
  sizes_ << 16 << 22 << 24 << 32 << 48 << 64 << 96 << 128;
  icon_path_.clear();
  icon_path_ << QString::fromLatin1(":icons/dark")
             << QString::fromLatin1(":icons/light")
             << QString::fromLatin1(":icons/common");
}

QIcon IconLoader::load(const QString& name, const IconMode& iconMode) {

    init();

  QIcon ret;
  // If the icon name is empty
  if (name.isEmpty()) {
    qDebug() << "Icon name is null";
    return ret;
  }

  QString filename;
  switch (iconMode) {
    case LightDark:
      (lumen_ < 100) ? filename = icon_path_.at(Dark)
                     : filename = icon_path_.at(Light);
      break;
    case General:
      filename = icon_path_.at(Indiscriminate);
      break;
    default:
      // should never reach
      qDebug() << "Unknown IconMode";
      break;
  }

  const QString locate(filename + QString::fromLatin1("/%1/%2.%3"));
  for (int i = 0; i < sizes_.size(); i++) {
    const QString filename_custom_png(
        locate.arg(sizes_.at(i)).arg(name).arg(QString::fromLatin1("png")));

    // First check if a png file is available
    if (QFile::exists(filename_custom_png)) {
      ret.addFile(filename_custom_png, QSize(sizes_.at(i), sizes_.at(i)));
    } else {
      const QString filename_custom_svg(
          locate.arg(sizes_.at(i)).arg(name).arg(QString::fromLatin1("svg")));
      // Then check if an svg file is available
      if (QFile::exists(filename_custom_svg)) {
        ret.addFile(filename_custom_svg, QSize(sizes_.at(i), sizes_.at(i)));
      } else {
        const QString filename_custom_xpm(
            locate.arg(sizes_.at(i)).arg(name).arg(QString::fromLatin1("xpm")));
        // Then check if an xpm file is available
        if (QFile::exists(filename_custom_xpm)) {
          ret.addFile(filename_custom_xpm, QSize(sizes_.at(i), sizes_.at(i)));
        }
      }
    }
  }

  // if no icons are found, then...
  if (ret.isNull()) {
    qDebug() << "Couldn't load icon" << name;
  }
  return ret;
}
