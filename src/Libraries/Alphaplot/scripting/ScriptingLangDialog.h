/***************************************************************************
        File                 : ScriptingLangDialog.h
        Project              : AlphaPlot
--------------------------------------------------------------------
        Copyright            : (C) 2006 by Knut Franke, Ion Vasilief
        Email (use @ for *)  : knut.franke*gmx.de, ion_vasilief*yahoo.fr
        Description          : Dialog for changing the current scripting
                               language

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#ifndef SCRIPTING_LANG_DIALOG_H
#define SCRIPTING_LANG_DIALOG_H

#include "ScriptingEnv.h"
#include "Script.h"

#include <QDialog>

class QMainWindow;
class QListWidget;
class QPushButton;

class ScriptingLangDialog : public QDialog, public scripted {
  Q_OBJECT

 public:
  ScriptingLangDialog(ScriptingEnv *env, QMainWindow *parent,
                      Qt::WindowFlags fl = Qt::Widget);

 public Q_SLOTS:
  void updateLangList();
  void accept();

 private:
  QListWidget *langList;
  QPushButton *btnOK, *btnCancel;
};

#endif  // SCRIPTING_LANG_DIALOG_H
