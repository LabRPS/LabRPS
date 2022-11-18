#include "PluginFit.h"

#include <QLibrary>
#include <QMessageBox>

PluginFit::PluginFit(ApplicationWindow *parent, AxisRect2D *axisrect)
    : Fit(parent, axisrect) {
  init();
}

PluginFit::PluginFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                     PlotData::AssociatedData *associateddata)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata);
}

PluginFit::PluginFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                     PlotData::AssociatedData *associateddata, double start,
                     double end)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void PluginFit::init() { d_explanation = tr("Plugin Fit"); }

bool PluginFit::load(const QString &pluginName) {
  if (!QFile::exists(pluginName)) {
    QMessageBox::critical(
        app_, tr("File not found"),
        tr("Plugin file: <p><b> %1 </b> <p>not found. Operation aborted!")
            .arg(pluginName));
    return false;
  }

  setObjectName(pluginName);
  QLibrary lib(pluginName);

  d_fsimplex = (fit_function_simplex)lib.resolve("function_d");
  if (!d_fsimplex) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for simplex fitting.")
                              .arg("function_d"));
    return false;
  }

  d_f = (fit_function)lib.resolve("function_f");
  if (!d_f) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for Levenberg-Marquardt fitting.")
                              .arg("function_f"));
    return false;
  }

  d_df = (fit_function_df)lib.resolve("function_df");
  if (!d_df) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for Levenberg-Marquardt fitting.")
                              .arg("function_df"));
    return false;
  }

  d_fdf = (fit_function_fdf)lib.resolve("function_fdf");
  if (!d_fdf) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for Levenberg-Marquardt fitting.")
                              .arg("function_fdf"));
    return false;
  }

  f_eval = (fitFunctionEval)lib.resolve("function_eval");
  if (!f_eval) return false;

  typedef char *(*fitFunc)();
  fitFunc fitFunction = (fitFunc)lib.resolve("parameters");
  if (fitFunction) {
    d_param_names = QString(fitFunction()).split(",", QString::SkipEmptyParts);
    d_p = d_param_names.count();
    d_min_points = d_p;
    d_param_init = gsl_vector_alloc(static_cast<size_t>(d_p));
    covar =
        gsl_matrix_alloc(static_cast<size_t>(d_p), static_cast<size_t>(d_p));
    d_results.resize(d_p);
  } else
    return false;

  fitFunc fitExplain = (fitFunc)lib.resolve("explanations");
  if (fitExplain)
    d_param_explain = QString(fitExplain()).split(",", QString::SkipEmptyParts);
  else
    for (int i = 0; i < d_p; i++) d_param_explain << "";

  fitFunction = (fitFunc)lib.resolve("name");
  setObjectName(QString(fitFunction()));

  fitFunction = (fitFunc)lib.resolve("function");
  if (fitFunction)
    d_formula = QString(fitFunction());
  else
    return false;

  return true;
}

void PluginFit::calculateFitCurveData(const std::vector<double> &par, double *X,
                                      double *Y) {
  if (d_gen_function) {
    double X0 = d_x[0];
    double step = (d_x[d_n - 1] - X0) / (d_points - 1);
    for (int i = 0; i < d_points; i++) {
      X[i] = X0 + i * step;
      Y[i] = f_eval(X[i], const_cast<double*>(&par[0]));
    }
  } else {
    for (int i = 0; i < d_points; i++) {
      X[i] = d_x[i];
      Y[i] = f_eval(X[i], const_cast<double*>(&par[0]));
    }
  }
}
