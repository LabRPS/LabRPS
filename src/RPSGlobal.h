/***************************************************************************
 *   Copyright (c) 2019 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
/** \file RPSGlobal.h
 *  \brief Include export or import macros.
 */


#ifndef RPS_GLOBAL_H
#define RPS_GLOBAL_H


#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(__CYGWIN__)
#  define LABRPS_DECL_EXPORT __declspec(dllexport)
#  define LABRPS_DECL_IMPORT __declspec(dllimport)
#else
#  define LABRPS_DECL_EXPORT
#  define LABRPS_DECL_IMPORT
#endif

// LabRPSBase
#ifdef LabRPSBase_EXPORTS
#  define BaseExport  LABRPS_DECL_EXPORT
#else
#  define BaseExport  LABRPS_DECL_IMPORT
#endif

// LabRPSApp
#ifdef LabRPSApp_EXPORTS
#       define AppExport   LABRPS_DECL_EXPORT
#       define DataExport  LABRPS_DECL_EXPORT
#else
#       define AppExport   LABRPS_DECL_IMPORT
#       define DataExport  LABRPS_DECL_IMPORT
#endif

// LabRPSGui
#ifdef LabRPSGui_EXPORTS
#  define GuiExport   LABRPS_DECL_EXPORT
#else
#  define GuiExport   LABRPS_DECL_IMPORT
#endif

#endif //RPS_GLOBAL_H
