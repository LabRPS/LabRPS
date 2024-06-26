/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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


#include "PreCompiled.h"

#ifndef _PreComp_
# include <qobject.h>
#endif

#include "Workbench.h"
#include <Gui/MenuManager.h>
#include <Gui/ToolBarManager.h>
#include <Mod/WindLabAPI/App/RPSWindLabAPI.h>
#include <Mod/WindLab/App/WindLabUtils.h>
#include <Mod/WindLab/App/WindLabSimulation.h>
#include <Mod/WindLab/Gui/WindLabSimulationObserver.h>
#include <Mod/WindLabAPI/App/RPSWindLabFramework.h>
#include <Mod/WindLab/Gui/ViewProviderWindLabFeatureLocationDistribution.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/MainWindow.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Mod/WindLabAPI/App/RPSWindLabpluginAPI.h>
#include <App/RPSpluginManager.h>

#define GLWAVE 4558

using namespace WindLabGui;
using namespace WindLabAPI;

//color relates stuff
typedef struct {
    double r;// percent
    double g;// percent
    double b;// percent
} rgb;

typedef struct {
    double h;// angle in degrees
    double s;// percent
    double v;// percent
} hsv;

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);


hsv rgb2hsv(rgb in)
{
    hsv out;
    double min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min < in.b ? min : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max > in.b ? max : in.b;

    out.v = max;// v
    delta = max - min;
    if (max > 0.0) {
        out.s = (delta / max);// s
    }
    else {
        // r = g = b = 0                        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;// its now undefined
        return out;
    }
    if (in.r >= max)                  // > is bogus, just keeps compilor happy
        out.h = (in.g - in.b) / delta;// between yellow & magenta
    else if (in.g >= max)
        out.h = 2.0 + (in.b - in.r) / delta;// between cyan & yellow
    else
        out.h = 4.0 + (in.r - in.g) / delta;// between magenta & cyan

    out.h *= 60.0;// degrees

    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}

rgb hsv2rgb(hsv in)
{
    double hh, p, q, t, ff;
    long i;
    rgb out;

    if (in.s <= 0.0) {// < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
    }
    return out;
}

#if 0 // needed for Qt's lupdate utility
    qApp->translate("CommandGroup", "WindLab");

#endif

/// @namespace WindLabGui @class Workbench
TYPESYSTEM_SOURCE(WindLabGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
    ParameterGrp::handle hGrp;

    hGrp = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Plugins");
    hGrp->SetASCII("Installed Plugins", "Plugin 1");

    WLReadAllTobeInstallObjVersionToRegistry();
    WLReadAllTobeInstallObjPublicationTitleToRegistry();
    WLReadAllTobeInstallObjPublicationLinkToRegistry();
    WLReadAllTobeInstallObjPublicationAuthorToRegistry();
    WLReadAllTobeInstallObjPublicationDateToRegistry();

    // read install windLab from registry if any
    WLReadAllTobeInstallObjectsFromRegistry();
    WLClearAllTobeInstallObjectsFromRegistry();

    IntallRegistryPlugins();
}

Workbench::~Workbench()
{
    RPSWriteInstalledPluginsToRegistry();

    WLWriteAllTobeInstallObjPublicationTitleToRegistry();
    WLWriteAllTobeInstallObjPublicationLinkToRegistry();
    WLWriteAllTobeInstallObjPublicationAuthorToRegistry();
    WLWriteAllTobeInstallObjPublicationDateToRegistry();
    WLWriteAllTobeInstallObjVersionToRegistry();

    WLWriteAllTobeInstallObjectsToRegistry();

}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows");

    Gui::MenuItem* windLab = new Gui::MenuItem;
    root->insertItem(item, windLab);
    windLab->setCommand("&WindLab");
    *windLab << "WindLab_NewSimulation"
             << "WindLab_Features"
             << "WindLab_Comparison"
             << "WindLab_Examples";
    

    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

     Gui::ToolBarItem* WindLabToolBar = new Gui::ToolBarItem(root);
    WindLabToolBar->setCommand("WindLab Features");
     *WindLabToolBar << "WindLab_NewSimulation"
                     << "WindLab_Features"
                     << "WindLab_Comparison"
                     << "WindLab_Examples";

     Gui::ToolBarItem* GraphTools = new Gui::ToolBarItem(root);
    GraphTools->setCommand("Graph Tools");
    *GraphTools << "Std_DisableTools"
                << "Std_DataReader"
                << "Std_ScreenReader"
                << "Std_SelectDataRange"
                << "Std_MoveDataPoints"
                << "Std_RemoveBadDataPoints"
                << "Separator"
                << "Std_DragRange"
                << "Std_ZoomRang"
                << "Std_RescaleToShowAll";

    Gui::ToolBarItem* TableTools = new Gui::ToolBarItem(root);
    TableTools->setCommand("Alphaplot Table Tools");
    *TableTools << "Std_StdScatters"
                << "Std_LinesAndSteps"
                << "Std_VerticalAndHorizontalBars"
                << "Std_Area"
                << "Std_ChannelFill"
                << "Std_Histogram"
                << "Std_BoxPlot"
                << "Std_VectorPlots"
                << "Std_PiePlots"
                << "Separator"
                << "Std_3DPlotBar"
                << "Std_3DPlotScatter";
    // 3D Plot
    Gui::ToolBarItem* TreeDPlot = new Gui::ToolBarItem(root);
    TreeDPlot->setCommand("3D Plot");
    *TreeDPlot << "Std_3DWireFrame"
               << "Std_3DSurface"
               << "Std_3DWireFrameSurface"
               << "Separator"
               << "Std_3DPlotBar"
               << "Std_3DPlotScatter"
               << "Separator"
               << "Std_ContourAndColourFill"
               << "Std_ContourLines"
               << "Std_GrayScaleMap";

     // 3D Plot Tools
    Gui::ToolBarItem* TreeDPlotT = new Gui::ToolBarItem(root);
    TreeDPlotT->setCommand("3D Plot Tools");
    *TreeDPlotT << "Std_PlotPlot3dModecolumnSelect"
                << "Std_PlotPlot3dModeRowSelect"
                << "Std_PlotPlot3dModeItemSelect"
                << "Std_PlotPlot3dAnimate";

    // Table statistics
    Gui::ToolBarItem* TableStatistics = new Gui::ToolBarItem(root);
    TableStatistics->setCommand("Table Statistics");
    *TableStatistics << "Std_AppendNewColumnToTable"
                     << "Std_ShowColumnStatistics"
                     << "Std_ShowRowStatistics";

     return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // WindLab tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}


