/***************************************************************************
    File                 : PluginFit.cpp
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Plugin Fit class

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

#include "PluginFit.h"
#include "MainWindow.h"

#include <QLibrary>
#include <QMessageBox>

PluginFit::PluginFit(Gui::MainWindow *parent, AxisRect2D *axisrect)
    : Fit(parent, axisrect) {
  init();
}

PluginFit::PluginFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
                     PlotData::AssociatedData *associateddata)
    : Fit(parent, axisrect) {
  init();
  setDataFromCurve(associateddata);
}

PluginFit::PluginFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
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
                              .arg(QString::fromLatin1("function_d")));
    return false;
  }

  d_f = (fit_function)lib.resolve("function_f");
  if (!d_f) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for Levenberg-Marquardt fitting.")
                              .arg(QString::fromLatin1("function_f")));
    return false;
  }

  d_df = (fit_function_df)lib.resolve("function_df");
  if (!d_df) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for Levenberg-Marquardt fitting.")
                              .arg(QString::fromLatin1("function_df")));
    return false;
  }

  d_fdf = (fit_function_fdf)lib.resolve("function_fdf");
  if (!d_fdf) {
    QMessageBox::critical(app_, tr("Plugin Error"),
                          tr("The plugin does not implement a %1 method "
                             "necessary for Levenberg-Marquardt fitting.")
                              .arg(QString::fromLatin1("function_fdf")));
    return false;
  }

  f_eval = (fitFunctionEval)lib.resolve("function_eval");
  if (!f_eval) return false;

  typedef char *(*fitFunc)();
  fitFunc fitFunction = (fitFunc)lib.resolve("parameters");
  if (fitFunction) {
    d_param_names = QString::fromLatin1(fitFunction()).split(QString::fromLatin1(","), QString::SkipEmptyParts);
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
    d_param_explain = QString::fromLatin1(fitExplain()).split(QString::fromLatin1(","), QString::SkipEmptyParts);
  else
      for (int i = 0; i < d_p; i++) d_param_explain << QString::fromLatin1("");

  fitFunction = (fitFunc)lib.resolve("name");
  setObjectName(QString::fromLatin1(fitFunction()));

  fitFunction = (fitFunc)lib.resolve("function");
  if (fitFunction)
    d_formula = QString::fromLatin1((fitFunction()));
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
