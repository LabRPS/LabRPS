#include "PreCompiled.h"
#include "EMD.h"
#include <math.h>
#include <Mod/GeneralTools/App/EMDPy.h>

using namespace GeneralTools;

EMD::EMD()
{

}

EMD::~EMD()
{

}

// Function to find the local maxima
std::vector<int> EMD::findLocalMaxima(const std::vector<double>& data) {
    std::vector<int> maxima;
    for (size_t i = 1; i < data.size() - 1; ++i) {
        if (data[i] > data[i - 1] && data[i] > data[i + 1]) {
            maxima.push_back(i);
        }
    }
    return maxima;
}

// Function to find the local minima
std::vector<int> EMD::findLocalMinima(const std::vector<double>& data) {
    std::vector<int> minima;
    for (size_t i = 1; i < data.size() - 1; ++i) {
        if (data[i] < data[i - 1] && data[i] < data[i + 1]) {
            minima.push_back(i);
        }
    }
    return minima;
}

// Function to create an envelope from the local extrema (maxima or minima)
std::vector<double> EMD::createEnvelope(const std::vector<int>& extrema, const std::vector<double>& data, bool isMaxima) {
    std::vector<double> envelope(data.size(), 0.0);
    for (size_t i = 0; i < extrema.size(); ++i) {
        size_t index = extrema[i];
        envelope[index] = data[index];
    }
    
    // Interpolation (linear interpolation between extrema)
    for (size_t i = 1; i < data.size(); ++i) {
        if (envelope[i] == 0.0) {
            size_t left = i - 1;
            size_t right = i + 1;
            while (left >= 0 && envelope[left] == 0.0 && left > 0) left--;
            while (right < data.size() && envelope[right] == 0.0) right++;
            if (left >= 0 && right < data.size()) {
                double slope = (data[right] - data[left]) / (right - left);
                envelope[i] = data[left] + slope * (i - left);
            }
        }
    }
    return envelope;
}

// Function to perform the sifting process
std::vector<double> EMD::siftSignal(const std::vector<double>& data, int maxIterations, double tol) {
    std::vector<double> signal = data;
    std::vector<double> imf;
    
    int iterations = 0;
    while (iterations < maxIterations) {
        // Find local maxima and minima
        std::vector<int> maxima = findLocalMaxima(signal);
        std::vector<int> minima = findLocalMinima(signal);
        
        // Create upper and lower envelopes
        std::vector<double> upperEnvelope = createEnvelope(maxima, signal, true);
        std::vector<double> lowerEnvelope = createEnvelope(minima, signal, false);
        
        // Calculate the mean of the envelopes
        std::vector<double> meanEnvelope(signal.size());
        for (size_t i = 0; i < signal.size(); ++i) {
            meanEnvelope[i] = (upperEnvelope[i] + lowerEnvelope[i]) / 2.0;
        }
        
        // Subtract the mean envelope from the signal
        std::vector<double> newSignal(signal.size());
        for (size_t i = 0; i < signal.size(); ++i) {
            newSignal[i] = signal[i] - meanEnvelope[i];
        }
        
        // Check if the signal is an IMF (mean envelope is close to zero)
        double signalEnergy = std::accumulate(newSignal.begin(), newSignal.end(), 0.0, 
                                             [](double sum, double val) { return sum + val * val; });
        
        if (check_extrema_zero_crossings(signal)/* && check_mean_of_envelopes(signal, tol)*/)
        {
            imf = newSignal;
        }
        
        if (signalEnergy < tol) {
            imf = newSignal;
            break;
        }
        
        signal = newSignal;
        iterations++;
    }
    
    return imf;
}

// Function to find the number of local extrema in the signal
int EMD::count_extrema(const std::vector<double>& signal)
{
    int extrema_count = 0;

    // Iterate through the signal to find local maxima and minima
    for (size_t i = 1; i < signal.size() - 1; ++i) {
        // Check for local maximum
        if (signal[i] > signal[i - 1] && signal[i] > signal[i + 1]) {
            extrema_count++;
        }
        // Check for local minimum
        else if (signal[i] < signal[i - 1] && signal[i] < signal[i + 1]) {
            extrema_count++;
        }
    }

    return extrema_count;
}

// Function to count the number of zero-crossings in the signal
int EMD::count_zero_crossings(const std::vector<double>& signal)
{
    int zero_crossing_count = 0;

    for (size_t i = 1; i < signal.size(); ++i) {
        // Check if the signal crosses zero between signal[i-1] and signal[i]
        if ((signal[i - 1] > 0 && signal[i] < 0) || (signal[i - 1] < 0 && signal[i] > 0)) {
            zero_crossing_count++;
        }
    }

    return zero_crossing_count;
}

// Function to calculate the mean of a vector
double EMD::calculate_mean(const std::vector<double>& values)
{
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

// Function to check if the number of extrema and zero-crossings are either equal or differ by at most one
bool EMD::check_extrema_zero_crossings(const std::vector<double>& signal)
{
    int extrema_count = count_extrema(signal);
    int zero_crossing_count = count_zero_crossings(signal);

    // Check if the number of extrema and zero-crossings differ by at most one
    return std::abs(extrema_count - zero_crossing_count) <= 1;
}

// Function to check if the mean of the upper and lower envelopes is approximately zero
bool EMD::check_mean_of_envelopes(const std::vector<double>& signal, double tol)
{
    std::vector<int> maxima = findLocalMaxima(signal);
    std::vector<int> minima = findLocalMinima(signal);

    // Create upper and lower envelopes
    std::vector<double> upperEnvelope = createEnvelope(maxima, signal, true);
    std::vector<double> lowerEnvelope = createEnvelope(minima, signal, false);

    // Calculate the mean of the upper and lower envelopes
    double upper_mean = calculate_mean(upperEnvelope);
    double lower_mean = calculate_mean(lowerEnvelope);

    // Check if both means are approximately zero
    return std::abs(upper_mean) < tol && std::abs(lower_mean) < tol;
}

// Function to perform Empirical Mode Decomposition (EMD)
std::vector<std::vector<double>> EMD::emd(const std::vector<double>& signal, int maxIMFs) {
    std::vector<std::vector<double>> imfs;
    std::vector<double> residual = signal;
    
    for (int i = 0; i < maxIMFs; ++i) {
        std::vector<double> imf = siftSignal(residual);
        imfs.push_back(imf);
        
        // Subtract IMF from residual to get the new residual
        residual = residual;
        for (size_t j = 0; j < imf.size(); ++j) {
            residual[j] -= imf[j];
        }
        
        // If the residual is almost constant, stop the decomposition
        if (std::accumulate(residual.begin(), residual.end(), 0.0, [](double sum, double val) { return sum + std::abs(val); }) < 1e-6) {
            break;
        }
    }
    
    return imfs;
}


PyObject* EMD::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new EMDPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}
