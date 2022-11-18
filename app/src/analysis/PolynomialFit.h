#ifndef POLYNOMIALFIT_H
#define POLYNOMIALFIT_H

#include "Fit.h"

class PolynomialFit : public Fit {
  Q_OBJECT

 public:
  PolynomialFit(ApplicationWindow *parent, AxisRect2D *axisrect, int order = 2);
  PolynomialFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                PlotData::AssociatedData *associateddata, int order = 2);
  PolynomialFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                PlotData::AssociatedData *associateddata, double start,
                double end, int order = 2);

  QString legendInfo() override;
  void fit() override;

  static QString generateFormula(int order);
  static QStringList generateParameterList(int order);

 private:
  void init();
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;

  int d_order;
};

class LinearFit : public Fit {
  Q_OBJECT

 public:
  LinearFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  LinearFit(ApplicationWindow *parent, AxisRect2D *axisrect,
            PlotData::AssociatedData *associateddata);
  LinearFit(ApplicationWindow *parent, AxisRect2D *axisrect,
            PlotData::AssociatedData *associateddata, double start, double end);

  void fit() override;

 private:
  void init();
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
};

#endif  // POLYNOMIALFIT_H
