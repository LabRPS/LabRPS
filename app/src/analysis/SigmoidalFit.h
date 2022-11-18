#ifndef SIGMOIDALFIT_H
#define SIGMOIDALFIT_H

#include "Fit.h"

class SigmoidalFit : public Fit {
  Q_OBJECT

 public:
  SigmoidalFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  SigmoidalFit(ApplicationWindow *parent, AxisRect2D *axisrect,
               PlotData::AssociatedData *associateddata);
  SigmoidalFit(ApplicationWindow *parent, AxisRect2D *axisrect,
               PlotData::AssociatedData *associateddata, double start,
               double end);
  void guessInitialValues() override;

 private:
  void init();
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
};

#endif  // SIGMOIDALFIT_H
