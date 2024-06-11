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

#include "DlgPluginImp.h"
#include "ui_DlgPlugin.h"
#include <App/Application.h>


using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgPluginImp */

/**
 *  Constructs a DlgPluginImp which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgPluginImp::DlgPluginImp( QWidget* parent )
  : PreferencePage(parent)
  , ui(new Ui_DlgPlugin)
{
    ui->setupUi(this);

        if (ui->customPluginPath->fileName().isEmpty()) {
        QDir d(QString::fromUtf8(App::GetApplication().getUserPluginDir().c_str()));
        ui->customPluginPath->setFileName(d.path());
    }
}

/**
 *  Destroys the object and frees any allocated resources
 */
DlgPluginImp::~DlgPluginImp()
{
}

void DlgPluginImp::saveSettings()
{
    ui->radioButtonLocal->onSave();
    ui->radioButtonOnline->onSave();
    ui->radioButtonLocalAndOnline->onSave();
    ui->radioButtonCustomLocation->onSave();
    ui->customPluginPath->onSave();

    
}

void DlgPluginImp::loadSettings()
{
    ui->radioButtonLocal->onRestore();
    ui->radioButtonOnline->onRestore();
    ui->radioButtonLocalAndOnline->onRestore();
    ui->radioButtonCustomLocation->onRestore();
    ui->customPluginPath->onRestore();

}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgPluginImp::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgPluginImp.cpp"
