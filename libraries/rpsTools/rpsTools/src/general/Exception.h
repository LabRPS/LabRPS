/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License (LGPL)   *
 *   as published by the Free Software Foundation; either version 2 of     *
 *   the License, or (at your option) any later version.                   *
 *   for detail see the LICENCE text file.                                 *
 *                                                                         *
 *   LabRPS is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with LabRPS; if not, write to the Free Software        *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>
#include <csignal>
#include "rpsTools/RPSToolsDefines.h"

/* MACROS FOR THROWING EXCEPTIONS */

/// the macros do NOT mark any message for translation
/// If you want to mark text for translation, use the QT_TRANSLATE_NOOP macro
/// with the context "Exceptions" and the right throwing macro from below (the one ending in T)
/// example:
/// THROWMT(Base::ValueError,QT_TRANSLATE_NOOP("Exceptions","The multiplicity cannot be increased beyond the degree of the B-Spline."));
///
/// N.B.: The QT_TRANSLATE_NOOP macro won't translate your string. It will just allow lupdate to identify that string for translation so that
/// if you ask for a translation (and the translator have provided one) at that time it gets translated (e.g. in the UI before showing the message
/// of the exception).

#ifdef _MSC_VER

# define THROW(exception) {exception myexcp; myexcp.setDebugInformation(__FILE__,__LINE__,__FUNCSIG__); throw myexcp;}
# define THROWM(exception, message) {exception myexcp(message); myexcp.setDebugInformation(__FILE__,__LINE__,__FUNCSIG__); throw myexcp;}
# define THROWMF_FILEEXCEPTION(message,filenameorfileinfo) {FileException myexcp(message, filenameorfileinfo); myexcp.setDebugInformation(__FILE__,__LINE__,__FUNCSIG__); throw myexcp;}

# define THROWT(exception) {exception myexcp; myexcp.setDebugInformation(__FILE__,__LINE__,__FUNCSIG__); myexcp.setTranslatable(true); throw myexcp;}
# define THROWMT(exception, message) {exception myexcp(message); myexcp.setDebugInformation(__FILE__,__LINE__,__FUNCSIG__); myexcp.setTranslatable(true); throw myexcp;}
# define THROWMFT_FILEEXCEPTION(message,filenameorfileinfo) {FileException myexcp(message, filenameorfileinfo); myexcp.setDebugInformation(__FILE__,__LINE__,__FUNCSIG__); myexcp.setTranslatable(true); throw myexcp;}

#elif defined(__GNUC__)

# define THROW(exception) {exception myexcp; myexcp.setDebugInformation(__FILE__,__LINE__,__PRETTY_FUNCTION__); throw myexcp;}
# define THROWM(exception, message) {exception myexcp(message); myexcp.setDebugInformation(__FILE__,__LINE__,__PRETTY_FUNCTION__); throw myexcp;}
# define THROWMF_FILEEXCEPTION(message,filenameorfileinfo) {FileException myexcp(message, filenameorfileinfo); myexcp.setDebugInformation(__FILE__,__LINE__,__PRETTY_FUNCTION__); throw myexcp;}

# define THROWT(exception) {exception myexcp; myexcp.setDebugInformation(__FILE__,__LINE__,__PRETTY_FUNCTION__); myexcp.setTranslatable(true); throw myexcp;}
# define THROWMT(exception, message) {exception myexcp(message); myexcp.setDebugInformation(__FILE__,__LINE__,__PRETTY_FUNCTION__); myexcp.setTranslatable(true); throw myexcp;}
# define THROWMFT_FILEEXCEPTION(message,filenameorfileinfo) {FileException myexcp(message, filenameorfileinfo); myexcp.setDebugInformation(__FILE__,__LINE__,__PRETTY_FUNCTION__); myexcp.setTranslatable(true); throw myexcp;}

#else

# define THROW(exception) {exception myexcp; myexcp.setDebugInformation(__FILE__,__LINE__,__func__); throw myexcp;}
# define THROWM(exception, message) {exception myexcp(message); myexcp.setDebugInformation(__FILE__,__LINE__,__func__); throw myexcp;}
# define THROWMF_FILEEXCEPTION(message,filenameorfileinfo) {FileException myexcp(message, filenameorfileinfo); myexcp.setDebugInformation(__FILE__,__LINE__,__func__);  throw myexcp;}

# define THROWT(exception) {exception myexcp; myexcp.setDebugInformation(__FILE__,__LINE__,__func__); myexcp.setTranslatable(true); throw myexcp;}
# define THROWMT(exception, message) {exception myexcp(message); myexcp.setDebugInformation(__FILE__,__LINE__,__func__); myexcp.setTranslatable(true); throw myexcp;}
# define THROWMFT_FILEEXCEPTION(message,filenameorfileinfo) {FileException myexcp(message, filenameorfileinfo); myexcp.setDebugInformation(__FILE__,__LINE__,__func__); myexcp.setTranslatable(true); throw myexcp;}


#endif

