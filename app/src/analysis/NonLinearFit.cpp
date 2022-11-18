#include "NonLinearFit.h"

#include <QMessageBox>

#include "fit_gsl.h"
#include "scripting/MyParser.h"

NonLinearFit::NonLinearFit(ApplicationWindow *parent, AxisRect2D *axisrect)
    : Fit(parent, axisrect) {
  init();
}

NonLinearFit::NonLinearFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                           PlotData::AssociatedData *associateddata)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata);
}

NonLinearFit::NonLinearFit(ApplicationWindow *parent, AxisRect2D *axisrect,
                           PlotData::AssociatedData *associateddata,
                           double start, double end)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void NonLinearFit::init() {
  setObjectName(tr("NonLinear"));
  d_formula = QString();
  d_f = user_f;
  d_df = user_df;
  d_fdf = user_fdf;
  d_fsimplex = user_d;
  d_explanation = tr("Non-linear");
  d_init_err = false;
}

void NonLinearFit::setFormula(const QString &s) { d_formula = s; }

void NonLinearFit::setParametersList(const QStringList &lst) {
  if (lst.count() < 1) {
    QMessageBox::critical(
        app_, tr("Fit Error"),
        tr("You must provide a list containing at least one parameter for this "
           "type of fit. Operation aborted!"));
    d_init_err = true;
    return;
  }

  d_init_err = false;
  d_param_names = lst;

  if (d_p > 0) {  // free previously allocated memory
    gsl_vector_free(d_param_init);
    gsl_matrix_free(covar);
  }

  d_p = lst.count();
  d_min_points = d_p;
  d_param_init = gsl_vector_alloc(static_cast<size_t>(d_p));
  gsl_vector_set_all(d_param_init, 1.0);

  covar = gsl_matrix_alloc(static_cast<size_t>(d_p), static_cast<size_t>(d_p));
  d_results.resize(d_p);

  for (int i = 0; i < d_p; i++) d_param_explain << "";
}

void NonLinearFit::calculateFitCurveData(const std::vector<double> &par,
                                         double *X, double *Y) {
  for (int i = 0; i < d_p; i++)
    d_script->setDouble(par[i], d_param_names[i].toUtf8());

  if (d_gen_function) {
    double X0 = d_x[0];
    double step = (d_x[d_n - 1] - X0) / (d_points - 1);
    for (int i = 0; i < d_points; i++) {
      X[i] = X0 + i * step;
      d_script->setDouble(X[i], "x");
      Y[i] = d_script->eval().toDouble();
    }
  } else {
    for (int i = 0; i < d_points; i++) {
      X[i] = d_x[i];
      d_script->setDouble(X[i], "x");
      Y[i] = d_script->eval().toDouble();
    }
  }
}
