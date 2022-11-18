#include "DateTime2StringFilter.h"
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

void DateTime2StringFilter::setFormat(const QString& format) {
  exec(new DateTime2StringFilterSetFormatCmd(
      static_cast<DateTime2StringFilter*>(this), format));
}

DateTime2StringFilterSetFormatCmd::DateTime2StringFilterSetFormatCmd(
    DateTime2StringFilter* target, const QString& new_format)
    : d_target(target), d_other_format(new_format) {
  if (d_target->parentAspect())
    setText(QObject::tr("%1: set date-time format to %2")
                .arg(d_target->parentAspect()->name())
                .arg(new_format));
  else
    setText(QObject::tr("set date-time format to %1").arg(new_format));
}

void DateTime2StringFilterSetFormatCmd::redo() {
  QString tmp = d_target->d_format;
  d_target->d_format = d_other_format;
  d_other_format = tmp;
  emit d_target->formatChanged();
}

void DateTime2StringFilterSetFormatCmd::undo() { redo(); }

void DateTime2StringFilter::writeExtraAttributes(
    QXmlStreamWriter* writer) const {
  writer->writeAttribute("format", format());
}

bool DateTime2StringFilter::load(XmlStreamReader* reader) {
  QXmlStreamAttributes attribs = reader->attributes();
  QString str =
      attribs.value(reader->namespaceUri().toString(), "format").toString();

  if (AbstractSimpleFilter::load(reader))
    setFormat(str);
  else
    return false;

  return !reader->hasError();
}
