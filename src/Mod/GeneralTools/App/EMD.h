#ifndef EMD_H
#define EMD_H

#include <Mod/GeneralTools/GeneralToolsGlobal.h>
#include <Base/SmartPtrPy.h>

#include <math.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <numeric>

namespace GeneralTools {

class GeneralToolsExport EMD
{
public:
    EMD();
    ~EMD();

    std::vector<int> findLocalMaxima(const std::vector<double>& data);
    std::vector<int> findLocalMinima(const std::vector<double>& data);
    std::vector<double> createEnvelope(const std::vector<int>& extrema, const std::vector<double>& data, bool isMaxima);
    std::vector<double> siftSignal(const std::vector<double>& data, int maxIterations = 100, double tol = 1e-6);

    // Function to find the number of local extrema in the signal
    int count_extrema(const std::vector<double>& signal);

    // Function to count the number of zero-crossings in the signal
    int count_zero_crossings(const std::vector<double>& signal);

    // Function to check if the number of extrema and zero-crossings are either equal or differ by at most one
    bool check_extrema_zero_crossings(const std::vector<double>& signal);

    // Function to check if the mean of the upper and lower envelopes is approximately zero
    bool check_mean_of_envelopes(const std::vector<double>& signal, double tol);

    // Function to calculate the mean of a vector
    double calculate_mean(const std::vector<double>& values);

    std::vector<std::vector<double>> emd(const std::vector<double>& signal, int maxIMFs = 10);

    virtual PyObject* getPyObject(void);

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

}

#endif //EMD_H
