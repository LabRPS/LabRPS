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


#ifndef APP_RPSFEATURE_H
#define APP_RPSFEATURE_H

#include "DocumentObject.h"
#include <Base/SmartPtrPy.h>

namespace App
{

/** Base class of all random phenomena simulation document objects.
 */
class AppExport RPSFeature : public App::DocumentObject
{
    PROPERTY_HEADER(App::RPSFeature);

public:
    std::string Text;

    /// Constructor
    RPSFeature(void);

    // destructor
    virtual ~RPSFeature();

    /// Specify the type of element name to return when calling getElementName() 
    enum ElementNameType {
        /// Normal usage
        Normal = 0,
        /// For importing
        Import = 1,
        /// For exporting
        Export = 2,
    };
    /** Return the new and old style sub-element name
     *
     * @param name: input name
     * @param type: desired element name type to return
     *
     * @return a pair(newName,oldName). New element name may be empty.
     *
     * This function currently is does nothing. The new style element name
     * generation will be added in the next batch of patches.
     */
    virtual std::pair<std::string, std::string> getElementName(
        const char* name, ElementNameType type = Normal) const;

    /** Resolve both the new and old style element name
     *
     * @param obj: top parent object
     * @param subname: subname reference
     * @param elementName: output of a pair(newElementName,oldElementName)
     * @param append: Whether to include subname prefix into the returned
     *                element name
     * @param type: the type of element name to request
     * @param filter: If none zero, then only perform lookup when the element
     *                owner object is the same as this filter
     * @param element: return the start of element name in subname
     *
     * @return Return the owner object of the element
     */
    static DocumentObject* resolveElement(App::DocumentObject* obj,
        const char* subname, std::pair<std::string, std::string>& elementName,
        bool append = false, ElementNameType type = Normal,
        const DocumentObject* filter = nullptr, const char** element = nullptr, RPSFeature** sim = nullptr);

    virtual PyObject* getPyObject() override;

/// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

} //namespace App


#endif // APP_RPSFEATURE_H
