
#include "DesignResponseSpectrum.h"
#include "widgets/DlgDesignResponseSpectrum.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <cmath>
#include <Eigen/Dense>
#include <Gui/Control.h>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::DesignResponseSpectrum, SeismicLabAPI::SeismicLabFeatureTableTool)

DesignResponseSpectrum::DesignResponseSpectrum()
{
    ADD_PROPERTY_TYPE(DesignCode, ((long int)1), "Parameters", App::Prop_Transient, "The structural design code.");
    static const char* designCodes[] = {"None", "Eurocode 8 1998-1 :2004",
                                        "ASCE 41-17 (United States of America)",
                                        "ASCE 7-16 (United States of America)",
                                        "UBC 1997 (United States of America)",
                                        "National Building Code of Canada 2015 (Canada)",
                                        "NTC-18 - Italian Code",
                                        "KANEPE - Greek Code",
                                        "TBDY 2018 - Turkish",
                                        "Arrete 2010/2011 - French Code",
                                        "NCSE-02 - Spanish Code",
                                        "NTE E.030 2016 - Peruvian Code",
                                        "NCh 433 - Chilean Code",
                                        "NSR10 - Colombian Code",
                                        "NEC 2014 - Ecuadorean Code",
                                        "Notification 1457-2000 - Japanese Code",
                                        "IS 1893 - Indian Code",
                                        "NBC 105 - Nepalese Code",
                                        "SP 2007 - Pakistani Code",
                                        "EC8 Portugal National Annex - Portugese Code",
                                        "Slovenian Standard - Slovenian Code",
                                        "NZS 1170.5:2004 - New Zealand Code",
                                        "MOC 2008 - Mexican Code",
                                        "NMX-R-079-SCFI-2015 - Mexican Code",
                                        "MOC 2015 - Mexican Code",
                                        "NTC 2004 - Mexican Code",
                                        "CSCR 2010 - Costa Rican Code",
                                        "INPRES-CIRSOC 1991 - Argentinian Code",
                                        "INPRES-CIRSOC 2013 - Argentinian Code",
                                        "Standard 2008 - Iranian Code",
                                        "KDS 17 10 00 2018 - Korean Code",
                                        "INDICATIV P 100-1/2013 - Romanian Code",
                                        "AS 1170.4/2007 - Australian Code", nullptr};
    DesignCode.setEnums(designCodes);

    ADD_PROPERTY_TYPE(SpacialComponent, ((long int)1), "Parameters", App::Prop_None, "The horizontal or vertical acceleration component of the earthquake motion.");
    static const char* spacialComponents[] = {"None", "Horizontal", "Vertical", nullptr};
    SpacialComponent.setEnums(spacialComponents);

    ADD_PROPERTY_TYPE(Elasticity, ((long int)1), "Parameters", App::Prop_None, "The horizontal or vertical acceleration component of the earthquake motion.");
    static const char* elasticities[] = {"None", "Elastic", "Design", nullptr};
    Elasticity.setEnums(elasticities);

    ADD_PROPERTY_TYPE(NationalAnnex, ((long int)1), "Parameters", App::Prop_None, "This allows to compute the response spectrum by considering the national annexes requirements.");
    static const char* nationalAnnexes[] = {"None", "EN Recommended", nullptr};
    NationalAnnex.setEnums(nationalAnnexes);

    ADD_PROPERTY_TYPE(DampingRatio, (5), "Parameters", App::Prop_None, "This is the damping ration. It is 5% by default. ");
    ADD_PROPERTY_TYPE(ReferencePeakGroundAcceleration, (0.16), "Parameters", App::Prop_None, "This is the reference peak ground acceleration. It defines the seismic intensity");

    ADD_PROPERTY_TYPE(SpectrumType, ((long int)1), "Parameters", App::Prop_None, "The type of spectrum (1 or 2). It affects the response spectrum.");
    static const char* spectrumTypes[] = {"None", "Type 1", "Type 2", nullptr};
    SpectrumType.setEnums(spectrumTypes);

    ADD_PROPERTY_TYPE(SoilType, ((long int)1), "Parameters", App::Prop_None, "The type of soil (A to E). The ground type modifies the spectral acceleration. This introduces a soil amplification factor which is determined based on the input soil type. Different soil types (A, B, C, D, E) modify the spectral acceleration based on the expected amplification of seismic waves in those conditions.");
    static const char* soilTypes[] = {"None", "A", "B", "C", "D", "E", nullptr};
    SoilType.setEnums(soilTypes);

    ADD_PROPERTY_TYPE(ImportanceClass, ((long int)1), "Parameters", App::Prop_None, "he importance class (I to IV). It affects the design of the structure. The importance class determines the level of seismic resistance required. Structures classified as critical require higher spectral accelerations.");
    static const char* importanceClasses[] = {"None", "I", "II", "III", "IV", "E", nullptr};
    ImportanceClass.setEnums(importanceClasses);

    ADD_PROPERTY_TYPE(BehaviorFactor, (1.00), "Parameters", App::Prop_None, "The increment of the mean speed");
    ADD_PROPERTY_TYPE(LowerBoundFactor, (0.20), "Parameters", App::Prop_None, "The increment of the mean speed");

}


