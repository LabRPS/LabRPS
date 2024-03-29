#include "IconLoader.h"

#include <QFile>
#include <QtDebug>

int IconLoader::lumen_;
QList<int> IconLoader::sizes_;
QList<QString> IconLoader::icon_path_;

void IconLoader::init() {
  sizes_.clear();
  sizes_ << 16 << 22 << 24 << 32 << 48 << 64 << 96 << 128;
  icon_path_.clear();
  icon_path_ << ":icons/dark"
             << ":icons/light"
             << ":icons/common";
}

QIcon IconLoader::load(const QString& name, const IconMode& iconMode) {
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

  const QString locate(filename + "/%1/%2.%3");
  for (int i = 0; i < sizes_.size(); i++) {
    const QString filename_custom_png(
        locate.arg(QString::number(sizes_.at(i)), name, "png"));

    // First check if a png file is available
    if (QFile::exists(filename_custom_png)) {
      ret.addFile(filename_custom_png, QSize(sizes_.at(i), sizes_.at(i)));
    } else {
      const QString filename_custom_svg(
          locate.arg(QString::number(sizes_.at(i)), name, "svg"));
      // Then check if an svg file is available
      if (QFile::exists(filename_custom_svg)) {
        ret.addFile(filename_custom_svg, QSize(sizes_.at(i), sizes_.at(i)));
      } else {
        const QString filename_custom_xpm(
            locate.arg(QString::number(sizes_.at(i)), name, "xpm"));
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
