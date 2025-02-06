/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
 *                                                                         *
 *   This file is part of the LabRPS development system.                   *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef SeaLab_SeaLabSimulation_H
#define SeaLab_SeaLabSimulation_H

#include <App/PropertyStandard.h>
#include <App/Simulation.h>
#include <Mod/SeaLabAPI/App/SeaLabFeature.h>
#include <App/PropertyUnits.h>
#include <Mod/SeaLab/SeaLabGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Base/Vector3D.h>
#include <Mod/SeaLabAPI/App/SeaLabSimulationData.h>

namespace SeaLabAPI
{
	class SeaLabFeatureDescription;
}

namespace SeaLab {
 class SeaLabSimulationPy; // the python SeaLabSimulation class

/**
 * @brief Container of objects relevant to one simulation.
 *
 * @details
 *  A Simulation contains all objects necessary for a complete specification
 *  of a simulation. After computing it also contains the result of the
 *  simulation. The Simulation object is a container but also offers ways to run the SeaLab features in the simulation.
 *
 *  The Simulation class is essentially a App::DocumentObjectGroup. It handles
 *  all the container stuff. The difference is that the Simulation document
 *  object uses a different ViewProvider, has a Uid property and does some
 *  compatibility handling via handleChangedPropertyName.
 *
 *  This implies that it is not checked which objects are put into the
 *  Simulation object. Every document object of LabRPS can be part of a
 *  Simulation.
 */
 class SeaLabExport SeaLabSimulation: public App::Simulation
 {
    
    PROPERTY_HEADER(SeaLab::SeaLabSimulation);

public:

    SeaLabSimulation();
    virtual ~SeaLabSimulation();

    App::PropertyString Phenomenon;
	App::PropertyInteger NumberOfProcess;
	App::PropertyInteger NumberOfFrequency;
	App::PropertyInteger NumberOfSample;
    App::PropertyInteger SampleIndex;
	App::PropertyInteger NumberOfTimeIncrements;
	App::PropertyInteger LocationIndexJ;
	App::PropertyInteger LocationIndexK;
	App::PropertyInteger FrequencyIndex;
	App::PropertyInteger DirectionIndex;
	App::PropertyInteger TimeIndex;
	App::PropertyInteger NumberOfTimeLags;
	App::PropertyInteger NumberOfWaveLengthIncrements;
	App::PropertyInteger NumberOfDirectionIncrements;
	App::PropertyInteger WaveLengthIndex;
	App::PropertyBool Stationarity;
	App::PropertyBool Gaussianity;
	App::PropertyBool  ComparisonMode;
	App::PropertyBool IsSimulationSuccessful;
	App::PropertyBool IsInterruptionRequested;
	App::PropertyBool UniformModulation;
	App::PropertyTime MinTime;
	App::PropertyTime MaxTime;
	App::PropertyTime TimeIncrement;
	App::PropertyFrequency MinFrequency;
	App::PropertyFrequency FrequencyIncrement;
	App::PropertyFrequency MaxFrequency;
	App::PropertyLength MinWaveLength;
	App::PropertyLength MaxWaveLength;
	App::PropertyLength WaveLengthIncrement;
	App::PropertyAngle MinDirection;
	App::PropertyAngle MaxDirection;
	App::PropertyAngle DirectionIncrement;
	App::PropertyEnumeration SpatialDistribution;
	App::PropertyEnumeration ShearVelocity;
	App::PropertyEnumeration MeanFunction;
	App::PropertyEnumeration FrequencySpectrum;
    App::PropertyEnumeration DirectionalSpectrum;
	App::PropertyEnumeration DirectionalSpreadingFunction;
	App::PropertyEnumeration CoherenceFunction;
	App::PropertyEnumeration SimulationMethod;
	App::PropertyEnumeration FrequencyDistribution;
	App::PropertyEnumeration SpectrumDecompositionMethod;
	App::PropertyEnumeration RandomnessProvider;
	App::PropertyEnumeration ModulationFunction;
	App::PropertyEnumeration CorrelationFunction;
	App::PropertyEnumeration VarianceFunction;
	App::PropertyEnumeration TableTool;
	App::PropertyEnumeration MatrixTool;
	App::PropertyEnumeration UserDefinedRPSObject;
	App::PropertyEnumeration CumulativeProbabilityDistribution;
	App::PropertyEnumeration Kurtosis;
	App::PropertyEnumeration PeakFactor;
	App::PropertyEnumeration ProbabilityDensityFunction;
	App::PropertyEnumeration Roughness;
	App::PropertyEnumeration ShearVelocityOfFlow;
	App::PropertyEnumeration Skewness;
	App::PropertyEnumeration StandardDeviation;
	App::PropertyEnumeration Variance;
	App::PropertyEnumeration WavePassageEffect;
	App::PropertyEnumeration Direction;
	App::PropertyInteger NumberOfIncrementOfVariableX;
    App::PropertyInteger IndexOfVariableX;
    App::PropertyFloat IncrementOfVariableX;
    App::PropertyFloat MinVariableX;
    App::PropertyPath WorkingDirectoryPath;
    App::PropertyString FileName;
    App::PropertyInteger NumberOfGridPointsAlongX;
    App::PropertyInteger NumberOfGridPointsAlongY;
    App::PropertyLength GridSpacingAlongX;
    App::PropertyLength GridSpacingAlongY;
    App::PropertyLength GridLengthAlongX;
    App::PropertyLength GridLengthAlongY;

