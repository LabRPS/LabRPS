#include <QColor>
#include <QImage>
#include <QString>

class Utilities {
 public:
  enum class ColorPal { Light, Dark };
  enum class TableColorProfile { Success, Failure, Generic };
  static int getWordSizeApp();
  static QString getOperatingSystem();
  static int getWordSizeOfOS();
  static QColor getRandColorGoldenRatio(const ColorPal &colpal);
  static QString splitstring(const QString &string);
  static QString joinstring(const QString &string);

  static QDateTime stripDateTimeToFormat(const QDateTime &datetime,
                                         const QString &format);

  static QImage convertToGrayScale(const QImage &srcImage);
  static QImage convertToGrayScaleFast(const QImage &srcImage);

  // html Formatting
  static QString makeHtmlTable(const int row, const int column,
                               const bool hasheader,
                               const TableColorProfile &profile);

 private:
  Utilities() {}
  static double rgbRandomSeed_;
  static int rgbCounter_;
};
