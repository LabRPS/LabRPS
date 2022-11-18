#ifndef XML_STREAM_READER_H
#define XML_STREAM_READER_H

#include <QXmlStreamReader>
#include <QString>
#include <QStringList>
#include "lib/macros.h"

//! XML stream parser that supports errors as well as warnings
/**
 * This class also adds line and column numbers to the error message.
 */
class XmlStreamReader : public QXmlStreamReader {
 public:
  XmlStreamReader();
  XmlStreamReader(QIODevice* device);
  XmlStreamReader(const QByteArray& data);
  XmlStreamReader(const QString& data);
  XmlStreamReader(const char* data);

  QStringList warningStrings() const;
  bool hasWarnings() const;
  void raiseWarning(const QString& message = QString());
  void raiseError(const QString& message = QString());
  CLASS_ACCESSOR(QString, d_error_prefix, errorPrefix, ErrorPrefix)
  CLASS_ACCESSOR(QString, d_error_postfix, errorPostfix, ErrorPostfix)
  CLASS_ACCESSOR(QString, d_warning_prefix, warningPrefix, WarningPrefix)
  CLASS_ACCESSOR(QString, d_warning_postfix, warningPostfix, WarningPostfix)

  //! Go to the next start or end element tag
  /**
   *	If the end of the document is reached, an error is raised.
   *
   * \return false if end of document reached, otherwise true
   */
  bool skipToNextTag();
  //! Go to the end element tag of the current element
  /**
   *	If the end of the document is reached, an error is raised.
   *
   * \return false if end of document reached, otherwise true
   */
  bool skipToEndElement();

  //! Read an XML attribute and convert it to int
  /**
   * \param name attribute name
   * \param ok pointer to report back whether the attribute value could be
   * determined (may be NULL)
   * \return the attriute value if found and converted, otherwise zero (in this
   * case *ok is false)
   */
  int readAttributeInt(const QString& name, bool* ok);
  double readAttributeDouble(const QString& name, bool* ok);
  bool readAttributeBool(const QString& name, bool* ok);
  QString readAttributeString(const QString& name, bool* ok);
  QXmlStreamAttributes readElements(const QString& element, bool* ok);

  QPair<QFont, QColor> readFont(bool* ok);
  QPen readPen(bool* ok);
  QBrush readBrush(bool* ok);

 private:
  QStringList d_warnings;
  QString d_error_prefix;
  QString d_error_postfix;
  QString d_warning_prefix;
  QString d_warning_postfix;

  void init();
};

#endif  // XML_STREAM_READER_H
