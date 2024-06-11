#include "RandomnessProviders.h"
#include "widgets/cgaussianrandomnessproviderdlg.h"
#include "widgets/RPSRandomDistributionDialog.h"

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>
#include <Base/Quantity.h>

using namespace RandomnessProviders;

static double para0 = 0;
static double para1 = 1;
static double para2 = 1;

//Weibull
PROPERTY_SOURCE(RandomnessProviders::CWeibullRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CWeibullRandomnessProvider::CWeibullRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (1.0), "Parameters", App::Prop_None, "The Weibull distribution exponential factor");

}
bool CWeibullRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CWeibullRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_weibull(r, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/);
        }
    }
    return returnResult;
}

bool CWeibullRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_weibull(r, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/);

    return true;

}
//Gaussian
PROPERTY_SOURCE(RandomnessProviders::CGaussianRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CGaussianRandomnessProvider::CGaussianRandomnessProvider()
{
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
   ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");


}
bool CGaussianRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CGaussianRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            returnResult = ComputeRandomValue(Data, dRandomValueArray(j, i));
            gsl_ran_gaussian(r, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond)) + Mean.getValue();
        }
    }
    return returnResult;

}

bool CGaussianRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_gaussian(r, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond)) + Mean.getValue();
        return true;

}

//Exponential
PROPERTY_SOURCE(RandomnessProviders::CExponentialRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CExponentialRandomnessProvider::CExponentialRandomnessProvider()
{
   ADD_PROPERTY_TYPE(Mean, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");

}

bool CExponentialRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

bool CExponentialRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            returnResult = ComputeRandomValue(Data, dRandomValueArray(j, i));
            gsl_ran_exponential(r, static_cast<double>(1 / Mean.getValue() /*lambda*/));
        }
    }
    return returnResult;

}

bool CExponentialRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_exponential(r, static_cast<double>(1 / Mean.getValue() /*lambda*/));
        return true;

}

//Laplace
PROPERTY_SOURCE(RandomnessProviders::CLaplaceRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CLaplaceRandomnessProvider::CLaplaceRandomnessProvider()
{
   ADD_PROPERTY_TYPE(Width, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
   ADD_PROPERTY_TYPE(Mean, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
}
bool CLaplaceRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CLaplaceRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            returnResult = ComputeRandomValue(Data, dRandomValueArray(j, i));
            gsl_ran_laplace(r, Width.getValue() /*a*/) + Mean.getValue() /*mu*/;
        }
    }
    return returnResult;

}

bool CLaplaceRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_laplace(r, Width.getValue() /*a*/) + Mean.getValue() /*mu*/;
    return true;

}

//Exponential Power
PROPERTY_SOURCE(RandomnessProviders::CExponentialPowerRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CExponentialPowerRandomnessProvider::CExponentialPowerRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (2.5), "Parameters", App::Prop_None, "The exponent factor");
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
}
bool CExponentialPowerRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
        para2 = dlg->getParametersVector().at(2);

    }

    return true;
}

bool CExponentialPowerRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_exppow(r, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/) + Mean.getValue() /*mu*/;

        }
    }
    return returnResult;

}

bool CExponentialPowerRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_exppow(r, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/) + Mean.getValue() /*mu*/;
    return true;

}

//Cauchy
PROPERTY_SOURCE(RandomnessProviders::CCauchyRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CCauchyRandomnessProvider::CCauchyRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");

}

bool CCauchyRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

bool CCauchyRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_cauchy(r, ScaleParameter.getValue() /*a*/);

        }
    }
    return returnResult;

}

bool CCauchyRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_cauchy(r, ScaleParameter.getValue() /*a*/);
        return true;

}

//Rayleigh
PROPERTY_SOURCE(RandomnessProviders::CRayleighRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CRayleighRandomnessProvider::CRayleighRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");

}

bool CRayleighRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

bool CRayleighRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_rayleigh(r, ScaleParameter.getValue() /*sigma*/);

        }
    }
    return returnResult;

}

bool CRayleighRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_rayleigh(r, ScaleParameter.getValue() /*sigma*/);
            return true;

}

