#ifndef WINDLAB_FEATURE_H
#define WINDLAB_FEATURE_H

#include <App/RPSFeature.h>
#include <Base/SmartPtrPy.h>
#include <Mod/WindLabAPI/WindLabAPIGlobal.h>

namespace WindLabAPI
{

/** Base class of all WindLab Features in LabRPS
 */
class WindLabAPIExport WindLabFeature : public App::RPSFeature
{
    PROPERTY_HEADER_WITH_OVERRIDE(WindLabAPI::WindLabFeature);

public:
    /// Constructor
    WindLabFeature(void);
    virtual ~WindLabFeature();

    App::PropertyBool IsActive;
    App::PropertyString FeatureType;
    App::PropertyString FeatureGroup;
    App::PropertyString Author;
    App::PropertyString PublicationTopic;
    App::PropertyString PublicationDate;
    App::PropertyString LinkToPublication;
    App::PropertyString PublicationAuthor;
    App::PropertyString Version;
    App::PropertyString PluginName;
    App::PropertyString PluginVersion;
    App::PropertyString APIVersion;
    App::PropertyString ReleaseDate;
    App::PropertyString Simulation;
    
    App::PropertyBool IsStationary;

    /** @name methods override feature */
    //@{
    virtual short mustExecute() const override;
    //@}

protected:
    /// recompute only this object
    virtual App::DocumentObjectExecReturn *recompute() override;
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute() override;
    virtual void onChanged(const App::Property* prop) override;

    virtual PyObject* getPyObject() override;

    /// python object of this class
protected:// attributes
    Py::SmartPtr PythonObject;
};

} //namespace App


#endif // WINDLAB_FEATURE_H

