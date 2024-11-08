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


#ifndef USERLABFEATURE_SIMUMETHOD_FEATURE_H
#define USERLABFEATURE_SIMUMETHOD_FEATURE_H

#include "UserLabFeature.h"

namespace UserLabAPI
{

/** Base class of all shape feature classes in LabRPS
 */
class UserLabAPIExport UserLabFeatureSimulationMethod : public UserLabAPI::UserLabFeature
{
    PROPERTY_HEADER_WITH_OVERRIDE(UserLabAPI::UserLabFeatureSimulationMethod);

public:
    /// Constructor
    UserLabFeatureSimulationMethod(void);
    virtual ~UserLabFeatureSimulationMethod();

    virtual const char* getViewProviderName() const {
        return "UserLabGui::ViewProviderUserLabFeatureSimulationMethod";
    }
    /** @name methods override feature */
    //@{
    virtual short mustExecute() const override;
    //@}

protected:
    /// recompute only this object
    virtual App::DocumentObjectExecReturn *recompute() override;
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute() override;
    virtual void onChanged(const App::Property* prop) override;
};

} //namespace UserLabAPI


#endif // USERLABFEATURE_SIMUMETHOD_FEATURE_H

