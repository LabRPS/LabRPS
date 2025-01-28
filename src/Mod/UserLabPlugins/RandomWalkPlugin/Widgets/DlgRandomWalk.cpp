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

#include "DlgRandomWalk.h"
#include <Mod/UserLabPlugins/RandomWalkPlugin/ui_DlgRandomWalk.h>
#include <Mod/UserLabPlugins/RandomWalkPlugin/RPSRandomWalk.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace UserLabGui;

/* TRANSLATOR UserLabGui::DlgRandomWalk */

DlgRandomWalk::DlgRandomWalk(const App::PropertyInteger& TotalSteps,
                  const App::PropertyInteger& NumberOfWalker,
                  const App::PropertyBool& MovePattern,
                  const App::PropertyBool& RandomStart,
                       const App::PropertyString& featureName, 
                       QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgRandomWalk), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);


    ui->spinBox_TotalSteps->setValue(TotalSteps.getValue());
    ui->spinBox_NumberOfWalker->setValue(NumberOfWalker.getValue());
    ui->checkBox_MovePattern->setChecked(MovePattern.getValue());
    ui->checkBox_RandomStart->setChecked(RandomStart.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSPowerLowProfile.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgRandomWalk::~DlgRandomWalk()
{
}

void DlgRandomWalk::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    UserLab::CRPSRandomWalk* activefeature = static_cast<UserLab::CRPSRandomWalk*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

     activefeature->TotalSteps.setValue(ui->spinBox_TotalSteps->value());
     activefeature->NumberOfWalker.setValue(ui->spinBox_NumberOfWalker->value());
     activefeature->MovePattern.setValue(ui->checkBox_MovePattern->isChecked());
     activefeature->RandomStart.setValue(ui->checkBox_RandomStart->isChecked());

  }

void DlgRandomWalk::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgRandomWalkEdit */

DlgRandomWalkEdit::DlgRandomWalkEdit(const App::PropertyInteger& TotalSteps,
                  const App::PropertyInteger& NumberOfWalker,
                  const App::PropertyBool& MovePattern,
                  const App::PropertyBool& RandomStart,
    const App::PropertyString& featureName)
{
	// create and show dialog for the UserLabFeatures
    widget = new DlgRandomWalk(TotalSteps, NumberOfWalker, MovePattern, RandomStart, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
   
}

DlgRandomWalkEdit::~DlgRandomWalkEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgRandomWalkEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgRandomWalkEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgRandomWalkEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgRandomWalk.cpp"
