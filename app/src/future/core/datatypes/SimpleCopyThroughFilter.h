#ifndef SIMPLE_COPY_THROUGH_FILTER_H
#define SIMPLE_COPY_THROUGH_FILTER_H

#include "core/AbstractSimpleFilter.h"
#include "lib/XmlStreamReader.h"
#include <QXmlStreamWriter>

/**
 * \brief Filter which copies the provided input unaltered to the output
 *
 * Most of the necessary methods for this filter are already implemented
 * in AbstractSimpleFilter.
 *
 * The difference between this filter and CopyThroughFilter is that
 * this inherits AbstractColumn and thus can be directly used
 * as input for other filters and plot functions.
 */
class SimpleCopyThroughFilter : public AbstractSimpleFilter {
  Q_OBJECT

 public:
  //!\name Masking
  //@{
  //! Return whether a certain row is masked
  virtual bool isMasked(int row) const {
    return d_inputs.value(0) ? d_inputs.at(0)->isMasked(row) : false;
  }
  //! Return whether a certain interval of rows rows is fully masked
  virtual bool isMasked(Interval<int> i) const {
    return d_inputs.value(0) ? d_inputs.at(0)->isMasked(i) : false;
  }
  //! Return all intervals of masked rows
  virtual QList<Interval<int> > maskedIntervals() const {
    return d_inputs.value(0) ? d_inputs.at(0)->maskedIntervals()
                             : QList<Interval<int> >();
  }
  //@}

 protected:
  //! All types are accepted.
  virtual bool inputAcceptable(int, const AbstractColumn *) { return true; }

  //!\name signal handlers
  //@{
  virtual void inputMaskingAboutToChange(const AbstractColumn *) {
    emit d_output_column->maskingAboutToChange(d_output_column);
  }
  virtual void inputMaskingChanged(const AbstractColumn *) {
    emit d_output_column->maskingChanged(d_output_column);
  }
  //@}
};

#endif  // SIMPLE_COPY_THROUGH_FILTER_H