bool DesignResponseSpectrum::TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData& Data, const mat& inputTable, mat& outputTable)
{
    if (inputTable.rows() != Data.numberOfTimeIncrements.getValue() || inputTable.cols() != 2)
    {
        Base::Console().Warning("The computation fails. Please make sure the simulated wind velocity data table is the active window before you run this code.");
        outputTable.resize(0,0);
        return false;
    }

    SeismicLabTools::DesignResponseSpectrum designResponseSpectrum;

    	// Compute the mean wind speed matrix
	for (int loop = 0; loop < Data.numberOfTimeIncrements.getValue() && !Data.isInterruptionRequested.getValue(); loop++)
	{
		const double dTime = Data.minTime.getValue() + Data.timeIncrement.getValue() * loop;
        outputTable(loop, 0) = dTime;
        outputTable(loop, 1) = computeResponseSpectrum(dTime, designResponseSpectrum);

	}

    return true;

}

bool DesignResponseSpectrum::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
 //   // the input diolag
 //   SeismicLabGui::DlgDesignResponseSpectrumEdit* dlg = new SeismicLabGui::DlgDesignResponseSpectrumEdit(
 //       MeanSpeedIncrement, NumberOfBins, ShapeParameter, ScaleParameter,
 //       UserDefinedWeibullParameters, WeibulParametersEstimationMethod,
 //       Data.tableTool);
	//Gui::Control().showDialog(dlg);

    return true;
}

void DesignResponseSpectrum::onChanged(const App::Property* prop)
{
    if (prop == &DesignCode) {

        hideAllParameter();

        if (DesignCode.getValue() == 1)
        {
            showEurocode8Parameter();
        }
    }

    SeismicLabAPI::SeismicLabFeatureTableTool::onChanged(prop);
}

double DesignResponseSpectrum::computeResponseSpectrum(double time, SeismicLabTools::DesignResponseSpectrum designResponseSpectrum)
{
    double response_spectrum = 0.0;

    if (DesignCode.getValue() == 1)//Eurocode 8
    {
        if (SpacialComponent.getValue() == 1) //Horizontal
        {
            if (Elasticity.getValue() == 1)//Elastic
            {
                response_spectrum = designResponseSpectrum
                    .compute_Euro_EN1998_1_2004_Hori_Elastic_Response_Spectrum(
                    time, NationalAnnex.getValue(), DampingRatio.getValue(),
                    ReferencePeakGroundAcceleration.getValue(), SpectrumType.getValue(),
                    SoilType.getValue(), ImportanceClass.getValue());
            }
            else if (Elasticity.getValue() == 2)//Design
            {
                response_spectrum = designResponseSpectrum.compute_Euro_EN1998_1_2004_Hori_Design_Response_Spectrum(
                    time, NationalAnnex.getValue(), DampingRatio.getValue(),
                    ReferencePeakGroundAcceleration.getValue(), SpectrumType.getValue(),
                    SoilType.getValue(), ImportanceClass.getValue(), BehaviorFactor.getValue(), LowerBoundFactor.getValue());
            }
        }
        else if (SpacialComponent.getValue() == 2)//Vertical
        {
            if (Elasticity.getValue() == 1)//Elastic
            {
                response_spectrum = designResponseSpectrum.compute_Euro_EN1998_1_2004_Vert_Elastic_Response_Spectrum(
                    time, NationalAnnex.getValue(), DampingRatio.getValue(),
                    ReferencePeakGroundAcceleration.getValue(), SpectrumType.getValue(),
                    SoilType.getValue(), ImportanceClass.getValue());
            }
            else if (Elasticity.getValue() == 2)//Design
            {
                response_spectrum = designResponseSpectrum.compute_Euro_EN1998_1_2004_Vert_Design_Response_Spectrum(
                    time, NationalAnnex.getValue(), DampingRatio.getValue(),
                    ReferencePeakGroundAcceleration.getValue(), SpectrumType.getValue(),
                    SoilType.getValue(), ImportanceClass.getValue(), BehaviorFactor.getValue(),
                    LowerBoundFactor.getValue());
            }
        }
    }

    return response_spectrum;
}

void DesignResponseSpectrum::hideAllParameter()
{
    SpacialComponent.setStatus(App::Property::Status::Hidden, true);
    Elasticity.setStatus(App::Property::Status::Hidden, true);
    NationalAnnex.setStatus(App::Property::Status::Hidden, true);
    DampingRatio.setStatus(App::Property::Status::Hidden, true);
    ReferencePeakGroundAcceleration.setStatus(App::Property::Status::Hidden, true);
    SpectrumType.setStatus(App::Property::Status::Hidden, true);
    SoilType.setStatus(App::Property::Status::Hidden, true);
    ImportanceClass.setStatus(App::Property::Status::Hidden, true);
    BehaviorFactor.setStatus(App::Property::Status::Hidden, true);
    LowerBoundFactor.setStatus(App::Property::Status::Hidden, true);
}
void DesignResponseSpectrum::showEurocode8Parameter()
{
    SpacialComponent.setStatus(App::Property::Status::Hidden, false);
    Elasticity.setStatus(App::Property::Status::Hidden, false);
    NationalAnnex.setStatus(App::Property::Status::Hidden, false);
    DampingRatio.setStatus(App::Property::Status::Hidden, false);
    ReferencePeakGroundAcceleration.setStatus(App::Property::Status::Hidden, false);
    SpectrumType.setStatus(App::Property::Status::Hidden, false);
    SoilType.setStatus(App::Property::Status::Hidden, false);
    ImportanceClass.setStatus(App::Property::Status::Hidden, false);
    BehaviorFactor.setStatus(App::Property::Status::Hidden, false);
    LowerBoundFactor.setStatus(App::Property::Status::Hidden, false);
}