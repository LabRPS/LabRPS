#ifndef FFT_H
#define FFT_H

#include "Filter.h"

class FFT : public Filter {
  Q_OBJECT

 public:
  FFT(ApplicationWindow *parent, Table *table, const QString &realColName,
      const QString &imagColName = QString());
  FFT(ApplicationWindow *parent, AxisRect2D *axisrect,
      PlotData::AssociatedData *associateddata);

  void setInverseFFT(bool inverse = true) { d_inverse = inverse; }
  void setSampling(double sampling) { d_sampling = sampling; }
  void normalizeAmplitudes(bool norm = true) { d_normalize = norm; }
  void shiftFrequencies(bool shift = true) { d_shift_order = shift; }

 private:
  void init();
  void output();
  void output(QList<Column *> columns);

  QList<Column *> fftCurve();
  QList<Column *> fftTable();

  void setDataFromTable(Table *t, const QString &realColName,
                        const QString &imagColName = QString());

  double d_sampling;
  //! Flag telling if an inverse FFT must be performed.
  bool d_inverse;
  //! Flag telling if the amplitudes in the output spectrum must be normalized.
  bool d_normalize;
  //! Flag telling if the output frequencies must be shifted in order to have a
  //! zero-centered spectrum.
  bool d_shift_order;

  int d_real_col, d_imag_col;
};

#endif  // FFT_H
