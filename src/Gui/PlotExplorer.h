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

#ifndef GUI_PLOTEXPLORER_H
#define GUI_PLOTEXPLORER_H

#include <QWidget>
#include <QGridLayout>
#include <QHeaderView>
#include <QSplitter>
#include <QWidget>


#include "Window.h"
#include <RPSGlobal.h>
#include <Libraries/Alphaplot/Folder.h>

namespace Gui {


/**
 * DockWind for exploring table, matrix, and plots.
 * @author Koffi Daniel
 */
class GuiExport PlotExplorer: public QWidget, public WindowParameter
{
    Q_OBJECT

public:

    PlotExplorer(QWidget* parent = nullptr);
    ~PlotExplorer();

    //These members should be private
    QWidget* dockWidgetContents;
    QGridLayout* explorerGridLayout;
    QSplitter* explorerSplitter;
    FolderTreeWidget* folderView;
    FolderTreeWidget* listView;
};


} // namespace Gui

#endif // GUI_PLOTEXPLORER_H
