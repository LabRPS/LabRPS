/***************************************************************************
 *   Copyright (c) 2021 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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

#include <RPSGlobal.h>

#ifndef WINDLABAPI_GLOBAL_H
#define WINDLABAPI_GLOBAL_H

#ifdef _WIN32
#ifdef RPS_BUILDING_CORE
#define RPS_CORE_API   __declspec(dllexport)
#define RPS_PLUGIN_API __declspec(dllimport)
#else
#define RPS_CORE_API   __declspec(dllimport)
#define RPS_PLUGIN_API __declspec(dllexport)
#endif
#else
#define RPS_CORE_API
#define RPS_PLUGIN_API
#endif

// WindLabAPI
#ifndef WindLabAPIExport
#ifdef WindLabAPI_EXPORTS
#  define WindLabAPIExport      LABRPS_DECL_EXPORT
#else
#  define WindLabAPIExport      LABRPS_DECL_IMPORT
#endif
#endif

// WindLabAPIGui
#ifndef WindLabAPIGuiExport
#ifdef WindLabAPIGui_EXPORTS
#  define WindLabAPIGuiExport   LABRPS_DECL_EXPORT
#else
#  define WindLabAPIGuiExport   LABRPS_DECL_IMPORT
#endif
#endif

#endif //WINDLABAPI_GLOBAL_H
