/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include <QWizard>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QProgressBar;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QTimer;
class QButtonGroup;
QT_END_NAMESPACE

//! [0]
class PlunginIntallationWizard : public QWizard
{
    Q_OBJECT

public:
    PlunginIntallationWizard(int installationType, QString installingPluginName, QString installingPluginFullPath, QWidget *parent = nullptr);

    void accept() override;

Q_SIGNALS:
    // void sendListWidget(QListWidget *list);
};


class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(int installationType, QString installingPluginName, QWidget *parent = nullptr);

private:
    QLabel *label;
};


class TaskSelectionPage : public QWizardPage
{
    Q_OBJECT

public:
    TaskSelectionPage(int installationType, QString installingPluginName, QWidget *parent = nullptr);

private:

    QGroupBox *groupBox;
    QRadioButton *intallRadioButton;
    QRadioButton *unInstallRadioButton;
    QRadioButton *modificationRadioButton;
    QButtonGroup *taskButtonGroup;
    
};

class ObjectSelectionPage : public QWizardPage
{
    Q_OBJECT

public:
    ObjectSelectionPage(int installationType, QString installingPluginName, QString installingPluginFullPath, QWidget *parent = nullptr);
    ~ObjectSelectionPage();

public Q_SLOTS:
    void highlightChecked(QListWidgetItem* item);
    void selectAll();
    void selectNone();
    void resetSelection();

private:
    QListWidget* objectList;
    QGroupBox* viewBox;
    QPushButton* selectAllButton;
    QPushButton* selectNoneButton;
    QPushButton* resetSelectionButton;

    void createListWidget();
    void createOtherWidgets();
    void createLayout();
    void createConnections();
private:
    int InstallationType;
    QString InstallingPluginName;
    QString InstallingPluginFullPath;
private:

bool validatePage() override;



};
//! [3]

class ProgressPage : public QWizardPage
{
    Q_OBJECT

public:
    ProgressPage(int installationType, QString installingPluginName, QWidget *parent = nullptr);

public Q_SLOTS:
    void updateProgress();

private:
    QProgressBar *progressBar;
};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(int installationType, QString installingPluginName, QWidget *parent = nullptr);

protected:
    void initializePage() override;

private:
    QLabel *label;


};

#endif
