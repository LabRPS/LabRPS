/***************************************************************************
    File                 : PolynomialFit.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Polynomial Fit and Linear Fit classes

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#include "Precompiled.h"

#include "PolynomialFit.h"
#include "MainWindow.h"

#include <future/core/column/Column.h>
#include <analysis/Filter.h>
#include <Table.h>

#include <QLocale>
#include <QMessageBox>

#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>

PolynomialFit::PolynomialFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                             int order)
    : Fit(parent, axisrect), d_order(order) {
  init();
}

PolynomialFit::PolynomialFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                             PlotData::AssociatedData *associateddata,
                             int order)
    : Fit(parent, axisrect), d_order(order) {
  init();
  setDataFromCurve(associateddata);
}

PolynomialFit::PolynomialFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                             PlotData::AssociatedData *associateddata,
                             double start, double end, int order)
    : Fit(parent, axisrect), d_order(order) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void PolynomialFit::init() {
  setObjectName(tr("Poly"));
  is_non_linear = false;
  d_explanation = tr("Polynomial");
  d_p = d_order + 1;
  d_min_points = d_p;

  covar = gsl_matrix_alloc(static_cast<size_t>(d_p), static_cast<size_t>(d_p));
  d_results.resize(d_p);

  d_formula = generateFormula(d_order);
  d_param_names = generateParameterList(d_order);

  for (int i = 0; i < d_p; i++) d_param_explain << QString::fromLatin1("");
}

QString PolynomialFit::generateFormula(int order) {
  QString formula;
  for (int i = 0; i < order + 1; i++) {
    QString par = QString::fromLatin1("a") + QString::number(i);
    formula += par;
    if (i > 0) formula += QString::fromLatin1("*x");
    if (i > 1) formula += QString::fromLatin1("^") + QString::number(i);
    if (i != order) formula += QString::fromLatin1("+");
  }
  return formula;
}

QStringList PolynomialFit::generateParameterList(int order) {
  QStringList lst;
    for (int i = 0; i < order + 1; i++) lst << QString::fromLatin1("a") + QString::number(i);
  return lst;
}

void PolynomialFit::calculateFitCurveData(const std::vector<double> &par, double *X, double *Y) {
  if (d_gen_function) {
    double X0 = d_x[0];
    double step = (d_x[d_n - 1] - X0) / (d_points - 1);
    for (int i = 0; i < d_points; i++) {
      X[i] = X0 + i * step;
      double yi = 0.0;
      for (int j = 0; j < d_p; j++) yi += par[j] * pow(X[i], j);

      Y[i] = yi;
    }
  } else {
    for (int i = 0; i < d_points; i++) {
      X[i] = d_x[i];
      double yi = 0.0;
      for (int j = 0; j < d_p; j++) yi += par[j] * pow(X[i], j);

      Y[i] = yi;
    }
  }
}

void PolynomialFit::fit() {
  if (d_init_err) return;

  if (d_p > d_n) {
    QMessageBox::critical(app_, tr("Fit Error"),
                          tr("You need at least %1 data points for this fit "
                             "operation. Operation aborted!")
                              .arg(d_p));
    return;
  }

  gsl_matrix *X =
      gsl_matrix_alloc(static_cast<size_t>(d_n), static_cast<size_t>(d_p));
  gsl_vector *c = gsl_vector_alloc(static_cast<size_t>(d_p));

  for (int i = 0; i < d_n; i++) {
    for (int j = 0; j < d_p; j++)
      gsl_matrix_set(X, static_cast<size_t>(i), static_cast<size_t>(j),
                     pow(d_x[i], j));
  }

  gsl_vector_view y = gsl_vector_view_array(d_y, static_cast<size_t>(d_n));

  gsl_vector *weights = gsl_vector_alloc(static_cast<size_t>(d_n));
  for (int i = 0; i < d_n; i++)
    gsl_vector_set(weights, static_cast<size_t>(i),
                   1.0 / pow(d_y_errors[i], 2));

  gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(
      static_cast<size_t>(d_n), static_cast<size_t>(d_p));

  if (d_y_error_source == UnknownErrors)
    gsl_multifit_linear(X, &y.vector, c, covar, &chi_2, work);
  else
    gsl_multifit_wlinear(X, weights, &y.vector, c, covar, &chi_2, work);

  for (int i = 0; i < d_p; i++)
    d_results[i] = gsl_vector_get(c, static_cast<size_t>(i));

  gsl_multifit_linear_free(work);
  gsl_matrix_free(X);
  gsl_vector_free(c);
  gsl_vector_free(weights);

 /* if (app_->writeFitResultsToLog)
    app_->updateLog(logFitInfo(d_results, 0, 0,
                               associateddata_->table->name() + QString::fromLatin1("_") +
                                   associateddata_->xcol->name() + QString::fromLatin1("_") +
                                   associateddata_->ycol->name()));*///koffa the way

  generateFitCurve(d_results);
}