void WindLabGui::Workbench::draw()
{
    ////get the active simulation
    //WindLab::WindLabSimulation* sim = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    //if (!sim || !sim->getSimulationData())
    //    return;

    ////get the active simulation data
    //WindLabAPI::WindLabSimuData* simData = sim->getSimulationData();
    //if (simData == nullptr)
    //    return;

    //  //get the number of simution point for the active simulation
    //int nberOfSimPoint = sim->getSimulationData()->numberOfSpatialPosition.getValue();

    ////allocate memory for an array that will be used to store the computed location coordinates
    //mat dLocCoord(nberOfSimPoint, 4);

    ////get the active document
    //auto doc = App::GetApplication().getActiveDocument();
    //if (!doc) {
    //    return;
    //}

    ////get the active location distribution feature
    //WindLabAPI::IrpsWLLocationDistribution* SelectedDistrObject =
    //    static_cast<WindLabAPI::IrpsWLLocationDistribution*>(
    //        doc->getObject(simData->spatialDistribution.getValue()));

    //if (!SelectedDistrObject) {
    //    return;
    //}

    ////get the corresponding view provider
    //WindLabGui::ViewProviderWindLabFeatureLocationDistribution* vp =
    //    dynamic_cast<WindLabGui::ViewProviderWindLabFeatureLocationDistribution*>(
    //        Gui::Application::Instance->getViewProvider(SelectedDistrObject));

    //if (!vp) {
    //    return;
    //}

    ////get the feature view visibility
    //bool visibiliy = vp->Visibility.getValue();
    //if (!visibiliy)
    //    return;

    ////compute the location coordinates of the corresponding feature
    //WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(*simData, dLocCoord);

    ////double lineWidth = vp->LineWidth.getValue();
    //double pointSize = vp->PointSize.getValue();
    ////const App::Color& lineC = vp->LineColor.getValue();
    //const App::Color& pointC = vp->PointColor.getValue();
    //bool showGround = vp->ShowGround.getValue();
    //double length = vp->GroundLength.getValue();
    //double width = vp->GroundWidth.getValue();
    //double groundOpacity = vp->GroundOpacity.getValue();
    //const App::Color& groundC = vp->GroundColor.getValue();
    //QColor groundColor(groundC.r * 255, groundC.g * 255, groundC.b * 255);
    //bool showGrid = vp->ShowGrid.getValue();
    //bool showAxis = vp->ShowAxis.getValue();
    //double axisScale = vp->AxisScale.getValue();
    //bool showPointNumbering = vp->ShowPointNumbering.getValue();
    //double NumberingOffsetX = vp->NumberingOffsetX.getValue();
    //double NumberingOffsetY = vp->NumberingOffsetY.getValue();
    //double NumberingOffsetZ = vp->NumberingOffsetZ.getValue();

    //float x;
    //float y;
    //float z;
    //float max = 1 /*dLocCoord.maxCoeff()*/;
    //glPointSize(pointSize);
    //glClear(GL_COLOR_BUFFER_BIT);

    //glBegin(GL_POINTS);
    //for (int i = 0; i < nberOfSimPoint; i++) {
    //    x = dLocCoord(i, 1) / max;
    //    y = dLocCoord(i, 2) / max;
    //    z = dLocCoord(i, 3) / max;

    //    glColor3f(pointC.r, pointC.g, pointC.b);
    //    glVertex3f(x, y, z);
    //}
    //glEnd();
    //glDisable(GL_LIGHTING);

    ////draw the ground
    //if (showGround) {

    //    glBegin(GL_POLYGON);

    //    glColor4d(groundColor.redF(), groundColor.greenF(), groundColor.blueF(), groundOpacity);

    //    Base::Vector3d A(-length / 2, -width / 2, 0.0);
    //    Base::Vector3d B(length / 2, -width / 2, 0.0);
    //    Base::Vector3d C(length / 2, width / 2, 0.0);
    //    Base::Vector3d D(-length / 2, width / 2, 0.0);

    //    glNormal3d(0, 0, 1);

    //    glVertex3d(A.x, A.y, A.z);
    //    glVertex3d(B.x, B.y, B.z);
    //    glVertex3d(C.x, C.y, C.z);
    //    glVertex3d(D.x, D.y, D.z);
    //    glVertex3d(A.x, A.y, A.z);

    //    glEnd();



    //    width = 400;
    //    length = 400;
    //    int z, y;
    //    double discW = 50;
    //    double discL = 50;
    //    Base::Vector3d centerPos(0, 0, 0);
    //    QVector<QVector<Base::Vector3d>> points, normals;
    //    double GlList = GLWAVE;
    //    double Hs = 8.1;
    //    double opacity = groundOpacity;

    //    for (z = 0; z <= discW; ++z)
    //    {
    //        QVector<Base::Vector3d> line;
    //        for (y = 0; y <= discL; ++y)
    //        {
    //            line.append(Base::Vector3d(0, 0, 0));
    //        }
    //        points.append(line);
    //        normals.append(line);
    //    }
    //    
    //     if (showAxis)
    //    {
    //         #pragma omp parallel default (none) shared (centerPos, points, time, width, length, discW, discL)
    //    {
    //        #pragma omp for
    //        for (int z = 0; z <= discW; ++z)
    //        {
    //            for (int y = 0; y <= discL; ++y)
    //            {
    //                double dd = double(rand()) / double(RAND_MAX) * 2.0 * 3.14;

    //                Base::Vector3d position = Base::Vector3d(centerPos.x + (y * length/discL - length/2.0), centerPos.y + (z * width/discW - width/2.0),0);
    //                points[z][y] = (position + Base::Vector3d(0,0,1)*(double(rand()) / double(RAND_MAX) * 2.0 * 3.14));;
    //            }
    //        }
    //    }
    //    }
    //    

    //    rgb water;
    //    water.r = 255;
    //    water.g = 255;
    //    water.b = 255;

    //    hsv hs = rgb2hsv(water);

    //    //glNewList(GlList, GL_COMPILE);

    //     for (int z = 0; z < points.size()-1; ++z)
    //        {
    //            for (int y = 0; y < points.at(z).size()-1; ++y)
    //            {

    //                Base::Vector3d A, B, C;
    //                A = points.at(z).at(y);
    //                B = points.at(z+1).at(y);
    //                C = points.at(z).at(y+1);

    //                Base::Vector3d normal = (C - A) & (B - A);
    //                normal.Normalize();

    //                normals[z][y] += normal/3.0;
    //                normals[z+1][y] += normal/3.0;
    //                normals[z][y+1] += normal/3.0;

    //            }
    //        }

    //        for (int z = 0; z < points.size(); ++z)
    //        {
    //            for (int y = 0; y < points.at(z).size(); ++y)
    //            {
    //                normals[z][y].Normalize();
    //            }
    //        }

    //        glEnable(GL_POINT_SMOOTH);
    //        glEnable(GL_LINE_SMOOTH);
    //        glEnable (GL_BLEND);
    //        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //        glEnable(GL_DEPTH_TEST);

    //        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //        glEnable(GL_POLYGON_OFFSET_FILL);  // polygons get a reduced Z-value. Now the grid is drawn onto the WindField surface
    //        glPolygonOffset(1.0, 0);

    //        for (z = 0; z < points.size() - 1; ++z) {
    //            glBegin(GL_TRIANGLE_STRIP);  // the surface
    //            glEnable(GL_POLYGON_OFFSET_FILL);  // polygons get a reduced Z-value. Now the grid is drawn onto the WindField surface
    //            glPolygonOffset(1.0, 0);
    //            for (y = 0; y < points.at(z).size(); ++y) {

    //                if (Hs > 0) hs.v = 2./3. + points.at(z).at(y).z / Hs / 3.0;

    //                glColor4f (hsv2rgb(hs).r, hsv2rgb(hs).g, hsv2rgb(hs).b,opacity);
    //                glNormal3f(normals.at(z).at(y).x, normals.at(z).at(y).y, normals.at(z).at(y).z);
    //                glVertex3f (points.at(z).at(y).x, points.at(z).at(y).y, points.at(z).at(y).z);

    //                if (Hs > 0) hs.v = 2./3. + points.at(z+1).at(y).z / Hs / 3.0;

    //                glColor4f (hsv2rgb(hs).r, hsv2rgb(hs).g, hsv2rgb(hs).b,opacity);
    //                glNormal3f(normals.at(z+1).at(y).x, normals.at(z+1).at(y).y, normals.at(z+1).at(y).z);
    //                glVertex3f (points.at(z+1).at(y).x, points.at(z+1).at(y).y, points.at(z+1).at(y).z);
    //            }
    //            glEnd();
    //        }

    //}

    //Gui::MDIView* view = Gui::getMainWindow()->activeWindow();
    //if (!view)
    //    return;
    //Gui::View3DInventorViewer* viewer = static_cast<Gui::View3DInventor*>(view)->getViewer();
    //if (!viewer)
    //    return;
    //if (view && view->isDerivedFrom(Gui::View3DInventor::getClassTypeId())) {
    //    Gui::View3DInventorViewer* viewer =
    //        static_cast<Gui::View3DInventor*>(view)->getViewer();
    //    viewer->setGridIsDrawn(showGrid);
    //    viewer->setAxisIsDrawn(showAxis);

    //    //if (showAxis) {
    //    //    viewer->drawAxis(axisScale);
    //    //}
    //}

    //if (showPointNumbering) {
    //    QFont font(QString::fromLatin1(vp->FontName.getValue()), (int)vp->FontSize.getValue());
    //    viewer->setOverpaintFont(font);

    //    for (int i = 0; i < nberOfSimPoint; i++) {
    //        x = dLocCoord(i, 1) / max;
    //        y = dLocCoord(i, 2) / max;
    //        z = dLocCoord(i, 3) / max;
    //        viewer->overpaintText(x + NumberingOffsetX, y + NumberingOffsetY, z + NumberingOffsetZ,
    //                              QString::number(dLocCoord(i, 0)));
    //    }
    //}
}
Base::Vector3d Workbench::getSceneCenter()
{
    //get the active simulation
    WindLab::WindLabSimulation* sim =
        static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (sim == nullptr)
        return Base::Vector3d(0, 0, 0);

    int nberOfSimPoint = sim->getSimulationData()->numberOfSpatialPosition.getValue();
    mat dLocCoord(nberOfSimPoint, 4);
    WindLabAPI::WindLabSimuData* simData = sim->getSimulationData();
    if (simData == nullptr)
        return Base::Vector3d(0, 0, 0);

    WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(*simData, dLocCoord);

    double x;
    double y;
    double z;
    float max = 1 /*dLocCoord.maxCoeff()*/;
    double min_x = 0.0;
    double min_y = 0.0;
    double min_z = 0.0;
    double max_x = 0.0;
    double max_y = 0.0;
    double max_z = 0.0;

    for (int i = 0; i < nberOfSimPoint; i++) {
        x = dLocCoord(i, 1) / max;
        y = dLocCoord(i, 2) / max;
        z = dLocCoord(i, 3) / max;

        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y);
        max_y = std::max(max_y, y);
        min_z = std::min(min_z, z);
        max_z = std::max(max_z, z);
    }

    Base::Vector3d sphereCentre((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2);
    return sphereCentre;
}
double Workbench::getSceneRadius()
{
    double sphereRadius = 0.0;

    //get the active simulation
    WindLab::WindLabSimulation* sim =
        static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->active());
    if (sim == nullptr)
        return sphereRadius;
    int nberOfSimPoint = sim->getSimulationData()->numberOfSpatialPosition.getValue();
    mat dLocCoord(nberOfSimPoint, 4);
    WindLabAPI::WindLabSimuData* simData = sim->getSimulationData();
    if (simData == nullptr)
        return sphereRadius;
    WindLabAPI::CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(*simData, dLocCoord);

    double x;
    double y;
    double z;
    float max = 1 /*dLocCoord.maxCoeff()*/;
    double max_x = 0.0;
    double max_y = 0.0;
    double max_z = 0.0;

    for (int i = 0; i < nberOfSimPoint; i++) {
        x = dLocCoord(i, 1) / max;
        y = dLocCoord(i, 2) / max;
        z = dLocCoord(i, 3) / max;

        max_x = std::max(max_x, x);
        max_y = std::max(max_y, y);
        max_z = std::max(max_z, z);
    }

    sphereRadius = std::sqrt(max_x * max_x + max_y * max_y + max_z * max_z);
    return sphereRadius;
}



