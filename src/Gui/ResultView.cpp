/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
#ifndef _PreComp_
# include <QApplication>
# include <QDockWidget>
#endif


#include "ResultView.h"

using namespace Gui;

/* TRANSLATOR Gui::ResultView */

/**
 *  Constructs a ResultView which is a child of 'parent'.
 */
ResultView::ResultView(QWidget* parent) 
    : QWidget(parent), WindowParameter("Result")
{
    dockWidgetContents = new QWidget(this);
    dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
    gridLayout = new QGridLayout(this);
    editor = new QTextEdit(dockWidgetContents);
    gridLayout->addWidget(editor, 0, 0, 1, 1);
}

/** Destroys the object and frees any allocated resources */
ResultView::~ResultView()
{

}


// -----------------------------------------------------

#include "moc_ResultView.cpp"
