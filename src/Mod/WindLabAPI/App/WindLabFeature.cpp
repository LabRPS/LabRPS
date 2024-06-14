#include "PreCompiled.h"

#ifndef _PreComp_
# include <sstream>
#endif

#include <Base/Console.h>
#include <Base/Exception.h>
#include "WindLabFeature.h"
#include "WindLabFeaturePy.h"

using namespace WindLabAPI;
namespace bp = boost::placeholders;

RPS_LOG_LEVEL_INIT("WindLab",true,true)

PROPERTY_SOURCE(WindLabAPI::WindLabFeature, App::RPSFeature)


WindLabFeature::WindLabFeature(void)
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
    ADD_PROPERTY_TYPE(LinkToPublication, (""), publicationgroup, App::Prop_ReadOnly, "The internet link to the article in which this feature was published");
   
    static const char* parentPlugin = "Parent Plugin";
    ADD_PROPERTY_TYPE(PluginVersion, (""), parentPlugin, App::Prop_ReadOnly, "Whether this feature is active or not");
    ADD_PROPERTY_TYPE(PluginName, (""), parentPlugin, App::Prop_ReadOnly, "Whether this feature is active or not");

    static const char* parentSimulation = "Parent Simulation";
    ADD_PROPERTY_TYPE(Simulation, (""), parentSimulation, App::Prop_ReadOnly, "Whether this feature is active or not");

    ADD_PROPERTY_TYPE(IsStationary, (true), featuregroup, App::Prop_ReadOnly, "Whether this feature is stationary or not");
}

WindLabFeature::~WindLabFeature()
{
}

short WindLabFeature::mustExecute(void) const
{
    return RPSFeature::mustExecute();
}

App::DocumentObjectExecReturn * WindLabFeature::recompute(void)
{
    try {
        return App::RPSFeature::recompute();
    }
    catch (Base::Exception& e) {

        App::DocumentObjectExecReturn* ret = new App::DocumentObjectExecReturn(e.what());
        if (ret->Why.empty()) ret->Why = "Unknown exception";
        return ret;
    }
}

App::DocumentObjectExecReturn * WindLabFeature::execute(void)
{
    return RPSFeature::execute();
}

void WindLabFeature::onChanged(const App::Property* prop)
{
    RPSFeature::onChanged(prop);
}

PyObject* WindLabFeature::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        PythonObject = Py::Object(new WindLabFeaturePy(this), true);
    }
    return Py::new_reference_to(PythonObject);
}