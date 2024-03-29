#include "AbstractSimpleFilter.h"
#include <QtDebug>

// TODO: should simple filters have a name argument?
AbstractSimpleFilter::AbstractSimpleFilter()
    : AbstractFilter("SimpleFilter"),
      d_output_column(new SimpleFilterColumn(this)) {
  addChild(d_output_column);
}

void AbstractSimpleFilter::clearMasks() {
  emit d_output_column->maskingAboutToChange(d_output_column);
  d_masking.clear();
  emit d_output_column->maskingChanged(d_output_column);
}

void AbstractSimpleFilter::setMasked(Interval<int> i, bool mask) {
  emit d_output_column->maskingAboutToChange(d_output_column);
  d_masking.setValue(i, mask);
  emit d_output_column->maskingChanged(d_output_column);
}

void AbstractSimpleFilter::inputPlotDesignationAboutToChange(
    const AbstractColumn *) {
  emit d_output_column->plotDesignationAboutToChange(d_output_column);
}

void AbstractSimpleFilter::inputPlotDesignationChanged(const AbstractColumn *) {
  emit d_output_column->plotDesignationChanged(d_output_column);
}

void AbstractSimpleFilter::inputModeAboutToChange(const AbstractColumn *) {
  emit d_output_column->dataAboutToChange(d_output_column);
}

void AbstractSimpleFilter::inputModeChanged(const AbstractColumn *) {
  emit d_output_column->dataChanged(d_output_column);
}

void AbstractSimpleFilter::inputDataAboutToChange(const AbstractColumn *) {
  emit d_output_column->dataAboutToChange(d_output_column);
}

void AbstractSimpleFilter::inputDataChanged(const AbstractColumn *) {
  emit d_output_column->dataChanged(d_output_column);
}

void AbstractSimpleFilter::inputRowsAboutToBeInserted(
    const AbstractColumn *source, int before, int count) {
  Q_UNUSED(source);
  Q_UNUSED(count);
  foreach (Interval<int> output_range,
           dependentRows(Interval<int>(before, before)))
    emit d_output_column->rowsAboutToBeInserted(
        d_output_column, output_range.start(), output_range.size());
}

void AbstractSimpleFilter::inputRowsInserted(const AbstractColumn *source,
                                             int before, int count) {
  Q_UNUSED(source);
  Q_UNUSED(count);
  foreach (Interval<int> output_range,
           dependentRows(Interval<int>(before, before)))
    emit d_output_column->rowsInserted(d_output_column, output_range.start(),
                                       output_range.size());
}

void AbstractSimpleFilter::inputRowsAboutToBeRemoved(
    const AbstractColumn *source, int first, int count) {
  Q_UNUSED(source);
  foreach (Interval<int> output_range,
           dependentRows(Interval<int>(first, first + count - 1)))
    emit d_output_column->rowsAboutToBeRemoved(
        d_output_column, output_range.start(), output_range.size());
}

void AbstractSimpleFilter::inputRowsRemoved(const AbstractColumn *source,
                                            int first, int count) {
  Q_UNUSED(source);
  foreach (Interval<int> output_range,
           dependentRows(Interval<int>(first, first + count - 1)))
    emit d_output_column->rowsRemoved(d_output_column, output_range.start(),
                                      output_range.size());
}

AbstractColumn *AbstractSimpleFilter::output(int port) {
  return port == 0 ? static_cast<AbstractColumn *>(d_output_column) : 0;
}

const AbstractColumn *AbstractSimpleFilter::output(int port) const {
  return port == 0 ? static_cast<const AbstractColumn *>(d_output_column) : 0;
}

void AbstractSimpleFilter::save(QXmlStreamWriter *writer) const {
  writer->writeStartElement("simple_filter");
  writeBasicAttributes(writer);
  writeExtraAttributes(writer);
  writer->writeAttribute("filter_name", metaObject()->className());
  writeCommentElement(writer);
  writer->writeEndElement();
}

bool AbstractSimpleFilter::load(XmlStreamReader *reader) {
  if (reader->isStartElement() && reader->name() == "simple_filter") {
    if (!readBasicAttributes(reader)) return false;

    QXmlStreamAttributes attribs = reader->attributes();
    QString str =
        attribs.value(reader->namespaceUri().toString(), "filter_name")
            .toString();
    if (str != metaObject()->className()) {
      reader->raiseError(tr("incompatible filter type"));
      return false;
    }

    // read child elements
    while (!reader->atEnd()) {
      reader->readNext();

      if (reader->isEndElement()) break;

      if (reader->isStartElement()) {
        if (reader->name() == "comment") {
          if (!readCommentElement(reader)) return false;
        } else  // unknown element
        {
          reader->raiseWarning(
              tr("unknown element '%1'").arg(reader->name().toString()));
          if (!reader->skipToEndElement()) return false;
        }
      }
    }
  } else
    reader->raiseError(tr("no simple filter element found"));

  return !reader->hasError();
}
