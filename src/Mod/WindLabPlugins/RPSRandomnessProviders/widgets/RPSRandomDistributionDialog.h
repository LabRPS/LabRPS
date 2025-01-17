#ifndef RPSRANDOMDISTRIBUTIONDIALOG_H
#define RPSRANDOMDISTRIBUTIONDIALOG_H

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
    Weibull,
    F,
    t,
    Beta,
    Logistic,
    Pareto,
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

  Q_SIGNALS:
  void randomDistribution(const RandomDistributionDialog::Distribution &dist,
                          const QVector<double> &params);

 private Q_SLOTS:
  void distributionChanged(int index);
  void ok();
  void cancel();

 private:
  Ui_RandomDistributionDialog *ui_;
  static Distribution distribution;
  static QVector<double> parameters;
  QString distFormulaPath;
public:
  QVector<double> getParametersVector();

};

#endif  // RPSRANDOMDISTRIBUTIONDIALOG_H