//Rayleigh Tail
PROPERTY_SOURCE(RandomnessProviders::CRayleighTailRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CRayleighTailRandomnessProvider::CRayleighTailRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(LowerLimit, (1.0), "Parameters", App::Prop_None, "The scale parameter");
}

bool CRayleighTailRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CRayleighTailRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_rayleigh_tail(r, LowerLimit.getValue() /*a*/, ScaleParameter.getValue() /*sigma*/);

        }
    }
    return returnResult;
}

bool CRayleighTailRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_rayleigh_tail(r, LowerLimit.getValue() /*a*/, ScaleParameter.getValue() /*sigma*/);
    return true;

}

//Landau
PROPERTY_SOURCE(RandomnessProviders::CLandauRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CLandauRandomnessProvider::CLandauRandomnessProvider() {

}

bool CLandauRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {

    }

    return true;
}

bool CLandauRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_landau(r);

        }
    }
    return returnResult;

}

bool CLandauRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_landau(r);
    return true;

}

//LevyAlphaStable
PROPERTY_SOURCE(RandomnessProviders::CLevyAlphaStableRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CLevyAlphaStableRandomnessProvider::CLevyAlphaStableRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (1.0), "Parameters", App::Prop_None, "The exponent factor");
}
bool CLevyAlphaStableRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CLevyAlphaStableRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_levy(r, ScaleParameter.getValue() /*c*/, ExponentFactor.getValue() /*alpha*/);

        }
    }
    return returnResult;

}

bool CLevyAlphaStableRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_levy(r, ScaleParameter.getValue() /*c*/, ExponentFactor.getValue() /*alpha*/);
    return true;

}

//LevySkewAlphaStable
PROPERTY_SOURCE(RandomnessProviders::CLevySkewAlphaStableRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CLevySkewAlphaStableRandomnessProvider::CLevySkewAlphaStableRandomnessProvider()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (1.0), "Parameters", App::Prop_None, "The exponent factor");
   ADD_PROPERTY_TYPE(SkewnessParameter, (1.0), "Parameters", App::Prop_None, "The skewness parameter");
}

bool CLevySkewAlphaStableRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
        para2 = dlg->getParametersVector().at(2);
    }

    return true;
}

bool CLevySkewAlphaStableRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_levy_skew(r, ScaleParameter.getValue() /*c*/, ExponentFactor.getValue() /*alpha*/, SkewnessParameter.getValue() /*beta*/);

        }
    }
    return returnResult;

}

bool CLevySkewAlphaStableRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_levy_skew(r, ScaleParameter.getValue() /*c*/, ExponentFactor.getValue() /*alpha*/, SkewnessParameter.getValue() /*beta*/);
    return true;

}

//Flat
PROPERTY_SOURCE(RandomnessProviders::CFlatRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CFlatRandomnessProvider::CFlatRandomnessProvider()
{
    ADD_PROPERTY_TYPE(LowerBound, (0.5), "Parameters", App::Prop_None, "The lower bound limit value");
    ADD_PROPERTY_TYPE(UpperBound, (2.5), "Parameters", App::Prop_None, "The upper bound limit value");
}
bool CFlatRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CFlatRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_flat(r, LowerBound.getValue() /*a*/, UpperBound.getValue() /*b*/);

        }
    }
    return returnResult;
}

bool CFlatRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_flat(r, LowerBound.getValue() /*a*/, UpperBound.getValue() /*b*/);
            return true;

}

//Gamma
PROPERTY_SOURCE(RandomnessProviders::CGammaRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CGammaRandomnessProvider::CGammaRandomnessProvider()
{
    ADD_PROPERTY_TYPE(ParameterA, (0.5), "Parameters", App::Prop_None, "The A parameter");
    ADD_PROPERTY_TYPE(ParameterB, (2.5), "Parameters", App::Prop_None, "The B parameter");
}
bool CGammaRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CGammaRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_gamma(r, ParameterA.getValue() /*a*/, ParameterB.getValue() /*b*/);

        }
    }
    return returnResult;

}

bool CGammaRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_gamma(r, ParameterA.getValue() /*a*/, ParameterB.getValue() /*b*/);
            return true;

}