    App::PropertyUUID    Uid;

    virtual const char* getViewProviderName() const {
        return "SeaLabGui::ViewProviderSeaLabSimulation";
    }

protected:

    virtual void handleChangedPropertyName(
        Base::XMLReader &reader, const char * TypeName, const char *PropName);
public:
    /**
  * run the simulation.
  */
    virtual bool run();

    virtual bool stop();

    // get the name of the random phenomenon this simulation with produice
    virtual std::string getPhenomenonName() const;

    // get the name of the workbench that implement this simulation
    virtual std::string workbenchName() const;

    void setSimulationData(SeaLabAPI::SeaLabSimulationData* simuData);
    SeaLabAPI::SeaLabSimulationData* getSimulationData() const;

    SeaLabAPI::SeaLabFeature* createFeature(Base::Type type, std::string pluggedObjectTypeName,
                                       std::string name);
	void setEnums(Base::Type type);
    void resetAllEnums();

    void seaLabFeatureInitalSetting(QString group, QString currentSelected);
    static QStringList findAllPluggedSeaLabFeatures(QString group);
    static QStringList findAllFeatureMethods(QString group);

    QStringList findAllSeaLabFeatures(Base::Type type);
	std::vector<std::string> findAllSeaLabFeaturesOfThisType(Base::Type type);
    QStringList findAllSeaLabFeaturesByGoupAndType(QString group, QString type);
    std::vector<QString> getSeaLabPluggableFeatures();
    std::vector<Base::Type> getRPSTypesOfPluggableFeatures();
    Base::Type getRPSType(QString group);

	void updateSimulationData();

	SeaLabAPI::SeaLabFeatureDescription* GetSeaLabPluggedSeaLabFeatureDescription(const QString& objectGroup, const QString& objName);

    virtual bool doubleClicked(void);
	virtual void onChanged(const App::Property* prop);

	void createNewSimulation();

