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
