#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QIcon>

class IconLoader {
 public:
  enum IconMode {
    General,
    LightDark,
  };
  static void init();
  static QIcon load(const QString& name, const IconMode& iconMode);
  static int inline isLight(const QColor& color) {
    // convert window background to a scale of darkness to choose which
    // icons(light or dark) to load using something similer to
    // http://stackoverflow.com/questions/12043187/
    // how-to-check-if-hex-color-is-too-black
    return static_cast<int>(0.2126 * color.red() + 0.7152 * color.blue() +
                            0.0722 * color.green());
  }
  static int lumen_;

 private:
  IconLoader() {}

  enum IconType {
    Dark = 0,
    Light = 1,
    Indiscriminate = 2,
  };

  static QList<int> sizes_;
  static QList<QString> icon_path_;
};

#endif  // ICONLOADER_H
