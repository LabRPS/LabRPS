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

#include <Base/Console.h>
#include <Base/PyObjectBase.h>
#include <Base/Exception.h>
#include <Base/FileInfo.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Base/Interpreter.h>
#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>
#include "UserLabSimulation.h"
#include "UserLabSimulationPy.h"
#include <App/Simulation.h>
#include <App/RPSpluginManager.h>
#include <Mod/UserLabAPI/App/UserLabFeature.h>
#include <Mod/UserLabAPI/App/UserLabFeatureDescription.h>
#include "UserLabUtils.h"

namespace UserLab {
class Module : public Py::ExtensionModule<Module>
{
public:

    Module() : Py::ExtensionModule<Module>("UserLab")
    {

        add_varargs_method("open",&Module::open );
        add_varargs_method("insert",&Module::insert);
        add_varargs_method("getSimulation", &Module::getSimulation, "getSimulation(str)");
        add_noargs_method("getAllPlugins", &Module::getAllPlugins, "getAllPlugins()");
        add_varargs_method("makeFeature", &Module::makeFeature, "makeFeature()");
        add_varargs_method("installPlugin", &Module::installPlugin, "installPlugin()");
        add_varargs_method("unInstallPlugin", &Module::unInstallPlugin, "unInstallPlugin()");
        
        initialize("This module is the UserLab module."); // register with Python
    }

    virtual ~Module() {}

private:
    Py::Object open(const Py::Tuple& args)
    {
        char* Name;
        if (!PyArg_ParseTuple(args.ptr(), "et","utf-8",&Name))
            throw Py::Exception();
        std::string EncodedName = std::string(Name);
        PyMem_Free(Name);

        //Base::Console().Log("Open in Part with %s",Name);
        Base::FileInfo file(EncodedName.c_str());

        // extract extension
        if (file.extension().empty())
            throw Py::RuntimeError("No file extension");

        throw Py::RuntimeError("Unknown file extension");
      //return Py::None();
    }

    Py::Object insert(const Py::Tuple& args)
    {
        char* Name;
        const char* DocName;
        if (!PyArg_ParseTuple(args.ptr(), "ets","utf-8",&Name,&DocName))
            throw Py::Exception();
        std::string EncodedName = std::string(Name);
        PyMem_Free(Name);

        try {
            //Base::Console().Log("Insert in Part with %s",Name);
            Base::FileInfo file(EncodedName.c_str());

            // extract extension
            if (file.extension().empty())
                throw Py::RuntimeError("No file extension");

            App::Document *pcDoc = App::GetApplication().getDocument(DocName);
            if (!pcDoc) {
                pcDoc = App::GetApplication().newDocument(DocName);
            }
        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }
        return Py::None();
    }

    Py::Object getSimulation(const Py::Tuple& args)
    {
        char* psName;
        if (!PyArg_ParseTuple(args.ptr(), "s", &psName))
            throw Py::Exception();
        try {
            
            auto doc = App::GetApplication().getActiveDocument();
            if (!doc) {
                Base::Console().Warning("No valid active document found.\n");
                return Py::Object();
            }

            UserLab::UserLabSimulation* sim = static_cast<UserLab::UserLabSimulation*>(doc->getObject(psName));
            if (!sim)
                throw Py::RuntimeError("Simulation not found.");

            if (!sim->getTypeId().isDerivedFrom(UserLab::UserLabSimulation::getClassTypeId()))
                throw Py::RuntimeError("Simulation not found.");
            
             return Py::asObject(sim->getPyObject());           

        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }
        return Py::None();
    }
    

    Py::Object Module::makeFeature(const Py::Tuple& args)
    {
        char* featureTypeName;
        char* simulationName;
        char* featureName;
        char* featureGroup;

        if (!PyArg_ParseTuple(args.ptr(), "ssss",&featureName, &simulationName,  &featureTypeName, &featureGroup))
        throw Py::Exception();

    try {

        auto doc = App::GetApplication().getActiveDocument();
        if (!doc) {
           Base::Console().Warning("No valid active document found.\n");
           return Py::Object();
        }

        UserLab::UserLabSimulation* parentSimulation = static_cast<UserLab::UserLabSimulation*>(doc->getObject(simulationName));
        if (!parentSimulation)
           throw Py::RuntimeError("Parent simulation not found.");

        if (!parentSimulation->getTypeId().isDerivedFrom(UserLab::UserLabSimulation::getClassTypeId())) 
              throw Py::RuntimeError("Parent simulation not found.");

        App::DocumentObject* feat = parentSimulation->addFeature(featureName, simulationName, featureTypeName, featureGroup);
        if (!feat)
              throw Py::RuntimeError("Feature creation fails.");
        return Py::asObject(feat->getPyObject());
	 }
    catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }
    return Py::Object();
    }

