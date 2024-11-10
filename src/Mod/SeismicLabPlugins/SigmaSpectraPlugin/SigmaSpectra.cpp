
#include "SigmaSpectra.h"
#include <Mod/SeismicLabAPI/App/RPSSeismicLabFramework.h>
#include <Base/Console.h>
#include <Libraries/SigmaSpectra/MotionLibrary.h>
#include <QMessageBox>
#include <QThread>
#include <cmath>
#include <Eigen/Dense>
#include <Gui/Control.h>
#include <QDirIterator>

using namespace SeismicLab;
using namespace SeismicLabAPI;

PROPERTY_SOURCE(SeismicLab::SigmaSpectra, SeismicLabAPI::SeismicLabFeatureTableTool)

SigmaSpectra::SigmaSpectra()
{
    ADD_PROPERTY_TYPE(NumberOfDataPoints, (40), "Parameters", App::Prop_None, "The number of data points found in the file");
    ADD_PROPERTY_TYPE(TimeIncrement, (0.001), "Parameters", App::Prop_None, "The time increment read from the file");
    ADD_PROPERTY_TYPE(FilePath, ("file.AT2"), "Parameters", App::Prop_None, "The path to the file");
    ADD_PROPERTY_TYPE(PeakGroundAcceleration, (1.0), "Parameters", App::Prop_None, "The peak ground acceleration");
    ADD_PROPERTY_TYPE(PeakGroundVelocity, (1.0), "Parameters", App::Prop_None, "The peak ground velocity");
    ADD_PROPERTY_TYPE(PeackGroundDisplacement, (1.0), "Parameters", App::Prop_None, "The peak ground displacement");
    ADD_PROPERTY_TYPE(Details, (""), "Parameters", App::Prop_None, "Descriptor of the motion found in the file");
    ADD_PROPERTY_TYPE(ComponentDirectionAizmuth, (""), "Parameters", App::Prop_None, "Component direction aizmuth (3 digits), N, S, E, W, T, or L -- based on filename");
    ADD_PROPERTY_TYPE(AriasIntensity, (1.0), "Parameters", App::Prop_None, "Arias intensity");
    ADD_PROPERTY_TYPE(FiveToSeventyFiveAriasIntensityDuration, (1.0), "Parameters", App::Prop_None, "The time interval during which 5¨C75% of the energy from an earthquake is dissipated");
    ADD_PROPERTY_TYPE(FiveToNinetyFiveAriasIntensityDuration, (1.0), "Parameters", App::Prop_None, "The time interval during which 5¨C95% of the energy from an earthquake is dissipated");
}


bool SigmaSpectra::TableToolCompute(const SeismicLabAPI::SeismicLabSimulationData& Data, const mat& inputTable, mat& outputTable)
{
    QFileInfo info(FilePath.getValue());
    //info.absoluteFilePath();// returns "c:/my/path/to/dir/file.txt"
    //info.dir();             // returns "c:/my/path/to/dir"
    //info.filename(); 
    //QString dir = info.dir().absolutePath();
    MotionLibrary* motionLibrary = new MotionLibrary();
    motionLibrary->setFileName(FilePath.getValue());
    motionLibrary->compute();
    Motion* motion = static_cast<Motion*>(motionLibrary->motions()[0]);
    
    // Get the time increment from the file
    TimeIncrement.setValue(motion->dtime());
    PeakGroundAcceleration.setValue(motion->pga() * 9806.65);//  times 9806.65 to convert g to mm/s^2
    PeakGroundVelocity.setValue(motion->pgv());
    PeackGroundDisplacement.setValue(motion->pgd());
    NumberOfDataPoints.setValue(motion->time().size());
    Details.setValue(motion->details().toStdString());
    ComponentDirectionAizmuth.setValue(motion->component().toStdString());
    AriasIntensity.setValue(motion->AI());
    FiveToSeventyFiveAriasIntensityDuration.setValue(motion->dur5_75());
    FiveToNinetyFiveAriasIntensityDuration.setValue(motion->dur5_95());

    int rows = min(NumberOfDataPoints.getValue(), inputTable.rows());
    int cols = min(4, inputTable.cols());

    for (int loop = 0; loop < rows && !Data.isInterruptionRequested.getValue(); loop++)
	{
        if (cols >= 1)
        outputTable(loop, 0) = motion->time()[loop];
        if (cols >= 2)
        outputTable(loop, 1) = motion->acc()[loop];
        if (cols >= 3)
        outputTable(loop, 2) = motion->vel()[loop];
        if (cols >= 4)
        outputTable(loop, 3) = motion->disp()[loop];

	}

    QString dd = motion->details();

   if (inputTable.cols() < 4 || inputTable.rows() < NumberOfDataPoints.getValue())
   {
       Base::Console().Warning("The entire result data couldn't be reported. Please make sure the number of columns of the active table(input) is 4 at least and its number of rows is %d at least.\n", NumberOfDataPoints.getValue());
   }
    return true;
}

bool SigmaSpectra::OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data)
{
    return true;
}

void SigmaSpectra::onChanged(const App::Property* prop)
{
   SeismicLabAPI::SeismicLabFeatureTableTool::onChanged(prop);
}