//Lognormal
PROPERTY_SOURCE(RandomnessProviders::CLognormalRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CLognormalRandomnessProvider::CLognormalRandomnessProvider()
{
    ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
    ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The stantard devialtion");
}
bool CLognormalRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

bool CLognormalRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

     bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_lognormal(r, Mean.getValue() /*zeta*/, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*sigma*/);

        }
    }
    return returnResult;

}

bool CLognormalRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_lognormal(r, Mean.getValue() /*zeta*/, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*sigma*/);
     return true;

}

//ChiSquared
PROPERTY_SOURCE(RandomnessProviders::CChiSquaredRandomnessProvider, WindLabAPI::WindLabFeatureRandomness)

CChiSquaredRandomnessProvider::CChiSquaredRandomnessProvider()
{
    ADD_PROPERTY_TYPE(DegreeOfFreedom, (1.0), "Parameters", App::Prop_None, "The degree of freedom");
}

bool CChiSquaredRandomnessProvider::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

bool CChiSquaredRandomnessProvider::GenerateRandomMatrixFP(const WindLabAPI::WindLabSimuData& Data, mat &dRandomValueArray)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);

    bool returnResult = true;

    for (int i = 0; i < Data.numberOfSpatialPosition.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; i++)
    {
        for (int j = 0; j <Data.numberOfFrequency.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
        {
            dRandomValueArray(j, i) = gsl_ran_chisq(r, DegreeOfFreedom.getValue() /*nu*/);

        }
    }
    return returnResult;

}

bool CChiSquaredRandomnessProvider::ComputeRandomValue(const WindLabAPI::WindLabSimuData& Data, double &dValue)
{
    // create a generator chosen by the environment variable GSL_RNG_TYPE
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *r = gsl_rng_alloc(T);
    dValue = gsl_ran_chisq(r, DegreeOfFreedom.getValue() /*nu*/);
    return true;

}

//ALL PROBABILITY DENSITY FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


PROPERTY_SOURCE(RandomnessProviders::CWeibullPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CWeibullPDF::CWeibullPDF()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (1.0), "Parameters", App::Prop_None, "The Weibull distribution exponential factor");

}

bool CWeibullPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_weibull_pdf(x, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/);
    return true;

}
bool CWeibullPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CWeibullPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

//
PROPERTY_SOURCE(RandomnessProviders::CGaussianPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CGaussianPDF::CGaussianPDF()
{
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
   ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");


}
bool CGaussianPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_gaussian_pdf(x, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*a*/) + Mean.getValue() /*mu*/;
   return true;

}
bool CGaussianPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CGaussianPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

//
PROPERTY_SOURCE(RandomnessProviders::CExponentialPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CExponentialPDF::CExponentialPDF()
{
   ADD_PROPERTY_TYPE(Mean, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");

}
bool CExponentialPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_exponential_pdf(x, Mean.getValue());
   return true;

}
bool CExponentialPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}
bool CExponentialPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;}

//
PROPERTY_SOURCE(RandomnessProviders::CLaplacePDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CLaplacePDF::CLaplacePDF()
{
   ADD_PROPERTY_TYPE(Width, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
   ADD_PROPERTY_TYPE(Mean, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
}
bool CLaplacePDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_laplace_pdf(x, Width.getValue() /*a*/) + Mean.getValue() /*mu*/;
   return true;

}
bool CLaplacePDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CLaplacePDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CExponentialPowerPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CExponentialPowerPDF::CExponentialPowerPDF()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (2.5), "Parameters", App::Prop_None, "The exponent factor");
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
}

bool CExponentialPowerPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_exppow_pdf(x, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/) + Mean.getValue() /*mu*/;
   return true;
}
bool CExponentialPowerPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CExponentialPowerPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
        para2 = dlg->getParametersVector().at(2);
    }

    return true;
}

//

PROPERTY_SOURCE(RandomnessProviders::CCauchyPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CCauchyPDF::CCauchyPDF()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");

}

bool CCauchyPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_cauchy_pdf(x, ScaleParameter.getValue() /*a*/);
    return true;
}

bool CCauchyPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{

    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}
bool CCauchyPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CRayleighPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CRayleighPDF::CRayleighPDF()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");

}
bool CRayleighPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_rayleigh_pdf(x, ScaleParameter.getValue() /*sigma*/);
   return true;

}

