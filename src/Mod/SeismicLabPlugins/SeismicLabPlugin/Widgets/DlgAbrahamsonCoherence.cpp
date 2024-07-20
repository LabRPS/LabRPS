/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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




#include "DlgAbrahamsonCoherence.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgAbrahamsonCoherence.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSAbrahamsonCoherence.h>

#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>

//#include <QPushButton>
//#include <QApplication>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgAbrahamsonCoherence */

DlgAbrahamsonCoherence::DlgAbrahamsonCoherence(const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgAbrahamsonCoherence), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->label_Image->setPixmap(QPixmap(":icons/RPSAbrahamsonCoherence.png"));


}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgAbrahamsonCoherence::~DlgAbrahamsonCoherence()
{
}

void DlgAbrahamsonCoherence::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;

    SeismicLab::CRPSAbrahamsonCoherence* activefeature = static_cast<SeismicLab::CRPSAbrahamsonCoherence*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;

  }

void DlgAbrahamsonCoherence::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgAbrahamsonCoherenceEdit */

DlgAbrahamsonCoherenceEdit::DlgAbrahamsonCoherenceEdit(const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgAbrahamsonCoherence(featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgAbrahamsonCoherenceEdit::~DlgAbrahamsonCoherenceEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgAbrahamsonCoherenceEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgAbrahamsonCoherenceEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgAbrahamsonCoherenceEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgAbrahamsonCoherence.cpp"
