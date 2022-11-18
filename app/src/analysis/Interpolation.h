#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Filter.h"

class AxisRect2D;
class Interpolation : public Filter {
  Q_OBJECT

 public:
  enum class InterpolationMethod : int {
    Linear = 0,
    Polynomial = 1,
    Cubic = 2,
    CubicPeriodic = 3,
    Akima = 4,
    AkimaPeriodic = 5,
    Steffen = 6
  };

  Interpolation(ApplicationWindow *parent, AxisRect2D *axisrect,
                PlotData::AssociatedData *associateddata,
                const InterpolationMethod &method);
  Interpolation(ApplicationWindow *parent, AxisRect2D *axisrect,
                PlotData::AssociatedData *associateddata, double start,
                double end, const InterpolationMethod &method);

  InterpolationMethod method() const { return d_method; }
  void setMethod(const InterpolationMethod &method);

 protected:
  virtual bool isDataAcceptable();

 private:
  void init(const InterpolationMethod &method);
  void calculateOutputData(double *x, double *y);

  //! the interpolation method
  InterpolationMethod d_method;
};

#endif  // INTERPOLATION_H