bool CRayleighPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CRayleighPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CRayleighTailPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CRayleighTailPDF::CRayleighTailPDF()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(LowerLimit, (1.0), "Parameters", App::Prop_None, "The scale parameter");
}
bool CRayleighTailPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   dValue = gsl_ran_rayleigh_tail_pdf(x, LowerLimit.getValue() /*a*/, ScaleParameter.getValue() /*sigma*/);
   return true;
}

bool CRayleighTailPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CRayleighTailPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CLandauPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CLandauPDF::CLandauPDF()
{

}

bool CLandauPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    dValue = gsl_ran_landau_pdf(x);
    return true;

}
bool CLandauPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}

bool CLandauPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {

    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CFlatPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CFlatPDF::CFlatPDF()
{
    ADD_PROPERTY_TYPE(LowerBound, (0.5), "Parameters", App::Prop_None, "The lower bound limit value");
    ADD_PROPERTY_TYPE(UpperBound, (2.5), "Parameters", App::Prop_None, "The upper bound limit value");
}

bool CFlatPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    dValue = gsl_ran_flat_pdf(x, LowerBound.getValue() /*a*/, UpperBound.getValue() /*b*/);
    return true;

}
bool CFlatPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    if (Data.minVariableX.getValue() < LowerBound.getValue()
        || (Data.minVariableX.getValue()
            + Data.numberOfIncrementOfVariableX.getValue() * Data.incrementOfVariableX.getValue())
            > UpperBound.getValue())
        return false;

    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CFlatPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CGammaPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CGammaPDF::CGammaPDF()
{
    ADD_PROPERTY_TYPE(ParameterA, (0.5), "Parameters", App::Prop_None, "The A parameter");
    ADD_PROPERTY_TYPE(ParameterB, (2.5), "Parameters", App::Prop_None, "The B parameter");
}

bool CGammaPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    dValue = gsl_ran_gamma_pdf(x, ParameterA.getValue() /*a*/, ParameterB.getValue() /*b*/);
            return true;

}
bool CGammaPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CGammaPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CLognormalPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CLognormalPDF::CLognormalPDF()
{
    ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
    ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The stantard devialtion");
}

bool CLognormalPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    dValue = gsl_ran_lognormal_pdf(x, Mean.getValue() /*zeta*/, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*sigma*/);
    return true;

}
bool CLognormalPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CLognormalPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CChiSquaredPDF, WindLabAPI::WindLabFeatureProbabilityDensityFunction)

CChiSquaredPDF::CChiSquaredPDF()
{
    ADD_PROPERTY_TYPE(DegreeOfFreedom, (1.0), "Parameters", App::Prop_None, "The degree of freedom");
}

bool CChiSquaredPDF::ComputePDFValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    dValue = gsl_ran_chisq_pdf(x, DegreeOfFreedom.getValue() /*nu*/);
    return true;

}
bool CChiSquaredPDF::ComputePDFVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;

   for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
        dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
        returnResult = ComputePDFValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CChiSquaredPDF::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

//ALL CUMULATIVE PROBABILITY DENSITY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//static int CPDtype = 0;
//

PROPERTY_SOURCE(RandomnessProviders::CWeibullCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CWeibullCPD::CWeibullCPD()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (1.0), "Parameters", App::Prop_None, "The Weibull distribution exponential factor");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

   static const char* types[] = {"Lower tail", "Upper tail", nullptr};
   Types.setEnums(types);
}


bool CWeibullCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_weibull_P(x,  ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/);
        break;
    case 1:
        dValue = gsl_cdf_weibull_Q(x, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/);
        break;
    default:
        break;
    }

            return true;

}
bool CWeibullCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}
bool CWeibullCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para1 = dlg->getParametersVector().at(1);
        para2 = dlg->getParametersVector().at(2);

    }

    return true;

}

//
PROPERTY_SOURCE(RandomnessProviders::CGaussianCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CGaussianCPD::CGaussianCPD()
{
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
   ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

   static const char* types[] = {"Lower tail", "Upper tail", nullptr};
   Types.setEnums(types);

}
bool CGaussianCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_gaussian_P(x, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*a*/) + Mean.getValue() /*mu*/;
        break;
    case 1:
        dValue = gsl_cdf_gaussian_Q(x, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*a*/) + Mean.getValue() /*mu*/;
        break;
    default:
        break;
    }

            return true;

}
bool CGaussianCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CGaussianCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);

    }

    return true;

}