//--------------------------------------------------------------------------------------------------
//plugins and features storing staff
//---------------------------------------------------------------------------------


bool WindLabGui::Workbench::getToBeInstalledObjectsList(QStringList& lstObject, QString pluginName) const
{
    lstObject.clear();

    try
    {
        WindLab::WindLabUtils::getObjects(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);

       WindLab::WindLabUtils::getObjects(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsGustFactorFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsRoughnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject, pluginName);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool WindLabGui::Workbench::getToBeUninstalledObjectsList(QStringList& lstObject, QString pluginName) const
{
    lstObject.clear();
    try
    {
       WindLab::WindLabUtils::getObjects(CrpsSimuMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsXSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsYSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsZSpectrumFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsCoherenceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsRandomnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsModulationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsMeanFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsTableToolFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsMatrixToolFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), lstObject, pluginName);

       WindLab::WindLabUtils::getObjects(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsGustFactorFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsKurtosisFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsPeakFactorFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsRoughnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsSkewnessFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsTurbulenceScaleFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsVarianceFactory::GetOjectAndPluginMap(), lstObject, pluginName);
       WindLab::WindLabUtils::getObjects(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), lstObject, pluginName);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool WindLabGui::Workbench::updateToBeInstalledObjectsMap(const QString& lstObject) const
{
    try
    {
       WindLab::WindLabUtils::updateObjectsMap(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsModulationFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsMeanFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(), lstObject);

       WindLab::WindLabUtils::updateObjectsMap(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsGustFactorFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsRoughnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), lstObject);
       WindLab::WindLabUtils::updateObjectsMap(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), lstObject);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool WindLabGui::Workbench::updateToBeUninstalledObjectsMap(const QString name, const QString pluginName) const
{
    try
    {
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);
       WindLab::WindLabUtils::updateObjectToSkipMap(CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap(), name, pluginName);

    }
    catch (const std::exception& e)
    {
        return false;
    }

    return true;
}

bool WindLabGui::Workbench::isObjectInstalled(QString& object) const
{
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsSimuMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsLocationDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsXSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsYSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsZSpectrumFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsCoherenceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsPSDdecomMethodFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsFrequencyDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsRandomnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsModulationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsMeanFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsTableToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsMatrixToolFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsUserDefinedRPSObjectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsCumulativeProbabilityDistributionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsGustFactorFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsKurtosisFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsPeakFactorFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsProbabilityDensityFunctionFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsRoughnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsShearVelocityOfFlowFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsSkewnessFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsStandardDeviationFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsTurbulenceIntensityFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsTurbulenceScaleFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsVarianceFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }
    if (WindLab::WindLabUtils::isThisObjectInstalled(CrpsWavePassageEffectFactory::GetOjectDescriptionMap(), object))
    {
        return true;
    }

    return false;
}

