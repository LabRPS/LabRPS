#include "ScriptingEnv.h"

#include <string.h>

#include "Script.h"

#ifdef SCRIPTING_MUPARSER
#include "MuParserScript.h"
#include "MuParserScripting.h"
#endif

ScriptingEnv::ScriptingEnv(ApplicationWindow *parent, const char *langName)
    : QObject(nullptr), d_parent(parent) {
  setObjectName(langName);
  d_initialized = false;
  d_refcount = 0;
}

const QString ScriptingEnv::fileFilter() const {
  QStringList extensions = fileExtensions();
  if (extensions.isEmpty())
    return "";
  else
    return tr("%1 Source (*.%2);;")
        .arg(objectName())
        .arg(extensions.join(" *."));
}

void ScriptingEnv::incref() { d_refcount++; }

void ScriptingEnv::decref() {
  d_refcount--;
  if (d_refcount == 0) delete this;
}