#define RPS_THROWM(_exception,_msg) do {\
    std::stringstream ss;\
    ss << _msg;\
    THROWM(_exception,ss.str().c_str());\
}while(0)

namespace rps{

    namespace ErrorHandling
    {

    class RPS_TOOLS_EXPORT Exception
    {
    public:

      virtual ~Exception() throw() {}

      Exception &operator=(const Exception &inst);

      virtual const char* what() const throw();

      /// Reports exception. It includes a mechanism to only report an exception once.
      virtual const char* ReportException () const;

      inline void setMessage(const char * sMessage);
      inline void setMessage(const std::string& sMessage);
      // what may differ from the message given by the user in
      // derived classes
      inline std::string getMessage() const;
      inline std::string getFile() const;
      inline int getLine() const;
      inline std::string getFunction() const;
      inline bool getTranslatable() const;
      inline bool getReported() const { return _isReported; }

      /// setter methods for including debug information
      /// intended to use via macro for autofilling of debugging information
      inline void setDebugInformation(const std::string & file, const int line, const std::string & function);

      inline void setTranslatable(bool translatable);

      inline void setReported(bool reported) { _isReported = reported; }

    protected:
     /* sMessage may be:
      * - a UI compliant string susceptible to being translated and shown to the user in the UI
      * - a very technical message not intended to be translated or shown to the user in the UI
      * The preferred way of throwing an exception is using the macros above.
      * This way, the file, line, and function are automatically inserted. */
      Exception(const char * sMessage);
      Exception(const std::string& sMessage);
      Exception();
      Exception(const Exception &inst);

    protected:
      std::string _sErrMsg;
      std::string _file;
      int _line;
      std::string _function;
      bool _isTranslatable;
      mutable bool _isReported;
    };


    /**
     * The AbortException is thrown if a pending operation was aborted.
     * @author Werner Mayer
     */
    class AbortException : public Exception
    {
    public:
      /// Construction
      AbortException(const char * sMessage);
      /// Construction
      AbortException();

      /// Destruction
      virtual ~AbortException() throw() {}
      /// Description of the exception
      virtual const char* what() const throw();
    };

    /**
     * The MemoryException is thrown if not enough memory can be allocated.
     * @author Werner Mayer
     */
    #if defined (__GNUC__)
    // It seems that the calling instance of our new handler expects a bad_alloc exception
    class RPS_TOOLS_EXPORT MemoryException : public Exception, virtual public std::bad_alloc
    #else
    class BaseExport MemoryException : public Exception
    #endif
    {
    public:
      /// Construction
      MemoryException();
      /// Construction
      MemoryException(const MemoryException &inst);
      /// Destruction
      virtual ~MemoryException() throw() {}
      /// Assignment operator
      MemoryException &operator=(const MemoryException &inst);
    #if defined (__GNUC__)
      /// Description of the exception
      virtual const char* what() const throw() override;
    #endif
    };