    Py::Object getAllPlugins()
    {
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("UserLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("UserLabWorkbench"));

    QString phenomenon = UserLabUtils::rpsPhenomenonWindVelocity;

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

    std::map<QString, App::PluginDescription*>::iterator it;
    Py::List list;
    for (it = App::PluginManager::GetInstance().GetPluginDescriptionsMap().begin();
         it != App::PluginManager::GetInstance().GetPluginDescriptionsMap().end(); ++it) {
        list.append(Py::String(it->second->name.toUtf8().constData()));
    }
    return Py::Object(list);
    }

    Py::Object Module::installPlugin(const Py::Tuple& args)
    {
    char* psName;
    if (!PyArg_ParseTuple(args.ptr(), "s", &psName))
        throw Py::Exception();
    bool ok = false;

    try {
       
    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
       
    }
    else if (PlugLang == "C++") {
     
   std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("UserLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("UserLabWorkbench"));

    QString phenomenon = UserLabUtils::rpsPhenomenonWindVelocity;

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

	auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[QString::fromLatin1(psName)];
    
    if (!InstallingPluginDescription)
    return Py::Boolean(ok);

	QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
    QString info;

	ok = App::PluginManager::GetInstance().InitializePlugin(InstallingPluginFullPath, 1, info);
    if (!ok)
    {
        return Py::Boolean(ok);
    }

    ok = App::PluginManager::GetInstance().InitializePluginType(InstallingPluginFullPath, 1);
    if (!ok)
    {
        return Py::Boolean(ok);
    }

    ok = App::PluginManager::GetInstance().InstallPlugin(QString::fromLatin1(psName));
    }
    }
    catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }
    return Py::Boolean(ok);

}

Py::Object Module::unInstallPlugin(const Py::Tuple& args)
{
  char* psName;
    if (!PyArg_ParseTuple(args.ptr(), "s", &psName))
        throw Py::Exception();
    bool ok = false;

    try {
       
    std::string PlugLang = "C++";
    PlugLang = App::GetApplication()
                   .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                   ->GetASCII("PluginProgrammingLanguage", PlugLang.c_str());

    if (PlugLang == "Python") {
       
    }
    else if (PlugLang == "C++") {
     
    std::string pluginSourcePath = "";
    int pluginSource = 0;

	pluginSource = App::Application::getUserPluginSource(pluginSourcePath);

	// get the path the plugin folder
	QString localPluginPath = App::PluginManager::GetInstance().GetPluginLacotionPath(QString::fromLatin1("UserLabWorkbench"));
    QString onlinePluginPath = App::PluginManager::GetInstance().GetOnlinePluginLacotionPath(QString::fromLatin1("UserLabWorkbench"));

    QString phenomenon = UserLabUtils::rpsPhenomenonWindVelocity;

	if (pluginSource == 1)
	{
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
	}
    if (pluginSource == 2) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 3) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(localPluginPath, phenomenon, 1);
        App::PluginManager::GetInstance().SearchForAllPlugins(onlinePluginPath, phenomenon, 2);
    }
    if (pluginSource == 4) {
        App::PluginManager::GetInstance().GetPluginDescriptionsMap().clear();
        App::PluginManager::GetInstance().SearchForAllPlugins(QString::fromLatin1(pluginSourcePath.c_str()), phenomenon, 3);
    }

	auto InstallingPluginDescription = App::PluginManager::GetInstance().GetPluginDescriptionsMap()[QString::fromLatin1(psName)];
    
    if (!InstallingPluginDescription)
    return Py::Boolean(ok);

	QString InstallingPluginFullPath = InstallingPluginDescription->fullPath;
    QString info;

    ok = App::PluginManager::GetInstance().UnInstallPlugin(QString::fromLatin1(psName));
    }
    }
    catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }

    return Py::Boolean(ok);
}

};

/// @cond DOXERR
PyObject* initModule()
{
    return Base::Interpreter().addModule(new Module);
}
/// @endcond

} // namespace UserLab