	virtual PyObject *getPyObject(void) override;

public:
	//get active features
	App::DocumentObject* getActiveCoherence();
    App::DocumentObject* getActiveCorrelation();
    App::DocumentObject* getActiveCumulativeProbabilityDistribution();
    App::DocumentObject* getActiveFrequencyDistribution();
    App::DocumentObject* getActiveKurtosis();
    App::DocumentObject* getActiveLocationDistribution();
    App::DocumentObject* getActiveMeanAcceleration();
    App::DocumentObject* getActiveModulation();
    App::DocumentObject* getActivePeakFactor();
    App::DocumentObject* getActiveProbabilityDensityFunction();
    App::DocumentObject* getActivePSDDecompositionMethod();
    App::DocumentObject* getActiveRandomness();
    App::DocumentObject* getActiveShearVelocityOfFlow();
    App::DocumentObject* getActiveSimulationMethod();
    App::DocumentObject* getActiveSkewness();
    App::DocumentObject* getActiveStandardDeviation();
    App::DocumentObject* getActiveUserDefinedRPSObject();
    App::DocumentObject* getActiveVariance();
    App::DocumentObject* getActiveWavePassageEffect();
    App::DocumentObject* getActiveMatrixTool();
    App::DocumentObject* getActiveTableTool();
    App::DocumentObject* getActiveFrequencySpectrum();
    App::DocumentObject* getActiveDirectionalSpectrum();
    App::DocumentObject* getActiveDirectionalSpreadingFunction();

    void setActiveFeature(App::RPSFeature* feature);
    App::RPSFeature* getActiveFeature(const QString group);
    std::vector <App::RPSFeature*> getAllFeatures(const QString group);

