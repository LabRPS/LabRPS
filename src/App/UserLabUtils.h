/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>         *
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

#ifndef APP_USERLAB_UTILS_H
#define APP_USERLAB_UTILS_H

#include <Mod/UserLab/UserLabGlobal.h>
#include <map>
#include <QString>

namespace App {

//! Definition of global constants and enums
/**
 * This class must not be instanced. All members are static.
 */
class AppExport UserLabUtils {

 private:
     UserLabUtils() {}  // don't allow instancing

 public:
  virtual ~UserLabUtils() {}  // avoid the warning message

  static QString rpsPhenomenon;
  static QString objGroupSimulationMethod;
  static QString docRPSFeatures;
  static QString docSimulations;
  static QString Simulate;
  static QString SimulateInLargeScaleMode;

};

} // namespace Gui

#endif  // APP_USERLAB_UTILS_H
