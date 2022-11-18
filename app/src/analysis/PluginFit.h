#ifndef PLUGINFIT_H
#define PLUGINFIT_H

#include "Fit.h"

class AxisRect2D;

class PluginFit : public Fit {
  Q_OBJECT

 public:
  PluginFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  PluginFit(ApplicationWindow *parent, AxisRect2D *axisrect,
            PlotData::AssociatedData *associateddata);
  PluginFit(ApplicationWindow *parent, AxisRect2D *axisrect,
            PlotData::AssociatedData *associateddata, double start, double end);

  bool load(const QString &pluginName);

 private:
  void init();
  typedef double (*fitFunctionEval)(double, double *);
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
  fitFunctionEval f_eval;
};

#endif  // PLUGINFIT_H
