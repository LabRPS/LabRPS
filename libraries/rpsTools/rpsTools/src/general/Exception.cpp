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



#include <typeinfo>

#include "Exception.h"

using namespace rps;
using namespace ErrorHandling;



Exception::Exception()
  : _line(0)
  , _isTranslatable(false)
  , _isReported(false)
{
  _sErrMsg = "LabRPS Exception";
}

Exception::Exception(const Exception &inst)
  : _sErrMsg(inst._sErrMsg)
  , _file(inst._file)
  , _line(inst._line)
  , _function(inst._function)
  , _isTranslatable(inst._isTranslatable)
  , _isReported(inst._isReported)
{
}

Exception::Exception(const char * sMessage)
  : _sErrMsg(sMessage)
  , _line(0)
  , _isTranslatable(false)
  , _isReported(false)
{
}

Exception::Exception(const std::string& sMessage)
  : _sErrMsg(sMessage)
  , _line(0)
  , _isTranslatable(false)
  , _isReported(false)
{
}

Exception &Exception::operator=(const Exception &inst)
{
    _sErrMsg = inst._sErrMsg;
    _file = inst._file;
    _line = inst._line;
    _function = inst._function;
    return *this;
}

const char* Exception::what() const throw()
{
    return _sErrMsg.c_str();
}

const char* Exception::ReportException () const
{
    if (!_isReported) {
        const char *msg;
        if (_sErrMsg.empty())
        {
            msg = typeid(*this).name();
            return msg;
        }
        else
        {
            msg = _sErrMsg.c_str();
            return msg;
        }
        _isReported = true;
    }

    return NULL;

}

// ---------------------------------------------------------


AbortException::AbortException(const char * sMessage)
  : Exception( sMessage )
{
}

AbortException::AbortException()
{
    _sErrMsg = "Aborted operation";
}

const char* AbortException::what() const throw()
{
    return Exception::what();
}

// ---------------------------------------------------------


MemoryException::MemoryException()
{
    _sErrMsg = "Not enough memory available";
}

MemoryException::MemoryException(const MemoryException &inst)
#if defined (__GNUC__)
  : std::bad_alloc(), Exception(inst)
#else
  : Exception(inst)
#endif
{
}

MemoryException & MemoryException::operator=(const MemoryException &inst)
{
    Exception::operator = (inst);
    return *this;
}

#if defined (__GNUC__)
const char* MemoryException::what() const throw()
{
    // call what() of Exception, not of std::bad_alloc
    return Exception::what();
}
#endif

// ---------------------------------------------------------

AccessViolation::AccessViolation()
{
    _sErrMsg = "Access violation";
}

AccessViolation::AccessViolation(const char * sMessage)
  : Exception(sMessage)
{
}

AccessViolation::AccessViolation(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

AbnormalProgramTermination::AbnormalProgramTermination()
{
    _sErrMsg = "Abnormal program termination";
}

AbnormalProgramTermination::AbnormalProgramTermination(const char * sMessage)
  : Exception(sMessage)
{
}

AbnormalProgramTermination::AbnormalProgramTermination(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

UnknownProgramOption::UnknownProgramOption()
  : Exception()
{
}

UnknownProgramOption::UnknownProgramOption(const char * sMessage)
  : Exception(sMessage)
{
}

UnknownProgramOption::UnknownProgramOption(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

ProgramInformation::ProgramInformation()
  : Exception()
{
}

ProgramInformation::ProgramInformation(const char * sMessage)
  : Exception(sMessage)
{
}

ProgramInformation::ProgramInformation(const std::string& sMessage)
  : Exception(sMessage)
{
}



// ---------------------------------------------------------

ValueError::ValueError()
  : Exception()
{
}

ValueError::ValueError(const char * sMessage)
  : Exception(sMessage)
{
}

ValueError::ValueError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

IndexError::IndexError()
  : Exception()
{
}

IndexError::IndexError(const char * sMessage)
  : Exception(sMessage)
{
}

IndexError::IndexError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

NameError::NameError()
  : Exception()
{
}

NameError::NameError(const char * sMessage)
  : Exception(sMessage)
{
}

NameError::NameError(const std::string& sMessage)
  : Exception(sMessage)
{
}


// ---------------------------------------------------------

ImportError::ImportError()
  : Exception()
{
}

ImportError::ImportError(const char * sMessage)
  : Exception(sMessage)
{
}

ImportError::ImportError(const std::string& sMessage)
  : Exception(sMessage)
{
}


// ---------------------------------------------------------

AttributeError::AttributeError()
  : Exception()
{
}

AttributeError::AttributeError(const char * sMessage)
  : Exception(sMessage)
{
}

AttributeError::AttributeError(const std::string& sMessage)
  : Exception(sMessage)
{
}


// ---------------------------------------------------------

RuntimeError::RuntimeError()
  : Exception()
{
}

RuntimeError::RuntimeError(const char * sMessage)
  : Exception(sMessage)
{
}

RuntimeError::RuntimeError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

BadGraphError::BadGraphError()
  : RuntimeError("The graph must be a DAG.")
{
}

BadGraphError::BadGraphError(const char * sMessage)
  : RuntimeError(sMessage)
{
}

BadGraphError::BadGraphError(const std::string& sMessage)
  : RuntimeError(sMessage)
{
}

// ---------------------------------------------------------

NotImplementedError::NotImplementedError()
  : Exception()
{
}

NotImplementedError::NotImplementedError(const char * sMessage)
  : Exception(sMessage)
{
}

NotImplementedError::NotImplementedError(const std::string& sMessage)
  : Exception(sMessage)
{
}


// ---------------------------------------------------------

ZeroDivisionError::ZeroDivisionError()
  : Exception()
{
}

ZeroDivisionError::ZeroDivisionError(const char * sMessage)
  : Exception(sMessage)
{
}

ZeroDivisionError::ZeroDivisionError(const std::string& sMessage)
  : Exception(sMessage)
{
}


// ---------------------------------------------------------

ReferenceError::ReferenceError()
: Exception()
{
}

ReferenceError::ReferenceError(const char * sMessage)
  : Exception(sMessage)
{
}

ReferenceError::ReferenceError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

OverflowError::OverflowError()
  : Exception()
{
}

OverflowError::OverflowError(const char * sMessage)
  : Exception(sMessage)
{
}

OverflowError::OverflowError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// ---------------------------------------------------------

UnderflowError::UnderflowError()
  : Exception()
{
}

UnderflowError::UnderflowError(const char * sMessage)
  : Exception(sMessage)
{
}

UnderflowError::UnderflowError(const std::string& sMessage)
  : Exception(sMessage)
{
}


// ---------------------------------------------------------

RestoreError::RestoreError()
  : Exception()
{
}

RestoreError::RestoreError(const char * sMessage)
  : Exception(sMessage)
{
}

RestoreError::RestoreError(const std::string& sMessage)
  : Exception(sMessage)
{
}