QString PolynomialFit::legendInfo() {
  QString legend = QString::fromLatin1("Y=") + QLocale().toString(d_results[0], 'g', d_prec);
  for (int j = 1; j < d_p; j++) {
    double cj = d_results[j];
      if (cj > 0 && !legend.isEmpty()) legend += QString::fromLatin1("+");

    QString s;
    s.sprintf("%.5f", cj);
    if (s != QString::fromLatin1("1.00000")) legend += QLocale().toString(cj, 'g', d_prec);

    legend += QString::fromLatin1("X");
    if (j > 1) legend += QString::fromLatin1("<sup>") + QString::number(j) + QString::fromLatin1("</sup>");
  }
  return legend;
}

/*****************************************************************************
 *
 * Class LinearFit
 *
 *****************************************************************************/

LinearFit::LinearFit(Gui::MainWindow *parent, AxisRect2D *axisrect)
    : Fit(parent, axisrect) {
  init();
}

LinearFit::LinearFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                     PlotData::AssociatedData *associateddata)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata);
}

LinearFit::LinearFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                     PlotData::AssociatedData *associateddata, double start,
                     double end)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void LinearFit::init() {
  d_p = 2;
  d_min_points = d_p;

  covar = gsl_matrix_alloc(static_cast<size_t>(d_p), static_cast<size_t>(d_p));
  d_results.resize(d_p);

  is_non_linear = false;
  d_formula = QString::fromLatin1("A*x+B");
  d_param_names << QString::fromLatin1("B")
                << QString::fromLatin1("A");
  d_param_explain << tr("(y-intercept)") << tr("(slope)");
  d_explanation = tr("Linear Regression");
  setObjectName(tr("Linear"));
}

void LinearFit::fit() {
  if (d_init_err) return;

  if (d_p > d_n) {
    QMessageBox::critical(app_, tr("Fit Error"),
                          tr("You need at least %1 data points for this fit "
                             "operation. Operation aborted!")
                              .arg(d_p));
    return;
  }

  double c0, c1, cov00, cov01, cov11;

  double *weights = new double[static_cast<size_t>(d_n)];
  for (int i = 0; i < d_n; i++) weights[i] = 1.0 / pow(d_y_errors[i], 2);

  if (d_y_error_source == UnknownErrors)
    gsl_fit_linear(d_x, 1, d_y, 1, static_cast<size_t>(d_n), &c0, &c1, &cov00,
                   &cov01, &cov11, &chi_2);
  else
    gsl_fit_wlinear(d_x, 1, weights, 1, d_y, 1, static_cast<size_t>(d_n), &c0,
                    &c1, &cov00, &cov01, &cov11, &chi_2);

  delete[] weights;

  d_results[0] = c0;
  d_results[1] = c1;

  gsl_matrix_set(covar, 0, 0, cov00);
  gsl_matrix_set(covar, 0, 1, cov01);
  gsl_matrix_set(covar, 1, 1, cov11);
  gsl_matrix_set(covar, 1, 0, cov01);

  /*if (app_->writeFitResultsToLog)
    app_->updateLog(logFitInfo(d_results, 0, 0,
                               associateddata_->table->name() + QString::fromLatin1("_") +
                                   associateddata_->xcol->name() + QString::fromLatin1("_") +
                                   associateddata_->ycol->name()));*///koffa the way

  generateFitCurve(d_results);
}

void LinearFit::calculateFitCurveData(const std::vector<double> &par, double *X, double *Y) {
  if (d_gen_function) {
    double X0 = d_x[0];
    double step = (d_x[d_n - 1] - X0) / (d_points - 1);
    for (int i = 0; i < d_points; i++) {
      X[i] = X0 + i * step;
      Y[i] = par[0] + par[1] * X[i];
    }
  } else {
    for (int i = 0; i < d_points; i++) {
      X[i] = d_x[i];
      Y[i] = par[0] + par[1] * X[i];
    }
  }
}
