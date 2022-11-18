#ifndef MULTIPEAKFIT_H
#define MULTIPEAKFIT_H

#include "Fit.h"

class MultiPeakFit : public Fit {
  Q_OBJECT

 public:
  enum PeakProfile { Gauss, Lorentz };
  MultiPeakFit(ApplicationWindow *parent, AxisRect2D *axisrect,
               PeakProfile profile = Gauss, int peaks = 1);

  int peaks() { return d_peaks; }
  void setNumPeaks(int n);

  void enablePeakCurves(bool on) { generate_peak_curves = on; }
  void setPeakCurvesColor(int colorIndex) { d_peaks_color = colorIndex; }

  static QString generateFormula(int order, PeakProfile profile);
  static QStringList generateParameterList(int order);
  static QStringList generateExplanationList(int order);

 private:
  QString logFitInfo(const std::vector<double> &par, int iterations, int status,
                     const QString &plotName) override;
  void generateFitCurve(const std::vector<double> &par) override;
  static QString peakFormula(int peakIndex, PeakProfile profile);
  //! Inserts a peak function curve into the plot
  void insertPeakFunctionCurve(double *x, double *y, int peak);
  void storeCustomFitResults(const std::vector<double> &par) override;

  //! Used by the GaussFit and LorentzFit derived classes to calculate initial
  //! values for the parameters
 protected:
  void guessInitialValues() override;

 private:
  //! Number of peaks
  int d_peaks;

  //! Tells weather the peak curves should be displayed together with the best
  //! line fit.
  bool generate_peak_curves;

  //! Color index for the peak curves
  int d_peaks_color;

  //! The peak profile
  PeakProfile d_profile;
};

class LorentzFit : public MultiPeakFit {
  Q_OBJECT

 public:
  LorentzFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  LorentzFit(ApplicationWindow *parent, AxisRect2D *axisrect,
             PlotData::AssociatedData *associateddata);
  LorentzFit(ApplicationWindow *parent, AxisRect2D *axisrect,
             PlotData::AssociatedData *associateddata, double start,
             double end);

 private:
  void init();
};

class GaussFit : public MultiPeakFit {
  Q_OBJECT

 public:
  GaussFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  GaussFit(ApplicationWindow *parent, AxisRect2D *axisrect,
           PlotData::AssociatedData *associateddata);
  GaussFit(ApplicationWindow *parent, AxisRect2D *axisrect,
           PlotData::AssociatedData *associateddata, double start, double end);

 private:
  void init();
};

class GaussAmpFit : public Fit {
  Q_OBJECT

 public:
  GaussAmpFit(ApplicationWindow *parent, AxisRect2D *axisrect);
  GaussAmpFit(ApplicationWindow *parent, AxisRect2D *axisrect,
              PlotData::AssociatedData *associateddata);
  GaussAmpFit(ApplicationWindow *parent, AxisRect2D *axisrect,
              PlotData::AssociatedData *associateddata, double start,
              double end);

 private:
  void init();
  void calculateFitCurveData(const std::vector<double> &par, double *X,
                             double *Y) override;
};

#endif  // MULTIPEAKFIT_H
