/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC) <vv.titov@gmail.com>       *
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

/**
  * AttacherTexts.h, .cpp - files that contain user-friendly translatable names
  * of attachment modes, as well as help texts, and the like.
  */

#ifndef RPSWINDLABPYTHONPLUGIN_UTILITIES
#define RPSWINDLABPYTHONPLUGIN_UTILITIES

#include <Mod/WindLab/WindLabGlobal.h>
#include <CXX/Objects.hxx>

namespace WindLabGui
{
// Python interface
class WindLabGuiExport RPSWindLabPyTool
{
public:
    static PyMethodDef    Methods[];
    static PyObject* ShowArray(PyObject* /*self*/, PyObject* args);
    static PyObject* ShowArrayAsMatrix(PyObject* /*self*/, PyObject* args);
    static PyObject* ShowValueAsTable(PyObject* /*self*/, PyObject* args);
    static PyObject* GetActiveTable(PyObject* /*self*/, PyObject* args);
    static PyObject* GetActiveMatrix(PyObject* /*self*/, PyObject* args);


};

} 
#endif // RPSWINDLABPYTHONPLUGIN_UTILITIES