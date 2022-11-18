#include "ScriptingEnv.h"
#include "Script.h"

#include <string.h>

#ifdef SCRIPTING_MUPARSER
#include "MuParserScript.h"
#include "MuParserScripting.h"
#endif

ScriptingLangManager::ScriptingLang ScriptingLangManager::langs[] = {
#ifdef SCRIPTING_MUPARSER
    {MuParserScripting::langName, MuParserScripting::constructor},
#endif
    {nullptr, nullptr}};

ScriptingEnv *ScriptingLangManager::newEnv(ApplicationWindow *parent) {
  if (!langs[0].constructor)
    return nullptr;
  else
    return langs[0].constructor(parent);
}

ScriptingEnv *ScriptingLangManager::newEnv(const char *name,
                                           ApplicationWindow *parent) {
  for (ScriptingLang *i = langs; i->constructor; i++)
    if (!strcmp(name, i->name)) return i->constructor(parent);
  return nullptr;
}

QStringList ScriptingLangManager::languages() {
  QStringList l;
  for (ScriptingLang *i = langs; i->constructor; i++) l << i->name;
  return l;
}

bool Script::compile(bool for_eval) {
  Q_UNUSED(for_eval);
  emit_error("Script::compile called!", 0);
  return false;
}

QVariant Script::eval() {
  emit_error("Script::eval called!", 0);
  return QVariant();
}

bool Script::exec() {
  emit_error("Script::exec called!", 0);
  return false;
}

scripted::scripted(ScriptingEnv *env) {
  env->incref();
  scriptEnv = env;
}

scripted::~scripted() { scriptEnv->decref(); }

void scripted::scriptingChangeEvent(ScriptingChangeEvent *sce) {
  scriptEnv->decref();
  sce->scriptingEnv()->incref();
  scriptEnv = sce->scriptingEnv();
}
