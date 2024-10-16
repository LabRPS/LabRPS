/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *                *
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

#include <App/Application.h>

#include "DlgSettingsSeismicLabGeneralImp.h"
#include "ui_DlgSettingsSeismicLabGeneral.h"


using namespace SeismicLabGui;

DlgSettingsSeismicLabGeneralImp::DlgSettingsSeismicLabGeneralImp(QWidget* parent)
    : PreferencePage(parent)
    , ui(new Ui_DlgSettingsSeismicLabGeneralImp)
{
    ui->setupUi(this);

    connect(ui->chooser_lm_custom_working_dir, &Gui::PrefFileChooser::fileNameChanged, this, &DlgSettingsSeismicLabGeneralImp::onfileNameChanged);
}

DlgSettingsSeismicLabGeneralImp::~DlgSettingsSeismicLabGeneralImp()
{

}

void DlgSettingsSeismicLabGeneralImp::onfileNameChanged(QString FileName)
{
    
}

void DlgSettingsSeismicLabGeneralImp::saveSettings()
{
    ui->chooser_lm_custom_working_dir->onSave();
   
}

void DlgSettingsSeismicLabGeneralImp::loadSettings()
{
    ui->chooser_lm_custom_working_dir->onRestore();

}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsSeismicLabGeneralImp::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsSeismicLabGeneralImp.cpp"
