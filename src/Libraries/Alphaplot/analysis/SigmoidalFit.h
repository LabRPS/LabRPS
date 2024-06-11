/***************************************************************************
    File                 : SigmoidalFit.h
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
#ifndef SIGMOIDALFIT_H
#define SIGMOIDALFIT_H

#include "Fit.h"

namespace Gui {
    class MainWindow;
}

class AlphaplotExport SigmoidalFit : public Fit {
  Q_OBJECT

 public:
  SigmoidalFit(Gui::MainWindow *parent, AxisRect2D *axisrect);
  SigmoidalFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
               PlotData::AssociatedData *associateddata);
  SigmoidalFit(Gui::MainWindow *parent, AxisRect2D *axisrect,
               PlotData::AssociatedData *associateddata, double start,
               double end);
  void guessInitialValues() override;

 private:
  void init();
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
};

#endif  // SIGMOIDALFIT_H
