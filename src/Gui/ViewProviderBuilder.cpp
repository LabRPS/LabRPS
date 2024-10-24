/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
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
#endif

#include <App/PropertyStandard.h>

#include "ViewProviderBuilder.h"
#include "Window.h"


using namespace Gui;

std::map<Base::Type, Base::Type> ViewProviderBuilder::_prop_to_view;

ViewProviderBuilder::ViewProviderBuilder()
{
}

ViewProviderBuilder::~ViewProviderBuilder()
{
}

void ViewProviderBuilder::add(const Base::Type& prop, const Base::Type& view)
{
    _prop_to_view[prop] = view;
}

ViewProvider* ViewProviderBuilder::create(const Base::Type& type)
{
    std::map<Base::Type, Base::Type>::iterator it = _prop_to_view.find(type);
    if (it != _prop_to_view.end())
        return reinterpret_cast<ViewProvider*>(it->second.createInstance());
    return nullptr;
}

// --------------------------------------

ViewProviderColorBuilder::ViewProviderColorBuilder()
{
}

ViewProviderColorBuilder::~ViewProviderColorBuilder()
{
}

