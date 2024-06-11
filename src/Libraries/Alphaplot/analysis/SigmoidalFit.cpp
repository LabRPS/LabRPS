/***************************************************************************
    File                 : SigmoidalFit.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Sigmoidal (Boltzmann) Fit class

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
#include "MainWindow.h"

#include "SigmoidalFit.h"

#include <QMessageBox>

#include "fit_gsl.h"

SigmoidalFit::SigmoidalFit(Gui::MainWindow *parent, AxisRect2D *axisrect)
    : Fit(parent, axisrect) {
  init();
}

SigmoidalFit::SigmoidalFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                           PlotData::AssociatedData *associateddata)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata);
}

SigmoidalFit::SigmoidalFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                           PlotData::AssociatedData *associateddata,
                           double start, double end)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata, start, end);
}

void SigmoidalFit::init() {
  setObjectName(QString::fromLatin1("Boltzmann"));
  d_f = boltzmann_f;
  d_df = boltzmann_df;
  d_fdf = boltzmann_fdf;
  d_fsimplex = boltzmann_d;
  d_p = 4;
  d_min_points = d_p;
  d_param_init = gsl_vector_alloc(d_p);
  gsl_vector_set_all(d_param_init, 1.0);
  covar = gsl_matrix_alloc(d_p, d_p);
  d_results.resize(d_p);
  d_param_explain << tr("(init value)") << tr("(final value)") << tr("(center)")
                  << tr("(time constant)");
  d_param_names << QString::fromLatin1("A1")
                << QString::fromLatin1("A2")
                << QString::fromLatin1("x0")
                << QString::fromLatin1("dx");
  d_explanation = tr("Boltzmann (Sigmoidal) Fit");
  d_formula = QString::fromLatin1("(A1-A2)/(1+exp((x-x0)/dx))+A2");
}

void SigmoidalFit::calculateFitCurveData(const std::vector<double> &par,
                                         double *X, double *Y) {
  if (d_gen_function) {
    double X0 = d_x[0];
    double step = (d_x[d_n - 1] - X0) / (d_points - 1);
    for (int i = 0; i < d_points; i++) {
      X[i] = X0 + i * step;
      Y[i] = (par[0] - par[1]) / (1 + exp((X[i] - par[2]) / par[3])) + par[1];
    }
  } else {
    for (int i = 0; i < d_points; i++) {
      X[i] = d_x[i];
      Y[i] = (par[0] - par[1]) / (1 + exp((X[i] - par[2]) / par[3])) + par[1];
    }
  }
}

void SigmoidalFit::guessInitialValues() {
  gsl_vector_view x = gsl_vector_view_array(d_x, d_n);
  gsl_vector_view y = gsl_vector_view_array(d_y, d_n);

  double min_out, max_out;
  gsl_vector_minmax(&y.vector, &min_out, &max_out);

  gsl_vector_set(d_param_init, 0, min_out);
  gsl_vector_set(d_param_init, 1, max_out);
  gsl_vector_set(d_param_init, 2, gsl_vector_get(&x.vector, d_n / 2));
  gsl_vector_set(d_param_init, 3, 1.0);
}
