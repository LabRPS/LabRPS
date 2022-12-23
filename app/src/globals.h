#ifndef LAB_RPS_GLOBALS_H
#define LAB_RPS_GLOBALS_H

#include <QColor>
#include <QObject>
#include <QString>

//! Definition of global constants and enums
/**
 * This class must not be instanced. All members are static.
 */
class LabRPS : public QObject {
    Q_OBJECT
    Q_ENUMS(PlotDesignation)
    Q_ENUMS(ColumnMode)
    Q_ENUMS(ColumnDataType)

private:
    LabRPS() {}  // don't allow instancing

public:
    virtual ~LabRPS() {}  // avoid the warning message

    // Url links
    static const char* homepage_Uri;
    static const char* wiki_Uri;
    static const char* forum_Uri;
    static const char* bugreport_Uri;
    static const char* download_Uri;

    // rps

    // phenomena
    static QString rpsPhenomenonWindVelocity;
    static QString rpsPhenomenonSeaSurface;
    static QString rpsPhenomenonSeismicGroundMotion;
    static QString rpsPhenomenonUserDefined;

    // object groups
    static QString objGroupLocationDistribution;
    static QString objGroupMeanWindProfile;
    static QString objGroupAlongWindSpectrum;
    static QString objGroupVerticalWindSpectrum;
    static QString objGroupAcrossWindSpectrum;
    static QString objGroupSpectrumDecompositionMethod;
    static QString objGroupCoherenceFunction;
    static QString objGroupSimulationMethod;
    static QString objGroupFrequencyDistribution;
    static QString objGroupRandomnessProvider;
    static QString objGroupModulationFunction;
    static QString objGroupCorrelationFunction;
    static QString objGroupTableTool;
    static QString objGroupMatrixTool;
    static QString objGroupUserDefinedRPSObject;
    static QString objGroupUserDefinedPhenomenonObject;
    static QString objGroupCumulativeProbabilityDistribution;
    static QString objGroupGustFactor;
    static QString objGroupKurtosis;
    static QString objGroupPeakFactor;
    static QString objGroupProbabilityDensityFunction;
    static QString objGroupRoughness;
    static QString objGroupShearVelocityOfFlow;
    static QString objGroupSkewness;
    static QString objGroupStandardDeviation;
    static QString objGroupTurbulenceIntensity;
    static QString objGroupTurbulenceScale;
    static QString objGroupVariance;
    static QString objGroupWavePassageEffect;

    // available comparison categories
    static QString ComputeCrossCoherenceVectorF;
    static QString ComputeCrossCoherenceVectorT;
    static QString ComputeCrossCorrelationVectorT;
    static QString ComputeFrequenciesVectorF;
    static QString ComputeMeanWindSpeedVectorP;
    static QString ComputeMeanWindSpeedVectorT;
    static QString ComputeModulationVectorT;
    static QString ComputeModulationVectorP;
    static QString ComputeDecomposedCrossSpectrumVectorF;
    static QString ComputeDecomposedCrossSpectrumVectorT;
    static QString Simulate;
    static QString SimulateInLargeScaleMode;
    static QString ComputeXAutoSpectrumVectorF;
    static QString ComputeYAutoSpectrumVectorF;
    static QString ComputeZAutoSpectrumVectorF;
    static QString ComputeXAutoSpectrumVectorT;
    static QString ComputeYAutoSpectrumVectorT;
    static QString ComputeZAutoSpectrumVectorT;
    static QString UserDefinedRPSObjectCompute;
    static QString ComputeCDFVectorP;
    static QString ComputeGustFactorVectorP;
    static QString ComputeKurtosisVectorP;
    static QString ComputePeakFactorVectorP;
    static QString ComputePDFVectorP;
    static QString ComputeRoughnessVectorP;
    static QString ComputeShearVelocityOfFlowVectorP;
    static QString ComputeSkewnessVectorP;
    static QString ComputeStandardDeviationVectorP;
    static QString ComputeTurbulenceIntensityVectorP;
    static QString ComputeTurbulenceScaleVectorP;
    static QString ComputeVarianceVectorP;
    static QString ComputeWavePassageEffectVectorF;
    static QString ComputeWavePassageEffectVectorT;

    static QString ComputeGustFactorVectorT;
    static QString ComputeKurtosisVectorT;
    static QString ComputePeakFactorVectorT;
    static QString ComputeRoughnessVectorT;
    static QString ComputeShearVelocityOfFlowVectorT;
    static QString ComputeSkewnessVectorT;
    static QString ComputeStandardDeviationVectorT;
    static QString ComputeTurbulenceIntensityVectorT;
    static QString ComputeTurbulenceScaleVectorT;
    static QString ComputeVarianceVectorT;


    //! Types of plot designations
    enum PlotDesignation {
        noDesignation = 0,  //!< no plot designation
        X = 1,              //!< x values
        Y = 2,              //!< y values
        Z = 3,              //!< z values
        xErr = 4,           //!< x errors
        yErr = 5            //!< y errors
    };

    //! The column mode (defines output and input filter for table columns)
    enum ColumnMode {
        Numeric = 0,   //!< column contains doubles
        Text = 1,      //!< column contains strings
        Month = 4,     //!< column contains month names
        Day = 5,       //!< column containts day of week names
        DateTime = 6,  //!< column contains dates and/or times
        // 2 and 3 are skipped to avoid problems with old obsolete values
    };

    //! Column data type
    enum ColumnDataType {
        TypeDouble = 1,
        TypeString = 2,
        TypeMonth = 3,
        TypeDay = 4,
        TypeDateTime = 5
    };

    // Return the LabRPS version number
    static int version();

    static QString enumValueToString(int key, const QString& enum_name);
    static int enumStringToValue(const QString& string, const QString& enum_name);

    // Return the LabRPS version string ("LabRPS x.y.z" without extra
    // version) used in the project file
    static QString schemaVersion();
    /// the user visible release version string (x.Dy usually)
    static QString versionString();
    static QString windLabAPIVersionString();
    static QString windLabPluginAPIVersionString();
    static QString userDefinedPhenomenonAPIVersionString();
    static QString userDefinedPhenomenonPluginAPIVersionString();

    // Return the extra version as a string
    static QString extraVersion();

    // Return the release date as a string
    static QString releaseDateString();
    static QDate releaseDate();

    // Returns original author
    static QString originalAuthor();

    static QString originalAuthorWithMail();
    static QStringList getLocales();
    static void setLocales(QStringList locales);

private:
    /* 0xMMmmbb means MM.mm.bb with<br>
   * MM = major version
   * mm = minor version
   * bb = bugfix version */
    static const int LabRPS_versionNo;
    static const char* LabRPS_version;
    static const char* LabRPS_Windlab_api_version;
    static const char* LabRPS_Windlab_plugin_api_version;
    static const char* LabRPS_UserDefinedPhenomenon_api_version;
    static const char* LabRPS_UserDefinedPhenomenon_plugin_api_version;

    // Extra version information string (like "-alpha", "-beta", "-rc1", etc...)
    static const char* extra_version;
    // Release date
    static const QDate release_date;
    static QStringList locales_;
};

#endif  // LAB_RPS_GLOBALS_H
