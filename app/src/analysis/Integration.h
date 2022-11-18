#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "Filter.h"

class AxisRect2D;

class Integration : public Filter {
  Q_OBJECT

 public:
  enum InterpolationMethod { Linear, Cubic, Akima };

  Integration(ApplicationWindow *parent, AxisRect2D *axisrect);
  Integration(ApplicationWindow *parent, AxisRect2D *axisrect,
              PlotData::AssociatedData *associateddata);
  Integration(ApplicationWindow *parent, AxisRect2D *axisrect,
              PlotData::AssociatedData *associateddata, double start, double end);

  InterpolationMethod method() { return d_method; }
  void setMethod(InterpolationMethod method) {
    InterpolationMethod backup = d_method;
    d_method = method;
    if (!isDataAcceptable()) d_method = backup;
  }

  double result() { return d_result; }

 protected:
  virtual bool isDataAcceptable();

 private:
  void init();
  QString logInfo();
  void output() {}

  //! The method for computing the interpolation used for integrating.
  InterpolationMethod d_method;

  double d_result;
};

#endif  // INTEGRATION_H
