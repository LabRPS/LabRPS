/* This file is part of AlphaPlot.
   Copyright 2016 - 2020, Arun Narayanankutty <n.arun.lifescience@gmail.com>
   Copyright 2006 - 2007, Ion Vasilief <ion_vasilief@yahoo.fr>
   Copyright 2006 - 2009, Knut Franke <knut.franke@gmx.de>
   Copyright 2006 - 2009, Tilman Benkert <thzs@gmx.net>

   AlphaPlot is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   AlphaPlot is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with AlphaPlot.  If not, see <http://www.gnu.org/licenses/>.

   Description : Main part of UI & project management related stuff */
#include "Precompiled.h"

//  #include "2Dplot/TextItem2D.h"
//  #include "future/lib/XmlStreamReader.h"
//#include  "IconLoader.h"
//  #include "future/core/column/Column.h"

#include <Libraries/Alphaplot/2Dplot/Plot2D.h>
#include <Libraries/Alphaplot/2Dplot/Plotcolumns.h>
#include <Libraries/Alphaplot/2Dplot/widgets/AddPlot2DDialog.h>
#include <Libraries/Alphaplot/2Dplot/widgets/ArrangeLegend2D.h>
#include <Libraries/Alphaplot/2Dplot/widgets/Function2DDialog.h>
#include <Libraries/Alphaplot/2Dplot/widgets/SwapLayout2DDialog.h>
#include <Libraries/Alphaplot/3Dplot/Bar3D.h>
#include <Libraries/Alphaplot/3Dplot/DataManager3D.h>
#include <Libraries/Alphaplot/3Dplot/Layout3D.h>
#include <Libraries/Alphaplot/3Dplot/Scatter3D.h>
#include <Libraries/Alphaplot/3Dplot/Surface3D.h>
#include <Libraries/Alphaplot/3Dplot/SurfaceDialog.h>
#include <Libraries/Alphaplot/ImportASCIIDialog.h>
#include <Libraries/Alphaplot/LayerDialog.h>
#include <Libraries/Alphaplot/OpenProjectDialog.h>
#include <Libraries/Alphaplot/Spectrogram.h>
#include <Libraries/Alphaplot/TableStatistics.h>
#include <Libraries/Alphaplot/2Dplot/widgets/ErrDialog.h>
#include <Libraries/Alphaplot/PlotWizard.h>
//#include <Libraries/Alphaplot/CurveRangeDialog.h>
#include <Libraries/Alphaplot/ImageExportDlg.h>
#include <Libraries/Alphaplot/core/AppearanceManager.h>
#include <Libraries/Alphaplot/ui/ExportDialog.h>
//#include <Libraries/Alphaplot/ui/CharacterMapWidget.h>
#include <Libraries/Alphaplot/FindDialog.h>
#include <Libraries/Alphaplot/Folder.h>
#include <Libraries/Alphaplot/ui/PropertiesDialog.h>

//
//  #include "future/lib/XmlStreamWriter.h"
//  #include "future/core/AbstractAspect.h"
// #include <Libraries/Alphaplot/3rdparty/qcustomplot/qcustomplot.h>
// #include "future/core/Project.h"
// #include "future/table/future_Table.h"
// #include "future/matrix/future_Matrix.h"

//  #include "About.h"
//  #include "AssociationsDialog.h"
//  #include "ColorBox.h"
//  #include "ConfigDialog.h"
//  #include "analysis/Convolution.h"
//  #include "analysis/Correlation.h"
//  #include "analysis/Differentiation.h"
//  #include "analysis/ExpDecayDialog.h"
//  #include "analysis/FFTDialog.h"
//  #include "analysis/FFTFilter.h"
//  #include "analysis/FilterDialog.h"
//  #include "analysis/Fit.h"
//  #include "analysis/FitDialog.h"
//  #include "analysis/IntDialog.h"
//  #include "analysis/InterpolationDialog.h"
//  #include "analysis/MultiPeakFit.h"
//  #include "analysis/PolynomFitDialog.h"
//  #include "analysis/PolynomialFit.h"
//  #include "analysis/SigmoidalFit.h"
//  #include "analysis/SmoothCurveDialog.h"
//  #include "analysis/SmoothFilter.h"
#include "AlphaPlotAprojHandler.h"
//  #include "globals.h"
#include "PlotPropertyEditor.h"
//#include "DocumentFeaturePropertyEditor.h"
#include "RPSGlobals.h"

//#include <matplot/matplot.h>

// // TODO: move tool-specific code to an extension manager
// #include "TranslateCurveTool.h"
// #include "analysis/MultiPeakFitTool.h"
//#include "ui/SettingsDialog.h"

#include <stdio.h>
#include <stdlib.h>

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDialogButtonBox>
#include <QDockWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QImageReader>
#include <QImageWriter>
#include <QInputDialog>
#include <QKeySequence>
#include <QList>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPixmap>
#include <QPixmapCache>
#include <QPrintDialog>
#include <QPrinter>
#include <QProgressDialog>
//#include <QScriptValue>
#include <QSettings>
#include <QShortcut>
#include <QSignalMapper>
#include <QSplitter>
#include <QStatusBar>
#include <QTemporaryFile>
#include <QTextStream>
#include <QToolBar>
#include <QToolButton>
#include <QTranslator>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QUndoStack>
#include <QUndoView>
#include <QUrl>
#include <QVarLengthArray>
#include <QtDebug>
#include <iostream>

#if defined(QTWEBENGINE)
#include <QWebEngineView>

#elif defined(QTWEBKIT)
#include <QWebView>
#endif
#include <QTextBrowser>


#include "Application.h"
#include <App/Application.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <Base/Exception.h>
#include <Base/FileInfo.h>
#include <Base/Parameter.h>
#include <Base/Stream.h>

#include "Action.h"
#include "BitmapFactory.h"
#include "Command.h"
#include "DlgParameterImp.h"
#include "Document.h"
#include "DownloadManager.h"
#include "FileDialog.h"
#include "MDIView.h"
#include "ProgressBar.h"
#include "Splashscreen.h"
#include "Tools.h"
#include "WaitCursor.h"
#include "Window.h"
#include "Workbench.h"
#include "WorkbenchManager.h"
#include "MainWindow.h"

//#include <Libraries/Alphaplot/Table.h>
//#include <Libraries/Alphaplot/Matrix.h>
#include <Libraries/Alphaplot/2Dplot/Curve2D.h>
#include <Libraries/Alphaplot/2Dplot/DataManager2D.h>
#include <Libraries/Alphaplot/2Dplot/Layout2D.h>
#include <Libraries/Alphaplot/2Dplot/PickerTool2D.h>
#include <Libraries/Alphaplot/3Dplot/Layout3D.h>
#include <Libraries/Alphaplot/MyWidget.h>
#include <Libraries/Alphaplot/core/IconLoader.h>
#include <Libraries/Alphaplot/future/core/Project.h>
#include <Libraries/Alphaplot/future/matrix/future_Matrix.h>
#include <Libraries/Alphaplot/future/table/future_Table.h>
#include <Libraries/Alphaplot/future/core/column/Column.h>


#include "PlotExplorer.h"
#include "PlotPropertyEditor.h"
#include "AlphaPlotAprojHandler.h"

RPS_LOG_LEVEL_INIT("MainAlphaPlot", false, true, true)

#if defined(Q_OS_WIN32)
#define slots
//#include <private/qmainwindowlayout_p.h>
//#include <private/qwidgetresizehandler_p.h>
#endif

using namespace Gui;
using namespace std;

#include "AlphaPlot.h"


#ifdef Q_OS_WIN
#include <io.h>// for _commit()
#else
#include <unistd.h>// for fsync()
#endif

MainAlphaPlot::MainAlphaPlot(MainWindow* app)
    : app_(app), scripted(ScriptingLangManager::newEnv(app)),
      plotPropertyeditor(nullptr),
      plotExplorer(nullptr),
      hiddenWindows(new QList<QWidget*>()), outWindows(new QList<QWidget*>()),
      lastModified(nullptr), fileToolbar(new QToolBar(tr("File"), this)),
      editToolbar(new QToolBar(tr("Edit"), this)),
      graphToolsToolbar(new QToolBar(tr("Graph"), this)),
      plot2DToolbar(new QToolBar(tr("Plot"), this)), tableToolbar(new QToolBar(tr("Table"), this)),
      matrix3DPlotToolbar(new QToolBar(tr("Matrix Plot"), this)),
      graph3DToolbar(new QToolBar(tr("3D Surface"), this)),
      current_folder(new Folder(nullptr, tr("Untitled"))), show_windows_policy(ActiveFolder),
      appCustomColor(false), appStyle(qApp->style()->objectName()), appColorScheme(0),
      appFont(QFont()), projectname(QString::fromLatin1("untitled")), logInfo(QString()), savingTimerId(0),
      copiedLayer(false), renamedTables(QStringList()),
      aprojhandler_(new AlphaPlotAprojHandler(this)), actionplot3dAnimate_(new QAction(tr("Animate"), this)),
      actionResetCameraFront_(new QAction(tr("Reset Camera Front"), this)),
      actionResetZoomfactor_(new QAction(tr("Reset Zoom Factor"), this)),
      graphToolsGroup(new QActionGroup(this)), groupplot3dselectionmode_(new QActionGroup(this)),
      actionplot3dmodecolumnselect_(new QAction(tr("Column Select"), groupplot3dselectionmode_)),
      actionplot3dmoderowselect_(new QAction(tr("Row Select"), groupplot3dselectionmode_)),
      actionplot3dmodeitemselect_(new QAction(tr("Point Select"), groupplot3dselectionmode_)),
      actionplot3dmodenoneselect_(new QAction(tr("No Selection"), groupplot3dselectionmode_)),
      d_plot_mapper(new QSignalMapper(this)), statusBarInfo(new QLabel(this)),
      actionShowPropertyEditor(new QAction(this)), actionShowProjectExplorer(new QAction(this)),
      actionShowResultsLog(new QAction(this)), actionShowConsole(new QAction(this)),
      btn_new_aspect_(new QToolButton(this)), btn_layout_(new QToolButton(this)),
      btn_curves_(new QToolButton(this)), btn_plot_enrichments_(new QToolButton(this)),
      btn_plot_scatters_(new QToolButton(this)), btn_plot_linespoints_(new QToolButton(this)),
      btn_plot_bars_(new QToolButton(this)), btn_plot_vect_(new QToolButton(this)),
      btn_plot_pie_(new QToolButton(this)), multiPeakfitactive_(false), multiPeakfitpoints_(0),
      multiPeakfittype_(0), glowstatus_(true), glowcolor_(Qt::red), glowxoffset_(0),
      glowyoffset_(0), glowradius_(8)
{
    // non menu qactions
    actionSaveNote = new QAction(tr("Save Note As..."), this);
    actionExportPDF = new QAction(tr("&Export PDF") + QString::fromLatin1("..."), this);
    actionHideActiveWindow = new QAction(tr("&Hide Window"), this);
    actionShowMoreWindows = new QAction(tr("More windows..."), this);
    actionPixelLineProfile = new QAction(tr("&View Pixel Line Profile"), this);
    actionIntensityTable = new QAction(tr("&Intensity Table"), this);
    actionActivateWindow = new QAction(tr("&Activate Window"), this);
    actionMinimizeWindow = new QAction(tr("Mi&nimize Window"), this);
    actionMaximizeWindow = new QAction(tr("Ma&ximize Window"), this);
    actionPrintWindow = new QAction(tr("&Print Window"), this);
    actionAdd3DData = new QAction(tr("&Data Set..."), this);
    actionEditSurfacePlot = new QAction(tr("&Surface..."), this);
    actionInvertMatrix = new QAction(tr("&Invert"), this);
    actionMatrixDeterminant = new QAction(tr("&Determinant"), this);
    actionConvertMatrix = new QAction(tr("&Convert to Table"), this);
    actionConvertTable = new QAction(tr("Convert to &Matrix"), this);
    actionEditCurveRange = new QAction(tr("Edit &Range..."), this);
    actionCopyStatusBarText = new QAction(tr("&Copy status bar text"), this);
    actionExportPDF->setShortcut(tr("Ctrl+Alt+P"));
    // Load Style & color scheme here
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("General"));
    changeAppStyle(settings.value(QString::fromLatin1("Style"), appStyle).toString());
    changeAppColorScheme(settings.value(QString::fromLatin1("ColorScheme"), 0).toInt());
    // Initialize scripting environment.
    attachQtScript();
    // icons load needed so do it after setting Style & ColorScheme
    // settings_ = new SettingsDialog(this);

    // Toolbar QToolbuttons
    btn_new_aspect_->setPopupMode(QToolButton::InstantPopup);
    btn_new_aspect_->setToolTip(tr("New Aspect"));
    btn_layout_->setPopupMode(QToolButton::InstantPopup);
    btn_layout_->setToolTip(tr("Manage layers"));
    btn_curves_->setPopupMode(QToolButton::InstantPopup);
    btn_curves_->setToolTip(tr("Add curves / error bars"));
    btn_plot_enrichments_->setPopupMode(QToolButton::InstantPopup);
    btn_plot_enrichments_->setToolTip(tr("Enrichments"));
    btn_plot_scatters_->setPopupMode(QToolButton::InstantPopup);
    btn_plot_scatters_->setToolTip(tr("Scatters"));
    btn_plot_linespoints_->setPopupMode(QToolButton::InstantPopup);
    btn_plot_linespoints_->setToolTip(tr("Lines and/or symbols"));
    btn_plot_bars_->setPopupMode(QToolButton::InstantPopup);
    btn_plot_vect_->setPopupMode(QToolButton::InstantPopup);
    btn_plot_pie_->setPopupMode(QToolButton::InstantPopup);

    // Mainwindow properties
    setWindowIcon(IconLoader::load(QString::fromLatin1("alpha-logo"), IconLoader::General));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString::fromLatin1("AlphaPlot - ") + tr("untitled"));
    QPixmapCache::setCacheLimit(20 * QPixmapCache::cacheLimit());

    // Initiate Fonts
    QString family = appFont.family();
    int pointSize = appFont.pointSize();
    tableTextFont = appFont;
    tableHeaderFont = appFont;
    plotAxesFont = QFont(family, pointSize, QFont::Bold, false);
    plotNumbersFont = QFont(family, pointSize);
    plotLegendFont = appFont;
    plotTitleFont = QFont(family, pointSize + 2, QFont::Bold, false);
    plot3DAxesFont = QFont(family, pointSize, QFont::Bold, false);
    plot3DNumbersFont = QFont(family, pointSize);
    plot3DTitleFont = QFont(family, pointSize + 2, QFont::Bold, false);

    // Initiate projects & set connections
    d_project = new Project();
    connect(d_project, SIGNAL(aspectAdded(const AbstractAspect*, int)), this,
            SLOT(handleAspectAdded(const AbstractAspect*, int)));
    connect(d_project, SIGNAL(aspectAboutToBeRemoved(const AbstractAspect*, int)), this,
            SLOT(handleAspectAboutToBeRemoved(const AbstractAspect*, int)));
    //connect(d_project->undoStack(), &QUndoStack::canUndoChanged, ui_->actionUndo,
    //        &QAction::setEnabled);
    //connect(d_project->undoStack(), &QUndoStack::canRedoChanged, ui_->actionRedo,
    //        &QAction::setEnabled);

    // Explorer window
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {

            plotExplorer->explorerGridLayout->setContentsMargins(0, 0, 0, 0);
        plotExplorer->setMinimumHeight(150);

        plotExplorer->folderView->setColumnCount(1);
        plotExplorer->folderView->setHeaderLabel(tr("Folder"));
        plotExplorer->folderView->setRootIsDecorated(true);

        plotExplorer->folderView->header()->setSectionsClickable(false);
        plotExplorer->folderView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

        plotExplorer->folderView->header()->hide();
        plotExplorer->folderView->setSelectionMode(QAbstractItemView::SingleSelection);
        plotExplorer->folderView->setContextMenuPolicy(Qt::CustomContextMenu);

        // Explorer Window folder view connections
        connect(plotExplorer->folderView, &FolderTreeWidget::currentItemChanged, this,
                &MainAlphaPlot::folderItemChanged);
        connect(plotExplorer->folderView, SIGNAL(customContextMenuRequested(const QPoint&)), this,
                SLOT(showFolderPopupMenu(const QPoint&)));
        connect(plotExplorer->folderView, SIGNAL(addFolderItem()), this, SLOT(addFolder()));
        connect(plotExplorer->folderView, SIGNAL(deleteSelection()), this,
                SLOT(deleteSelectedItems()));
        connect(plotExplorer->folderView, &FolderTreeWidget::dragItems, this,
                &MainAlphaPlot::dragFolderItems);
        connect(plotExplorer->folderView, &FolderTreeWidget::dropItems, this,
                &MainAlphaPlot::dropFolderItems);
        // Explorer window folderview list item
        FolderTreeWidgetItem* folderTreeItem =
            new FolderTreeWidgetItem(plotExplorer->folderView, current_folder);
        current_folder->setFolderTreeWidgetItem(folderTreeItem);
        folderTreeItem->setExpanded(true);
        // Explorer window list view properties
        plotExplorer->listView->setHeaderLabels(QStringList()
                                                << tr("Name") << tr("Type") << tr("View")
                                                << tr("Created") << tr("Label"));
        plotExplorer->listView->header()->setStretchLastSection(true);
        plotExplorer->listView->setMinimumHeight(80);
        plotExplorer->listView->setRootIsDecorated(false);
        plotExplorer->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        plotExplorer->listView->setContextMenuPolicy(Qt::CustomContextMenu);

        // Explorer Window list view connections
        connect(plotExplorer->listView, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this,
                SLOT(folderItemDoubleClicked(QTreeWidgetItem*)));
        connect(plotExplorer->listView, SIGNAL(customContextMenuRequested(const QPoint&)), this,
                SLOT(showWindowPopupMenu(const QPoint&)));
        connect(plotExplorer->listView, SIGNAL(addFolderItem()), this, SLOT(addFolder()));
        connect(plotExplorer->listView, SIGNAL(deleteSelection()), this,
                SLOT(deleteSelectedItems()));
        connect(plotExplorer->listView, &FolderTreeWidget::dragItems, this,
                &MainAlphaPlot::dragFolderItems);
        connect(plotExplorer->listView, &FolderTreeWidget::dropItems, this,
                &MainAlphaPlot::dropFolderItems);
        // Explorer window set folder & listview
        plotExplorer->folderView->setFrameShape(QFrame::NoFrame);
        plotExplorer->listView->setFrameShape(QFrame::NoFrame);
        plotExplorer->explorerSplitter->setFrameShape(QFrame::NoFrame);
        plotExplorer->explorerSplitter->setSizes(QList<int>() << 30 << 70);

        // drag n drop
        plotExplorer->listView->setDragEnabled(true);
        plotExplorer->listView->setAcceptDrops(true);
        plotExplorer->listView->setDefaultDropAction(Qt::MoveAction);
        plotExplorer->folderView->setDragEnabled(true);
        plotExplorer->folderView->setAcceptDrops(true);
        plotExplorer->folderView->setDefaultDropAction(Qt::MoveAction);
        
    }


    //// Results log window
    //ui_->resultLogGridLayout->setContentsMargins(0, 0, 0, 0);
    //ui_->resultLog->setFrameShape(QFrame::NoFrame);
    //ui_->resultLog->setReadOnly(true);
    //ui_->logWindow->hide();

    disableActions();
    // After initialization of QDockWidget, for toggleViewAction() to work
    // Set icons for QActions
    loadIcons();

//    // disable time axis as all the features are available in datetime axis
//    ui_->actionLeftTime->setVisible(false);
//    ui_->actionBottomTime->setVisible(false);
//    ui_->actionRightTime->setVisible(false);
//    ui_->actionTopTime->setVisible(false);
//    // QAction Connections
//    // File menu
//    connect(ui_->actionNewProject, SIGNAL(triggered()), this, SLOT(newAproj()));
//    connect(ui_->actionNewGraph, SIGNAL(triggered()), this, SLOT(newGraph2D()));
//    connect(ui_->actionNewNote, SIGNAL(triggered()), this, SLOT(newNote()));
//    connect(ui_->actionNewTable, SIGNAL(triggered()), this, SLOT(newTable()));
//    connect(ui_->actionNewMatrix, SIGNAL(triggered()), this, SLOT(newMatrix()));
//    connect(ui_->actionNewFunctionPlot, SIGNAL(triggered()), this, SLOT(functionDialog()));
//    connect(ui_->actionNew3DSurfacePlot, SIGNAL(triggered()), this, SLOT(newSurfacePlot()));
//    connect(ui_->actionOpenAproj, SIGNAL(triggered()), this, SLOT(openAproj()));
//    connect(ui_->actionOpenImage, SIGNAL(triggered()), this, SLOT(loadImage()));
//    connect(ui_->actionImportImage, SIGNAL(triggered()), this, SLOT(importImage()));
//    connect(ui_->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
//    connect(ui_->actionSaveProjectAs, SIGNAL(triggered()), this, SLOT(saveProjectAs()));
//    connect(ui_->actionOpenTemplate, SIGNAL(triggered()), this, SLOT(openTemplate()));
//    connect(ui_->actionSaveAsTemplate, SIGNAL(triggered()), this, SLOT(saveAsTemplate()));
//    connect(ui_->actionExportCurrentGraph, SIGNAL(triggered()), this, SLOT(exportGraph()));
//    connect(ui_->actionExportAllGraphs, SIGNAL(triggered()), this, SLOT(exportAllGraphs()));
//    connect(ui_->actionPrint, SIGNAL(triggered()), this, SLOT(print()));
//    connect(ui_->actionPrintAllPlots, SIGNAL(triggered()), this, SLOT(printAllPlots()));
//    connect(ui_->actionExportASCII, SIGNAL(triggered()), this, SLOT(showExportASCIIDialog()));
//    connect(ui_->actionImportASCII, SIGNAL(triggered()), this, SLOT(importASCII()));
//    connect(ui_->actionQuit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
//    // Edit menu
//    connect(ui_->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
//    ui_->actionUndo->setEnabled(false);
//    connect(ui_->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
//    ui_->actionRedo->setEnabled(false);
//    connect(ui_->actionCutSelection, SIGNAL(triggered()), this, SLOT(cutSelection()));
//    connect(ui_->actionCopySelection, SIGNAL(triggered()), this, SLOT(copySelection()));
//    connect(ui_->actionPasteSelection, SIGNAL(triggered()), this, SLOT(pasteSelection()));
//    connect(ui_->actionClearSelection, SIGNAL(triggered()), this, SLOT(clearSelection()));
//    connect(ui_->actionClearLogInfo, SIGNAL(triggered()), this, SLOT(clearLogInfo()));
//    connect(ui_->actionDeleteFitTables, SIGNAL(triggered()), this, SLOT(deleteFitTables()));
//    connect(ui_->actionAddGlyphs, &QAction::triggered, this, &MainAlphaPlot::showAddGlyphs);
//    connect(ui_->actionPreferences, SIGNAL(triggered()), this, SLOT(showPreferencesDialog()));
//    // View menu
//    connect(ui_->actionPlotWizard, SIGNAL(triggered()), this, SLOT(showPlotWizard()));
//    connect(ui_->actionShowUndoRedoHistory, SIGNAL(triggered(bool)), this,
//            SLOT(showUndoRedoHistory()));
//    connect(ui_->actionShowFileToolbar, SIGNAL(toggled(bool)), fileToolbar, SLOT(setVisible(bool)));
//    connect(ui_->actionShowEditToolbar, SIGNAL(toggled(bool)), editToolbar, SLOT(setVisible(bool)));
//    connect(ui_->actionShowGraphToolbar, SIGNAL(toggled(bool)), graphToolsToolbar,
//            SLOT(setVisible(bool)));
//    connect(ui_->actionShowPlotToolbar, SIGNAL(toggled(bool)), plot2DToolbar,
//            SLOT(setVisible(bool)));
//    connect(ui_->actionShowTableToolbar, SIGNAL(toggled(bool)), tableToolbar,
//            SLOT(setVisible(bool)));
//    connect(ui_->actionShowMatrixPlotToolbar, SIGNAL(toggled(bool)), matrix3DPlotToolbar,
//            SLOT(setVisible(bool)));
//    connect(ui_->actionShow3DSurfacePlotToolbar, SIGNAL(toggled(bool)), graph3DToolbar,
//            SLOT(setVisible(bool)));
//    connect(ui_->actionLockToolbars, SIGNAL(toggled(bool)), this, SLOT(lockToolbars(bool)));
//    actionShowPropertyEditor->setText(tr("Property Editor"));
//    actionShowProjectExplorer->setText(tr("Project Explorer"));
//    actionShowResultsLog->setText(tr("Result Log"));
//    actionShowConsole->setText(tr("Console"));
//    actionShowPropertyEditor->setToolTip(tr("Show Property Editor"));
//    actionShowProjectExplorer->setToolTip(tr("Show Project Explorer"));
//    actionShowResultsLog->setToolTip(tr("Show Result Log"));
//    actionShowConsole->setToolTip(tr("Show Scripting Console"));
//    actionShowProjectExplorer->setShortcut(tr("Ctrl+E"));
//    actionShowPropertyEditor->setCheckable(true);
//    actionShowProjectExplorer->setCheckable(true);
//    actionShowResultsLog->setCheckable(true);
//    actionShowConsole->setCheckable(true);
//    ui_->menuView->addAction(actionShowPropertyEditor);
//    ui_->menuView->addAction(actionShowProjectExplorer);
//    ui_->menuView->addAction(actionShowResultsLog);
//#ifdef SCRIPTING_CONSOLE
//    ui_->menuView->addAction(actionShowConsole);
//    actionShowConsole->setEnabled(true);
//    actionShowConsole->setVisible(true);
//#else
//    actionShowConsole->setEnabled(false);
//    actionShowConsole->setVisible(false);
//#endif
//
//// Scripting menu
//#ifdef SCRIPTING_DIALOG
//    connect(ui_->actionScriptingLanguage, SIGNAL(triggered()), this,
//            SLOT(showScriptingLangDialog()));
//    ui_->actionScriptingLanguage->setVisible(true);
//#else
//    ui_->actionScriptingLanguage->setVisible(false);
//#endif
//    connect(ui_->actionRestartScripting, SIGNAL(triggered()), this, SLOT(restartScriptingEnv()));
//    // Plot menu
//    connect(d_plot_mapper, SIGNAL(mapped(int)), this, SLOT(selectPlotType(int)));
//    connect(ui_->actionPlot2DLine, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DLine, static_cast<int>(Graph::Line));
//    connect(ui_->actionPlot2DScatter, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DScatter, static_cast<int>(Graph::Scatter));
//    connect(ui_->actionPlot2DScatterXErr, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DScatterXErr, static_cast<int>(Graph::ScatterXError));
//    connect(ui_->actionPlot2DScatterYErr, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DScatterYErr, static_cast<int>(Graph::ScatterYError));
//    connect(ui_->actionPlot2DScatterXYErr, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DScatterXYErr,
//                              static_cast<int>(Graph::ScatterXYError));
//    connect(ui_->actionPlot2DLineSymbol, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DLineSymbol, static_cast<int>(Graph::LineSymbols));
//    connect(ui_->actionPlot2DVerticalDropLines, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DVerticalDropLines,
//                              static_cast<int>(Graph::VerticalDropLines));
//    connect(ui_->actionPlot2DSpline, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DSpline, static_cast<int>(Graph::Spline));
//    connect(ui_->actionPlot2DVerticalSteps, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DVerticalSteps,
//                              static_cast<int>(Graph::VerticalSteps));
//    connect(ui_->actionPlot2DHorizontalSteps, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DHorizontalSteps,
//                              static_cast<int>(Graph::HorizontalSteps));
//    connect(ui_->actionPlot2DVerticalBars, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DVerticalBars, static_cast<int>(Graph::VerticalBars));
//    connect(ui_->actionPlot2DVerticalStackedBars, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DVerticalStackedBars,
//                              static_cast<int>(Graph::VerticalStackedBars));
//    connect(ui_->actionPlot2DVerticalGroupedBars, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DVerticalGroupedBars,
//                              static_cast<int>(Graph::VerticalGroupedBars));
//    connect(ui_->actionPlot2DHorizontalBars, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DHorizontalBars,
//                              static_cast<int>(Graph::HorizontalBars));
//    connect(ui_->actionPlot2DHorizontalStackedBars, SIGNAL(triggered()), d_plot_mapper,
//            SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DHorizontalStackedBars,
//                              static_cast<int>(Graph::HorizontalStackedBars));
//    connect(ui_->actionPlot2DHorizontalGroupedBars, SIGNAL(triggered()), d_plot_mapper,
//            SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DHorizontalGroupedBars,
//                              static_cast<int>(Graph::HorizontalGroupedBars));
//    connect(ui_->actionPlot2DArea, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DArea, static_cast<int>(Graph::Area));
//    connect(ui_->actionPlot2DChannelFill, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DChannelFill, static_cast<int>(Graph::Channel));
//    connect(ui_->actionPlot2DPie, &QAction::triggered,
//            [&]() { plotPie(Graph2DCommon::PieStyle::Pie); });
//    connect(ui_->actionPlot2DHalfPie, &QAction::triggered,
//            [&]() { plotPie(Graph2DCommon::PieStyle::HalfPie); });
//    connect(ui_->actionPlot2DVectorsXYAM, SIGNAL(triggered()), this, SLOT(plotVectXYAM()));
//    connect(ui_->actionPlot2DVectorsXYXY, SIGNAL(triggered()), this, SLOT(plotVectXYXY()));
//    connect(ui_->actionPlot2DStatBox, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DStatBox, static_cast<int>(Graph::Box));
//    connect(ui_->actionPlot2DStatHistogram, SIGNAL(triggered()), d_plot_mapper, SLOT(map()));
//    d_plot_mapper->setMapping(ui_->actionPlot2DStatHistogram, static_cast<int>(Graph::Histogram));
//    connect(ui_->actionPlot2DStatStackedHistogram, SIGNAL(triggered()), this,
//            SLOT(plotStackedHistograms()));
//    connect(ui_->actionPanelVertical2Layouts, &QAction::triggered, [&]() {
//        Layout2D* layout = newGraph2D();
//        layout->addAxisRectWithAxis(QPair<int, int>(0, 0));
//        layout->addAxisRectWithAxis(QPair<int, int>(1, 0));
//    });
//    connect(ui_->actionPanelHorizontal2Layouts, &QAction::triggered, [&]() {
//        Layout2D* layout = newGraph2D();
//        layout->addAxisRectWithAxis(QPair<int, int>(0, 0));
//        layout->addAxisRectWithAxis(QPair<int, int>(0, 1));
//    });
//    connect(ui_->actionPanel4Layouts, &QAction::triggered, [&]() {
//        Layout2D* layout = newGraph2D();
//        layout->addAxisRectWithAxis(QPair<int, int>(0, 0));
//        layout->addAxisRectWithAxis(QPair<int, int>(0, 1));
//        layout->addAxisRectWithAxis(QPair<int, int>(1, 0));
//        layout->addAxisRectWithAxis(QPair<int, int>(1, 1));
//    });
//    ui_->actionPlot3DRibbon->setVisible(false);
//    connect(ui_->actionPlot3DRibbon, SIGNAL(triggered()), this, SLOT(plot3DRibbon()));
//    connect(ui_->actionPlot3DBar, SIGNAL(triggered()), this, SLOT(plot3DBars()));
//    connect(ui_->actionPlot3DScatter, SIGNAL(triggered()), this, SLOT(plot3DScatter()));
//    ui_->actionPlot3DTrajectory->setVisible(false);
//    connect(ui_->actionPlot3DTrajectory, SIGNAL(triggered()), this, SLOT(plot3DTrajectory()));
//    // 3D Plot menu
//    connect(ui_->action3DWireFrame, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawWireframe);
//    });
//    connect(ui_->action3DSurface, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawSurface);
//    });
//    connect(ui_->action3DWireSurface, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe);
//    });
//    connect(ui_->action3DBar, SIGNAL(triggered()), ui_->actionPlot3DBar, SIGNAL(triggered()));
//    connect(ui_->action3DScatter, SIGNAL(triggered()), ui_->actionPlot3DScatter,
//            SIGNAL(triggered()));
//    connect(ui_->action3DCountourColorFill, SIGNAL(triggered()), this, SLOT(plotColorMap()));
//    connect(ui_->action3DCountourLines, SIGNAL(triggered()), this, SLOT(plotContour()));
//    connect(ui_->action3DGreyScaleMap, SIGNAL(triggered()), this, SLOT(plotGrayScale()));
//    connect(ui_->action3DWireFramePolar, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawWireframe);
//        layout->getSurface3DModifier()->getGraph()->setPolar(true);
//    });
//    connect(ui_->action3DSurfacePolar, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawSurface);
//        layout->getSurface3DModifier()->getGraph()->setPolar(true);
//    });
//    connect(ui_->action3DWireFrameSurfacePolar, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe);
//        layout->getSurface3DModifier()->getGraph()->setPolar(true);
//    });
//    connect(ui_->action3DScatterPolar, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Scatter);
//        if (layout && layout->getScatter3DModifier())
//            layout->getScatter3DModifier()->getGraph()->setPolar(true);
//    });
//    connect(ui_->action3DPolarSpectrogram, &QAction::triggered, [=]() {
//        Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
//        if (layout && layout->getSurface3DModifier())
//            layout->getSurface3DModifier()->setSurfaceMeshType(
//                QSurface3DSeries::DrawFlag::DrawSurface);
//        layout->getSurface3DModifier()->getGraph()->setOrthoProjection(true);
//        layout->getSurface3DModifier()->getGraph()->setPolar(true);
//        layout->getSurface3DModifier()->getGraph()->setFlipHorizontalGrid(true);
//        layout->getSurface3DModifier()->getGraph()->scene()->activeCamera()->setCameraPreset(
//            Q3DCamera::CameraPreset::CameraPresetDirectlyAbove);
//    });
//    // Graph menu
//    connect(ui_->actionAddRemovePloty, &QAction::triggered, this,
//            &MainAlphaPlot::showCurvesDialog);
//    connect(ui_->actionAddRemoveVector, &QAction::triggered, this,
//            &MainAlphaPlot::showCurvesDialog);
//    connect(ui_->actionAddRemoveCurve, &QAction::triggered, this,
//            &MainAlphaPlot::showCurvesDialog);
//    connect(ui_->actionAddErrorBars, &QAction::triggered, this, &MainAlphaPlot::addErrorBars);
//    connect(ui_->actionAddFunctionCurve, &QAction::triggered, this,
//            &MainAlphaPlot::addFunctionCurve);
//    connect(ui_->actionLeftValue, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionLeftLog, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionLeftPi, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionLeftText, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionLeftTime, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionLeftDateTime, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionBottomValue, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionBottomLog, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionBottomPi, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionBottomText, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionBottomTime, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionBottomDateTime, &QAction::triggered, this,
//            &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionRightValue, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionRightLog, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionRightPi, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionRightText, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionRightTime, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionRightDateTime, &QAction::triggered, this,
//            &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionTopValue, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionTopLog, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionTopPi, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionTopText, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionTopTime, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionTopDateTime, &QAction::triggered, this, &MainAlphaPlot::addGraph2DAxis);
//    connect(ui_->actionLegendReorder, &QAction::triggered, this, &MainAlphaPlot::legendReorder);
//    connect(ui_->actionAddText, SIGNAL(triggered()), this, SLOT(addText()));
//    graphToolsGroup->setExclusive(true);
//    ui_->actionDrawArrow->setActionGroup(graphToolsGroup);
//    // ui_->actionDrawLine->setActionGroup(graphToolsGroup);
//    connect(ui_->actionDrawLine, SIGNAL(triggered()), this, SLOT(drawLine()));
//    connect(ui_->actionAddTimeStamp, SIGNAL(triggered()), this, SLOT(addTimeStamp()));
//    connect(ui_->actionAddImage, SIGNAL(triggered()), this, SLOT(addImage()));
//    connect(ui_->actionDrawEllipse, SIGNAL(triggered()), this, SLOT(drawEllipse()));
//    connect(ui_->actionAddNestedLayout, SIGNAL(triggered()), this, SLOT(addNestedLayout()));
//    connect(ui_->actionAddLayoutUp, &QAction::triggered, this,
//            [&]() { addLayout(Graph2DCommon::AddLayoutElement::Top); });
//    connect(ui_->actionAddLayoutDown, &QAction::triggered, this,
//            [&]() { addLayout(Graph2DCommon::AddLayoutElement::Bottom); });
//    connect(ui_->actionAddLayoutLeft, &QAction::triggered, this,
//            [&]() { addLayout(Graph2DCommon::AddLayoutElement::Left); });
//    connect(ui_->actionAddLayoutRight, &QAction::triggered, this,
//            [&]() { addLayout(Graph2DCommon::AddLayoutElement::Right); });
//    connect(ui_->actionRemoveLayout, &QAction::triggered, this, &MainAlphaPlot::deleteLayout);
//    connect(ui_->actionArrangeLayout, &QAction::triggered, this,
//            &MainAlphaPlot::showSwapLayoutDialog);
//    // Tools menu
//    ui_->actionDisableGraphTools->setActionGroup(graphToolsGroup);
//    ui_->actionDisableGraphTools->setCheckable(true);
//    connect(ui_->actionGraphRescaleShowAll, SIGNAL(triggered()), this, SLOT(setAutoScale()));
//    ui_->actionGraphDragRange->setActionGroup(graphToolsGroup);
//    ui_->actionGraphDragRange->setCheckable(true);
//    ui_->actionGraphZoomRange->setActionGroup(graphToolsGroup);
//    ui_->actionGraphZoomRange->setCheckable(true);
//    ui_->actionGraphScreenReader->setActionGroup(graphToolsGroup);
//    ui_->actionGraphScreenReader->setCheckable(true);
//    ui_->actionGraphDataReader->setActionGroup(graphToolsGroup);
//    ui_->actionGraphDataReader->setCheckable(true);
//    ui_->actionGraphSelectDataRange->setActionGroup(graphToolsGroup);
//    ui_->actionGraphSelectDataRange->setCheckable(true);
//    ui_->actionGraphMoveDataPoints->setActionGroup(graphToolsGroup);
//    ui_->actionGraphMoveDataPoints->setCheckable(true);
//    ui_->actionGraphRemoveBadDataPoints->setActionGroup(graphToolsGroup);
//    ui_->actionGraphRemoveBadDataPoints->setCheckable(true);
//    connect(graphToolsGroup, SIGNAL(triggered(QAction*)), this, SLOT(pickGraphTool(QAction*)));
//    // Table Analysis menu
//    connect(ui_->actionStatisticsOnColumns, SIGNAL(triggered()), this,
//            SLOT(showColumnStatistics()));
//    connect(ui_->actionStatisticsOnRows, SIGNAL(triggered()), this, SLOT(showRowStatistics()));
//    connect(ui_->actionTableFFT, SIGNAL(triggered()), this, SLOT(showFFTDialog()));
//    connect(ui_->actionCorrelate, SIGNAL(triggered()), this, SLOT(correlate()));
//    connect(ui_->actionAutocorrelate, SIGNAL(triggered()), this, SLOT(autoCorrelate()));
//    connect(ui_->actionConvolute, SIGNAL(triggered()), this, SLOT(convolute()));
//    connect(ui_->actionDeconvolute, SIGNAL(triggered()), this, SLOT(deconvolute()));
//    // Graph Analysis menu
//    connect(ui_->actionHorizontalTranslate, SIGNAL(triggered()), this, SLOT(horizontalTranslate()));
//    connect(ui_->actionVerticalTranslate, SIGNAL(triggered()), this, SLOT(verticalTranslate()));
//    connect(ui_->actionDifferentiate, SIGNAL(triggered()), this, SLOT(differentiate()));
//    connect(ui_->actionIntegrate, SIGNAL(triggered()), this, SLOT(integrate()));
//    connect(ui_->actionSavitzkySmooth, SIGNAL(triggered()), this, SLOT(savitzkySmooth()));
//    connect(ui_->actionMovingWindowAverageSmooth, SIGNAL(triggered()), this,
//            SLOT(movingWindowAverageSmooth()));
//    connect(ui_->actionFFTFilterSmooth, SIGNAL(triggered()), this, SLOT(fFTFilterSmooth()));
//    connect(ui_->actionLowPassFFTFilter, SIGNAL(triggered()), this, SLOT(lowPassFilter()));
//    connect(ui_->actionHighPassFFTFilter, SIGNAL(triggered()), this, SLOT(highPassFilter()));
//    connect(ui_->actionBandPassFFTFilter, SIGNAL(triggered()), this, SLOT(bandPassFilter()));
//    connect(ui_->actionBandBlockFFTFilter, SIGNAL(triggered()), this, SLOT(bandBlockFilter()));
//    connect(ui_->actionInterpolate, SIGNAL(triggered()), this, SLOT(interpolate()));
//    connect(ui_->actionGraph2DFFT, SIGNAL(triggered()), this, SLOT(showFFTDialog()));
//    connect(ui_->actionFitLinear, SIGNAL(triggered()), this, SLOT(fitLinear()));
//    connect(ui_->actionFitPolynomial, SIGNAL(triggered()), this, SLOT(fitPolynomial()));
//    connect(ui_->actionFirstOrderExponentialDecay, SIGNAL(triggered()), this,
//            SLOT(fitFirstOrderExponentialDecay()));
//    connect(ui_->actionSecondOrderExponentialDecay, SIGNAL(triggered()), this,
//            SLOT(fitSecondOrderExponentialDecay()));
//    connect(ui_->actionThirdOrderExponentialDecay, SIGNAL(triggered()), this,
//            SLOT(fitThirdOrderExponentialDecay()));
//    connect(ui_->actionFitExponentialGrowth, SIGNAL(triggered()), this,
//            SLOT(fitExponentialGrowth()));
//    connect(ui_->actionFitBoltzmannSigmoid, SIGNAL(triggered()), this, SLOT(fitBoltzmannSigmoid()));
//    connect(ui_->actionFitGaussian, SIGNAL(triggered()), this, SLOT(fitGaussian()));
//    connect(ui_->actionFitLorentzian, SIGNAL(triggered()), this, SLOT(fitLorentzian()));
//    connect(ui_->actionMultiPeakGaussian, SIGNAL(triggered()), this, SLOT(fitMultiPeakGaussian()));
//    connect(ui_->actionMultiPeakLorentzian, SIGNAL(triggered()), this,
//            SLOT(fitMultiPeakLorentzian()));
//    connect(ui_->actionGraph2DFitWizard, SIGNAL(triggered()), this, SLOT(showFitDialog()));
//    // Windows menu
//    connect(ui_->actionCascadeWindow, SIGNAL(triggered()), d_workspace, SLOT(cascadeSubWindows()));
//    connect(ui_->actionTileWindow, SIGNAL(triggered()), d_workspace, SLOT(tileSubWindows()));
//    connect(ui_->actionNextWindow, SIGNAL(triggered()), d_workspace, SLOT(activateNextSubWindow()));
//    connect(ui_->actionPreviousWindow, SIGNAL(triggered()), d_workspace,
//            SLOT(activatePreviousSubWindow()));
//    connect(ui_->actionDuplicateWindow, SIGNAL(triggered()), this, SLOT(clone()));
//    connect(ui_->actionHideWindow, SIGNAL(triggered()), this, SLOT(hideActiveWindow()));
//    connect(ui_->actionCloseWindow, SIGNAL(triggered()), this, SLOT(closeActiveWindow()));
//    // Help menu
//    connect(ui_->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
//#ifdef DYNAMIC_MANUAL_PATH
//    connect(ui_->actionChooseHelpFolder, SIGNAL(triggered()), this, SLOT(chooseHelpFolder()));
//    ui_->actionChooseHelpFolder->setVisible(true);
//#else
//    ui_->actionChooseHelpFolder->setVisible(false);
//#endif
//    connect(ui_->actionHomepage, SIGNAL(triggered()), this, SLOT(showHomePage()));
//#ifdef SEARCH_FOR_UPDATES
//    connect(ui_->actionCheckUpdates, SIGNAL(triggered()), this, SLOT(searchForUpdates()));
//    ui_->actionCheckUpdates->setVisible(true);
//#else
//    ui_->actionCheckUpdates->setVisible(false);
//#endif// defined SEARCH_FOR_UPDATES
//#ifdef DOWNLOAD_LINKS
//    connect(ui_->actionDownloadManual, SIGNAL(triggered()), this, SLOT(downloadManual()));
//    ui_->actionDownloadManual->setVisible(true);
//#else
//    ui_->actionDownloadManual->setVisible(false);
//#endif
//    connect(ui_->actionVisitForum, SIGNAL(triggered()), this, SLOT(showForums()));
//    connect(ui_->actionReportBug, SIGNAL(triggered()), this, SLOT(showBugTracker()));
//    connect(ui_->actionAbout, &QAction::triggered, this, &MainAlphaPlot::about);
//
//    // non main menu QAction Connections
//    connect(actionSaveNote, SIGNAL(triggered()), this, SLOT(saveNoteAs()));
//    connect(actionExportPDF, SIGNAL(triggered()), this, SLOT(exportPDF()));
//    connect(actionHideActiveWindow, SIGNAL(triggered()), this, SLOT(hideActiveWindow()));
//    connect(actionShowMoreWindows, SIGNAL(triggered()), this, SLOT(showMoreWindows()));
//    connect(actionPixelLineProfile, SIGNAL(triggered()), this, SLOT(pixelLineProfile()));
//    connect(actionIntensityTable, SIGNAL(triggered()), this, SLOT(intensityTable()));
//    connect(actionActivateWindow, SIGNAL(triggered()), this, SLOT(activateWindow()));
//    connect(actionMinimizeWindow, SIGNAL(triggered()), this, SLOT(minimizeWindow()));
//    connect(actionMaximizeWindow, SIGNAL(triggered()), this, SLOT(maximizeWindow()));
//    connect(actionPrintWindow, SIGNAL(triggered()), this, SLOT(printWindow()));
//    connect(actionEditSurfacePlot, SIGNAL(triggered()), this, SLOT(editSurfacePlot()));
//    connect(actionAdd3DData, SIGNAL(triggered()), this, SLOT(add3DData()));
//    connect(actionInvertMatrix, SIGNAL(triggered()), this, SLOT(invertMatrix()));
//    connect(actionMatrixDeterminant, SIGNAL(triggered()), this, SLOT(matrixDeterminant()));
//    connect(actionConvertMatrix, SIGNAL(triggered()), this, SLOT(convertMatrixToTable()));
//    connect(actionConvertTable, SIGNAL(triggered()), this, SLOT(convertTableToMatrix()));
//    connect(actionEditCurveRange, SIGNAL(triggered()), this, SLOT(showCurveRangeDialog()));
//    connect(actionCopyStatusBarText, SIGNAL(triggered()), this, SLOT(copyStatusBarText()));

    // Make toolbars
    makeToolBars();

    connect(qobject_cast<QMdiArea*>(getMainWindow()->centralWidget()),
            &QMdiArea::subWindowActivated,
            this,
            &MainAlphaPlot::windowActivated);

    loadSettings();
    setAppColors();
    createLanguagesList();
    connect(this, SIGNAL(modified()), this, SLOT(modifiedProject()));

    /*connect(scriptEnv, &ScriptingEnv::error, this, &MainAlphaPlot::scriptError);
    connect(scriptEnv, &ScriptingEnv::print, this, &MainAlphaPlot::scriptPrint);*/
    // this has to be done after connecting scriptEnv
    scriptEnv->initialize();
}

// Distructor
MainAlphaPlot::~MainAlphaPlot()
{

    Q_FOREACH (QMdiSubWindow* window, subWindowsList()) {
        if (qobject_cast<Layout2D*>(window)) {
            qobject_cast<Layout2D*>(window)->setCloseWithoutColumnModeLockChange(true);
        }
        else if (qobject_cast<Layout3D*>(window)) {
            qobject_cast<Layout3D*>(window)->setCloseWithoutColumnModeLockChange(true);
        }
    }

    delete hiddenWindows;
    delete outWindows;
    //delete d_project;
    QApplication::clipboard()->clear(QClipboard::Clipboard);

}

MyWidget* MainAlphaPlot::getactiveMyWidget()
{
    return qobject_cast<MyWidget*>(getMainWindow()->getactiveMyWidget());
}

void MainAlphaPlot::verticalTowLayers()
{
    Layout2D* layout = newGraph2D();
    layout->addAxisRectWithAxis(QPair<int, int>(0, 0));
    layout->addAxisRectWithAxis(QPair<int, int>(1, 0));
}

void MainAlphaPlot::horizontalTowLayers()
{
    Layout2D* layout = newGraph2D();
    layout->addAxisRectWithAxis(QPair<int, int>(0, 0));
    layout->addAxisRectWithAxis(QPair<int, int>(0, 1));
}

void MainAlphaPlot::fourLayers()
{
    Layout2D* layout = newGraph2D();
    layout->addAxisRectWithAxis(QPair<int, int>(0, 0));
    layout->addAxisRectWithAxis(QPair<int, int>(0, 1));
    layout->addAxisRectWithAxis(QPair<int, int>(1, 0));
    layout->addAxisRectWithAxis(QPair<int, int>(1, 1));
}

void MainAlphaPlot::treeDWireFrame()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(
            QSurface3DSeries::DrawFlag::DrawWireframe);
}

void MainAlphaPlot::treeDSurface()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(QSurface3DSeries::DrawFlag::DrawSurface);
}

void MainAlphaPlot::treeDWireSurface()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(
            QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe);
}

void MainAlphaPlot::treeDWireFramePolar()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(
            QSurface3DSeries::DrawFlag::DrawWireframe);
    layout->getSurface3DModifier()->getGraph()->setPolar(true);
}

void MainAlphaPlot::treeDSurfacePolar()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(QSurface3DSeries::DrawFlag::DrawSurface);
    layout->getSurface3DModifier()->getGraph()->setPolar(true);
}

void MainAlphaPlot::treeDWireFrameSurfacePolar()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(
            QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe);
    layout->getSurface3DModifier()->getGraph()->setPolar(true);
}

void MainAlphaPlot::treeDScatterPolar()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Scatter);
    if (layout && layout->getScatter3DModifier())
        layout->getScatter3DModifier()->getGraph()->setPolar(true);
}

void MainAlphaPlot::treeDPolarSpectrogram()
{
    Layout3D* layout = plot3DMatrix(Graph3DCommon::Plot3DType::Surface);
    if (layout && layout->getSurface3DModifier())
        layout->getSurface3DModifier()->setSurfaceMeshType(QSurface3DSeries::DrawFlag::DrawSurface);
    layout->getSurface3DModifier()->getGraph()->setOrthoProjection(true);
    layout->getSurface3DModifier()->getGraph()->setPolar(true);
    layout->getSurface3DModifier()->getGraph()->setFlipHorizontalGrid(true);
    layout->getSurface3DModifier()->getGraph()->scene()->activeCamera()->setCameraPreset(
        Q3DCamera::CameraPreset::CameraPresetDirectlyAbove);
}


// Apply user settings
void MainAlphaPlot::applyUserSettings()
{
    qApp->setFont(appFont);
    this->setFont(appFont);
    //setScriptingLang(defaultScriptingLang);
}

// Make all toolbars
void MainAlphaPlot::makeToolBars()
{
    //// Set object names needed for restoreState()
    //fileToolbar->setObjectName(QString::fromLatin1("fileToolbar"));
    //editToolbar->setObjectName(QString::fromLatin1("editToolbar"));
    //graphToolsToolbar->setObjectName(QString::fromLatin1("graphToolsToolbar"));
    //plot2DToolbar->setObjectName(QString::fromLatin1("plot2DToolbar"));
    //tableToolbar->setObjectName(QString::fromLatin1("tableToolbar"));
    //matrix3DPlotToolbar->setObjectName(QString::fromLatin1("matrix3DPlotToolbar"));
    //graph3DToolbar->setObjectName(QString::fromLatin1("graph3DToolbar"));

    //// File tools toolbar
    //fileToolbar->addAction(ui_->actionNewProject);
    //QMenu* menu_new_aspect = new QMenu(this);
    //menu_new_aspect->addAction(ui_->actionNewTable);
    //menu_new_aspect->addAction(ui_->actionNewMatrix);
    //menu_new_aspect->addAction(ui_->actionNewNote);
    //menu_new_aspect->addAction(ui_->actionNewGraph);
    //menu_new_aspect->addAction(ui_->actionNewFunctionPlot);
    //menu_new_aspect->addAction(ui_->actionNew3DSurfacePlot);
    //btn_new_aspect_->setMenu(menu_new_aspect);
    //fileToolbar->addWidget(btn_new_aspect_);
    //fileToolbar->addAction(ui_->actionOpenAproj);
    //fileToolbar->addAction(ui_->actionOpenTemplate);
    //fileToolbar->addAction(ui_->actionImportASCII);
    //fileToolbar->addAction(ui_->actionSaveProject);
    //fileToolbar->addAction(ui_->actionSaveAsTemplate);
    //fileToolbar->addSeparator();
    //fileToolbar->addAction(ui_->actionPrint);
    //fileToolbar->addAction(actionExportPDF);
    //fileToolbar->addSeparator();
    //fileToolbar->addAction(actionShowProjectExplorer);
    //fileToolbar->addAction(actionShowResultsLog);
    //fileToolbar->addAction(ui_->actionLockToolbars);

    //// Edit tools toolbar
    //editToolbar->addAction(ui_->actionUndo);
    //editToolbar->addAction(ui_->actionRedo);
    //editToolbar->addAction(ui_->actionCutSelection);
    //editToolbar->addAction(ui_->actionCopySelection);
    //editToolbar->addAction(ui_->actionPasteSelection);
    //editToolbar->addAction(ui_->actionClearSelection);

    //// 2D Graph tools toolbar
    //ui_->actionDisableGraphTools->setChecked(true);
    //graphToolsToolbar->addAction(ui_->actionDisableGraphTools);
    //graphToolsToolbar->addAction(ui_->actionGraphDataReader);
    //graphToolsToolbar->addAction(ui_->actionGraphScreenReader);
    //graphToolsToolbar->addAction(ui_->actionGraphSelectDataRange);
    //graphToolsToolbar->addAction(ui_->actionGraphMoveDataPoints);
    //graphToolsToolbar->addAction(ui_->actionGraphRemoveBadDataPoints);
    //graphToolsToolbar->addAction(ui_->actionGraphDragRange);
    //graphToolsToolbar->addAction(ui_->actionGraphZoomRange);
    //graphToolsToolbar->addAction(ui_->actionGraphRescaleShowAll);
    //graphToolsToolbar->addSeparator();
    //QMenu* menu_layers = new QMenu(this);
    //btn_layout_->setMenu(menu_layers);
    //graphToolsToolbar->addWidget(btn_layout_);
    //menu_layers->addAction(ui_->actionAddNestedLayout);
    ////menu_layers->addMenu(ui_->menuAddLayout);//koffa
    //menu_layers->addAction(ui_->actionRemoveLayout);
    //menu_layers->addAction(ui_->actionArrangeLayout);
    //QMenu* menu_curves = new QMenu(this);
    //btn_curves_->setMenu(menu_curves);
    //graphToolsToolbar->addWidget(btn_curves_);
    //menu_curves->addAction(ui_->actionAddRemoveCurve);
    //menu_curves->addAction(ui_->actionAddErrorBars);
    //menu_curves->addAction(ui_->actionAddFunctionCurve);
    //menu_curves->addAction(ui_->actionLegendReorder);
    //QMenu* menu_plot_enrichments = new QMenu(this);
    //btn_plot_enrichments_->setMenu(menu_plot_enrichments);
    //graphToolsToolbar->addWidget(btn_plot_enrichments_);
    //menu_plot_enrichments->addAction(ui_->actionAddText);
    //menu_plot_enrichments->addAction(ui_->actionDrawArrow);
    //menu_plot_enrichments->addAction(ui_->actionDrawLine);
    //menu_plot_enrichments->addAction(ui_->actionAddTimeStamp);
    //menu_plot_enrichments->addAction(ui_->actionAddImage);

    //// 2D plots tool toolbar
    //QMenu* menu_plot_scatters = new QMenu(this);
    //btn_plot_scatters_->setMenu(menu_plot_scatters);
    //plot2DToolbar->addWidget(btn_plot_scatters_);
    //menu_plot_scatters->addAction(ui_->actionPlot2DScatter);
    //menu_plot_scatters->addAction(ui_->actionPlot2DScatterXErr);
    //menu_plot_scatters->addAction(ui_->actionPlot2DScatterYErr);
    //menu_plot_scatters->addAction(ui_->actionPlot2DScatterXYErr);
    //QMenu* menu_plot_linespoints = new QMenu(this);
    //btn_plot_linespoints_->setMenu(menu_plot_linespoints);
    //plot2DToolbar->addWidget(btn_plot_linespoints_);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DLine);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DScatter);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DLineSymbol);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DVerticalDropLines);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DSpline);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DVerticalSteps);
    //menu_plot_linespoints->addAction(ui_->actionPlot2DHorizontalSteps);
    //QMenu* menu_plot_bars = new QMenu(this);
    //btn_plot_bars_->setMenu(menu_plot_bars);
    //plot2DToolbar->addWidget(btn_plot_bars_);
    //menu_plot_bars->addAction(ui_->actionPlot2DVerticalBars);
    //menu_plot_bars->addAction(ui_->actionPlot2DVerticalStackedBars);
    //menu_plot_bars->addAction(ui_->actionPlot2DVerticalGroupedBars);
    //menu_plot_bars->addAction(ui_->actionPlot2DHorizontalBars);
    //menu_plot_bars->addAction(ui_->actionPlot2DHorizontalStackedBars);
    //menu_plot_bars->addAction(ui_->actionPlot2DHorizontalGroupedBars);
    //plot2DToolbar->addAction(ui_->actionPlot2DArea);
    //plot2DToolbar->addAction(ui_->actionPlot2DChannelFill);
    //plot2DToolbar->addAction(ui_->actionPlot2DStatHistogram);
    //plot2DToolbar->addAction(ui_->actionPlot2DStatBox);
    //QMenu* menu_plot_vect = new QMenu(this);
    //btn_plot_vect_->setMenu(menu_plot_vect);
    //plot2DToolbar->addWidget(btn_plot_vect_);
    //menu_plot_vect->addAction(ui_->actionPlot2DVectorsXYXY);
    //menu_plot_vect->addAction(ui_->actionPlot2DVectorsXYAM);
    //QMenu* menu_plot_pie = new QMenu(this);
    //btn_plot_pie_->setMenu(menu_plot_pie);
    //plot2DToolbar->addWidget(btn_plot_pie_);
    //menu_plot_pie->addAction(ui_->actionPlot2DPie);
    //menu_plot_pie->addAction(ui_->actionPlot2DHalfPie);
    //plot2DToolbar->addSeparator();
    //plot2DToolbar->addAction(ui_->actionPlot3DScatter);
    //plot2DToolbar->addAction(ui_->actionPlot3DTrajectory);
    //plot2DToolbar->addAction(ui_->actionPlot3DRibbon);
    //plot2DToolbar->addAction(ui_->actionPlot3DBar);

    //// Matrix tools toolbar
    //matrix3DPlotToolbar->addAction(ui_->action3DWireFrame);
    //matrix3DPlotToolbar->addAction(ui_->action3DSurface);
    //matrix3DPlotToolbar->addAction(ui_->action3DWireSurface);
    //matrix3DPlotToolbar->addSeparator();
    //matrix3DPlotToolbar->addAction(ui_->actionPlot3DBar);
    //matrix3DPlotToolbar->addAction(ui_->actionPlot3DScatter);
    //matrix3DPlotToolbar->addSeparator();
    //matrix3DPlotToolbar->addAction(ui_->action3DCountourColorFill);
    //matrix3DPlotToolbar->addAction(ui_->action3DCountourLines);
    //matrix3DPlotToolbar->addAction(ui_->action3DGreyScaleMap);

    //// Graph 3D orentation actions
    //graph3DToolbar->addAction(actionResetZoomfactor_);
    //graph3DToolbar->addAction(actionResetCameraFront_);
    //graph3DToolbar->addSeparator();

    //// Graph 3D floor actions
    //actionplot3dmodecolumnselect_->setCheckable(true);
    //actionplot3dmoderowselect_->setCheckable(true);
    //actionplot3dmodeitemselect_->setCheckable(true);
    //actionplot3dmodenoneselect_->setCheckable(true);
    //graph3DToolbar->addAction(actionplot3dmodecolumnselect_);
    //graph3DToolbar->addAction(actionplot3dmoderowselect_);
    //graph3DToolbar->addAction(actionplot3dmodeitemselect_);
    //graph3DToolbar->addAction(actionplot3dmodenoneselect_);
    //actionplot3dmodenoneselect_->setChecked(true);
    //graph3DToolbar->addSeparator();

    //// Graph 3D animation actions
    //actionplot3dAnimate_->setCheckable(true);
    //graph3DToolbar->addAction(actionplot3dAnimate_);

    //// Set toolbar icon size
    //fileToolbar->setIconSize(QSize(24, 24));
    //editToolbar->setIconSize(QSize(24, 24));
    //graphToolsToolbar->setIconSize(QSize(24, 24));
    //plot2DToolbar->setIconSize(QSize(24, 24));
    //tableToolbar->setIconSize(QSize(24, 24));
    //matrix3DPlotToolbar->setIconSize(QSize(24, 24));
    //graph3DToolbar->setIconSize(QSize(24, 24));

    //// Add toolbars
    //addToolBar(Qt::TopToolBarArea, fileToolbar);
    //addToolBar(editToolbar);
    //addToolBar(graphToolsToolbar);
    //addToolBar(Qt::LeftToolBarArea, plot2DToolbar);
    //addToolBar(Qt::TopToolBarArea, tableToolbar);
    //addToolBar(Qt::BottomToolBarArea, graph3DToolbar);
    //addToolBar(Qt::BottomToolBarArea, matrix3DPlotToolbar);

    //// Disable toolbars
    //graphToolsToolbar->setEnabled(false);
    //tableToolbar->setEnabled(false);
    //plot2DToolbar->setEnabled(false);
    //matrix3DPlotToolbar->setEnabled(false);
    //graph3DToolbar->setEnabled(false);

    //// Graph 3D orentation actions
    //connect(actionResetCameraFront_, SIGNAL(triggered()), this,
    //    SLOT(setCameraPresetFront()));
    //connect(actionResetZoomfactor_, SIGNAL(triggered()), this,
    //    SLOT(resetZoomfactor()));
    //// Graph 3D floor Actions
    //connect(groupplot3dselectionmode_, SIGNAL(triggered(QAction*)), this,
    //    SLOT(pickSelectionType(QAction*)));
    //// Graph 3D animation actions
    //connect(actionplot3dAnimate_, SIGNAL(toggled(bool)), this,
    //    SLOT(toggle3DAnimation(bool)));
}

// Lock/unlock toolbar move
void MainAlphaPlot::lockToolbars(const bool status)
{
    /*if (status) {
         fileToolbar->setMovable(false);
         editToolbar->setMovable(false);
         graphToolsToolbar->setMovable(false);
         graph3DToolbar->setMovable(false);
         plot2DToolbar->setMovable(false);
         tableToolbar->setMovable(false);
         matrix3DPlotToolbar->setMovable(false);
         ui_->actionLockToolbars->setIcon(
             IconLoader::load(QString::fromLatin1("lock"), IconLoader::LightDark));
     }
     else {
         fileToolbar->setMovable(true);
         editToolbar->setMovable(true);
         graphToolsToolbar->setMovable(true);
         graph3DToolbar->setMovable(true);
         plot2DToolbar->setMovable(true);
         tableToolbar->setMovable(true);
         matrix3DPlotToolbar->setMovable(true);
         ui_->actionLockToolbars->setIcon(
             IconLoader::load(QString::fromLatin1("unlock"), IconLoader::LightDark));
     }*/
}

// Dynamic menu
void MainAlphaPlot::customMenu(QMdiSubWindow* subwindow)
{
    //    menuBar()->clear();
    ///*    menuBar()->addMenu(ui_->menuFile);
    //    menuBar()->addMenu(ui_->menuEdit);
    //    menuBar()->addMenu(ui_->menuView);
    //    menuBar()->addMenu(ui_->menuScripting);*/

    //    // use the same shortcut (Ctrl+Return) should not be enabled at this time
    //    ui_->actionEvaluateExpression->setEnabled(false);

    //    // There are active windows
    //    if (subwindow) {
    //        ui_->actionPrintAllPlots->setEnabled(projectHas2DPlots());
    //        ui_->actionPrint->setEnabled(true);
    //        ui_->actionCutSelection->setEnabled(true);
    //        ui_->actionCopySelection->setEnabled(true);
    //        ui_->actionPasteSelection->setEnabled(true);
    //        ui_->actionClearSelection->setEnabled(true);
    //        ui_->actionSaveAsTemplate->setEnabled(true);

    //        // Active window is a 2D plot
    //        if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
    //            //menuBar()->addMenu(ui_->menuGraph);
    //            //menuBar()->addMenu(ui_->menuTools);
    //            //menuBar()->addMenu(ui_->menuGraph2DAnalysis);
    //            //ui_->menuExportGraph->setEnabled(true);//koffa
    //            ui_->actionExportASCII->setEnabled(false);

    //            // Active window is a 3D plot
    //        }
    //        else if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {
    //            disableActions();
    //            ui_->actionPrint->setEnabled(true);
    //            ui_->actionSaveAsTemplate->setEnabled(true);
    //            //ui_->menuExportGraph->setEnabled(true);//koffa

    //            // Active window is a table
    //        }
    //        else if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
    //           /* menuBar()->addMenu(ui_->menuPlot);
    //            menuBar()->addMenu(ui_->menuTableAnalysis);
    //            ui_->actionExportASCII->setEnabled(true);
    //            ui_->menuExportGraph->setEnabled(false);
    //            ui_->menuTable->clear();*///koffa
    //            static_cast<Table*>(subwindow)->d_future_table->fillProjectMenu(
    //                ui_->menuTable);
    //            /*ui_->menuTable->addSeparator();
    //            ui_->menuTable->addAction(ui_->actionExportASCII);
    //            ui_->menuTable->addSeparator();
    //            ui_->menuTable->addAction(actionConvertTable);
    //            menuBar()->addMenu(ui_->menuTable);*///koffa

    //            // Active window is a matrix
    //        }
    //        else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow)) {
    //            menuBar()->addMenu(ui_->menu3DPlot);
    //            ui_->menuMatrix->clear();
    //            static_cast<Matrix*>(subwindow)->d_future_matrix->fillProjectMenu(
    //                ui_->menuMatrix);
    //            ui_->menuMatrix->addSeparator();
    //            ui_->menuMatrix->addAction(actionInvertMatrix);
    //            ui_->menuMatrix->addAction(actionMatrixDeterminant);
    //            ui_->menuMatrix->addSeparator();
    //            ui_->menuMatrix->addAction(actionConvertMatrix);
    //            menuBar()->addMenu(ui_->menuMatrix);

    //            // Active window is a note
    //        }
    //        else if (isActiveSubWindow(subwindow, SubWindowType::NoteSubWindow)) {
    //            ui_->actionSaveAsTemplate->setEnabled(false);
    //            ui_->actionEvaluateExpression->setEnabled(true);
    //            ui_->actionExecute->disconnect(SIGNAL(triggered()));
    //            ui_->actionExecuteAll->disconnect(SIGNAL(triggered()));
    //            ui_->actionEvaluateExpression->disconnect(SIGNAL(triggered()));
    //            connect(ui_->actionExecute, SIGNAL(triggered()), subwindow,
    //                SLOT(execute()));
    //            connect(ui_->actionExecuteAll, SIGNAL(triggered()), subwindow,
    //                SLOT(executeAll()));
    //            connect(ui_->actionEvaluateExpression, SIGNAL(triggered()), subwindow,
    //                SLOT(evaluate()));
    //        }
    //        else
    //            disableActions();  // None of the above

    //        menuBar()->addMenu(ui_->menuWindow);
    //    }
    //    else
    //        disableActions();  // No active Window

    //    menuBar()->addMenu(ui_->menuHelp);
}

// Dynamic toolbar
void MainAlphaPlot::customToolBars(QMdiSubWindow* subwindow)
{
    // There are active windows
    //if (subwindow) {
    //    if (!projectHas3DPlots()) graph3DToolbar->setEnabled(false);
    //    if (!projectHas2DPlots()) graphToolsToolbar->setEnabled(false);
    //    if (!projectHasMatrices()) matrix3DPlotToolbar->setEnabled(false);
    //    if (tableWindows().count() <= 0) {
    //        tableToolbar->setEnabled(false);
    //        plot2DToolbar->setEnabled(false);
    //    }

    //    if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
    //        graphToolsToolbar->setEnabled(true);
    //        graph3DToolbar->setEnabled(false);
    //        tableToolbar->setEnabled(false);
    //        matrix3DPlotToolbar->setEnabled(false);

    //        // 3D plots
    //        ui_->actionPlot3DRibbon->setEnabled(false);
    //        ui_->actionPlot3DScatter->setEnabled(false);
    //        ui_->actionPlot3DTrajectory->setEnabled(false);
    //        ui_->actionPlot3DBar->setEnabled(false);
    //        // } else
    //        plot2DToolbar->setEnabled(false);
    //    }
    //    else if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
    //        tableToolbar->clear();
    //        static_cast<Table*>(subwindow)->d_future_table->fillProjectToolBar(
    //            tableToolbar);
    //        tableToolbar->setEnabled(true);

    //        graphToolsToolbar->setEnabled(false);
    //        graph3DToolbar->setEnabled(false);
    //        matrix3DPlotToolbar->setEnabled(false);

    //        plot2DToolbar->setEnabled(true);
    //        // plot tools managed by d_plot_mapper
    //        for (int i = 0; i <= static_cast<int>(Graph::VerticalSteps); i++) {
    //            QAction* a = static_cast<QAction*>(d_plot_mapper->mapping(i));
    //            if (a) a->setEnabled(true);
    //        }
    //        // others
    //        ui_->actionPlot2DPie->setEnabled(true);
    //        ui_->actionPlot2DVectorsXYAM->setEnabled(true);
    //        ui_->actionPlot2DVectorsXYXY->setEnabled(true);
    //        ui_->actionPlot2DStatBox->setEnabled(true);
    //        // 3D plots
    //        ui_->actionPlot3DRibbon->setEnabled(true);
    //        ui_->actionPlot3DScatter->setEnabled(true);
    //        ui_->actionPlot3DTrajectory->setEnabled(true);
    //        ui_->actionPlot3DBar->setEnabled(true);
    //    }
    //    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow)) {
    //        graphToolsToolbar->setEnabled(false);
    //        graph3DToolbar->setEnabled(false);
    //        tableToolbar->setEnabled(false);
    //        plot2DToolbar->setEnabled(false);
    //        matrix3DPlotToolbar->setEnabled(true);
    //    }
    //    else if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {
    //        graphToolsToolbar->setEnabled(false);
    //        tableToolbar->setEnabled(false);
    //        plot2DToolbar->setEnabled(false);
    //        matrix3DPlotToolbar->setEnabled(false);
    //        graph3DToolbar->setEnabled(true);
    //        custom3DActions(subwindow);
    //    }
    //    else if (isActiveSubWindow(subwindow, SubWindowType::NoteSubWindow)) {
    //        graphToolsToolbar->setEnabled(false);
    //        graph3DToolbar->setEnabled(false);
    //        tableToolbar->setEnabled(false);
    //        plot2DToolbar->setEnabled(false);
    //        matrix3DPlotToolbar->setEnabled(false);
    //    }

    //}
    //else {
    //    graphToolsToolbar->setEnabled(false);
    //    tableToolbar->setEnabled(false);
    //    plot2DToolbar->setEnabled(false);
    //    graph3DToolbar->setEnabled(false);
    //    matrix3DPlotToolbar->setEnabled(false);
    //}
}

// Disable selected QActions
void MainAlphaPlot::disableActions()
{
    /* ui_->actionSaveAsTemplate->setEnabled(false);
     ui_->actionPrintAllPlots->setEnabled(false);
     ui_->actionPrint->setEnabled(false);
     ui_->actionExportASCII->setEnabled(false);
     ui_->menuExportGraph->setEnabled(false);
     ui_->actionUndo->setEnabled(false);
     ui_->actionRedo->setEnabled(false);
     ui_->actionCutSelection->setEnabled(false);
     ui_->actionCopySelection->setEnabled(false);
     ui_->actionPasteSelection->setEnabled(false);
     ui_->actionClearSelection->setEnabled(false);*/
}

void MainAlphaPlot::plot3DRibbon()
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow))
        return;

    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (!validFor3DPlot(table))
        return;
    dataPlot3D(table, Graph3DCommon::Plot3DType::Surface);
}

void MainAlphaPlot::plot3DBars()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
        Table* table = qobject_cast<Table*>(subwindow);
        if (!validFor3DPlot(table))
            return;

        dataPlotXYZ(table, Graph3DCommon::Plot3DType::Bar);
    }
    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow))
        plot3DMatrix(Graph3DCommon::Plot3DType::Bar);
}

void MainAlphaPlot::plot3DScatter()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
        Table* table = qobject_cast<Table*>(subwindow);
        if (!validFor3DPlot(table))
            return;

        dataPlotXYZ(table, Graph3DCommon::Plot3DType::Scatter);
    }
    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow))
        plot3DMatrix(Graph3DCommon::Plot3DType::Scatter);
}

void MainAlphaPlot::plot3DTrajectory()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
        Table* table = qobject_cast<Table*>(subwindow);
        if (!validFor3DPlot(table))
            return;

        dataPlotXYZ(table, Graph3DCommon::Plot3DType::Scatter);
    }
}

void MainAlphaPlot::plotPie(const Graph2DCommon::PieStyle& style)
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow))
        return;

    Table* table = qobject_cast<Table*>(getactiveMyWidget());

    QStringList selectedcolumns = table->selectedColumns();
    if (selectedcolumns.count() != 2) {
        QMessageBox::warning(this, tr("Plot error"),
                             tr("Please select an X column with labels and Y column "
                                "with values to plot!"));
        return;
    }

    Column* xcol = nullptr;
    Column* ycol = nullptr;
    Q_FOREACH (QString colname, selectedcolumns) {
        (table->YColumns().contains(colname)) ? ycol = table->column(table->colIndex(colname))
                                              : xcol = table->column(table->colIndex(colname));
    }

    if (!xcol || !ycol) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Please select an X column with labels and Y column "
                                "with values to plot!"));
        return;
    }

    if (xcol->dataType() != AlphaPlot::ColumnDataType::TypeString) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Please select an X column with labels and set the "
                                "column type as Text!"));
        return;
    }

    if (selectedcolumns.count() == 2) {
        Layout2D* layout = newGraph2D();
        layout->generatePie2DPlot(style, table, xcol, ycol, table->firstSelectedRow(),
                                  table->firstSelectedRow() + table->selectedRowCount() - 1);
    }
    else
        QMessageBox::warning(this, tr("Error"),
                             tr("Please select a X column wth labels and Y column "
                                "with values to plot!"));
}

void MainAlphaPlot::plotVectXYXY()
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow))
        return;

    Table* table = qobject_cast<Table*>(getactiveMyWidget());

    if (!validFor2DPlot(table, Graph::VectXYXY))
        return;

    QStringList list = table->selectedColumns();
    if (list.count() == 4) {
        Column* xcol = nullptr;
        QList<Column*> ycollist;
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString colname, list) {
            if (table->YColumns().contains(colname)) {
                ycollist << table->column(table->colIndex(colname));
            }
            else {
                xcol = table->column(table->colIndex(colname));
            }
        }
        Q_ASSERT(ycollist.size() == 3);

        Layout2D* layout = newGraph2D();
        layout->generateVector2DPlot(Vector2D::VectorPlot::XYXY, table, xcol, ycollist.at(0),
                                     ycollist.at(1), ycollist.at(2), table->firstSelectedRow(),
                                     table->firstSelectedRow() + table->selectedRowCount() - 1);
    }
    else
        QMessageBox::warning(this, tr("Error"),
                             tr("Please select four columns for this operation!"));
}

void MainAlphaPlot::plotVectXYAM()
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow))
        return;

    Table* table = qobject_cast<Table*>(getactiveMyWidget());

    if (!validFor2DPlot(table, Graph::VectXYAM))
        return;

    QStringList s = table->selectedColumns();
    if (s.count() == 4) {
        Column* xcol = nullptr;
        QList<Column*> ycollist;
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString colname, list) {
            if (table->YColumns().contains(colname)) {
                ycollist << table->column(table->colIndex(colname));
            }
            else {
                xcol = table->column(table->colIndex(colname));
            }
        }
        Q_ASSERT(ycollist.size() == 3);

        Layout2D* layout = newGraph2D();
        layout->generateVector2DPlot(Vector2D::VectorPlot::XYAM, table, xcol, ycollist.at(0),
                                     ycollist.at(1), ycollist.at(2), table->firstSelectedRow(),
                                     table->firstSelectedRow() + table->selectedRowCount() - 1);
    }
    else
        QMessageBox::warning(this, tr("Error"),
                             tr("Please select four columns for this operation!"));
}

void MainAlphaPlot::renameListViewItem(const QString& oldName, const QString& newName)
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        QList<QTreeWidgetItem*> items =
            plotExplorer->listView->findItems(oldName, Qt::MatchExactly, 0);
        Q_FOREACH (QTreeWidgetItem* item, items) {
            if (item)
                item->setText(0, newName);
        }
    }
}

void MainAlphaPlot::setListViewLabel(const QString& caption, const QString& label)
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        QList<QTreeWidgetItem*> items =
            plotExplorer->listView->findItems(caption, Qt::MatchExactly, 0);
        Q_FOREACH (QTreeWidgetItem* item, items) {
            if (item)
                item->setText(4, label);
        }
    }
    
}

void MainAlphaPlot::setListViewDate(const QString& caption, const QString& date)
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        QList<QTreeWidgetItem*> items =
            plotExplorer->listView->findItems(caption, Qt::MatchExactly, 0);
        Q_FOREACH (QTreeWidgetItem* item, items) {
            if (item)
                item->setText(3, date);
        }
    
    }

}

void MainAlphaPlot::setListViewView(const QString& caption, const QString& view)
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        QList<QTreeWidgetItem*> items =
            plotExplorer->listView->findItems(caption, Qt::MatchExactly, 0);
        Q_FOREACH (QTreeWidgetItem* item, items) {
            if (item)
                item->setText(2, view);
        }
    }
}

QString MainAlphaPlot::listViewDate(const QString& caption)
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (!this->plotExplorer)
        return QString::fromLatin1("");

    QList<QTreeWidgetItem*> items = plotExplorer->listView->findItems(caption, Qt::MatchExactly, 0);
    Q_FOREACH (QTreeWidgetItem* item, items) {
        if (item) {
            return item->text(3);
        }
        else {
            return QString::fromLatin1("");
        }
    }
    return QString::fromLatin1("");
}

void MainAlphaPlot::add3DData()
{
    //if (tableWindows().count() <= 0) {
    //    QMessageBox::warning(
    //        this, tr("Warning"),
    //        tr("<h4>There are no tables available in this project.</h4>"
    //            "<p><h4>Please create a table and try again!</h4>"));
    //    return;
    //}

    //// TODO: string list -> Column * list
    //QStringList zColumns = columnsList(AlphaPlot::Z);
    //if (static_cast<int>(zColumns.count()) <= 0) {
    //    QMessageBox::critical(
    //        this, tr("Warning"),
    //        tr("There are no available columns with plot designation set to Z!"));
    //    return;
    //}

    //DataSetDialog* ad = new DataSetDialog(tr("Column") + QString::fromLatin1(" : "), this);
    //ad->setAttribute(Qt::WA_DeleteOnClose);
    //ad->setWindowTitle(tr("Choose data set"));
    //ad->setCurveNames(zColumns);
    //ad->exec();
}

void MainAlphaPlot::change3DData()
{
    //DataSetDialog* ad = new DataSetDialog(tr("Column") + QString::fromLatin1(" : "), this);
    //ad->setAttribute(Qt::WA_DeleteOnClose);
    //connect(ad, SIGNAL(options(const QString&)), this,
    //    SLOT(change3DData(const QString&)));

    //ad->setWindowTitle(tr("Choose data set"));
    //// TODO: string list -> Column * list
    //ad->setCurveNames(columnsList(AlphaPlot::Z));
    //ad->exec();
}

void MainAlphaPlot::change3DMatrix()
{
    //DataSetDialog* ad = new DataSetDialog(tr("Matrix") + QString::fromLatin1(" : "), this);
    //ad->setAttribute(Qt::WA_DeleteOnClose);
    //connect(ad, SIGNAL(options(const QString&)), this,
    //    SLOT(change3DMatrix(const QString&)));

    //ad->setWindowTitle(tr("Choose matrix to plot"));
    //ad->setCurveNames(matrixNames());

    //Layout3D* layout = qobject_cast<Layout3D*>(getactiveMyWidget());
    //// if (layout && layout->getMatrix())
    ////  ad->setCurentDataSet(layout->getMatrix()->name());
    //ad->exec();
}

void MainAlphaPlot::change3DMatrix(const QString& matrix_name)
{
    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    Layout3D* layout = qobject_cast<Layout3D*>(getactiveMyWidget());
    Matrix* mat = matrix(matrix_name);
    // if (m && g) g->changeMatrix(m);
    Q_EMIT modified();
}

void MainAlphaPlot::add3DMatrixPlot()
{
    /*QStringList matrices = matrixNames();
     if (static_cast<int>(matrices.count()) <= 0) {
         QMessageBox::warning(
             this, tr("Warning"),
             tr("<h4>There are no matrices available in this project.</h4>"
                 "<p><h4>Please create a matrix and try again!</h4>"));
         return;
     }

     DataSetDialog* ad = new DataSetDialog(tr("Matrix") + QString::fromLatin1(" :"), this);
     ad->setAttribute(Qt::WA_DeleteOnClose);
     ;

     ad->setWindowTitle(tr("Choose matrix to plot"));
     ad->setCurveNames(matrices);
     ad->exec();*/
}

void MainAlphaPlot::change3DData(const QString& colName)
{
    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    Q_EMIT modified();
}

void MainAlphaPlot::editSurfacePlot()
{
    if (isActiveSubwindow(SubWindowType::Plot3DSubWindow)) {}
}

void MainAlphaPlot::newSurfacePlot()
{
    SurfaceDialog* sd = new SurfaceDialog(this);
    sd->setAttribute(Qt::WA_DeleteOnClose);
    connect(sd, SIGNAL(options(const QString&, double, double, double, double, double, double)),
            this, SLOT(newPlot3D(const QString&, double, double, double, double, double, double)));
    connect(sd, SIGNAL(clearFunctionsList()), this, SLOT(clearSurfaceFunctionsList()));

    sd->insertFunctionsList(surfaceFunc);

    if (sd->exec() == QDialog::Accepted)
    {
        updateSurfaceFuncList(sd->getBoxFunction()->currentText());
    }

}

Layout3D* MainAlphaPlot::newPlot3D(const QString& formula, const double xl, const double xr,
                                const double yl, const double yr, const double zl, const double zr)
{
    QString label = generateUniqueName(tr("Graph"));

    Layout3D* layout = newGraph3D(Graph3DCommon::Plot3DType::Surface, label);
    Graph3DCommon::Function3DData funcdata;
    funcdata.function = formula;
    funcdata.xl = xl;
    funcdata.xu = xr;
    funcdata.yl = yl;
    funcdata.yu = yr;
    funcdata.zl = zl;
    funcdata.zu = zr;
    funcdata.xpoints = 50;
    funcdata.ypoints = 50;
    layout->getSurface3DModifier()->setfunctiondata(generateFunction3ddata(funcdata), funcdata);

    Q_EMIT modified();
    return layout;
}

void MainAlphaPlot::updateSurfaceFuncList(const QString& s)
{
    surfaceFunc.removeAll(s);

    surfaceFunc.push_front(s);
    while (static_cast<int>(surfaceFunc.size()) > 10)
        surfaceFunc.pop_back();
}

Layout3D* MainAlphaPlot::newPlot3D(const QString& caption, const QString& formula, const double xl,
                                const double xr, const double yl, const double yr, const double zl,
                                const double zr)
{
    Layout3D* layout = newPlot3D(formula, xl, xr, yl, yr, zl, zr);

    QString label = caption;
    while (alreadyUsedName(label))
        label = layout->name();

    layout->setWindowTitle(label);
    layout->setName(label);
    return layout;
}

Layout3D* MainAlphaPlot::dataPlot3D(Table* table, const Graph3DCommon::Plot3DType& type)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    // prepare edata
    QList<Column*> selectedcols;
    Column* xcol = nullptr;
    Column* ycol = nullptr;
    Column* zcol = nullptr;
    QStringList list = table->selectedColumns();
    Q_FOREACH (QString colname, list)
        selectedcols << table->column(table->colIndex(colname));
    Q_FOREACH (Column* col, selectedcols) {
        if (col->plotDesignation() == AlphaPlot::PlotDesignation::X)
            xcol = col;
        else if (col->plotDesignation() == AlphaPlot::PlotDesignation::Y)
            ycol = col;
        else if (col->plotDesignation() == AlphaPlot::PlotDesignation::Z)
            zcol = col;
    }

    Layout3D* layout = nullptr;
    QString label = generateUniqueName(tr("Graph"));
    switch (type) {
        case Graph3DCommon::Plot3DType::Surface:
            qDebug() << "cannot plot surface using XYZ data";
            break;
        case Graph3DCommon::Plot3DType::Bar:
            layout = newGraph3D(Graph3DCommon::Plot3DType::Bar, label);
            layout->getBar3DModifier()->settabledata(table, xcol, ycol, zcol);
            break;
        case Graph3DCommon::Plot3DType::Scatter:
            layout = newGraph3D(Graph3DCommon::Plot3DType::Scatter, label);
            layout->getScatter3DModifier()->settabledata(table, xcol, ycol, zcol);
            break;
    }

    Q_EMIT modified();
    QApplication::restoreOverrideCursor();
    return layout;
}

Layout3D* MainAlphaPlot::dataPlotXYZ(Table* table, const Graph3DCommon::Plot3DType& type)
{
    Q_ASSERT(type != Graph3DCommon::Plot3DType::Surface);
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    // prepare edata
    QList<Column*> selectedcols;
    Column* xcol = nullptr;
    Column* ycol = nullptr;
    Column* zcol = nullptr;
    QStringList list = table->selectedColumns();
    Q_FOREACH (QString colname, list)
        selectedcols << table->column(table->colIndex(colname));
    Q_FOREACH (Column* col, selectedcols) {
        if (col->plotDesignation() == AlphaPlot::PlotDesignation::X)
            xcol = col;
        else if (col->plotDesignation() == AlphaPlot::PlotDesignation::Y)
            ycol = col;
        else if (col->plotDesignation() == AlphaPlot::PlotDesignation::Z)
            zcol = col;
    }

    Layout3D* layout = nullptr;
    QString label = generateUniqueName(tr("Graph"));
    switch (type) {
        case Graph3DCommon::Plot3DType::Surface:
            layout = nullptr;
            qDebug() << "dataplot XYZ not supported for Surface3D";
            break;
        case Graph3DCommon::Plot3DType::Bar:
            layout = newGraph3D(Graph3DCommon::Plot3DType::Bar, label);
            layout->getBar3DModifier()->settabledata(table, xcol, ycol, zcol);
            break;
        case Graph3DCommon::Plot3DType::Scatter:
            layout = newGraph3D(Graph3DCommon::Plot3DType::Scatter, label);
            layout->getScatter3DModifier()->settabledata(table, xcol, ycol, zcol);
            break;
    }

    Q_EMIT modified();
    QApplication::restoreOverrideCursor();
    return layout;
}

Matrix* MainAlphaPlot::importImage()
{
    QList<QByteArray> list = QImageReader::supportedImageFormats();
    QString filter = tr("Images") + QString::fromLatin1(" (");
    QString aux1;
    QString aux2;
    Q_FOREACH (QByteArray item, list) {
        aux1 = QString::fromLatin1(" *.") + QString::fromLatin1(item) + QString::fromLatin1(" ");
        aux2 += QString::fromLatin1(" *.") + QString::fromLatin1(item) + QString::fromLatin1(";;");
        filter += aux1;
    }
    filter += QString::fromLatin1(");;") + aux2;

    QString fn =
        QFileDialog::getOpenFileName(this, tr("Import image from file"), imagesDirPath, filter);
    if (!fn.isEmpty()) {
        QFileInfo fi(fn);
        imagesDirPath = fi.absolutePath();
        return importImage(fn);
    }
    else
        return nullptr;
}

void MainAlphaPlot::loadImage()
{
    QList<QByteArray> list = QImageReader::supportedImageFormats();
    QString filter = tr("Images") + QString::fromLatin1(" (");
    QString aux1;
    QString aux2;
    Q_FOREACH (QByteArray item, list) {
        aux1 = QString::fromLatin1(" *.") + QString::fromLatin1(item) + QString::fromLatin1(" ");
        aux2 += QString::fromLatin1(" *.") + QString::fromLatin1(item) + QString::fromLatin1(";;");
        filter += aux1;
    }
    filter += QString::fromLatin1(");;") + aux2;

    QString fn =
        QFileDialog::getOpenFileName(this, tr("Load image from file"), imagesDirPath, filter);
    if (!fn.isEmpty()) {
        loadImage(fn);
        QFileInfo fi(fn);
        imagesDirPath = fi.absolutePath();
    }
}

void MainAlphaPlot::loadImage(const QString& fn)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    if (!QPixmap(fn).isNull()) {
        Layout2D* layout = newGraph2D();
        layout->setBackgroundImage(fn);
    }
    else
        qDebug() << QString::fromLatin1("unrecognised image file name %1").arg(fn);
    QApplication::restoreOverrideCursor();
}

Layout2D* MainAlphaPlot::newGraph2D(const QString& caption)
{
    Layout2D* layout2d = new Layout2D(QString::fromLatin1(""), getMainWindow()->centralWidget(),
                                      QString::fromLatin1(""), 0);
    layout2d->setAttribute(Qt::WA_DeleteOnClose);
    layout2d->askOnCloseEvent(confirmClosePlot2D);
    QString label = caption;
    while (alreadyUsedName(label))
        label = generateUniqueName(tr("Graph"));

    current_folder->addWindow(layout2d);
    layout2d->setFolder(current_folder);
    getMainWindow()->addSubWindow(layout2d);

    layout2d->setWindowTitle(label);
    layout2d->setName(label);
    layout2d->setWindowIcon(
        IconLoader::load(QString::fromLatin1("edit-graph"), IconLoader::LightDark));
    addListViewItem(layout2d);

    layout2d->show();
    layout2d->setFocus();

    // window connections
    connect(layout2d, &Layout2D::closedWindow, this, &MainAlphaPlot::closeWindow);
    connect(layout2d, &Layout2D::hiddenWindow, this, &MainAlphaPlot::hideWindow);
    connect(layout2d, &Layout2D::statusChanged, this, &MainAlphaPlot::updateWindowStatus);
    connect(layout2d, &Layout2D::showTitleBarMenu, this, &MainAlphaPlot::showWindowTitleBarMenu);
    
        if (!this->plotPropertyeditor)
        this->plotPropertyeditor = getMainWindow()->findChild<PlotPropertyEditor*>();
    // Python console found?
        if (this->plotPropertyeditor) {
        connect(layout2d, &Layout2D::AxisRectRemoved, this->plotPropertyeditor,
                &PlotPropertyEditor::populateObjectBrowser);
        connect(layout2d, &Layout2D::AxisRectSwap, [=]() {
            this->plotPropertyeditor->populateObjectBrowser(static_cast<MyWidget*>(layout2d));
        });
        connect(layout2d, &Layout2D::layout2DResized, this->plotPropertyeditor,
                &PlotPropertyEditor::refreshCanvasRect);
        // axis connection resize property update
        connect(layout2d, &Layout2D::rescaleAxis2D, this->plotPropertyeditor,
                &PlotPropertyEditor::rescaleAxis2D);
        }
    
   
    connect(layout2d, &Layout2D::mousepressevent, [=](MyWidget* widget) {
        if (getactiveMyWidget() == widget)
            return;
        widget->setNormal();
            getMainWindow()->setActiveSubWindow(widget);
    });
    //connect(layout2d, &Layout2D::ResetPicker, [&]() {
    //    pickGraphTool(ui_->actionDisableGraphTools);
    //    ui_->actionDisableGraphTools->setChecked(true);
    //    });
   
    connect(layout2d, &Layout2D::datapoint, this, &MainAlphaPlot::multipeakfitappendpoints);
    connect(layout2d, &Layout2D::showContextMenu, this, &MainAlphaPlot::showWindowContextMenu);
   

    return layout2d;
}

Layout3D* MainAlphaPlot::newGraph3D(const Graph3DCommon::Plot3DType& type, const QString& caption)
{
    Layout3D* layout3d = new Layout3D(type, QString::fromLatin1(""),
                                      getMainWindow()->centralWidget(), QString::fromLatin1(""), 0);
    layout3d->setAttribute(Qt::WA_DeleteOnClose);
    layout3d->askOnCloseEvent(confirmClosePlot3D);
    QString label = caption;
    while (alreadyUsedName(label))
        label = generateUniqueName(tr("Graph"));

    current_folder->addWindow(layout3d);
    layout3d->setFolder(current_folder);
    getMainWindow()->addSubWindow(layout3d);

    layout3d->setWindowTitle(label);
    layout3d->setName(label);
    layout3d->setWindowIcon(
        IconLoader::load(QString::fromLatin1("edit-graph3d"), IconLoader::LightDark));
    addListViewItem(layout3d);

    layout3d->show();
    layout3d->setFocus();

    // window connections
    connect(layout3d, &MyWidget::closedWindow, this, &MainAlphaPlot::closeWindow);
    connect(layout3d, &MyWidget::hiddenWindow, this, &MainAlphaPlot::hideWindow);
    connect(layout3d, &MyWidget::statusChanged, this, &MainAlphaPlot::updateWindowStatus);
    connect(layout3d, &MyWidget::showTitleBarMenu, this, &MainAlphaPlot::showWindowTitleBarMenu);
    /*connect(layout3d, &Layout3D::dataAdded, visualObjectPropertyEditor,
         &PropertyEditor::populateObjectBrowser);*/
    connect(layout3d, &Layout3D::showContextMenu, this, &MainAlphaPlot::showWindowContextMenu);
    // QWindow doesnt pass mousepressevent to the container widget
    // so do it here manually
    connect(layout3d, &Layout3D::mousepressevent, this, [=]() {
        if (getactiveMyWidget() == layout3d)
            return;
        getMainWindow()->setActiveSubWindow(layout3d);
    });

    return layout3d;
}

QList<QPair<QPair<double, double>, double>>*
MainAlphaPlot::generateFunctiondata(const QString& formula, double xl, double xr, double yl, double yr,
                                 double zl, double zr)
{
    /*auto* data = new QList<QPair<QPair<double, double>, double>>();
      Q_UNUSED(zl);
      Q_UNUSED(zr);
      Q_ASSERT(!formula.isEmpty());
      QString name = QString::fromLatin1("3d-surface-function");
      std::unique_ptr<Script> script(scriptEnv->newScript(formula, 0, name));
      QObject::connect(script.get(),
          SIGNAL(error(const QString&, const QString&, int)), this,
          SLOT(scriptError(const QString&, const QString&, int)));

      const int points = 1000;
      const double xstep = (xr - xl) / static_cast<double>(points - 1);
      const double ystep = (yr - yl) / static_cast<double>(points - 1);
      double x = xl;
      double y = yl;
      double z = 0;
      for (int i = 0; i < points; i++, x += xstep, y += ystep) {
          script->setDouble(x, "x");
          script->setDouble(y, "y");
          QVariant result = script->eval();
          if (result.type() != QVariant::Double) {
              delete data;
              data = nullptr;
              return data;
          }
          QPair<QPair<double, double>, double> datapair;
          datapair.first.first = x;
          datapair.first.second = y;
          datapair.second = result.toDouble();
          z = result.toDouble();
          data->append(datapair);
          qDebug() << x << y << z;
      }
      return data;*/
    return nullptr;
}

void MainAlphaPlot::customizeTables(const Table::Custom& custom)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            customTable(qobject_cast<Table*>(subwindow), custom);
    }
}

void MainAlphaPlot::customizeCommentsTables()
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
            Table* table = qobject_cast<Table*>(subwindow);
            if (table)
                table->showComments(d_show_table_comments);
        }
    }
}

void MainAlphaPlot::customTable(Table* table, const Table::Custom& custom)
{
    if (!table)
        return;

    switch (custom) {
        case Table::Custom::BackgroundColor:
            (tableCustomColor)
                ? table->setTableBackgroundColor(tableBkgdColor)
                : table->setTableBackgroundColor(qApp->palette().color(QPalette::Window));
            break;
        case Table::Custom::HeaderColor:
            (tableCustomColor) ? table->setHeaderColor(tableHeaderColor)
                               : table->setHeaderColor(qApp->palette().color(QPalette::Text));
            break;
        case Table::Custom::TextColor:
            (tableCustomColor) ? table->setTableTextColor(tableBkgdColor)
                               : table->setTableTextColor(qApp->palette().color(QPalette::Text));
            break;
        case Table::Custom::HeaderFont:
            table->setHeaderFont(tableHeaderFont);
            break;
        case Table::Custom::TextFont:
            table->setTextFont(tableTextFont);
            break;
    }
}

// Used when importing an ASCII file
Table* MainAlphaPlot::newTable(const QString& fname, const QString& sep, int lines, bool renameCols,
                            bool stripSpaces, bool simplifySpaces, bool convertToNumeric,
                            QLocale numericLocale)
{
    Table* table = new Table(fname, sep, lines, renameCols, stripSpaces, simplifySpaces, convertToNumeric,
                  numericLocale, fname, getMainWindow()->centralWidget(), 0, Qt::Widget, ScriptingLangManager::newEnv(getMainWindow()));
    if (table) {
        table->setName(generateUniqueName(tr("Table")));
        d_project->addChild(table->d_future_table);
    }
    return table;
}

// Creates a new empty table
Table* MainAlphaPlot::newTable()
{
    Table* table = new Table(30, 2, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(("Table")).c_str()));
    d_project->addChild(table->d_future_table);
    table->showMaximized();

    /*  unsigned long steps = 100000000;
       Base::SequencerLauncher seq("Starting progress bar", 0);
       for (unsigned long i = 0; i < steps; i++)
       {
        seq.next();
       }*/
    return table;
}

Table* MainAlphaPlot::newTableShowVectors(const vec& x, const vec& y, const QString caption)
{
    if (x.size() != y.size()) {
        return nullptr;
    }

    Table* table = new Table(x.rows(), 2, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(QString::fromLatin1(
        App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(table->d_future_table);
    //if (table->name() != caption)// the table was renamed
    //{
    //    renamedTables << caption << table->name();

    //    QMessageBox::warning(this, tr("Renamed Window"),
    //                         tr("The table '%1' already exists. It has been renamed '%2'.")
    //                             .arg(caption)
    //                             .arg(table->name()));
    //}

    for (int i = 0; i < x.rows(); i++) {
        table->setCellValue(i, 0, x(i));
        table->setCellValue(i, 1, y(i));
    }

    /*QList<Column*> columns;
    columns << new Column(tr("Variables"), AlphaPlot::Numeric);
    columns << new Column(tr("Values"), AlphaPlot::Numeric);

    columns.at(0)->setPlotDesignation(AlphaPlot::X);
    columns.at(1)->setPlotDesignation(AlphaPlot::Y);

    for (int i = 0; i < x.rows(); i++) {
        columns.at(0)->setValueAt(i, x(i));
        columns.at(1)->setValueAt(i, y(i));
    }


    Table* table = newHiddenTable(sName, QString::fromLatin1("Resuls"), columns);
    Layout2D* layout = newGraph2D();

    if (!layout)
        return nullptr;
    if (!table)
        return nullptr;

    layout->generateCurve2DPlot(AxisRect2D::LineScatterType::Line2D, table, columns.at(0),
                                QList<Column*>() << columns.at(1), 0, table->numRows() - 1);*/

    return table;
}

Table* MainAlphaPlot::newTableShowVector(const vec& x, const QString caption)
{
    if (x.size() == 0) {
        return nullptr;
    }

    Table* table = new Table(x.rows(), 1, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(table->d_future_table);

    for (int i = 0; i < x.rows(); i++) {
        table->setCellValue(i, 0, x(i));
    }

    return table;
}

Table* MainAlphaPlot::newTableShowComplexVectors(const vec& x, const cx_vec& y, const QString caption, const int& complexRealImag)
{
    if (x.size() != y.size()) {
        return nullptr;
    }

    Table* table = new Table(x.rows(), 3, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(table->d_future_table);

        for (int i = 0; i < x.rows(); i++) {
        table->setCellValue(i, 0, x(i));
        table->setCellValue(i, 1, y(i).real());
        table->setCellValue(i, 2, y(i).imag());
    }

    return table;
}

Table* MainAlphaPlot::newTableShowMatrix(const mat& x, const QString caption)
{

    Table* table = new Table(x.rows(), x.cols(), QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(table->d_future_table);
 
    for (int i = 0; i < x.rows(); i++) {
        for (int j = 0; j < x.cols(); j++) {
            table->setCellValue(i, j, x(i, j));
        }
    }

    return table;
}

Table* MainAlphaPlot::newTableShowTensor(const cube& x, int index, const QString caption)
{
    Eigen::Tensor<double, 2> matrix_at_k = x.chip(index, 2);
    Eigen::Map<Eigen::MatrixXd> matrix_k(matrix_at_k.data(), matrix_at_k.dimension(0), matrix_at_k.dimension(1));
    return newTableShowMatrix(matrix_k, caption);
}

Table* MainAlphaPlot::newTableShowComplexTensor(const cx_cube& x, int index, const QString caption)
{
    Eigen::Tensor<std::complex<double>, 2> matrix_at_k = x.chip(index, 2);
    Eigen::Map<Eigen::MatrixXcd> matrix_k(matrix_at_k.data(), matrix_at_k.dimension(0), matrix_at_k.dimension(1));
    return newTableShowComplexMatrix(matrix_k, caption);
}

Table* MainAlphaPlot::newTableShowComplexMatrix(const cx_mat& x, const QString caption, const int& complexRealImag)
{
    Table* table1 = new Table(x.rows(), x.cols(), QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    Table* table2 = new Table(x.rows(), x.cols(), QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));

    table1->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()) + QString::fromLatin1("_Real"));
    table2->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()) + QString::fromLatin1("_Imag"));

    d_project->addChild(table1->d_future_table);
    d_project->addChild(table2->d_future_table);

    for (int i = 0; i < x.rows(); i++) {
        for (int j = 0; j < x.cols(); j++) {
            table1->setCellValue(i, j, x(i, j).real());
            table2->setCellValue(i, j, x(i, j).imag());

        }
    }
    return table1;
}

Table* MainAlphaPlot::newTableShowArrayPy(int rws, int cls, const std::vector<std::vector<double>> array, QString caption)
{
    Table* table = new Table(rws, cls, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(table->d_future_table);
 
    for (int i = 0; i < rws; i++) {
        for (int j = 0; j < cls; j++) {
            table->setCellValue(i, j, array[i][j]);
        }
    }

    return table;
}

// Used when opening a project file
Table* MainAlphaPlot::newTable(const QString& caption, int r, int c)
{
    Table* table = new Table(r, c, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(caption);
    d_project->addChild(table->d_future_table);
    if (table->name() != caption)// the table was renamed
    {
        renamedTables << caption << table->name();

        QMessageBox::warning(this, tr("Renamed Window"),
                             tr("The table '%1' already exists. It has been renamed '%2'.")
                                 .arg(caption)
                                 .arg(table->name()));
    }
    return table;
}

Table* MainAlphaPlot::newTable(int r, int c, const QString& name, const QString& legend)
{
    Table* table = new Table(r, c, legend, getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->setName(name);
    d_project->addChild(table->d_future_table);
    return table;
}

Table* MainAlphaPlot::newTable(const QString& name, const QString& legend, QList<Column*> columns)
{
    Table* table = new Table(0, 0, legend, 0, 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->d_future_table->appendColumns(columns);
    table->setName(name);
    d_project->addChild(table->d_future_table);
    return table;
}

Table* MainAlphaPlot::newHiddenTable(const QString& name, const QString& label, QList<Column*> columns)
{
    Table* table = new Table(0, 0, label, 0, 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    table->d_future_table->appendColumns(columns);
    table->setName(name);
    d_project->addChild(table->d_future_table);
    hideWindow(table);
    return table;
}

void MainAlphaPlot::initTable(Table* table)
{
    table->setWindowIcon(IconLoader::load(QString::fromLatin1("table"), IconLoader::LightDark));
    table->askOnCloseEvent(confirmCloseTable);
    current_folder->addWindow(table);
    table->setFolder(current_folder);
    getMainWindow()->addSubWindow(table);
    addListViewItem(table);
    table->showNormal();

    connectTable(table);
    customTable(table, Table::Custom::BackgroundColor);
    customTable(table, Table::Custom::HeaderColor);
    customTable(table, Table::Custom::TextColor);
    customTable(table, Table::Custom::HeaderFont);
    customTable(table, Table::Custom::TextFont);
    table->showComments(d_show_table_comments);

    QMenu* Scatter = new QMenu(tr("Scatter"));
    auto cmdScatter1 = Application::Instance->commandManager().getCommandByName("Std_Plot_Scatters");
    auto cmdScatter2 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Scatters_with_xerr");
    auto cmdScatter3 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Scatters_with_yerr");
    auto cmdScatter4 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Scatters_with_xyerr");
    Scatter->addAction(cmdScatter1->getAction()->action());
    Scatter->addAction(cmdScatter2->getAction()->action());
    Scatter->addAction(cmdScatter3->getAction()->action());
    Scatter->addAction(cmdScatter4->getAction()->action());

    QMenu* submenu = new QMenu(tr("Plot"));
    auto cmd = Application::Instance->commandManager().getCommandByName("Std_Plot_Line");
    submenu->addAction(cmd->getAction()->action());
    submenu->addMenu(Scatter);

    auto cmd1 = Application::Instance->commandManager().getCommandByName("Std_Plot_LineSymbol");
    submenu->addAction(cmd1->getAction()->action());
    
    QMenu* SpecialLineAndSymbol = new QMenu(tr("Special Line + Symbol"));
    auto SpecialLineAndSymbolCmd1 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vertical_drop_lines");
    auto SpecialLineAndSymbolCmd2 = Application::Instance->commandManager().getCommandByName("Std_Plot_Spline");
    auto SpecialLineAndSymbolCmd3 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vertical_steps");
    auto SpecialLineAndSymbolCmd4 = Application::Instance->commandManager().getCommandByName("Std_Plot_Horizontal_steps");
    SpecialLineAndSymbol->addAction(SpecialLineAndSymbolCmd1->getAction()->action());
    SpecialLineAndSymbol->addAction(SpecialLineAndSymbolCmd2->getAction()->action());
    SpecialLineAndSymbol->addAction(SpecialLineAndSymbolCmd3->getAction()->action());
    SpecialLineAndSymbol->addAction(SpecialLineAndSymbolCmd4->getAction()->action());
    submenu->addMenu(SpecialLineAndSymbol);
    submenu->addSeparator();

    auto cmd3 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vertical_Bars");
    auto cmd4 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vertical_Stacked_bars");
    auto cmd5 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vertical_Grouped_bars");
    auto cmd6 = Application::Instance->commandManager().getCommandByName("Std_Plot_Horizontal_Bars");
    auto cmd7 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Horizontal_Stacked_bars");
    auto cmd8 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Horizontal_Grouped_bars");
    auto cmd9 = Application::Instance->commandManager().getCommandByName("Std_Plot_Area");
    auto cmd10 = Application::Instance->commandManager().getCommandByName("Std_Plot_Channel_fil");
    auto cmd11 = Application::Instance->commandManager().getCommandByName("Std_Plot_Pie");
    auto cmd12 = Application::Instance->commandManager().getCommandByName("Std_Plot_Half_pie");
    auto cmd13 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vectors_XYXY");
    auto cmd14 = Application::Instance->commandManager().getCommandByName("Std_Plot_Vectors_XYAM");
    submenu->addAction(cmd1->getAction()->action());
    //submenu->addAction(cmd2->getAction()->action());
    submenu->addAction(cmd3->getAction()->action());
    submenu->addAction(cmd4->getAction()->action());
    submenu->addAction(cmd5->getAction()->action());
    submenu->addAction(cmd6->getAction()->action());
    submenu->addAction(cmd7->getAction()->action());
    submenu->addAction(cmd8->getAction()->action());
    submenu->addAction(cmd9->getAction()->action());
    submenu->addAction(cmd10->getAction()->action());
    submenu->addAction(cmd11->getAction()->action());
    submenu->addAction(cmd12->getAction()->action());
    submenu->addAction(cmd13->getAction()->action());
    submenu->addAction(cmd14->getAction()->action());
    submenu->addSeparator();

    // Statistical graphs
    QMenu* StatisticalGraphs = new QMenu(tr("Statistical Graphs"));
    auto StatisticalGraphs1 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_SG_box_plot");
    auto StatisticalGraphs2 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_SG_histogram");
    auto StatisticalGraphs3 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_SG_stacked_histogram");
    StatisticalGraphs->addAction(StatisticalGraphs1->getAction()->action());
    StatisticalGraphs->addAction(StatisticalGraphs2->getAction()->action());
    StatisticalGraphs->addAction(StatisticalGraphs3->getAction()->action());
    submenu->addMenu(StatisticalGraphs);

    // Layout grids
    QMenu* LayoutGrids = new QMenu(tr("Layout Grids"));
    auto LayoutGrids1 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Layout_grids_vertical_2_layouts");
    auto LayoutGrids2 =
        Application::Instance->commandManager().getCommandByName("Std_Plot_Layout_grids_horizontal_2_layouts");
    auto LayoutGrids3 = Application::Instance->commandManager().getCommandByName("Std_Plot_Layout_grids_4_layouts");
    LayoutGrids->addAction(LayoutGrids1->getAction()->action());
    LayoutGrids->addAction(LayoutGrids2->getAction()->action());
    LayoutGrids->addAction(LayoutGrids3->getAction()->action());
    submenu->addMenu(LayoutGrids);

    table->d_future_table->setPlotMenu(submenu);

    Q_EMIT modified();
}

//  Creates a new table with statistics on target columns/rows of base table
TableStatistics* MainAlphaPlot::newTableStatistics(Table* base, int type,
    QList<int> target,
    const QString& caption) {
    TableStatistics* statTable =
        new TableStatistics(scriptEnv, getMainWindow()->centralWidget(), base,
            static_cast<TableStatistics::Type>(type), target);
    if (!caption.isEmpty()) statTable->setName(caption);

    d_project->addChild(statTable->d_future_table);
    connect(base, SIGNAL(modifiedData(Table*, const QString&)), statTable,
        SLOT(update(Table*, const QString&)));
    connect(base, SIGNAL(changedColHeader(const QString&, const QString&)),
        statTable, SLOT(renameCol(const QString&, const QString&)));
    connect(base, SIGNAL(removedCol(const QString&)), statTable,
        SLOT(removeCol(const QString&)));
    connect(base->d_future_table,
        SIGNAL(aspectAboutToBeRemoved(const AbstractAspect*)), this,
        SLOT(removeDependentTableStatistics(const AbstractAspect*)));
    return statTable;
}

void MainAlphaPlot::removeDependentTableStatistics(
    const AbstractAspect* aspect) {
    Gui::TableViewProvider* future_table =
        qobject_cast<Gui::TableViewProvider*>(const_cast<AbstractAspect*>(aspect));
    if (!future_table) return;
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH(QMdiSubWindow * subwindow, subwindowlist) {
        TableStatistics* table_stat = qobject_cast<TableStatistics*>(subwindow);
        if (!table_stat) continue;
        Table* table = qobject_cast<Table*>(future_table->view());
        if (!table) continue;
        if (table_stat->base() == table)
            d_project->removeChild(table_stat->d_future_table);
    }
}

Matrix* MainAlphaPlot::newMatrix(int rows, int columns)
{
    Matrix* matrix = new Matrix(rows, columns, QString::fromLatin1(""), 0, 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    QString caption = QString::fromLatin1(App::GetApplication().getUniqueDocumentName(("Matrix")).c_str());

    matrix->setName(caption);
    d_project->addChild(matrix->d_future_matrix);
    return matrix;
}

Matrix* MainAlphaPlot::newMatrix(const QString& caption, int r, int c)
{
    Matrix* matrix = new Matrix(r, c, QString::fromLatin1(""), 0, 0,Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    const char *myCaption = caption.toUtf8().constData();
    QString name = QString::fromLatin1(App::GetApplication().getUniqueDocumentName(myCaption).c_str());

    while (alreadyUsedName(name)) {
        name = generateUniqueName(caption);
    }
    matrix->setName(name);
    d_project->addChild(matrix->d_future_matrix);
    if (matrix->name() != caption)// the matrix was renamed
        renamedTables << caption << matrix->name();

    return matrix;
}

Matrix* MainAlphaPlot::newMatrixShowMatrix(const mat& x, const QString caption)
{
    Matrix* matrix = new Matrix(x.rows(), x.cols(), QString::fromLatin1(""), 0, 0,Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    const char *myCaption = caption.toUtf8().constData();
    QString name = QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str());


    matrix->setName(name);
    d_project->addChild(matrix->d_future_matrix);
    if (matrix->name() != caption)// the matrix was renamed
        renamedTables << caption << matrix->name();

     matrix->setCoordinates(1, x.rows(), 1, x.cols());

     for (int i = 0; i < x.rows(); i++) {
        for (int j = 0; j < x.cols(); j++) {
            matrix->setText(i, j, QString::number(x(i, j)));
        }
    }

    return matrix;
}


Matrix* MainAlphaPlot::newMatrixShowVectors(const vec& x, const vec& y, const QString caption)
{
    if (x.size() != y.size()) {
        return nullptr;
    }

    Matrix* matrix = new Matrix(x.rows(), 2, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));

    matrix->setName(QString::fromLatin1(
        App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(matrix->d_future_matrix);
    if (matrix->name() != caption)// the table was renamed
    {
        renamedTables << caption << matrix->name();

        QMessageBox::warning(this, tr("Renamed Window"),
                             tr("The matrix '%1' already exists. It has been renamed '%2'.")
                                 .arg(caption)
                                 .arg(matrix->name()));
    }

    for (int i = 0; i < x.rows(); i++) {
        matrix->setText(i, 0, QString::number(x(i)));
        matrix->setText(i, 1, QString::number(y(i)));
    }

    return matrix;
}

Matrix* MainAlphaPlot::newMatrixShowVector(const vec& x, QString caption)
{
    if (x.size() == 0) {
        return nullptr;
    }

    Matrix* matrix = new Matrix(x.rows(), 1, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    matrix->setName(QString::fromLatin1(
        App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(matrix->d_future_matrix);
    if (matrix->name() != caption)// the table was renamed
    {
        renamedTables << caption << matrix->name();

        QMessageBox::warning(this, tr("Renamed Window"),
                             tr("The matrix '%1' already exists. It has been renamed '%2'.")
                                 .arg(caption)
                                 .arg(matrix->name()));
    }

    for (int i = 0; i < x.rows(); i++) {
        matrix->setText(i, 0, QString::number(x(i)));
    }

    return matrix;
}

Matrix* MainAlphaPlot::newMatrixShowComplexVectors(const vec& x, const cx_vec& y, const QString caption, const int& complexRealImag)
{
    if (x.size() != y.size()) {
        return nullptr;
    }

    Matrix* matrix = new Matrix(x.rows(), 2, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    matrix->setName(QString::fromLatin1(
        App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()));
    d_project->addChild(matrix->d_future_matrix);
    if (matrix->name() != caption)// the table was renamed
    {
        renamedTables << caption << matrix->name();

        QMessageBox::warning(this, tr("Renamed Window"),
                             tr("The matrix '%1' already exists. It has been renamed '%2'.")
                                 .arg(caption)
                                 .arg(matrix->name()));
    }

    //if (complexRealImag == 0)
    //{
    //    /*for (int i = 0; i < x.rows(); i++) {
    //        matrix->setText(i, 0, QString::number(x(i)));
    //        std::complex<double> cx_value = y(i);

    //        double real_part = cx_value.real();
    //        double imag_part = cx_value.imag();

    //        QString real_text = QString::number(real_part);
    //        QString imag_text = QString::number(imag_part);
    //        static QString text = real_text + QString::fromLatin1(" + ") + imag_text + QString::fromLatin1("i");
    //        matrix->setText(i, 1, text);
    //    }*/
    //}
    //else 
    if (complexRealImag == 0)
    {
        for (int i = 0; i < x.rows(); i++) {
            matrix->setText(i, 0, QString::number(x(i)));
            std::complex<double> cx_value = y(i);
            double real_part = cx_value.real();
            QString real_text = QString::number(real_part);
            matrix->setText(i, 1, real_text);
        }
    }
    else if (complexRealImag == 1)
    {
        for (int i = 0; i < x.rows(); i++) {
            matrix->setText(i, 0, QString::number(x(i)));
            std::complex<double> cx_value = y(i);

            double imag_part = cx_value.imag();

            QString imag_text = QString::number(imag_part);

            matrix->setText(i, 1, imag_text);
        }
    }

    return matrix;
}

Matrix* MainAlphaPlot::newMatrixShowComplexMatrix(const cx_mat& x, const QString caption, const int& complexRealImag)
{
    Matrix* matrix1 = new Matrix(x.rows(), x.cols(), QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    Matrix* matrix2 = new Matrix(x.rows(), x.cols(), QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));

    matrix1->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()) + QString::fromLatin1("_Real"));
    matrix2->setName(QString::fromLatin1(App::GetApplication().getUniqueDocumentName(caption.toUtf8().constData()).c_str()) + QString::fromLatin1("_Imag"));

    d_project->addChild(matrix1->d_future_matrix);
    d_project->addChild(matrix2->d_future_matrix);

    for (int i = 0; i < x.rows(); i++) {
        for (int j = 0; j < x.cols(); j++) {
             QString text1 = QString::number(x(i, j).real());
             QString text2 = QString::number(x(i, j).imag());
             matrix1->setText(i, j, text1);
             matrix2->setText(i, j, text2);
        }
    }

    return matrix1;
}


Matrix* MainAlphaPlot::newMatrixShowArrayPy(int rws, int cls, const std::vector<std::vector<double>> array, QString caption)
{
    Matrix* matrix = new Matrix(rws, cls, QString::fromLatin1(""), 0, 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    const char *myCaption = caption.toUtf8().constData();
    QString name = QString::fromLatin1(App::GetApplication().getUniqueDocumentName(myCaption).c_str());
    matrix->setName(name);
    d_project->addChild(matrix->d_future_matrix);
    if (matrix->name() != caption)// the matrix was renamed
        renamedTables << caption << matrix->name();

    QString text;
    for (int i = 0; i < rws; i++) {
        for (int j = 0; j < cls; j++) {
            text = QString::number(array[i][j]);
            matrix->setText(i, j, text);
        }
    }

    matrix->setCoordinates(1, rws, 1, cls);
    matrix->d_future_matrix->setDisplayedDigits(4);
    return matrix;
}


void MainAlphaPlot::matrixDeterminant()
{
    if (!getMainWindow()->isActiveWindow())
        return;
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    if (!matrix)
        return;

    QDateTime dt = QDateTime::currentDateTime();
    QString info = dt.toString(Qt::LocalDate);
    info += QString::fromLatin1("\n") + tr("Determinant of ") + QString(matrix->name())
        + QString::fromLatin1(":\t");
    info += QString::fromLatin1("det = ") + QString::number(matrix->determinant())
        + QString::fromLatin1("\n");
    info += QString::fromLatin1("-------------------------------------------------------------\n");

    getMainWindow()->setResultLogInfo(info);
    getMainWindow()->showResults(true);
}

void MainAlphaPlot::invertMatrix()
{
    if (!getMainWindow()->isActiveWindow())
        return;
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    if (!matrix)
        return;

    matrix->invert();
}

void MainAlphaPlot::transposeMatrix()
{
    if (!getMainWindow()->isActiveWindow())
        return;
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    if (!matrix)
        return;

    matrix->transpose();
}

void MainAlphaPlot::mirrorHorizontally()
{
    if (!getMainWindow()->isActiveWindow())
        return;
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    if (!matrix)
        return;

    matrix->mirrorHorizontally();
}
void MainAlphaPlot::mirrorVertically()
{
    if (!getMainWindow()->isActiveWindow())
        return;
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    if (!matrix)
        return;

    matrix->mirrorVertically();
}

Table* MainAlphaPlot::convertMatrixToTable()
{
    if (!getMainWindow()->isActiveWindow())
        return nullptr;
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    if (!matrix)
        return nullptr;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    int rows = matrix->numRows();
    int cols = matrix->numCols();

    Table* table = new Table(rows, cols, QString::fromLatin1(""), getMainWindow()->centralWidget(), 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            table->setCellValue(i, j, matrix->cell(i, j));
    }

    table->setName(generateUniqueName(tr("Table")));
    d_project->addChild(table->d_future_table);
    table->setWindowLabel(matrix->windowLabel());
    table->setCaptionPolicy(matrix->captionPolicy());
    table->resize(matrix->size());
    table->showNormal();

    QApplication::restoreOverrideCursor();

    return table;
}

void MainAlphaPlot::initMatrix(Matrix* matrix)
{
    matrix->setWindowIcon(IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark));
    matrix->askOnCloseEvent(confirmCloseMatrix);
    matrix->setNumericFormat(QChar::fromLatin1(d_default_numeric_format), d_decimal_digits);
    matrix->setFolder(current_folder);

    current_folder->addWindow(matrix);
    matrix->setFolder(current_folder);
    getMainWindow()->addSubWindow(matrix);
    addListViewItem(matrix);
    matrix->showNormal();

    connect(matrix, SIGNAL(showTitleBarMenu()), this, SLOT(showWindowTitleBarMenu()));
    connect(matrix, SIGNAL(modifiedWindow(MyWidget*)), this, SLOT(modifiedProject(MyWidget*)));
    connect(matrix, SIGNAL(hiddenWindow(MyWidget*)), this, SLOT(hideWindow(MyWidget*)));
    connect(matrix, SIGNAL(statusChanged(MyWidget*)), this, SLOT(updateWindowStatus(MyWidget*)));
    connect(matrix, SIGNAL(showContextMenu()), this, SLOT(showWindowContextMenu()));
    connect(matrix, &Matrix::mousepressevent, [=](MyWidget* widget) {
        if (getactiveMyWidget() == widget)
            return;
        widget->setNormal();
        getMainWindow()->setActiveSubWindow(widget);
    });
    Q_EMIT modified();
}

Matrix* MainAlphaPlot::convertTableToMatrix()
{
    if (!getactiveMyWidget())
        return nullptr;
    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (!table)
        return nullptr;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    int rows = table->numRows();
    int cols = table->numCols();

    Matrix* matrix = new Matrix(rows, cols, QString::fromLatin1(""), 0, 0, Qt::SubWindow, ScriptingLangManager::newEnv(getMainWindow()));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            matrix->setText(i, j, table->text(i, j));
    }

    QString caption = generateUniqueName(table->name());
    matrix->setName(caption);
    d_project->addChild(matrix->d_future_matrix);

    matrix->setCaptionPolicy(table->captionPolicy());
    matrix->resize(table->size());
    matrix->showNormal();

    QApplication::restoreOverrideCursor();
    return matrix;
}

QMdiSubWindow* MainAlphaPlot::window(const QString& name)
{
    QMdiSubWindow* subwindow = nullptr;
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    for (int i = 0; i < subwindowlist.count(); i++) {
        MyWidget* widget = qobject_cast<MyWidget*>(subwindowlist.at(i));
        if (widget && widget->name() == name) {
            subwindow = subwindowlist.at(i);
            break;
        }
    }
    return subwindow;
}

Table* MainAlphaPlot::table(const QString& name)
{
    int pos = name.indexOf(QString::fromLatin1("_"), 0);
    QString caption = name.left(pos);

    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)
            && qobject_cast<Table*>(subwindow)->name() == caption) {
            return qobject_cast<Table*>(subwindow);
        }
    }
    return nullptr;
}

Matrix* MainAlphaPlot::matrix(const QString& name)
{
    QString caption = name;
    if (!renamedTables.isEmpty() && renamedTables.contains(caption)) {
        int index = renamedTables.indexOf(caption);
        caption = renamedTables[index + 1];
    }

    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow)
            && qobject_cast<Matrix*>(subwindow)->name() == caption) {
            return qobject_cast<Matrix*>(subwindow);
        }
    }

    return nullptr;
}

void MainAlphaPlot::windowActivated(QMdiSubWindow* subwindow)
{
    if (!subwindow || !qobject_cast<MyWidget*>(subwindow)) {

        if (!this->plotPropertyeditor)
            this->plotPropertyeditor = getMainWindow()->findChild<PlotPropertyEditor*>();
       
        // Alphaplot explorer window found?
        if (this->plotPropertyeditor) {
            plotPropertyeditor->populateObjectBrowser(nullptr);
        }

        return;
    }

    // will be destroyed when parent set graphicseffect to nullptr
    Q_FOREACH (QMdiSubWindow* window, subWindowsList()) {
        window->setGraphicsEffect(nullptr);
        // disable picker
        if (isActiveSubWindow(window, SubWindowType::Plot2DSubWindow)) {
            Layout2D* layout = qobject_cast<Layout2D*>(window);
            layout->setGraphTool(Graph2DCommon::Picker::None);
        }
    }

    //// reset picker menu
    //pickGraphTool(ui_->actionDisableGraphTools);
    //ui_->actionDisableGraphTools->setChecked(true);

    // glow effect
    if (glowstatus_) {
        QGraphicsDropShadowEffect* gloweffect = new QGraphicsDropShadowEffect;
        // Set glow effect values
        gloweffect->setColor(glowcolor_);
        gloweffect->setXOffset(glowxoffset_);
        gloweffect->setYOffset(glowyoffset_);
        gloweffect->setBlurRadius(glowradius_);
        subwindow->setGraphicsEffect(gloweffect);
    }

    customToolBars(subwindow);
    customMenu(subwindow);

    MyWidget* mywidget = qobject_cast<MyWidget*>(subwindow);

    Folder* f = mywidget->folder();

    if (f)
        f->setActiveWindow(mywidget);
    if (!this->plotPropertyeditor)
        this->plotPropertyeditor = getMainWindow()->findChild<PlotPropertyEditor*>();
    // Python console found?
    if (this->plotPropertyeditor) {
        plotPropertyeditor->populateObjectBrowser(mywidget);
    }
    //documentFeaturePropertyEditor->populateObjectBrowser(mywidget);

    Q_EMIT modified();
}

void MainAlphaPlot::addErrorBars()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no suitable layout/plot available in this "
                                "window.</h4><p><h4>Please add a layout/plot and try again!</h4>"));
        return;
    }

    ErrDialog* ed = new ErrDialog(getMainWindow()->centralWidget(), axisrect);
    ed->setAttribute(Qt::WA_DeleteOnClose);
    ed->exec();
}

void MainAlphaPlot::removeCurves(Table* table, const QString& name)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
            Layout2D* layout2d = qobject_cast<Layout2D*>(subwindow);
            if (layout2d)
                layout2d->removeColumn(table, name);
        }
        else if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {}
    }
    QApplication::restoreOverrideCursor();
}

void MainAlphaPlot::updateCurves(Table* t, const QString& name)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
            Layout2D* layout2d = qobject_cast<Layout2D*>(subwindow);
            if (layout2d)
                layout2d->updateData(t, name);
        }
        else if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {}
    }
}

void MainAlphaPlot::showPreferencesDialog()
{
    /* std::unique_ptr<SettingsDialog> settings_(new SettingsDialog);
     connect(settings_.get(), &SettingsDialog::generalapplicationsettingsupdates,
         this, &MainAlphaPlot::updateGeneralApplicationOptions);
     connect(settings_.get(), &SettingsDialog::generalconfirmationsettingsupdates,
         this, &MainAlphaPlot::updateGeneralConfirmOptions);
     connect(settings_.get(), &SettingsDialog::generalappreancesettingsupdates,
         this, &MainAlphaPlot::updateGeneralAppearanceOptions);
     connect(settings_.get(), &SettingsDialog::generalnumericformatsettingsupdates,
         this, &MainAlphaPlot::updateGeneralNumericFormatOptions);
     connect(settings_.get(), &SettingsDialog::tablebasicsettingsupdates, this,
         &MainAlphaPlot::updateTableBasicOptions);
     connect(settings_.get(), &SettingsDialog::tablecolorsettingsupdates, this,
         &MainAlphaPlot::updateTableColorOptions);
     connect(settings_.get(), &SettingsDialog::tablefontsettingsupdates, this,
         &MainAlphaPlot::updateTableFontOptions);
     connect(settings_.get(), &SettingsDialog::fittingsettingsupdates, this,
         &MainAlphaPlot::updateFittingOptions);
     settings_->exec();*/
}

void MainAlphaPlot::setSaveSettings(bool autoSaving, int min)
{
    if (autoSave == autoSaving && autoSaveTime == min)
        return;

    autoSave = autoSaving;
    autoSaveTime = min;

    killTimer(savingTimerId);

    if (autoSave) {
        savingTimerId = startTimer(autoSaveTime * 60000);
    }
    else {
        savingTimerId = 0;
    }
}

void MainAlphaPlot::changeAppStyle(const QString& s)
{
    // style keys are case insensitive
    if (appStyle.toLower() == s.toLower())
        return;

    qApp->setStyle(s);
    appStyle = qApp->style()->objectName();

    // comment out color handling
    /*QPalette pal = qApp->palette();
     pal.setColor (QPalette::Active, QPalette::Base, QColor(panelsColor));
     qApp->setPalette(pal);*/
}

void MainAlphaPlot::changeAppColorScheme(int colorScheme)
{
    //switch (colorScheme) {
    //    case 0: {
    //        qApp->setStyleSheet(styleSheet());
    //        setStyleSheet(styleSheet());
    //        QPalette pal = qApp->palette();
    //        QColor color = pal.color(QPalette::Active, QPalette::Base);
    //        d->mdiArea->setBackground(QBrush(color));
    //        IconLoader::lumen_ = IconLoader::isLight(palette().color(QPalette::Window));
    //        appColorScheme = 0;
    //    } break;
    //    case 1: {
    //        QFile schemefile(QString::fromLatin1(":style/alpha/dark.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QBrush(QColor(32, 31, 31)));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::black);
    //        appColorScheme = 1;
    //    } break;
    //    case 2: {
    //        QFile schemefile(QString::fromLatin1(":style/smooth/dark-blue.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QColor(200, 200, 200));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::black);
    //        appColorScheme = 2;
    //    } break;
    //    case 3: {
    //        QFile schemefile(QString::fromLatin1(":style/smooth/dark-green.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QColor(200, 200, 200));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::black);
    //        appColorScheme = 3;
    //    } break;
    //    case 4: {
    //        QFile schemefile(QString::fromLatin1(":style/smooth/dark-orange.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QColor(200, 200, 200));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::black);
    //        appColorScheme = 4;
    //    } break;
    //    case 5: {
    //        QFile schemefile(QString::fromLatin1(":style/smooth/light-blue.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QColor(230, 230, 230));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::white);
    //        appColorScheme = 5;
    //    } break;
    //    case 6: {
    //        QFile schemefile(QString::fromLatin1(":style/smooth/light-green.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QColor(230, 230, 230));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::white);
    //        appColorScheme = 6;
    //    } break;
    //    case 7: {
    //        QFile schemefile(QString::fromLatin1(":style/smooth/light-orange.qss"));
    //        schemefile.open(QFile::ReadOnly | QFile::Text);
    //        QTextStream schemeFileStream(&schemefile);
    //        qApp->setStyleSheet(schemeFileStream.readAll());
    //        setStyleSheet(schemeFileStream.readAll());
    //        d->mdiArea->setBackground(QColor(230, 230, 230));
    //        IconLoader::lumen_ = IconLoader::isLight(Qt::white);
    //        appColorScheme = 7;
    //    } break;
    //    default:
    //        // should not reach
    //        qDebug() << "color scheme index out of range";
    //        break;
    //}
    //loadIcons();
}

void MainAlphaPlot::changeAppFont(const QFont& font)
{
    if (appFont == font)
        return;

    appFont = font;
    qApp->setFont(appFont);
    this->setFont(appFont);
}

void MainAlphaPlot::updateGeneralConfirmOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("Confirmations"));
    bool nconfirmCloseFolder = settings.value(QString::fromLatin1("Folder"), true).toBool();
    bool nconfirmCloseTable = settings.value(QString::fromLatin1("Table"), true).toBool();
    bool nconfirmCloseMatrix = settings.value(QString::fromLatin1("Matrix"), true).toBool();
    bool nconfirmClosePlot2D = settings.value(QString::fromLatin1("Plot2D"), true).toBool();
    bool nconfirmClosePlot3D = settings.value(QString::fromLatin1("Plot3D"), true).toBool();
    bool nconfirmCloseNotes = settings.value(QString::fromLatin1("Note"), true).toBool();
    settings.endGroup();// Confirmations

    confirmCloseFolder = nconfirmCloseFolder;
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    if (confirmCloseTable != nconfirmCloseTable) {
        confirmCloseTable = nconfirmCloseTable;
        for (int i = 0; i < int(subwindowlist.count()); i++) {
            if (isActiveSubWindow(subwindowlist.at(i), SubWindowType::TableSubWindow))
                qobject_cast<MyWidget*>(subwindowlist.at(i))->askOnCloseEvent(confirmCloseTable);
        }
    }

    if (confirmCloseMatrix != nconfirmCloseMatrix) {
        confirmCloseMatrix = nconfirmCloseMatrix;
        for (int i = 0; i < int(subwindowlist.count()); i++) {
            if (isActiveSubWindow(subwindowlist.at(i), SubWindowType::MatrixSubWindow))
                qobject_cast<MyWidget*>(subwindowlist.at(i))->askOnCloseEvent(confirmCloseMatrix);
        }
    }

    if (confirmClosePlot2D != nconfirmClosePlot2D) {
        confirmClosePlot2D = nconfirmClosePlot2D;
        for (int i = 0; i < int(subwindowlist.count()); i++) {
            if (isActiveSubWindow(subwindowlist.at(i), SubWindowType::Plot2DSubWindow))
                qobject_cast<MyWidget*>(subwindowlist.at(i))->askOnCloseEvent(confirmClosePlot2D);
        }
    }

    if (confirmClosePlot3D != nconfirmClosePlot3D) {
        confirmClosePlot3D = nconfirmClosePlot3D;
        for (int i = 0; i < int(subwindowlist.count()); i++) {
            if (isActiveSubWindow(subwindowlist.at(i), SubWindowType::Plot3DSubWindow))
                qobject_cast<MyWidget*>(subwindowlist.at(i))->askOnCloseEvent(confirmClosePlot3D);
        }
    }

    if (confirmCloseNotes != nconfirmCloseNotes) {
        confirmCloseNotes = nconfirmCloseNotes;
        for (int i = 0; i < int(subwindowlist.count()); i++) {
            if (isActiveSubWindow(subwindowlist.at(i), SubWindowType::NoteSubWindow))
                qobject_cast<MyWidget*>(subwindowlist.at(i))->askOnCloseEvent(confirmCloseNotes);
        }
    }
}

void MainAlphaPlot::updateGeneralAppearanceOptions()
{

    ParameterGrp::handle hGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("General");

    QString nappstyle_ = QString::fromUtf8(
        hGrp->GetASCII("Style", qApp->style()->objectName().toLatin1().constData()).c_str());

    int ncolorscheme_ = hGrp->GetInt("ColorScheme", 0);

    hGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("General")->GetGroup("Colors");

    bool ncustomcolors_ = hGrp->GetBool("Custom", false);

    unsigned long col = hGrp->GetUnsigned("Workspace", palette().base().color().rgba() >> 8);
    QColor nworkspacecolor_;
    nworkspacecolor_.setRgb(col);

    col = hGrp->GetUnsigned("Panels", palette().window().color().rgba() >> 8);
    QColor npanelcolor_;
    npanelcolor_.setRgb(col);

    col = hGrp->GetUnsigned("PanelsText", palette().windowText().color().rgba() >> 8);
    QColor npaneltextcolor_;
    npaneltextcolor_.setRgb(col);

    /*QSettings settings;
     settings.beginGroup(QString::fromLatin1("General"));
     QString nappstyle_ =
         settings.value(QString::fromLatin1("Style"), qApp->style()->objectName()).toString();*/
    //int ncolorscheme_ = settings.value(QString::fromLatin1("ColorScheme"), 0).toInt();

    /* settings.beginGroup(QString::fromLatin1("Colors"));
     bool ncustomcolors_ = settings.value(QString::fromLatin1("Custom"), false).toBool();
     QColor nworkspacecolor_ =
         settings.value(QString::fromLatin1("Workspace"), QString::fromLatin1("darkGray")).value<QColor>();
     QColor npanelcolor_ =
         settings.value(QString::fromLatin1("Panels"), palette().window().color()).value<QColor>();
     QColor npaneltextcolor_ =
         settings.value(QString::fromLatin1("PanelsText"), palette().windowText().color())
         .value<QColor>();
     settings.endGroup();
     settings.endGroup();*/

    if (nappstyle_ != appStyle) {
        changeAppStyle(nappstyle_);
    }

    if (ncolorscheme_ != appColorScheme) {
        changeAppColorScheme(ncolorscheme_);
    }

    if (ncustomcolors_ != appCustomColor) {
        appCustomColor = ncustomcolors_;
        workspaceColor = nworkspacecolor_;
        panelsColor = npanelcolor_;
        panelsTextColor = npaneltextcolor_;
        setAppColors();
    }
}

void MainAlphaPlot::updateGeneralNumericFormatOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("General"));
    QString localestring =
        settings.value(QString::fromLatin1("Locale"), QLocale::system().name()).toString();
    bool usegroupseperator =
        settings.value(QString::fromLatin1("LocaleUseGroupSeparator"), true).toBool();
    int precision = settings.value(QString::fromLatin1("DecimalDigits"), 6).toInt();
    char defaultnumericformat =
        settings.value(QString::fromLatin1("DefaultNumericFormat"), 'g').toChar().toLatin1();
    settings.endGroup();
    QLocale locale;
    (localestring == QLocale::system().name())              ? locale = QLocale::system()
        : (localestring == QLocale::c().name())             ? locale = QLocale::c()
        : (localestring == QLocale(QLocale::German).name()) ? locale = QLocale(QLocale::German)
        : (localestring == QLocale(QLocale::French).name()) ? locale = QLocale(QLocale::French)
                                                            : locale = QLocale::system();

    if (usegroupseperator)
        locale.setNumberOptions(locale.numberOptions() & ~QLocale::OmitGroupSeparator);
    else
        locale.setNumberOptions(locale.numberOptions() | QLocale::OmitGroupSeparator);

    if (QLocale() != locale) {
        QLocale::setDefault(locale);
    }

    if (d_decimal_digits != precision) {
        d_decimal_digits = precision;
    }

    if (d_default_numeric_format != defaultnumericformat) {
        d_default_numeric_format = defaultnumericformat;
    }
}

void MainAlphaPlot::updateTableBasicOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("Tables"));
    bool nshow_table_comments =
        settings.value(QString::fromLatin1("DisplayComments"), false).toBool();
    settings.endGroup();
    settings.beginGroup(QString::fromLatin1("ImportASCII"));
    QString ncolumnseparator =
        settings.value(QString::fromLatin1("ColumnSeparator"), QString::fromLatin1("\\t"))
            .toString();
    settings.endGroup();

    if (d_show_table_comments != nshow_table_comments) {
        d_show_table_comments = nshow_table_comments;
        customizeCommentsTables();
    }
    columnSeparator = ncolumnseparator;
}

void MainAlphaPlot::updateTableColorOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("Tables"));
    settings.beginGroup(QString::fromLatin1("ColumnColorIndicator"));
    QColor nxColorCode =
        settings.value(QString::fromLatin1("xColorCode"), QColor(0, 172, 109, 100)).value<QColor>();
    QColor nyColorCode =
        settings.value(QString::fromLatin1("yColorCode"), QColor(204, 140, 91, 100))
            .value<QColor>();
    QColor nzColorCode =
        settings.value(QString::fromLatin1("zColorCode"), QColor(174, 129, 255, 100))
            .value<QColor>();
    QColor nxErrColorCode =
        settings.value(QString::fromLatin1("xErrColorCode"), QColor(255, 0, 0, 100))
            .value<QColor>();
    QColor nyErrColorCode =
        settings.value(QString::fromLatin1("yErrColorCode"), QColor(255, 0, 0, 100))
            .value<QColor>();
    QColor nnoneColorCode =
        settings.value(QString::fromLatin1("noneColorCode"), QColor(150, 150, 150, 100))
            .value<QColor>();
    settings.endGroup();
    settings.beginGroup(QString::fromLatin1("Colors"));
    bool ncustomColor = settings.value(QString::fromLatin1("Custom"), false).toBool();
    QColor nbkgdColor =
        settings.value(QString::fromLatin1("Background"), qApp->palette().color(QPalette::Base))
            .value<QColor>();
    QColor ntextColor =
        settings.value(QString::fromLatin1("Text"), qApp->palette().color(QPalette::Text))
            .value<QColor>();
    QColor nlabelColor =
        settings.value(QString::fromLatin1("Header"), qApp->palette().color(QPalette::Text))
            .value<QColor>();
    settings.endGroup();// Colors
    settings.endGroup();
    AppearanceManager::xColorCode = nxColorCode;
    AppearanceManager::yColorCode = nyColorCode;
    AppearanceManager::zColorCode = nzColorCode;
    AppearanceManager::xErrColorCode = nxErrColorCode;
    AppearanceManager::yErrColorCode = nyErrColorCode;
    AppearanceManager::noneColorCode = nnoneColorCode;

    bool customcolor = false;
    if (tableCustomColor != ncustomColor) {
        customcolor = true;
        tableCustomColor = ncustomColor;
    }
    if (tableBkgdColor != nbkgdColor || customcolor != false) {
        tableBkgdColor = nbkgdColor;
        customizeTables(Table::Custom::BackgroundColor);
    }
    if (tableBkgdColor != tableHeaderColor || customcolor != false) {
        tableHeaderColor = nlabelColor;
        customizeTables(Table::Custom::HeaderColor);
    }
    if (tableTextColor != ntextColor || customcolor != false) {
        tableTextColor = ntextColor;
        customizeTables(Table::Custom::TextColor);
    }
}

void MainAlphaPlot::updateTableFontOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("Tables"));
    QStringList tableFonts = settings.value(QString::fromLatin1("Fonts")).toStringList();
    QFont ntableTextFont;
    QFont ntableHeaderFont;
    if (tableFonts.size() == 8) {
        ntableTextFont = QFont(tableFonts[0], tableFonts[1].toInt(), tableFonts[2].toInt(),
                               tableFonts[3].toInt());
        ntableHeaderFont = QFont(tableFonts[4], tableFonts[5].toInt(), tableFonts[6].toInt(),
                                 tableFonts[7].toInt());
    }
    else {
        ntableTextFont = qApp->font();
        ntableHeaderFont = qApp->font();
    }
    settings.endGroup();
    if (tableTextFont != ntableTextFont) {
        tableTextFont = ntableTextFont;
        customizeTables(Table::Custom::TextFont);
    }
    if (tableHeaderFont != ntableHeaderFont) {
        tableHeaderFont = ntableHeaderFont;
        customizeTables(Table::Custom::HeaderFont);
    }
}

void MainAlphaPlot::updateFittingOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("Fitting"));
    fit_output_precision = settings.value(QString::fromLatin1("OutputPrecision"), 15).toInt();
    pasteFitResultsToPlot =
        settings.value(QString::fromLatin1("PasteResultsToPlot"), false).toBool();
    writeFitResultsToLog = settings.value(QString::fromLatin1("WriteResultsToLog"), true).toBool();
    generateUniformFitPoints =
        settings.value(QString::fromLatin1("GenerateFunction"), true).toBool();
    fitPoints = settings.value(QString::fromLatin1("Points"), 100).toInt();
    generatePeakCurves = settings.value(QString::fromLatin1("GeneratePeakCurves"), true).toBool();
    peakCurvesColor = settings.value(QString::fromLatin1("PeaksColor"), 2).toInt();// green color
    fit_scale_errors = settings.value(QString::fromLatin1("ScaleErrors"), false).toBool();
    d_2_linear_fit_points =
        settings.value(QString::fromLatin1("TwoPointsLinearFit"), true).toBool();
    settings.endGroup();// Fitting
}

MainAlphaPlot* MainAlphaPlot::plotFile(const QString& fn)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    MainAlphaPlot* app = new MainAlphaPlot(getMainWindow());
    app->applyUserSettings();
    app->showMaximized();

    Table* t =
        app->newTable(fn, app->columnSeparator, 0, true, app->strip_spaces, app->simplify_spaces,
                      app->d_convert_to_numeric, app->d_ASCII_import_locale);
    t->setCaptionPolicy(MyWidget::Both);
    QApplication::restoreOverrideCursor();
    return nullptr;
}

void MainAlphaPlot::importASCII()
{
    ImportASCIIDialog* import_dialog =
         new ImportASCIIDialog(isActiveSubwindow(SubWindowType::TableSubWindow),strip_spaces, simplify_spaces,
                    ignoredLines, renameColumns, columnSeparator, d_convert_to_numeric, d_ASCII_import_locale,this, d_extended_import_ASCII_dialog);
     import_dialog->setDirectory(asciiDirPath);
     import_dialog->selectNameFilter(d_ASCII_file_filter);
     if (import_dialog->exec() != QDialog::Accepted) return;

     asciiDirPath = import_dialog->directory().path();
     if (import_dialog->rememberOptions()) {
         columnSeparator = import_dialog->columnSeparator();
         ignoredLines = import_dialog->ignoredLines();
         renameColumns = import_dialog->renameColumns();
         strip_spaces = import_dialog->stripSpaces();
         simplify_spaces = import_dialog->simplifySpaces();
         d_ASCII_import_locale = import_dialog->decimalSeparators();
         d_convert_to_numeric = import_dialog->convertToNumeric();
         saveSettings();
     }

     importASCII(import_dialog->selectedFiles(), import_dialog->importMode(),
         import_dialog->columnSeparator(), import_dialog->ignoredLines(),
         import_dialog->renameColumns(), import_dialog->stripSpaces(),
         import_dialog->simplifySpaces(),
         import_dialog->convertToNumeric(),
         import_dialog->decimalSeparators());
}

void MainAlphaPlot::importASCII(const QStringList& files, int import_mode,
                             const QString& local_column_separator, int local_ignored_lines,
                             bool local_rename_columns, bool local_strip_spaces,
                             bool local_simplify_spaces, bool local_convert_to_numeric,
                             QLocale local_numeric_locale)
{
    if (files.isEmpty())
        return;

    // this is very much a special case, and thus is handled completely in its own
    // block
    if (import_mode == ImportASCIIDialog::NewTables) {
        int dx = 0, dy = 0;
        QStringList sorted_files = files;
        sorted_files.sort();
        for (int i = 0; i < sorted_files.size(); i++) {
            Table* w = newTable(sorted_files.at(i), local_column_separator, local_ignored_lines,
                                local_rename_columns, local_strip_spaces, local_simplify_spaces,
                                local_convert_to_numeric, local_numeric_locale);
            if (!w)
                continue;
            w->setCaptionPolicy(MyWidget::Both);
            setListViewLabel(w->name(), sorted_files[i]);
            if (i == 0) {
                dx = w->verticalHeaderWidth();
                dy = w->frameGeometry().height() - w->height();
                w->move(QPoint(0, 0));
            }
            else
                w->move(QPoint(i * dx, i * dy));
        }
        modifiedProject();
        return;
    }

    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (!table)
        return;

    Q_FOREACH (QString file, files) {
        Table* temp =
            new Table(file, local_column_separator, local_ignored_lines, local_rename_columns,
                      local_strip_spaces, local_simplify_spaces, local_convert_to_numeric,
                      local_numeric_locale, QString::fromLatin1("temp"), 0, 0, Qt::Widget, ScriptingLangManager::newEnv(getMainWindow()));
        if (!temp)
            continue;

        // need to check data types of columns for append/overwrite
        if (import_mode == ImportASCIIDialog::NewRows
            || import_mode == ImportASCIIDialog::Overwrite) {
            if (local_convert_to_numeric) {
                for (int col = 0; col < qMin(temp->columnCount(), table->columnCount()); col++)
                    if (table->column(col)->columnMode() != AlphaPlot::Numeric) {
                        QMessageBox::critical(this, tr("ASCII Import Failed"),
                                              tr("Numeric data cannot be imported into "
                                                 "non-numeric column \"%1\".")
                                                  .arg(table->column(col)->name()));
                        delete temp;
                        return;
                    }
            }
            else {
                for (int col = 0; col < qMin(temp->columnCount(), table->columnCount()); col++)
                    if (table->column(col)->columnMode() != AlphaPlot::Text) {
                        QMessageBox::critical(this, tr("ASCII Import Failed"),
                                              tr("Non-numeric data cannot be imported into "
                                                 "non-text column \"%1\".")
                                                  .arg(table->column(col)->name()));
                        delete temp;
                        return;
                    }
            }
        }

        // copy or move data from temp to table
        switch (import_mode) {
            case ImportASCIIDialog::NewColumns:
                while (temp->d_future_table->childCount() > 0)
                    temp->d_future_table->reparentChild(table->d_future_table,
                                                        temp->d_future_table->child(0));
                break;
            case ImportASCIIDialog::NewRows: {
                int missing_columns = temp->columnCount() - table->columnCount();
                for (int col = 0; col < missing_columns; col++) {
                    Column* new_col =
                        new Column(tr("new_by_import") + QString::number(col + 1),
                                   local_convert_to_numeric ? AlphaPlot::Numeric : AlphaPlot::Text);
                    new_col->setPlotDesignation(AlphaPlot::Y);
                    table->d_future_table->addChild(new_col);
                }
                Q_ASSERT(table->columnCount() >= temp->columnCount());
                int start_row = table->numRows();
                table->d_future_table->setRowCount(table->numRows() + temp->numRows());
                for (int col = 0; col < temp->columnCount(); col++) {
                    Column* src_col = temp->column(col);
                    Column* dst_col = table->column(col);
                    Q_ASSERT(src_col->dataType() == dst_col->dataType());
                    dst_col->copy(src_col, 0, start_row, src_col->rowCount());
                    if (local_rename_columns)
                        dst_col->setName(src_col->name());
                }
                break;
            }
            case ImportASCIIDialog::Overwrite: {
                if (table->numRows() < temp->numRows())
                    table->d_future_table->setRowCount(temp->numRows());
                for (int col = 0; col < table->columnCount() && col < temp->columnCount(); col++) {
                    Column* src_col = temp->column(col);
                    Column* dst_col = table->column(col);
                    Q_ASSERT(src_col->dataType() == dst_col->dataType());
                    dst_col->copy(src_col, 0, 0, temp->numRows());
                    if (local_rename_columns)
                        dst_col->setName(src_col->name());
                }
                if (temp->columnCount() > table->columnCount()) {
                    temp->d_future_table->removeColumns(0, table->columnCount());
                    while (temp->d_future_table->childCount() > 0)
                        temp->d_future_table->reparentChild(table->d_future_table,
                                                            temp->d_future_table->child(0));
                }
                break;
            }
        }
        delete temp;
    }

    table->setWindowLabel(files.join(QString::fromLatin1("; ")));
    table->notifyChanges();
    Q_EMIT modifiedProject(table);
    modifiedProject();
}

void MainAlphaPlot::openAproj()
{
    OpenProjectDialog* openDialog =
        new OpenProjectDialog(this, d_extended_open_dialog);
    openDialog->setDirectory(workingDir);
    if (openDialog->exec() != QDialog::Accepted ||
        openDialog->selectedFiles().isEmpty())
        return;
    workingDir = openDialog->directory().path();

    switch (openDialog->openMode()) {
    case OpenProjectDialog::NewProject: {
        QString fileName = openDialog->selectedFiles()[0];
        QFileInfo fi(fileName);

        /*if (projectname != QString::fromLatin1("untitled")) {
            QFileInfo fileInf(projectname);
            QString pn = fileInf.absoluteFilePath();
            if (fileName == pn) {
                QMessageBox::warning(
                    this, tr("File opening error"),
                    tr("The file: <b>%1</b> is the current file!").arg(fileName));
                return;
            }
        }*/
        if (fileName.endsWith(QString::fromLatin1(".aproj"), Qt::CaseInsensitive) ||
            fileName.endsWith(QString::fromLatin1(".aproj~"), Qt::CaseInsensitive) ||
            fileName.endsWith(QString::fromLatin1(".aproj.gz"), Qt::CaseInsensitive)) {
            if (!fi.exists()) {
                QMessageBox::critical(
                    this, tr("File opening error"),
                    tr("The file: <b>%1</b> doesn't exist!").arg(fileName));
                return;
            }

            saveSettings();  // the recent projects must be saved

            MainAlphaPlot* appWindow = openAproj(fileName);
            if (appWindow) {
                appWindow->workingDir = workingDir;
                if (fileName.endsWith(QString::fromLatin1(".aproj"), Qt::CaseInsensitive) ||
                    fileName.endsWith(QString::fromLatin1(".aproj~"), Qt::CaseInsensitive) ||
                    fileName.endsWith(QString::fromLatin1(".aproj.gz"), Qt::CaseInsensitive))
                    this->close();
            }
        }
        else {
            QMessageBox::critical(
                this, tr("File opening error"),
                tr("The file <b>%1</b> is not a valid project file.")
                .arg(fileName));
            return;
        }
        break;
    }
    case OpenProjectDialog::NewFolder:
        aprojhandler_->appendproject(openDialog->selectedFiles().at(0));
        break;
    }
}

MainAlphaPlot* MainAlphaPlot::openAproj(const QString& fileName)
{
    if (fileName.endsWith(QString::fromLatin1(".py"), Qt::CaseInsensitive)) {
        return loadScript(fileName);
    }
    else if (fileName.endsWith(QString::fromLatin1(".aproj"), Qt::CaseInsensitive)
             || fileName.endsWith(QString::fromLatin1(".aproj.gz"), Qt::CaseInsensitive)
             || fileName.endsWith(QString::fromLatin1(".aproj~"), Qt::CaseInsensitive)
             || fileName.endsWith(QString::fromLatin1(".aproj.gz~"), Qt::CaseInsensitive)) {
        return aprojhandler_->openproject(fileName);
    }
    else {
        return plotFile(fileName);
    }
}

void MainAlphaPlot::openRecentAproj()
{
    QAction* trigger = qobject_cast<QAction*>(sender());
    if (!trigger)
        return;
    QString filename = trigger->text();
    int pos = filename.indexOf(QString::fromLatin1(" "), 0);
    filename = filename.right(filename.length() - pos - 1);

    QFile file(filename);
    if (!file.exists()) {
        QMessageBox::critical(this, tr("File Open Error"),
                              tr("The file: <b> %1 </b> <p>does not exist anymore!"
                                 "<p>It will be removed from the list.")
                                  .arg(filename));

        recentProjects.removeAll(filename);
        updateRecentProjectsList();
        return;
    }

    if (projectname != QString::fromLatin1("untitled")) {
        QFileInfo fileinfo(projectname);
        QString pathname = fileinfo.absoluteFilePath();
        if (filename == pathname) {
            QMessageBox::warning(
                this, tr("File opening error"),
                tr("The file: <p><b> %1 </b><p> is the current file!").arg(filename));
            return;
        }
    }

    if (!filename.isEmpty()) {
        saveSettings();// the recent projects must be saved
        MainAlphaPlot* app = openAproj(filename);
        if (app
            && (filename.endsWith(QString::fromLatin1(".aproj"), Qt::CaseInsensitive)
                || filename.endsWith(QString::fromLatin1(".aproj~"), Qt::CaseInsensitive)
                || filename.endsWith(QString::fromLatin1(".aproj.gz"), Qt::CaseInsensitive)))
            this->close();
    }
}

void MainAlphaPlot::newCurve2D(Table* table, Column* xcol, Column* ycol)
{
    Layout2D* layout = newGraph2D();
    layout->generateCurve2DPlot(AxisRect2D::LineScatterType::Line2D, table, xcol,
                                QList<Column*>() << ycol, 0, xcol->rowCount() - 1);
}

void MainAlphaPlot::openTemplate()
{
    QString filter = tr("AlphaPlot 2D Graph Template") + QString::fromLatin1(" (*.apt);;");
    filter += tr("AlphaPlot 3D Surface Template") + QString::fromLatin1(" (*.ast);;");
    filter += tr("AlphaPlot Table Template") + QString::fromLatin1(" (*.att);;");
    filter += tr("AlphaPlot Matrix Template") + QString::fromLatin1(" (*.amt);;");

    QString filename =
        QFileDialog::getOpenFileName(this, tr("Open Template File"), templatesDir, filter);
    if (!filename.isEmpty()
        && (filename.endsWith(QString::fromLatin1(".apt"))
            || filename.endsWith(QString::fromLatin1(".ast"))
            || filename.endsWith(QString::fromLatin1(".att"))
            || filename.endsWith(QString::fromLatin1(".amt")))) {
        aprojhandler_->opentemplate(filename);
    }
}

void MainAlphaPlot::loadSettings()
{
        QSettings settings;

        /* ---------------- group General --------------- */
        settings.beginGroup(QString::fromLatin1("General"));
    #ifdef SEARCH_FOR_UPDATES
        autoSearchUpdates = settings.value(QString::fromLatin1("AutoSearchUpdates"), false).toBool();
    #endif
        settings.beginGroup(QString::fromLatin1("GlowIndicator"));
        glowstatus_ = settings.value(QString::fromLatin1("Show"), false).toBool();
        glowcolor_ = settings.value(QString::fromLatin1("Color"), QString::fromLatin1("red")).value<QColor>();
        glowradius_ = settings.value(QString::fromLatin1("Radius"), 8).toDouble();
        settings.endGroup();
        appLanguage =
            settings.value(QString::fromLatin1("Language"), QLocale::system().name().section(QChar::fromLatin1('_'), 0, 0))
            .toString();
        show_windows_policy = static_cast<ShowWindowsPolicy>(
            settings.value(QString::fromLatin1("ShowWindowsPolicy"), MainAlphaPlot::ActiveFolder)
            .toInt());

        recentProjects = settings.value(QString::fromLatin1("RecentProjects")).toStringList();
        // Follows an ugly hack to fix Qt4 porting issues (only needed on Windows)
    #ifdef Q_OS_WIN
        if (!recentProjects.isEmpty() && recentProjects[0].contains(QString::fromLatin1("^e")))
            recentProjects = recentProjects[0].split(QString::fromLatin1("^e"), QString::SkipEmptyParts);
        else if (recentProjects.count() == 1) {
            QString s = recentProjects[0];
            if (s.remove(QRegExp(QString::fromLatin1("\\s"))).isEmpty()) recentProjects = QStringList();
        }
    #endif

        updateRecentProjectsList();

        undoLimit = settings.value(QString::fromLatin1("UndoLimit"), 10).toInt();
        d_project->undoStack()->setUndoLimit(undoLimit);
        autoSave = settings.value(QString::fromLatin1("AutoSave"), true).toBool();
        autoSaveTime = settings.value(QString::fromLatin1("AutoSaveTime"), 15).toInt();
        defaultScriptingLang = settings.value(QString::fromLatin1("ScriptingLang"), QString::fromLatin1("muParser")).toString();

        QLocale temp_locale =
            QLocale(settings.value(QString::fromLatin1("Locale"), QLocale::system().name()).toString());
        bool usegl = settings.value(QString::fromLatin1("LocaleUseGroupSeparator"), true).toBool();
        if (usegl)
            temp_locale.setNumberOptions(temp_locale.numberOptions() &
                ~QLocale::OmitGroupSeparator);
        else
            temp_locale.setNumberOptions(temp_locale.numberOptions() |
                QLocale::OmitGroupSeparator);
        QLocale::setDefault(temp_locale);

        d_decimal_digits = settings.value(QString::fromLatin1("DecimalDigits"), 6).toInt();
        d_default_numeric_format =
            settings.value(QString::fromLatin1("DefaultNumericFormat"), 'g').toChar().toLatin1();

        // Set last used geometry to position window on the correct monitor(multi
        // monitor scenario)
        // Set window state only if the window was last maximized
        was_maximized_ = settings.value(QString::fromLatin1("Maximized"), false).toBool();
        restoreGeometry(settings.value(QString::fromLatin1("ProjectWindowGeometry")).toByteArray());

        //// restore dock windows and tool bars
        //restoreState(settings.value(QString::fromLatin1("DockWindows")).toByteArray());
        //ui_->explorerSplitter->restoreState(
        //    settings.value(QString::fromLatin1("ExplorerSplitter")).toByteArray());

    #ifdef SCRIPTING_CONSOLE
        consoleWindow->setSplitterPosition(settings.value("ScriptingConsoleSplitter").toByteArray());
    #endif

        QStringList applicationFont = settings.value(QString::fromLatin1("Font")).toStringList();
        if (applicationFont.size() == 4)
            appFont =
            QFont(applicationFont.at(0), applicationFont.at(1).toInt(),
                applicationFont.at(2).toInt(), applicationFont.at(3).toInt());

        settings.beginGroup(QString::fromLatin1("Dialogs"));
        d_extended_open_dialog = settings.value(QString::fromLatin1("ExtendedOpenDialog"), true).toBool();
        d_extended_export_dialog =
            settings.value(QString::fromLatin1("ExtendedExportDialog"), true).toBool();
        d_extended_import_ASCII_dialog =
            settings.value(QString::fromLatin1("ExtendedImportAsciiDialog"), true).toBool();
        d_extended_plot_dialog = settings.value(QString::fromLatin1("ExtendedPlotDialog"), true)
            .toBool();  // used by PlotDialog

        settings.beginGroup(QString::fromLatin1("AddRemoveCurves"));
        d_add_curves_dialog_size = QSize(settings.value(QString::fromLatin1("Width"), 700).toInt(),
            settings.value(QString::fromLatin1("Height"), 400).toInt());
        d_show_current_folder = settings.value(QString::fromLatin1("ShowCurrentFolder"), false).toBool();
        settings.endGroup();  // AddRemoveCurves Dialog
        settings.endGroup();  // Dialogs

        settings.beginGroup(QString::fromLatin1("Colors"));
        appCustomColor = settings.value(QString::fromLatin1("Custom"), false).toBool();
        /*workspaceColor =
            settings.value(QString::fromLatin1("Workspace"), d->mdiArea->background().color())
            .value<QColor>();*/
        // see http://doc.trolltech.com/4.2/qvariant.html for instructions on qcolor
        // <-> qvariant conversion
        panelsColor =
            settings.value(QString::fromLatin1("Panels"), palette().window().color()).value<QColor>();
        panelsTextColor = settings.value(QString::fromLatin1("PanelsText"), palette().windowText().color())
            .value<QColor>();
        settings.endGroup();  // Colors

        settings.beginGroup(QString::fromLatin1("Paths"));
        workingDir =
            settings.value(QString::fromLatin1("WorkingDir"), qApp->applicationDirPath()).toString();
        helpFilePath = settings.value(QString::fromLatin1("HelpFile"), QString::fromLatin1("")).toString();
    #ifdef PLUGIN_PATH
        QString defaultFitPluginsPath = PLUGIN_PATH;
    #else  // defined PLUGIN_PATH
    #ifdef Q_OS_WIN
        QString defaultFitPluginsPath = QString::fromLatin1("fitPlugins");
    #else
        QString defaultFitPluginsPath = QString::fromLatin1("/usr/lib/AlphaPlot/plugins");
    #endif
    #endif  // defined PLUGIN_PATH
    #ifdef DYNAMIC_PLUGIN_PATH
        fitPluginsPath =
            settings.value(QString::fromLatin1("FitPlugins", defaultFitPluginsPath).toString();
    #else  // defined PLUGIN_PATH
        fitPluginsPath = defaultFitPluginsPath;
    #endif

    #ifdef Q_OS_WIN
        templatesDir =
            settings.value(QString::fromLatin1("TemplatesDir"), qApp->applicationDirPath()).toString();
        asciiDirPath = settings.value(QString::fromLatin1("ASCII"), qApp->applicationDirPath()).toString();
        imagesDirPath =
            settings.value(QString::fromLatin1("Images"), qApp->applicationDirPath()).toString();
    #else
        templatesDir = settings.value(QString::fromLatin1("TemplatesDir"), QDir::homePath()).toString();
        asciiDirPath = settings.value(QString::fromLatin1("ASCII"), QDir::homePath()).toString();
        imagesDirPath = settings.value(QString::fromLatin1("Images"), QDir::homePath()).toString();
    #endif
        settings.endGroup();  // Paths
        settings.endGroup();
        /* ------------- end group General ------------------- */

    //    settings.beginGroup(QString::fromLatin1("View"));
    //    ui_->actionShowFileToolbar->setChecked(
    //        settings.value(QString::fromLatin1("FileToolbar"), true).toBool());
    //    ui_->actionShowEditToolbar->setChecked(
    //        settings.value(QString::fromLatin1("EditToolbar"), true).toBool());
    //    ui_->actionShowGraphToolbar->setChecked(
    //        settings.value(QString::fromLatin1("GraphToolbar"), true).toBool());
    //    ui_->actionShowPlotToolbar->setChecked(
    //        settings.value(QString::fromLatin1("PlotToolbar"), true).toBool());
    //    ui_->actionShowTableToolbar->setChecked(
    //        settings.value(QString::fromLatin1("TableToolbar"), true).toBool());
    //    ui_->actionShowMatrixPlotToolbar->setChecked(
    //        settings.value(QString::fromLatin1("MatrixPlotToolbar"), true).toBool());
    //    ui_->actionShow3DSurfacePlotToolbar->setChecked(
    //        settings.value(QString::fromLatin1("3DSurfacePlotToolbar"), true).toBool());
    //    ui_->actionLockToolbars->setChecked(
    //        settings.value(QString::fromLatin1("LockToolbars"), false).toBool());
    //    ui_->explorerWindow->setVisible(
    //        settings.value(QString::fromLatin1("ShowExplorer"), false).toBool());
    //    ui_->logWindow->setVisible(settings.value(QString::fromLatin1("ShowResultsLog"), false).toBool());
    //#ifdef SCRIPTING_CONSOLE
    //    consoleWindow->setVisible(settings.value(QString::fromLatin1("ShowConsole"), false).toBool());
    //#endif
    //    settings.endGroup();  // View

        settings.beginGroup(QString::fromLatin1("UserFunctions"));
        fitFunctions = settings.value(QString::fromLatin1("FitFunctions")).toStringList();
        surfaceFunc = settings.value(QString::fromLatin1("SurfaceFunctions")).toStringList();
        xFunctions = settings.value(QString::fromLatin1("xFunctions")).toStringList();
        yFunctions = settings.value(QString::fromLatin1("yFunctions")).toStringList();
        rFunctions = settings.value(QString::fromLatin1("rFunctions")).toStringList();
        thetaFunctions = settings.value(QString::fromLatin1("thetaFunctions")).toStringList();
        settings.endGroup();  // UserFunctions

        settings.beginGroup(QString::fromLatin1("Confirmations"));
        confirmCloseFolder = settings.value(QString::fromLatin1("Folder"), true).toBool();
        confirmCloseTable = settings.value(QString::fromLatin1("Table"), true).toBool();
        confirmCloseMatrix = settings.value(QString::fromLatin1("Matrix"), true).toBool();
        confirmClosePlot2D = settings.value(QString::fromLatin1("Plot2D"), true).toBool();
        confirmClosePlot3D = settings.value(QString::fromLatin1("Plot3D"), true).toBool();
        confirmCloseNotes = settings.value(QString::fromLatin1("Note"), true).toBool();
        settings.endGroup();  // Confirmations

        /* ---------------- group Tables --------------- */
        settings.beginGroup(QString::fromLatin1("Tables"));
        d_show_table_comments = settings.value(QString::fromLatin1("DisplayComments"), false).toBool();
        QStringList tableFonts = settings.value(QString::fromLatin1("Fonts")).toStringList();
        if (tableFonts.size() == 8) {
            tableTextFont = QFont(tableFonts[0], tableFonts[1].toInt(),
                tableFonts[2].toInt(), tableFonts[3].toInt());
            tableHeaderFont = QFont(tableFonts[4], tableFonts[5].toInt(),
                tableFonts[6].toInt(), tableFonts[7].toInt());
        }
        settings.beginGroup(QString::fromLatin1("ColumnColorIndicator"));
        AppearanceManager::xColorCode =
            settings.value(QString::fromLatin1("xColorCode"), QColor(0, 172, 109, 100)).value<QColor>();
        AppearanceManager::yColorCode =
            settings.value(QString::fromLatin1("yColorCode"), QColor(204, 140, 91, 100)).value<QColor>();
        AppearanceManager::zColorCode =
            settings.value(QString::fromLatin1("zColorCode"), QColor(174, 129, 255, 100)).value<QColor>();
        AppearanceManager::xErrColorCode =
            settings.value(QString::fromLatin1("xErrColorCode"), QColor(255, 0, 0, 100)).value<QColor>();
        AppearanceManager::yErrColorCode =
            settings.value(QString::fromLatin1("yErrColorCode"), QColor(255, 0, 0, 100)).value<QColor>();
        AppearanceManager::noneColorCode =
            settings.value(QString::fromLatin1("noneColorCode"), QColor(150, 150, 150, 100))
            .value<QColor>();
        settings.endGroup();  // ColumnColorIndicator
        settings.beginGroup(QString::fromLatin1("Colors"));
        tableCustomColor = settings.value(QString::fromLatin1("Custom"), false).toBool();
        tableBkgdColor =
            settings.value(QString::fromLatin1("Background"), qApp->palette().color(QPalette::Base))
            .value<QColor>();
        tableTextColor = settings.value(QString::fromLatin1("Text"), qApp->palette().color(QPalette::Text))
            .value<QColor>();
        tableHeaderColor =
            settings.value(QString::fromLatin1("Header"), qApp->palette().color(QPalette::Text))
            .value<QColor>();
        settings.endGroup();  // Colors
        settings.endGroup();  // Tables
        /* --------------- end group Tables ------------------------ */

        /* --------------- group 2D Plots ----------------------------- */
        settings.beginGroup(QString::fromLatin1("2DPlots"));
        settings.beginGroup(QString::fromLatin1("General"));
        titleOn = settings.value(QString::fromLatin1("Title"), true).toBool();
        allAxesOn = settings.value(QString::fromLatin1("AllAxes"), false).toBool();
        canvasFrameOn = settings.value(QString::fromLatin1("CanvasFrame"), false).toBool();
        canvasFrameWidth = settings.value(QString::fromLatin1("CanvasFrameWidth"), 0).toInt();
        defaultPlotMargin = settings.value(QString::fromLatin1("Margin"), 0).toInt();
        drawBackbones = settings.value(QString::fromLatin1("AxesBackbones"), true).toBool();
        axesLineWidth = settings.value(QString::fromLatin1("AxesLineWidth"), 1).toInt();
        autoscale2DPlots = settings.value(QString::fromLatin1("Autoscale"), true).toBool();
        autoScaleFonts = settings.value(QString::fromLatin1("AutoScaleFonts"), true).toBool();
        autoResizeLayers = settings.value(QString::fromLatin1("AutoResizeLayers"), true).toBool();
        antialiasing2DPlots = settings.value(QString::fromLatin1("Antialiasing"), true).toBool();
        d_scale_plots_on_print = settings.value(QString::fromLatin1("ScaleLayersOnPrint"), false).toBool();
        d_print_cropmarks = settings.value(QString::fromLatin1("PrintCropmarks"), false).toBool();

        QStringList graphFonts = settings.value(QString::fromLatin1("Fonts")).toStringList();
        if (graphFonts.size() == 16) {
            plotAxesFont = QFont(graphFonts[0], graphFonts[1].toInt(),
                graphFonts[2].toInt(), graphFonts[3].toInt());
            plotNumbersFont = QFont(graphFonts[4], graphFonts[5].toInt(),
                graphFonts[6].toInt(), graphFonts[7].toInt());
            plotLegendFont = QFont(graphFonts[8], graphFonts[9].toInt(),
                graphFonts[10].toInt(), graphFonts[11].toInt());
            plotTitleFont = QFont(graphFonts[12], graphFonts[13].toInt(),
                graphFonts[14].toInt(), graphFonts[15].toInt());
        }
        settings.endGroup();  // General

        settings.beginGroup(QString::fromLatin1("Curves"));
        defaultCurveLineWidth = settings.value(QString::fromLatin1("LineWidth"), 1).toInt();
        defaultSymbolSize = settings.value(QString::fromLatin1("SymbolSize"), 7).toInt();
        settings.endGroup();  // Curves

        settings.beginGroup(QString::fromLatin1("Ticks"));
        minTicksLength = settings.value(QString::fromLatin1("MinTicksLength"), 5).toInt();
        majTicksLength = settings.value(QString::fromLatin1("MajTicksLength"), 9).toInt();
        settings.endGroup();  // Ticks

        settings.beginGroup(QString::fromLatin1("Legend"));
        legendTextColor = settings.value(QString::fromLatin1("TextColor"), QString::fromLatin1("#000000"))
            .value<QColor>();  // default color Qt::black
        legendBackground = settings.value(QString::fromLatin1("BackgroundColor"), QString::fromLatin1("#ffffff"))
            .value<QColor>();  // default color Qt::white
        legendBackground.setAlpha(
            settings.value(QString::fromLatin1("Transparency"), 0).toInt());  // transparent by default;
        settings.endGroup();                             // Legend

        settings.beginGroup(QString::fromLatin1("Arrows"));
        defaultArrowLineWidth = settings.value(QString::fromLatin1("Width"), 1).toInt();
        defaultArrowColor = settings.value(QString::fromLatin1("Color"), QString::fromLatin1("#000000"))
            .value<QColor>();  // default color Qt::black
        defaultArrowHeadLength = settings.value(QString::fromLatin1("HeadLength"), 4).toInt();
        defaultArrowHeadAngle = settings.value(QString::fromLatin1("HeadAngle"), 45).toInt();
        defaultArrowHeadFill = settings.value(QString::fromLatin1("HeadFill"), true).toBool();
        settings.endGroup();  // Arrows
        settings.endGroup();
        /* ----------------- end group 2D Plots --------------------------- */

        /* ----------------- group 3D Plots --------------------------- */
        settings.beginGroup(QString::fromLatin1("3DPlots"));
        showPlot3DLegend = settings.value(QString::fromLatin1("Legend"), true).toBool();
        showPlot3DProjection = settings.value(QString::fromLatin1("Projection"), false).toBool();
        smooth3DMesh = settings.value(QString::fromLatin1("Antialiasing"), true).toBool();
        plot3DResolution = settings.value(QString::fromLatin1("Resolution"), 1).toInt();
        orthogonal3DPlots = settings.value(QString::fromLatin1("Orthogonal"), false).toBool();
        autoscale3DPlots = settings.value(QString::fromLatin1("Autoscale"), true).toBool();

        QStringList plot3DFonts = settings.value(QString::fromLatin1("Fonts")).toStringList();
        if (plot3DFonts.size() == 12) {
            plot3DTitleFont = QFont(plot3DFonts[0], plot3DFonts[1].toInt(),
                plot3DFonts[2].toInt(), plot3DFonts[3].toInt());
            plot3DNumbersFont = QFont(plot3DFonts[4], plot3DFonts[5].toInt(),
                plot3DFonts[6].toInt(), plot3DFonts[7].toInt());
            plot3DAxesFont = QFont(plot3DFonts[8], plot3DFonts[9].toInt(),
                plot3DFonts[10].toInt(), plot3DFonts[11].toInt());
        }

        settings.beginGroup(QString::fromLatin1("Colors"));
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("MaxData"), QString::fromLatin1("blue")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("Labels"), QString::fromLatin1("#000000")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("Mesh"), QString::fromLatin1("#000000")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("Grid"), QString::fromLatin1("#000000")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("MinData"), QString::fromLatin1("red")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("Numbers"), QString::fromLatin1("#000000")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("Axes"), QString::fromLatin1("#000000")).value<QColor>()).name();
        plot3DColors
            << QColor(settings.value(QString::fromLatin1("Background"), QString::fromLatin1("#ffffff")).value<QColor>()).name();
        settings.endGroup();  // Colors
        settings.endGroup();
        /* ----------------- end group 3D Plots --------------------------- */

        settings.beginGroup(QString::fromLatin1("Fitting"));
        fit_output_precision = settings.value(QString::fromLatin1("OutputPrecision"), 15).toInt();
        pasteFitResultsToPlot = settings.value(QString::fromLatin1("PasteResultsToPlot"), false).toBool();
        writeFitResultsToLog = settings.value(QString::fromLatin1("WriteResultsToLog"), true).toBool();
        generateUniformFitPoints = settings.value(QString::fromLatin1("GenerateFunction"), true).toBool();
        fitPoints = settings.value(QString::fromLatin1("Points"), 100).toInt();
        generatePeakCurves = settings.value(QString::fromLatin1("GeneratePeakCurves"), true).toBool();
        peakCurvesColor = settings.value(QString::fromLatin1("PeaksColor"), 2).toInt();  // green color
        fit_scale_errors = settings.value(QString::fromLatin1("ScaleErrors"), false).toBool();
        d_2_linear_fit_points = settings.value(QString::fromLatin1("TwoPointsLinearFit"), true).toBool();
        settings.endGroup();  // Fitting

        settings.beginGroup(QString::fromLatin1("ImportASCII"));
        columnSeparator = settings.value(QString::fromLatin1("ColumnSeparator"), QString::fromLatin1("\\t")).toString();
        columnSeparator.replace(QString::fromLatin1("\\t"), QString::fromLatin1("\t")).replace(QString::fromLatin1("\\s"), QString::fromLatin1(" "));
        ignoredLines = settings.value(QString::fromLatin1("IgnoreLines"), 0).toInt();
        renameColumns = settings.value(QString::fromLatin1("RenameColumns"), true).toBool();
        strip_spaces = settings.value(QString::fromLatin1("StripSpaces"), false).toBool();
        simplify_spaces = settings.value(QString::fromLatin1("SimplifySpaces"), false).toBool();
        d_ASCII_file_filter = settings.value(QString::fromLatin1("AsciiFileTypeFilter"), QString::fromLatin1("*")).toString();
        d_ASCII_import_locale = settings.value(QString::fromLatin1("AsciiImportLocale"), QString::fromLatin1("C")).toString();
        d_convert_to_numeric = settings.value(QString::fromLatin1("ConvertToNumeric"), true).toBool();
        settings.endGroup();  // Import ASCII

        settings.beginGroup(QString::fromLatin1("ExportImage"));
        d_image_export_filter =
            settings.value(QString::fromLatin1("ImageFileTypeFilter"), QString::fromLatin1(".png")).toString();
        d_export_transparency = settings.value(QString::fromLatin1("ExportTransparency"), false).toBool();
        d_export_quality = settings.value(QString::fromLatin1("ImageQuality"), 100).toInt();
        d_export_resolution = settings.value(QString::fromLatin1("Resolution"), 72).toInt();
        d_export_color = settings.value(QString::fromLatin1("ExportColor"), true).toBool();
        d_export_vector_size =
            settings.value(QString::fromLatin1("ExportPageSize"), QPrinter::Custom).toInt();
        d_keep_plot_aspect = settings.value(QString::fromLatin1("KeepAspect"), true).toBool();
        d_export_orientation =
            settings.value(QString::fromLatin1("Orientation"), QPrinter::Landscape).toInt();
        settings.endGroup();  // ExportImage
}

void MainAlphaPlot::saveSettings()
{
        QSettings settings;

        /* ---------------- group General --------------- */
        settings.beginGroup(QString::fromLatin1("General"));
    #ifdef SEARCH_FOR_UPDATES
        settings.setValue(QString::fromLatin1("AutoSearchUpdates"), autoSearchUpdates);
    #endif
        settings.beginGroup(QString::fromLatin1("GlowIndicator"));
        settings.setValue(QString::fromLatin1("Show"), glowstatus_);
        settings.setValue(QString::fromLatin1("Color"), glowcolor_);
        settings.setValue(QString::fromLatin1("Radius"), glowradius_);
        settings.endGroup();
        settings.setValue(QString::fromLatin1("Language"), appLanguage);
        settings.setValue(QString::fromLatin1("ShowWindowsPolicy"), show_windows_policy);
        settings.setValue(QString::fromLatin1("RecentProjects"), recentProjects);
        settings.setValue(QString::fromLatin1("Style"), appStyle);
        settings.setValue(QString::fromLatin1("ColorScheme"), appColorScheme);
        settings.setValue(QString::fromLatin1("AutoSave"), autoSave);
        settings.setValue(QString::fromLatin1("AutoSaveTime"), autoSaveTime);
        settings.setValue(QString::fromLatin1("UndoLimit"), undoLimit);
        settings.setValue(QString::fromLatin1("ScriptingLang"), defaultScriptingLang);
        settings.setValue(QString::fromLatin1("Locale"), QLocale().name());
        settings.setValue(
            QString::fromLatin1("LocaleUseGroupSeparator"),
            bool(!(QLocale().numberOptions() & QLocale::OmitGroupSeparator)));
        settings.setValue(QString::fromLatin1("DecimalDigits"), d_decimal_digits);
        settings.setValue(QString::fromLatin1("DefaultNumericFormat"), QChar::fromLatin1(d_default_numeric_format));

        was_maximized_ = isMaximized();
        settings.setValue(QString::fromLatin1("Maximized"), was_maximized_);
        // Save the mainwindow geometry
        settings.setValue(QString::fromLatin1("ProjectWindowGeometry"), saveGeometry());

      /*  settings.setValue(QString::fromLatin1("DockWindows"), saveState());
        settings.setValue(QString::fromLatin1("ExplorerSplitter"), ui_->explorerSplitter->saveState());*/

    #ifdef SCRIPTING_CONSOLE
        settings.setValue(QString::fromLatin1("ScriptingConsoleSplitter"), consoleWindow->getSplitterPosition());
    #endif

        QStringList applicationFont;
        applicationFont << appFont.family();
        applicationFont << QString::number(appFont.pointSize());
        applicationFont << QString::number(appFont.weight());
        applicationFont << QString::number(appFont.italic());
        settings.setValue(QString::fromLatin1("Font"), applicationFont);

        settings.beginGroup(QString::fromLatin1("Dialogs"));
        settings.setValue(QString::fromLatin1("ExtendedOpenDialog"), d_extended_open_dialog);
        settings.setValue(QString::fromLatin1("ExtendedExportDialog"), d_extended_export_dialog);
        settings.setValue(QString::fromLatin1("ExtendedImportAsciiDialog"),
            d_extended_import_ASCII_dialog);
        settings.setValue(QString::fromLatin1("ExtendedPlotDialog"), d_extended_plot_dialog);
        settings.beginGroup(QString::fromLatin1("AddRemoveCurves"));
        settings.setValue(QString::fromLatin1("Width"), d_add_curves_dialog_size.width());
        settings.setValue(QString::fromLatin1("Height"), d_add_curves_dialog_size.height());
        settings.setValue(QString::fromLatin1("ShowCurrentFolder"), d_show_current_folder);
        settings.endGroup();  // AddRemoveCurves Dialog
        settings.endGroup();  // Dialogs

        settings.beginGroup(QString::fromLatin1("Colors"));
        settings.setValue(QString::fromLatin1("Custon"), appCustomColor);
        settings.setValue(QString::fromLatin1("Workspace"), workspaceColor);
        settings.setValue(QString::fromLatin1("Panels"), panelsColor);
        settings.setValue(QString::fromLatin1("PanelsText"), panelsTextColor);
        settings.endGroup();  // Colors

        settings.beginGroup(QString::fromLatin1("Paths"));
        settings.setValue(QString::fromLatin1("WorkingDir"), workingDir);
        settings.setValue(QString::fromLatin1("TemplatesDir"), templatesDir);
        settings.setValue(QString::fromLatin1("HelpFile"), helpFilePath);
        settings.setValue(QString::fromLatin1("FitPlugins"), fitPluginsPath);
        settings.setValue(QString::fromLatin1("ASCII"), asciiDirPath);
        settings.setValue(QString::fromLatin1("Images"), imagesDirPath);
        settings.endGroup();  // Paths
        settings.endGroup();
        /* ---------------- end group General --------------- */

    //    settings.beginGroup(QString::fromLatin1("View"));
    //    settings.setValue(QString::fromLatin1("FileToolbar"), ui_->actionShowFileToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("EditToolbar"), ui_->actionShowEditToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("GraphToolbar"), ui_->actionShowGraphToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("PlotToolbar"), ui_->actionShowPlotToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("TableToolbar"), ui_->actionShowTableToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("MatrixPlotToolbar"),
    //        ui_->actionShowMatrixPlotToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("3DSurfacePlotToolbar"),
    //        ui_->actionShow3DSurfacePlotToolbar->isChecked());
    //    settings.setValue(QString::fromLatin1("LockToolbars"), ui_->actionLockToolbars->isChecked());
    //    settings.setValue(QString::fromLatin1("ShowExplorer"), ui_->explorerWindow->isVisible());
    //    settings.setValue(QString::fromLatin1("ShowResultsLog"), ui_->logWindow->isVisible());
    //#ifdef SCRIPTING_CONSOLE
    //    settings.setValue(QString::fromLatin1("ShowConsole"), consoleWindow->isVisible());
    //#endif
    //    settings.endGroup();  // View

        settings.beginGroup(QString::fromLatin1("UserFunctions"));
        settings.setValue(QString::fromLatin1("FitFunctions"), fitFunctions);
        settings.setValue(QString::fromLatin1("SurfaceFunctions"), surfaceFunc);
        settings.setValue(QString::fromLatin1("xFunctions"), xFunctions);
        settings.setValue(QString::fromLatin1("yFunctions"), yFunctions);
        settings.setValue(QString::fromLatin1("rFunctions"), rFunctions);
        settings.setValue(QString::fromLatin1("thetaFunctions"), thetaFunctions);
        settings.endGroup();  // UserFunctions

        settings.beginGroup(QString::fromLatin1("Confirmations"));
        settings.setValue(QString::fromLatin1("Folder"), confirmCloseFolder);
        settings.setValue(QString::fromLatin1("Table"), confirmCloseTable);
        settings.setValue(QString::fromLatin1("Matrix"), confirmCloseMatrix);
        settings.setValue(QString::fromLatin1("Plot2D"), confirmClosePlot2D);
        settings.setValue(QString::fromLatin1("Plot3D"), confirmClosePlot3D);
        settings.setValue(QString::fromLatin1("Note"), confirmCloseNotes);
        settings.endGroup();  // Confirmations

        /* ----------------- group Tables -------------- */
        settings.beginGroup(QString::fromLatin1("Tables"));
        settings.setValue(QString::fromLatin1("DisplayComments"), d_show_table_comments);
        QStringList tableFonts;
        tableFonts << tableTextFont.family();
        tableFonts << QString::number(tableTextFont.pointSize());
        tableFonts << QString::number(tableTextFont.weight());
        tableFonts << QString::number(tableTextFont.italic());
        tableFonts << tableHeaderFont.family();
        tableFonts << QString::number(tableHeaderFont.pointSize());
        tableFonts << QString::number(tableHeaderFont.weight());
        tableFonts << QString::number(tableHeaderFont.italic());
        settings.setValue(QString::fromLatin1("Fonts"), tableFonts);
        settings.beginGroup(QString::fromLatin1("ColumnColorIndicator"));
        settings.setValue(QString::fromLatin1("xColorCode"), AppearanceManager::xColorCode);
        settings.setValue(QString::fromLatin1("yColorCode"), AppearanceManager::yColorCode);
        settings.setValue(QString::fromLatin1("zColorCode"), AppearanceManager::zColorCode);
        settings.setValue(QString::fromLatin1("xErrColorCode"), AppearanceManager::xErrColorCode);
        settings.setValue(QString::fromLatin1("yErrColorCode"), AppearanceManager::yErrColorCode);
        settings.setValue(QString::fromLatin1("noneColorCode"), AppearanceManager::noneColorCode);
        settings.endGroup();

        settings.beginGroup(QString::fromLatin1("Colors"));
        settings.setValue(QString::fromLatin1("Custom"), tableCustomColor);
        settings.setValue(QString::fromLatin1("Background"), tableBkgdColor);
        settings.setValue(QString::fromLatin1("Text"), tableTextColor);
        settings.setValue(QString::fromLatin1("Header"), tableHeaderColor);
        settings.endGroup();  // Colors
        settings.endGroup();
        /* ----------------- end group Tables ---------- */

        /* ----------------- group 2D Plots ------------ */
        settings.beginGroup(QString::fromLatin1("2DPlots"));
        settings.beginGroup(QString::fromLatin1("General"));
        settings.setValue(QString::fromLatin1("Title"), titleOn);
        settings.setValue(QString::fromLatin1("AllAxes"), allAxesOn);
        settings.setValue(QString::fromLatin1("CanvasFrame"), canvasFrameOn);
        settings.setValue(QString::fromLatin1("CanvasFrameWidth"), canvasFrameWidth);
        settings.setValue(QString::fromLatin1("Margin"), defaultPlotMargin);
        settings.setValue(QString::fromLatin1("AxesBackbones"), drawBackbones);
        settings.setValue(QString::fromLatin1("AxesLineWidth"), axesLineWidth);
        settings.setValue(QString::fromLatin1("Autoscale"), autoscale2DPlots);
        settings.setValue(QString::fromLatin1("AutoScaleFonts"), autoScaleFonts);
        settings.setValue(QString::fromLatin1("AutoResizeLayers"), autoResizeLayers);
        settings.setValue(QString::fromLatin1("Antialiasing"), antialiasing2DPlots);
        settings.setValue(QString::fromLatin1("ScaleLayersOnPrint"), d_scale_plots_on_print);
        settings.setValue(QString::fromLatin1("PrintCropmarks"), d_print_cropmarks);

        QStringList graphFonts;
        graphFonts << plotAxesFont.family();
        graphFonts << QString::number(plotAxesFont.pointSize());
        graphFonts << QString::number(plotAxesFont.weight());
        graphFonts << QString::number(plotAxesFont.italic());
        graphFonts << plotNumbersFont.family();
        graphFonts << QString::number(plotNumbersFont.pointSize());
        graphFonts << QString::number(plotNumbersFont.weight());
        graphFonts << QString::number(plotNumbersFont.italic());
        graphFonts << plotLegendFont.family();
        graphFonts << QString::number(plotLegendFont.pointSize());
        graphFonts << QString::number(plotLegendFont.weight());
        graphFonts << QString::number(plotLegendFont.italic());
        graphFonts << plotTitleFont.family();
        graphFonts << QString::number(plotTitleFont.pointSize());
        graphFonts << QString::number(plotTitleFont.weight());
        graphFonts << QString::number(plotTitleFont.italic());
        settings.setValue(QString::fromLatin1("Fonts"), graphFonts);
        settings.endGroup();  // General

        settings.beginGroup(QString::fromLatin1("Curves"));
        settings.setValue(QString::fromLatin1("Style"), defaultCurveStyle);
        settings.setValue(QString::fromLatin1("LineWidth"), defaultCurveLineWidth);
        settings.setValue(QString::fromLatin1("SymbolSize"), defaultSymbolSize);
        settings.endGroup();  // Curves

        settings.beginGroup(QString::fromLatin1("Ticks"));
        settings.setValue(QString::fromLatin1("MajTicksStyle"), majTicksStyle);
        settings.setValue(QString::fromLatin1("MinTicksStyle"), minTicksStyle);
        settings.setValue(QString::fromLatin1("MinTicksLength"), minTicksLength);
        settings.setValue(QString::fromLatin1("MajTicksLength"), majTicksLength);
        settings.endGroup();  // Ticks

        settings.beginGroup(QString::fromLatin1("Legend"));
        settings.setValue(QString::fromLatin1("FrameStyle"), legendFrameStyle);
        settings.setValue(QString::fromLatin1("TextColor"), legendTextColor);
        settings.setValue(QString::fromLatin1("BackgroundColor"), legendBackground);
        settings.setValue(QString::fromLatin1("Transparency"), legendBackground.alpha());
        settings.endGroup();  // Legend

        settings.beginGroup(QString::fromLatin1("Arrows"));
        settings.setValue(QString::fromLatin1("Width"), defaultArrowLineWidth);
        settings.setValue(QString::fromLatin1("Color"), defaultArrowColor.name());
        settings.setValue(QString::fromLatin1("HeadLength"), defaultArrowHeadLength);
        settings.setValue(QString::fromLatin1("HeadAngle"), defaultArrowHeadAngle);
        settings.setValue(QString::fromLatin1("HeadFill"), defaultArrowHeadFill);
        settings.setValue(QString::fromLatin1("LineStyle"), QString::fromLatin1(""));
        settings.endGroup();  // Arrows
        settings.endGroup();
        /* ----------------- end group 2D Plots -------- */

        /* ----------------- group 3D Plots ------------ */
        settings.beginGroup(QString::fromLatin1("3DPlots"));
        settings.setValue(QString::fromLatin1("Legend"), showPlot3DLegend);
        settings.setValue(QString::fromLatin1("Projection"), showPlot3DProjection);
        settings.setValue(QString::fromLatin1("Antialiasing"), smooth3DMesh);
        settings.setValue(QString::fromLatin1("Resolution"), plot3DResolution);
        settings.setValue(QString::fromLatin1("Orthogonal"), orthogonal3DPlots);
        settings.setValue(QString::fromLatin1("Autoscale"), autoscale3DPlots);

        QStringList plot3DFonts;
        plot3DFonts << plot3DTitleFont.family();
        plot3DFonts << QString::number(plot3DTitleFont.pointSize());
        plot3DFonts << QString::number(plot3DTitleFont.weight());
        plot3DFonts << QString::number(plot3DTitleFont.italic());
        plot3DFonts << plot3DNumbersFont.family();
        plot3DFonts << QString::number(plot3DNumbersFont.pointSize());
        plot3DFonts << QString::number(plot3DNumbersFont.weight());
        plot3DFonts << QString::number(plot3DNumbersFont.italic());
        plot3DFonts << plot3DAxesFont.family();
        plot3DFonts << QString::number(plot3DAxesFont.pointSize());
        plot3DFonts << QString::number(plot3DAxesFont.weight());
        plot3DFonts << QString::number(plot3DAxesFont.italic());
        settings.setValue(QString::fromLatin1("Fonts"), plot3DFonts);

        settings.beginGroup(QString::fromLatin1("Colors"));
        settings.setValue(QString::fromLatin1("MaxData"), plot3DColors[0]);
        settings.setValue(QString::fromLatin1("Labels"), plot3DColors[1]);
        settings.setValue(QString::fromLatin1("Mesh"), plot3DColors[2]);
        settings.setValue(QString::fromLatin1("Grid"), plot3DColors[3]);
        settings.setValue(QString::fromLatin1("MinData"), plot3DColors[4]);
        settings.setValue(QString::fromLatin1("Numbers"), plot3DColors[5]);
        settings.setValue(QString::fromLatin1("Axes"), plot3DColors[6]);
        settings.setValue(QString::fromLatin1("Background"), plot3DColors[7]);
        settings.endGroup();  // Colors
        settings.endGroup();
        /* ----------------- end group 2D Plots -------- */

        settings.beginGroup(QString::fromLatin1("Fitting"));
        settings.setValue(QString::fromLatin1("OutputPrecision"), fit_output_precision);
        settings.setValue(QString::fromLatin1("PasteResultsToPlot"), pasteFitResultsToPlot);
        settings.setValue(QString::fromLatin1("WriteResultsToLog"), writeFitResultsToLog);
        settings.setValue(QString::fromLatin1("GenerateFunction"), generateUniformFitPoints);
        settings.setValue(QString::fromLatin1("Points"), fitPoints);
        settings.setValue(QString::fromLatin1("GeneratePeakCurves"), generatePeakCurves);
        settings.setValue(QString::fromLatin1("PeaksColor"), peakCurvesColor);
        settings.setValue(QString::fromLatin1("ScaleErrors"), fit_scale_errors);
        settings.setValue(QString::fromLatin1("TwoPointsLinearFit"), d_2_linear_fit_points);
        settings.endGroup();  // Fitting

        settings.beginGroup(QString::fromLatin1("ImportASCII"));
        QString sep = columnSeparator;
        settings.setValue(QString::fromLatin1("ColumnSeparator"),
            sep.replace(QString::fromLatin1("\t"), QString::fromLatin1("\\t")).replace(QString::fromLatin1(" "), QString::fromLatin1("\\s")));
        settings.setValue(QString::fromLatin1("IgnoreLines"), ignoredLines);
        settings.setValue(QString::fromLatin1("RenameColumns"), renameColumns);
        settings.setValue(QString::fromLatin1("StripSpaces"), strip_spaces);
        settings.setValue(QString::fromLatin1("SimplifySpaces"), simplify_spaces);
        settings.setValue(QString::fromLatin1("AsciiFileTypeFilter"), d_ASCII_file_filter);
        settings.setValue(QString::fromLatin1("AsciiImportLocale"), d_ASCII_import_locale.name());
        settings.setValue(QString::fromLatin1("ConvertToNumeric"), d_convert_to_numeric);
        settings.endGroup();  // ImportASCII

        settings.beginGroup(QString::fromLatin1("ExportImage"));
        settings.setValue(QString::fromLatin1("ImageFileTypeFilter"), d_image_export_filter);
        settings.setValue(QString::fromLatin1("ExportTransparency"), d_export_transparency);
        settings.setValue(QString::fromLatin1("ImageQuality"), d_export_quality);
        settings.setValue(QString::fromLatin1("Resolution"), d_export_resolution);
        settings.setValue(QString::fromLatin1("ExportColor"), d_export_color);
        settings.setValue(QString::fromLatin1("ExportPageSize"), d_export_vector_size);
        settings.setValue(QString::fromLatin1("KeepAspect"), d_keep_plot_aspect);
        settings.setValue(QString::fromLatin1("Orientation"), d_export_orientation);
        settings.endGroup();  // ExportImage
}

void MainAlphaPlot::exportGraph()
{
    QMdiSubWindow* w = getactiveMyWidget();
    if (!w)
        return;

    if (isActiveSubWindow(w, SubWindowType::Plot2DSubWindow)) {
        Layout2D* plot2D = qobject_cast<Layout2D*>(w);
        if (!plot2D->getCurrentAxisRect()) {
            QMessageBox::critical(
                this, tr("Export Error"),
                tr("<h4>There are no plot layouts available in this window!</h4>"));
            return;
        }
        else {
            plot2D->exportGraph();
            return;
        }
    }
    else if (isActiveSubWindow(w, SubWindowType::Plot3DSubWindow)) {
        Layout3D* plot3D = qobject_cast<Layout3D*>(w);
        plot3D->exportGraph();
    }
}

void MainAlphaPlot::exportLayer() { qDebug() << "not implimented"; }

void MainAlphaPlot::exportAllGraphs()
{
    ImageExportDlg* ied = new ImageExportDlg(this, true, d_extended_export_dialog);
    ied->setWindowTitle(tr("Choose a directory to export the graphs to"));
    QStringList tmp = ied->nameFilters();
    ied->setFileMode(QFileDialog::Directory);
    ied->setNameFilters(tmp);
    ied->setLabelText(QFileDialog::FileType, tr("Output format:"));
    ied->setLabelText(QFileDialog::FileName, tr("Directory:"));

    ied->setDirectory(workingDir);
    ied->selectFilter(d_image_export_filter);

    if (ied->exec() != QDialog::Accepted)
        return;
    workingDir = ied->directory().path();
    if (ied->selectedFiles().isEmpty())
        return;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QString output_dir = ied->selectedFiles()[0];
    QString file_suffix = ied->selectedNameFilter();
    file_suffix = file_suffix.toLower();
    file_suffix.remove(QString::fromLatin1("*"));

    QList<QMdiSubWindow*> windows = subWindowsList();
    bool confirm_overwrite = true;
    Layout2D* plot2D;
    Layout3D* plot3D;

    Q_FOREACH (QMdiSubWindow* w, windows) {
        if (isActiveSubWindow(w, SubWindowType::Plot2DSubWindow)) {
            plot3D = nullptr;
            plot2D = qobject_cast<Layout2D*>(w);
            if (!plot2D->getCurrentAxisRect()) {
                QApplication::restoreOverrideCursor();
                QMessageBox::warning(
                    this, tr("Warning"),
                    tr("There are no plot layers available in window <b>%1</b>.<br>"
                       "Graph window not exported!")
                        .arg(plot2D->name()));
                QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
                continue;
            }
        }
        else if (isActiveSubWindow(w, SubWindowType::Plot3DSubWindow)) {
            plot2D = nullptr;
            plot3D = qobject_cast<Layout3D*>(w);
        }
        else
            continue;

        QString file_name = output_dir + QString::fromLatin1("/") + w->objectName() + file_suffix;
        QFile f(file_name);
        if (f.exists() && confirm_overwrite) {
            QApplication::restoreOverrideCursor();
            switch (QMessageBox::question(this, tr("Overwrite file?"),
                                          tr("A file called: <p><b>%1</b><p>already exists. "
                                             "Do you want to overwrite it?")
                                              .arg(file_name),
                                          tr("&Yes"), tr("&All"), tr("&Cancel"), 0, 1)) {
                case 1:
                    confirm_overwrite = false;
                    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
                    break;
                case 0:
                    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
                    break;
                case 2:
                    return;
            }
        }
        if (!f.open(QIODevice::WriteOnly)) {
            QApplication::restoreOverrideCursor();
            QMessageBox::critical(
                this, tr("Export Error"),
                tr("Could not write to file: <br><h4>%1</h4><p>"
                   "Please verify that you have the right to write to this location!")
                    .arg(file_name));
            return;
        }
        if (file_suffix.contains(QString::fromLatin1(".eps"))
            || file_suffix.contains(QString::fromLatin1(".pdf"))
            || file_suffix.contains(QString::fromLatin1(".ps"))
            || file_suffix.contains(QString::fromLatin1(".svg"))) {
            if (plot3D)
                plot3D->exportGraphwithoutdialog(file_name, file_suffix,
                                                 plot3D->getContainerSize());
            if (plot2D)
                plot2D->exportGraphwithoutdialog(file_name, file_suffix);
        }
        else {
            QList<QByteArray> list = QImageWriter::supportedImageFormats();
            for (int i = 0; i < static_cast<int>(list.count()); i++) {
                if (file_suffix.contains(QString::fromLatin1(".")
                                         + QString::fromLatin1((list[i]).toLower()))) {
                    if (plot3D)
                        plot3D->exportGraphwithoutdialog(file_name, file_suffix,
                                                         plot3D->getContainerSize());
                    if (plot2D)
                        plot2D->exportGraphwithoutdialog(file_name, file_suffix);
                    ;
                }
            }
        }
    }

    QApplication::restoreOverrideCursor();
}

QString MainAlphaPlot::windowGeometryInfo(MyWidget* w)
{
    QString s = QString::fromLatin1("geometry\t");
    if (w->status() == MyWidget::Maximized) {
        if (w == w->folder()->activeWindow())
            return s + QString::fromLatin1("maximized\tactive\n");
        else
            return s + QString::fromLatin1("maximized\n");
    }

    if (!w->parent())
        s += QString::fromLatin1("0\t0\t500\t400\t");
    else {
        QPoint p = w->pos();// store position
        s += QString::number(p.x()) + QString::fromLatin1("\t");
        s += QString::number(p.y()) + QString::fromLatin1("\t");
        s += QString::number(w->frameGeometry().width()) + QString::fromLatin1("\t");
        s += QString::number(w->frameGeometry().height()) + QString::fromLatin1("\t");
    }

    if (w->status() == MyWidget::Minimized)
        s += QString::fromLatin1("minimized\t");

    bool hide = hidden(w);
    if (w == w->folder()->activeWindow() && !hide)
        s += QString::fromLatin1("active\n");
    else if (hide)
        s += QString::fromLatin1("hidden\n");
    else
        s += QString::fromLatin1("\n");
    return s;
}

void MainAlphaPlot::restoreWindowGeometry(MainAlphaPlot* app, MyWidget* w, const QString s)
{
    w->blockSignals(true);
    QString caption = w->name();
    if (s.contains(QString::fromLatin1("minimized"))) {
        QStringList lst = s.split(QString::fromLatin1("\t"));
        if (lst.count() > 4)
            w->setGeometry(lst[1].toInt(), lst[2].toInt(), lst[3].toInt(), lst[4].toInt());
        w->setStatus(MyWidget::Minimized);
        app->setListViewView(caption, tr("Minimized"));
    }
    else if (s.contains(QString::fromLatin1("maximized"))) {
        w->setStatus(MyWidget::Maximized);
        app->setListViewView(caption, tr("Maximized"));
    }
    else {
        QStringList lst = s.split(QString::fromLatin1("\t"));
        w->setGeometry(lst[1].toInt(), lst[2].toInt(), lst[3].toInt(), lst[4].toInt());
        w->setStatus(MyWidget::Normal);

        if (lst.count() > 5) {
            if (lst[5] == QString::fromLatin1("hidden"))
                app->hideWindow(w);
        }
    }

    if (s.contains(QString::fromLatin1("active"))) {
        Folder* f = w->folder();
        if (f)
            f->setActiveWindow(w);
    }

    w->blockSignals(false);
}

Folder* MainAlphaPlot::projectFolder()
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        return static_cast<FolderTreeWidgetItem*>(plotExplorer->folderView->topLevelItem(0))
            ->folder();
    }
    return nullptr;
}

bool MainAlphaPlot::saveProject()
{
    if (projectname == QString::fromLatin1("untitled")) {
        saveProjectAs();
        return false;
    }

    const QString filename = projectname;
    aprojhandler_->saveproject(filename, projectFolder());

    setWindowTitle(QString::fromLatin1("AlphaPlot - ") + projectname);
    savedProject();
    //ui_->actionUndo->setEnabled(false);
    //ui_->actionRedo->setEnabled(false);

    if (autoSave) {
        if (savingTimerId)
            killTimer(savingTimerId);
        savingTimerId = startTimer(autoSaveTime * 60000);
    }
    else
        savingTimerId = 0;

    QApplication::restoreOverrideCursor();
    return true;
}

void MainAlphaPlot::saveProjectAs()
{
    QString filter = QString(tr("AlphaPlot project %1")).arg(QString::fromLatin1("(*.aproj);;"));
    filter +=
        QString(tr("Compressed AlphaPlot project %1")).arg(QString::fromLatin1("(*.aproj.gz);;"));
    filter += QString(tr("Backup files %1")).arg(QString::fromLatin1("(*.aproj~ *.aproj.gz~);;"));
    filter += QString(tr("All files %1")).arg(QString::fromLatin1("(*.*);;"));

    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Project As"), workingDir, filter,
                                                    &selectedFilter);
    if (!filename.isEmpty()) {
        QFileInfo fi(filename);
        workingDir = fi.absolutePath();
        QString baseName = fi.fileName();
        if (!baseName.endsWith(QString::fromLatin1(".aproj"))
            && !baseName.endsWith(QString::fromLatin1(".aproj.gz"))) {
            filename.append(QString::fromLatin1(".aproj"));
            if (selectedFilter.contains(QString::fromLatin1(".gz")))
                filename.append(QString::fromLatin1(".gz"));
        }
        projectname = filename;

        if (aprojhandler_->saveproject(filename, projectFolder())) {
            recentProjects.removeAll(filename);
            recentProjects.push_front(filename);
            updateRecentProjectsList();

            QFileInfo fi(filename);
            QString baseName = fi.baseName();

             if (!this->plotExplorer)
                this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
            // Python console found?
             if (this->plotExplorer) {
                 FolderTreeWidgetItem* item =
                    static_cast<FolderTreeWidgetItem*>(plotExplorer->folderView->topLevelItem(0));
                item->setText(0, baseName);
                item->folder()->setName(baseName);            
             }
            
        }
        else {
            QMessageBox::critical(this, tr("Export Error"),
                                  tr("Could not write to file: <br><h4> %1 </h4><p>Please verify "
                                     "that you have the right to write to this location!")
                                      .arg(filename));
        }
    }
}

//void MainAlphaPlot::saveNoteAs() {
//    if (!getactiveMyWidget()) return;
//    Note* w = qobject_cast<Note*>(getactiveMyWidget());
//    if (!isActiveSubWindow(w, SubWindowType::NoteSubWindow)) return;
//    w->exportASCII();
//}

void MainAlphaPlot::saveAsTemplate()
{
    if (!getactiveMyWidget())
        return;
    MyWidget* mywidget = qobject_cast<MyWidget*>(getactiveMyWidget());
    if (!mywidget)
        return;

    QString filter;
    if (isActiveSubWindow(mywidget, SubWindowType::MatrixSubWindow))
        filter = tr("AlphaPlot Matrix Template") + QString::fromLatin1(" (*.amt);;");
    else if (isActiveSubWindow(mywidget, SubWindowType::Plot2DSubWindow))
        filter = tr("AlphaPlot2D Graph Template") + QString::fromLatin1(" (*.apt);;");
    else if (isActiveSubWindow(mywidget, SubWindowType::TableSubWindow))
        filter = tr("AlphaPlot Table Template") + QString::fromLatin1(" (*.att);;");
    else if (isActiveSubWindow(mywidget, SubWindowType::Plot3DSubWindow))
        filter = tr("AlphaPlot 3D Surface Template") + QString::fromLatin1(" (*.ast);;");

    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
        this, tr("Save Window As Template"),
        templatesDir + QString::fromLatin1("/") + mywidget->name(), filter, &selectedFilter);
    if (!filename.isEmpty()) {
        QFileInfo fileinfo(filename);
        workingDir = fileinfo.absolutePath();
        QString baseName = fileinfo.fileName();
        if (!baseName.contains(QString::fromLatin1("."))) {
            selectedFilter = selectedFilter.right(5).left(4);
            filename.append(selectedFilter);
        }

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        if (!aprojhandler_->saveTemplate(filename, mywidget)) {
            QMessageBox::critical(this, tr("Export Error"),
                                  tr("Could not write to file: <br><h4> %1 </h4><p>Please verify "
                                     "that you have the right to write to this location!")
                                      .arg(filename));
        }
        QApplication::restoreOverrideCursor();
    }
}

void MainAlphaPlot::renameWindow(QTreeWidgetItem* item, int, const QString& text)
{
    if (!item)
        return;

    MyWidget* w = dynamic_cast<WindowTableWidgetItem*>(item)->window();
    if (!w || text == w->name())
        return;
}

bool MainAlphaPlot::renameWindow(MyWidget* w, const QString& text)
{
    if (!w)
        return false;

    QString name = w->name();
    QString newName = text;
    if (name == newName)
        return false;

    if (newName.isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("Please enter a valid name!"));
        return false;
    }
    else if (!newName.contains(QRegExp(QString::fromLatin1("^[a-zA-Z0-9-]*$")))) {
        QMessageBox::critical(this, tr("Error"),
                              tr("The name you chose is not valid: only letters, "
                                 "digits and hyphen are allowed!")
                                  + QString::fromLatin1("<p>") + tr("Please choose another name!"));
        return false;
    }

    while (alreadyUsedName(newName)) {
        QMessageBox::critical(this, tr("Error"),
                              tr("Name <b>%1</b> already exists!").arg(newName)
                                  + QString::fromLatin1("<p>") + tr("Please choose another name!")
                                  + QString::fromLatin1("<p>")
                                  + tr("Warning: for internal consistency reasons only alphabets "
                                       "numbers and hyphen can be used for naming."));
        return false;
    }

    if (isActiveSubWindow(w, SubWindowType::TableSubWindow)) {
        QStringList labels = qobject_cast<Table*>(w)->colNames();
        if (labels.contains(newName) > 0) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("The table name must be different from the "
                                     "names of its columns!")
                                      + QString::fromLatin1("<p>")
                                      + tr("Please choose another name!"));
            return false;
        }
    }

    w->setName(newName);
    w->setCaptionPolicy(w->captionPolicy());
    renameListViewItem(name, newName);
    return true;
}

// TODO: string list -> Column * list
QStringList MainAlphaPlot::columnsList(AlphaPlot::PlotDesignation plotType)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QStringList columnlist;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (!isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            continue;

        Table* t = qobject_cast<Table*>(subwindow);
        for (int i = 0; i < t->numCols(); i++) {
            if (t->colPlotDesignation(i) == plotType)
                columnlist << QString(t->name()) + QString::fromLatin1("_") + t->colLabel(i);
        }
    }
    return columnlist;
}

QList<QPair<Table*, Column*>> MainAlphaPlot::columnList(AlphaPlot::PlotDesignation plotType)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QList<QPair<Table*, Column*>> list;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (!isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            continue;

        Table* t = qobject_cast<Table*>(subwindow);
        for (int i = 0; i < t->numCols(); i++) {
            if (t->colPlotDesignation(i) == plotType)
                list << QPair<Table*, Column*>(t, t->column(i));
        }
    }
    return list;
}

QList<QPair<Table*, Column*>> MainAlphaPlot::columnList(Folder* folder,
                                                     AlphaPlot::PlotDesignation plotType)
{
    QList<MyWidget*> subwindowlist = folder->windowsList();
    QList<QPair<Table*, Column*>> list;

    Q_FOREACH (MyWidget* subwindow, subwindowlist) {
        if (!isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            continue;

        Table* t = qobject_cast<Table*>(subwindow);
        for (int i = 0; i < t->numCols(); i++) {
            if (t->colPlotDesignation(i) == plotType)
                list << QPair<Table*, Column*>(t, t->column(i));
        }
    }
    return list;
}

QList<QPair<Table*, QPair<Column*, Column*>>> MainAlphaPlot::columnList()
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QList<QPair<Table*, QPair<Column*, Column*>>> columnpairlist;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (!isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            continue;

        QList<Column*> ylist;
        QList<Column*> xlist;
        Table* t = qobject_cast<Table*>(subwindow);
        for (int i = 0; i < t->numCols(); i++) {
            if (t->colPlotDesignation(i) == AlphaPlot::PlotDesignation::Y)
                ylist << t->column(i);
            else if (t->colPlotDesignation(i) == AlphaPlot::PlotDesignation::X)
                xlist << t->column(i);
        }

        Q_FOREACH (Column* xcol, xlist) {
            Q_FOREACH (Column* ycol, ylist) {
                QPair<Table*, QPair<Column*, Column*>> columnpair;
                columnpair.first = t;
                columnpair.second.first = xcol;
                columnpair.second.second = ycol;
                columnpairlist << columnpair;
            }
        }
    }
    return columnpairlist;
}

QList<QPair<Table*, QPair<Column*, Column*>>> MainAlphaPlot::columnList(Folder* folder)
{
    QList<MyWidget*> subwindowlist = folder->windowsList();
    QList<QPair<Table*, QPair<Column*, Column*>>> columnpairlist;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (!isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            continue;

        QList<Column*> ylist;
        QList<Column*> xlist;
        Table* t = qobject_cast<Table*>(subwindow);
        for (int i = 0; i < t->numCols(); i++) {
            if (t->colPlotDesignation(i) == AlphaPlot::PlotDesignation::Y)
                ylist << t->column(i);
            else if (t->colPlotDesignation(i) == AlphaPlot::PlotDesignation::X)
                xlist << t->column(i);
        }

        Q_FOREACH (Column* xcol, xlist) {
            Q_FOREACH (Column* ycol, ylist) {
                QPair<Table*, QPair<Column*, Column*>> columnpair;
                columnpair.first = t;
                columnpair.second.first = xcol;
                columnpair.second.second = ycol;
                columnpairlist << columnpair;
            }
        }
    }
    return columnpairlist;
}

// TODO: string list -> Column * list
QStringList MainAlphaPlot::columnsList()
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QStringList list;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (!isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
            continue;

        Table* t = qobject_cast<Table*>(subwindow);
        for (int i = 0; i < t->numCols(); i++) {
            list << QString(t->name()) + QString::fromLatin1("_") + t->colLabel(i);
        }
    }
    return list;
}

void MainAlphaPlot::showCurvesDialog(QAction* action)
{
    //QAction* action = qobject_cast<QAction*>(sender());
    if (!action)
        return;
    AddPlot2DDialog::Type type;
    if (action == /*ui_->actionAddRemovePloty*/ Application::Instance->commandManager()
                      .getCommandByName("Std_Graph_AddRemove_other_plots_y")
                      ->getAction()
                      ->action())
        type = AddPlot2DDialog::Type::Table_Y;
    else if (action == /*ui_->actionAddRemoveCurve*/ Application::Instance->commandManager()
                           .getCommandByName("Std_Graph_AddRemove_plot_xyxyy")
                           ->getAction()
                           ->action())
        type = AddPlot2DDialog::Type::Table_X_Y;
    else if (action == /*ui_->actionAddRemoveVector*/ Application::Instance->commandManager()
                           .getCommandByName("Std_Graph_AddRemove_other_plots_vector")
                           ->getAction()
                           ->action())
        type = AddPlot2DDialog::Type::Table_X_Y_Y_Y;

    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout elements "
                                "selected/available in this window.</h4>"
                                "<p><h4>Please add/select a layout element and try again!</h4>"));
        return;
    }

    std::unique_ptr<AddPlot2DDialog> addplot2d(
        new AddPlot2DDialog(getMainWindow()->centralWidget(), axisrect, type, currentFolder()->windowsList()));
    addplot2d->setModal(true);
    addplot2d->exec();
}

QList<QMdiSubWindow*>* MainAlphaPlot::tableList()
{
    QList<QMdiSubWindow*>* lst = new QList<QMdiSubWindow*>();
    QList<QMdiSubWindow*> windows = subWindowsList();
    for (int i = 0; i < int(windows.count()); i++) {
        if (isActiveSubWindow(windows.at(i), SubWindowType::TableSubWindow))
            lst->append(windows.at(i));
    }
    return lst;
}

void MainAlphaPlot::showPlotAssociations(int curve)
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow))
        return;

    /*Graph *g = qobject_cast<MultiLayer *>(subwindow)->activeGraph();
     if (!g) return;

     AssociationsDialog *ad =
         new AssociationsDialog(this, Qt::WindowStaysOnTopHint);
     ad->setAttribute(Qt::WA_DeleteOnClose);
     ad->setGraph(g);
     ad->initTablesList(tableList(), curve);
     ad->exec();*/
}

void MainAlphaPlot::showExportASCIIDialog()
{
    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (table) {
        ExportDialog* ed = new ExportDialog(this, Qt::WindowContextHelpButtonHint);
        ed->setAttribute(Qt::WA_DeleteOnClose);
        connect(ed, SIGNAL(exportTable(const QString&, const QString&, bool, bool)), this,
                SLOT(exportASCII(const QString&, const QString&, bool, bool)));
        connect(ed, SIGNAL(exportAllTables(const QString&, bool, bool)), this,
                SLOT(exportAllTables(const QString&, bool, bool)));

        ed->setTableNames(tableWindows());
        ed->setActiveTableName(table->name());
        ed->setColumnSeparator(columnSeparator);
        ed->exec();
    }
}

void MainAlphaPlot::exportAllTables(const QString& sep, bool colNames, bool expSelection)
{
    QString dir =
        QFileDialog::getExistingDirectory(this, tr("Choose a directory to export the tables to"),
                                          workingDir, QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty()) {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        QList<QMdiSubWindow*> subwindowlist = subWindowsList();
        workingDir = dir;

        bool confirmOverwrite = true;
        bool success = true;
        QMdiSubWindow* subwindow;
        Q_FOREACH (subwindow, subwindowlist) {
            if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
                Table* t = qobject_cast<Table*>(subwindow);
                QString fileName =
                    dir + QString::fromLatin1("/") + t->name() + QString::fromLatin1(".txt");
                QFile f(fileName);
                if (f.exists(fileName) && confirmOverwrite) {
                    QApplication::restoreOverrideCursor();
                    switch (
                        QMessageBox::question(this, tr("Overwrite file?"),
                                              tr("A file called: <p><b>%1</b><p>already exists. "
                                                 "Do you want to overwrite it?")
                                                  .arg(fileName),
                                              tr("&Yes"), tr("&All"), tr("&Cancel"), 0, 1)) {
                        case 0:
                            success = t->exportASCII(fileName, sep, colNames, expSelection);
                            break;

                        case 1:
                            confirmOverwrite = false;
                            success = t->exportASCII(fileName, sep, colNames, expSelection);
                            break;

                        case 2:
                            return;
                    }
                }
                else
                    success = t->exportASCII(fileName, sep, colNames, expSelection);

                if (!success)
                    break;
            }
        }
        QApplication::restoreOverrideCursor();
    }
}

void MainAlphaPlot::exportASCII(const QString& tableName, const QString& sep, bool colNames,
                             bool expSelection)
{
    Table* t = table(tableName);
    if (!t)
        return;

    QString selectedFilter;
    QString fname = QFileDialog::getSaveFileName(
        this, tr("Choose a filename to save under"), asciiDirPath,
        QString::fromLatin1("*.txt;;*.csv;;*.dat;;*.DAT"), &selectedFilter);
    if (!fname.isEmpty()) {
        QFileInfo fi(fname);
        QString baseName = fi.fileName();
        if (baseName.contains(QString::fromLatin1(".")) == 0)
            fname.append(selectedFilter.remove(QString::fromLatin1("*")));

        asciiDirPath = fi.absolutePath();

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        t->exportASCII(fname, sep, colNames, expSelection);
        QApplication::restoreOverrideCursor();
    }
}

void MainAlphaPlot::correlate()
{
    /*if (!isActiveSubwindow(SubWindowType::TableSubWindow)) return;

     Table* t = qobject_cast<Table*>(getactiveMyWidget());
     QStringList s = t->selectedColumns();
     if (static_cast<int>(s.count()) != 2) {
         QMessageBox::warning(this, tr("Error"),
             tr("Please select two columns for this operation!"));
         return;
     }

     Correlation* cor = new Correlation(this, t, s[0], s[1]);
     cor->run();
     delete cor;*/
}

void MainAlphaPlot::autoCorrelate()
{
    /*if (!isActiveSubwindow(SubWindowType::TableSubWindow)) return;

     Table* t = qobject_cast<Table*>(getactiveMyWidget());
     QStringList s = t->selectedColumns();
     if (static_cast<int>(s.count()) != 1) {
         QMessageBox::warning(
             this, tr("Error"),
             tr("Please select exactly one columns for this operation!"));
         return;
     }

     Correlation* cor = new Correlation(this, t, s[0], s[0]);
     cor->run();
     delete cor;*/
}

void MainAlphaPlot::convolute()
{
    /*if (!isActiveSubwindow(SubWindowType::TableSubWindow)) return;

     Table* t = qobject_cast<Table*>(getactiveMyWidget());
     QStringList s = t->selectedColumns();
     if (static_cast<int>(s.count()) != 2) {
         QMessageBox::warning(
             this, tr("Error"),
             tr("Please select two columns for this operation:\n the first "
                 "represents the signal and the second the response function!"));
         return;
     }

     Convolution* cv = new Convolution(this, t, s[0], s[1]);
     cv->run();
     delete cv;*/
}

void MainAlphaPlot::deconvolute()
{
    /*if (!isActiveSubwindow(SubWindowType::TableSubWindow)) return;

     Table* t = qobject_cast<Table*>(getactiveMyWidget());
     QStringList s = t->selectedColumns();
     if (static_cast<int>(s.count()) != 2) {
         QMessageBox::warning(
             this, tr("Error"),
             tr("Please select two columns for this operation:\n the first "
                 "represents the signal and the second the response function!"));
         return;
     }

     Deconvolution* dcv = new Deconvolution(this, t, s[0], s[1]);
     dcv->run();
     delete dcv;*/
}

void MainAlphaPlot::showColumnStatistics()
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow)) return;
     Table* t = qobject_cast<Table*>(getactiveMyWidget());

     if (int(t->selectedColumns().count()) > 0) {
         QList<int> targets;
         for (int i = 0; i < t->numCols(); i++)
             if (t->isColumnSelected(i, false)) targets << i;
         newTableStatistics(t, TableStatistics::StatColumn, targets)->showNormal();
     }
     else
         QMessageBox::warning(this, tr("Column selection error"),
             tr("Please select a column first!"));
}

void MainAlphaPlot::showRowStatistics()
{
     if (!isActiveSubwindow(SubWindowType::TableSubWindow)) return;
     Table* t = qobject_cast<Table*>(getactiveMyWidget());

     if (t->numSelectedRows() > 0) {
         QList<int> targets;
         for (int i = 0; i < t->numRows(); i++)
             if (t->isRowSelected(i, false)) targets << i;
         newTableStatistics(t, TableStatistics::StatRow, targets)->showNormal();
     }
     else
         QMessageBox::warning(this, tr("Row selection error"),
             tr("Please select a row first!"));
}

void MainAlphaPlot::plotStackedHistograms()
{
    if (!getactiveMyWidget())
        return;

    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (!table || !validFor2DPlot(table, Graph::Histogram))
        return;

    int from = table->firstSelectedRow();
    int to = table->firstSelectedRow() + table->numSelectedRows() - 1;

    QList<Column*> collist;

    QStringList list = table->selectedColumns();
    Q_FOREACH (QString colname, list)
        collist << table->column(table->colIndex(colname));

    Layout2D* layout = newGraph2D();
    layout->generateHistogram2DPlot(AxisRect2D::BarType::VerticalBars, true, table, collist, from,
                                    to);
}

void MainAlphaPlot::setAutoScale()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout elements "
                                "selected/available in this window.</h4>"
                                "<p><h4>Please add/select a layout element and try again!</h4>"));
        return;
    }

    QList<Axis2D*> axes = axisrect->getAxes2D();
    Q_FOREACH (Axis2D* axis, axes) {
        axis->rescale();
    }
    Q_FOREACH (StatBox2D* statbox, axisrect->getStatBoxVec()) {
        statbox->rescaleaxes_statbox();
        break;
    }
    axisrect->parentPlot()->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
}

void MainAlphaPlot::removePoints()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    layout->setGraphTool(Graph2DCommon::Picker::DataRemove);
}

void MainAlphaPlot::movePoints()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    layout->setGraphTool(Graph2DCommon::Picker::DataMove);
    // ui_->actionDisableGraphTools->setChecked(true);
    // QMessageBox::warning(this, tr("Warning"), tr("<h4>not implimented!</h4>"));
}

void MainAlphaPlot::exportPDF()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)
        && !qobject_cast<Layout2D*>(subwindow)->getCurrentAxisRect()) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layers available in this window.</h4>"));
        return;
    }

    QString fname = QFileDialog::getSaveFileName(this, tr("Choose a filename to save under"),
                                                 workingDir, QString::fromLatin1("*.pdf"));
    if (!fname.isEmpty()) {
        QFileInfo fi(fname);
        QString baseName = fi.fileName();
        if (!baseName.contains(QString::fromLatin1(".")))
            fname.append(QString::fromLatin1(".pdf"));

        workingDir = fi.absolutePath();

        QFile f(fname);
        if (!f.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(
                this, tr("Export Error"),
                tr("Could not write to file: <h4>%1</h4><p>Please verify that you "
                   "have the right to write to this location or that the file is not "
                   "being used by another application!")
                    .arg(fname));
            return;
        }

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        qobject_cast<MyWidget*>(subwindow)->exportPDF(fname);

        QApplication::restoreOverrideCursor();
    }
}

void MainAlphaPlot::print(QMdiSubWindow* subwindow)
{
    if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)
        && qobject_cast<Layout2D*>(subwindow)->getCurrentAxisRect() == nullptr) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layouts available in this window.</h4>"));
        return;
    }

    qobject_cast<MyWidget*>(subwindow)->print();
}

// print active window
void MainAlphaPlot::print()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    print(subwindow);
}

// print window from project explorer
void MainAlphaPlot::printWindow()
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
            WindowTableWidgetItem* it =
            static_cast<WindowTableWidgetItem*>(plotExplorer->listView->currentItem());
        MyWidget* widget = it->window();
        if (!widget)
            return;

        print(qobject_cast<QMdiSubWindow*>(widget));
    
    }
}

void MainAlphaPlot::printAllPlots()
{
    std::unique_ptr<QPrinter> printer = std::unique_ptr<QPrinter>(new QPrinter);
    std::unique_ptr<QPrintPreviewDialog> previewDialog =
        std::unique_ptr<QPrintPreviewDialog>(new QPrintPreviewDialog(printer.get(), this));

    QList<QToolBar*> toolbarlist = previewDialog->findChildren<QToolBar*>();
    if (toolbarlist.count()) {
        auto toolbar = toolbarlist.at(0);
        if (toolbar) {
            if (toolbar->actions().count() == 22) {
                toolbar->setMovable(false);
                toolbar->actions().at(4)->setIcon(
                    IconLoader::load(QString::fromLatin1("zoom-out"), IconLoader::LightDark));
                toolbar->actions().at(5)->setIcon(
                    IconLoader::load(QString::fromLatin1("zoom-in"), IconLoader::LightDark));
                toolbar->actions().at(11)->setIcon(
                    IconLoader::load(QString::fromLatin1("go-previous"), IconLoader::LightDark));
                toolbar->actions().at(13)->setIcon(
                    IconLoader::load(QString::fromLatin1("go-next"), IconLoader::LightDark));
                toolbar->actions().at(21)->setIcon(
                    IconLoader::load(QString::fromLatin1("edit-print"), IconLoader::LightDark));
            }
        }
    }

    connect(previewDialog.get(), &QPrintPreviewDialog::paintRequested, [=](QPrinter* printer) {
        printer->setColorMode(QPrinter::Color);
        std::unique_ptr<QCPPainter> painter = std::unique_ptr<QCPPainter>(new QCPPainter(printer));

        int newpage = false;
        Q_FOREACH (QMdiSubWindow* subwindow, subWindowsList()) {
            if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
                if (newpage) {
                    printer->newPage();
                    newpage = false;
                }
                Layout2D* layout = qobject_cast<Layout2D*>(subwindow);
                int plotWidth = layout->getPlotCanwas()->viewport().width();
                int plotHeight = layout->getPlotCanwas()->viewport().height();

                painter->setMode(QCPPainter::pmVectorized);
                painter->setMode(QCPPainter::pmNoCaching);
                // comment this out if you want cosmetic thin lines (always 1 pixel
                // thick independent of pdf zoom level)
                // painter.setMode(QCPPainter::pmNonCosmetic);
                layout->hideCurrentAxisRectIndicator(true);
                layout->getPlotCanwas()->toPainter(painter.get(), plotWidth, plotHeight);
                layout->hideCurrentAxisRectIndicator(false);
                newpage = true;
            }
        }
    });
    previewDialog->exec();
}

void MainAlphaPlot::fitExponentialGrowth() { fitExponential(-1); }

void MainAlphaPlot::fitFirstOrderExponentialDecay() { fitExponential(1); }

void MainAlphaPlot::fitExponential(int type)
{
    /*if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     AxisRect2D* axisrect =
         qobject_cast<Layout2D*>(getactiveMyWidget())
         ->getCurrentAxisRect();
     if (!axisrect) return;

     ExpDecayDialog* edd = new ExpDecayDialog(type, this);
     edd->setAttribute(Qt::WA_DeleteOnClose);
     edd->setAxisRect(axisrect);
     edd->show();*/
}

void MainAlphaPlot::fitSecondOrderExponentialDecay() { fitExponential(2); }

void MainAlphaPlot::fitThirdOrderExponentialDecay() { fitExponential(3); }

void MainAlphaPlot::showFitDialog()
{
    /* QMdiSubWindow* subwindow = getactiveMyWidget();
     if (!subwindow) return;

     Layout2D* plot = nullptr;
     AxisRect2D* axisrect = nullptr;
     if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
         plot = qobject_cast<Layout2D*>(subwindow);
     }

     if (!plot) return;
     axisrect = plot->getCurrentAxisRect();
     if (!axisrect) return;

     FitDialog* fd = new FitDialog(this);
     fd->setAttribute(Qt::WA_DeleteOnClose);
     connect(fd, SIGNAL(clearFunctionsList()), this,
         SLOT(clearFitFunctionsList()));
     connect(fd, SIGNAL(saveFunctionsList(const QStringList&)), this,
         SLOT(saveFitFunctionsList(const QStringList&)));
     connect(plot, SIGNAL(destroyed()), fd, SLOT(close()));

     fd->addUserFunctions(fitFunctions);
     fd->setAxisRect(axisrect);
     fd->setSrcTables(tableList());
     fd->exec();*/
}

void MainAlphaPlot::showFilterDialog(int filter)
{
    /*if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     AxisRect2D* axisrect =
         qobject_cast<Layout2D*>(getactiveMyWidget())
         ->getCurrentAxisRect();
     if (axisrect) {
         FilterDialog* fd = new FilterDialog(filter, this);
         fd->setAttribute(Qt::WA_DeleteOnClose);
         fd->setAxisRect(axisrect);
         fd->exec();
     }*/
}

void MainAlphaPlot::lowPassFilter()
{
    //showFilterDialog(FFTFilter::LowPass);
}

void MainAlphaPlot::highPassFilter()
{
    //showFilterDialog(FFTFilter::HighPass);
}

void MainAlphaPlot::bandPassFilter()
{
    //showFilterDialog(FFTFilter::BandPass);
}

void MainAlphaPlot::bandBlockFilter()
{
    //showFilterDialog(FFTFilter::BandBlock);
}

void MainAlphaPlot::showFFTDialog()
{
    /*QMdiSubWindow* subwindow = getactiveMyWidget();
     if (!subwindow) return;

     std::unique_ptr<FFTDialog> sd = nullptr;
     if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
         AxisRect2D* axisrect =
             qobject_cast<Layout2D*>(subwindow)->getCurrentAxisRect();
         if (axisrect) {
             sd = std::unique_ptr<FFTDialog>(new FFTDialog(FFTDialog::onGraph, this));
             sd->setAxisrect(axisrect);
         }
     }
     else if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
         sd = std::unique_ptr<FFTDialog>(new FFTDialog(FFTDialog::onTable, this));
         sd->setTable(qobject_cast<Table*>(subwindow));
     }
     if (sd) sd->exec();*/
}

void MainAlphaPlot::showSmoothDialog(int m)
{
    /*if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     AxisRect2D* axisrect =
         qobject_cast<Layout2D*>(getactiveMyWidget())
         ->getCurrentAxisRect();
     if (!axisrect) return;

     SmoothCurveDialog* sd = new SmoothCurveDialog(m, this);
     sd->setAttribute(Qt::WA_DeleteOnClose);
     sd->setAxisRect(axisrect);
     sd->exec();*/
}

void MainAlphaPlot::savitzkySmooth()
{
    //showSmoothDialog(SmoothFilter::SavitzkyGolay);
}

void MainAlphaPlot::fFTFilterSmooth()
{
    //showSmoothDialog(SmoothFilter::FFT);
}

void MainAlphaPlot::movingWindowAverageSmooth()
{
    //showSmoothDialog(SmoothFilter::Average);
}

void MainAlphaPlot::interpolate()
{
    /* if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
     AxisRect2D* axisrect = layout->getCurrentAxisRect();
     if (!axisrect) {
         QMessageBox::warning(
             this, tr("Warning"),
             tr("<h4>There are no plot layout available in this window.</h4>"
                 "<p><h4>Please add a layout and try again!</h4>"));
         ui_->actionDisableGraphTools->setChecked(true);
         return;
     }

     InterpolationDialog* id = new InterpolationDialog(this);
     id->setAttribute(Qt::WA_DeleteOnClose);
     id->setAxisRect(axisrect);
     id->show();*/
}

void MainAlphaPlot::fitPolynomial()
{
    /*if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
     AxisRect2D* axisrect = layout->getCurrentAxisRect();
     if (!axisrect) {
         QMessageBox::warning(
             this, tr("Warning"),
             tr("<h4>There are no plot layout available in this window.</h4>"
                 "<p><h4>Please add a layout and try again!</h4>"));
         ui_->actionDisableGraphTools->setChecked(true);
         return;
     }

     PolynomFitDialog* pfd = new PolynomFitDialog(this);
     pfd->setAttribute(Qt::WA_DeleteOnClose);
     pfd->setAxisRect(axisrect);
     pfd->show();*/
}

void MainAlphaPlot::fitLinear() { analysis(QString::fromLatin1("fitLinear")); }

void MainAlphaPlot::updateLog(const QString& result)
{
    if (!result.isEmpty()) {
        getMainWindow()->setResultLogInfo(result);
        getMainWindow()->showResults(true);
        Q_EMIT modified();
    }
}

void MainAlphaPlot::integrate()
{
    //if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

    //Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    //AxisRect2D* axisrect = layout->getCurrentAxisRect();
    //if (!axisrect) {
    //    QMessageBox::warning(
    //        this, tr("Warning"),
    //        tr("<h4>There are no plot layout available in this window.</h4>"
    //            "<p><h4>Please add a layout and try again!</h4>"));
    //    ui_->actionDisableGraphTools->setChecked(true);
    //    return;
    //}

    //// std::unique_ptr<IntDialog> id =
    ////     std::unique_ptr<IntDialog>(new IntDialog(this));
    //IntDialog* id = new IntDialog(this);
    //id->setAttribute(Qt::WA_DeleteOnClose);
    //id->setAxisrect(axisrect);
    //id->exec();
}

void MainAlphaPlot::fitBoltzmannSigmoid() { analysis(QString::fromLatin1("fitSigmoidal")); }

void MainAlphaPlot::fitGaussian() { analysis(QString::fromLatin1("fitGauss")); }

void MainAlphaPlot::fitLorentzian() { analysis(QString::fromLatin1("fitLorentz")); }

void MainAlphaPlot::differentiate()
{
    /* if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
     AxisRect2D* axisrect = layout->getCurrentAxisRect();
     if (!axisrect) {
         QMessageBox::warning(
             this, tr("Warning"),
             tr("<h4>There are no plot layout available in this window.</h4>"
                 "<p><h4>Please add a layout and try again!</h4>"));
         ui_->actionDisableGraphTools->setChecked(true);
         return;
     }
     analysis(QString::fromLatin1("differentiate"));*/
}

void MainAlphaPlot::showResults(bool ok)
{
    /*if (ok) {
         if (!logInfo.isEmpty()) ui_->resultLog->setText(logInfo);

         ui_->logWindow->show();
         QTextCursor cursor = ui_->resultLog->textCursor();
         cursor.movePosition(QTextCursor::End);
         ui_->resultLog->setTextCursor(cursor);
     }
     else
         ui_->logWindow->hide();*/
}

void MainAlphaPlot::showResults(const QString& text, bool ok)
{
    /*logInfo += text;
     if (!logInfo.isEmpty()) ui_->resultLog->setText(logInfo);
     showResults(ok);*/
}

void MainAlphaPlot::showScreenReader()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    layout->setGraphTool(Graph2DCommon::Picker::DataGraph);
}

void MainAlphaPlot::showRangeSelectors()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        // ui_->actionDisableGraphTools->setChecked(true);
        return;
    }

    QVector<Curve2D*> cvec;
    Q_FOREACH (Curve2D* curve, axisrect->getCurveVec()) {
        if (curve->getplottype_cplot() != Graph2DCommon::PlotType::Function)
            cvec.append(curve);
    }
    if (cvec.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no compatible plots available in this layout "
                                "element.</h4><p><h4>Please add a compatible plot and try "
                                "again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    if (cvec.size() == 1) {
        layout->getPickerTool()->setRangePickerCurve(cvec.at(0));
        layout->setGraphTool(Graph2DCommon::Picker::DataRange);
    }
    else {
        /*QStringList list;
         Q_FOREACH(Curve2D * curve, cvec) {
             list << curve->getdatablock_cplot()->gettable()->name() + QString::fromLatin1("_") +
                 curve->getdatablock_cplot()->getxcolumn()->name() + QString::fromLatin1("_") +
                 curve->getdatablock_cplot()->getycolumn()->name();
         }
         DataSetDialog* ad = new DataSetDialog(tr("Curve") + QString::fromLatin1(" : "), nullptr);
         ad->setAttribute(Qt::WA_DeleteOnClose);
         ad->setWindowTitle(tr("Choose curve"));
         ad->setCurveNames(list);
         connect(ad, &DataSetDialog::options, this, [=](QString text) {
             layout->getPickerTool()->setRangePickerCurve(cvec.at(list.indexOf(text)));
             layout->setGraphTool(Graph2DCommon::Picker::DataRange);
             });
         ad->exec();*/
    }
}

void MainAlphaPlot::showDataReader()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    layout->setGraphTool(Graph2DCommon::Picker::DataPoint);
}

void MainAlphaPlot::dragRange()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    layout->setGraphTool(Graph2DCommon::Picker::DragRange);
}

void MainAlphaPlot::zoomRange()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    layout->setGraphTool(Graph2DCommon::Picker::ZoomRange);
}

void MainAlphaPlot::drawEllipse()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        //ui_->actionDisableGraphTools->setChecked(true);
        return;
    }
    QMessageBox::warning(this, tr("Warning"), tr("<h4>not implimented yet!</h4>"));
}

void MainAlphaPlot::addTimeStamp()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        return;
    }

    QString date = QDateTime::currentDateTime().toString(Qt::LocalDate);
    axisrect->addTextItem2D(date);
}

void MainAlphaPlot::disableAddText()
{
    //ui_->actionAddText->setChecked(false);
}

void MainAlphaPlot::addText()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        return;
    }
    QString text = QString::fromLatin1("Text");
    axisrect->addTextItem2D(text);
    disableAddText();
}

void MainAlphaPlot::addImage()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        return;
    }
    QList<QByteArray> list = QImageReader::supportedImageFormats();
    QString filter = tr("Images") + QString::fromLatin1(" ("), aux1, aux2;
    for (int i = 0; i < list.count(); i++) {
        aux1 = QString::fromLatin1(" *.") + QString::fromLatin1(list[i]) + QString::fromLatin1(" ");
        aux2 +=
            QString::fromLatin1(" *.") + QString::fromLatin1(list[i]) + QString::fromLatin1(";;");
        filter += aux1;
    }
    filter += QString::fromLatin1(");;") + aux2;

    QString filename =
        QFileDialog::getOpenFileName(this, tr("Insert image from file"), imagesDirPath, filter);
    if (!filename.isEmpty()) {
        QFileInfo fi(filename);
        imagesDirPath = fi.absolutePath();

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        layout->getCurrentAxisRect()->addImageItem2D(filename);
        QApplication::restoreOverrideCursor();
    }
}

void MainAlphaPlot::drawLine()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        return;
    }
    axisrect->addLineItem2D();
}

void MainAlphaPlot::drawArrow()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout available in this window.</h4>"
                                "<p><h4>Please add a layout and try again!</h4>"));
        return;
    }
    axisrect->addArrowItem2D();
}

void MainAlphaPlot::showSwapLayoutDialog()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    if (!layout)
        return;

    if (layout->getAxisRectList().count() < 2) {
        QMessageBox::warning(
            this, tr("Warning"),
            tr("There are no more than 2 layout elements available in this Graph2D "
               "window. Swamp needs atleast 2 layout elements!"));
        return;
    }

    std::unique_ptr<SwapLayout2DDialog> swapdlg =
        std::unique_ptr<SwapLayout2DDialog>(new SwapLayout2DDialog(layout));
    swapdlg->setModal(true);
    swapdlg->exec();
}

void MainAlphaPlot::showAddGlyphs()
{
    /* std::unique_ptr<CharacterMapWidget> charmap =
         std::unique_ptr<CharacterMapWidget>(new CharacterMapWidget(nullptr));
     charmap->setModal(false);
     charmap->exec();*/
}

void MainAlphaPlot::addColToTable()
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow))
        return;
    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (table)
        table->addCol();
}

void MainAlphaPlot::clearSelection()
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        if (plotExplorer->listView->hasFocus()) {
            deleteSelectedItems();
            return;
        }
    }

    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
        qobject_cast<Table*>(subwindow)->clearSelection();
    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow))
        qobject_cast<Matrix*>(subwindow)->clearSelection();
    else if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
        // QMessageBox::warning(this, tr("Error"), tr("Cannot use this on
        // Graph2D!")); resizing subwindows unintentionally activate this for some
        // unknown reason issue #19
        qDebug() << "Cannot use this on Graph2D!";
        return;
    }
    /*else if (isActiveSubWindow(subwindow, SubWindowType::NoteSubWindow))
         qobject_cast<Note*>(subwindow)->textWidget()->clear();*/
    Q_EMIT modified();
}

void MainAlphaPlot::copySelection()
{
   /* if (ui_->resultLog->hasFocus()) {
        ui_->resultLog->copy();
        return;
    }*/

    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
        qobject_cast<Table*>(subwindow)->copySelection();
    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow))
        qobject_cast<Matrix*>(subwindow)->copySelection();
    else if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
        // QMessageBox::warning(this, tr("Error"), tr("Cannot use this on
        // Graph2D!")); resizing subwindows unintentionally activate this for some
        // unknown reason issue #19
        qDebug() << "Cannot use this on Graph2D!";
        return;
    }
    /*else if (isActiveSubWindow(subwindow, SubWindowType::NoteSubWindow))
         qobject_cast<Note*>(subwindow)->textWidget()->copy();*/
}

void MainAlphaPlot::cutSelection()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow))
        qobject_cast<Table*>(subwindow)->cutSelection();
    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow))
        qobject_cast<Matrix*>(subwindow)->cutSelection();
    else if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
        // QMessageBox::warning(this, tr("Error"), tr("Cannot use this on
        // Graph2D!")); resizing subwindows unintentionally activate this for some
        // unknown reason issue #19
        qDebug() << "Cannot use this on Graph2D!";
        return;
    }
    //else if (isActiveSubWindow(subwindow, SubWindowType::NoteSubWindow))
    //    qobject_cast<Note*>(subwindow)->textWidget()->cut();

    Q_EMIT modified();
}

void MainAlphaPlot::pasteSelection()
{
    if (!getactiveMyWidget())
        return;
    MyWidget* widget = qobject_cast<MyWidget*>(getactiveMyWidget());
    if (!widget)
        return;

    if (isActiveSubWindow(widget, SubWindowType::TableSubWindow))
        qobject_cast<Table*>(widget)->pasteSelection();
    else if (isActiveSubWindow(widget, SubWindowType::MatrixSubWindow))
        qobject_cast<Matrix*>(widget)->pasteSelection();
    /*else if (isActiveSubWindow(widget, SubWindowType::NoteSubWindow))
         qobject_cast<Note*>(widget)->textWidget()->paste();*/
    else if (isActiveSubWindow(widget, SubWindowType::Plot2DSubWindow)) {
        // QMessageBox::warning(this, tr("Error"), tr("Cannot use this on
        // Graph2D!")); resizing subwindows unintentionally activate this for some
        // unknown reason issue #19
        qDebug() << "Cannot use this on Graph2D!";
        return;
    }

    Q_EMIT modified();
}

MyWidget* MainAlphaPlot::clone()
{
    if (!getactiveMyWidget())
        return nullptr;
    MyWidget* widget = qobject_cast<MyWidget*>(getactiveMyWidget());
    if (!widget) {
        QMessageBox::critical(this, tr("Duplicate window error"),
                              tr("There are no windows available in this project!"));
        return nullptr;
    }

    return clone(widget);
}

MyWidget* MainAlphaPlot::clone(MyWidget* widget)
{
    if (!widget)
        return nullptr;

    MyWidget* newWidget = nullptr;
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    if (isActiveSubWindow(widget, SubWindowType::Plot2DSubWindow)) {
        Layout2D* layout = newGraph2D(qobject_cast<Layout2D*>(widget)->name());
        layout->copy(qobject_cast<Layout2D*>(widget), aprojhandler_->tables(this),
                     aprojhandler_->matrixs(this));
        newWidget = layout;
    }
    else if (isActiveSubWindow(widget, SubWindowType::TableSubWindow)) {
        Table* t = qobject_cast<Table*>(widget);
        QString caption = generateUniqueName(tr("Table"));
        newWidget = newTable(caption, t->numRows(), t->numCols());
        qobject_cast<Table*>(newWidget)->copy(t);
    }
    else if (isActiveSubWindow(widget, SubWindowType::Plot3DSubWindow)) {
        Layout3D* layout = newGraph3D(qobject_cast<Layout3D*>(widget)->getPlotType(),
                                      qobject_cast<Layout3D*>(widget)->name());
        layout->copy(qobject_cast<Layout3D*>(widget), aprojhandler_->tables(this),
                     aprojhandler_->matrixs(this), 0);//koffa
        newWidget = layout;
    }
    else if (isActiveSubWindow(widget, SubWindowType::MatrixSubWindow)) {
        newWidget = newMatrix(qobject_cast<Matrix*>(widget)->numRows(),
                              qobject_cast<Matrix*>(widget)->numCols());
        qobject_cast<Matrix*>(newWidget)->copy(qobject_cast<Matrix*>(widget));
    }
    /* else if (isActiveSubWindow(widget, SubWindowType::NoteSubWindow)) {
         newWidget = newNote();
         if (newWidget)
             qobject_cast<Note*>(newWidget)->setText(
                 qobject_cast<Note*>(widget)->text());
     }*/

    if (newWidget) {
        if (isActiveSubWindow(widget, SubWindowType::Plot2DSubWindow)) {
            if (widget->status() == MyWidget::Maximized)
                newWidget->showMaximized();
        }
        else if (isActiveSubWindow(widget, SubWindowType::Plot3DSubWindow)) {}
        else {
            newWidget->resize(widget->size());
            newWidget->showNormal();
        }

        newWidget->setWindowLabel(widget->windowLabel());
        newWidget->setCaptionPolicy(widget->captionPolicy());
        setListViewLabel(newWidget->name(), widget->windowLabel());
    }
    QApplication::restoreOverrideCursor();
    return newWidget;
}

void MainAlphaPlot::undo()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    d_project->undoStack()->undo();
    QApplication::restoreOverrideCursor();
}

void MainAlphaPlot::redo()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    d_project->undoStack()->redo();
    QApplication::restoreOverrideCursor();
}

bool MainAlphaPlot::hidden(QWidget* window)
{
    if (hiddenWindows->contains(window) || outWindows->contains(window))
        return true;

    return false;
}

void MainAlphaPlot::updateWindowStatus(MyWidget* w)
{
    setListViewView(w->name(), w->aspect());
    if (w->status() == MyWidget::Maximized) {
        QList<MyWidget*> windows = current_folder->windowsList();
        Q_FOREACH (MyWidget* oldMaxWindow, windows) {
            if (oldMaxWindow != w && oldMaxWindow->status() == MyWidget::Maximized)
                oldMaxWindow->setStatus(MyWidget::Normal);
        }
    }
    modifiedProject();
}

void MainAlphaPlot::hideActiveWindow()
{
    MyWidget* w = qobject_cast<MyWidget*>(getactiveMyWidget());
    if (!w)
        return;

    hideWindow(w);
}

void MainAlphaPlot::hideWindow(MyWidget* w)
{
    hiddenWindows->append(w);
    w->setHidden();
    Q_EMIT modified();
}

void MainAlphaPlot::setWindowGeometry(int x, int y, int w, int h)
{
    getactiveMyWidget()->setGeometry(x, y, w, h);
}

void MainAlphaPlot::activateWindow()
{
    if (was_maximized_) {
        setWindowState(Qt::WindowActive | Qt::WindowMaximized);
    }
    else {
        setWindowState(Qt::WindowActive);
    }
    raise();
    show();
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        WindowTableWidgetItem* it =
            static_cast<WindowTableWidgetItem*>(plotExplorer->listView->currentItem());
        if (it)
            activateWindow(it->window());
    }

}

void MainAlphaPlot::activateWindow(MyWidget* w)
{
    if (!w)
        return;
    w->setNormal();
    getMainWindow()->setActiveSubWindow(w);

    updateWindowLists(w);
    Q_EMIT modified();
}

void MainAlphaPlot::maximizeWindow(QTreeWidgetItem* lbi)
{
    if (!lbi || lbi->type() == FolderTreeWidget::Folders)
        return;

    MyWidget* w = dynamic_cast<WindowTableWidgetItem*>(lbi)->window();
    if (!w)
        return;

    w->showMaximized();
    updateWindowLists(w);
    Q_EMIT modified();
}

void MainAlphaPlot::maximizeWindow()
{
    MyWidget* w = qobject_cast<MyWidget*>(getactiveMyWidget());
    if (!w)
        return;

    updateWindowLists(w);
    w->showMaximized();
    Q_EMIT modified();
}

void MainAlphaPlot::minimizeWindow()
{
    MyWidget* w = qobject_cast<MyWidget*>(getactiveMyWidget());
    if (!w)
        return;

    updateWindowLists(w);
    w->showMinimized();
    Q_EMIT modified();
}

void MainAlphaPlot::updateWindowLists(MyWidget* w)
{
    if (!w)
        return;

    if (hiddenWindows->contains(w))
        hiddenWindows->takeAt(hiddenWindows->indexOf(w));
    else if (outWindows->contains(w)) {
        outWindows->takeAt(outWindows->indexOf(w));
        getMainWindow()->addSubWindow(w);
        w->setAttribute(Qt::WA_DeleteOnClose);
    }
}

void MainAlphaPlot::closeActiveWindow()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (subwindow)
        subwindow->close();
}

void MainAlphaPlot::removeWindowFromLists(MyWidget* widgrt)
{
    if (!widgrt)
        return;

    QString caption = widgrt->name();
    if (isActiveSubwindow(SubWindowType::TableSubWindow)) {
        Table* table = qobject_cast<Table*>(widgrt);
        if (!table)
            return;
        for (int i = 0; i < table->numCols(); i++) {
            QString name = table->colName(i);
            removeCurves(table, name);
        }
        if (widgrt == lastModified) {
            /* ui_->actionUndo->setEnabled(false);
             ui_->actionRedo->setEnabled(false);*/
        }
    }

    if (hiddenWindows->contains(widgrt))
        hiddenWindows->takeAt(hiddenWindows->indexOf(widgrt));
    else if (outWindows->contains(widgrt))
        outWindows->takeAt(outWindows->indexOf(widgrt));
}

void MainAlphaPlot::closeWindow(MyWidget* window)
{
    if (!window)
        return;

    removeWindowFromLists(window);
    window->folder()->removeWindow(window);

     if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
     if (this->plotExplorer) {
        // update list view in project explorer
        QList<QTreeWidgetItem*> items =
            plotExplorer->listView->findItems(window->name(), Qt::MatchExactly, 0);
        Q_FOREACH (QTreeWidgetItem* item, items) {
            if (item)
                delete item;
        }
     }

    //// reset picktools after deleting
    //if (isActiveSubwindow(SubWindowType::Plot2DSubWindow))
    //    pickGraphTool(ui_->actionDisableGraphTools);

    (isActiveSubwindow(SubWindowType::MatrixSubWindow)
     || isActiveSubwindow(SubWindowType::TableSubWindow))
        ? window->setParent(nullptr)
        : window->deleteLater();

    QList<QMdiSubWindow*> subwindowlist = getMainWindow()->subWindowList();
    subwindowlist.removeOne(window);
    if (subwindowlist.isEmpty()) {
        customMenu(nullptr);
        customToolBars(nullptr);
        if (!this->plotPropertyeditor)
            this->plotPropertyeditor = getMainWindow()->findChild<PlotPropertyEditor*>();
        // Python console found?
        if (this->plotPropertyeditor) {
            plotPropertyeditor->populateObjectBrowser(nullptr);
        }
    }

    Q_EMIT modified();
}

void MainAlphaPlot::showMarkerPopupMenu() {}

void MainAlphaPlot::showMoreWindows()
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        if (plotExplorer->isVisible())
            QMessageBox::information(this, QString::fromLatin1("AlphaPlot"),
                                     tr("Please use the project explorer to select a window!"));
        else
            plotExplorer->show();
    
    }
}

void MainAlphaPlot::windowsMenuActivated(int id)
{
    QList<QMdiSubWindow*> windowlist = getMainWindow()->subWindowList();
    MyWidget* w = qobject_cast<MyWidget*>(windowlist.at(id));
    if (w) {
        w->showNormal();
        w->setFocus();
        if (hidden(w)) {
            hiddenWindows->takeAt(hiddenWindows->indexOf(w));
            setListViewView(w->name(), tr("Normal"));
        }
    }
}

void MainAlphaPlot::newAproj()
{
    saveSettings();// the recent projects must be saved

    MainAlphaPlot* ed = new MainAlphaPlot(getMainWindow());
    ed->applyUserSettings();
    ed->newTable();

    if (this->isMaximized())
        ed->showMaximized();
    else
        ed->show();
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        ed->plotExplorer->folderView->setCurrentItem(ed->projectFolder()->folderTreeWidgetItem());
    }
    ed->savedProject();

    this->close();
}

void MainAlphaPlot::savedProject()
{
    /* ui_->actionSaveProject->setEnabled(false);
     saved = true;
     d_project->undoStack()->clear();*/
}

void MainAlphaPlot::modifiedProject()
{
    /* ui_->actionSaveProject->setEnabled(true);
     saved = false;*/
}

void MainAlphaPlot::modifiedProject(MyWidget* widget)
{
    /*modifiedProject();

     ui_->actionUndo->setEnabled(true);
     lastModified = widget;*/
}

/*void MainAlphaPlot::timerEvent(QTimerEvent* event) {
     if (event->timerId() == savingTimerId) {
         saveProject();
     }
     else {
         QWidget::timerEvent(event);
     }
 }*/

//void MainAlphaPlot::dropEvent(QDropEvent* event) {
//    if (event->mimeData()->hasUrls()) {
//        QStringList asciiFiles;
//        QList<QUrl> urls = event->mimeData()->urls();

//        Q_FOREACH(QUrl url, urls) {
//            QString fileName = url.toLocalFile();
//            QFileInfo fileInfo(fileName);

//            QString ext = fileInfo.completeSuffix().toLower();

//            if (ext == QString::fromLatin1("aproj") || ext == QString::fromLatin1("aproj~") || ext == QString::fromLatin1("aproj.gz") ||
//                ext == QString::fromLatin1("aproj.gz~")) {
//                openAproj(fileName);
//            }
//            else if (ext == QString::fromLatin1("csv") || ext == QString::fromLatin1("dat") || ext == QString::fromLatin1("txt") || ext == QString::fromLatin1("tsv")) {
//                asciiFiles << fileName;
//            }
//            else if (ext == QString::fromLatin1("bmp") || ext == QString::fromLatin1("bw") || ext == QString::fromLatin1("eps") || ext == QString::fromLatin1("epsf") ||
//                ext == QString::fromLatin1("epsi") || ext == QString::fromLatin1("exr") || ext == QString::fromLatin1("kra") ||
//                ext == QString::fromLatin1("ora") || ext == QString::fromLatin1("pcx") || ext == QString::fromLatin1("psd") || ext == QString::fromLatin1("ras") ||
//                ext == QString::fromLatin1("rgb") || ext == QString::fromLatin1("rgba") || ext == QString::fromLatin1("sgi") ||
//                ext == QString::fromLatin1("tga") || ext == QString::fromLatin1("xcf") || ext == QString::fromLatin1("dds") || ext == QString::fromLatin1("gif") ||
//                ext == QString::fromLatin1("ico") || ext == QString::fromLatin1("jp2") || ext == QString::fromLatin1("jpeg") ||
//                ext == QString::fromLatin1("jpg") || ext == QString::fromLatin1("mng") || ext == QString::fromLatin1("pbm") || ext == QString::fromLatin1("pgm") ||
//                ext == QString::fromLatin1("pic") || ext == QString::fromLatin1("png") || ext == QString::fromLatin1("ppm") || ext == QString::fromLatin1("svg") ||
//                ext == QString::fromLatin1("svgz") || ext == QString::fromLatin1("tif") || ext == QString::fromLatin1("tiff") ||
//                ext == QString::fromLatin1("webp") || ext == QString::fromLatin1("xbm") || ext == QString::fromLatin1("xpm") || ext == QString::fromLatin1("xv")) {
//                loadImage(fileName);
//            }
//        }
//        if (!asciiFiles.isEmpty()) {
//            importASCII(asciiFiles, ImportASCIIDialog::NewTables, columnSeparator,
//                ignoredLines, renameColumns, strip_spaces, simplify_spaces,
//                d_convert_to_numeric, d_ASCII_import_locale);
//        }
//    }
//}

//void MainAlphaPlot::dragEnterEvent(QDragEnterEvent* event) {
//    if (event->source() && event->possibleActions() & Qt::MoveAction) {
//        event->ignore();
//        return;
//    }
//    (event->mimeData()->hasUrls() || event->mimeData()->hasImage())
//        ? event->acceptProposedAction()
//        : event->ignore();
//}

//void MainAlphaPlot::closeEvent(QCloseEvent* event) {
//    saved = false;
//    if (!saved) {
//        switch (QMessageBox::information(
//            this, tr("AlphaPlot"),
//            tr("Save changes to project: <p><b> %1 </b> ?").arg(projectname),
//            tr("Yes"), tr("No"), tr("Cancel"), 0, 2)) {
//        case 0:
//            if (!saveProject()) {
//                event->ignore();
//                break;
//            }
//            saveSettings();  // the recent projects must be saved
//            event->accept();
//            break;

//        case 1:
//        default:
//            saveSettings();  // the recent projects must be saved
//            event->accept();
//            break;

//        case 2:
//            event->ignore();
//            break;
//        }
//    }
//    else {
//        saveSettings();  // the recent projects must be saved
//        event->accept();
//    }
//}

//void MainAlphaPlot::customEvent(QEvent* event) {
//    //if (event->type() == SCRIPTING_CHANGE_EVENT) {
//    //    scriptingChangeEvent(dynamic_cast<ScriptingChangeEvent*>(event));
//    //    // If the event is triggered by setScriptingLang(), the connections are
//    //    // already made (for messages emitted during initialization). However,
//    //    // it's good programming practice not to assume a particular call path for
//    //    // an event; which means that we don't know for sure at this point whether
//    //    // scriptEnv is connected or not.
//    //    scriptEnv->disconnect(this);
//    //    connect(scriptEnv, SIGNAL(error(const QString&, const QString&, int)),
//    //        this, SLOT(scriptError(const QString&, const QString&, int)));
//    //    connect(scriptEnv, SIGNAL(print(const QString&)), this,
//    //        SLOT(scriptPrint(const QString&)));
//    //}
//}

void MainAlphaPlot::deleteSelectedItems()
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {

        // we never allow the user to delete the project folder item
        if (plotExplorer->folderView->hasFocus()
            && plotExplorer->folderView->currentItem() != plotExplorer->folderView->topLevelItem(0)) {
            deleteFolder();
            return;
        }

        QTreeWidgetItem* item;
        QList<QTreeWidgetItem*> lst;
        for (int i = 0; i < plotExplorer->listView->topLevelItemCount(); i++) {
            item = plotExplorer->listView->topLevelItem(i);
            if (item->isSelected())
                lst.append(item);
        }

        plotExplorer->folderView->blockSignals(true);
        Q_FOREACH (item, lst) {
            if (item->type() == FolderTreeWidget::Folders) {
                Folder* f = dynamic_cast<FolderTreeWidgetItem*>(item)->folder();
                if (deleteFolder(f))
                    delete item;
            }
            else
                dynamic_cast<WindowTableWidgetItem*>(item)->window()->close();
        }
        plotExplorer->folderView->blockSignals(false);
    
    }
}

void MainAlphaPlot::showListViewSelectionMenu(const QPoint& p)
{
    QMenu cm(this);
    cm.addAction(tr("&Delete Selection"), this, SLOT(deleteSelectedItems()), Qt::Key_F8);
    cm.exec(p);
}

void MainAlphaPlot::showListViewPopupMenu(const QPoint& p)
{
    QMenu cm(this);
    QMenu window(this);

    window.setTitle(tr("New &Window"));

    auto NewTable = Application::Instance->commandManager().getCommandByName("Std_New_Table");
    auto NewMatrix = Application::Instance->commandManager().getCommandByName("Std_New_Matrix");
    auto NewGraph = Application::Instance->commandManager().getCommandByName("Std_New_Graph");
    auto NewFunctionPlot = Application::Instance->commandManager().getCommandByName("Std_New_2DPlot");
    auto New3DSurfacePlot = Application::Instance->commandManager().getCommandByName("Std_New_3DPlot");

    window.setTitle(tr("New &Window"));

    window.addAction(NewTable->getAction()->action());
    window.addAction(NewMatrix->getAction()->action());
    //window.addAction(actionNewNote->getAction()->action());
    window.addAction(NewGraph->getAction()->action());
    window.addAction(NewFunctionPlot->getAction()->action());
    window.addAction(New3DSurfacePlot->getAction()->action());
    cm.addMenu(&window);

    cm.addAction(IconLoader::load(QString::fromLatin1("folder-explorer"), IconLoader::LightDark),
                 tr("New F&older"), this, SLOT(addFolder()), Qt::Key_F7);
    cm.addSeparator();
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        cm.addAction(tr("Auto &Column Width"), plotExplorer->listView, SLOT(adjustColumns()));
    }
    cm.exec(p);
}

void MainAlphaPlot::showWindowPopupMenu(const QPoint& p)
{
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();

    if (this->plotExplorer) {
        QTreeWidgetItem* it = plotExplorer->listView->itemAt(p);

        if (!it) {
            showListViewPopupMenu(plotExplorer->listView->mapToGlobal(p));
            return;
        }

        QTreeWidgetItem* item;
        int selected = 0;
        for (int i = 0; i < plotExplorer->listView->topLevelItemCount(); i++) {
            item = plotExplorer->listView->topLevelItem(i);
            if (item->isSelected())
                selected++;

            if (selected > 1) {
                showListViewSelectionMenu(plotExplorer->listView->mapToGlobal(p));
                return;
            }
        }

        if (it->type() == FolderTreeWidget::Folders) {
            current_folder = dynamic_cast<FolderTreeWidgetItem*>(it)->folder();
            showFolderPopupMenu(it, plotExplorer->listView->mapToGlobal(p), false);
            return;
        }

        MyWidget* w = dynamic_cast<WindowTableWidgetItem*>(it)->window();
        if (w)
            showWindowMenu(w);
    }
}

void MainAlphaPlot::showTable(const QString& curve)
{
    Table* w = table(curve);
    if (!w)
        return;

    updateWindowLists(w);
    int colIndex = w->colIndex(curve);
    w->deselectAll();
    w->setCellsSelected(0, colIndex, w->d_future_table->rowCount() - 1, colIndex);
    w->showMaximized();
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        QList<QTreeWidgetItem*> items =
            plotExplorer->listView->findItems(w->name(), Qt::MatchExactly, 0);
        Q_FOREACH (QTreeWidgetItem* item, items) {
            if (item)
                item->setText(2, tr("Maximized"));
        }
    }
   
    Q_EMIT modified();
}

QStringList MainAlphaPlot::depending3DPlots(Matrix* m)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QStringList plots;
    /*for (int i = 0; i < static_cast<int>(subwindowlist.count()); i++) {
        MyWidget* w = qobject_cast<MyWidget*>(subwindowlist.at(i));
         if (isActiveSubWindow(w, SubWindowType::Plot3DSubWindow) &&
             qobject_cast<Layout3D *>(w)->getMatrix() == m)
        plots << w->name();
    }*/
    return plots;
}

// TODO: Implement this in an elegant way
QStringList MainAlphaPlot::dependingPlots(const QString& name)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QStringList onPlot, plots;

    for (int i = 0; i < subwindowlist.count(); i++) {
        MyWidget* w = qobject_cast<MyWidget*>(subwindowlist.at(i));
        if (!w)
            continue;
        if (isActiveSubWindow(w, SubWindowType::Plot3DSubWindow)) {
            /*if ((qobject_cast<Graph3D *>(w)->formula())
                     .contains(name, Qt::CaseSensitive) &&
                 plots.contains(w->name()) <= 0)
               plots << w->name();*/
        }
    }
    return plots;
}

void MainAlphaPlot::showWindowContextMenu()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!subwindow)
        return;

    QMenu cm(this);
    cm.setAttribute(Qt::WA_DeleteOnClose);
    QMenu itemsubmenu(&cm);
    QMenu plot3D(this);
    if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow)) {
        Matrix* matrix = qobject_cast<Matrix*>(subwindow);
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-cut"), IconLoader::LightDark),
                     tr("Cu&t"), matrix, SLOT(cutSelection()));
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-copy"), IconLoader::LightDark),
                     tr("&Copy"), matrix, SLOT(copySelection()));
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-paste"), IconLoader::LightDark),
                     tr("&Paste"), matrix, SLOT(pasteSelection()));
        cm.addSeparator();
        cm.addAction(tr("&Insert Row"), matrix, SLOT(insertRow()));
        cm.addAction(tr("&Insert Column"), matrix, SLOT(insertColumn()));
        if (matrix->rowsSelected()) {
            cm.addAction(IconLoader::load(QString::fromLatin1("edit-delete"), IconLoader::General),
                         tr("&Delete Rows"), matrix, SLOT(deleteSelectedRows()));
        }
        else if (matrix->columnsSelected()) {
            cm.addAction(IconLoader::load(QString::fromLatin1("edit-delete"), IconLoader::General),
                         tr("&Delete Columns"), matrix, SLOT(deleteSelectedColumns()));
        }
        cm.addAction(
            IconLoader::load(QString::fromLatin1("edit-delete-selection"), IconLoader::LightDark),
            tr("Clea&r"), matrix, SLOT(clearSelection()));
    }
    else if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
        Layout2D* layout = qobject_cast<Layout2D*>(subwindow);
        cm.addAction(
            IconLoader::load(QString::fromLatin1("edit-recalculate"), IconLoader::LightDark),
            tr("Refresh"), layout, &Layout2D::refresh);
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-select"), IconLoader::LightDark),
                     tr("Disable Tools"), layout, &Layout2D::ResetPicker);
        cm.addSeparator();


        auto cmd1 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_AddRemove_plot_xyxyy");
        auto cmd2 = Application::Instance->commandManager().getCommandByName("Std_Graph_Add_function");
        auto cmd3 = Application::Instance->commandManager().getCommandByName("Std_Graph_Add_error_bars");
        cm.addAction(cmd1->getAction()->action());
        cm.addAction(cmd2->getAction()->action());
        cm.addAction(cmd3->getAction()->action());

        // Add And Remove other Plots
        QMenu* AddAndRemoveOtherPlots = new QMenu(tr("Add/Remove curves"));
        auto AddAndRemoveOtherPlots1 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_AddRemove_other_plots_y");
        auto AddAndRemoveOtherPlots2 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_AddRemove_other_plots_vector");
        AddAndRemoveOtherPlots->addAction(AddAndRemoveOtherPlots1->getAction()->action());
        AddAndRemoveOtherPlots->addAction(AddAndRemoveOtherPlots2->getAction()->action());
        cm.addMenu(AddAndRemoveOtherPlots);

        // Add left axis
        QMenu* AddLeftAxis = new QMenu(tr("Add Left Axis"));
        auto AddLeftAxis1 =
            Application::Instance->commandManager().getCommandByName("Std_AddLeftAxisValue");
        auto AddLeftAxis2 =
            Application::Instance->commandManager().getCommandByName("Std_AddLeftAxisLog");
        auto AddLeftAxis3 =
            Application::Instance->commandManager().getCommandByName("Std_AddLeftAxisPi");
        auto AddLeftAxis4 =
            Application::Instance->commandManager().getCommandByName("Std_AddLeftAxisText");
        auto AddLeftAxis5 =
            Application::Instance->commandManager().getCommandByName("Std_AddLeftAxisTime");
        auto AddLeftAxis6 =
            Application::Instance->commandManager().getCommandByName("Std_AddLeftAxisDateTime");
        AddLeftAxis->addAction(AddLeftAxis1->getAction()->action());
        AddLeftAxis->addAction(AddLeftAxis2->getAction()->action());
        AddLeftAxis->addAction(AddLeftAxis3->getAction()->action());
        AddLeftAxis->addAction(AddLeftAxis4->getAction()->action());
        AddLeftAxis->addAction(AddLeftAxis5->getAction()->action());
        AddLeftAxis->addAction(AddLeftAxis6->getAction()->action());

        // Add Bottom axis
        QMenu* AddBottomAxis = new QMenu(tr("Add Bottom Axis"));
        auto AddBottomAxis1 =
            Application::Instance->commandManager().getCommandByName("Std_AddBottomAxisValue");
        auto AddBottomAxis2 =
            Application::Instance->commandManager().getCommandByName("Std_AddBottomAxisLog");
        auto AddBottomAxis3 =
            Application::Instance->commandManager().getCommandByName("Std_AddBottomAxisPi");
        auto AddBottomAxis4 =
            Application::Instance->commandManager().getCommandByName("Std_AddBottomAxisText");
        auto AddBottomAxis5 =
            Application::Instance->commandManager().getCommandByName("Std_AddBottomAxisTime");
        auto AddBottomAxis6 =
            Application::Instance->commandManager().getCommandByName("Std_AddBottomAxisDateTime");
        AddBottomAxis->addAction(AddBottomAxis1->getAction()->action());
        AddBottomAxis->addAction(AddBottomAxis2->getAction()->action());
        AddBottomAxis->addAction(AddBottomAxis3->getAction()->action());
        AddBottomAxis->addAction(AddBottomAxis4->getAction()->action());
        AddBottomAxis->addAction(AddBottomAxis5->getAction()->action());
        AddBottomAxis->addAction(AddBottomAxis6->getAction()->action());

        // Add right axis
        QMenu* AddRightAxis = new QMenu(tr("Add Right Axis"));
        auto AddRightAxis1 =
            Application::Instance->commandManager().getCommandByName("Std_AddRightAxisValue");
        auto AddRightAxis2 =
            Application::Instance->commandManager().getCommandByName("Std_AddRightAxisLog");
        auto AddRightAxis3 =
            Application::Instance->commandManager().getCommandByName("Std_AddRightAxisPi");
        auto AddRightAxis4 =
            Application::Instance->commandManager().getCommandByName("Std_AddRightAxisText");
        auto AddRightAxis5 =
            Application::Instance->commandManager().getCommandByName("Std_AddRightAxisTime");
        auto AddRightAxis6 =
            Application::Instance->commandManager().getCommandByName("Std_AddRightAxisDateTime");
        AddRightAxis->addAction(AddRightAxis1->getAction()->action());
        AddRightAxis->addAction(AddRightAxis2->getAction()->action());
        AddRightAxis->addAction(AddRightAxis3->getAction()->action());
        AddRightAxis->addAction(AddRightAxis4->getAction()->action());
        AddRightAxis->addAction(AddRightAxis5->getAction()->action());
        AddRightAxis->addAction(AddRightAxis6->getAction()->action());

        // Add top axis
        QMenu* AddTopAxis = new QMenu(tr("Add Top Axis"));
        auto AddTopAxis1 =
            Application::Instance->commandManager().getCommandByName("Std_AddTopAxisValue");
        auto AddTopAxis2 =
            Application::Instance->commandManager().getCommandByName("Std_AddTopAxisLog");
        auto AddTopAxis3 =
            Application::Instance->commandManager().getCommandByName("Std_AddTopAxisPi");
        auto AddTopAxis4 =
            Application::Instance->commandManager().getCommandByName("Std_AddTopAxisText");
        auto AddTopAxis5 =
            Application::Instance->commandManager().getCommandByName("Std_AddTopAxisTime");
        auto AddTopAxis6 =
            Application::Instance->commandManager().getCommandByName("Std_AddTopAxisDateTime");
        AddTopAxis->addAction(AddTopAxis1->getAction()->action());
        AddTopAxis->addAction(AddTopAxis2->getAction()->action());
        AddTopAxis->addAction(AddTopAxis3->getAction()->action());
        AddTopAxis->addAction(AddTopAxis4->getAction()->action());
        AddTopAxis->addAction(AddTopAxis5->getAction()->action());
        AddTopAxis->addAction(AddTopAxis6->getAction()->action());

        // Add axis
        QMenu* AddAxis = new QMenu(tr("Add Axis"));
        AddAxis->addMenu(AddLeftAxis);
        AddAxis->addMenu(AddBottomAxis);
        AddAxis->addMenu(AddRightAxis);
        AddAxis->addMenu(AddTopAxis);


        // Add layout
        QMenu* AddLayout = new QMenu(tr("Add Layout"));
        auto AddLayout1 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_Add_layout_up");
        auto AddLayout2 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_Add_layout_down");
        auto AddLayout3 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_Add_layout_left");
        auto AddLayout4 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_Add_layout_right");
        AddLayout->addAction(AddLayout1->getAction()->action());
        AddLayout->addAction(AddLayout2->getAction()->action());
        AddLayout->addAction(AddLayout3->getAction()->action());
        AddLayout->addAction(AddLayout4->getAction()->action());

        cm.addMenu(AddAxis);

        QMenu* AddItems = new QMenu(tr("Add Items..."));
        auto AddItem1 = Application::Instance->commandManager().getCommandByName("Std_Graph_Add_text");
        auto AddItem2 =
            Application::Instance->commandManager().getCommandByName("Std_Graph_Add_time_stamp");
        auto AddItem3 = Application::Instance->commandManager().getCommandByName("Std_Graph_Add_image");
        auto AddItem4 = Application::Instance->commandManager().getCommandByName("Std_Graph_Draw_line");
        auto AddItem5 = Application::Instance->commandManager().getCommandByName("Std_Graph_Draw_arrow");
        auto AddItem6 = Application::Instance->commandManager().getCommandByName("Std_Graph_Draw_ellipse");
        AddItems->addAction(AddItem1->getAction()->action());
        AddItems->addAction(AddItem2->getAction()->action());
        AddItems->addAction(AddItem3->getAction()->action());
        AddItems->addAction(AddItem4->getAction()->action());
        AddItems->addAction(AddItem5->getAction()->action());
        AddItems->addAction(AddItem6->getAction()->action());

        auto cmd4 = Application::Instance->commandManager().getCommandByName("Std_Graph_Lengend_reorder");
        auto cmd5 = Application::Instance->commandManager().getCommandByName("Std_Graph_Add_nested_layout");
        auto cmd6 = Application::Instance->commandManager().getCommandByName("Std_Graph_Remove_layout");
        auto cmd7 = Application::Instance->commandManager().getCommandByName("Std_Graph_Swap_layouts");

        cm.addAction(cmd4->getAction()->action());
        cm.addMenu(AddItems);
        cm.addAction(cmd5->getAction()->action());
        cm.addAction(cmd6->getAction()->action());
        cm.addAction(cmd7->getAction()->action());

        cm.addMenu(AddLayout);


        // cm.addAction(ui_->actionAddRemoveCurve);
        // cm.addAction(ui_->actionAddFunctionCurve);
        // cm.addAction(ui_->actionAddErrorBars);
        // //cm.addMenu(ui_->menuAddRemoveOtherPlots);
        //// cm.addMenu(ui_->menuAddAxis);
        // cm.addAction(ui_->actionLegendReorder);
        //cm.addSeparator();
        //itemsubmenu.setTitle(tr("Add Items ..."));
        //itemsubmenu.addAction(ui_->actionAddText);
        //itemsubmenu.addAction(ui_->actionAddTimeStamp);
        //itemsubmenu.addAction(ui_->actionAddImage);
        //itemsubmenu.addAction(ui_->actionDrawLine);
        //itemsubmenu.addAction(ui_->actionDrawArrow);
        //itemsubmenu.addAction(ui_->actionDrawEllipse);
        //cm.addMenu(&itemsubmenu);
        ////cm.addMenu(ui_->menuGraph2DAnalysis);
        //cm.addSeparator();
        //cm.addAction(ui_->actionAddNestedLayout);
        ////cm.addMenu(ui_->menuAddLayout);
        //cm.addAction(ui_->actionRemoveLayout);
        //cm.addAction(ui_->actionArrangeLayout);
        cm.addSeparator();
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-copy"), IconLoader::LightDark),
                     tr("Copy as Pixmap"), layout, &Layout2D::copyToClipbord);
        cm.addAction(IconLoader::load(QString::fromLatin1("document-save"), IconLoader::LightDark),
                     tr("Export"), layout, &Layout2D::exportGraph);
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-print"), IconLoader::LightDark),
                     tr("Print"), layout, &Layout2D::print);
    }
    else if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {
        Layout3D* layout = qobject_cast<Layout3D*>(subwindow);
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-copy"), IconLoader::LightDark),
                     tr("Copy as Pixmap"), layout, &Layout3D::copyToClipbord);
        cm.addAction(IconLoader::load(QString::fromLatin1("document-save"), IconLoader::LightDark),
                     tr("Export"), layout, &Layout3D::exportGraph);
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-print"), IconLoader::LightDark),
                     tr("Print"), layout, &Layout3D::print);
    }
    cm.exec(QCursor::pos());
}

void MainAlphaPlot::itemContextMenuRequested(Layout2D* layout, AxisRect2D* axisrect)
{
    layout->axisRectSetFocus(axisrect);
    QMenu cm(this);
    cm.setAttribute(Qt::WA_DeleteOnClose);
    /*QMenu itemsubmenu(&cm);
     cm.addAction(ui_->actionAddRemoveCurve);
     cm.addAction(ui_->actionAddFunctionCurve);
     cm.addAction(ui_->actionAddErrorBars);
     cm.addMenu(ui_->menuAddRemoveOtherPlots);
     cm.addMenu(ui_->menuAddAxis);
     cm.addAction(ui_->actionLegendReorder);
     cm.addSeparator();
     itemsubmenu.setTitle(tr("Add Items ..."));
     itemsubmenu.addAction(ui_->actionAddText);
     itemsubmenu.addAction(ui_->actionAddTimeStamp);
     itemsubmenu.addAction(ui_->actionAddImage);
     itemsubmenu.addAction(ui_->actionDrawLine);
     itemsubmenu.addAction(ui_->actionDrawArrow);
     itemsubmenu.addAction(ui_->actionDrawEllipse);
     cm.addMenu(&itemsubmenu);
     cm.addAction(ui_->actionAddNestedLayout);
     cm.addMenu(ui_->menuAddLayout);
     cm.addAction(ui_->actionRemoveLayout);
     cm.addAction(ui_->actionArrangeLayout);*/
    cm.exec(QCursor::pos());
}

void MainAlphaPlot::showWindowTitleBarMenu()
{
    if (!qobject_cast<MyWidget*>(getactiveMyWidget()))
        return;
    showWindowMenu(qobject_cast<MyWidget*>(getactiveMyWidget()));
}

void MainAlphaPlot::showPlotWizard()
{
    if (tableWindows().count() < 1) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no tables available in this project.</h4>"
                                "<p><h4>Please create a table and try again!</h4>"));
        return;
    }

    auto plotwizard = std::unique_ptr<PlotWizard>(new PlotWizard(this));
    // connect(pw, SIGNAL(plot(const QStringList &)), this,
    //         SLOT(multilayerPlot(const QStringList &)));

    plotwizard->insertTablesList(tableWindows());
    // TODO: string list -> Column * list
    plotwizard->setColumnsList(columnsList());
    plotwizard->changeColumnsList(tableWindows()[0]);
    plotwizard->exec();
}

void MainAlphaPlot::showCurveRangeDialog()
{
    /* if (!isActiveSubwindow(SubWindowType::MultiLayerSubWindow)) return;

      Graph *graph =
          qobject_cast<MultiLayer
      *>(getactiveMyWidget())->activeGraph(); if (!graph) return;

      int curveKey = actionEditCurveRange->data().toInt();
      showCurveRangeDialog(graph, graph->curveIndex(curveKey));*/
}

//CurveRangeDialog* MainAlphaPlot::showCurveRangeDialog(AxisRect2D* axisrect,
//    int curve) {
//    if (!axisrect) return nullptr;

//    CurveRangeDialog* crd = new CurveRangeDialog(this);
//    crd->setAttribute(Qt::WA_DeleteOnClose);
//    // crd->setCurveToModify(g, curve);
//    crd->show();
//    return crd;
//}

Function2DDialog* MainAlphaPlot::functionDialog()
{
    Function2DDialog* fd = new Function2DDialog(getMainWindow()->centralWidget());
    //fd->setAttribute(Qt::WA_DeleteOnClose);
    connect(fd, SIGNAL(clearParamFunctionsList()), this, SLOT(clearParamFunctionsList()));
    connect(fd, SIGNAL(clearPolarFunctionsList()), this, SLOT(clearPolarFunctionsList()));

    fd->insertParamFunctionsList(xFunctions, yFunctions);
    fd->insertPolarFunctionsList(rFunctions, thetaFunctions);
    //fd->show();
    //fd->activateWindow();
   
    if (fd->exec() == QDialog::Accepted) {
        bool result;

        switch (fd->getType()) {
            case 0:

                updateFunctionLists(fd->getType(), fd->getFormulas());

                if (!fd->getAxisrect()) {
                    result =
                        newFunctionPlot(fd->getType(), fd->getFormulas(), QString::fromLatin1("x"),
                                        fd->getRange(), fd->getPoints());
                }
                else {
                    if (fd->getPlottomodify() == -1) {
                        result = addFunctionPlot(fd->getType(), fd->getFormulas(),
                                                 QString::fromLatin1("x"), fd->getRange(),
                                                 fd->getPoints(), fd->getAxisrect());
                    }
                    else {
                        // result = app->editFunctionPlot();
                    }
                }

                Q_EMIT fd->updateFunctionLists(fd->getType(), fd->getFormulas());

                break;

            case 1:
                updateFunctionLists(fd->getType(), fd->getFormulas());

                Q_EMIT fd->updateFunctionLists(fd->getType(), fd->getFormulas());
                if (!fd->getAxisrect()) {
                    result = newFunctionPlot(fd->getType(), fd->getFormulas(), fd->getTheText(),
                                             fd->getRange(), fd->getPoints());
                }
                else {
                    if (fd->getPlottomodify() == -1) {
                        result =
                            addFunctionPlot(fd->getType(), fd->getFormulas(), fd->getTheText(),
                                            fd->getRange(), fd->getPoints(), fd->getAxisrect());
                    }
                    else {
                        // result = app->editFunctionPlot();
                    }
                }
                break;

            case 2:
                // result = acceptPolar();
                break;
        }
    }

    return fd;
}

void MainAlphaPlot::addFunctionCurve()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(subwindow);
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout elements "
                                "selected/available in this window.</h4>"
                                "<p><h4>Please add/select a layout element and try again!</h4>"));
        return;
    }

    std::unique_ptr<Function2DDialog> fd(new Function2DDialog(getMainWindow()->centralWidget()));
    fd->setLayout2DToModify(axisrect, -1);
    fd->setModal(true);
    if (fd->exec() == QDialog::Accepted) 
    {
        bool result;

        switch (fd->getType()) {
            case 0:
                
                updateFunctionLists(fd->getType(), fd->getFormulas());

                if (!fd->getAxisrect()) {
                    result = newFunctionPlot(fd->getType(), fd->getFormulas(), QString::fromLatin1("x"),
                                             fd->getRange(),
                                                  fd->getPoints());
                }
                else {
                    if (fd->getPlottomodify() == -1) {
                        result = addFunctionPlot(fd->getType(), fd->getFormulas(),
                                                 QString::fromLatin1("x"), fd->getRange(),
                                                 fd->getPoints(), fd->getAxisrect());
                    }
                    else {
                        // result = app->editFunctionPlot();
                    }
                }

                Q_EMIT fd->updateFunctionLists(fd->getType(), fd->getFormulas());

                break;

            case 1:
                updateFunctionLists(fd->getType(), fd->getFormulas());

                Q_EMIT fd->updateFunctionLists(fd->getType(), fd->getFormulas());
                if (!fd->getAxisrect()) {
                    result = newFunctionPlot(fd->getType(), fd->getFormulas(),
                                             fd->getTheText(),
                                             fd->getRange(), fd->getPoints());
                }
                else {
                    if (fd->getPlottomodify() == -1) {
                        result = addFunctionPlot(fd->getType(), fd->getFormulas(), fd->getTheText(),
                                            fd->getRange(), fd->getPoints(), fd->getAxisrect());
                    }
                    else {
                        // result = app->editFunctionPlot();
                    }
                }
                break;

            case 2:
                // result = acceptPolar();
                break;
        }
    }
}

void MainAlphaPlot::addGraph2DAxis(QAction* action)
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(subwindow);
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout elements "
                                "selected/available in this window.</h4>"
                                "<p><h4>Please add/select a layout element and try again!</h4>"));
        return;
    }

    //QAction* action = qobject_cast<QAction*>(sender());
    if (!action)
        return;

    if (action
        == Application::Instance->commandManager()
               .getCommandByName("Std_AddLeftAxisValue")
               ->getAction()
               ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::Value);
    else if (action == /*ui_->actionLeftLog*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddLeftAxisLog")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::Log);
    else if (action == /*ui_->actionLeftPi*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddLeftAxisPi")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::Pi);
    else if (action == /*ui_->actionLeftText*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddLeftAxisText")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::Text);
    else if (action == /*ui_->actionLeftTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddLeftAxisTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::Time);
    else if (action == /*ui_->actionLeftDateTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddLeftAxisDateTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::DateTime);
    else if (action == /*ui_->actionBottomValue*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddBottomAxisValue")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Bottom, Axis2D::TickerType::Value);
    else if (action == /*ui_->actionBottomLog*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddBottomAxisLog")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Bottom, Axis2D::TickerType::Log);
    else if (action == /*ui_->actionBottomPi*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddBottomAxisPi")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Left, Axis2D::TickerType::Pi);
    else if (action == /*ui_->actionBottomText*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddBottomAxisText")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Bottom, Axis2D::TickerType::Text);
    else if (action == /*ui_->actionBottomTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddBottomAxisTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Bottom, Axis2D::TickerType::Time);
    else if (action == /*ui_->actionBottomDateTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddBottomAxisDateTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Bottom, Axis2D::TickerType::DateTime);
    else if (action == /*ui_->actionRightValue*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddRightAxisValue")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Right, Axis2D::TickerType::Value);
    else if (action == /*ui_->actionRightLog*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddRightAxisLog")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Right, Axis2D::TickerType::Log);
    else if (action == /*ui_->actionRightPi*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddRightAxisPi")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Right, Axis2D::TickerType::Pi);
    else if (action == /*ui_->actionRightText*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddRightAxisText")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Right, Axis2D::TickerType::Text);
    else if (action == /*ui_->actionRightTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddRightAxisTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Right, Axis2D::TickerType::Time);
    else if (action == /*ui_->actionRightDateTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddRightAxisDateTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Right, Axis2D::TickerType::DateTime);
    else if (action == /*ui_->actionTopValue*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddTopAxisValue")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Top, Axis2D::TickerType::Value);
    else if (action == /*ui_->actionTopLog*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddTopAxisLog")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Top, Axis2D::TickerType::Log);
    else if (action == /*ui_->actionTopPi*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddTopAxisPi")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Top, Axis2D::TickerType::Pi);
    else if (action == /*ui_->actionTopText*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddTopAxisText")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Top, Axis2D::TickerType::Text);
    else if (action == /*ui_->actionTopTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddTopAxisTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Top, Axis2D::TickerType::Time);
    else if (action == /*ui_->actionTopDateTime*/ Application::Instance->commandManager()
                           .getCommandByName("Std_AddTopAxisDateTime")
                           ->getAction()
                           ->action())
        axisrect->addAxis2D(Axis2D::AxisOreantation::Top, Axis2D::TickerType::DateTime);
}

void MainAlphaPlot::legendReorder()
{
    QMdiSubWindow* subwindow = getactiveMyWidget();
    if (!isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow))
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(subwindow);
    AxisRect2D* axisrect = layout->getCurrentAxisRect();
    if (!axisrect) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot layout elements "
                                "selected/available in this window.</h4>"
                                "<p><h4>Please add/select a layout element and try again!</h4>"));
        return;
    }
    std::unique_ptr<ArrangeLegend2D> arlegend(new ArrangeLegend2D(this, axisrect->getLegend()));
    arlegend->exec();
}

void MainAlphaPlot::updateFunctionLists(int type, QStringList& formulas)
{
    int maxListSize = 10;
    if (type == 2) {
        rFunctions.removeAll(formulas[0]);
        rFunctions.push_front(formulas[0]);

        thetaFunctions.removeAll(formulas[1]);
        thetaFunctions.push_front(formulas[1]);

        while (static_cast<int>(rFunctions.size()) > maxListSize)
            rFunctions.pop_back();
        while (static_cast<int>(thetaFunctions.size()) > maxListSize)
            thetaFunctions.pop_back();
    }
    else if (type == 1) {
        xFunctions.removeAll(formulas[0]);
        xFunctions.push_front(formulas[0]);

        yFunctions.removeAll(formulas[1]);
        yFunctions.push_front(formulas[1]);

        while (static_cast<int>(xFunctions.size()) > maxListSize)
            xFunctions.pop_back();
        while (static_cast<int>(yFunctions.size()) > maxListSize)
            yFunctions.pop_back();
    }
}

bool MainAlphaPlot::newFunctionPlot(const int type, const QStringList& formulas, const QString& var,
                                 const QList<double>& ranges, const int points)
{
    Q_ASSERT(ranges.size() == 2);
    switch (type) {
        case 0:
        case 1:
        case 2: {
            QPair<QVector<double>*, QVector<double>*> datapair;
            datapair = generateFunctiondata(type, formulas, var, ranges, points);
            if (!datapair.first && !datapair.second)
                return false;
            Layout2D* layout = newGraph2D();
            PlotData::FunctionData funcdata;
            funcdata.type = type;
            funcdata.functions = formulas;
            funcdata.parameter = var;
            funcdata.from = ranges.at(0);
            funcdata.to = ranges.at(1);
            funcdata.points = points;
            layout->generateFunction2DPlot(datapair.first, datapair.second, funcdata);
            return true;
        }
        default:
            qDebug() << "unknown function type!";
    }
    return false;
}

Curve2D* MainAlphaPlot::addFunctionPlot(const int type, const QStringList& formulas,
                                     const QString& var, const QList<double>& ranges,
                                     const int points, AxisRect2D* axisrect)
{
    Q_ASSERT(ranges.size() == 2);
    Curve2D* curve = nullptr;
    switch (type) {
        case 0:
        case 1:
        case 2: {
            QPair<QVector<double>*, QVector<double>*> datapair;
            datapair = generateFunctiondata(type, formulas, var, ranges, points);
            if (!datapair.first || !datapair.second)
                return curve;

            QString label;
            QString xlabel, ylabel;
            if (formulas.size() == 2) {
                xlabel = formulas.at(0);
                ylabel = formulas.at(1);
            }
            else if (formulas.size() == 1) {
                xlabel = QString::fromLatin1("x");
                ylabel = formulas.at(0);
            }
            label = QString::fromLatin1("f(") + xlabel + QString::fromLatin1("): ")
                + ylabel.split(QString::fromLatin1("\n")).last();
            // func data
            PlotData::FunctionData funcdata;
            funcdata.type = type;
            funcdata.functions = formulas;
            funcdata.parameter = var;
            funcdata.from = ranges.at(0);
            funcdata.to = ranges.at(1);
            funcdata.points = points;
            curve =
                axisrect->addFunction2DPlot(funcdata, datapair.first, datapair.second,
                                            axisrect->getXAxis(0), axisrect->getYAxis(0), label);
            return curve;
        }
        default:
            qDebug() << "unknown function type!";
    }
    return curve;
}

QPair<QVector<double>*, QVector<double>*>
MainAlphaPlot::generateFunctiondata(const int type, const QStringList& formulas, const QString& var,
                                 const QList<double>& ranges, const int points)
{
    QPair<QVector<double>*, QVector<double>*> datapair;
    datapair.first = nullptr;
    datapair.second = nullptr;
    switch (type) {
        case 0: {
            Q_ASSERT(formulas.size() == 1);
            QString name = QString::fromLatin1("normal-function");
            std::unique_ptr<Script> script(scriptEnv->newScript(formulas.at(0), 0, name));
            QObject::connect(script.get(), SIGNAL(error(const QString&, const QString&, int)), this,
                             SLOT(scriptError(const QString&, const QString&, int)));

            QVector<double>* xData = new QVector<double>();
            QVector<double>* yData = new QVector<double>();
            xData->reserve(points);
            yData->reserve(points);

            const double xMin = ranges.at(0), xMax = ranges.at(1);
            const double step = (xMax - xMin) / static_cast<double>(points - 1);
            double x = xMin, y = 0;
            for (int i = 0; i < points; i++, x += step) {
                script->setDouble(x, var.toUtf8().constData());
                QVariant result = script->eval();
                if (result.type() != QVariant::Double) {
                    delete xData;
                    delete yData;
                    xData = nullptr;
                    yData = nullptr;
                    return datapair;
                }
                y = result.toDouble();
                xData->append(x);
                yData->append(y);
            }

            if (xData && yData) {
                datapair.first = xData;
                datapair.second = yData;
                return datapair;
            }
            delete xData;
            delete yData;
            xData = nullptr;
            yData = nullptr;
        } break;
        case 1:
        case 2: {
            Q_ASSERT(formulas.size() == 2);
            QString name = QString::fromLatin1("parametric/polar-function");
            std::unique_ptr<Script> script_x(scriptEnv->newScript(formulas.at(0), 0, name));
            std::unique_ptr<Script> script_y(scriptEnv->newScript(formulas.at(1), 0, name));
            QObject::connect(script_x.get(), SIGNAL(error(const QString&, const QString&, int)),
                             this, SLOT(scriptError(const QString&, const QString&, int)));
            QObject::connect(script_y.get(), SIGNAL(error(const QString&, const QString&, int)),
                             this, SLOT(scriptError(const QString&, const QString&, int)));

            QVector<double>* xData = new QVector<double>();
            QVector<double>* yData = new QVector<double>();
            xData->reserve(points);
            yData->reserve(points);

            const double xMin = ranges.at(0), xMax = ranges.at(1);
            const double step = (xMax - xMin) / static_cast<double>(points - 1);
            double x = xMin;
            for (int i = 0; i < points; i++, x += step) {
                script_x->setDouble(x, var.toUtf8().constData());
                script_y->setDouble(x, var.toUtf8().constData());
                QVariant result_x = script_x->eval();
                QVariant result_y = script_y->eval();
                if (result_x.type() != QVariant::Double || result_y.type() != QVariant::Double) {
                    delete xData;
                    delete yData;
                    xData = nullptr;
                    yData = nullptr;
                    return datapair;
                }
                if (type == 2) {
                    xData->append(result_x.toDouble() * cos(result_y.toDouble()));
                    yData->append(result_x.toDouble() * sin(result_y.toDouble()));
                }
                else {
                    xData->append(result_x.toDouble());
                    yData->append(result_y.toDouble());
                }
            }
            if (xData && yData) {
                datapair.first = xData;
                datapair.second = yData;
                return datapair;
            }
            delete xData;
            delete yData;
            xData = nullptr;
            yData = nullptr;
        } break;
        default:
            qDebug() << "unknown function type!";
    }
    return datapair;
}

QList<QPair<QPair<double, double>, double>>*
MainAlphaPlot::generateFunction3ddata(const Graph3DCommon::Function3DData& funcdata)
{
    QList<QPair<QPair<double, double>, double>>* data =
        new QList<QPair<QPair<double, double>, double>>();
    QString name = QString::fromLatin1("surface3d");
    std::unique_ptr<Script> script(scriptEnv->newScript(funcdata.function, 0, name));
    QObject::connect(script.get(), SIGNAL(error(const QString&, const QString&, int)), this,
                     SLOT(scriptError(const QString&, const QString&, int)));
    const double points = funcdata.xpoints;
    const double xstep = (funcdata.xu - funcdata.xl) / static_cast<double>(points - 1);
    const double ystep = (funcdata.yu - funcdata.yl) / static_cast<double>(points - 1);
    for (int i = 0; i < points; i++) {
        double x = qMin(funcdata.xu, i * xstep + funcdata.xl);
        for (int j = 0; j < points; j++) {
            double y = qMin(funcdata.yu, j * ystep + funcdata.yl);
            script->setDouble(x, QString::fromLatin1("x").toUtf8().constData());
            script->setDouble(y, QString::fromLatin1("y").toUtf8().constData());
            QVariant result = script->eval();
            if (result.type() != QVariant::Double) {
                delete data;
                data = nullptr;
                return data;
            }
            else {
                QPair<QPair<double, double>, double> tuple;
                tuple.first.first = x;
                tuple.first.second = y;
                tuple.second = result.toDouble();
                data->append(tuple);
            }
        }
    }
    return data;
}

void MainAlphaPlot::clearLogInfo()
{
   /* if (!logInfo.isEmpty()) {
        logInfo = QString::fromLatin1("");
        ui_->resultLog->setText(logInfo);
        Q_EMIT modified();
    }*/
}

void MainAlphaPlot::clearParamFunctionsList()
{
    xFunctions.clear();
    yFunctions.clear();
}

void MainAlphaPlot::clearPolarFunctionsList()
{
    rFunctions.clear();
    thetaFunctions.clear();
}

void MainAlphaPlot::clearFitFunctionsList() { fitFunctions.clear(); }

void MainAlphaPlot::saveFitFunctionsList(const QStringList& l) { fitFunctions = l; }

void MainAlphaPlot::clearSurfaceFunctionsList() { surfaceFunc.clear(); }

void MainAlphaPlot::removeAxes3DPlot()
{
    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    // qobject_cast<Graph3D *>(getactiveMyWidget())->setNoAxes();
}

void MainAlphaPlot::pickSelectionType(QAction* action)
{
    if (!action)
        return;

    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    Layout3D* lout = qobject_cast<Layout3D*>(getactiveMyWidget());
    QAbstract3DGraph* graph = nullptr;
    switch (lout->getPlotType()) {
        case Graph3DCommon::Plot3DType::Surface:
            graph = static_cast<QAbstract3DGraph*>(lout->getSurface3DModifier()->getGraph());
            break;
        case Graph3DCommon::Plot3DType::Bar:
            graph = static_cast<QAbstract3DGraph*>(lout->getBar3DModifier()->getGraph());
            break;
        case Graph3DCommon::Plot3DType::Scatter:
            graph = static_cast<QAbstract3DGraph*>(lout->getScatter3DModifier()->getGraph());
            break;
    }

    if (action
        == Application::Instance->commandManager()
               .getCommandByName("Std_PlotPlot3dModecolumnSelect")
               ->getAction()
               ->action()) {
        lout->setCustomInteractions(graph, false);
        graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                | QAbstract3DGraph::SelectionSlice);
    }
    else if (action
             == Application::Instance->commandManager()
                    .getCommandByName("Std_PlotPlot3dModeRowSelect")
                    ->getAction()
                    ->action()) {
        lout->setCustomInteractions(graph, false);
        graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                | QAbstract3DGraph::SelectionSlice);
    }
    else if (action
             == Application::Instance->commandManager()
                    .getCommandByName("Std_PlotPlot3dModeItemSelect")
                    ->getAction()
                    ->action()) {
        lout->setCustomInteractions(graph, false);
        graph->setSelectionMode(QAbstract3DGraph::SelectionItem);
    }
    // else if (action
    //          == Application::Instance->commandManager()
    //                 .getCommandByName("Std_PlotPlot3dModeNoneSelect")
    //                 ->getAction()
    //                 ->action()) {
    //     lout->setCustomInteractions(graph, true);
    //     graph->setSelectionMode(QAbstract3DGraph::SelectionNone);
    // }

    Q_EMIT modified();
}

void MainAlphaPlot::custom3DActions(QMdiSubWindow* subwindow)
{
    if (!isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow))
        return;

    Layout3D* layout = qobject_cast<Layout3D*>(subwindow);
}

void MainAlphaPlot::pixelLineProfile()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    bool ok;
    int res = QInputDialog::getInt(this, tr("Set the number of pixels to average"),
                                   tr("Number of averaged pixels"), 1, 1, 2000, 2, &ok);
    if (!ok)
        return;

    qDebug() << "not implimented";
}

void MainAlphaPlot::intensityTable() {}

Matrix* MainAlphaPlot::importImage(const QString& fileName)
{
    QImage image(fileName);
    if (image.isNull())
        return nullptr;

    Matrix* m = Matrix::fromImage(image);
    if (!m) {
        QMessageBox::information(nullptr, tr("Error importing image"),
                                 tr("Import of image '%1' failed").arg(fileName));
        return nullptr;
    }
    QString caption = generateUniqueName(tr("Matrix"));
    m->setName(caption);
    d_project->addChild(m->d_future_matrix);
    return m;
}

void MainAlphaPlot::addNestedLayout()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    // layout->generateLayoutInset2D();
    QMessageBox::warning(this, tr("Warning"), tr("<h4>not implimented!</h4>"));
}

void MainAlphaPlot::addLayout(const Graph2DCommon::AddLayoutElement& position)
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    layout->addAxisRectWithAxis(position);
}

void MainAlphaPlot::deleteLayout()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    layout->removeAxisRectItem();
}

void MainAlphaPlot::copyActiveLayer()
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;
    qDebug() << "not implimented";
}

void MainAlphaPlot::showDataSetDialog(const QString& whichFit)
{
    /*if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;

     AxisRect2D* axisrect =
         qobject_cast<Layout2D*>(getactiveMyWidget())
         ->getCurrentAxisRect();

     if (!axisrect) return;

     DataSetDialog* ad = new DataSetDialog(tr("Curve") + QString::fromLatin1(": "), this);
     ad->setAttribute(Qt::WA_DeleteOnClose);
     ad->setAxisRect(axisrect);
     ad->setOperationType(whichFit);
     ad->exec();*/
}

void MainAlphaPlot::analyzeCurve(AxisRect2D* axisrect, const QString& whichFit,
                              const QString& curveTitle)
{
    /*if (whichFit == QString::fromLatin1("fitLinear") || whichFit == QString::fromLatin1("fitSigmoidal") ||
         whichFit == QString::fromLatin1("fitGauss") || whichFit == QString::fromLatin1("fitLorentz")) {
         Fit* fitter = nullptr;
         if (whichFit == QString::fromLatin1("fitLinear"))
             fitter = new LinearFit(this, axisrect);
         else if (whichFit == QString::fromLatin1("fitSigmoidal"))
             fitter = new SigmoidalFit(this, axisrect);
         else if (whichFit == QString::fromLatin1("fitGauss"))
             fitter = new GaussFit(this, axisrect);
         else if (whichFit == QString::fromLatin1("fitLorentz"))
             fitter = new LorentzFit(this, axisrect);

         if (fitter->setDataFromCurve(
             PlotColumns::getassociateddatafromstring(axisrect, curveTitle),
             axisrect)) {
             if (whichFit != QString::fromLatin1("fitLinear")) fitter->guessInitialValues();

             fitter->scaleErrors(fit_scale_errors);
             fitter->setOutputPrecision(fit_output_precision);

             if (whichFit == QString::fromLatin1("fitLinear") && d_2_linear_fit_points)
                 fitter->generateFunction(generateUniformFitPoints, 2);
             else
                 fitter->generateFunction(generateUniformFitPoints, fitPoints);
             fitter->fit();
             delete fitter;
         }
     }
     else if (whichFit == QString::fromLatin1("differentiate")) {
         std::unique_ptr<Differentiation> diff(new Differentiation(
             this, axisrect,
             PlotColumns::getassociateddatafromstring(axisrect, curveTitle)));
         diff->run();
     }*/
}

void MainAlphaPlot::analysis(const QString& whichFit)
{
    if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow))
        return;

    AxisRect2D* axisrect =
        qobject_cast<Layout2D*>(getactiveMyWidget())->getCurrentAxisRect();

    if (!axisrect)
        return;

    QStringList lst = PlotColumns::getstringlistfromassociateddata(axisrect);
    if (lst.count() == 0) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("<h4>There are no plot(s) available in this layout.</h4>"
                                "<p><h4>Please add a plot and try again!</h4>"));
    }

    if (lst.count() == 1) {
        QString analyzablecurve = lst.at(0);
        if (!analyzablecurve.isEmpty())
            analyzeCurve(axisrect, whichFit, lst.at(0));
    }
    else
        showDataSetDialog(whichFit);
}

void MainAlphaPlot::pickPointerCursor()
{
    //ui_->actionDisableGraphTools->setChecked(true);
}

void MainAlphaPlot::pickGraphTool(QAction* action)
{
    if (!action)
        return;

    Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());
    if (!layout)
        return;
    auto actionDisableGraphTools = Application::Instance->commandManager()
                                       .getCommandByName("Std_Tools_Disable_tools")
                                       ->getAction()
                                       ->action();
    auto actionGraphDataReader = Application::Instance->commandManager()
                                     .getCommandByName("Std_Tools_Data_reader")
                                     ->getAction()
                                     ->action();
    auto actionGraphSelectDataRange = Application::Instance->commandManager()
                                          .getCommandByName("Std_Tools_Select_data_range")
                                          ->getAction()
                                          ->action();
    auto actionGraphDragRange = Application::Instance->commandManager()
                                    .getCommandByName("Std_Graph_Drag_range")
                                    ->getAction()
                                    ->action();
    auto actionGraphZoomRange = Application::Instance->commandManager()
                                    .getCommandByName("Std_Tools_Zoom_range")
                                    ->getAction()
                                    ->action();
    auto actionGraphScreenReader = Application::Instance->commandManager()
                                       .getCommandByName("Std_Tools_Screen_reader")
                                       ->getAction()
                                       ->action();
    auto actionGraphMoveDataPoints = Application::Instance->commandManager()
                                         .getCommandByName("Std_Tools_Move_data_points")
                                         ->getAction()
                                         ->action();
    auto actionGraphRemoveBadDataPoints = Application::Instance->commandManager()
                                              .getCommandByName("Std_Tools_Remove_bad_data_points")
                                              ->getAction()
                                              ->action();
    auto actionDrawArrow = Application::Instance->commandManager()
                               .getCommandByName("Std_Graph_Draw_arrow")
                               ->getAction()
                               ->action();
    auto actionDrawLine = Application::Instance->commandManager()
                              .getCommandByName("Std_Graph_Draw_line")
                              ->getAction()
                              ->action();


    if (action == actionDisableGraphTools) {
        actionDisableGraphTools->setChecked(true);
        layout->setGraphTool(Graph2DCommon::Picker::None);
    }
    else if (action == actionGraphDataReader) {
        actionGraphDataReader->setChecked(true);
        showDataReader();
    }
    else if (action == actionGraphSelectDataRange) {
        actionGraphSelectDataRange->setChecked(true);
        showRangeSelectors();
    }
    else if (action == actionGraphDragRange) {
        actionGraphDragRange->setChecked(true);
        dragRange();
    }
    else if (action == actionGraphZoomRange) {
        actionGraphZoomRange->setChecked(true);
        zoomRange();
    }
    else if (action == actionGraphScreenReader) {
        actionGraphScreenReader->setChecked(true);
        showScreenReader();
    }
    else if (action == actionGraphMoveDataPoints) {
        actionGraphMoveDataPoints->setChecked(true);
        movePoints();
    }
    else if (action == actionGraphRemoveBadDataPoints) {
        actionGraphRemoveBadDataPoints->setChecked(true);
        removePoints();
    }
    else if (action == actionDrawArrow)
        drawArrow();
    else if (action == actionDrawLine)
        drawLine();
}

void MainAlphaPlot::connectTable(Table* table)
{
    connect(table, SIGNAL(showTitleBarMenu()), this, SLOT(showWindowTitleBarMenu()));
    connect(table, SIGNAL(statusChanged(MyWidget*)), this, SLOT(updateWindowStatus(MyWidget*)));
    connect(table, SIGNAL(hiddenWindow(MyWidget*)), this, SLOT(hideWindow(MyWidget*)));
    connect(table, SIGNAL(closedWindow(MyWidget*)), this, SLOT(closeWindow(MyWidget*)));
    connect(table, SIGNAL(aboutToRemoveCol(Table*, const QString&)), this,
            SLOT(removeCurves(Table*, const QString&)));
    connect(table, SIGNAL(modifiedData(Table*, const QString&)), this,
            SLOT(updateCurves(Table*, const QString&)));
    connect(table, SIGNAL(modifiedWindow(MyWidget*)), this, SLOT(modifiedProject(MyWidget*)));
    connect(table->d_future_table, SIGNAL(requestRowStatistics()), this, SLOT(showRowStatistics()));
    connect(table->d_future_table, SIGNAL(requestColumnStatistics()), this,
            SLOT(showColumnStatistics()));
    connect(table, &Table::mousepressevent, [=](MyWidget* widget) {
        if (getactiveMyWidget() == widget)
            return;
        widget->setNormal();
        getMainWindow()->setActiveSubWindow(widget);
    });
    table->askOnCloseEvent(confirmCloseTable);
}

void MainAlphaPlot::setAppColors()
{
    //// comment out setting color for now
    //if (appCustomColor) {
    //    QPalette pale = qApp->palette();
    //    pale.setColor(QPalette::Base, panelsColor);
    //    // pal.setColor(QPalette::Window, panelsColor);
    //    pale.setColor(QPalette::Button, panelsColor);
    //    pale.setColor(QPalette::ToolTipBase, panelsColor);
    //    qApp->setPalette(pale);
    //    QPalette palet = qApp->palette();
    //    palet.setColor(QPalette::Text, panelsTextColor);
    //    palet.setColor(QPalette::WindowText, panelsTextColor);
    //    palet.setColor(QPalette::Foreground, panelsTextColor);
    //    palet.setColor(QPalette::ToolTipText, panelsTextColor);
    //    palet.setColor(QPalette::PlaceholderText, panelsTextColor);
    //    palet.setColor(QPalette::ButtonText, panelsTextColor);
    //    palet.setColor(QPalette::BrightText, panelsTextColor);
    //    qApp->setPalette(palet);
    //    QPalette pal = d->mdiArea->palette();
    //    d->mdiArea->setBackground(QBrush(workspaceColor));
    //}
    //else {
    //    qApp->setStyle(appStyle);
    //    qApp->setStyleSheet(styleSheet());
    //    setStyleSheet(styleSheet());
    //    changeAppColorScheme(appColorScheme);
    //}
}

Layout3D* MainAlphaPlot::plot3DMatrix(const Graph3DCommon::Plot3DType& plottype)
{
    if (!isActiveSubwindow(SubWindowType::MatrixSubWindow))
        return nullptr;

    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString label = generateUniqueName(tr("Graph"));

    Layout3D* layout = newGraph3D(plottype, label);
    switch (plottype) {
        case Graph3DCommon::Plot3DType::Surface:
            layout->getSurface3DModifier()->setmatrixdatamodel(matrix);
            break;
        case Graph3DCommon::Plot3DType::Bar:
            layout->getBar3DModifier()->setmatrixdatamodel(matrix);
            break;
        case Graph3DCommon::Plot3DType::Scatter:
            layout->getScatter3DModifier()->setmatrixdatamodel(matrix);
            break;
    }

    Q_EMIT modified();
    QApplication::restoreOverrideCursor();
    return layout;
}

Layout2D* MainAlphaPlot::plotGrayScale()
{
    if (!isActiveSubwindow(SubWindowType::MatrixSubWindow))
        return nullptr;
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    Layout2D* layout = newGraph2D();
    if (matrix)
        layout->generateColorMap2DPlot(matrix, true, false);
    Q_EMIT modified();
    QApplication::restoreOverrideCursor();
    return layout;
}

Layout2D* MainAlphaPlot::plotContour()
{
    if (!isActiveSubwindow(SubWindowType::MatrixSubWindow))
        return nullptr;
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    Layout2D* layout = newGraph2D();
    if (matrix)
        layout->generateColorMap2DPlot(matrix, false, true);
    Q_EMIT modified();
    QApplication::restoreOverrideCursor();
    return layout;
}

Layout2D* MainAlphaPlot::plotColorMap()
{
    if (!isActiveSubwindow(SubWindowType::MatrixSubWindow))
        return nullptr;
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
    Layout2D* layout = newGraph2D();
    if (matrix)
        layout->generateColorMap2DPlot(matrix, false, false);
    Q_EMIT modified();
    QApplication::restoreOverrideCursor();
    return layout;
}

void MainAlphaPlot::deleteFitTables()
{
    /*QList<QMdiSubWindow *> *mLst = new QList<QMdiSubWindow *>();
     QList<QMdiSubWindow *> subwindowlist = subWindowsList();
     for (int i = 0; i < subwindowlist.count(); i++) {
       if (isActiveSubWindow(subwindowlist.at(i),
                             SubWindowType::MultiLayerSubWindow))
         mLst->append(subwindowlist.at(i));
     }

     Q_FOREACH (QMdiSubWindow *ml, *mLst) {
       if (isActiveSubWindow(ml, SubWindowType::MultiLayerSubWindow)) {
         QWidgetList lst = qobject_cast<MultiLayer *>(ml)->graphPtrs();
         Q_FOREACH (QWidget *widget, lst) {
           QList<QwtPlotCurve *> curves =
               qobject_cast<Graph *>(widget)->fitCurvesList();
           Q_FOREACH (QwtPlotCurve *c, curves) {
             if (dynamic_cast<PlotCurve *>(c)->type() != Graph::Function) {
               Table *t = dynamic_cast<DataCurve *>(c)->table();
               if (!t) continue;

               t->askOnCloseEvent(false);
               t->close();
             }
           }
         }
       }
     }
     delete mLst;*/
}

QList<QMdiSubWindow*> MainAlphaPlot::subWindowsList()
{
    /*QList<QMdiSubWindow *> subwindowlist;
     return subWindowsListFromTreeRecursive(
         subwindowlist, projectFolder()->folderTreeWidgetItem());*/
    return getMainWindow()->subWindowList();
}

QList<QMdiSubWindow*> MainAlphaPlot::subWindowsListFromTreeRecursive(QList<QMdiSubWindow*> list,
                                                                  FolderTreeWidgetItem* item)
{
    QList<MyWidget*> folderWindows = item->folder()->windowsList();
    Q_FOREACH (MyWidget* widget, folderWindows)
        list.append(widget);

    for (int i = 0; i < item->childCount(); ++i)
        subWindowsListFromTreeRecursive(list, static_cast<FolderTreeWidgetItem*>(item->child(i)));

    return list;
}

void MainAlphaPlot::updateRecentProjectsList()
{
    /*if (recentProjects.isEmpty()) return;

     while (static_cast<int>(recentProjects.size()) > MaxRecentProjects)
         recentProjects.pop_back();

     Q_FOREACH(QAction * action, ui_->menuRecentProjects->actions())
         action->deleteLater();

     for (int i = 0; i < static_cast<int>(recentProjects.size()); i++)
         connect(ui_->menuRecentProjects->addAction(QString::fromLatin1("&") + QString::number(i + 1) +
             QString::fromLatin1(" ") + recentProjects[i]),
             SIGNAL(triggered()), this, SLOT(openRecentAproj()));*/
}

void MainAlphaPlot::horizontalTranslate()
{
    /*QMdiSubWindow *subwindow = getactiveMyWidget();
     if (!isActiveSubWindow(subwindow, SubWindowType::MultiLayerSubWindow)) return;

     MultiLayer *plot = qobject_cast<MultiLayer *>(subwindow);
     if (plot->isEmpty()) {
       QMessageBox::warning(
           this, tr("Warning"),
           tr("<h4>There are no plot layers available in this window.</h4>"
              "<p><h4>Please add a layer and try again!</h4>"));
       ui_->actionDisableGraphTools->setChecked(true);
       return;
     }

     Graph *graph = qobject_cast<Graph *>(plot->activeGraph());
     if (!graph) return;

     if (graph->isPiePlot()) {
       QMessageBox::warning(
           this, tr("Warning"),
           tr("This functionality is not available for pie plots!"));
       ui_->actionDisableGraphTools->setChecked(true);
       return;
     } else if (graph->validCurvesDataSize()) {
       ui_->actionDisableGraphTools->setChecked(true);
       graph->setActiveTool(
           new TranslateCurveTool(graph, this, TranslateCurveTool::Horizontal,
                                  statusBarInfo, SLOT(setText(const QString &))));
     }*/
}

void MainAlphaPlot::verticalTranslate()
{
    /*QMdiSubWindow *subwindow = getactiveMyWidget();
     if (!isActiveSubWindow(subwindow, SubWindowType::MultiLayerSubWindow)) return;

     MultiLayer *plot = qobject_cast<MultiLayer *>(subwindow);
     if (plot->isEmpty()) {
       QMessageBox::warning(
           this, tr("Warning"),
           tr("<h4>There are no plot layers available in this window.</h4>"
              "<p><h4>Please add a layer and try again!</h4>"));
       ui_->actionDisableGraphTools->setChecked(true);
       return;
     }

     Graph *graph = qobject_cast<Graph *>(plot->activeGraph());
     if (!graph) return;

     if (graph->isPiePlot()) {
       QMessageBox::warning(
           this, tr("Warning"),
           tr("This functionality is not available for pie plots!"));

       ui_->actionDisableGraphTools->setChecked(true);
       return;
     } else if (graph->validCurvesDataSize()) {
       ui_->actionDisableGraphTools->setChecked(true);
       graph->setActiveTool(
           new TranslateCurveTool(graph, this, TranslateCurveTool::Vertical,
                                  statusBarInfo, SLOT(setText(const QString &))));
     }*/
}

void MainAlphaPlot::updateGeneralApplicationOptions()
{
    QSettings settings;
    settings.beginGroup(QString::fromLatin1("General"));
    settings.beginGroup(QString::fromLatin1("GlowIndicator"));
    bool nglowstatus = settings.value(QString::fromLatin1("Show"), false).toBool();
    QColor nglowcolor =
        settings.value(QString::fromLatin1("Color"), QString::fromLatin1("red")).value<QColor>();
    double nglowradius = settings.value(QString::fromLatin1("Radius"), 8).toDouble();
    settings.endGroup();
    QString napplanguage =
        settings
            .value(QString::fromLatin1("Language"),
                   QLocale::system().name().section(QChar::fromLatin1('_'), 0, 0))
            .toString();
    QString ndefaultscriptinglang =
        settings.value(QString::fromLatin1("ScriptingLang"), QString::fromLatin1("muParser"))
            .toString();
    bool nautosave = settings.value(QString::fromLatin1("AutoSave"), true).toBool();
    int nautosavetime = settings.value(QString::fromLatin1("AutoSaveTime"), 15).toInt();
    int nundolimit = settings.value(QString::fromLatin1("UndoLimit"), 10).toInt();
    QStringList applicationFont = settings.value(QString::fromLatin1("Font")).toStringList();
    if (applicationFont.size() == 4)
        QFont napplicationfont_ =
            QFont(applicationFont.at(0), applicationFont.at(1).toInt(),
                  applicationFont.at(2).toInt(), applicationFont.at(3).toInt());
#ifdef SEARCH_FOR_UPDATES
    bool nautosearchupdates_ =
        settings.value(QString::fromLatin1("AutoSearchUpdates"), false).toBool();
    autoSearchUpdates = nautosearchupdates_;
#endif
    settings.endGroup();
    glowcolor_ = nglowcolor;
    glowradius_ = nglowradius;
    if (nglowstatus != glowstatus_) {
        glowstatus_ = nglowstatus;
        windowActivated(getactiveMyWidget());
    }

    setSaveSettings(nautosave, nautosavetime);
    if (undoLimit != nundolimit) {
        undoLimit = nundolimit;
        d_project->undoStack()->setUndoLimit(undoLimit);
    }
    QFont applicationfontfont = QFont(applicationFont.at(0), applicationFont.at(1).toInt(),
                                      applicationFont.at(2).toInt(), applicationFont.at(3).toInt());
    if (applicationfontfont.family() != appFont.family()
        || applicationfontfont.pointSize() != appFont.pointSize()
        || applicationfontfont.weight() != appFont.weight()
        || applicationfontfont.italic() != appFont.italic()) {
        changeAppFont(applicationfontfont);
    }
}

void MainAlphaPlot::fitMultiPeakGaussian()
{
    //fitMultiPeak(static_cast<int>(MultiPeakFit::Gauss));
}

void MainAlphaPlot::fitMultiPeakLorentzian()
{
    //fitMultiPeak(static_cast<int>(MultiPeakFit::Lorentz));
}

void MainAlphaPlot::fitMultiPeak(int profile)
{
    /*if (!isActiveSubwindow(SubWindowType::Plot2DSubWindow)) return;
     Layout2D* layout = qobject_cast<Layout2D*>(getactiveMyWidget());

     if (layout->getAxisRectList().size() == 0) {
         QMessageBox::warning(
             this, tr("Warning"),
             tr("<h4>There are no plot layouts available in this window.</h4>"
                 "<p><h4>Please add a layout and try again!</h4>"));
         ui_->actionDisableGraphTools->setChecked(true);
         return;
     }

     AxisRect2D* axisrect = layout->getCurrentAxisRect();
     QVector<LineSpecial2D*> lsvec = axisrect->getLsVec();
     QVector<Curve2D*> curvevec = axisrect->getCurveVec();
     if (lsvec.size() + curvevec.size() == 0) {
         QMessageBox::warning(
             this, tr("Warning"),
             tr("<h4>There are no compatible plots available in this layout.</h4>"
                 "<p><h4>Please add Line Special or Line Scatter plot to the layout "
                 "and try again!</h4>"));
         ui_->actionDisableGraphTools->setChecked(true);
         return;
     }

     bool ok;
     int peaks = QInputDialog::getInt(this, tr("Enter the number of peaks"),
         tr("Peaks"), 2, 2, 1000000, 1, &ok);

     if (ok && peaks) {
         multiPeakfitactive_ = true;
         multiPeakfitpoints_ = peaks;
         multiPeakfittype_ = profile;
         pickGraphTool(ui_->actionGraphDataReader);
     }*/
}

void MainAlphaPlot::multipeakfitappendpoints(Curve2D* curve, double x, double y)
{
    /* if (!multiPeakfitactive_ || multiPeakfitpoints_ == 0) return;

     QPair<Curve2D*, QPair<double, double>> newpair;
     QString pointstext;
     newpair.first = curve;
     newpair.second.first = x;
     newpair.second.second = y;
     if (multipeakfitvalues_.size() == 0) {
         multipeakfitvalues_ << newpair;
         ui_->statusBar->showMessage(
             QString::fromLatin1("Selected Points << x=%1, y=%2").arg(x).arg(y));
         QMessageBox::information(
             this, tr("Multi Peakfit"),
             tr("Data point selected") + QString::fromLatin1(" x=%1, y=%2. ").arg(x).arg(y) +
             tr("Data point") + QString::fromLatin1(" %1 ").arg(multipeakfitvalues_.size()) +
             tr("out of") + QString::fromLatin1(" %1 ").arg(multiPeakfitpoints_));
     }
     else {
         if (multipeakfitvalues_.last().first == curve) {
             bool duplicate = false;
             Q_FOREACH(auto p, multipeakfitvalues_) {
                 if (p.second.first == x && p.second.second == y) duplicate = true;
             }
             if (duplicate) {
                 pickGraphTool(ui_->actionDisableGraphTools);
                 multipeakfitvalues_.erase(multipeakfitvalues_.begin(),
                     multipeakfitvalues_.end());
                 multiPeakfitactive_ = false;
                 multiPeakfitpoints_ = 0;
                 ui_->statusBar->clearMessage();
                 QMessageBox::warning(
                     this, tr("Error"),
                     tr("Same data points selected twice! "
                         "Please select different data points from the plot."
                         "Aborting Multipeakfit!"));
                 return;
             }
             multipeakfitvalues_ << newpair;
             ui_->statusBar->showMessage(ui_->statusBar->currentMessage() +
                 QString::fromLatin1(" << x=%1, y=%2").arg(x).arg(y));
             QMessageBox::information(
                 this, tr("Multi Peakfit"),
                 tr("Data point selected") + QString::fromLatin1(" x=%1, y=%2. ").arg(x).arg(y) +
                 tr("Data point") +
                 QString::fromLatin1(" %1 ").arg(multipeakfitvalues_.size()) + tr("out of") +
                 QString::fromLatin1(" %1 ").arg(multiPeakfitpoints_));
         }
         else {
             pickGraphTool(ui_->actionDisableGraphTools);
             multipeakfitvalues_.erase(multipeakfitvalues_.begin(),
                 multipeakfitvalues_.end());
             multiPeakfitactive_ = false;
             multiPeakfitpoints_ = 0;
             ui_->statusBar->clearMessage();
             QMessageBox::warning(this, tr("Error"),
                 tr("Data Points from different plots selected. "
                     "Please select data points from the same plot."
                     "Aborting Multipeakfit!"));
             return;
         }
     }

     if (multipeakfitvalues_.size() == multiPeakfitpoints_) {
         AxisRect2D* axisrect =
             multipeakfitvalues_.first().first->getxaxis()->getaxisrect_axis();
         std::unique_ptr<MultiPeakFit> d_fit(new MultiPeakFit(
             this, axisrect, MultiPeakFit::PeakProfile::Gauss, multiPeakfitpoints_));
         d_fit->enablePeakCurves(generatePeakCurves);
         d_fit->setPeakCurvesColor(peakCurvesColor);
         d_fit->generateFunction(generateUniformFitPoints, fitPoints);
         d_fit->setDataFromCurve(curve->getdatablock_cplot()->getassociateddata());
         for (int i = 0; i < multipeakfitvalues_.size(); i++) {
             d_fit->setInitialGuess(3 * i, multipeakfitvalues_.at(i).second.second);
             d_fit->setInitialGuess(3 * i + 1, multipeakfitvalues_.at(i).second.first);
         }
         d_fit->fit();
         multipeakfitvalues_.erase(multipeakfitvalues_.begin(),
             multipeakfitvalues_.end());
         multiPeakfitactive_ = false;
         multiPeakfitpoints_ = 0;
         pickGraphTool(ui_->actionDisableGraphTools);
         ui_->statusBar->clearMessage();
     }*/
}

#ifdef DOWNLOAD_LINKS
void MainAlphaPlot::downloadManual() { QDesktopServices::openUrl(QUrl(AlphaPlot::manual_Uri)); }
#endif// defined DOWNLOAD_LINKS

void MainAlphaPlot::showHomePage()
{
    QDesktopServices::openUrl(QUrl(QString::fromLatin1(AlphaPlot::homepage_Uri)));
}

void MainAlphaPlot::showForums()
{
    QDesktopServices::openUrl(QUrl(QString::fromLatin1(AlphaPlot::forum_Uri)));
}

void MainAlphaPlot::showBugTracker()
{
    QDesktopServices::openUrl(QUrl(QString::fromLatin1(AlphaPlot::bugreport_Uri)));
}

void MainAlphaPlot::parseCommandLineArguments(const QStringList& args)
{
    int num_args = args.count();
    if (num_args == 0)
        return;

    QString str;
    bool exec = false;
    Q_FOREACH (str, args) {
        if (str == QString::fromLatin1("-v") || str == QString::fromLatin1("--version")) {
            QString s = AlphaPlot::versionString() + AlphaPlot::extraVersion()
                + QString::fromLatin1("\n") + tr("Released") + QString::fromLatin1(": ")
                + AlphaPlot::releaseDateString() + QString::fromLatin1("\n") + tr("Original author")
                + QString::fromLatin1(": ") + AlphaPlot::originalAuthorWithMail()
                + QString::fromLatin1("\n");

#ifdef Q_OS_WIN
            hide();
            QMessageBox::information(
                this, tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Version"), s);
#else
            std::cout << s.toStdString();
#endif
            exit(0);
        }
        else if (str == QString::fromLatin1("-h") || str == QString::fromLatin1("--help")) {
            QString s = QString::fromLatin1("\n") + tr("Usage") + QString::fromLatin1(": ")
                + QString::fromLatin1("AlphaPlot [") + tr("options") + QString::fromLatin1("] [")
                + tr("file") + QString::fromLatin1("_") + tr("name") + QString::fromLatin1("]\n\n");
            s + tr("Valid options are") + QString::fromLatin1(":\n");
            s += QString::fromLatin1("-a ") + tr("or") + QString::fromLatin1(" --about: ")
                + tr("about AlphaPlot application") + QString::fromLatin1("\n");
            s += QString::fromLatin1("-h ") + tr("or") + QString::fromLatin1(" --help: ")
                + tr("show command line options") + QString::fromLatin1("\n");
            s += QString::fromLatin1("-l=XX ") + tr("or") + QString::fromLatin1(" --lang=XX: ")
                + tr("start AlphaPlot in language")
                + QString::fromLatin1(" XX ('en', 'fr', 'de', ...)\n");
            s += QString::fromLatin1("-v ") + tr("or") + QString::fromLatin1(" --version: ")
                + tr("print AlphaPlot version and release date") + QString::fromLatin1("\n");
            s += QString::fromLatin1("'") + tr("file") + QString::fromLatin1("_") + tr("name")
                + QString::fromLatin1("' ")
                + tr("can be any .aproj, .aproj.gz, .py or ASCII "
                     "file")
                + QString::fromLatin1("\n");
#ifdef Q_OS_WIN
            hide();
            QMessageBox::information(this, tr("AlphaPlot - Help"), s);
#else
            std::cout << s.toStdString();
#endif
            exit(0);
        }
        else if (str.startsWith(QString::fromLatin1("--lang="))
                 || str.startsWith(QString::fromLatin1("-l="))) {
            QStringList localesplits = str.split(QString::fromLatin1("="));
            QString locale = localesplits.at(1).trimmed();
            if (locales.contains(locale))
                switchToLanguage(locale);

            if (!locales.contains(locale))
                QMessageBox::critical(
                    this, tr("Error"),
                    tr("<b> %1 </b>: Wrong locale option or no translation available!")
                        .arg(locale));
        }
        else if (str.startsWith(QString::fromLatin1("--about"))
                 || str.startsWith(QString::fromLatin1("-a"))) {
            QString abt = tr("AlphaPlot is a free cross-platform program for two- and "
                             "three-dimensional graphical presentation of data sets and for "
                             "data analysis. The plots can be produced from data sets stored "
                             "in tables or from analytical functions.")
                + QString::fromLatin1("\n")
                + tr("AlphaPlot uses code from SciDAVis, which consisted (at the time "
                     "of the fork, i.e. SciDAVis 1.D9) which inturn is the fork of "
                     "QtiPlot 0.9-rc.")
                + QString::fromLatin1("\n");
#ifdef Q_OS_WIN
            hide();
            QMessageBox::information(this, tr("AlphaPlot - about"), abt);
#else
            std::cout << abt.toStdString();
#endif
            exit(0);
        }
        else if (str.startsWith(QString::fromLatin1("-"))
                 || str.startsWith(QString::fromLatin1("--"))) {
            QString err = tr("(%1) unknown command line option!").arg(str)
                + QString::fromLatin1("\n")
                + tr("Type %1 to see the list of the valid options.")
                      .arg(QString::fromLatin1("'AlphaPlot -h'"))
                + QString::fromLatin1("\n");

#ifdef Q_OS_WIN
            QMessageBox::critical(this, tr("Error"), err);
#else
            std::cout << err.toStdString();
#endif
            exit(0);
        }
    }

    QString file_name = args[num_args - 1];// last argument
    if (file_name.startsWith(QString::fromLatin1("-")))
        return;// no file name given

    if (!file_name.isEmpty()) {
        QFileInfo fi(file_name);
        if (fi.isDir()) {
            QMessageBox::critical(
                this, tr("File opening error"),
                tr("<b>%1</b> is a directory, please specify a file name!").arg(file_name));
            return;
        }
        else if (!fi.isReadable()) {
            QMessageBox::critical(
                this, tr("File opening error"),
                tr("You don't have the permission to open this file: <b>%1</b>").arg(file_name));
            return;
        }
        else if (!fi.exists()) {
            QMessageBox::critical(this, tr("File opening error"),
                                  tr("The file: <b>%1</b> doesn't exist!").arg(file_name));
            return;
        }

        workingDir = fi.absolutePath();
        saveSettings();// the recent projects must be saved

        MainAlphaPlot* a;
        if (exec)
            a = loadScript(file_name, exec);
        else
            a = openAproj(file_name);

        if (a) {
            a->workingDir = workingDir;
            close();
        }
    }
}

void MainAlphaPlot::createLanguagesList()
{
    appTranslator = new QTranslator(this);
    qtTranslator = new QTranslator(this);
    qApp->installTranslator(appTranslator);
    qApp->installTranslator(qtTranslator);

    qmPath = QString(TS_PATH);

    QString lng; // lang, as en_GB
    QString slng;// short lang, as en
    lng = QLocale().name();
    {
        if (lng == QString::fromLatin1("C"))
            lng = QString::fromLatin1("en");
        int i = lng.indexOf(QString::fromLatin1("."));
        if (i >= 0)
            lng = lng.left(i);
        i = lng.indexOf(QString::fromLatin1("_"));
        if (i >= 0)
            slng = lng.left(i);
        else
            slng = lng;
    }
    if (slng.size() > 2)
        slng = slng.left(2);

    QDir dir(qmPath);
    QStringList fileNames = dir.entryList(QStringList(QString::fromLatin1("alphaplot_*.qm")));
    if (fileNames.size() == 0) {
        // fall back to looking in the executable's directory
        qmPath = QFileInfo(QCoreApplication::applicationFilePath()).path()
            + QString::fromLatin1("/translations");
        dir.setPath(qmPath);
        fileNames = dir.entryList(QStringList(QString::fromLatin1("alphaplot_*.qm")));
    }
    for (int i = 0; i < static_cast<int>(fileNames.size()); i++) {
        QString locale = fileNames[i];
        locale = locale.mid(locale.indexOf(QChar::fromLatin1('_')) + 1);
        locale.truncate(locale.indexOf(QChar::fromLatin1('.')));
        locales.push_back(locale);
    }
    locales.push_back(QString::fromLatin1("en"));
    locales.sort();
    AlphaPlot::setLocales(locales);

    if (appLanguage != QString::fromLatin1("en")) {
        if (!appTranslator->load(QString::fromLatin1("alphaplot_") + appLanguage, qmPath))
            if (!appTranslator->load(QString::fromLatin1("alphaplot_") + appLanguage))
                if (!appTranslator->load(QString::fromLatin1("alphaplot_") + lng, qmPath))
                    if (!appTranslator->load(QString::fromLatin1("alphaplot_") + lng))
                        if (!appTranslator->load(QString::fromLatin1("alphaplot_") + slng, qmPath))
                            appTranslator->load(QString::fromLatin1("alphaplot_") + slng);
        if (!qtTranslator->load(QString::fromLatin1("qt_") + appLanguage,
                                qmPath + QString::fromLatin1("/qt")))
            if (!qtTranslator->load(QString::fromLatin1("qt_") + appLanguage))
                if (!qtTranslator->load(QString::fromLatin1("qt_") + lng,
                                        qmPath + QString::fromLatin1("/qt")))
                    if (!qtTranslator->load(QString::fromLatin1("qt_") + lng))
                        if (!qtTranslator->load(QString::fromLatin1("qt_") + slng,
                                                qmPath + QString::fromLatin1("/qt")))
                            qtTranslator->load(QString::fromLatin1("qt_") + slng);
    }
}

void MainAlphaPlot::switchToLanguage(int param)
{
    if (param < static_cast<int>(locales.size()))
        switchToLanguage(locales[param]);
}

void MainAlphaPlot::switchToLanguage(const QString& locale)
{
    if (!locales.contains(locale) || appLanguage == locale)
        return;

    appLanguage = locale;
    if (locale == QString::fromLatin1("en")) {
        qApp->removeTranslator(appTranslator);
        qApp->removeTranslator(qtTranslator);
        delete appTranslator;
        delete qtTranslator;
        appTranslator = new QTranslator(this);
        qtTranslator = new QTranslator(this);
        qApp->installTranslator(appTranslator);
        qApp->installTranslator(qtTranslator);
    }
    else {
        if (!appTranslator->load(QString::fromLatin1("alphaplot_") + appLanguage, qmPath))
            appTranslator->load(QString::fromLatin1("alphaplot_") + appLanguage);
        if (!qtTranslator->load(QString::fromLatin1("qt_") + appLanguage,
                                qmPath + QString::fromLatin1("/qt")))
            qtTranslator->load(QString::fromLatin1("qt_") + appLanguage);
    }
}

QStringList MainAlphaPlot::matrixNames()
{
    QStringList names;
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow))
            names << qobject_cast<Matrix*>(subwindow)->name();
    }
    return names;
}

bool MainAlphaPlot::alreadyUsedName(const QString& label)
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        MyWidget* widget = qobject_cast<MyWidget*>(subwindow);
        if (widget && widget->name() == label) {
            return true;
        }
    }
    return false;
}

bool MainAlphaPlot::projectHasMatrices()
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    bool has = false;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow)) {
            has = true;
            break;
        }
    }
    return has;
}

bool MainAlphaPlot::projectHas2DPlots()
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    bool hasPlots = false;
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
            hasPlots = true;
            break;
        }
    }
    return hasPlots;
}

bool MainAlphaPlot::projectHas3DPlots()
{
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
        if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {
            return true;
        }
    }
    return false;
}

void MainAlphaPlot::appendProject()
{
     OpenProjectDialog* open_dialog = new OpenProjectDialog(this, false);
     open_dialog->setDirectory(workingDir);
     open_dialog->setExtensionWidget(nullptr);
     if (open_dialog->exec() != QDialog::Accepted ||
         open_dialog->selectedFiles().isEmpty())
         return;
     workingDir = open_dialog->directory().path();
     aprojhandler_->appendproject(open_dialog->selectedFiles().at(0));
}

void MainAlphaPlot::saveAsProject()
{
    QString filter = tr("AlphaPlot project") + QString::fromLatin1(" (*.aproj);;");
    filter += tr("Compressed AlphaPlot project") + QString::fromLatin1(" (*.aproj.gz)");

    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this, tr("Save project as"), workingDir, filter,
                                                    &selectedFilter);

    if (!filename.isEmpty()) {
        QFileInfo fi(filename);
        workingDir = fi.absolutePath();
        QString baseName = fi.fileName();
        if (!baseName.endsWith(QString::fromLatin1(".aproj"))
            && !baseName.endsWith(QString::fromLatin1(".aproj.gz"))) {
            filename.append(QString::fromLatin1(".aproj"));
            if (selectedFilter.contains(QString::fromLatin1(".gz")))
                filename.append(QString::fromLatin1(".gz"));
        }

        if (aprojhandler_->saveproject(filename, current_folder)) {
            recentProjects.removeAll(filename);
            recentProjects.push_front(filename);
            updateRecentProjectsList();
        }
    }
}

// Folder popup menu from folder view (project explorer)
void MainAlphaPlot::showFolderPopupMenu(const QPoint& p)
{
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        QTreeWidgetItem* it = this->plotExplorer->folderView->itemAt(p);
        if (it)
            showFolderPopupMenu(it, this->plotExplorer->folderView->mapToGlobal(p), true);
    }

}

// General Folder popup menu (project explorer)
void MainAlphaPlot::showFolderPopupMenu(QTreeWidgetItem* it, const QPoint& p, bool fromFolders)
{
    if (!it)
        return;

    QMenu cm(this);
    QMenu window(this);
    QMenu viewWindowsMenu(this);

    cm.addAction(tr("&Find..."), this, SLOT(findWindowOrFolderFromProjectExplorer()));
    cm.addSeparator();
    cm.addAction(tr("App&end Project..."), this, SLOT(appendProject()));
    if (static_cast<FolderTreeWidgetItem*>(it)->folder()->parent())
        cm.addAction(tr("Save &As Project..."), this, SLOT(saveAsProject()));
    else
        cm.addAction(tr("Save Project &As..."), this, SLOT(saveProjectAs()));
    cm.addSeparator();

    if (fromFolders && show_windows_policy != HideAll) {
        cm.addAction(tr("&Show All Windows"), this, SLOT(showAllFolderWindows()));
        cm.addAction(tr("&Hide All Windows"), this, SLOT(hideAllFolderWindows()));
        cm.addSeparator();
    }

    if (!fromFolders || it->parent()) {
        cm.addAction(IconLoader::load(QString::fromLatin1("edit-delete"), IconLoader::General),
                     tr("&Delete Folder"), this, SLOT(deleteFolder()), Qt::Key_F8);
        cm.addAction(tr("&Rename"), this, SLOT(renameFolderFromMenu()), Qt::Key_F2);
        cm.addSeparator();
    }

     if (fromFolders) {
        auto NewTable = Application::Instance->commandManager().getCommandByName("Std_New_Table");
        auto NewMatrix = Application::Instance->commandManager().getCommandByName("Std_New_Matrix");
        auto NewGraph = Application::Instance->commandManager().getCommandByName("Std_New_Graph");
        auto NewFunctionPlot = Application::Instance->commandManager().getCommandByName("Std_New_2DPlot");
        auto New3DSurfacePlot = Application::Instance->commandManager().getCommandByName("Std_New_3DPlot");
       
        window.setTitle(tr("New &Window"));
        
        window.addAction(NewTable->getAction()->action());
        window.addAction(NewMatrix->getAction()->action());
        //window.addAction(actionNewNote->getAction()->action());
        window.addAction(NewGraph->getAction()->action());
        window.addAction(NewFunctionPlot->getAction()->action());
        window.addAction(New3DSurfacePlot->getAction()->action());

        cm.addMenu(&window);
     }

    cm.addAction(IconLoader::load(QString::fromLatin1("folder-explorer"), IconLoader::LightDark),
                 tr("New F&older"), this, SLOT(addFolder()), Qt::Key_F7);
    cm.addSeparator();

    viewWindowsMenu.setTitle(tr("&View Windows"));
    QActionGroup showWindowsPolicyGroup(this);
    QAction windowsNone(tr("&None"), this);
    QAction windowsInActiveFolder(tr("&Windows in Active Folder"), this);
    QAction windowsInActiveFoldersAndSubs(tr("Windows in &Active Folder && Subfolders"), this);
    windowsNone.setCheckable(true);
    windowsInActiveFolder.setCheckable(true);
    windowsInActiveFoldersAndSubs.setCheckable(true);
    showWindowsPolicyGroup.addAction(&windowsNone);
    showWindowsPolicyGroup.addAction(&windowsInActiveFolder);
    showWindowsPolicyGroup.addAction(&windowsInActiveFoldersAndSubs);

    viewWindowsMenu.addAction(&windowsNone);
    viewWindowsMenu.addAction(&windowsInActiveFolder);
    viewWindowsMenu.addAction(&windowsInActiveFoldersAndSubs);

    QSignalMapper mapper;
    mapper.setMapping(&windowsNone, HideAll);
    mapper.setMapping(&windowsInActiveFolder, ActiveFolder);
    mapper.setMapping(&windowsInActiveFoldersAndSubs, SubFolders);

    switch (show_windows_policy) {
        case HideAll:
            windowsNone.setChecked(true);
            break;
        case ActiveFolder:
            windowsInActiveFolder.setChecked(true);
            break;
        case SubFolders:
            windowsInActiveFoldersAndSubs.setChecked(true);
            break;
    }

    connect(&windowsNone, SIGNAL(triggered()), &mapper, SLOT(map()));
    connect(&windowsInActiveFolder, SIGNAL(triggered()), &mapper, SLOT(map()));
    connect(&windowsInActiveFoldersAndSubs, SIGNAL(triggered()), &mapper, SLOT(map()));
    connect(&mapper, SIGNAL(mapped(int)), this, SLOT(setShowWindowsPolicy(int)));

    cm.addMenu(&viewWindowsMenu);
    cm.addSeparator();
    cm.addAction(tr("&Properties..."), this, SLOT(folderProperties()));
    cm.exec(p);
}

// Setting windows policy & windows view (project explorer)
void MainAlphaPlot::setShowWindowsPolicy(int policy)
{
    if (show_windows_policy == static_cast<ShowWindowsPolicy>(policy))
        return;

    show_windows_policy = static_cast<ShowWindowsPolicy>(policy);
    if (show_windows_policy == HideAll) {
        QList<QMdiSubWindow*> subwindowlist = subWindowsList();
        Q_FOREACH (QMdiSubWindow* subwindow, subwindowlist) {
            MyWidget* widget = qobject_cast<MyWidget*>(subwindow);
            if (!widget)
                continue;
            hiddenWindows->append(widget);
            widget->hide();
            setListViewView(widget->name(), tr("Hidden"));
        }
    }
    else
        showAllFolderWindows();
}

// Find window or folder dialog (project explorer)
void MainAlphaPlot::findWindowOrFolderFromProjectExplorer()
{
    std::unique_ptr<FindDialog> findDialog(new FindDialog(current_folder, this));
    if (findDialog->exec() == QDialog::Accepted) {

        
     find(findDialog->boxFind->currentText(), findDialog->boxWindowNames->isChecked(),
             findDialog->boxWindowLabels->isChecked(), findDialog->boxFolderNames->isChecked(),
             findDialog->boxCaseSensitive->isChecked(), findDialog->boxPartialMatch->isChecked(),
             findDialog->boxSubfolders->isChecked());
        // add the combo box's current text to the list when the find button is
        // pressed
     QString text = findDialog->boxFind->currentText();
        if (!text.isEmpty()) {
            if (findDialog->boxFind->findText(text) == -1)// no duplicates
            {
                findDialog->boxFind->insertItem(0, text);
                findDialog->boxFind->setCurrentIndex(0);//koffa the way
            }
        }
    }
    
}

// Rename triggered from folder/list view context menu (project explorer)
void MainAlphaPlot::renameFolderFromMenu()
{
    FolderTreeWidgetItem* fi = current_folder->folderTreeWidgetItem();
    if (fi)
        startRenameFolder(fi);
}

// Start rename selected folder item (project explorer)
void MainAlphaPlot::startRenameFolder(FolderTreeWidgetItem* fi)
{
    if (!fi || !fi->parent())
        return;

    current_folder = fi->folder();
    Folder::currentFolderNames.clear();

    Folder* parent = static_cast<Folder*>(current_folder->parent());
    if (!parent)// the parent folder is the project folder (it always exists)
        parent = projectFolder();

    Folder::currentFolderNames << parent->subfolders();

     // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        this->plotExplorer->folderView->clearSelection();
        this->plotExplorer->folderView->setCurrentItem(fi);
        fi->treeWidget()->editItem(fi, 0);

        connect(this->plotExplorer->folderView, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this,
                SLOT(renameFolder(QTreeWidgetItem*)));
    }
}

// Rename selected folder item (project explorer)
void MainAlphaPlot::renameFolder(QTreeWidgetItem* item)
{
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        disconnect(plotExplorer->folderView, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this,
                   SLOT(renameFolder(QTreeWidgetItem*)));

        if (!item)
            return;

        Folder* parent = static_cast<Folder*>(current_folder->parent());
        if (!parent)// the parent folder is the project folder (it always exists)
            parent = projectFolder();

        current_folder->setName(item->text(0));
        folderItemChanged(parent->folderTreeWidgetItem());// update the list views
        plotExplorer->folderView->setCurrentItem(parent->folderTreeWidgetItem());
    }
    
}

// Show all windows in folders and subfolders (project explorer)
void MainAlphaPlot::showAllFolderWindows()
{
    showAllFolderWindowsRecursive(current_folder->folderTreeWidgetItem());
}

// Show all windows in folders and subfolders recursive (project explorer)
void MainAlphaPlot::showAllFolderWindowsRecursive(FolderTreeWidgetItem* fitem)
{
    if (!fitem)
        return;

    FolderTreeWidgetItem* item = nullptr;
    for (int i = 0; i < fitem->childCount(); i++) {// toggle item view sub dirs
        item = static_cast<FolderTreeWidgetItem*>(fitem->child(i));
        QList<MyWidget*> list = static_cast<Folder*>(item->folder())->windowsList();
        Q_FOREACH (MyWidget* myWidget, list) {
            if (myWidget && show_windows_policy == SubFolders) {
                updateWindowLists(myWidget);
                switch (myWidget->status()) {
                    case MyWidget::Hidden:
                        myWidget->showNormal();
                        break;

                    case MyWidget::Normal:
                        myWidget->showNormal();
                        break;

                    case MyWidget::Minimized:
                        myWidget->showMinimized();
                        break;

                    case MyWidget::Maximized:
                        myWidget->showMaximized();
                        break;
                }
            }
            else
                myWidget->hide();
        }
    }

    for (int i = 0; i < fitem->childCount(); i++) {
        item = static_cast<FolderTreeWidgetItem*>(fitem->child(i));
        showAllFolderWindowsRecursive(item);
    }
}

// Hide all windows in this folder (project explorer)
void MainAlphaPlot::hideAllFolderWindows()
{
    QList<MyWidget*> lst = current_folder->windowsList();
    Q_FOREACH (MyWidget* w, lst)
        hideWindow(w);
}

// Add new folder (project explorer)
Folder* MainAlphaPlot::addFolder()
{
    QStringList lst = current_folder->subfolders();
    QString name = tr("New Folder");
    lst = lst.filter(name);
    if (!lst.isEmpty())
        name +=
            QString::fromLatin1(" (") + QString::number(lst.size() + 1) + QString::fromLatin1(")");

    Folder* f = new Folder(current_folder, name);
    addFolderListViewItem(f);

    FolderTreeWidgetItem* fi = new FolderTreeWidgetItem(current_folder->folderTreeWidgetItem(), f);
    if (fi) {
        f->setFolderTreeWidgetItem(fi);
        fi->setActive(false);
        Folder* parentFolder = dynamic_cast<Folder*>(f->parent());
        if (parentFolder) {
            // search for the plot explorer window
            if (!this->plotExplorer)
                this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
            // Python console found?
            if (this->plotExplorer) {
                plotExplorer->folderView->setCurrentItem(parentFolder->folderTreeWidgetItem());
            }
        }
    }
    return f;
}

// Delete selected folder & subfolders (project explorer)
bool MainAlphaPlot::deleteFolder(Folder* f)
{
    if (confirmCloseFolder
        && QMessageBox::information(
            this, tr("Delete folder?"),
            tr("Delete folder '%1' and all the windows it contains?").arg(f->name()), tr("Yes"),
            tr("No"), QString::fromLatin1(""), 0))
        return false;
    else {
        FolderTreeWidgetItem* fi = f->folderTreeWidgetItem();
        Q_FOREACH (MyWidget* w, f->windowsList())
            closeWindow(w);

        if (!(f->children()).isEmpty()) {
            FolderTreeWidgetItem* item;
            for (int i = 0; i < fi->childCount(); i++) {
                item = static_cast<FolderTreeWidgetItem*>(fi->child(i));
                Folder* subFolder = static_cast<Folder*>(item->folder());
                if (subFolder) {
                    Q_FOREACH (MyWidget* w, subFolder->windowsList()) {
                        removeWindowFromLists(w);
                        subFolder->removeWindow(w);
                        delete w;
                    }

                    FolderTreeWidgetItem* old_item = item;
                    delete subFolder;
                    delete old_item;
                }
            }
        }

        delete f;
        delete fi;
        return true;
    }
}

// Delete selected folder & subfolders (project explorer)
void MainAlphaPlot::deleteFolder()
{
    Folder* parent = qobject_cast<Folder*>(current_folder->parent());
    if (!parent)
        parent = projectFolder();

     // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        plotExplorer->folderView->blockSignals(true);
        if (deleteFolder(current_folder)) {
            current_folder = parent;
            plotExplorer->folderView->setCurrentItem(parent->folderTreeWidgetItem());
            changeFolder(parent, true);
        }

        plotExplorer->folderView->blockSignals(false);
        plotExplorer->folderView->setFocus();

    }

}

// Folder item doubleclicked (project explorer)
void MainAlphaPlot::folderItemDoubleClicked(QTreeWidgetItem* it)
{
    if (!it)
        return;

    if (it->type() == FolderTreeWidget::Folders) {
        FolderTreeWidgetItem* item =
            dynamic_cast<FolderTreeWidgetItem*>(it)->folder()->folderTreeWidgetItem();

           // search for the plot explorer window
        if (!this->plotExplorer)
            this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
        // Python console found?
        if (this->plotExplorer) {
            plotExplorer->folderView->setCurrentItem(item);
        }
    }
    else {
        MyWidget* widget = dynamic_cast<WindowTableWidgetItem*>(it)->window();
        if (!widget)
            return;
        if (getactiveMyWidget() != widget)
            activateWindow(widget);
        else {
            if (!widget->isMaximized())
                widget->setMaximized();
            else
                widget->setNormal();
        }
    }
}

// Change Folder in folder view (project explorer)
void MainAlphaPlot::folderItemChanged(QTreeWidgetItem* item)
{
    if (!item)
        return;

    item->setExpanded(true);
    changeFolder(static_cast<FolderTreeWidgetItem*>(item)->folder());

      // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        plotExplorer->folderView->setFocus();
    }
}

// Hide all windows of current folder (project explorer)
void MainAlphaPlot::hideFolderWindows(Folder* f)
{
    QList<MyWidget*> lst = f->windowsList();
    Q_FOREACH (MyWidget* w, lst)
        w->hide();

    if ((f->children()).isEmpty())
        return;

    FolderTreeWidgetItem* fi = f->folderTreeWidgetItem();
    FolderTreeWidgetItem* item;
    for (int i = 0; i < fi->childCount(); i++) {
        item = static_cast<FolderTreeWidgetItem*>(fi->child(i));
        lst = item->folder()->windowsList();
        Q_FOREACH (MyWidget* w, lst)
            w->hide();
    }
}

// Change Folder in folder view main implimentation(project explorer)
bool MainAlphaPlot::changeFolder(Folder* newFolder, bool force)
{
    if (current_folder == newFolder && !force)
        return false;

    deactivateFolders();
    newFolder->folderTreeWidgetItem()->setActive(true);

    Folder* oldFolder = current_folder;
    MyWidget::Status old_active_window_state = MyWidget::Normal;
    MyWidget* old_active_window = oldFolder->activeWindow();
    if (old_active_window)
        old_active_window_state = old_active_window->status();

    MyWidget::Status active_window_state = MyWidget::Normal;
    MyWidget* active_window = newFolder->activeWindow();
    if (active_window)
        active_window_state = active_window->status();

    // d->mdiArea->blockSignals(true);
    hideFolderWindows(oldFolder);
    current_folder = newFolder;

    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        this->plotExplorer->listView->clear();
    }

    QObjectList folderLst = newFolder->children();
    if (!folderLst.isEmpty()) {
        Q_FOREACH (QObject* folder, folderLst)
            addFolderListViewItem(static_cast<Folder*>(folder));
    }

    QList<MyWidget*> lst = newFolder->windowsList();
    Q_FOREACH (MyWidget* w, lst) {
        if (!hiddenWindows->contains(w) && !outWindows->contains(w)
            && show_windows_policy != HideAll) {
            // show only windows in the current folder not hidden by the user
            if (w->status() == MyWidget::Normal)
                w->showNormal();
            else if (w->status() == MyWidget::Minimized)
                w->showMinimized();
        }
        else
            w->setStatus(MyWidget::Hidden);

        addListViewItem(w);
    }

    if (!(newFolder->children()).isEmpty()) {
        refreshFolderTreeWidgetItemsRecursive(newFolder->folderTreeWidgetItem());
    }

    // d->mdiArea->blockSignals(false);

    if (active_window) {
        getMainWindow()->setActiveSubWindow(active_window);
        if (active_window_state == MyWidget::Minimized)
            active_window->showMinimized();// d->mdiArea->setActiveWindow() makes
                                           // minimized windows to be shown normally
        current_folder->setActiveWindow(active_window);
        customMenu(active_window);
        customToolBars(active_window);
    }
    else {
        getMainWindow()->setActiveSubWindow(active_window);
        customMenu(active_window);
        customToolBars(active_window);
    }

    if (old_active_window) {
        old_active_window->setStatus(old_active_window_state);
        oldFolder->setActiveWindow(old_active_window);
    }

    return true;
}

// Recursively set windows policy (project explorer)
void MainAlphaPlot::refreshFolderTreeWidgetItemsRecursive(FolderTreeWidgetItem* item)
{
    if (!item)
        return;

    if (!(item->folder()->children()).isEmpty()) {
        FolderTreeWidgetItem* fi = item->folder()->folderTreeWidgetItem();
        FolderTreeWidgetItem* tempItem;
        for (int i = 0; i < fi->childCount(); i++) {
            tempItem = static_cast<FolderTreeWidgetItem*>(fi->child(i));
            QList<MyWidget*> list = static_cast<Folder*>(tempItem->folder())->windowsList();
            Q_FOREACH (MyWidget* widget, list) {
                if (!hiddenWindows->contains(widget) && !outWindows->contains(widget)) {
                    if (show_windows_policy == SubFolders) {
                        if (widget->status() == MyWidget::Normal
                            || widget->status() == MyWidget::Maximized)
                            widget->showNormal();
                        else if (widget->status() == MyWidget::Minimized)
                            widget->showMinimized();
                    }
                    else if (widget->isVisible())
                        widget->hide();
                }
            }
        }
    }

    FolderTreeWidgetItem* it = nullptr;
    for (int i = 0; i < item->childCount(); i++) {
        it = static_cast<FolderTreeWidgetItem*>(item->child(i));
        refreshFolderTreeWidgetItemsRecursive(it);
    }
}

// Deactivate all folders (project explorer)
void MainAlphaPlot::deactivateFolders()
{
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        FolderTreeWidgetItem* item =
            static_cast<FolderTreeWidgetItem*>(plotExplorer->folderView->topLevelItem(0));
        deactivateFolderTreeWidgetItemsRecursive(item);
    }
}

// Deactivate all children of specific folder item (project explorer)
void MainAlphaPlot::deactivateFolderTreeWidgetItemsRecursive(FolderTreeWidgetItem* item)
{
    if (!item)
        return;

    FolderTreeWidgetItem* it = nullptr;
    for (int i = 0; i < item->childCount(); i++) {
        it = static_cast<FolderTreeWidgetItem*>(item->child(i));
        it->setActive(false);
    }

    for (int i = 0; i < item->childCount(); i++) {
        it = static_cast<FolderTreeWidgetItem*>(item->child(i));
        deactivateFolderTreeWidgetItemsRecursive(it);
    }
}

// Add list view items (project explorer)
void MainAlphaPlot::addListViewItem(MyWidget* widget)
{
    if (!widget)
        return;
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        WindowTableWidgetItem* it = new WindowTableWidgetItem(this->plotExplorer->listView, widget);
        if (isActiveSubWindow(widget, SubWindowType::MatrixSubWindow)) {
            it->setIcon(0, IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark));
            it->setText(1, tr("Matrix"));
        }
        else if (isActiveSubWindow(widget, SubWindowType::TableSubWindow)) {
            it->setIcon(0, IconLoader::load(QString::fromLatin1("table"), IconLoader::LightDark));
            it->setText(1, tr("Table"));
        }
        else if (isActiveSubWindow(widget, SubWindowType::NoteSubWindow)) {
            it->setIcon(0,
                        IconLoader::load(QString::fromLatin1("edit-note"), IconLoader::LightDark));
            it->setText(1, tr("Note"));
        }
        else if (isActiveSubWindow(widget, SubWindowType::Plot2DSubWindow)) {
            it->setIcon(0,
                        IconLoader::load(QString::fromLatin1("edit-graph"), IconLoader::LightDark));
            it->setText(1, tr("2D Graph"));
        } /*else if (isActiveSubWindow(widget, SubWindowType::SubwindowPlot3D)) {
       it->setIcon(0, IconLoader::load(QString::fromLatin1("edit-graph3d"), IconLoader::LightDark));
       it->setText(1, tr("3D Graph"));
     }*/
        else if (isActiveSubWindow(widget, SubWindowType::Plot3DSubWindow)) {
            it->setIcon(
                0, IconLoader::load(QString::fromLatin1("edit-graph3d"), IconLoader::LightDark));
            it->setText(1, tr("3D Graph"));
        }

        it->setText(0, widget->name());
        it->setText(2, widget->aspect());
        it->setText(3, widget->birthDate());
        it->setText(4, widget->windowLabel());
    }
}

// Folder view item Properties (project explorer)
void MainAlphaPlot::folderProperties()
{
    //std::unique_ptr<PropertiesDialog> propertiesDialog(
    //    new PropertiesDialog(this));
    //PropertiesDialog::Properties properties;
    //// project properties
    //if (!current_folder->parent()) {
    //    properties.icon = QPixmap(QString::fromLatin1(":icons/common/64/project-properties.png"));
    //    properties.name = currentFolder()->name();
    //    properties.type = QString::fromLatin1("AlphaPlot ") + tr("Project");
    //    properties.description = tr("This is an AlphaPlot project");
    //    properties.content = QString(tr("%1 Folders,\n%2 Windows"))
    //        .arg(current_folder->subfolders().count())
    //        .arg(subWindowsList().count());
    //    if (projectname != QString::fromLatin1("untitled")) {
    //        QFileInfo fileInfo(projectname);
    //        properties.path = projectname;
    //        (saved) ? properties.status = tr("Saved")
    //            : properties.status = tr("Not Saved");
    //        properties.size = QString::number(fileInfo.size());
    //        properties.created = fileInfo.birthTime().toString(Qt::LocalDate);
    //        properties.modified = fileInfo.lastModified().toString(Qt::LocalDate);
    //        properties.label = QString::fromLatin1("");
    //    }
    //    else {
    //        properties.path = projectname;
    //        properties.status = tr("never saved");
    //        properties.size = tr("never saved");
    //        properties.created = current_folder->birthDate();
    //        properties.modified = tr("never saved");
    //        properties.label = QString::fromLatin1("");
    //    }
    //    // folder properties
    //}
    //else {
    //    properties.icon =
    //        QPixmap(QPixmap(QString::fromLatin1(":icons/common/64/folder-properties.png")));
    //    properties.name = currentFolder()->name();
    //    properties.type = tr("Folder");
    //    properties.status = tr("Not applicable");
    //    properties.path = current_folder->path();
    //    properties.size = tr("Not applicable");
    //    properties.created = current_folder->birthDate();
    //    properties.modified = currentFolder()->modificationDate();
    //    properties.label = QString::fromLatin1("");
    //    properties.content = QString(tr("%1 Folders,\n%2 Windows"))
    //        .arg(current_folder->subfolders().count())
    //        .arg(current_folder->windowsList().count());
    //    properties.description = tr("This is an AlphaPlot Folder");
    //}
    //propertiesDialog->setupProperties(properties);
    //propertiesDialog->exec();
}

// List view windows properties (project explorer)
void MainAlphaPlot::windowProperties()
{
    MyWidget* window = qobject_cast<MyWidget*>(getactiveMyWidget());

    if (!window)
        return;
    std::unique_ptr<PropertiesDialog> propertiesDialog(new PropertiesDialog(this));
    PropertiesDialog::Properties properties;

    if (isActiveSubWindow(window, SubWindowType::MatrixSubWindow)) {
        properties.icon = QPixmap(QString::fromLatin1(":icons/common/64/matrix-properties.png"));
        properties.type = tr("Matrix");
        properties.size = QString::fromLatin1("%1 x %2")
                              .arg(static_cast<Matrix*>(window)->size().height())
                              .arg(static_cast<Matrix*>(window)->size().width());
        properties.content = QString(tr("%1 Rows,\n%2 Columns"))
                                 .arg(static_cast<Matrix*>(window)->numRows())
                                 .arg(static_cast<Matrix*>(window)->numCols());
        properties.description = tr("This is an AlphaPlot Matrix");
    }
    else if (isActiveSubWindow(window, SubWindowType::TableSubWindow)) {
        properties.icon = QPixmap(QString::fromLatin1(":icons/common/64/table-properties.png"));
        properties.type = tr("Table");
        properties.size = QString::fromLatin1("%1 x %2")
                              .arg(static_cast<Table*>(window)->size().height())
                              .arg(static_cast<Table*>(window)->size().width());
        properties.content = QString(tr("%1 Rows,\n%2 Columns"))
                                 .arg(static_cast<Table*>(window)->numRows())
                                 .arg(static_cast<Table*>(window)->numCols());
        properties.description = tr("This is an AlphaPlot Table");
    }
    /*else if (isActiveSubWindow(window, SubWindowType::NoteSubWindow)) {
         properties.icon = QPixmap(QString::fromLatin1(":icons/common/64/note-properties.png"));
         properties.type = tr("Note");
         properties.size = QString::fromLatin1("%1 x %2")
             .arg(static_cast<Note*>(window)->size().height())
             .arg(static_cast<Note*>(window)->size().width());
         properties.content =
             QString(tr("%1 Characters,\n%2 Lines"))
             .arg(QString::number(static_cast<Note*>(window)->text().count()))
             .arg(QString::fromLatin1("(unavailable)"));
         properties.description = tr("This is an AlphaPlot Note");
     }*/
    else if (isActiveSubWindow(window, SubWindowType::Plot2DSubWindow)) {
        properties.icon = QPixmap(QString::fromLatin1(":icons/common/64/graph2D-properties.png"));
        properties.type = tr("Graph2D");
        properties.size = QString::fromLatin1(("%1 x %2"))
                              .arg(static_cast<Layout2D*>(window)->size().height())
                              .arg(static_cast<Layout2D*>(window)->size().width());
        properties.content = QString(tr("%1 Layers,\n%2x%3 Layout"))
                                 .arg(QString::fromLatin1(""))
                                 .arg(QString::fromLatin1(""))
                                 .arg(QString::fromLatin1(""));
        properties.description = tr("This is an AlphaPlot 2D Graph");
    }
    else if (isActiveSubWindow(window, SubWindowType::Plot3DSubWindow)) {
        properties.icon = QPixmap(QString::fromLatin1(":icons/common/64/graph3D-properties.png"));
        properties.type = tr("Graph3D");
        properties.size = QString::fromLatin1("%1 x %2")
                              .arg(static_cast<Layout3D*>(window)->size().height())
                              .arg(static_cast<Layout3D*>(window)->size().width());
        properties.content = QString(tr("%1x%2 Resolution,\n%3 Grids"))
                                 .arg(static_cast<Layout3D*>(window)->size().height())
                                 .arg(static_cast<Layout3D*>(window)->size().width())
                                 .arg(false);
        properties.description = tr("This is an AlphaPlot 3D Graph");
    }

    properties.name = window->name();
    if (window->status() == MyWidget::Normal) {
        properties.status = tr("Normal");
    }
    else if (window->status() == MyWidget::Hidden) {
        properties.status = tr("Hidden");
    }
    else if (window->status() == MyWidget::Maximized) {
        properties.status = tr("Maximized");
    }
    else if (window->status() == MyWidget::Minimized) {
        properties.status = tr("Minimized");
    }
    properties.path = current_folder->path();
    properties.created = window->birthDate();
    properties.modified = QString::fromLatin1("");
    properties.label = window->windowLabel();

    propertiesDialog->setupProperties(properties);
    propertiesDialog->exec();
}

// Add folder view items (project explorer)
void MainAlphaPlot::addFolderListViewItem(Folder* folder)
{
    if (!folder)
        return;
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        FolderTreeWidgetItem* item = new FolderTreeWidgetItem(plotExplorer->listView, folder);
        item->setActive(false);
        item->setText(0, folder->name());
        item->setText(1, tr("Folder"));
        item->setText(3, folder->birthDate());
    }
}

// Find window or folders (project explorer)
void MainAlphaPlot::find(const QString& s, bool windowNames, bool labels, bool folderNames,
                      bool caseSensitive, bool partialMatch, bool subfolders)
{
    if (windowNames || labels) {
        MyWidget* widget =
            current_folder->findWindow(s, windowNames, labels, caseSensitive, partialMatch);
        if (widget) {
            activateWindow(widget);
            return;
        }

            // search for the plot explorer window
        if (!this->plotExplorer)
            this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
        // Python console found?
        if (this->plotExplorer) {
            if (subfolders) {
                bool found = findRecursive(
                    static_cast<FolderTreeWidgetItem*>(plotExplorer->folderView->currentItem()),
                    FindWindowItem, s, labels, caseSensitive, partialMatch);
                if (found)
                    return;
            }
        }

        if (folderNames) {
            Folder* dir = current_folder->findSubfolder(s, caseSensitive, partialMatch);
            if (dir) {
                plotExplorer->folderView->setCurrentItem(dir->folderTreeWidgetItem());
                return;
            }

            if (subfolders) {
                bool found = findRecursive(
                    static_cast<FolderTreeWidgetItem*>(plotExplorer->folderView->currentItem()),
                    FindFolderItem, s, false, caseSensitive, partialMatch);
                if (found)
                    return;
            }
        }
        }

    QMessageBox::warning(this, tr("No match found"),
                         tr("Sorry, no match found for string: '%1'").arg(s));
}

// Find window or folders recursively (project explorer)
bool MainAlphaPlot::findRecursive(FolderTreeWidgetItem* item, FindItem findItem, QString s,
                               bool labels, bool caseSensitive, bool partialMatch)
{
    if (!item)
        return false;
    FolderTreeWidgetItem* it = nullptr;

          // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {

        switch (findItem) {
            case FindWindowItem: {
                for (int i = 0; i < item->childCount(); i++) {
                    it = static_cast<FolderTreeWidgetItem*>(item->child(i));
                    MyWidget* myWidget =
                        it->folder()->findWindow(s, true, labels, caseSensitive, partialMatch);
                    if (myWidget) {
                        this->plotExplorer->folderView->setCurrentItem(
                            it->folder()->folderTreeWidgetItem());
                        activateWindow(myWidget);
                        return true;
                    }
                }
            } break;
            case FindFolderItem: {
                for (int i = 0; i < item->childCount(); i++) {
                    it = static_cast<FolderTreeWidgetItem*>(item->child(i));
                    Folder* fldr = it->folder()->findSubfolder(s, caseSensitive, partialMatch);
                    if (fldr) {
                        this->plotExplorer->folderView->setCurrentItem(
                            fldr->folderTreeWidgetItem());
                        return true;
                    }
                }
            } break;
        }


    }

    for (int i = 0; i < item->childCount(); i++) {
        it = static_cast<FolderTreeWidgetItem*>(item->child(i));
        bool status = findRecursive(it, findItem, s, labels, caseSensitive, partialMatch);
        if (status) {
            return true;
        }
    }

    return false;
}

void MainAlphaPlot::dropFolderItems(QTreeWidgetItem* dest)
{
    if (!dest || draggedItems.isEmpty())
        return;

    Folder* dest_f = static_cast<FolderTreeWidgetItem*>(dest)->folder();

    QTreeWidgetItem* it = nullptr;
    QStringList subfolders = dest_f->subfolders();
    bool stopdrag = false;
    QList<MyWidget*> draggedwidgets;

    Q_FOREACH (it, draggedItems) {
        if (it->type() != FolderTreeWidget::ItemType::Folders) {
            MyWidget* w = dynamic_cast<WindowTableWidgetItem*>(it)->window();
            if (w) {
                draggedwidgets << w;
            }
        }
    }

    // check the data structure is moving along with the graphs and viceversa
    Q_FOREACH (MyWidget* w, draggedwidgets) {
        if (qobject_cast<Layout2D*>(w)) {
            Layout2D* layout = qobject_cast<Layout2D*>(w);
            QList<MyWidget*> dependson = layout->dependentTableMatrix();
            Q_FOREACH (QTreeWidgetItem* depitems, draggedItems) {
                if (depitems->type() != FolderTreeWidget::ItemType::Folders) {
                    MyWidget* depw = dynamic_cast<WindowTableWidgetItem*>(depitems)->window();
                    if (depw) {
                        if (dependson.contains(depw))
                            dependson.removeOne(depw);
                    }
                }
            }
            if (dependson.size() > 0)
                stopdrag = true;
        }
        else if (qobject_cast<Layout3D*>(w)) {
            Layout3D* layout = qobject_cast<Layout3D*>(w);
            QList<MyWidget*> dependson = layout->dependentTableMatrix();
            Q_FOREACH (QTreeWidgetItem* depitems, draggedItems) {
                if (depitems->type() != FolderTreeWidget::ItemType::Folders) {
                    MyWidget* depw = dynamic_cast<WindowTableWidgetItem*>(depitems)->window();
                    if (depw) {
                        if (dependson.contains(depw))
                            dependson.removeOne(depw);
                    }
                }
            }
            if (dependson.size() > 0)
                stopdrag = true;
        }
        else if (w && (qobject_cast<Table*>(w) || qobject_cast<Matrix*>(w))) {
            QList<MyWidget*> widgetlist = current_folder->windowsList();
            Q_FOREACH (MyWidget* widget, widgetlist) {
                if (qobject_cast<Layout2D*>(widget)) {
                    QList<MyWidget*> dependson =
                        qobject_cast<Layout2D*>(widget)->dependentTableMatrix();
                    if (dependson.contains(w) && !draggedwidgets.contains(widget))
                        stopdrag = true;
                }
                else if (qobject_cast<Layout3D*>(widget)) {
                    QList<MyWidget*> dependson =
                        qobject_cast<Layout3D*>(widget)->dependentTableMatrix();
                    if (dependson.contains(w) && !draggedwidgets.contains(widget))
                        stopdrag = true;
                }
            }
        }
    }

    if (stopdrag) {
        QMessageBox::critical(this, QString::fromLatin1("Error"),
                              tr("Cannot move an object which depends "
                                 "on another object!"));
        draggedItems.clear();
        return;
    }

    Q_FOREACH (it, draggedItems) {
        if (it->type() == FolderTreeWidget::ItemType::Folders) {
            Folder* f = static_cast<FolderTreeWidgetItem*>(it)->folder();
            FolderTreeWidgetItem* src = f->folderTreeWidgetItem();
            if (dest_f == f) {
                QMessageBox::critical(this, QString::fromLatin1("Error"),
                                      tr("Cannot move an object to itself!"));
                draggedItems.clear();
                return;
            }

            if (static_cast<FolderTreeWidgetItem*>(dest)->isChildOf(src)) {
                QMessageBox::critical(this, QString::fromLatin1("Error"),
                                      tr("Cannot move a parent folder into a child folder!"));
                draggedItems.clear();
                // search for the plot explorer window
                if (!this->plotExplorer)
                    this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
                // Python console found?
                if (this->plotExplorer) {
                    this->plotExplorer->folderView->setCurrentItem(
                        current_folder->folderTreeWidgetItem());
                }
                return;
            }

            Folder* parent = dynamic_cast<Folder*>(f->parent());
            if (!parent)
                parent = projectFolder();
            if (dest_f == parent) {
                draggedItems.clear();
                return;
            }

            if (subfolders.contains(f->name())) {
                QMessageBox::critical(
                    this,
                    tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Skipped moving folder"),
                    tr("The destination folder already contains a folder called '%1'! "
                       "Folder skipped!")
                        .arg(f->name()));
            }
            else {
                QMessageBox::critical(
                    this,
                    tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Skipped moving folder"),
                    tr("Currently alphaplot dont support drag n drop folder items!")
                        .arg(f->name()));
                // moveFolder(src, static_cast<FolderTreeWidgetItem *>(dest));
            }
        }
        else {
            if (dest_f == current_folder)
                return;

            MyWidget* w = dynamic_cast<WindowTableWidgetItem*>(it)->window();
            if (w) {
                current_folder->removeWindow(w);
                w->hide();
                dest_f->addWindow(w);
                delete it;
            }
        }
    }

    draggedItems.clear();
    current_folder = dest_f;
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        plotExplorer->folderView->setCurrentItem(dest_f->folderTreeWidgetItem());
        changeFolder(dest_f, true);
        plotExplorer->folderView->setFocus();
    }

    modifiedProject();
}

void MainAlphaPlot::moveFolder(FolderTreeWidgetItem* src, FolderTreeWidgetItem* dest)
{
    // search for the plot explorer window
    if (!this->plotExplorer)
            this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
            plotExplorer->folderView->blockSignals(true);
    }

    Folder* dest_f = dest->folder();
    Folder* src_f = src->folder();

    QStringList lst = dest_f->subfolders();
    QString name = src_f->name();
    lst = lst.filter(name);
    if (!lst.isEmpty()) {
        QMessageBox::critical(
            this, tr("AlphaPlot") + QString::fromLatin1(" - ") + tr("Skipped moving folder"),
            tr("The destination folder already contains a folder called '%1'! "
               "Folder skipped!")
                .arg(name));
        return;
    }

    Folder* f = new Folder(dest_f, name);
    f->setBirthDate(src_f->birthDate());
    f->setModificationDate(src_f->modificationDate());
    addFolderListViewItem(f);

    FolderTreeWidgetItem* fi = new FolderTreeWidgetItem(dest_f->folderTreeWidgetItem(), f);
    f->setFolderTreeWidgetItem(fi);
    fi->setActive(false);

    QList<MyWidget*> list = QList<MyWidget*>(src_f->windowsList());
    Q_FOREACH (MyWidget* w, list) {
        src_f->removeWindow(w);
        w->hide();
        f->addWindow(w);
    }

    if (!(src_f->children()).isEmpty()) {
        FolderTreeWidgetItem* item = (FolderTreeWidgetItem*)src->child(0);
        int initial_depth = item->depth();
        QTreeWidgetItemIterator it(item);
        dest_f = src_f;

        while (item && item->depth() >= initial_depth) {
            src_f = (Folder*)item->folder();

            Folder* f = new Folder(dest_f, src_f->name());
            f->setBirthDate(src_f->birthDate());
            f->setModificationDate(src_f->modificationDate());
            addFolderListViewItem(f);

            FolderTreeWidgetItem* fi = new FolderTreeWidgetItem(dest_f->folderTreeWidgetItem(), f);
            f->setFolderTreeWidgetItem(fi);
            fi->setActive(false);

            dest_f = f;

            /*dest_f = new Folder(dest_f, src_f->name());
             dest_f->setBirthDate(src_f->birthDate());
             dest_f->setModificationDate(src_f->modificationDate());

             copy_item = new FolderTreeWidgetItem(copy_item, dest_f);
             copy_item->setText(0, src_f->name());
             dest_f->setFolderTreeWidgetItem(copy_item);*/

            QList<MyWidget*> list = QList<MyWidget*>(src_f->windowsList());
            Q_FOREACH (MyWidget* w, list) {
                src_f->removeWindow(w);
                w->hide();
                f->addWindow(w);
            }

            it++;
            item = (FolderTreeWidgetItem*)(*it);
        }
    }
    /*setCurrentFolderViewItem(dest);
     addFolder();
     des
     dest_f = new Folder(dest_f, src_f->name());
     dest_f->setBirthDate(src_f->birthDate());
     dest_f->setModificationDate(src_f->modificationDate());

     FolderTreeWidgetItem *copy_item = new FolderTreeWidgetItem(dest, dest_f);
     copy_item->setText(0, src_f->name());
     src_f->setFolderTreeWidgetItem(copy_item);

     QList<MyWidget *> lst = QList<MyWidget *>(src_f->windowsList());
     Q_FOREACH (MyWidget *w, lst) {
       src_f->removeWindow(w);
       w->hide();
       dest_f->addWindow(w);
     }

     if (!(src_f->children()).isEmpty()) {
       FolderTreeWidgetItem *item = (FolderTreeWidgetItem *)src->child(0);
       int initial_depth = item->depth();
       QTreeWidgetItemIterator it(item);

       while (item && item->depth() >= initial_depth) {
         src_f = (Folder *)item->folder();

         dest_f = new Folder(dest_f, src_f->name());
         dest_f->setBirthDate(src_f->birthDate());
         dest_f->setModificationDate(src_f->modificationDate());

         copy_item = new FolderTreeWidgetItem(copy_item, dest_f);
         copy_item->setText(0, src_f->name());
         dest_f->setFolderTreeWidgetItem(copy_item);

         lst = QList<MyWidget *>(src_f->windowsList());
         Q_FOREACH (MyWidget *w, lst) {
           src_f->removeWindow(w);
           w->hide();
           dest_f->addWindow(w);
         }

         it++;
         item = (FolderTreeWidgetItem *)(*it);
       }
     }*/

    src_f = src->folder();
    delete src_f;
    delete src;

    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        this->plotExplorer->folderView->blockSignals(false);
    }
}

// Turns 3D animation on or off
void MainAlphaPlot::toggle3DAnimation(bool on)
{
    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    Layout3D* lout = qobject_cast<Layout3D*>(getactiveMyWidget());
    lout->setAnimation(on);
}

QString MainAlphaPlot::generateUniqueName(const QString& name, bool increment)
{
    int index = 0;
    QList<QMdiSubWindow*> subwindowlist = subWindowsList();
    QStringList lst;

    for (int i = 0; i < subwindowlist.count(); i++) {
        MyWidget* widget = qobject_cast<MyWidget*>(subwindowlist.at(i));
        if (!widget)
            continue;
        lst << widget->name();
        if (widget->name().startsWith(name))
            index++;
    }

    QString newName = name;
    if (increment)// force return of a different name
        newName += QString::number(++index);
    else {
        if (index > 0)
            newName += QString::number(index);
    }

    while (lst.contains(newName))
        newName = name + QString::number(++index);
    return newName;
}

void MainAlphaPlot::blockFolderviewsignals(bool value) { 
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        plotExplorer->folderView->blockSignals(value); 
    }
}

FolderTreeWidgetItem* MainAlphaPlot::getProjectRootItem()
{
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) 
    {
        return static_cast<FolderTreeWidgetItem*>(plotExplorer->folderView->topLevelItem(0));
    }

    return nullptr;
}

QString MainAlphaPlot::getLogInfoText() const { return logInfo; }

void MainAlphaPlot::setCurrentFolderViewItem(FolderTreeWidgetItem* item)
{
    // search for the plot explorer window
    if (!this->plotExplorer)
        this->plotExplorer = getMainWindow()->findChild<Gui::PlotExplorer*>();
    // Python console found?
    if (this->plotExplorer) {
        plotExplorer->folderView->setCurrentItem(item);
    }
}

void MainAlphaPlot::clearTable()
{
    if (!isActiveSubwindow(SubWindowType::TableSubWindow))
        return;

    if (QMessageBox::question(this, tr("Warning"),
                              tr("This will clear the contents of all the data "
                                 "associated with the table. Are you sure?"),
                              tr("&Yes"), tr("&No"), QString(), 0, 1))
        return;
    else
        qobject_cast<Table*>(getactiveMyWidget())->clear();
}

/*!
   Turns perspective mode on or off
   */
void MainAlphaPlot::setCameraPresetFront()
{
    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    Layout3D* layout = qobject_cast<Layout3D*>(getactiveMyWidget());
    layout->getAbstractGraph()->scene()->activeCamera()->setCameraPreset(
        Q3DCamera::CameraPresetFront);
}

/*!
   Resets rotation of 3D plots to default values
   */
void MainAlphaPlot::resetZoomfactor()
{
    if (!isActiveSubwindow(SubWindowType::Plot3DSubWindow))
        return;
    Layout3D* layout = qobject_cast<Layout3D*>(getactiveMyWidget());
    layout->getAbstractGraph()->scene()->activeCamera()->setZoomLevel(100);
}

QString MainAlphaPlot::versionString() { return AlphaPlot::versionString(); }

MainAlphaPlot* MainAlphaPlot::loadScript(const QString& fn, bool execute)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    MainAlphaPlot* app = new MainAlphaPlot(getMainWindow());
    /*app->applyUserSettings();
     if (fn.endsWith(QString::fromLatin1(".py"), Qt::CaseInsensitive))
         app->setScriptingLang(QString::fromLatin1("Python"), false);
     else
         app->setScriptingLang(QString::fromLatin1("muParser"), false);
     app->showMaximized();
     Note* script_note = app->newNote(fn);
     script_note->importASCII(fn);
     QApplication::restoreOverrideCursor();
     if (execute) script_note->executeAll();*/
    return app;
}

void MainAlphaPlot::copyStatusBarText() { QApplication::clipboard()->setText(statusBarInfo->text()); }

void MainAlphaPlot::showStatusBarContextMenu(const QPoint& pos)
{
    QMenu cm(this);
    //cm.addAction(actionCopyStatusBarText);
    cm.exec(statusBarInfo->mapToGlobal(pos));
}

void MainAlphaPlot::showWindowMenu(MyWidget* widget)
{
    getMainWindow()->setActiveSubWindow(widget);// FIXME not user-friendly

    QMenu cm(this);
    QMenu depend_menu(this);
    if (!hidden(widget)) {
        if (isActiveSubWindow(widget, SubWindowType::TableSubWindow))
        {
            cm.addAction(Application::Instance->commandManager()
                             .getCommandByName("Std_Table_Export_ASCII")
                             ->getAction()
                             ->action());
        }

        /* else if (isActiveSubWindow(widget, SubWindowType::NoteSubWindow))
             cm.addAction(actionSaveNote);*/
        //else
            //cm.addAction(ui_->actionSaveAsTemplate);
            //cm.addAction(Application::Instance->commandManager()
            //                 .getCommandByName("Std_PrintTableMatrixGhraph")
            //                 ->getAction()
            //                 ->action());
        cm.addAction(Application::Instance->commandManager()
                         .getCommandByName("Std_DuplicateWindow")
                         ->getAction()
                         ->action());
        cm.addSeparator();
        //cm.addAction(ui_->actionCloseWindow);
        //cm.addAction(Application::Instance->commandManager()
        //                 .getCommandByName("Std_PlotHideActiveWindow")
        //                 ->getAction()
        //                 ->action());
    }
    //cm.addAction(Application::Instance->commandManager()
    //                 .getCommandByName("Std_PlotActivateWindow")
    //                 ->getAction()
    //                 ->action());
    /*if (!hidden(widget)) {
        cm.addAction(Application::Instance->commandManager()
                         .getCommandByName("Std_PlotMinimizeWindow")
                         ->getAction()
                         ->action());
        cm.addAction(Application::Instance->commandManager()
                         .getCommandByName("Std_PlotMaximizeWindow")
                         ->getAction()
                         ->action());
        cm.addSeparator();
        cm.addAction(tr("&Properties..."), this, SLOT(windowProperties()));
    }*/

    int n;
    if (isActiveSubWindow(widget, SubWindowType::TableSubWindow)) {
        QStringList graphs = dependingPlots(widget->name());
        n = graphs.count();
        if (n > 0) {
            cm.addSeparator();
            for (int i = 0; i < n; i++)
                depend_menu.addAction(graphs[i], this, SLOT(setActiveWindowFromAction()));

            depend_menu.setTitle(tr("D&epending Graphs"));
            cm.addMenu(&depend_menu);
        }
    }
    else if (isActiveSubWindow(widget, SubWindowType::MatrixSubWindow)) {
        QStringList graphs = depending3DPlots(qobject_cast<Matrix*>(widget));
        n = graphs.count();
        if (n > 0) {
            cm.addSeparator();
            for (int i = 0; i < n; i++)
                depend_menu.addAction(graphs[i], this, SLOT(setActiveWindowFromAction()));

            depend_menu.setTitle(tr("D&epending 3D Graphs"));
            cm.addMenu(&depend_menu);
        }
    }
    else if (isActiveSubWindow(widget, SubWindowType::Plot2DSubWindow)) {
        Layout2D* layout = qobject_cast<Layout2D*>(widget);
        if (layout->getCurrentAxisRect()) {
            depend_menu.setTitle(tr("D&epends on"));
            Q_FOREACH (MyWidget* widget, layout->dependentTableMatrix()) {
                depend_menu.addAction(widget->name(), this, SLOT(setActiveWindowFromAction()));
            }
            cm.addMenu(&depend_menu);
        }
    }

    else if (isActiveSubWindow(widget, SubWindowType::Plot3DSubWindow)) {
        Layout3D* layout = qobject_cast<Layout3D*>(widget);
        Matrix* matrix = nullptr;
        switch (layout->getPlotType()) {
            case Graph3DCommon::Plot3DType::Surface:
                // matrix = layout->getSurface3DModifier()->getData()->getmatrix();
                break;
            case Graph3DCommon::Plot3DType::Bar:
                // matrix = layout->getBar3DModifier()->getData()->getmatrix();
                break;
            case Graph3DCommon::Plot3DType::Scatter:
                // matrix = layout->getScatter3DModifier()->getData()->getmatrix();
                break;
        }

        QString formula;
        if (!formula.isEmpty()) {
            cm.addSeparator();
            if (formula.contains(QString::fromLatin1("_"))) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
                QStringList tl = formula.split(QString::fromLatin1("_"), Qt::SkipEmptyParts);
#else
                QStringList tl = formula.split(QString::fromLatin1("_"), QString::SkipEmptyParts);
#endif
                depend_menu.addAction(tl.at(0), this, SLOT(setActiveWindowFromAction()));
                depend_menu.setTitle(tr("D&epends on"));
                cm.addMenu(&depend_menu);
            }
            else if (matrix) {
                depend_menu.addAction(matrix->name(), this, SLOT(setActiveWindowFromAction()));
                depend_menu.setTitle(tr("D&epends on"));
                cm.addMenu(&depend_menu);
            }
        }
    }

    cm.exec(QCursor::pos());
}

void MainAlphaPlot::setActiveWindowFromAction()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action)
        activateWindow(
            qobject_cast<MyWidget*>(window(action->text().remove(QString::fromLatin1("&")))));
}

bool MainAlphaPlot::validFor3DPlot(Table* table)
{
    int ncolx = 0;
    int ncoly = 0;
    int ncolz = 0;
    int ncolunknown = 0;
    QList<Column*> selectedcols;
    QStringList list = table->selectedColumns();
    Q_FOREACH (QString colname, list)
        selectedcols << table->column(table->colIndex(colname));
    Q_FOREACH (Column* col, selectedcols) {
        if (col->plotDesignation() == AlphaPlot::PlotDesignation::X)
            ncolx++;
        else if (col->plotDesignation() == AlphaPlot::PlotDesignation::Y)
            ncoly++;
        else if (col->plotDesignation() == AlphaPlot::PlotDesignation::Z)
            ncolz++;
        else
            ncolunknown++;
    }

    if (ncolunknown > 0) {
        QMessageBox::critical(this, tr("Error (non X/Y/Z column selected)"),
                              tr("Please select X,Y & Z column(s) only for this operation!"));
        return false;
    }

    if (ncolx == 0) {
        QMessageBox::critical(this, tr("Error (no X column)"),
                              tr("Please select 1X,1Y & Z column(s) for this operation!"));
        return false;
    }

    if (ncolx > 1) {
        QMessageBox::critical(this, tr("Error (multiple X column)"),
                              tr("Please select 1X,1Y & Z column(s) for this operation!"));
        return false;
    }

    if (ncoly == 0) {
        QMessageBox::critical(this, tr("Error (no Y column)"),
                              tr("Please select 1X,1Y & Z column(s) for this operation!"));
        return false;
    }

    if (ncoly > 1) {
        QMessageBox::critical(this, tr("Error (multiple Y column)"),
                              tr("Please select 1X,1Y & Z column(s) for this operation!"));
        return false;
    }

    if (ncolz == 0) {
        QMessageBox::critical(this, tr("Error (multiple Z column)"),
                              tr("Please select 1X,1Y & 1Z column for this operation!"));
        return false;
    }

    if (ncolz > 1) {
        QMessageBox::critical(this, tr("Error (no Z column)"),
                              tr("Please select 1X,1Y & 1Z column for this operation!"));
        return false;
    }

    return true;
}

bool MainAlphaPlot::validFor2DPlot(Table* table, Graph type)
{
    switch (type) {
        case Graph::Histogram:
        case Graph::Pie:
            if (table->selectedColumnCount() < 1) {
                QMessageBox::warning(this, tr("Error"), tr("Please select a column to plot!"));
                return false;
            }
            break;
        case Graph::Box: {
            if (table->selectedColumnCount(AlphaPlot::Y) == 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select one or multiple Y column(s) to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::X) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("You can not select X column(s) for this operation!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
        } break;
        case Graph::Channel: {
            if (table->selectedColumnCount(AlphaPlot::X) != 1
                || table->selectedColumnCount(AlphaPlot::Y) != 2) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select a X & two Y column to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
        } break;
        case Graph::VerticalStackedBars:
        case Graph::HorizontalStackedBars:
        case Graph::VerticalGroupedBars:
        case Graph::HorizontalGroupedBars:
            if (table->selectedColumnCount(AlphaPlot::X) != 1
                || table->selectedColumnCount(AlphaPlot::Y) < 2) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select one X & multiple Y column(s) to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
            break;
        case Graph::ScatterYError: {
            if (table->selectedColumnCount(AlphaPlot::X) == 0
                || table->selectedColumnCount(AlphaPlot::Y) == 0
                || table->selectedColumnCount(AlphaPlot::yErr) == 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select one X, Y & yErr column to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::X) > 1
                     || table->selectedColumnCount(AlphaPlot::Y) > 1
                     || table->selectedColumnCount(AlphaPlot::yErr) > 1
                     || table->selectedColumns().count() != 3) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("You can only select one X, Y & yErr column "
                                        "for this operation!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
        } break;
        case Graph::ScatterXError: {
            if (table->selectedColumnCount(AlphaPlot::X) == 0
                || table->selectedColumnCount(AlphaPlot::Y) == 0
                || table->selectedColumnCount(AlphaPlot::xErr) == 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select one X, Y & xErr column to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::X) > 1
                     || table->selectedColumnCount(AlphaPlot::Y) > 1
                     || table->selectedColumnCount(AlphaPlot::xErr) > 1
                     || table->selectedColumns().count() != 3) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("You can only select one X, Y & xErr column "
                                        "for this operation!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
        } break;
        case Graph::ScatterXYError: {
            if (table->selectedColumnCount(AlphaPlot::X) == 0
                || table->selectedColumnCount(AlphaPlot::Y) == 0
                || table->selectedColumnCount(AlphaPlot::xErr) == 0
                || table->selectedColumnCount(AlphaPlot::yErr) == 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select one X, Y, xErr & yErr column to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::X) > 1
                     || table->selectedColumnCount(AlphaPlot::Y) > 1
                     || table->selectedColumnCount(AlphaPlot::xErr) > 1
                     || table->selectedColumnCount(AlphaPlot::yErr) > 1
                     || table->selectedColumns().count() != 4) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("You can only select one X, Y, xErr & yErr column "
                                        "for this operation!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
        } break;
        default:
            if (table->selectedColumnCount(AlphaPlot::X) == 0
                || table->selectedColumnCount(AlphaPlot::Y) == 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please select a X & Y column to plot!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::X) > 1) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("You can only select one X column for this operation!"));
                return false;
            }
            else if (table->selectedColumnCount(AlphaPlot::Z) > 0) {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Please dont select Z column for this operation!"));
                return false;
            }
            break;
    }
    // check if columns are empty
    QStringList list = table->selectedColumns();
    Q_FOREACH (QString name, list) {
        Column* col = table->column(table->colIndex(name));
        if (col->rowCount() == 0) {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Please dont select empty columns for this operation!"));
            return false;
        }
    }
    return true;
}

void MainAlphaPlot::selectPlotType(int value)
{
    if (!getactiveMyWidget())
        return;

    Graph type = static_cast<Graph>(value);
    Table* table = qobject_cast<Table*>(getactiveMyWidget());
    if (!table || !validFor2DPlot(table, type))
        return;

    int from = table->firstSelectedRow();
    int to = table->firstSelectedRow() + table->numSelectedRows() - 1;

    if (type == Graph::ScatterXError) {
        Column* xcol = nullptr;
        Column* ycol = nullptr;
        Column* xerr = nullptr;
        Layout2D* layout = newGraph2D();
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString col, list) {
            if (table->YColumns().contains(col)) {
                ycol = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::X) {
                xcol = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::xErr) {
                xerr = table->column(table->colIndex(col));
            }
        }
        layout->generateScatterWithXerror2DPlot(table, xcol, ycol, xerr, from, to);
        return;
    }
    else if (type == Graph::ScatterYError) {
        Column* xcol = nullptr;
        Column* ycol = nullptr;
        Column* yerr = nullptr;
        Layout2D* layout = newGraph2D();
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString col, list) {
            if (table->YColumns().contains(col)) {
                ycol = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::X) {
                xcol = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::yErr) {
                yerr = table->column(table->colIndex(col));
            }
        }
        layout->generateScatterWithYerror2DPlot(table, xcol, ycol, yerr, from, to);
        return;
    }
    else if (type == Graph::ScatterXYError) {
        Column* xcol = nullptr;
        Column* ycol = nullptr;
        Column* xerr = nullptr;
        Column* yerr = nullptr;
        Layout2D* layout = newGraph2D();
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString col, list) {
            if (table->YColumns().contains(col)) {
                ycol = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::X) {
                xcol = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::xErr) {
                xerr = table->column(table->colIndex(col));
            }
            else if (table->column(table->colIndex(col))->plotDesignation() == AlphaPlot::yErr) {
                yerr = table->column(table->colIndex(col));
            }
        }
        layout->generateScatterWithXYerror2DPlot(table, xcol, ycol, xerr, yerr, from, to);
        return;
    }
    else if (type == Graph::Box) {
        QList<Column*> ycollist;
        Layout2D* layout = newGraph2D();
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString colname, list)
            ycollist << table->column(table->colIndex(colname));
        layout->generateStatBox2DPlot(table, ycollist, from, to);
        return;
    }
    else if (type == Graph::Histogram) {
        QList<Column*> collist;
        Layout2D* layout = newGraph2D();
        QStringList list = table->selectedColumns();
        Q_FOREACH (QString colname, list)
            collist << table->column(table->colIndex(colname));
        layout->generateHistogram2DPlot(AxisRect2D::BarType::VerticalBars, false, table, collist,
                                        from, to);
        return;
    }

    QStringList list = table->selectedColumns();
    Column* xcol = nullptr;
    QList<Column*> ycollist;
    Q_FOREACH (QString col, list) {
        if (table->YColumns().contains(col)) {
            ycollist << table->column(table->colIndex(col));
        }
        else {
            xcol = table->column(table->colIndex(col));
        }
    }

    AlphaPlot::ColumnDataType coldatatype = ycollist.at(0)->dataType();
    Q_FOREACH (Column* col, ycollist) {
        if (col->dataType() != coldatatype) {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Please select all Y Column(s) with same "
                                    "ColumnDataType for plotting!"));
            return;
        }
    }

    if (type == Graph::Spline) {
        if (to - from < 2) {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Please select three or more rows for Spline plotting!"));
            return;
        }
    }

    Layout2D* layout = newGraph2D();
    switch (type) {
        case Graph::Scatter:
            layout->generateCurve2DPlot(AxisRect2D::LineScatterType::Scatter2D, table, xcol,
                                        ycollist, from, to);
            return;
        case Graph::Line:
            layout->generateCurve2DPlot(AxisRect2D::LineScatterType::Line2D, table, xcol, ycollist,
                                        from, to);
            return;
        case Graph::LineSymbols:
            layout->generateCurve2DPlot(AxisRect2D::LineScatterType::LineAndScatter2D, table, xcol,
                                        ycollist, from, to);
            return;
        case Graph::Spline:
            layout->generateCurve2DPlot(AxisRect2D::LineScatterType::Spline2D, table, xcol,
                                        ycollist, from, to);
            return;
        case Graph::VerticalDropLines:
            layout->generateLineSpecial2DPlot(
                AxisRect2D::LineScatterSpecialType::VerticalDropLine2D, table, xcol, ycollist, from,
                to);
            return;
        case Graph::VerticalSteps:
            layout->generateLineSpecial2DPlot(AxisRect2D::LineScatterSpecialType::VerticalStep2D,
                                              table, xcol, ycollist, from, to);
            return;
        case Graph::HorizontalSteps:
            layout->generateLineSpecial2DPlot(AxisRect2D::LineScatterSpecialType::HorizontalStep2D,
                                              table, xcol, ycollist, from, to);
            return;
        case Graph::Area:
            layout->generateLineSpecial2DPlot(AxisRect2D::LineScatterSpecialType::Area2D, table,
                                              xcol, ycollist, from, to);
            return;
        case Graph::HorizontalBars:
            layout->generateBar2DPlot(AxisRect2D::BarType::HorizontalBars, table, xcol, ycollist,
                                      from, to);
            return;
        case Graph::HorizontalStackedBars:
            layout->generateStakedBar2DPlot(AxisRect2D::BarType::HorizontalBars, table, xcol,
                                            ycollist, from, to);
            setAutoScale();
            return;
        case Graph::HorizontalGroupedBars:
            layout->generateGroupedBar2DPlot(AxisRect2D::BarType::HorizontalBars, table, xcol,
                                             ycollist, from, to);
            setAutoScale();
            return;
        case Graph::VerticalBars:
            layout->generateBar2DPlot(AxisRect2D::BarType::VerticalBars, table, xcol, ycollist,
                                      from, to);
            return;
        case Graph::VerticalStackedBars:
            layout->generateStakedBar2DPlot(AxisRect2D::BarType::VerticalBars, table, xcol,
                                            ycollist, from, to);
            setAutoScale();
            return;
        case Graph::VerticalGroupedBars:
            layout->generateGroupedBar2DPlot(AxisRect2D::BarType::VerticalBars, table, xcol,
                                             ycollist, from, to);
            setAutoScale();
            return;
        case Graph::Channel:
            layout->generateLineSpecialChannel2DPlot(table, xcol, ycollist, from, to);
            return;
        default: {
            qDebug() << "not implimented" << value;
            return;
        }
    }
}

void MainAlphaPlot::handleAspectAdded(const AbstractAspect* parent, int index)
{
    AbstractAspect* aspect = parent->child(index);

    Gui::MatrixViewProvider* matrix = qobject_cast<Gui::MatrixViewProvider*>(aspect);
    if (matrix) {
        initMatrix(static_cast<Matrix*>(matrix->view()));
        return;
    }
    Gui::TableViewProvider* table = qobject_cast<Gui::TableViewProvider*>(aspect);
    if (table) {
        initTable(static_cast<Table*>(table->view()));
        return;
    }
}

void MainAlphaPlot::handleAspectAboutToBeRemoved(const AbstractAspect* parent, int index)
{
    AbstractAspect* aspect = parent->child(index);
    Gui::MatrixViewProvider* matrix = qobject_cast<Gui::MatrixViewProvider*>(aspect);
    if (matrix) {
        closeWindow(static_cast<Matrix*>(matrix->view()));
        return;
    }
    Gui::TableViewProvider* table = qobject_cast<Gui::TableViewProvider*>(aspect);
    if (table) {
        closeWindow(static_cast<Table*>(table->view()));
        return;
    }
}

void MainAlphaPlot::showUndoRedoHistory()
{
    if (!d_project->undoStack())
        return;
    QDialog dialog;
    QVBoxLayout layout(&dialog);

    QDialogButtonBox button_box;
    button_box.setOrientation(Qt::Horizontal);
    button_box.setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::NoButton
                                  | QDialogButtonBox::Ok);
    QObject::connect(&button_box, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&button_box, SIGNAL(rejected()), &dialog, SLOT(reject()));

    int index = d_project->undoStack()->index();
    QUndoView undo_view(d_project->undoStack());

    layout.addWidget(&undo_view);
    layout.addWidget(&button_box);

    dialog.setWindowTitle(tr("Undo/Redo History"));
    if (dialog.exec() == QDialog::Accepted)
        return;

    d_project->undoStack()->setIndex(index);
}

QStringList MainAlphaPlot::tableWindows()
{
    QList<AbstractAspect*> tables = d_project->descendantsThatInherit("Gui::TableViewProvider");
    QStringList result;
    Q_FOREACH (AbstractAspect* aspect, tables)
        result.append(aspect->name());
    return result;
}

void MainAlphaPlot::loadIcons()
{
    // ui_->statusBar->setStyleSheet(
    //    "QStatusBar { background-color: #ff8633; color: white }");
    // File menu
    //ui_->actionNewProject->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-new"), IconLoader::LightDark));
    //ui_->actionNewGraph->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-graph"), IconLoader::LightDark));
    //ui_->actionNewNote->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-note"), IconLoader::LightDark));
    //ui_->actionNewTable->setIcon(
    //    IconLoader::load(QString::fromLatin1("table"), IconLoader::LightDark));
    //ui_->actionNewMatrix->setIcon(
    //    IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark));
    //ui_->actionNewFunctionPlot->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-function-xy"), IconLoader::LightDark));
    //ui_->actionNew3DSurfacePlot->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-function-xyz"), IconLoader::LightDark));
    //ui_->actionOpenAproj->setIcon(
    //    IconLoader::load(QString::fromLatin1("project-open"), IconLoader::LightDark));
    //ui_->actionOpenImage->setIcon(QIcon());
    //ui_->actionImportImage->setIcon(
    //    IconLoader::load(QString::fromLatin1("view-image"), IconLoader::LightDark));
    //ui_->actionSaveProject->setIcon(
    //    IconLoader::load(QString::fromLatin1("document-save"), IconLoader::LightDark));
    //ui_->actionSaveProjectAs->setIcon(QIcon());
    //ui_->actionOpenTemplate->setIcon(
    //    IconLoader::load(QString::fromLatin1("template-open"), IconLoader::LightDark));
    //ui_->actionSaveAsTemplate->setIcon(
    //    IconLoader::load(QString::fromLatin1("template-save"), IconLoader::LightDark));
    //ui_->actionExportCurrentGraph->setIcon(QIcon());
    //ui_->actionExportAllGraphs->setIcon(QIcon());
    //ui_->actionPrint->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-print"), IconLoader::LightDark));
    //ui_->actionPrintAllPlots->setIcon(QIcon());
    //ui_->actionExportASCII->setIcon(QIcon());
    //ui_->actionImportASCII->setIcon(
    //    IconLoader::load(QString::fromLatin1("import-ascii-filter"), IconLoader::LightDark));
    //ui_->actionQuit->setIcon(
    //    IconLoader::load(QString::fromLatin1("application-exit"), IconLoader::General));
    //// Edit menu
    //ui_->actionUndo->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-undo"), IconLoader::LightDark));
    //ui_->actionRedo->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-redo"), IconLoader::LightDark));
    //ui_->actionCutSelection->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-cut"), IconLoader::LightDark));
    //ui_->actionCopySelection->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-copy"), IconLoader::LightDark));
    //ui_->actionPasteSelection->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-paste"), IconLoader::LightDark));
    //ui_->actionClearSelection->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-delete-selection"), IconLoader::LightDark));
    //ui_->actionDeleteFitTables->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-delete"), IconLoader::General));
    //ui_->actionClearLogInfo->setIcon(
    //    IconLoader::load(QString::fromLatin1("clear-loginfo"), IconLoader::General));
    //ui_->actionPreferences->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-preference"), IconLoader::LightDark));
    //// View menu
    //ui_->actionPlotWizard->setIcon(
    //    IconLoader::load(QString::fromLatin1("tools-wizard"), IconLoader::LightDark));
    //ui_->actionShowUndoRedoHistory->setIcon(QIcon());
    //(fileToolbar->isMovable())
    //    ? ui_->actionLockToolbars->setIcon(
    //        IconLoader::load(QString::fromLatin1("unlock"), IconLoader::LightDark))
    //    : ui_->actionLockToolbars->setIcon(
    //        IconLoader::load(QString::fromLatin1("lock"), IconLoader::LightDark));
    //actionShowProjectExplorer->setIcon(
    //    IconLoader::load(QString::fromLatin1("folder-explorer"), IconLoader::LightDark));
    //actionShowResultsLog->setIcon(
    //    IconLoader::load(QString::fromLatin1("view-console"), IconLoader::LightDark));
    //actionShowConsole->setIcon(QIcon());
    //// Scripting menu
    //ui_->actionScriptingLanguage->setIcon(QIcon());
    //ui_->actionRestartScripting->setIcon(QIcon());
    //ui_->actionExecute->setIcon(QIcon());
    //ui_->actionExecuteAll->setIcon(QIcon());
    //ui_->actionEvaluateExpression->setIcon(QIcon());
    //// Plot menu
    //ui_->actionPlot2DLine->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-line"), IconLoader::LightDark));
    //ui_->menuPlot2DScatter->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-scatter"), IconLoader::LightDark));
    //ui_->actionPlot2DScatter->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-scatter"), IconLoader::LightDark));
    //ui_->actionPlot2DLineSymbol->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-line-scatter"), IconLoader::LightDark));
    //ui_->actionPlot2DVerticalDropLines->setIcon(
    //    QIcon(IconLoader::load(QString::fromLatin1("graph2d-vertical-drop"), IconLoader::LightDark)));
    //ui_->actionPlot2DSpline->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-spline"), IconLoader::LightDark));
    //ui_->actionPlot2DVerticalSteps->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vertical-step"), IconLoader::LightDark));
    //ui_->actionPlot2DHorizontalSteps->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-horizontal-step"), IconLoader::LightDark));
    //ui_->actionPlot2DVerticalBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vertical-bar"), IconLoader::LightDark));
    //ui_->actionPlot2DVerticalStackedBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vertical-stack-bar"), IconLoader::LightDark));
    //ui_->actionPlot2DVerticalGroupedBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vertical-group-bar"), IconLoader::LightDark));
    //ui_->actionPlot2DHorizontalBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-horizontal-bar"), IconLoader::LightDark));
    //ui_->actionPlot2DHorizontalStackedBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-horizontal-stack-bar"), IconLoader::LightDark));
    //ui_->actionPlot2DHorizontalGroupedBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-horizontal-group-bar"), IconLoader::LightDark));
    //ui_->actionPlot2DArea->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-area"), IconLoader::LightDark));
    //ui_->actionPlot2DChannelFill->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-channel"), IconLoader::LightDark));
    //ui_->actionPlot2DPie->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-pie"), IconLoader::LightDark));
    //ui_->actionPlot2DHalfPie->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-halfpie"), IconLoader::LightDark));
    //ui_->actionPlot2DVectorsXYAM->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vector-xyam"), IconLoader::LightDark));
    //ui_->actionPlot2DVectorsXYXY->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vector-xy"), IconLoader::LightDark));
    //ui_->actionPlot2DStatBox->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-box"), IconLoader::LightDark));
    //ui_->actionPlot2DStatHistogram->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-histogram"), IconLoader::LightDark));
    //ui_->actionPlot2DStatStackedHistogram->setIcon(QIcon(QPixmap()));
    //ui_->actionPanelVertical2Layouts->setIcon(QIcon(QPixmap()));
    //ui_->actionPanelHorizontal2Layouts->setIcon(QIcon(QPixmap()));
    //ui_->actionPanel4Layouts->setIcon(QIcon(QPixmap()));
    //ui_->actionPlot3DRibbon->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-ribbon"), IconLoader::LightDark));
    //ui_->actionPlot3DBar->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-bar"), IconLoader::LightDark));
    //ui_->actionPlot3DScatter->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-scatter"), IconLoader::LightDark));
    //ui_->actionPlot3DTrajectory->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-trajectory"), IconLoader::LightDark));
    //// 3D Plot menu
    //ui_->action3DWireFrame->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-hidden-line"), IconLoader::LightDark));
    //ui_->action3DSurface->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-ribbon"), IconLoader::LightDark));
    //ui_->action3DWireSurface->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-polygon-mesh"), IconLoader::LightDark));
    //ui_->action3DBar->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-bar"), IconLoader::LightDark));
    //ui_->action3DScatter->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-scatter"), IconLoader::LightDark));
    //ui_->action3DCountourColorFill->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-colormap3d"), IconLoader::General));
    //ui_->action3DCountourLines->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-contour3d"), IconLoader::General));
    //ui_->action3DGreyScaleMap->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-graymap3d"), IconLoader::General));
    //// Graph menu
    //ui_->actionAddRemoveCurve->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-add-graph"), IconLoader::LightDark));
    //ui_->actionAddErrorBars->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph-y-error"), IconLoader::LightDark));
    //ui_->actionAddFunctionCurve->setIcon(
    //    IconLoader::load(QString::fromLatin1("math-fofx"), IconLoader::LightDark));
    //ui_->menuAddAxis->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left"), IconLoader::LightDark));
    //ui_->menuAddTopAxis->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top"), IconLoader::LightDark));
    //ui_->menuAddBottomAxis->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom"), IconLoader::LightDark));
    //ui_->menuAddLeftAxis->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left"), IconLoader::LightDark));
    //ui_->menuAddRightAxis->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right"), IconLoader::LightDark));
    //ui_->actionLeftValue->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left-value"), IconLoader::LightDark));
    //ui_->actionLeftLog->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left-log"), IconLoader::LightDark));
    //ui_->actionLeftPi->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left-symbol"), IconLoader::LightDark));
    //ui_->actionLeftText->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left-text"), IconLoader::LightDark));
    //ui_->actionLeftTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left-time"), IconLoader::LightDark));
    //ui_->actionLeftDateTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-left-datetime"), IconLoader::LightDark));
    //ui_->actionTopValue->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top-value"), IconLoader::LightDark));
    //ui_->actionTopLog->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top-log"), IconLoader::LightDark));
    //ui_->actionTopPi->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top-symbol"), IconLoader::LightDark));
    //ui_->actionTopText->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top-text"), IconLoader::LightDark));
    //ui_->actionTopTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top-time"), IconLoader::LightDark));
    //ui_->actionTopDateTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-top-datetime"), IconLoader::LightDark));
    //ui_->actionBottomValue->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-value"), IconLoader::LightDark));
    //ui_->actionBottomLog->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-log"), IconLoader::LightDark));
    //ui_->actionBottomPi->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-symbol"), IconLoader::LightDark));
    //ui_->actionBottomText->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-text"), IconLoader::LightDark));
    //ui_->actionBottomTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-time"), IconLoader::LightDark));
    //ui_->actionBottomDateTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-bottom-datetime"), IconLoader::LightDark));
    //ui_->actionRightValue->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right-value"), IconLoader::LightDark));
    //ui_->actionRightLog->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right-log"), IconLoader::LightDark));
    //ui_->actionRightPi->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right-symbol"), IconLoader::LightDark));
    //ui_->actionRightText->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right-text"), IconLoader::LightDark));
    //ui_->actionRightTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right-time"), IconLoader::LightDark));
    //ui_->actionRightDateTime->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-axis-right-datetime"), IconLoader::LightDark));
    //ui_->actionLegendReorder->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-legend"), IconLoader::LightDark));
    //ui_->actionAddText->setIcon(
    //    IconLoader::load(QString::fromLatin1("draw-text"), IconLoader::LightDark));
    //ui_->actionDrawArrow->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-arrow"), IconLoader::LightDark));
    //ui_->actionDrawLine->setIcon(
    //    IconLoader::load(QString::fromLatin1("draw-line"), IconLoader::LightDark));
    //ui_->actionAddTimeStamp->setIcon(
    //    IconLoader::load(QString::fromLatin1("clock"), IconLoader::LightDark));
    //ui_->actionAddImage->setIcon(
    //    IconLoader::load(QString::fromLatin1("view-image"), IconLoader::LightDark));
    //ui_->actionAddNestedLayout->setIcon(
    //    IconLoader::load(QString::fromLatin1("auto-layout"), IconLoader::LightDark));
    //ui_->menuAddLayout->setIcon(
    //    IconLoader::load(QString::fromLatin1("layer-new"), IconLoader::LightDark));
    //ui_->actionAddLayoutUp->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-up"), IconLoader::LightDark));
    //ui_->actionAddLayoutDown->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-down"), IconLoader::LightDark));
    //ui_->actionAddLayoutLeft->setIcon(
    //    IconLoader::load(QString::fromLatin1("go-previous"), IconLoader::LightDark));
    //ui_->actionAddLayoutRight->setIcon(
    //    IconLoader::load(QString::fromLatin1("go-next"), IconLoader::LightDark));
    //ui_->actionRemoveLayout->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-delete-selection"), IconLoader::LightDark));
    //ui_->actionArrangeLayout->setIcon(
    //    IconLoader::load(QString::fromLatin1("layer-arrange"), IconLoader::LightDark));
    //// Tools menu
    //ui_->actionDisableGraphTools->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-select"), IconLoader::LightDark));
    //ui_->actionGraphRescaleShowAll->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph-unzoom"), IconLoader::LightDark));
    //ui_->actionGraphDragRange->setIcon(
    //    IconLoader::load(QString::fromLatin1("drag-move"), IconLoader::LightDark));
    //ui_->actionGraphZoomRange->setIcon(
    //    IconLoader::load(QString::fromLatin1("zoom-in"), IconLoader::LightDark));
    //ui_->actionGraphScreenReader->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-crosshair"), IconLoader::LightDark));
    //ui_->actionGraphDataReader->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-select-data"), IconLoader::LightDark));
    //ui_->actionGraphSelectDataRange->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-data-range"), IconLoader::LightDark));
    //ui_->actionGraphMoveDataPoints->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-hand"), IconLoader::LightDark));
    //ui_->actionGraphRemoveBadDataPoints->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-erasor"), IconLoader::LightDark));
    //// Table Analysis menu
    //ui_->actionStatisticsOnColumns->setIcon(
    //    IconLoader::load(QString::fromLatin1("table-column-sum"), IconLoader::LightDark));
    //ui_->actionStatisticsOnRows->setIcon(
    //    IconLoader::load(QString::fromLatin1("table-row-sum"), IconLoader::LightDark));
    //ui_->actionTableFFT->setIcon(QIcon());
    //ui_->actionCorrelate->setIcon(QIcon());
    //ui_->actionAutocorrelate->setIcon(QIcon());
    //ui_->actionConvolute->setIcon(QIcon());
    //ui_->actionDeconvolute->setIcon(QIcon());
    //// Graph Analysis menu
    //ui_->actionHorizontalTranslate->setIcon(QIcon());
    //ui_->actionVerticalTranslate->setIcon(QIcon());
    //ui_->actionDifferentiate->setIcon(QIcon());
    //ui_->actionIntegrate->setIcon(QIcon());
    //ui_->actionSavitzkySmooth->setIcon(QIcon());
    //ui_->actionMovingWindowAverageSmooth->setIcon(QIcon());
    //ui_->actionFFTFilterSmooth->setIcon(QIcon());
    //ui_->actionLowPassFFTFilter->setIcon(QIcon());
    //ui_->actionHighPassFFTFilter->setIcon(QIcon());
    //ui_->actionBandPassFFTFilter->setIcon(QIcon());
    //ui_->actionBandBlockFFTFilter->setIcon(QIcon());
    //ui_->actionInterpolate->setIcon(QIcon());
    //ui_->actionGraph2DFFT->setIcon(QIcon());
    //ui_->actionFitLinear->setIcon(QIcon());
    //ui_->actionFitPolynomial->setIcon(QIcon());
    //ui_->actionFirstOrderExponentialDecay->setIcon(QIcon());
    //ui_->actionSecondOrderExponentialDecay->setIcon(QIcon());
    //ui_->actionThirdOrderExponentialDecay->setIcon(QIcon());
    //ui_->actionFitExponentialGrowth->setIcon(QIcon());
    //ui_->actionFitBoltzmannSigmoid->setIcon(QIcon());
    //ui_->actionFitGaussian->setIcon(QIcon());
    //ui_->actionFitLorentzian->setIcon(QIcon());
    //ui_->actionMultiPeakGaussian->setIcon(QIcon());
    //ui_->actionMultiPeakLorentzian->setIcon(QIcon());
    //ui_->actionGraph2DFitWizard->setIcon(QIcon());
    //// Windows menu
    //ui_->actionCascadeWindow->setIcon(QIcon());
    //ui_->actionTileWindow->setIcon(QIcon());
    //ui_->actionNextWindow->setIcon(
    //    IconLoader::load(QString::fromLatin1("go-next"), IconLoader::LightDark));
    //ui_->actionPreviousWindow->setIcon(
    //    IconLoader::load(QString::fromLatin1("go-previous"), IconLoader::LightDark));
    //ui_->actionDuplicateWindow->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-duplicate"), IconLoader::LightDark));
    //ui_->actionHideWindow->setIcon(QIcon());
    //ui_->actionCloseWindow->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-delete"), IconLoader::General));
    //// Help menu
    //ui_->actionHelp->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-help"), IconLoader::LightDark));
    //ui_->actionChooseHelpFolder->setIcon(QIcon());
    //ui_->actionHomepage->setIcon(
    //    IconLoader::load(QString::fromLatin1("go-home"), IconLoader::LightDark));
    //ui_->actionCheckUpdates->setIcon(QIcon());
    //ui_->actionDownloadManual->setIcon(QIcon());
    //ui_->actionUserDocumentation->setIcon(
    //    IconLoader::load(QString::fromLatin1("internet - web - browser.svg"), IconLoader::General));
    //ui_->actionVisitForum->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-help-forum"), IconLoader::LightDark));
    //ui_->actionReportBug->setIcon(
    //    IconLoader::load(QString::fromLatin1("tools-report-bug"), IconLoader::LightDark));
    //ui_->actionAbout->setIcon(
    //    IconLoader::load(QString::fromLatin1("help-about"), IconLoader::LightDark));
    //// Toolbutton
    //btn_new_aspect_->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-new-aspect"), IconLoader::LightDark));
    //btn_layout_->setIcon(
    //    IconLoader::load(QString::fromLatin1("layer-arrange"), IconLoader::LightDark));
    //btn_curves_->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-add-graph"), IconLoader::LightDark));
    //btn_plot_enrichments_->setIcon(
    //    IconLoader::load(QString::fromLatin1("draw-text"), IconLoader::LightDark));
    //btn_plot_scatters_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-scatter"), IconLoader::LightDark));
    //btn_plot_linespoints_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-line-scatter"), IconLoader::LightDark));
    //btn_plot_bars_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vertical-bar"), IconLoader::LightDark));
    //btn_plot_vect_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-vector-xyam"), IconLoader::LightDark));
    //btn_plot_pie_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph2d-pie"), IconLoader::LightDark));
    //// 3d toolbars
    //actionplot3dmodecolumnselect_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-column-slice"), IconLoader::LightDark));
    //actionplot3dmoderowselect_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-row-slice"), IconLoader::LightDark));
    //actionplot3dmodeitemselect_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-select-item"), IconLoader::LightDark));
    //actionplot3dmodenoneselect_->setIcon(
    //    IconLoader::load(QString::fromLatin1("list-remove"), IconLoader::General));
    //actionResetCameraFront_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-reset-rotation"), IconLoader::LightDark));
    //actionResetZoomfactor_->setIcon(
    //    IconLoader::load(QString::fromLatin1("graph3d-perspective-view"), IconLoader::LightDark));
    //actionplot3dAnimate_->setIcon(
    //    IconLoader::load(QString::fromLatin1("view-3dplot-movie"), IconLoader::LightDark));
    //// non menu qaction icons
    //actionExportPDF->setIcon(
    //    IconLoader::load(QString::fromLatin1("application-pdf"), IconLoader::LightDark));
    //actionPixelLineProfile->setIcon(QIcon(QPixmap()));
    //actionPrintWindow->setIcon(
    //    IconLoader::load(QString::fromLatin1("edit-print"), IconLoader::LightDark));

    //Q_FOREACH(QMdiSubWindow * subwindow, subWindowsList()) {
    //    QList<QTreeWidgetItem*> items = ui_->listView->findItems(
    //        qobject_cast<MyWidget*>(subwindow)->name(), Qt::MatchExactly, 0);
    //    if (isActiveSubWindow(subwindow, SubWindowType::TableSubWindow)) {
    //        Table* table = qobject_cast<Table*>(subwindow);
    //        if (items.count() > 0)
    //            items.at(0)->setIcon(0,
    //                IconLoader::load(QString::fromLatin1("table"), IconLoader::LightDark));
    //        table->setWindowIcon(IconLoader::load(QString::fromLatin1("table"), IconLoader::LightDark));
    //        table->d_future_table->loadIcons();
    //    }
    //    else if (isActiveSubWindow(subwindow, SubWindowType::MatrixSubWindow)) {
    //        Matrix* matrix = qobject_cast<Matrix*>(subwindow);
    //        if (items.count() > 0)
    //            items.at(0)->setIcon(0,
    //                IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark));
    //        matrix->setWindowIcon(IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark));
    //        matrix->d_future_matrix->loadIcons();
    //    }
    //    /*else if (isActiveSubWindow(subwindow, SubWindowType::NoteSubWindow)) {
    //        Note* note = qobject_cast<Note*>(subwindow);
    //        if (items.count() > 0)
    //            items.at(0)->setIcon(
    //                0, IconLoader::load(QString::fromLatin1("edit-note"), IconLoader::LightDark));
    //        note->setWindowIcon(IconLoader::load(QString::fromLatin1("edit-note"), IconLoader::LightDark));
    //    }*/
    //    else if (isActiveSubWindow(subwindow, SubWindowType::Plot2DSubWindow)) {
    //        Layout2D* layout = qobject_cast<Layout2D*>(subwindow);
    //        if (items.count() > 0)
    //            items.at(0)->setIcon(
    //                0, IconLoader::load(QString::fromLatin1("edit-graph"), IconLoader::LightDark));
    //        layout->setWindowIcon(
    //            IconLoader::load(QString::fromLatin1("edit-graph"), IconLoader::LightDark));
    //        layout->loadIcons();
    //    }
    //    else if (isActiveSubWindow(subwindow, SubWindowType::Plot3DSubWindow)) {
    //        Layout3D* graph = qobject_cast<Layout3D*>(subwindow);
    //        if (items.count() > 0)
    //            items.at(0)->setIcon(
    //                0, IconLoader::load(QString::fromLatin1("edit-graph3d"), IconLoader::LightDark));
    //        graph->setWindowIcon(
    //            IconLoader::load(QString::fromLatin1("edit-graph3d"), IconLoader::LightDark));
    //    }
    //}
}

bool MainAlphaPlot::isActiveSubwindow(const MainAlphaPlot::SubWindowType& subwindowtype)
{
    bool result = false;
    if (getactiveMyWidget()) {
        switch (subwindowtype) {
            case TableSubWindow:
                (qobject_cast<Table*>(getactiveMyWidget())) ? result = true
                                                                      : result = false;
                break;
            case MatrixSubWindow:
                (qobject_cast<Matrix*>(getactiveMyWidget())) ? result = true
                                                                       : result = false;
                break;
            /*case NoteSubWindow:
             (qobject_cast<Note*>(getactiveMyWidget())) ? result = true
                 : result = false;
             break;*/
            case Plot2DSubWindow:
                (qobject_cast<Layout2D*>(getactiveMyWidget())) ? result = true
                                                                         : result = false;
                break;
            case Plot3DSubWindow:
                (qobject_cast<Layout3D*>(getactiveMyWidget())) ? result = true
                                                                         : result = false;
                break;
        }
    }
    return result;
}

bool MainAlphaPlot::isActiveSubWindow(QMdiSubWindow* subwindow,
                                   const MainAlphaPlot::SubWindowType& subwindowtype)
{
    bool result = false;
    if (subwindow) {
        switch (subwindowtype) {
            case TableSubWindow:
                (qobject_cast<Table*>(subwindow)) ? result = true : result = false;
                break;
            case MatrixSubWindow:
                (qobject_cast<Matrix*>(subwindow)) ? result = true : result = false;
                break;
                /* case NoteSubWindow:
             (qobject_cast<Note*>(subwindow)) ? result = true : result = false;
             break;*/
            case Plot2DSubWindow:
                (qobject_cast<Layout2D*>(subwindow)) ? result = true : result = false;
                break;
            case Plot3DSubWindow:
                (qobject_cast<Layout3D*>(subwindow)) ? result = true : result = false;
                break;
        }
    }
    return result;
}

//----------------------------scripting related code---------------------------
void MainAlphaPlot::attachQtScript()
{
    //// pass mainwindow as global object
    //QScriptValue objectValue = consoleWindow->engine->newQObject(this);
    //consoleWindow->engine->globalObject().setProperty("Alpha", objectValue);

    //QScriptValue clearFunction = consoleWindow->engine->newFunction(&openProj);
    //clearFunction.setData(objectValue);
    //consoleWindow->engine->globalObject().setProperty("openAproj", clearFunction);

    //qScriptRegisterMetaType<Table *>(consoleWindow->engine,
    //                                 tableObjectToScriptValue,
    //                                 tableObjectFromScriptValue);
    //qScriptRegisterMetaType<Note *>(consoleWindow->engine,
    //                                tableObjectToScriptValue,
    //                                tableObjectFromScriptValue);
    //qScriptRegisterMetaType<Matrix *>(consoleWindow->engine,
    //                                  tableObjectToScriptValue,
    //                                  tableObjectFromScriptValue);
    //qScriptRegisterMetaType<Column *>(consoleWindow->engine,
    //                                  tableObjectToScriptValue,
    //                                  tableObjectFromScriptValue);
    //qScriptRegisterMetaType<QVector<int>>(consoleWindow->engine, toScriptValue,
    //                                      fromScriptValue);
    //qScriptRegisterMetaType<QVector<float>>(consoleWindow->engine, toScriptValue,
    //                                        fromScriptValue);
    //qScriptRegisterMetaType<QVector<double>>(consoleWindow->engine, toScriptValue,
    //                                         fromScriptValue);
    //qScriptRegisterMetaType<QVector<long>>(consoleWindow->engine, toScriptValue,
    //                                       fromScriptValue);
    //qScriptRegisterMetaType<QVector<QString>>(consoleWindow->engine,
    //                                          toScriptValue, fromScriptValue);
    //qScriptRegisterMetaType<QVector<QDate>>(consoleWindow->engine, toScriptValue,
    //                                        fromScriptValue);
    //qScriptRegisterMetaType<QVector<QDateTime>>(consoleWindow->engine,
    //                                            toScriptValue, fromScriptValue);
}

bool MainAlphaPlot::isActiveSubWindowAGraph()
{
    // bool result = false;
    // if (getactiveMyWidget()) {
    //     (qobject_cast<Layout2D*>(getactiveMyWidget())) ? result = true : result = false;
    // }

    // return result;

     return (isActiveSubWindow(getactiveMyWidget(), SubWindowType::Plot2DSubWindow));
}
bool MainAlphaPlot::isActiveSubWindowA3DPlot()
{
    return (isActiveSubWindow(getactiveMyWidget(), SubWindowType::Plot3DSubWindow));
    //return true;
}
bool MainAlphaPlot::isActiveSubWindowAScene()
{
    return (isActiveSubWindow(getactiveMyWidget(), SubWindowType::SceneSubWindow));
    //return true;
}

bool MainAlphaPlot::isActiveSubWindowATable()
{
    return (isActiveSubWindow(getactiveMyWidget(), SubWindowType::TableSubWindow));
    //return true;
}
bool MainAlphaPlot::isActiveSubWindowAMatrix()
{
    return (isActiveSubWindow(getactiveMyWidget(), SubWindowType::MatrixSubWindow));
    //return true;
}

void MainAlphaPlot::convertTableToEigenMatrix(Table* table, mat& eigenMatrix)
{
    eigenMatrix.resize(table->numRows(), table->numCols());

    for (int i = 0; i < table->numRows(); i++) {
        for (int j = 0; j < table->numCols(); j++) {
            eigenMatrix(i, j) = table->cell(i, j);
        }
    }
}
void MainAlphaPlot::convertMatrixToEigenMatrix(Matrix* matrix, mat& eigenMatrix)
{
    eigenMatrix.resize(matrix->numRows(), matrix->numCols());

    for (int i = 0; i < matrix->numRows(); i++) {
        for (int j = 0; j < matrix->numCols(); j++) {
            eigenMatrix(i, j) = matrix->cell(i, j);
        }
    }
}

Matrix* MainAlphaPlot::getActiveMatrix() 
{
    if (isActiveSubWindowAMatrix())
    {
        Matrix* matrix = qobject_cast<Matrix*>(getactiveMyWidget());
        return matrix;
    }

    return nullptr;
}

void MainAlphaPlot::getActiveMatrixAsEigenMatrix(mat& matrix)
{
    Matrix* AplaPlotMatrix = getActiveMatrix();
    convertMatrixToEigenMatrix(AplaPlotMatrix, matrix);
}

Table* MainAlphaPlot::getActiveTable()
{
    if (isActiveSubWindowATable()) {
        Table* table = qobject_cast<Table*>(getactiveMyWidget());
        return table;
    }

    return nullptr;
}

void MainAlphaPlot::getActiveTableAsEigenMatrix(mat& matrix)
{
    Table* AplaPlotTable = getActiveTable();
    convertTableToEigenMatrix(AplaPlotTable, matrix);
}

Table* MainAlphaPlot::getTableByName(QString tableName)
{
  Table *table = nullptr;
    if (!aprojhandler_)
        return nullptr;

  QList<Table*> tabs = aprojhandler_->tables(this);
  Q_FOREACH (Table *tab, tabs) {
      if (tab->name() == tableName)
      {
          return tab;
      }
  }
  return table;
}

Matrix* MainAlphaPlot::getMatrixByName(QString matrixName) {
  Matrix *matrix = nullptr;
    if (!aprojhandler_)
        return nullptr;

  QList<Matrix*> mats = aprojhandler_->matrixs(this);
    Q_FOREACH (Matrix* mat, mats) {
      if (mat->name() == matrixName)
      {
            return mat;
      }
  }
  return matrix;
}