    /**
     * The AccessViolation can be used in an own signal handler.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT AccessViolation : public Exception
    {
    public:
      /// Construction
      AccessViolation();
      AccessViolation(const char * sMessage);
      AccessViolation(const std::string& sMessage);
      /// Destruction
      virtual ~AccessViolation() throw() {}
    };

    /**
     * The AbnormalProgramTermination can be used in an own signal handler.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT AbnormalProgramTermination : public Exception
    {
    public:
      /// Construction
      AbnormalProgramTermination();
      /// Construction
      AbnormalProgramTermination(const char * sMessage);
      AbnormalProgramTermination(const std::string& sMessage);
      /// Destruction
      virtual ~AbnormalProgramTermination() throw() {}
    };

    /**
     * The UnknownProgramOption can be used to indicate an unknown program option.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT UnknownProgramOption : public Exception
    {
    public:
      /// Construction
      UnknownProgramOption();
      UnknownProgramOption(const char * sMessage);
      UnknownProgramOption(const std::string& sMessage);
      /// Destruction
      virtual ~UnknownProgramOption() throw() {}
    };

    /**
     * The ProgramInformation can be used to show information about the program.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT ProgramInformation : public Exception
    {
    public:
      /// Construction
      ProgramInformation();
      ProgramInformation(const char * sMessage);
      ProgramInformation(const std::string& sMessage);

      /// Destruction
      virtual ~ProgramInformation() throw() {}
    };


    /**
     * The ValueError can be used to indicate the usage of a wrong value.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT ValueError : public Exception
    {
    public:
      /// Construction
      ValueError();
      ValueError(const char * sMessage);
      ValueError(const std::string& sMessage);
      /// Destruction
      virtual ~ValueError() throw() {}
    };

    /**
     * The IndexError can be used when a sequence subscript is out of range.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT IndexError : public Exception
    {
    public:
      /// Construction
      IndexError();
      IndexError(const char * sMessage);
      IndexError(const std::string& sMessage);
      /// Destruction
      virtual ~IndexError() throw() {}
    };

    class RPS_TOOLS_EXPORT NameError : public Exception
    {
    public:
      /// Construction
      NameError();
      NameError(const char * sMessage);
      NameError(const std::string& sMessage);
      /// Destruction
      virtual ~NameError() throw() {}
    };

    class RPS_TOOLS_EXPORT ImportError : public Exception
    {
    public:
      /// Construction
      ImportError();
      ImportError(const char * sMessage);
      ImportError(const std::string& sMessage);
      /// Destruction
      virtual ~ImportError() throw() {}
    };

    /**
     * The AttributeError can be used to indicate the usage of a wrong value.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT AttributeError : public Exception
    {
    public:
      /// Construction
      AttributeError();
      AttributeError(const char * sMessage);
      AttributeError(const std::string& sMessage);
      /// Destruction
      virtual ~AttributeError() throw() {}
    };

    /**
     * The RuntimeError can be used to indicate an unknown exception at runtime.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT RuntimeError : public Exception
    {
    public:
      /// Construction
      RuntimeError();
      RuntimeError(const char * sMessage);
      RuntimeError(const std::string& sMessage);
      /// Destruction
      virtual ~RuntimeError() throw() {}
    };

    /**
     * The BadGraphError can be used to indicate that a graph is e.g. not a DAG.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT BadGraphError : public RuntimeError
    {
    public:
      /// Construction
      BadGraphError();
      BadGraphError(const char * sMessage);
      BadGraphError(const std::string& sMessage);
      /// Destruction
      virtual ~BadGraphError() throw() {}
    };

    /**
     * The NotImplementedError can be used to indicate that an invoked function is not implemented.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT NotImplementedError : public Exception
    {
    public:
      /// Construction
      NotImplementedError();
      NotImplementedError(const char * sMessage);
      NotImplementedError(const std::string& sMessage);
      /// Destruction
      virtual ~NotImplementedError() throw() {}
    };

    /**
     * The ZeroDivisionError can be used to indicate a division by zero.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT ZeroDivisionError : public Exception
    {
    public:
      /// Construction
      ZeroDivisionError();
      ZeroDivisionError(const char * sMessage);
      ZeroDivisionError(const std::string& sMessage);
      /// Destruction
      virtual ~ZeroDivisionError() throw() {}
    };

    /**
     * The ReferenceError can be used to indicate a reference counter has the wrong value.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT ReferenceError : public Exception
    {
    public:
      /// Construction
      ReferenceError();
      ReferenceError(const char * sMessage);
      ReferenceError(const std::string& sMessage);
      /// Destruction
      virtual ~ReferenceError() throw() {}
    };

    /**
     * The ExpressionError can be used to indicate erroneous.input
     * to the expression engine.
     * @author Werner Mayer
     */

    /**
     * The OverflowError can be used to indicate overflows of numbers.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT OverflowError : public Exception
    {
    public:
      /// Construction
      OverflowError();
      OverflowError(const char * sMessage);
      OverflowError(const std::string& sMessage);
      /// Destruction
      virtual ~OverflowError() throw() {}
    };

    /**
     * The UnderflowError can be used to indicate underflows of numbers.
     * @author Werner Mayer
     */
    class RPS_TOOLS_EXPORT UnderflowError : public Exception
    {
    public:
      /// Construction
      UnderflowError();
      UnderflowError(const char * sMessage);
      UnderflowError(const std::string& sMessage);
      /// Destruction
      virtual ~UnderflowError() throw() {}
    };


    /* The RestoreError can be used to try to do a best recovery effort when an error during restoring
     * occurs. The best recovery effort may be to ignore the element altogether or to insert a placeholder
     * depending on where the actual element being restored is used.
     *
     * For example, if it is part of an array (e.g. PropertyList) and the order in the array is relevant, it
     * is better to have a placeholder than to fail to restore the whole array.
     */
    class RPS_TOOLS_EXPORT RestoreError : public Exception
    {
    public:
        /// Construction
        RestoreError();
        RestoreError(const char * sMessage);
        RestoreError(const std::string& sMessage);
        /// Destruction
        virtual ~RestoreError() throw() {}
    };



    inline void Exception::setMessage(const char * sMessage)
    {
      _sErrMsg = sMessage;
    }

    inline void Exception::setMessage(const std::string& sMessage)
    {
      _sErrMsg = sMessage;
    }

    inline std::string Exception::getMessage() const
    {
        return _sErrMsg;
    }

    inline std::string Exception::getFile() const
    {
        return _file;
    }

    inline int Exception::getLine() const
    {
        return _line;
    }

    inline std::string Exception::getFunction() const
    {
        return _function;
    }

    inline bool Exception::getTranslatable() const
    {
        return _isTranslatable;
    }

    inline void Exception::setDebugInformation(const std::string & file, const int line, const std::string & function)
    {
        _file = file;
        _line = line;
        _function = function;
    }

    inline void Exception::setTranslatable(bool translatable)
    {
        _isTranslatable = translatable;
    }

    } //namespace Base


}
#endif // BASE_EXCEPTION_H
