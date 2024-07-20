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


#include "PreCompiled.h"
#include "RPSFeature.h"
#include <App/RPSFeaturePy.h>


using namespace App;


//===========================================================================
// Feature
//===========================================================================

PROPERTY_SOURCE(App::RPSFeature, App::DocumentObject)


RPSFeature::RPSFeature(void)
{
    static const char* featuregroup = "Basic Data";
    ADD_PROPERTY_TYPE(IsActive, (false), featuregroup, App::Prop_ReadOnly, "Whether this feature is active or not");
    ADD_PROPERTY_TYPE(Author, (""), featuregroup, App::Prop_ReadOnly, "The name of the person that implements the feature");
    ADD_PROPERTY_TYPE(Version, (""), featuregroup, App::Prop_ReadOnly, "This feature version");
    ADD_PROPERTY_TYPE(APIVersion, (""), featuregroup, App::Prop_ReadOnly, "This feature API version");
    ADD_PROPERTY_TYPE(ReleaseDate, (""), featuregroup, App::Prop_ReadOnly, "This feature release date");
    ADD_PROPERTY_TYPE(FeatureType, (""), featuregroup, App::Prop_ReadOnly, "The feature type");
    ADD_PROPERTY_TYPE(FeatureGroup, (""), featuregroup, App::Prop_ReadOnly, "The feature group");

    static const char* publicationgroup = "Feature Publication";
    ADD_PROPERTY_TYPE(PublicationAuthor, (""), publicationgroup, App::Prop_ReadOnly, "The name of the author that publishes this feature");
    ADD_PROPERTY_TYPE(PublicationTopic, (""), publicationgroup, App::Prop_ReadOnly, "The publication topic of the article in which this feature was published");
    ADD_PROPERTY_TYPE(PublicationDate, (""), publicationgroup, App::Prop_ReadOnly, "The publication date of the article in which this feature was published");
    ADD_PROPERTY_TYPE(LinkToPublication, (""), publicationgroup, App::Prop_None, "The internet link to the article in which this feature was published");
   
    static const char* parentPlugin = "Parent Plugin";
    ADD_PROPERTY_TYPE(PluginVersion, (""), parentPlugin, App::Prop_ReadOnly, "The version of the plugin in which the feature is implemented.");
    ADD_PROPERTY_TYPE(PluginName, (""), parentPlugin, App::Prop_ReadOnly, "The name of the plugin in which the feature is implemented");

    static const char* parentSimulation = "Parent Simulation";
    ADD_PROPERTY_TYPE(Simulation, (""), parentSimulation, App::Prop_ReadOnly, "The name of the simulation where the feature is created.");

    ADD_PROPERTY_TYPE(IsStationary, (true), featuregroup, App::Prop_ReadOnly, "Whether this feature is stationary or not");
    ADD_PROPERTY_TYPE(IsUniformlyModulated, (false), featuregroup, App::Prop_None, "Whether this feature should be uniformly modulated or not. This is useful in case of non-stationarity");

}

RPSFeature::~RPSFeature(void)
{
}

std::pair<std::string, std::string> RPSFeature::getElementName(
    const char* name, ElementNameType type) const
{
    (void)type;

    std::pair<std::string, std::string> ret;
    if (!name)
        return ret;

    ret.second = name;
    return ret;
}

DocumentObject* RPSFeature::resolveElement(DocumentObject* obj, const char* subname,
    std::pair<std::string, std::string>& elementName, bool append,
    ElementNameType type, const DocumentObject* filter,
    const char** _element, RPSFeature** geoFeature)
{
    if (!obj || !obj->getNameInDocument())
        return nullptr;
    if (!subname)
        subname = "";
    const char* element = subname;//Koffa
    if (_element) *_element = element;
    auto sobj = obj->getSubObject(subname);
    if (!sobj)
        return nullptr;
    //obj = sobj->getLinkedObject(true);
    auto geo = dynamic_cast<RPSFeature*>(obj);
    if (geoFeature)
        *geoFeature = geo;
    if (!obj || (filter && obj != filter))
        return nullptr;
    if (!element || !element[0]) {
       /* if (append)
            elementName.second = Data::ComplexGeoData::oldElementName(subname);*/
        return sobj;
    }

    if (!geo || hasHiddenMarker(element)) {
        if (!append)
            elementName.second = element;
        /*else
            elementName.second = Data::ComplexGeoData::oldElementName(subname);*/
        return sobj;
    }
    if (!append)
        elementName = geo->getElementName(element, type);
    else {
        const auto& names = geo->getElementName(element, type);
        std::string prefix(subname, element - subname);
        if (names.first.size())
            elementName.first = prefix + names.first;
        elementName.second = prefix + names.second;
    }
    return sobj;
}

PyObject* RPSFeature::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new RPSFeaturePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}