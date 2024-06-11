/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS development system.              *
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

#ifndef GUI_RESULTVIEW_H
#define GUI_RESULTVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>


#include "Window.h"
#include <RPSGlobal.h>

namespace Gui {


/**
 * DockWind for showing calculation results.
 * @author Koffi Daniel
 */
class GuiExport ResultView: public QWidget, public WindowParameter
{
    Q_OBJECT

public:

    ResultView(QWidget* parent = nullptr);
    ~ResultView();

    //These members should be private
    QWidget* dockWidgetContents;
    QGridLayout* gridLayout;
    QTextEdit* editor;
};


} // namespace Gui

#endif // GUI_PLOTEXPLORER_H
