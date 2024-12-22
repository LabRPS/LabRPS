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

#include <RPSGlobal.h>

#ifndef USERLABPLUGIN_GLOBAL_H
#define USERLABPLUGIN_GLOBAL_H


// UserLabPlugin
#ifndef UserLabPluginExport
#ifdef UserLabPlugin_EXPORTS
#  define UserLabPluginExport      LABRPS_DECL_EXPORT
#else
#  define UserLabPluginExport      LABRPS_DECL_IMPORT
#endif
#endif

// UserLabPluginGui
#ifndef UserLabPluginGuiExport
#ifdef UserLabPluginGui_EXPORTS
#  define UserLabPluginGuiExport   LABRPS_DECL_EXPORT
#else
#  define UserLabPluginGuiExport   LABRPS_DECL_IMPORT
#endif
#endif

#endif //USERLABPLUGIN_GLOBAL_H
