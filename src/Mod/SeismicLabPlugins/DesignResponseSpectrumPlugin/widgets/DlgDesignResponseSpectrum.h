/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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

#ifndef SEISMICLABGUI_DlgDesignResponseSpectrum_H
#define SEISMICLABGUI_DlgDesignResponseSpectrum_H
#define QT_NO_KEYWORDS

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeismicLabGui {

class Ui_DlgDesignResponseSpectrum;
class DlgDesignResponseSpectrum : public QWidget
{
    Q_OBJECT

public:
    DlgDesignResponseSpectrum(const App::PropertySpeed& MeanSpeedIncrement,
                    const App::PropertyInteger& NumberOfBins,
                    const App::PropertyFloat& ShapeParameter,
                    const App::PropertyFloat& ScaleParameter,
                    const App::PropertyBool& UserDefinedWeibullParameters,
                    const App::PropertyEnumeration& WeibulParametersEstimationMethod,
                    const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgDesignResponseSpectrum();
    void accept();
    void reject();

 public Q_SLOTS:
    void slotEnableUserDefinedWeibullParameters();    
        

private:
    std::unique_ptr<Ui_DlgDesignResponseSpectrum> ui;
    std::string _featureName;
};

class DlgDesignResponseSpectrumEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgDesignResponseSpectrumEdit(const App::PropertySpeed& MeanSpeedIncrement,
                        const App::PropertyInteger& NumberOfBins,
                        const App::PropertyFloat& ShapeParameter,
                        const App::PropertyFloat& ScaleParameter,
                        const App::PropertyBool& UserDefinedWeibullParameters,
                        const App::PropertyEnumeration& WeibulParametersEstimationMethod,
                        const App::PropertyString& featureName);
    ~DlgDesignResponseSpectrumEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgDesignResponseSpectrum* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeismicLabGui

#endif // SEISMICLABGUI_DlgDesignResponseSpectrum_H
