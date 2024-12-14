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


#ifndef SEALABGUI_VIEWPROVIDERSEALABFEATURELOCATIONDISTRIBUTION_H
#define SEALABGUI_VIEWPROVIDERSEALABFEATURELOCATIONDISTRIBUTION_H

#include <Gui/ViewProviderRPSFeature.h>
#include <Libraries/Alphaplot/Table.h>
#include <Mod/SeaLab/SeaLabGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Mod/SeaLab/Gui/SeaLabAllFeaturesComputation.h>

namespace SeaLabGui {

    class SeaLabGuiExport ViewProviderSeaLabFeatureLocationDistribution : public Gui::ViewProviderRPSFeature
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeaLabGui::ViewProviderSeaLabFeatureLocationDistribution);

public:
    /// constructor
    ViewProviderSeaLabFeatureLocationDistribution();
    /// destructor
    virtual ~ViewProviderSeaLabFeatureLocationDistribution();

     App::PropertyBool ShowSimulationPoints;

    // // Points
    //App::PropertyFloatConstraint PointSize;
    //App::PropertyColor PointColor;
    //App::PropertyMaterial PointMaterial;
    //App::PropertyColorList PointColorArray;
    //// Lines
    //App::PropertyFloatConstraint LineWidth;
    //App::PropertyColor LineColor;
    //App::PropertyMaterial LineMaterial;
    //App::PropertyColorList LineColorArray;

    ////ground
    //App::PropertyBool ShowGround;
    //App::PropertyFloat GroundLength;
    //App::PropertyFloat GroundWidth;
    //App::PropertyColor GroundColor;
    //App::PropertyFloat GroundOpacity;

    ////grid
    //App::PropertyBool ShowGrid;

    ////axis
    //App::PropertyBool ShowAxis;
    //App::PropertyFloat AxisScale;

    //App::PropertyBool ShowPointNumbering;
    //App::PropertyFloat NumberingOffsetX;
    //App::PropertyFloat NumberingOffsetY;
    //App::PropertyFloat NumberingOffsetZ;
    //App::PropertyFloat FontSize;
    //App::PropertyFont FontName;

    virtual bool doubleClicked(void);
    void setupContextMenu(QMenu*, QObject*, const char*);

    bool ComputeLocationCoordinateMatrixP3();
    bool ActivateFeature();
    bool OnInitialSetting();
    bool getComputationResultVariableVector(vec& resultVectorVar);
    bool getComputationResultValueVector(vec& resultVectorVal);
    bool getComputationResultComplexValueVector(cx_vec& resultVectorVal_cx);
    bool getComputationResultMatrix(mat& resultMatrix);
    bool getComputationResultComplexMatrix(cx_mat& resultMatrix_cx);

protected:
    /// get called by the container whenever a property has been changed
    virtual void onChanged(const App::Property* prop) override;

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);

public:
    virtual PyObject* getPyObject() override;

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
    static App::PropertyFloatConstraint::Constraints sizeRange;

// public:
//     SeaLabAllFeaturesComputation* seaLabAllFeaturesComputation = nullptr;

public:
    bool runFeatureMethod(const QString function, const char* complexNumberDisplay = "Real");
};

} // namespace PartGui


#endif // SEALABGUI_VIEWPROVIDERSEALABFEATURELOCATIONDISTRIBUTION_H