//
PROPERTY_SOURCE(RandomnessProviders::CExponentialCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CExponentialCPD::CExponentialCPD()
{
   ADD_PROPERTY_TYPE(Mean, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
    ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

    static const char* types[] = {"Lower tail", "Upper tail", nullptr};
    Types.setEnums(types);
}

bool CExponentialCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_exponential_P(x, Mean.getValue());
        break;
    case 1:
        dValue = gsl_cdf_exponential_Q(x, Mean.getValue());
        break;
    default:
        break;
    }

            return true;

}
bool CExponentialCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CExponentialCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

//
PROPERTY_SOURCE(RandomnessProviders::CLaplaceCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CLaplaceCPD::CLaplaceCPD()
{
   ADD_PROPERTY_TYPE(Width, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
   ADD_PROPERTY_TYPE(Mean, (1.0), "Parameters", App::Prop_None, "The mean or the expected value");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

   static const char* types[] = {"Lower tail", "Upper tail", nullptr};
   Types.setEnums(types);
}

bool CLaplaceCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_laplace_P(x, Width.getValue() /*a*/) + Mean.getValue() /*mu*/;
        break;
    case 1:
        dValue = gsl_cdf_laplace_Q(x, Width.getValue() /*a*/) + Mean.getValue() /*mu*/;
        break;
    default:
        break;
    }

            return true;

}
bool CLaplaceCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CLaplaceCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}

//
PROPERTY_SOURCE(RandomnessProviders::CExponentialPowerCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CExponentialPowerCPD::CExponentialPowerCPD()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(ExponentFactor, (2.5), "Parameters", App::Prop_None, "The exponent factor");
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

   static const char* types[] = {"Lower tail", "Upper tail", nullptr};
   Types.setEnums(types);
}

bool CExponentialPowerCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_exppow_P(x, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/) + Mean.getValue() /*mu*/;
        break;
    case 1:
        dValue = gsl_cdf_exppow_P(x, ScaleParameter.getValue() /*a*/, ExponentFactor.getValue() /*b*/) + Mean.getValue() /*mu*/;
        break;
    default:
        break;
    }

            return true;

}
bool CExponentialPowerCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}

bool CExponentialPowerCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
        para2 = dlg->getParametersVector().at(2);

    }

    return true;
}

//
PROPERTY_SOURCE(RandomnessProviders::CCauchyCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CCauchyCPD::CCauchyCPD()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

   static const char* types[] = {"Lower tail", "Upper tail", nullptr};
   Types.setEnums(types);
}

bool CCauchyCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_cauchy_P(x, ScaleParameter.getValue() /*a*/);
        break;
    case 1:
        dValue = gsl_cdf_cauchy_Q(x, ScaleParameter.getValue() /*a*/);
        break;
    default:
        break;
    }

    return true;

}
bool CCauchyCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CCauchyCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CRayleighCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CRayleighCPD::CRayleighCPD()
{
   ADD_PROPERTY_TYPE(ScaleParameter, (1.0), "Parameters", App::Prop_None, "The scale parameter");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

   static const char* types[] = {"Lower tail", "Upper tail", nullptr};
   Types.setEnums(types);
}

bool CRayleighCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
   switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_rayleigh_P(x, ScaleParameter.getValue() /*sigma*/);
        break;
    case 1:
        dValue = gsl_cdf_rayleigh_Q(x, ScaleParameter.getValue() /*sigma*/);
        break;
    default:
        break;
    }

            return true;

}
bool CRayleighCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}
bool CRayleighCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

