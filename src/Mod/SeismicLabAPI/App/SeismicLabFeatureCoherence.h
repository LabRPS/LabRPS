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


#ifndef SEISMICLABFEATURE_COHERENCE_FEATURE_H
#define SEISMICLABFEATURE_COHERENCE_FEATURE_H

#include "SeismicLabFeature.h"

namespace SeismicLabAPI
{

/** Base class of all shape feature classes in LabRPS
 */
class SeismicLabAPIExport SeismicLabFeatureCoherence : public SeismicLabAPI::SeismicLabFeature
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLabAPI::SeismicLabFeatureCoherence);

public:
    /// Constructor
    SeismicLabFeatureCoherence(void);
    virtual ~SeismicLabFeatureCoherence();

    virtual const char* getViewProviderName() const {
        return "SeismicLabGui::ViewProviderSeismicLabFeatureCoherence";
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

} //namespace SeismicLabAPI


#endif // SEISMICLABFEATURE_COHERENCE_FEATURE_H
