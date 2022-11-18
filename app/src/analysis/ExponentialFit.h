#ifndef EXPONENTIALFIT_H
#define EXPONENTIALFIT_H

#include "Fit.h"

class ExponentialFit : public Fit {
  Q_OBJECT

 public:
  ExponentialFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                 bool expGrowth = false);
  ExponentialFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                 PlotData::AssociatedData *associateddata,
                 bool expGrowth = false);
  ExponentialFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                 PlotData::AssociatedData *associateddata, double start,
                 double end, bool expGrowth = false);

 private:
  void init();
  void storeCustomFitResults(const std::vector<double> &par) override;
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;

  bool is_exp_growth;
};

class TwoExpFit : public Fit {
  Q_OBJECT

 public:
  TwoExpFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  TwoExpFit(ApplicationWindow *parent, AxisRect2D *axisrect,
            PlotData::AssociatedData *associateddata);
  TwoExpFit(ApplicationWindow *parent, AxisRect2D *axisrect,
            PlotData::AssociatedData *associateddata, double start, double end);

 private:
  void init();
  void storeCustomFitResults(const std::vector<double> &par) override;
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
};

class ThreeExpFit : public Fit {
  Q_OBJECT

 public:
  ThreeExpFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  ThreeExpFit(ApplicationWindow *parent, AxisRect2D *axisrect,
              PlotData::AssociatedData *associateddata);
  ThreeExpFit(ApplicationWindow *parent, AxisRect2D *axisrect,
              PlotData::AssociatedData *associateddata, double start,
              double end);

 private:
  void init();
  void storeCustomFitResults(const std::vector<double> &par) override;
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
};

#endif  // EXPONENTIALFIT_H