//
PROPERTY_SOURCE(RandomnessProviders::CFlatCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CFlatCPD::CFlatCPD()
{
    ADD_PROPERTY_TYPE(LowerBound, (0.5), "Parameters", App::Prop_None, "The lower bound limit value");
    ADD_PROPERTY_TYPE(UpperBound, (2.5), "Parameters", App::Prop_None, "The upper bound limit value");
    ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

    static const char* types[] = {"Lower tail", "Upper tail", nullptr};
    Types.setEnums(types);
}

bool CFlatCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_flat_P(x, LowerBound.getValue() /*a*/, UpperBound.getValue() /*b*/);
        break;
    case 1:
        dValue = gsl_cdf_flat_Q(x, LowerBound.getValue() /*a*/, UpperBound.getValue() /*b*/);
        break;
    default:
        break;
    }

    return true;

}
bool CFlatCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CFlatCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);

    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CGammaCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CGammaCPD::CGammaCPD()
{
    ADD_PROPERTY_TYPE(ParameterA, (0.5), "Parameters", App::Prop_None, "The A parameter");
    ADD_PROPERTY_TYPE(ParameterB, (2.5), "Parameters", App::Prop_None, "The B parameter");
    ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

    static const char* types[] = {"Lower tail", "Upper tail", nullptr};
    Types.setEnums(types);
}

bool CGammaCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_gamma_P(x, ParameterA.getValue() /*a*/, ParameterB.getValue() /*b*/);
    case 1:
        dValue = gsl_cdf_gamma_Q(x, ParameterA.getValue() /*a*/, ParameterB.getValue() /*b*/);
        break;
    default:
        break;
    }

            return true;

}
bool CGammaCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}
bool CGammaCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CLognormalCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CLognormalCPD::CLognormalCPD()
{
   ADD_PROPERTY_TYPE(Mean, (0.0), "Parameters", App::Prop_None, "The mean value");
   ADD_PROPERTY_TYPE(StandardDeviation, (1.0), "Parameters", App::Prop_None, "The standard deviation");
   ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

    static const char* types[] = {"Lower tail", "Upper tail", nullptr};
    Types.setEnums(types);
}
bool CLognormalCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_lognormal_P(x, Mean.getValue() /*zeta*/, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*sigma*/);
    case 1:
        dValue = gsl_cdf_lognormal_Q(x, Mean.getValue() /*zeta*/, StandardDeviation.getQuantityValue().getValueAs(Base::Quantity::MetrePerSecond) /*sigma*/);
        break;
    default:
        break;
    }

            return true;

}
bool CLognormalCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
     bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;
}
bool CLognormalCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
        para1 = dlg->getParametersVector().at(1);
    }

    return true;
}


//
PROPERTY_SOURCE(RandomnessProviders::CChiSquaredCPD, WindLabAPI::WindLabFeatureCumulativeProbabilityDistribution)

CChiSquaredCPD::CChiSquaredCPD()
{
    ADD_PROPERTY_TYPE(DegreeOfFreedom, (1.0), "Parameters", App::Prop_None, "The degree of freedom");
    ADD_PROPERTY_TYPE(Types, ((long int)0), "CPD Type", App::Prop_None, "The CPD type");

    static const char* types[] = {"Lower tail", "Upper tail", nullptr};
    Types.setEnums(types);
}

bool CChiSquaredCPD::ComputeCPDValue(const WindLabAPI::WindLabSimuData& Data, const double &x, double &dValue)
{
    switch (Types.getValue()) {
    case 0:
        dValue = gsl_cdf_chisq_P(x, DegreeOfFreedom.getValue() /*nu*/);
    case 1:
        dValue = gsl_cdf_chisq_Q(x, DegreeOfFreedom.getValue() /*nu*/);
        break;
    default:
        break;
    }

            return true;

}
bool CChiSquaredCPD::ComputeCPDVectorX(const WindLabAPI::WindLabSimuData& Data, vec &dVarVector, vec &dValVector)
{
    bool returnResult = true;
    for (int j = 0 ; j < Data.numberOfIncrementOfVariableX.getValue() && false == Data.isInterruptionRequested.getValue() && true == returnResult; j++)
    {
       dVarVector(j) = Data.minVariableX.getValue() + j * Data.incrementOfVariableX.getValue();
       returnResult = ComputeCPDValue(Data, dVarVector(j), dValVector(j));    
    }

    return returnResult;

}
bool CChiSquaredCPD::OnInitialSetting(const WindLabAPI::WindLabSimuData& Data)
{
    std::unique_ptr<RandomDistributionDialog> dlg(new RandomDistributionDialog());
    if (dlg->exec() == QDialog::Accepted)
    {
        para0 = dlg->getParametersVector().at(0);
    }

    return true;
}

