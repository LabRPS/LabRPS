#ifndef NONLINEARFIT_H
#define NONLINEARFIT_H

#include "Fit.h"

class NonLinearFit : public Fit {
  Q_OBJECT

 public:
  NonLinearFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  NonLinearFit(ApplicationWindow *parent, AxisRect2D *axisrect,
               PlotData::AssociatedData *associateddata);
  NonLinearFit(ApplicationWindow *parent, AxisRect2D *axisrect,
               PlotData::AssociatedData *associateddata, double start,
               double end);

  void setParametersList(const QStringList &lst);
  void setFormula(const QString &s);

 private:
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
  void init();
};

#endif  // NONLINEARFIT_H
