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

#ifndef SEISMICLAB_PLUGIN_SIMUMETHOD_SEISMSIM_H
#define SEISMICLAB_PLUGIN_SIMUMETHOD_SEISMSIM_H

#include <Mod/SeismicLabAPI/App/IrpsSLSimulationMethod.h>
#include <App/PropertyUnits.h>

namespace SeismicLabAPI { class SeismicLabSimulationData; }

namespace SeismicLab {

class CRPSAspasiaZerva: public SeismicLabAPI::IrpsSLSimulationMethod
{
    PROPERTY_HEADER_WITH_OVERRIDE(SeismicLab::CRPSAspasiaZerva);

public:
	CRPSAspasiaZerva();

	~CRPSAspasiaZerva() {};

	bool OnInitialSetting(const SeismicLabAPI::SeismicLabSimulationData& Data);

    bool Simulate(const SeismicLabAPI::SeismicLabSimulationData& Data, cube &dPhenomenon);

    bool SimulateInLargeScaleMode(const SeismicLabAPI::SeismicLabSimulationData& Data, QString &strFileName);

public:
    App::PropertyAcceleration StandardDeviation; 
    App::PropertyFrequency DominantFrequency;
    App::PropertyFloat DampingRatio;
    App::PropertyFloat EnvelopValueAtNinetyPercentDuration;
    App::PropertyTime NormalizedDurationTimeAtPeak;
};

} // namespace SeismicLab

#endif // #ifndef SEISMICLAB_PLUGIN_SIMUMETHOD_SEISMSIM_H