void WindLabGui::Workbench::emptyAllToBeUninstalledObjectsMap() const
{
    try
    {
        CrpsSimuMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsLocationDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsXSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsYSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsZSpectrumFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsCoherenceFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsPSDdecomMethodFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsFrequencyDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsRandomnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsModulationFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsMeanFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTableToolFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsMatrixToolFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsUserDefinedRPSObjectFactory::GetOjectsSkipDuringUnintallationMap().clear();

        CrpsCumulativeProbabilityDistributionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsGustFactorFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsKurtosisFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsPeakFactorFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsProbabilityDensityFunctionFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsRoughnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsShearVelocityOfFlowFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsSkewnessFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsStandardDeviationFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTurbulenceIntensityFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsTurbulenceScaleFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsVarianceFactory::GetOjectsSkipDuringUnintallationMap().clear();
        CrpsWavePassageEffectFactory::GetOjectsSkipDuringUnintallationMap().clear();



    }
    catch (const std::exception& e)
    {

    }
}

bool WindLabGui::Workbench::isThisPluginInstalled(const QString& pluginName) const
{
    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSimuMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsXSpectrumFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsYSpectrumFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsZSpectrumFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCoherenceFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsRandomnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsModulationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCorrelationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsMeanFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsTableToolFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsMatrixToolFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsGustFactorFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsKurtosisFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsPeakFactorFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsRoughnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsSkewnessFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsTurbulenceScaleFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsVarianceFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    if (WindLab::WindLabUtils::isThisObjectGroupPluggedInThisPlugin(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), pluginName)) { return true; }

    return false;
}

QString WindLabGui::Workbench::getPhenomenonName() const
{
    return WindLab::WindLabUtils::rpsPhenomenonWindVelocity;
}

