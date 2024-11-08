#include "PreCompiled.h"
#include "DesignResponseSpectrum.h"
#include <math.h>
#include <Mod/SeismicLabTools/App/ResponseSpectrum/DesignResponseSpectrumPy.h>

using namespace SeismicLabTools;

DesignResponseSpectrum::DesignResponseSpectrum()
{

}

DesignResponseSpectrum::~DesignResponseSpectrum()
{

}

double get_h_T_B(int soil_type, int spectrum_type) {
    if (spectrum_type == 1)
    {
        if (soil_type == 1) return 0.15;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 0.15;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 0.20;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 0.20;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 0.15;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    else if (spectrum_type == 2)
    {
        if (soil_type == 1) return 0.05;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 0.05;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 0.10;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 0.10;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 0.05;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

double get_h_T_C(int soil_type, int spectrum_type) {
    if (spectrum_type == 1)
    {
        if (soil_type == 1) return 0.40;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 0.50;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 0.60;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 0.80;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 0.15;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    else if (spectrum_type == 2)
    {
        if (soil_type == 1) return 0.25;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 0.25;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 0.25;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 0.30;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 0.25;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

double get_h_T_D(int soil_type, int spectrum_type) {
    if (spectrum_type == 1)
    {
        if (soil_type == 1) return 2.00;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 2.00;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 2.00;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 2.00;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 2.00;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    else if (spectrum_type == 2)
    {
        if (soil_type == 1) return 1.20;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 1.20;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 1.20;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 1.20;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 1.20;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

// Function to get the soil amplification factor based on soil type
double get_soil_factor(int soil_type, int spectrum_type) {
    if (spectrum_type == 1)
    {
        if (soil_type == 1) return 1.00;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 1.20;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 1.15;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 1.35;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 1.40;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    else if (spectrum_type == 2)
    {
        if (soil_type == 1) return 1.00;  // 'A': Rock or very dense soil (no amplification)
        if (soil_type == 2) return 1.35;  // 'B': Firm soil (slightly higher amplification)
        if (soil_type == 3) return 1.50;  // 'C': Soft soil (higher amplification)
        if (soil_type == 4) return 1.80;  // 'D': Very soft soil (higher amplification)
        if (soil_type == 5) return 1.60;  // 'E': Extremely soft soil (maximum amplification)
        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
}

// Function to get the importance factor based on importance class
double get_importance_factor(int importance_class) {
    if (importance_class == 1) return 1.0;  // Normal buildings
    if (importance_class == 2) return 1.2;  // Important buildings
    if (importance_class == 3) return 1.5;  // Critical infrastructure
    throw std::invalid_argument("Invalid importance class. Valid options are: 1, 2, 3.");
}

// Function to get the damping factor (for typical buildings, damping factor < 1.0)
double get_damping_factor(double damping_percentage) {
    double damping_factor = 0.0;
    damping_factor = std::sqrt(10/(5 + damping_percentage));  // Damping factor reduces with higher damping
    if (damping_factor >= 0.55)
    return damping_factor;
    return 0.0;
}



double get_v_T_B(int soil_type, int spectrum_type) {
    if (spectrum_type == 1 || spectrum_type == 2)
    {
        if (soil_type == 1 || soil_type == 2 || soil_type == 3 || soil_type == 4 || soil_type == 5)
            return 0.05;

        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

double get_v_T_C(int soil_type, int spectrum_type) {
    if (spectrum_type == 1 || spectrum_type == 2)
    {
        if (soil_type == 1 || soil_type == 2 || soil_type == 3 || soil_type == 4 || soil_type == 5)
            return 0.15;

        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

double get_v_T_D(int soil_type, int spectrum_type) {
    if (spectrum_type == 1 || spectrum_type == 2)
    {
        if (soil_type == 1 || soil_type == 2 || soil_type == 3 || soil_type == 4 || soil_type == 5)
            return 1.00;

        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

double get_v_PGA(int soil_type, int spectrum_type, double pga) {
    if (spectrum_type == 1)
    {
        if (soil_type == 1 || soil_type == 2 || soil_type == 3 || soil_type == 4 || soil_type == 5)
            return pga * 0.90;

        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    else if (spectrum_type == 2)
    {
        if (soil_type == 1 || soil_type == 2 || soil_type == 3 || soil_type == 4 || soil_type == 5)
            return pga * 0.45;

        throw std::invalid_argument("Invalid soil type. Valid options are: 1, 2, 3, 4, 5.");
    }
    throw std::invalid_argument("Invalid spectrum type. Valid options are: 1 and 2.");
}

double DesignResponseSpectrum::compute_Euro_EN1998_1_2004_Hori_Elastic_Response_Spectrum(const double &time, 
    const int &nationalAnnex, 
    const double &damping, const double & pga, 
    const int &spectrumType, const int &groundType, 
    const int &importanceClass)
{
    double spectral_accel = 0.0;
    
    // Get the soil amplification factor based on the soil type
    double soil_factor = get_soil_factor(groundType, spectrumType);

    // Get the importance factor based on the importance class
    double importance_factor = get_importance_factor(importanceClass);

    //Get the damping factor based on the damping percentage
    double damping_factor = get_damping_factor(damping);

    double tB = get_h_T_B(groundType, spectrumType);
    double tC = get_h_T_C(groundType, spectrumType);
    double tD = get_h_T_D(groundType, spectrumType);

    if (time < 0){
        //time < 0
        //do nothing or report error
    }
    else if (time <= tB) {
        // For 0 < time <= TB
        spectral_accel = 1 + (time/tB) * (damping_factor * 2.5 - 1);
    } else if (time <= tC) {
        // For TB < time <= TC
        spectral_accel = damping_factor * 2.5;
    } else if (time <= tD) {
        // For TC < time <= TD
        spectral_accel = damping_factor * 2.5 * tC / time;
    } else if (time <= 4.00) {
        // For time > 4 seconds
        spectral_accel = damping_factor * 2.5 * tC * tD/time / time;
    }

    // Apply the soil amplification factor
    spectral_accel *= soil_factor;

    // Apply importance factor
    spectral_accel *= importance_factor;

    // Scale by PGA (Peak Ground Acceleration on type A ground)
    spectral_accel *= pga;

    return spectral_accel;
}

double DesignResponseSpectrum::compute_Euro_EN1998_1_2004_Hori_Design_Response_Spectrum(
    const double& time, const int& nationalAnnex, const double& damping, const double& pga,
    const int& spectrumType, const int& groundType, const int& importanceClass, const double& behaviorFactor,
    const double& lowerBoundFactor)
{
      double spectral_accel = 0.0;
    
    // Get the soil amplification factor based on the soil type
    double soil_factor = get_soil_factor(groundType, spectrumType);

    // Get the importance factor based on the importance class
    double importance_factor = get_importance_factor(importanceClass);

    //Get the damping factor based on the damping percentage
    double damping_factor = get_damping_factor(damping);

    double tB = get_h_T_B(groundType, spectrumType);
    double tC = get_h_T_C(groundType, spectrumType);
    double tD = get_h_T_D(groundType, spectrumType);

    if (time < 0){
        //time < 0
        //do nothing or report error
    }
    else if (time <= tB) {
        // For 0 < time <= TB
        spectral_accel = 2 / 3 + (time / tB) * (2.5 / behaviorFactor - 2/3);
    } else if (time <= tC) {
        // For TB < time <= TC
        spectral_accel = 2.5 / behaviorFactor;
    } else if (time <= tD) {
        // For TC < time <= TD
        spectral_accel = (2.5 / behaviorFactor) * tC / time;
        if (spectral_accel < lowerBoundFactor * pga)
            spectral_accel = lowerBoundFactor * pga;
    } else if (time >= tD) {
        // For time > 4 seconds
        spectral_accel = (2.5 / behaviorFactor) * tC * tD / time / time;
        if (spectral_accel < lowerBoundFactor * pga)
            spectral_accel = lowerBoundFactor * pga;
    }

    // Apply the soil amplification factor
    spectral_accel *= soil_factor;

    // Apply importance factor
    spectral_accel *= importance_factor;

    // Scale by PGA (Peak Ground Acceleration on type A ground)
    spectral_accel *= pga;

    return spectral_accel;
}


double DesignResponseSpectrum::compute_Euro_EN1998_1_2004_Vert_Elastic_Response_Spectrum(const double &time, 
    const int &nationalAnnex, 
    const double &damping, const double & pga, 
    const int &spectrumType, const int &groundType, 
    const int &importanceClass)
{
    double spectral_accel = 0.0;
    
    // Get the importance factor based on the importance class
    double importance_factor = get_importance_factor(importanceClass);

    //Get the damping factor based on the damping percentage
    double damping_factor = get_damping_factor(damping);

     //Get the peak ground acceleration in the vertical direction
    double pga_v = get_v_PGA(groundType, spectrumType, pga);

    double tB = get_v_T_B(groundType, spectrumType);
    double tC = get_v_T_C(groundType, spectrumType);
    double tD = get_v_T_D(groundType, spectrumType);

    if (time < 0){
        //time < 0
        //do nothing or report error
    }
    else if (time <= tB) {
        // For 0 < time <= TB
        spectral_accel = 1 + (time/tB) * (damping_factor * 3.0 - 1);
    } else if (time <= tC) {
        // For TB < time <= TC
        spectral_accel = damping_factor * 3.0;
    } else if (time <= tD) {
        // For TC < time <= TD
        spectral_accel = damping_factor * 3.0 * tC / time;
    } else if (time <= 4.00) {
        // For time > 4 seconds
        spectral_accel = damping_factor * 3.0 * tC * tD / time / time;
    }

    // Apply importance factor
    spectral_accel *= importance_factor;

    // Scale by PGA (Peak Ground Acceleration on type A ground)
    spectral_accel *= pga_v;

    return spectral_accel;
}

double DesignResponseSpectrum::compute_Euro_EN1998_1_2004_Vert_Design_Response_Spectrum(
    const double& time, const int& nationalAnnex, const double& damping, const double& pga,
    const int& spectrumType, const int& groundType, const int& importanceClass, const double& behaviorFactor,
    const double& lowerBoundFactor)
{
      double spectral_accel = 0.0;
    
    // Get the importance factor based on the importance class
    double importance_factor = get_importance_factor(importanceClass);

    //Get the damping factor based on the damping percentage
    double damping_factor = get_damping_factor(damping);

    //Get the peak ground acceleration in the vertical direction
    double pga_v = get_v_PGA(groundType, spectrumType, pga);

    double tB = get_v_T_B(groundType, spectrumType);
    double tC = get_v_T_C(groundType, spectrumType);
    double tD = get_v_T_D(groundType, spectrumType);

    if (time < 0){
        //time < 0
        //do nothing or report error
    }
    else if (time <= tB) {
        // For 0 < time <= TB
        spectral_accel = 2 / 3 + (time / tB) * (2.5 / behaviorFactor - 2/3);
    } else if (time <= tC) {
        // For TB < time <= TC
        spectral_accel = 2.5 / behaviorFactor;
    } else if (time <= tD) {
        // For TC < time <= TD
        spectral_accel = (2.5 / behaviorFactor) * tC / time;
        if (spectral_accel < lowerBoundFactor * pga_v)
            spectral_accel = lowerBoundFactor * pga_v;
    } else if (time >= tD) {
        // For time > 4 seconds
        spectral_accel = (2.5 / behaviorFactor) * tC * tD / time / time;
                if (spectral_accel < lowerBoundFactor * pga_v)
            spectral_accel = lowerBoundFactor * pga_v;
    }

    // Apply importance factor
    spectral_accel *= importance_factor;

    // Scale by PGA (Peak Ground Acceleration on type A ground)
    spectral_accel *= pga_v;

    return spectral_accel;
}
PyObject* DesignResponseSpectrum::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new DesignResponseSpectrumPy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}