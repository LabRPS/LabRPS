/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
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


#ifndef APP_PROPERTYGEO_H
#define APP_PROPERTYGEO_H

#include <Base/Unit.h>
#include <Base/Vector3D.h>

#include "PropertyLinks.h"
#include <RPSGlobal.h>


namespace Base {
class Writer;
}

namespace App
{
class Feature;
class Placement;



/** Vector properties
 * This is the father of all properties handling Integers.
 */
class AppExport PropertyVector: public Property
{
    TYPESYSTEM_HEADER_WITH_OVERRIDE();

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyVector();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyVector();

    /** Sets the property
     */
    void setValue(const Base::Vector3d &vec);
    void setValue(double x, double y, double z);

    /// Get valid paths for this property; used by auto completer
    void getPaths(std::vector<ObjectIdentifier> &paths) const override;

    /** This method returns a string representation of the property
     */
    const Base::Vector3d &getValue(void) const;
    const char* getEditorName(void) const override {
        return "Gui::PropertyEditor::PropertyVectorItem";
    }

    virtual PyObject *getPyObject(void) override;
    virtual void setPyObject(PyObject *) override;

    virtual void Save (Base::Writer &writer) const override;
    virtual void Restore(Base::XMLReader &reader) override;

    virtual Property *Copy(void) const override;
    virtual void Paste(const Property &from) override;

    virtual unsigned int getMemSize (void) const override {
        return sizeof(Base::Vector3d);
    }

    virtual const boost::any getPathValue(const ObjectIdentifier &path) const override;

    virtual bool getPyPathValue(const ObjectIdentifier &path, Py::Object &res) const override;

    virtual Base::Unit getUnit() const {
        return Base::Unit();
    }

    virtual bool isSame(const Property &other) const override {
        if (&other == this)
            return true;
        return getTypeId() == other.getTypeId()
            && getValue() == static_cast<decltype(this)>(&other)->getValue();
    }

private:
    Base::Vector3d _cVec;
};


class AppExport PropertyVectorDistance: public PropertyVector
{
    TYPESYSTEM_HEADER();

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyVectorDistance();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyVectorDistance();

    virtual Base::Unit getUnit() const {
        return Base::Unit::Length;
    }

    const char* getEditorName(void) const {
        return "Gui::PropertyEditor::PropertyVectorDistanceItem";
    }
};

class AppExport PropertyPosition: public PropertyVector
{
    TYPESYSTEM_HEADER();

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyPosition();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyPosition();

    virtual Base::Unit getUnit() const {
        return Base::Unit::Length;
    }

    const char* getEditorName(void) const {
        return "Gui::PropertyEditor::PropertyPositionItem";
    }
};

class AppExport PropertyDirection: public PropertyVector
{
    TYPESYSTEM_HEADER();

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyDirection();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyDirection();

    virtual Base::Unit getUnit() const {
        return Base::Unit::Length;
    }

    const char* getEditorName(void) const {
        return "Gui::PropertyEditor::PropertyDirectionItem";
    }
};

class AppExport PropertyVectorList: public PropertyListsT<Base::Vector3d>
{
    TYPESYSTEM_HEADER_WITH_OVERRIDE();

    typedef PropertyListsT<Base::Vector3d> inherited;

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyVectorList();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyVectorList();

    void setValue(double x, double y, double z);
    using inherited::setValue;

    virtual PyObject *getPyObject(void) override;

    virtual void Save (Base::Writer &writer) const override;
    virtual void Restore(Base::XMLReader &reader) override;

    virtual void SaveDocFile (Base::Writer &writer) const override;
    virtual void RestoreDocFile(Base::Reader &reader) override;

    virtual Property *Copy(void) const override;
    virtual void Paste(const Property &from) override;

    virtual unsigned int getMemSize (void) const override;
    const char* getEditorName(void) const override {
        return "Gui::PropertyEditor::PropertyVectorListItem";
    }

protected:
    Base::Vector3d getPyValue(PyObject *) const override;
};

} // namespace App


#endif // APP_PROPERTYGEO_H