void WindLabGui::Workbench::WLReadAllTobeInstallObjectsFromRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethod"), count = 1;
    ReadMapFromRegistry2(CrpsSimuMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLoc"), count = 1;
    ReadMapFromRegistry2(CrpsLocationDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSD"), count = 1;
    ReadMapFromRegistry2(CrpsXSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSD"), count = 1;
    ReadMapFromRegistry2(CrpsYSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSD"), count = 1;
    ReadMapFromRegistry2(CrpsZSpectrumFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCoh"), count = 1;
    ReadMapFromRegistry2(CrpsCoherenceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecomp"), count = 1;
    ReadMapFromRegistry2(CrpsPSDdecomMethodFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("WLFreq"), count = 1;
    ReadMapFromRegistry2(CrpsFrequencyDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRand"), count = 1;
    ReadMapFromRegistry2(CrpsRandomnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMod"), count = 1;
    ReadMapFromRegistry2(CrpsModulationFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorr"), count = 1;
    ReadMapFromRegistry2(CrpsCorrelationFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("WLMean"), count = 1;
    ReadMapFromRegistry2(CrpsMeanFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableTool"), count = 1;
    ReadMapFromRegistry2(CrpsTableToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixTool"), count = 1;
    ReadMapFromRegistry2(CrpsMatrixToolFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObj"), count = 1;
    ReadMapFromRegistry2(CrpsUserDefinedRPSObjectFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistribution"), count = 1;
    ReadMapFromRegistry2(CrpsCumulativeProbabilityDistributionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLGustFactor"), count = 1;
    ReadMapFromRegistry2(CrpsGustFactorFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosis"), count = 1;
    ReadMapFromRegistry2(CrpsKurtosisFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactor"), count = 1;
    ReadMapFromRegistry2(CrpsPeakFactorFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunction"), count = 1;
    ReadMapFromRegistry2(CrpsProbabilityDensityFunctionFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughness"), count = 1;
    ReadMapFromRegistry2(CrpsRoughnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlow"), count = 1;
    ReadMapFromRegistry2(CrpsShearVelocityOfFlowFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewness"), count = 1;
    ReadMapFromRegistry2(CrpsSkewnessFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviation"), count = 1;
    ReadMapFromRegistry2(CrpsStandardDeviationFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensity"), count = 1;
    ReadMapFromRegistry2(CrpsTurbulenceIntensityFactory::GetTobeInstalledObjectsMap(),
                         settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScale"), count = 1;
    ReadMapFromRegistry2(CrpsTurbulenceScaleFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);

    settingsGroup = QString::fromLatin1("WLVariance"), count = 1;
    ReadMapFromRegistry2(CrpsVarianceFactory::GetTobeInstalledObjectsMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffect"), count = 1;
    ReadMapFromRegistry2(CrpsWavePassageEffectFactory::GetTobeInstalledObjectsMap(), settingsGroup,
                         count);
}

void WindLabGui::Workbench::WLWriteAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodTitle"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocTitle"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDTitle"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohTitle"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompTitle"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqTitle"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandTitle"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModTitle"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrTitle"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanTitle"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolTitle"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolTitle"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjTitle"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionTitle"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLGustFactorTitle"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisTitle"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorTitle"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionTitle"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessTitle"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowTitle"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessTitle"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationTitle"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityTitle"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleTitle"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceTitle"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectTitle"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLReadAllTobeInstallObjPublicationTitleToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodTitle"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocTitle"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDTitle"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohTitle"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompTitle"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqTitle"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandTitle"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModTitle"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrTitle"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanTitle"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolTitle"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjTitle"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionTitle"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetTitleMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("WLGustFactorTitle"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisTitle"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorTitle"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionTitle"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessTitle"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowTitle"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessTitle"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationTitle"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityTitle"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleTitle"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceTitle"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetTitleMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectTitle"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetTitleMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLWriteAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodLink"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocLink"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDLink"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDLink"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDLink"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohLink"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompLink"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqLink"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandLink"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModLink"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrLink"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanLink"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolLink"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolLink"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjLink"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionLink"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLGustFactorLink"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisLink"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorLink"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionLink"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessLink"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowLink"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessLink"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationLink"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityLink"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleLink"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceLink"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectLink"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLReadAllTobeInstallObjPublicationLinkToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodLink"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocLink"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDLink"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohLink"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompLink"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqLink"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandLink"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModLink"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrLink"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanLink"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolLink"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolLink"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjLink"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionLink"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetLinkMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("WLGustFactorLink"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisLink"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorLink"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionLink"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessLink"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowLink"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessLink"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationLink"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityLink"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleLink"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceLink"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetLinkMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectLink"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetLinkMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLWriteAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodAuthor"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocAuthor"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDAuthor"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohAuthor"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompAuthor"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqAuthor"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandAuthor"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModAuthor"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrAuthor"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanAuthor"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolAuthor"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjAuthor"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionAuthor"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLGustFactorAuthor"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisAuthor"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorAuthor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionAuthor"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessAuthor"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowAuthor"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessAuthor"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationAuthor"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityAuthor"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleAuthor"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceAuthor"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectAuthor"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLReadAllTobeInstallObjPublicationAuthorToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocAuthor"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDAuthor"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqAuthor"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandAuthor"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModAuthor"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolAuthor"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjAuthor"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetAuthorMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("WLGustFactorAuthor"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisAuthor"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorAuthor"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionAuthor"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetAuthorMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("WLRoughnessAuthor"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowAuthor"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessAuthor"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationAuthor"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleAuthor"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceAuthor"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetAuthorMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectAuthor"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetAuthorMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLWriteAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodDate"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocDate"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDDate"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDDate"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDDate"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohDate"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompDate"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqDate"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandDate"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModDate"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrDate"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanDate"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolDate"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolDate"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjDate"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionDate"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLGustFactorDate"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisDate"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorDate"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionDate"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessDate"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowDate"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessDate"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationDate"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityDate"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleDate"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceDate"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectDate"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLReadAllTobeInstallObjPublicationDateToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodDate"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocDate"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDDate"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohDate"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompDate"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqDate"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandDate"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModDate"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrDate"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanDate"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolDate"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolDate"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjDate"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionDate"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetDateMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("WLGustFactorDate"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisDate"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorDate"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionDate"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRoughnessDate"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowDate"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessDate"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationDate"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityDate"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleDate"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceDate"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetDateMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectDate"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetDateMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WriteMapToRegistry(std::map<const std::string, std::string>& map,
                                              QString& settingsGroup, int& count)
{

    if (map.empty()) {
        return;
    }

    QStringList mapkeylst;
    QStringList mapvaluelst;

    // Iterate though the map
    for (auto it1 = map.begin(); it1 != map.end(); ++it1) {
        mapkeylst.append(QLatin1String(it1->first.c_str()));
        mapvaluelst.append(QLatin1String(it1->second.c_str()));
    }

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue(QLatin1String("mapkey"), mapkeylst);
    settings.setValue(QLatin1String("mapValue"), mapvaluelst);
    settings.endGroup();

    count++;
}

void WindLabGui::Workbench::ReadMapFromRegistry(std::map<const const std::string, std::string>& map,
                                               QString& settingsGroup, int& count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value(QLatin1String("mapkey")).toStringList();
    QStringList mapvaluelst = settings.value(QLatin1String("mapValue")).toStringList();
    settings.endGroup();

    if (mapkeylst.isEmpty()) {
        return;
    }

    for (int i = 0; i < mapkeylst.size(); ++i) {
        std::string key = mapkeylst.at(i).toUtf8().constData();
        std::string value = mapvaluelst.at(i).toUtf8().constData();

        map[key] = value;
    }

    count++;
}

void WindLabGui::Workbench::WriteMapToRegistry2(std::map<const const std::string, std::string>& map,
                                               QString& settingsGroup, int& count)
{

    if (map.empty()) {
        return;
    }

    QStringList mapkeylst;
    QStringList mapvaluelst;

    // Iterate though the map
    for (auto it1 = map.begin(); it1 != map.end(); ++it1) {
        mapkeylst.append(QString::fromUtf8(it1->first.c_str()));
        mapvaluelst.append(QString::fromUtf8(it1->second.c_str()));
    }

    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.setValue(QString::fromLatin1("mapkey"), mapkeylst);
    settings.setValue(QString::fromLatin1("mapValue"), mapvaluelst);
    settings.endGroup();

    count++;
}

void WindLabGui::Workbench::ReadMapFromRegistry2(
    std::map<const const std::string, std::string>& map,
                                                QString& settingsGroup, int& count)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    QStringList mapkeylst = settings.value(QString::fromLatin1("mapkey")).toStringList();
    QStringList mapvaluelst = settings.value(QString::fromLatin1("mapValue")).toStringList();
    settings.endGroup();

    if (mapkeylst.isEmpty()) {
        return;
    }

    for (int i = 0; i < mapkeylst.size(); ++i) {
        std::string key = mapkeylst.at(i).toUtf8().constData();
        std::string value = mapvaluelst.at(i).toUtf8().constData();

        map[key] = value;
        App::PluginManager::GetInstance().GetAllPlugedObjectsMap()[mapkeylst.at(i)] = mapvaluelst.at(i);
    }

    count++;
}

void WindLabGui::Workbench::WLWriteAllTobeInstallObjectsToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethod"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLoc"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLXPSD"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSD"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSD"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCoh"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecomp"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreq"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLRand"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMod"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorr"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMean"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableTool"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixTool"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObj"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistribution"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetOjectAndPluginMap(),
                       settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLGustFactor"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosis"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactor"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunction"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLRoughness"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlow"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLSkewness"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviation"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensity"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetOjectAndPluginMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScale"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVariance"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetOjectAndPluginMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffect"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetOjectAndPluginMap(), settingsGroup, count);
}


void WindLabGui::Workbench::WLWriteAllTobeInstallObjVersionToRegistry()
{
    int count = 1;
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethodVersion"), count = 1;
    WriteMapToRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocVersion"), count = 1;
    WriteMapToRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsXSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsYSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDVersion"), count = 1;
    WriteMapToRegistry(CrpsZSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohVersion"), count = 1;
    WriteMapToRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompVersion"), count = 1;
    WriteMapToRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqVersion"), count = 1;
    WriteMapToRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandVersion"), count = 1;
    WriteMapToRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModVersion"), count = 1;
    WriteMapToRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrVersion"), count = 1;
    WriteMapToRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanVersion"), count = 1;
    WriteMapToRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolVersion"), count = 1;
    WriteMapToRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolVersion"), count = 1;
    WriteMapToRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjVersion"), count = 1;
    WriteMapToRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionVersion"), count = 1;
    WriteMapToRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLGustFactorVersion"), count = 1;
    WriteMapToRegistry(CrpsGustFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisVersion"), count = 1;
    WriteMapToRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorVersion"), count = 1;
    WriteMapToRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionVersion"), count = 1;
    WriteMapToRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup,
                       count);

    settingsGroup = QString::fromLatin1("WLRoughnessVersion"), count = 1;
    WriteMapToRegistry(CrpsRoughnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowVersion"), count = 1;
    WriteMapToRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessVersion"), count = 1;
    WriteMapToRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationVersion"), count = 1;
    WriteMapToRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityVersion"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceIntensityFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleVersion"), count = 1;
    WriteMapToRegistry(CrpsTurbulenceScaleFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceVersion"), count = 1;
    WriteMapToRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectVersion"), count = 1;
    WriteMapToRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLReadAllTobeInstallObjVersionToRegistry()
{
    int count = 1;

    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethod"), count = 1;
    ReadMapFromRegistry(CrpsSimuMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLLocVersion"), count = 1;
    ReadMapFromRegistry(CrpsLocationDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLXPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsXSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLYPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsYSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLZPSDVersion"), count = 1;
    ReadMapFromRegistry(CrpsZSpectrumFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCohVersion"), count = 1;
    ReadMapFromRegistry(CrpsCoherenceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLDecompVersion"), count = 1;
    ReadMapFromRegistry(CrpsPSDdecomMethodFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLFreqVersion"), count = 1;
    ReadMapFromRegistry(CrpsFrequencyDistributionFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLRandVersion"), count = 1;
    ReadMapFromRegistry(CrpsRandomnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLModVersion"), count = 1;
    ReadMapFromRegistry(CrpsModulationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCorrVersion"), count = 1;
    ReadMapFromRegistry(CrpsCorrelationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMeanVersion"), count = 1;
    ReadMapFromRegistry(CrpsMeanFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTableToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsTableToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLMatrixToolVersion"), count = 1;
    ReadMapFromRegistry(CrpsMatrixToolFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjVersion"), count = 1;
    ReadMapFromRegistry(CrpsUserDefinedRPSObjectFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionVersion"), count = 1;
    ReadMapFromRegistry(CrpsCumulativeProbabilityDistributionFactory::GetVersionMap(),
                        settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLGustFactorVersion"), count = 1;
    ReadMapFromRegistry(CrpsGustFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLKurtosisVersion"), count = 1;
    ReadMapFromRegistry(CrpsKurtosisFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLPeakFactorVersion"), count = 1;
    ReadMapFromRegistry(CrpsPeakFactorFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionVersion"), count = 1;
    ReadMapFromRegistry(CrpsProbabilityDensityFunctionFactory::GetVersionMap(), settingsGroup,
                        count);

    settingsGroup = QString::fromLatin1("WLRoughnessVersion"), count = 1;
    ReadMapFromRegistry(CrpsRoughnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowVersion"), count = 1;
    ReadMapFromRegistry(CrpsShearVelocityOfFlowFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLSkewnessVersion"), count = 1;
    ReadMapFromRegistry(CrpsSkewnessFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLStandardDeviationVersion"), count = 1;
    ReadMapFromRegistry(CrpsStandardDeviationFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityVersion"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceIntensityFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleVersion"), count = 1;
    ReadMapFromRegistry(CrpsTurbulenceScaleFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLVarianceVersion"), count = 1;
    ReadMapFromRegistry(CrpsVarianceFactory::GetVersionMap(), settingsGroup, count);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectVersion"), count = 1;
    ReadMapFromRegistry(CrpsWavePassageEffectFactory::GetVersionMap(), settingsGroup, count);
}

void WindLabGui::Workbench::WLClearAllTobeInstallObjectsFromRegistry()
{
    QString settingsGroup;

    settingsGroup = QString::fromLatin1("WLSimMethod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLLoc");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLXPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLYPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLZPSD");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCoh");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLDecomp");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLFreq");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRand");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMod");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCorr");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMean");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTableTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMatrixTool");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObj");
    ClearMapFromRegistry(settingsGroup);

    //
    settingsGroup = QString::fromLatin1("WLSimMethodTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLLocTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLXPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLYPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLZPSDTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCohTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLDecompTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLFreqTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRandTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLModTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCorrTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMeanTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTableToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMatrixToolTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjTitle");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("WLSimMethodLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLLocLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLXPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLYPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLZPSDLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCohLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLDecompLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLFreqLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRandLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLModLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCorrLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMeanLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTableToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMatrixToolLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjLink");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("WLSimMethodAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLLocAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLXPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLYPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLZPSDAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCohAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLDecompAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLFreqAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRandAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLModAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCorrAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMeanAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTableToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMatrixToolAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjAuthor");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("WLSimMethodDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLLocDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLXPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLYPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLZPSDDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCohDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLDecompDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLFreqDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRandDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLModDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCorrDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMeanDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTableToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMatrixToolDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjDate");
    ClearMapFromRegistry(settingsGroup);


    //
    settingsGroup = QString::fromLatin1("WLSimMethodVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLLocVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLXPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLYPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLZPSDVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCohVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLDecompVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLFreqVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRandVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLModVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCorrVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMeanVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTableToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLMatrixToolVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLUserDefinedRPSObjVersion");
    ClearMapFromRegistry(settingsGroup);

    //////////////////////////////////////////////////////

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistribution");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLGustFactor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLKurtosis");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLPeakFactor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunction");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRoughness");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlow");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLSkewness");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLStandardDeviation");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensity");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceScale");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLVariance");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLWavePassageEffect");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLGustFactorTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLKurtosisTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLPeakFactorTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRoughnessTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLSkewnessTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLStandardDeviationTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLVarianceTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectTitle");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLGustFactorLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLKurtosisLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLPeakFactorLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRoughnessLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLSkewnessLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLStandardDeviationLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLVarianceLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectLink");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLGustFactorAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLKurtosisAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLPeakFactorAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRoughnessAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLSkewnessAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLStandardDeviationAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLVarianceAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectAuthor");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLGustFactorDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLKurtosisDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLPeakFactorDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRoughnessDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLSkewnessDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLStandardDeviationDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLVarianceDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectDate");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLCumulativeProbabilityDistributionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLGustFactorVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLKurtosisVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLPeakFactorVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLProbabilityDensityFunctionVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLRoughnessVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLShearVelocityOfFlowVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLSkewnessVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLStandardDeviationVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceIntensityVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLTurbulenceScaleVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLVarianceVersion");
    ClearMapFromRegistry(settingsGroup);

    settingsGroup = QString::fromLatin1("WLWavePassageEffectVersion");
    ClearMapFromRegistry(settingsGroup);
}



void WindLabGui::Workbench::ClearMapFromRegistry(QString& settingsGroup)
{
    QSettings settings;

    settings.beginGroup(settingsGroup);
    settings.remove(QString::fromLatin1(""));// removes the group, and all it keys
    settings.endGroup();
}



int WindLabGui::Workbench::RPSWriteInstalledPluginsToRegistry()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    // number of plugins to be installed
    int NberOfInstalledPlugins = App::PluginManager::GetInstance().GetInstalledPluginsMap().size();

    QSettings settings;
    settings.beginGroup(QLatin1String("WindLabToBeInstalledPlugins"));
    settings.setValue(QLatin1String("WindLabToBeInstalledPluginsNumber"), NberOfInstalledPlugins);

    std::map<QString, App::PluginInstance*>::iterator it;
    for (it = App::PluginManager::GetInstance().GetInstalledPluginsMap().begin();
         it != App::PluginManager::GetInstance().GetInstalledPluginsMap().end(); ++it) {
        // Get the plugin names
        Descript = it->second->GetPluginSubFolder();// second veut dire "b", first sera "a" map<a,b>

        // Make a name of each plugin to be saved
        PlgName = QLatin1String("%1").arg(i);

        settings.setValue(PlgName, Descript);

        i++;
    }

    settings.endGroup();

    return 1;
}

bool WindLabGui::Workbench::IntallRegistryPlugins()
{
    // Read the installed plugins from registry
    RPSReadInstalledPluginsFromRegistry();
    QString str;

    // Install each of them
    for (int i = 0; i < App::PluginManager::GetInstance().GetInstalledPluginsInRegVector().size(); i++) {
        QString PluginFromReg =
            App::PluginManager::GetInstance().GetInstalledPluginsInRegVector().at(i);

        App::PluginManager::GetInstance().InitializePlugin(PluginFromReg, 1, str);
        App::PluginManager::GetInstance().InitializePluginType(PluginFromReg, 1);
        App::PluginManager::GetInstance().InstallPlugin(PluginFromReg);
    }

    return true;
}

int WindLabGui::Workbench::RPSReadInstalledPluginsFromRegistry()
{
    RPSReadInstalledPluginsFromRegistryCommon();

    return 1;
}

int WindLabGui::Workbench::RPSReadInstalledPluginsFromRegistryCommon()
{
    int i = 1;
    QString PlgName;
    QString Descript;

    QSettings settings;

    settings.beginGroup(QLatin1String("WindLabToBeInstalledPlugins"));
    int NberOfInstalledPlugins = settings.value(QLatin1String("WindLabToBeInstalledPluginsNumber")).toInt();

    // Read one by one plugins saved in registry
    for (int i = 1; i <= NberOfInstalledPlugins; i++) {
        // Make a name of each plugin to be saved
        PlgName = QLatin1String("%1").arg(i);

        QString value = settings.value(PlgName).toString();

        App::PluginManager::GetInstance().GetInstalledPluginsInRegVector().push_back(value);
    }

    settings.endGroup();

    return 1;
}

void WindLabGui::Workbench::restoreSimulations(const App::Document &doc, const std::vector<App::DocumentObject*>& objs)
{  
   /* WindLab::WindLabSimulation* sim = nullptr;
     for(auto obj : objs) {
         if (obj->getTypeId().isDerivedFrom(WindLab::WindLabSimulation::getClassTypeId()))
         {
            sim = static_cast<WindLab::WindLabSimulation*>(obj);
            sim->setName(sim->Label.getStrValue());
            WindLabGui::WindLabSimulationObserver::instance()->addSimulation(sim);
            WindLabGui::WindLabSimulationObserver::instance()->addToSimulationDocumentMap(sim->Label.getStrValue(), doc.Label.getStrValue());

         }
     }*/
}

std::list<std::string> WindLabGui::Workbench::getAllPlugins() const
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("WindLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("WindLabWorkbench"));

    QString phenomenon = getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

    std::map<QString, App::PluginDescription*>::iterator it;
    std::list<std::string> list;
    for (it = App::PluginManager::GetInstance().GetPluginDescriptionsMap().begin(); it != App::PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it) {
         list.push_back(it->second->name.toUtf8().constData());
     }

    return list; 
}
std::list<std::string> WindLabGui::Workbench::getAllInstalledPlugins() const
{
    std::list<std::string> list;
    std::list<std::string> items = getAllPlugins();
    for (std::list<std::string>::const_iterator item = items.begin(); item != items.end(); ++item)
         if (isThisPluginInstalled(QString::fromLatin1((*item).c_str())))
         list.push_back(*item);
    return list;
}

bool WindLabGui::Workbench::installPlugin(const std::string pluginName)
{
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("WindLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("WindLabWorkbench"));

    QString phenomenon = getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

	auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[QString::fromLatin1(pluginName.c_str())];
    if (!InstallingPluginDescription)
         return false;
	QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
    QString info;
	const bool result = Gui::Application::Instance->InitializePlugin(InstallingPluginFullPath, 1, info);
    if((!result) || (!info.isNull()))
    {
        return false;
    }

     return Gui::Application::Instance->InstallPlugin(InstallingPluginFullPath);

}

bool WindLabGui::Workbench::unInstallPlugin(const std::string pluginName)
{ 
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("WindLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("WindLabWorkbench"));

    QString phenomenon = getPhenomenonName();

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }
    auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[QString::fromLatin1(pluginName.c_str())];
     if (!InstallingPluginDescription)
        return false;
    QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
    bool ret = Gui::Application::Instance->UnInstallPlugin(InstallingPluginFullPath);
    Gui::Application::Instance->emptyAllToBeUninstalledObjectsMap();
    return ret;
}

void WindLabGui::Workbench::createSimulation(const std::string simulationName)
{
    auto doc = App::GetApplication().getActiveDocument();
    if (!doc)
    {
        Base::Console().Warning("No valid active document found.\n");
        return;
    }
    std::string uniqueName = doc->getUniqueObjectName(simulationName.c_str());
	 WindLab::WindLabSimulation* newSim = static_cast< WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->createSimulation(uniqueName, "WindLab::WindLabSimulation"));
	WindLabGui::WindLabSimulationObserver::instance()->setActiveSimulation(newSim);
	App::GetApplication().getActiveDocument()->recompute();
}

void WindLabGui::Workbench::createFeature(const std::string simulationName, const std::string featureTypeName, const std::string featureName, const std::string featureGroup, const int featureType)
{
    //get the simulation for which this feature will created
	WindLab::WindLabSimulation* simParent = static_cast<WindLab::WindLabSimulation*>(WindLabGui::WindLabSimulationObserver::instance()->getSimulation(simulationName));
	if (!simParent)
		return;
	//get all WindLab feature type
	std::vector<Base::Type> types = simParent->getRPSTypesOfPluggableFeatures();

	//get the type of the creating feature
    Base::Type type = types[featureType];

	//create the feature
	WindLabAPI::WindLabFeature* newFeature = simParent->createFeature(type, featureGroup, featureName);

	if (!newFeature)
		return;

	//set the feature properties
    auto featureProperties = simParent->GetWindLabPluggedWindLabFeatureDescription(QString::fromLatin1(featureTypeName.c_str()), QString::fromLatin1(featureGroup.c_str()));
    newFeature->FeatureGroup.setValue(featureTypeName);
    newFeature->FeatureType.setValue(featureGroup);
    newFeature->Author.setValue(featureProperties->Author.getValue());
    newFeature->PublicationTopic.setValue(featureProperties->PublicationTitle.getValue());
    newFeature->PublicationDate.setValue(featureProperties->PublicationDate.getValue());
    newFeature->LinkToPublication.setValue(featureProperties->PublicationLink.getValue());
    newFeature->PublicationAuthor.setValue(featureProperties->PublicationAuthor.getValue());
    newFeature->Version.setValue(featureProperties->Version.getValue());
    newFeature->IsStationary.setValue(featureProperties->Stationarity.getValue());
    newFeature->PluginName.setValue(featureProperties->PluginName.getValue());
    newFeature->PluginVersion.setValue(featureProperties->PluginVersion.getValue());
    newFeature->APIVersion.setValue(featureProperties->APIVersion.getValue());
    newFeature->ReleaseDate.setValue(featureProperties->ReleaseDate.getValue());
	newFeature->Simulation.setValue(simParent->Label.getValue());

	App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(static_cast<App::DocumentObject*>(simParent));

    newFeature->recomputeFeature();
	group->addObject(newFeature);

    //show change in the property editor
    simParent->setEnums(type);
}