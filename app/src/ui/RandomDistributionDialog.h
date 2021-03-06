/* This file is part of LabPlot & LabRPS.
   Copyright 2014, Alexander Semke <alexander.semke@web.de>
   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   LabRPS is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   LabRPS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with LabRPS.  If not, see <http://www.gnu.org/licenses/>.

   Description : Random distribution dialog for selection
*/

#ifndef RANDOMDISTRIBUTIONDIALOG_H
#define RANDOMDISTRIBUTIONDIALOG_H

#include <QDialog>

class Ui_RandomDistributionDialog;

class RandomDistributionDialog : public QDialog {
  Q_OBJECT
 public:
  explicit RandomDistributionDialog(QWidget *parent = nullptr);
  ~RandomDistributionDialog();

  enum Distribution {
    Gaussian,
    Exponential,
    Laplace,
    ExponentialPower,
    Cauchy,
    Rayleigh,
    RayleighTail,
    Landau,
    LevyAlphaStable,
    LevySkewAlphaStable,
    Gamma,
    Flat,
    Lognormal,
    ChiSquared,
    F,
    t,
    Beta,
    Logistic,
    Pareto,
    Weibull,
    Gumbel1,
    Gumbel2,
    Poisson,
    Bernoulli,
    Binomial,
    NegativeBinomial,
    Pascal,
    Geometric,
    Hypergeometric,
    Logarithmic
  };

 signals:
  void randomDistribution(const RandomDistributionDialog::Distribution &dist,
                          const QVector<double> &params);

 private slots:
  void distributionChanged(int index);
  void ok();
  void cancel();

 private:
  Ui_RandomDistributionDialog *ui_;
  static Distribution distribution;
  static QVector<double> parameters;
  QString distFormulaPath;
};

#endif  // RANDOMDISTRIBUTIONDIALOG_H
