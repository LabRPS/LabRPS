/* This file is part of LabRPS.
   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   LabRPS is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   LabRPS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with LabRPS.  If not, see <http://www.gnu.org/licenses/>.

   Description : central settings dialog
*/

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QModelIndex>

class aSettingsListView;
class SettingsPage;
class Ui_SettingsDialog;

class QScrollArea;
class QStandardItemModel;
class QAbstractButton;
class QListWidgetItem;
class QTabWidget;

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    static void addPage(const std::string& className, const std::string& group);
    static void removePage(const std::string& className, const std::string& group);
    static void reloadSettings();

    SettingsDialog(QWidget* parent = 0, Qt::WindowFlags fl = Qt::WindowFlags());
    ~SettingsDialog();

    void accept();
    void reload();
    void activateGroupPage(const QString& group, int id);

protected:
    void changeEvent(QEvent *e);
    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent*);


protected Q_SLOTS:
    void changeGroup(QListWidgetItem *current, QListWidgetItem *previous);
    void on_buttonBox_clicked(QAbstractButton*);
    void resizeWindow(int w, int h);

private:
    /** @name for internal use only */
    //@{
    void setupPages();
    void reloadPages();
    QTabWidget* createTabForGroup(const std::string& groupName);
    void createPageInGroup(QTabWidget* tabWidget, const std::string& pageName);
    void applyChanges();
    void restoreDefaults();
    //@}

private:
    typedef std::pair<std::string, std::list<std::string>> TGroupPages;
    static std::list<TGroupPages> _pages; /**< Name of all registered preference pages */
    std::unique_ptr<Ui_SettingsDialog> ui;
    bool invalidParameter;
    bool canEmbedScrollArea;

    static const int GroupNameRole; /**< A name for our Qt::UserRole, used when storing user data in a list item */

    static SettingsDialog* _activeDialog; /**< Defaults to the nullptr, points to the current instance if there is one */

 signals:
  void generalapplicationsettingsupdates();
  void generalconfirmationsettingsupdates();
  void generalappreancesettingsupdates();
  void generalnumericformatsettingsupdates();
  void tablebasicsettingsupdates();
  void tablecolorsettingsupdates();
  void tablefontsettingsupdates();
  void fittingsettingsupdates();

};

#endif  // SETTINGSDIALOG_H
