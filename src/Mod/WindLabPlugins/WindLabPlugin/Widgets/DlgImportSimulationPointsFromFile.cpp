
/***************************************************************************
 *   Copyright (c) 2024 Koffi Daniel <kfdani@labrps.com>                   *
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

#include "DlgImportSimulationPointsFromFile.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgImportSimulationPointsFromFile.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSImportSimulationPointsFromFile.h>
#include <App/Application.h>
#include <App/Document.h>

#include <QSignalMapper>
#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>

using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgImportSimulationPointsFromFile */

DlgImportSimulationPointsFromFile::DlgImportSimulationPointsFromFile(const App::PropertyString& WorkingDirectory, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgImportSimulationPointsFromFile), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->le_working_dir->setText(WorkingDirectory.getValue());
    workingDirectory = "";

    connect(ui->tb_choose_working_dir, &QPushButton::clicked, this, &DlgImportSimulationPointsFromFile::slotSetWorkingDirectory);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgImportSimulationPointsFromFile::~DlgImportSimulationPointsFromFile()
{
}

void DlgImportSimulationPointsFromFile::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CRPSImportSimulationPointsFromFile* activefeature = static_cast<WindLab::CRPSImportSimulationPointsFromFile*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->WorkingDirectory.setValue(ui->le_working_dir->text().toStdString());

  }

void DlgImportSimulationPointsFromFile::reject()
{

}

void DlgImportSimulationPointsFromFile::slotSetWorkingDirectory() 
{
  QString filter = "Text files (*.txt)";

  QString fn = QFileDialog::getOpenFileName(0,"Import random phases from file", workingDirectory, filter);
  if (!fn.isEmpty()) {
    QFileInfo fi(fn);
      workingDirectory = fi.absoluteFilePath().toUtf8().constData();
    ui->le_working_dir->setText(workingDirectory);
  }
}
// ----------------------------------------------

/* TRANSLATOR PartGui::DlgImportSimulationPointsFromFileEdit */

DlgImportSimulationPointsFromFileEdit::DlgImportSimulationPointsFromFileEdit(const App::PropertyString& WorkingDirectory, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgImportSimulationPointsFromFile(WorkingDirectory, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgImportSimulationPointsFromFileEdit::~DlgImportSimulationPointsFromFileEdit()
{
	// automatically deleted in the sub-class
}


QDialogButtonBox::StandardButtons DlgImportSimulationPointsFromFileEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgImportSimulationPointsFromFileEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgImportSimulationPointsFromFileEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgImportSimulationPointsFromFile.cpp"
