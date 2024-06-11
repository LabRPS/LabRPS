 /**************************************************************************
 *   Copyright (c) 2018 LabRPS Developers                                 *
 *   Author: Bernd Hahnebach <bernd@bimstatik.ch>                          *
 *   Based on src/Mod/WindLab/Gui/DlgSettingsWindLabElmer.h                        *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
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

#ifndef WINDLABGUI_DLGSETTINGSFEMMATERIALIMP_H
#define WINDLABGUI_DLGSETTINGSFEMMATERIALIMP_H

#include <memory>
#include <Gui/PropertyPage.h>


namespace WindLabGui {
class Ui_DlgSettingsWindLabLimitImp;

class DlgSettingsWindLabLimitImp : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    explicit DlgSettingsWindLabLimitImp( QWidget* parent = nullptr );
    ~DlgSettingsWindLabLimitImp() override;

protected:
    void saveSettings() override;
    void loadSettings() override;
    void changeEvent(QEvent *e) override;

private:
    std::unique_ptr<Ui_DlgSettingsWindLabLimitImp> ui;
};

} // namespace WindLabGui

#endif // FEMGUI_DLGSETTINGSFEMMATERIALIMP_H