	// coherence function
    bool computeCrossCoherenceVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName);
    bool computeCrossCoherenceVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName);
    bool computeCrossCoherenceMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName);

	// correlation function
	bool computeCrossCorrelationVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeCrossCorrelationMatrixPP(const double &dTime, mat &dCorrelationMatrix, std::string& featureName);

   // frequency
    bool computeFrequenciesVectorF(const Base::Vector3d &location, vec &dValVector, std::string& featureName);
    bool computeFrequenciesMatrixFP(mat& dMatrix, std::string& featureName);
    bool computeLocationCoordinateMatrixP3(mat& dLocCoord, std::string& featureName);

	// mean ground motion acceleration
    bool computeMeanAccelerationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeMeanAccelerationVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName);

	// modulation function
    bool computeModulationValue(Base::Vector3d location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName);
    bool computeModulationVectorT(Base::Vector3d location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeModulationVectorP(const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeModulationVectorF(Base::Vector3d location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);

	// psd decomposition
    bool computeDecomposedCrossSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName);
    bool computeDecomposedCrossSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName);
    bool computeDecomposedCrossSpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dPSDMatrix, std::string& featureName);

	// randomness
    bool generateRandomMatrixFP(mat &dRandomValueArray, std::string& featureName);
    bool generateRandomCubeFPS(cube &dRandomValueCube, std::string& featureName);

    // frequency spectrum
    bool computeAutoFrequencySpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, double &dValue, std::string& featureName);
    
    bool computeAutoFrequencySpectrumVectorF(const Base::Vector3d &location, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeAutoFrequencySpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeCrossFrequencySpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName);

    bool computeCrossFrequencySpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName);

    bool computeCrossFrequencySpectrumMatrixPP(const double &dFrequency, const double &dTime, cx_mat &psdMatrix, std::string& featureName);

    bool computeCrossFrequencySpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName);

    // direction spectrum
  
    bool computeCrossDirectionalSpectrumValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, const double &dDirection, std::complex<double> &dValue, std::string& featureName);

    bool computeCrossDirectionalSpectrumVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, const double &dDirection, vec &dVarVector, cx_vec &dValVector, std::string& featureName);

    bool computeCrossDirectionalSpectrumVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dDirection, vec &dVarVector, cx_vec &dValVector, std::string& featureName);

    bool computeCrossDirectionalSpectrumVectorD(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName);

    bool computeCrossDirectionalSpectrumMatrixPP(const double &dFrequency, const double &dTime, const double &dDirection, cx_mat &psdMatrix, std::string& featureName);

    bool computeAutoDirectionalSpectrumValue(const Base::Vector3d &location, const double &dFrequency, const double &dTime, const double &dDirection, double &dValue, std::string& featureName);
    
    bool computeAutoDirectionalSpectrumVectorF(const Base::Vector3d &location, const double &dTime, const double &dDirection, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeAutoDirectionalSpectrumVectorT(const Base::Vector3d &location, const double &dFrequency, const double &dDirection, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeAutoDirectionalSpectrumVectorD(const Base::Vector3d &location, const double &dFrequency, const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);

   // directional spreading function
    bool computeDirectionalSpreadingFunctionValue(const Base::Vector3d &location, const double &dFrequency, const double &dDirection, double &dValue, std::string& featureName);
    
    bool computeDirectionalSpreadingFunctionVectorF(const Base::Vector3d &location, const double &dDirection, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeDirectionalSpreadingFunctionVectorP(const double &dFrequency, const double &dDirection, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeDirectionalSpreadingFunctionVectorD(const Base::Vector3d &location, const double &dFrequency, vec &dVarVector, vec &dValVector, std::string& featureName);

    bool computeCrossCoherenceValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName);
    bool computeCrossCorrelationValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, double &dValue, std::string& featureName);
    bool computeMeanAccelerationValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName);
    bool computeRandomValue(double &dValue, std::string& featureName);
	bool computeFrequencyValue(const Base::Vector3d &location, const int &frequencyIndex, double &dValue, std::string& featureName);

    bool tableToolCompute(mat& inputTable, mat& outputTable, std::string& featureName);
    bool matrixToolCompute(mat& inputTable, mat& outputMatrix, std::string& featureName);
    bool userDefinedRPSObjectCompute(mat& dresult, std::string& featureName);

    bool computeCPDValue(const double& x, double& dValue, std::string& featureName);
    bool computeCPDVectorX(vec& dVarVector, vec& dValVector, std::string& featureName);
    
    //kurtosis
    bool computeKurtosisValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName);
    bool computeKurtosisVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeKurtosisVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName);

    //peak factor
    bool computePeakFactorValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName);
    bool computePeakFactorVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computePeakFactorVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName);

    //pdf
    bool computePDFValue(const double& x, double& dValue, std::string& featureName);
    bool computePDFVectorX(vec& dVarVector, vec& dValVector, std::string& featureName);

    //shear velocity
    bool computeShearVelocityOfFlowValue(Base::Vector3d location, const double &dTime, double &dValue, std::string& featureName);
    bool computeShearVelocityOfFlowVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeShearVelocityOfFlowVectorT(Base::Vector3d location, vec &dVarVector, vec &dValVector, std::string& featureName);

    //skewness
    bool computeSkewnessValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName);
    bool computeSkewnessVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeSkewnessVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName);

    //standard deviation
    bool computeStandardDeviationValue(const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName);
    bool computeStandardDeviationVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeStandardDeviationVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName);

      //variance
    bool computeVarianceValue( const Base::Vector3d &location, const double &dTime, double &dValue, std::string& featureName);
    bool computeVarianceVectorP(const double &dTime, vec &dVarVector, vec &dValVector, std::string& featureName);
    bool computeVarianceVectorT(const Base::Vector3d &location, vec &dVarVector, vec &dValVector, std::string& featureName);

    // wave passage effect
    bool computeWavePassageEffectVectorF(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dTime, vec &dVarVector, cx_vec &dValVector, std::string& featureName);
    bool computeWavePassageEffectVectorT(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, vec &dVarVector, cx_vec &dValVector, std::string& featureName);
    bool computeWavePassageEffectMatrixPP(const double &dFrequency, const double &dTime, cx_mat &dCoherenceMatrix, std::string& featureName);
    bool computeWavePassageEffectValue(const Base::Vector3d &locationJ, const Base::Vector3d &locationK, const double &dFrequency, const double &dTime, std::complex<double> &dValue, std::string& featureName);

    bool simulate(cube &dPhenomenon, std::string& featureName);
    App::DocumentObject* addFeature(const std::string featureName, const std::string simulationName, const std::string featureTypeName, const std::string featureGroup);
public:
    /** Called when a simulation should be aborted */
    virtual void slotSimulationAbort(const App::Document& Doc);
private:
    SeaLabAPI::SeaLabSimulationData* _simuData;

protected: 
    Py::SmartPtr PythonObject;
};

} //namespace SeaLab


#endif // SeaLab_SeaLabSimulation_H
