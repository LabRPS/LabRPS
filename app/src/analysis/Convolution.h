#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Filter.h"

class Convolution : public Filter {
  Q_OBJECT

 public:
  Convolution(ApplicationWindow *parent, Table *t, const QString &signalColName,
              const QString &responseColName);

  void setDataFromTable(Table *t, const QString &signalColName,
                        const QString &responseColName);
  //! Returns the size of the signal data set
  int signalDataSize() { return d_n_signal; }
  //! Returns the size of the response data set
  int responseDataSize() { return d_n_response; }

 protected:
  //! Handles the graphical output
  void addResultCurve();
  //! Performes the convolution of the two data sets and stores the result in
  //! the signal data set
  void convlv(double *sig, int n, double *dres, int m, int sign);

 private:
  virtual void output();
  //! Size of the signal data set
  int d_n_signal;
  //! Size of the response data set
  int d_n_response;
};

class Deconvolution : public Convolution {
  Q_OBJECT

 public:
  Deconvolution(ApplicationWindow *parent, Table *t, const QString &realColName,
                const QString &imagColName = QString());

 private:
  void output();
};

#endif  // CONVOLUTION_H
