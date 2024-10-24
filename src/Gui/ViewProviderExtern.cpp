/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
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

#include "PreCompiled.h"

#ifndef _PreComp_
# include <cstring>

#endif

#include <Base/Exception.h>
#include <Base/Stream.h>

#include "ViewProviderExtern.h"


using std::vector;
using std::string;


using namespace Gui;

PROPERTY_SOURCE(Gui::ViewProviderExtern, Gui::ViewProvider)


ViewProviderExtern::ViewProviderExtern()
{

}

ViewProviderExtern::~ViewProviderExtern()
{

}

void ViewProviderExtern::setModeByString(const char* name, const char* ivFragment)
{

}

void ViewProviderExtern::setModeByFile(const char* name, const char* ivFileName)
{
    Base::ifstream file(ivFileName, std::ios::in | std::ios::binary);
    if (file){
        std::streamoff size = 0;
        std::streambuf* buf = file.rdbuf();
        if (buf) {
            std::streamoff curr;
            curr = buf->pubseekoff(0, std::ios::cur, std::ios::in);
            size = buf->pubseekoff(0, std::ios::end, std::ios::in);
            buf->pubseekoff(curr, std::ios::beg, std::ios::in);
        }

        // read in the file
        std::vector<unsigned char> content;
        content.reserve(size);
        unsigned char c;
        while (file.get((char&)c)) {
            content.push_back(c);
        }

        file.close();
    }
}


void ViewProviderExtern::adjustDocumentName(const char* docname)
{
   
}

const char* ViewProviderExtern::getDefaultDisplayMode() const
{
    // returns the first item of the available modes
    return (modes.empty() ? "" : modes.front().c_str());
}

std::vector<std::string> ViewProviderExtern::getDisplayModes() const
{
    return modes;
}
