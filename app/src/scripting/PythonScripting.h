#ifndef PYTHON_SCRIPTING_H
#define PYTHON_SCRIPTING_H

#include "ScriptingEnv.h"
#include "PythonScript.h"

class QObject;
class QString;

typedef struct _object PyObject;

class PythonScripting: public ScriptingEnv
{
	Q_OBJECT

	public:
		static const char *langName;
		PythonScripting(ApplicationWindow *parent);
		~PythonScripting();
		static ScriptingEnv *constructor(ApplicationWindow *parent) { return new PythonScripting(parent); }
		bool initialize();

		void write(const QString &text) { emit print(text); }

		//! like str(object) in Python
		/**
		 * Convert object to a string.
		 * Steals a reference to object if decref is true; borrows otherwise.
		 */
		QString toString(PyObject *object, bool decref=false);
		//! evaluate a Python expression
		/**
		 * Evaluates code, using argDict (borrowed reference) as local dictionary
		 * or an empty one if argDict==NULL. name is the filename Python uses when
		 * reporting errors. Returns a new reference; NULL means caller has to do
		 * exception handling.
		 */
		PyObject* eval(const QString &code, PyObject *argDict=NULL, const char *name="<scidavis>");
		//! execute a sequence of Python statements
		/**
		 * Executes code, using argDict (borrowed reference) as local dictionary
		 * or an empty one if argDict==NULL. name is the filename Python uses when
		 * reporting errors. A false return value means caller has to do exception
		 * handling.
		 */
		bool exec(const QString &code, PyObject *argDict=NULL, const char *name="<scidavis>");
		QString errorMsg();

		bool isRunning() const;
		Script *newScript(const QString &code, QObject *context, const QString &name="<input>")
		{
			return new PythonScript(this, code, context, name);
		}

		bool setQObject(QObject*, const char*, PyObject *dict);
		bool setQObject(QObject *val, const char *name) { return setQObject(val,name,NULL); }
		bool setInt(int, const char*, PyObject *dict=NULL);
		bool setDouble(double, const char*, PyObject *dict=NULL);

		const QStringList mathFunctions() const;
		const QString mathFunctionDoc (const QString &name) const;
		const QStringList fileExtensions() const;

		PyObject *globalDict() { return globals; }
		PyObject *sysDict() { return sys; }

	private:
		bool loadInitFile(const QString &path);

		PyObject *globals;		// PyDict of global environment
		PyObject *math;		// PyDict of math functions
		PyObject *sys;		// PyDict of sys module
};

#endif
