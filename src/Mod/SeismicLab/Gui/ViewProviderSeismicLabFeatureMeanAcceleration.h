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


#ifndef SEISMICLABGUI_VIEWPROVIDERSEISMICLABFEATUREMEANACCELERATION_H
#define SEISMICLABGUI_VIEWPROVIDERSEISMICLABFEATUREMEANACCELERATION_H

#include <Gui/ViewProviderDocumentObject.h>
#include <Libraries/Alphaplot/Table.h>
#include <Mod/SeismicLab/SeismicLabGlobal.h>
#include <Base/SmartPtrPy.h>
#include <Mod/SeismicLab/Gui/SeismicLabAllFeaturesComputation.h>
namespace SeismicLabGui {


class SeismicLabGuiExport ViewProviderSeismicLabFeatureMeanAcceleration : public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLabGui::ViewProviderSeismicLabFeatureMeanAcceleration);

public:
    /// constructor
    ViewProviderSeismicLabFeatureMeanAcceleration();
    /// destructor
    virtual ~ViewProviderSeismicLabFeatureMeanAcceleration();

    virtual bool doubleClicked(void);
    void setupContextMenu(QMenu*, QObject*, const char*);

    bool computeMeanAccelerationValue();
    bool computeMeanAccelerationVectorP();
    bool computeMeanAccelerationVectorT();
    bool ActivateFeature();

    bool OnInitialSetting();

    virtual void onChanged(const App::Property* prop);

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);

private:
    QPointer<Table> tableWidget;

public:
    virtual PyObject* getPyObject() override;

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;

public:
    SeismicLabAllFeaturesComputation* seismicLabAllFeaturesComputation = nullptr;

public:
    bool runFeatureMethod(const QString function, const char* complexNumberDisplay = "Real");
};

} // namespace PartGui


#endif // SEISMICLABGUI_VIEWPROVIDERSEISMICLABFEATUREMEANACCELERATION_H

