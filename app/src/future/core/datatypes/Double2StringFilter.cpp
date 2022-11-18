#include "Double2StringFilter.h"
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

void Double2StringFilter::writeExtraAttributes(QXmlStreamWriter* writer) const {
  writer->writeAttribute("format", QString(QChar(numericFormat())));
  writer->writeAttribute("digits", QString::number(numDigits()));
}

bool Double2StringFilter::load(XmlStreamReader* reader) {
  QXmlStreamAttributes attribs = reader->attributes();
  QString format_str =
      attribs.value(reader->namespaceUri().toString(), "format").toString();
  QString digits_str =
      attribs.value(reader->namespaceUri().toString(), "digits").toString();

  if (AbstractSimpleFilter::load(reader)) {
    bool ok;
    int digits = digits_str.toInt(&ok);
    if ((format_str.size() != 1) || !ok)
      reader->raiseError(tr("missing or invalid format attribute(s)"));
    else {
      setNumericFormat(format_str.at(0).toLatin1());
      setNumDigits(digits);
    }
  } else
    return false;

  return !reader->hasError();
}

void Double2StringFilter::setNumericFormat(char format) {
  exec(new Double2StringFilterSetFormatCmd(this, format));
}

void Double2StringFilter::setNumDigits(int digits) {
  exec(new Double2StringFilterSetDigitsCmd(this, digits));
}

Double2StringFilterSetFormatCmd::Double2StringFilterSetFormatCmd(
    Double2StringFilter* target, char new_format)
    : d_target(target), d_other_format(new_format) {
  if (d_target->parentAspect())
    setText(QObject::tr("%1: set numeric format to '%2'")
                .arg(d_target->parentAspect()->name())
                .arg(new_format));
  else
    setText(QObject::tr("set numeric format to '%1'").arg(new_format));
}

void Double2StringFilterSetFormatCmd::redo() {
  char tmp = d_target->d_format;
  d_target->d_format = d_other_format;
  d_other_format = tmp;
  emit d_target->formatChanged();
}

void Double2StringFilterSetFormatCmd::undo() { redo(); }

Double2StringFilterSetDigitsCmd::Double2StringFilterSetDigitsCmd(
    Double2StringFilter* target, int new_digits)
    : d_target(target), d_other_digits(new_digits) {
  if (d_target->parentAspect())
    setText(QObject::tr("%1: set decimal digits to %2")
                .arg(d_target->parentAspect()->name())
                .arg(new_digits));
  else
    setText(QObject::tr("set decimal digits to %1").arg(new_digits));
}

void Double2StringFilterSetDigitsCmd::redo() {
  int tmp = d_target->d_digits;
  d_target->d_digits = d_other_digits;
  d_other_digits = tmp;
  emit d_target->formatChanged();
}

void Double2StringFilterSetDigitsCmd::undo() { redo(); }
