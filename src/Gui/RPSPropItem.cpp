/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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

#include "PreCompiled.h"
#ifndef _PreComp_

# include <QDir>
# include <QProcess>
# include <QTemporaryFile>
# include <sstream>
#endif

#include <Base/FileInfo.h>
#include <Base/Stream.h>
#include <Base/Tools.h>

#include "RPSPropItem.h"
#include "propertyeditor/PropertyItem.h"
#include "SelectionObject.h"


using namespace Gui;
using namespace Gui::PropertyEditor;

static bool init_done = false;

bool Gui::RPSPropItem::isInitialized()
{
    return init_done;
}

void Gui::RPSPropItem::init()
{
    PropertyItem                    ::init();
    PropertySeparatorItem           ::init();
    PropertyStringItem              ::init();
    PropertyFontItem                ::init();
    PropertyIntegerItem             ::init();
    PropertyIntegerConstraintItem   ::init();
    PropertyFloatItem               ::init();
    PropertyUnitItem                ::init();
    PropertyFloatConstraintItem     ::init();
    PropertyPrecisionItem           ::init();
    PropertyUnitConstraintItem      ::init();
    PropertyAngleItem               ::init();
    PropertyBoolItem                ::init();
    PropertyVectorItem              ::init();
    PropertyVectorListItem          ::init();
    PropertyVectorDistanceItem      ::init();
    PropertyPositionItem            ::init();
    PropertyDirectionItem           ::init();
    PropertyMatrixItem              ::init();
    PropertyRotationItem            ::init();
    PropertyEnumItem                ::init();
    PropertyStringListItem          ::init();
    PropertyFloatListItem           ::init();
    PropertyIntegerListItem         ::init();
    PropertyColorItem               ::init();
    PropertyMaterialItem            ::init();
    PropertyMaterialListItem        ::init();
    PropertyFileItem                ::init();
    PropertyPathItem                ::init();
    PropertyTransientFileItem       ::init();

    SelectionObject                 ::init();

    qRegisterMetaType<Base::Vector3f>("Base::Vector3f");
    qRegisterMetaType<Base::Vector3d>("Base::Vector3d");
    qRegisterMetaType<Base::Quantity>("Base::Quantity");
    qRegisterMetaType<QList<Base::Quantity> >("Base::QuantityList");
    init_done = true;
}

