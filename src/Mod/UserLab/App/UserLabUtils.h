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

#ifndef RPS_GLOBALS_H
#define RPS_GLOBALS_H

#include <Mod/UserLab/UserLabGlobal.h>
#include <map>
#include <QString>

namespace UserLab {

//! Definition of global constants and enums
/**
 * This class must not be instanced. All members are static.
 */
class UserLabExport UserLabUtils {

 private:
     UserLabUtils() {}  // don't allow instancing

 public:
  virtual ~UserLabUtils() {}  // avoid the warning message

  // phenomena
  static QString rpsPhenomenon;
  static QString objGroupSimulationMethod;
  static QString docRPSFeatures;
  static QString docSimulations;

  static QString Simulate;
  static QString SimulateInLargeScaleMode;

  static bool getObjects(std::map<const std::string, std::string>& map, std::map<const std::string, std::string>& lstObject, const std::string& pluginName, const std::string& objectGroup);
  static bool updateObjectsMap(std::map<const std::string, std::string>& map, const QString& lstObject);
  static bool updateObjectToSkipMap(std::map<const std::string, std::string>& map, const QString name, const QString pluginName);
  static bool isThisObjectGroupPluggedInThisPlugin(const std::map<const std::string, std::string>& map,const QString& pluginName);
  static bool isThisObjectInstalled(std::map<const std::string, std::string>& map, QString& object);

public:
  enum class ColorPal { Light, Dark };
  enum class TableColorProfile { Success, Failure, Generic };
  static int getWordSizeApp();
  static QString getOperatingSystem();
  static int getWordSizeOfOS();
  static QString splitstring(const QString &string);
  static QString joinstring(const QString &string);

  // html Formatting
  static QString makeHtmlTable(const int row, const int column,
                               const bool hasheader,
                               const TableColorProfile &profile);

 private:
  static double rgbRandomSeed_;
  static int rgbCounter_;
};

} // namespace Gui

#endif  // RPS_GLOBALS_H
