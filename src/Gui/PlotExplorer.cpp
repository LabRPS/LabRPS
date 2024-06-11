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

#include "PreCompiled.h"
#ifndef _PreComp_
# include <QApplication>
# include <QDockWidget>
#endif


#include "PlotExplorer.h"
#include "Application.h"
#include "MainWindow.h"



using namespace Gui;

/* TRANSLATOR Gui::PlotExplorer */

/**
 *  Constructs a PlotExplorer which is a child of 'parent'.
 */
PlotExplorer::PlotExplorer(QWidget* parent) 
    : QWidget(parent), WindowParameter("Plotting")
{
    //this->setGeometry(QRect(30, 40, 779, 189));
    dockWidgetContents = new QWidget(this);
    dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
    explorerGridLayout = new QGridLayout(this);
    explorerGridLayout->setObjectName(QString::fromUtf8("explorerGridLayout"));
    explorerSplitter = new QSplitter(dockWidgetContents);
    explorerSplitter->setObjectName(QString::fromUtf8("explorerSplitter"));
    explorerSplitter->setOrientation(Qt::Horizontal);
    folderView = new FolderTreeWidget(explorerSplitter);
    QTreeWidgetItem* __qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
    folderView->setHeaderItem(__qtreewidgetitem);
    folderView->setObjectName(QString::fromUtf8("folderView"));
    explorerSplitter->addWidget(folderView);
    listView = new FolderTreeWidget(explorerSplitter);
    QTreeWidgetItem* __qtreewidgetitem1 = new QTreeWidgetItem();
    __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
    listView->setHeaderItem(__qtreewidgetitem1);
    listView->setObjectName(QString::fromUtf8("listView"));
    explorerSplitter->addWidget(listView);

    explorerGridLayout->addWidget(explorerSplitter, 0, 0, 1, 1);

    //this->dockWidgetContents->setWidget(dockWidgetContents);

}

/** Destroys the object and frees any allocated resources */
PlotExplorer::~PlotExplorer()
{

}



// -----------------------------------------------------

#include "moc_PlotExplorer.cpp"
