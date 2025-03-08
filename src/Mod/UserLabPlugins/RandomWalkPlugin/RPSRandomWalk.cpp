/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
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

#include "RPSRandomWalk.h"
#include <unsupported/Eigen/FFT>
#include "Widgets/DlgRandomWalk.h"
#include <Gui/Control.h>
#include <Base/Console.h>

#include <QMessageBox>
#include <QThread>
#include <fstream>
#include <Mod/GeneralTools/App/UniformRandomPhaseMatrixGenerator.h>
#include <Mod/UserLabAPI/App/RPSUserLabFramework.h>
#include <Base/Interpreter.h>
#include <App/Application.h>
// #include <nlohmann/json.hpp>

const double PI = 3.14159265358979323846;

using namespace UserLab;
using namespace UserLabAPI;

PROPERTY_SOURCE(UserLab::CRPSRandomWalk, UserLabAPI::UserLabFeatureSimulationMethod)

CRPSRandomWalk::CRPSRandomWalk()
{
    ADD_PROPERTY_TYPE(TotalSteps, (1000), "Parameters", App::Prop_None, "Number of total steps every walker shall take.");
    ADD_PROPERTY_TYPE(NumberOfWalker, (1), "Parameters", App::Prop_None, "Number of total walkers to be created.");
    ADD_PROPERTY_TYPE(MovePattern, (true), "Parameters", App::Prop_None, "Choose neighborhood movement pattern between Neumann (4 directions) or Moore (8 directions).");
    ADD_PROPERTY_TYPE(RandomStart, (true), "Parameters", App::Prop_None, " Do you want different (random) start points for each walker or let all walkers start at 0,0?.");
    Phenomenon.setValue("Random Walk");
    this->LinkToWiki.setValue("https://wiki.labrps.com/Plugin_UserLab_RandomWalk#Random_Walk");

}
//Initial setting
bool CRPSRandomWalk::OnInitialSetting(const UserLabAPI::UserLabSimulationData& Data)
{
    UserLabGui::DlgRandomWalkEdit* dlg = new UserLabGui::DlgRandomWalkEdit(TotalSteps, NumberOfWalker, MovePattern, RandomStart, Data.simulationMethod);
    Gui::Control().showDialog(dlg);
	return true;
}

const char* CRPSRandomWalk::GetPhenomenonName()
{
    return "Longitudinal Pavement Profile";
}

    // The simulation function 
bool CRPSRandomWalk::Simulate(const UserLabAPI::UserLabSimulationData& Data, cube &dPhenomenon)
{
    dPhenomenon.resize(1 + TotalSteps.getValue(), 2 * NumberOfWalker.getValue(), Data.numberOfSample.getValue());
    
    // load the 'RandomWalk' module
    Base::PyGILStateLocker lock;
    try {
         QString homePath = QString::fromStdString(App::Application::getHomePath());

		QString pluginLacotionPath = homePath + QString::fromLatin1("Plugins/UserLabWorkbench/RandomWalkPlugin");
         std::string cmd;
        cmd += "sys.path.append('" + pluginLacotionPath.toStdString() + "')";
        Base::Interpreter().runString("import sys");
        Base::Interpreter().runString(cmd.c_str());

        Py::Module module(PyImport_ImportModule("RandomWalk"), true);
        if (module.isNull()) {
            Base::Console().Error("The RandomWalk python module couldn't be loaded.\n");
            return false;
        }
        Py::Dict dict = module.getDict();
        Py::Callable call(dict.getItem("generateRandomWalk"));
        Py::Tuple args(5);
        args.setItem(0, Py::Int(TotalSteps.getValue()));
        args.setItem(1, Py::Int(NumberOfWalker.getValue()));
        args.setItem(2, Py::Boolean(MovePattern.getValue()));
        args.setItem(3, Py::Boolean(RandomStart.getValue()));
        args.setItem(4, Py::Int(Data.numberOfSample.getValue()));
        Py::Tuple res(call.apply(args));
        Py::List list(res.getItem(0));
        Py::List listSpeed(res.getItem(1));
        Py::List listMotionType(res.getItem(2));

        //// Create JsonObject for event
        //auto walks = utilities::JsonObject();
        //std::vector<utilities::JsonObject> x(TotalSteps.getValue() + 1);
        //std::vector<utilities::JsonObject> y(TotalSteps.getValue() + 1);
        //std::vector<utilities::JsonObject> geometry(2);
        //std::vector<utilities::JsonObject> walker(NumberOfWalker.getValue());

        //auto speed = utilities::JsonObject();
        //auto motion = utilities::JsonObject();

        //walks.add_value("numWalker", NumberOfWalker.getValue());
        //walks.add_value("numSteps", TotalSteps.getValue() + 1);
        //walks.add_value("numSample", Data.numberOfSample.getValue());

        for (int ss = 0; ss < Data.numberOfSample.getValue() && false == Data.isInterruptionRequested.getValue(); ss++) 
        {
            Py::List list2D(list[ss]);

            for (int i = 0; i < (2 * NumberOfWalker.getValue()) && false == Data.isInterruptionRequested.getValue(); i++) 
            {
                Py::List list2DColum(list2D[i]);

                 for (int j = 0; j < (1 + TotalSteps.getValue()) && false == Data.isInterruptionRequested.getValue(); j++) 
                 {
                    Py::Float value(list2DColum[j]);

                    dPhenomenon(j, i, ss) = value.as_double() * ScaleCoefficient.getValue();
                   /* 
                    x[j].add_value("x", dPhenomenon(j, i, ss));

                    if (i < (2 * NumberOfWalker.getValue()) - 1)
                    {
                        y[j].add_value("y", dPhenomenon(j, i + 1, ss));
                    }*/

                 }

                /* geometry[0].add_value("geometry", x);
                 geometry[1].add_value("geometry", y);
                 walker[2 * i].add_value("walker", geometry);*/
            }
        }



        for (int ss = 0; ss < Data.numberOfSample.getValue() && false == Data.isInterruptionRequested.getValue(); ss++) 
        {
            Py::List list2D(listSpeed[ss]);

            for (int i = 0; i < NumberOfWalker.getValue() && false == Data.isInterruptionRequested.getValue(); i++) 
            {
                Py::Float value(list2D[i]);

            }
        }

    }
    catch (Py::Exception& e) {
        e.clear();
        return false;
    }

return true;
}





