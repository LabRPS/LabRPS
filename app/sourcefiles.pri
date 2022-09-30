#############################################################################
###################### PROJECT FILES SECTION ################################
#############################################################################

###################### HEADERS ##############################################

HEADERS  += src/ApplicationWindow.h \
            src/core/AppearanceManager.h \
            src/core/IconLoader.h \
            src/core/Utilities.h \
            src/core/propertybrowser/ObjectBrowserTreeItem.h \
            src/core/propertybrowser/ObjectBrowserTreeItemModel.h \
            src/core/propertybrowser/MyTreeWidget.h \
            src/core/propertybrowser/DummyWindow.h \
            src/core/propertybrowser/propertyeditor.h \
            src/core/propertybrowser/propertybrowser.h \
            src/core/propertybrowser/pluginpropertyeditor.h \
            src/core/propertybrowser/pluginpropertybrowser.h \            
            src/widgets/ColorLabel.h \
            src/globals.h\
            src/scripting/MuParserScript.h \
            src/scripting/MuParserScripting.h \
            src/scripting/ScriptingFunctions.h\
            src/scripting/MyParser.h \
            src/Table.h \
            src/PlotWizard.h \
            src/Matrix.h \
            src/DataSetDialog.h \
            src/ColorBox.h \
            src/PatternBox.h \
            src/ColorButton.h \
            src/AssociationsDialog.h \
            src/MyWidget.h \
            src/ImportASCIIDialog.h \
            src/ImageExportDlg.h\
            src/analysis/FilterDialog.h\
            src/analysis/FFTDialog.h\
            src/Note.h\
            src/Folder.h\
            src/FindDialog.h\
            src/scripting/ScriptingEnv.h\
            src/scripting/Script.h\
            src/scripting/ScriptEdit.h\
            src/scripting/customevents.h\
            src/scripting/ScriptingLangDialog.h\
            src/TextFormatButtons.h\
            src/TableStatistics.h\
            src/analysis/Filter.h\
            src/analysis/FFTFilter.h\
            src/analysis/FFT.h\
            src/analysis/Convolution.h\
            src/analysis/Correlation.h\
            src/analysis/Differentiation.h\
            src/analysis/Integration.h\
            src/analysis/IntDialog.h\
            src/analysis/Interpolation.h\
            src/analysis/InterpolationDialog.h\
            src/analysis/SmoothFilter.h\
            src/analysis/SmoothCurveDialog.h\
            src/analysis/Fit.h\
            src/analysis/fit_gsl.h\
            src/analysis/PolynomialFit.h\
            src/analysis/PolynomFitDialog.h\
            src/analysis/ExponentialFit.h\
            src/analysis/ExpDecayDialog.h\
            src/analysis/SigmoidalFit.h\
            src/analysis/PluginFit.h\
            src/analysis/MultiPeakFit.h\
            src/analysis/MultiPeakFitTool.h\
            src/analysis/NonLinearFit.h\
            src/analysis/FitDialog.h\
            src/OpenProjectDialog.h\
            src/TeXTableSettings.h \
            src/TeXTableSettingsWidget.h \
            src/TeXTableExportDialog.h \
            src/scripting/widgets/Console.h \
            src/scripting/widgets/ConsoleWidget.h \
            src/scripting/SyntaxHighlighter.h \
            src/widgets/aSettingsListView.h \
            src/widgets/CharacterWidget.h \
            src/widgets/CustomCharacterDialog.h \
            src/ui/CharacterMapWidget.h \
            src/ui/ExportDialog.h \
            src/ui/ExtensibleFileDialog.h \
            src/ui/GeneralApplicationSettings.h \
            src/ui/GeneralAppreanceSettings.h \
            src/ui/GeneralConfirmationSettings.h \
            src/ui/SettingsPage.h \
            src/ui/SettingsDialog.h \
            src/ui/PropertiesDialog.h \
            src/ui/RandomDistributionDialog.h \
            src/ui/FittingSettings.h \
            src/ui/GeneralNumericFormatSettings.h \
            src/ui/TableBasicSettings.h \
            src/ui/TableColorSettings.h \
            src/ui/TableFontSettings.h \
            src/About.h \
            src/core/AprojHandler.h \
            src/future/lib/XmlStreamWriter.h \


###################### SOURCES ##############################################

SOURCES  += src/ApplicationWindow.cpp \
            src/core/AppearanceManager.cpp \
            src/core/IconLoader.cpp \
            src/core/Utilities.cpp \
            src/core/propertybrowser/ObjectBrowserTreeItem.cpp \
            src/core/propertybrowser/ObjectBrowserTreeItemModel.cpp \
            src/core/propertybrowser/MyTreeWidget.cpp \
            src/core/propertybrowser/DummyWindow.cpp \
            src/core/propertybrowser/propertyeditor.cpp \
            src/core/propertybrowser/propertybrowser.cpp \
            src/core/propertybrowser/pluginpropertyeditor.cpp \
            src/core/propertybrowser/pluginpropertybrowser.cpp \            
            src/widgets/ColorLabel.cpp \
            src/scripting/MuParserScript.cpp \
            src/scripting/MuParserScripting.cpp \
            src/scripting/MyParser.cpp\
            src/Table.cpp \
            src/PlotWizard.cpp \
            src/DataSetDialog.cpp \
            src/Matrix.cpp \
            src/ColorBox.cpp \
            src/PatternBox.cpp \
            src/ColorButton.cpp \
            src/AssociationsDialog.cpp \
            src/MyWidget.cpp\
            src/analysis/FilterDialog.cpp\
            src/analysis/FFTDialog.cpp\
            src/Note.cpp\
            src/Folder.cpp\
            src/FindDialog.cpp\
            src/TextFormatButtons.cpp\
            src/scripting/ScriptEdit.cpp\
            src/ImportASCIIDialog.cpp\
            src/ImageExportDlg.cpp\
            src/scripting/ScriptingFunctions.cpp\
            src/scripting/ScriptingEnv.cpp\
            src/scripting/Script.cpp\
            src/scripting/ScriptingLangDialog.cpp\
            src/TableStatistics.cpp\
            src/analysis/Filter.cpp\
            src/analysis/FFTFilter.cpp\
            src/analysis/FFT.cpp\
            src/analysis/Convolution.cpp\
            src/analysis/Correlation.cpp\
            src/analysis/Differentiation.cpp\
            src/analysis/Integration.cpp\
            src/analysis/IntDialog.cpp\
            src/analysis/Interpolation.cpp\
            src/analysis/InterpolationDialog.cpp\
            src/analysis/SmoothFilter.cpp\
            src/analysis/SmoothCurveDialog.cpp\
            src/analysis/Fit.cpp\
            src/analysis/fit_gsl.cpp\
            src/analysis/PolynomialFit.cpp\
            src/analysis/PolynomFitDialog.cpp\
            src/analysis/ExponentialFit.cpp\
            src/analysis/ExpDecayDialog.cpp\
            src/analysis/SigmoidalFit.cpp\
            src/analysis/PluginFit.cpp\
            src/analysis/MultiPeakFit.cpp\
            src/analysis/MultiPeakFitTool.cpp\
            src/analysis/NonLinearFit.cpp\
            src/analysis/FitDialog.cpp\
            src/OpenProjectDialog.cpp\
            src/globals.cpp \
            src/TeXTableSettings.cpp \
            src/TeXTableSettingsWidget.cpp \
            src/TeXTableExportDialog.cpp \
            src/scripting/widgets/Console.cpp \
            src/scripting/widgets/ConsoleWidget.cpp \
            src/scripting/SyntaxHighlighter.cpp \
            src/widgets/aSettingsListView.cpp \
            src/widgets/CharacterWidget.cpp \
            src/widgets/CustomCharacterDialog.cpp \
            src/ui/CharacterMapWidget.cpp \
            src/ui/ExportDialog.cpp \
            src/ui/ExtensibleFileDialog.cpp \
            src/ui/GeneralApplicationSettings.cpp \
            src/ui/GeneralAppreanceSettings.cpp \
            src/ui/GeneralConfirmationSettings.cpp \
            src/ui/SettingsPage.cpp \
            src/ui/SettingsDialog.cpp \
            src/ui/PropertiesDialog.cpp \
            src/ui/RandomDistributionDialog.cpp \
            src/ui/FittingSettings.cpp \
            src/ui/GeneralNumericFormatSettings.cpp \
            src/ui/TableBasicSettings.cpp \
            src/ui/TableColorSettings.cpp \
            src/ui/TableFontSettings.cpp \
            src/About.cpp \
            src/main.cpp \
            src/core/AprojHandler.cpp \
            src/future/lib/XmlStreamWriter.cpp \


###################### FORMS ##############################################
FORMS        += src/ApplicationWindow.ui \
                src/core/propertybrowser/propertyeditor.ui \
                src/core/propertybrowser/propertybrowser.ui \
                src/core/propertybrowser/pluginpropertyeditor.ui \
                src/core/propertybrowser/pluginpropertybrowser.ui \                
                src/scripting/widgets/ConsoleWidget.ui \
                src/widgets/CustomCharacterDialog.ui \
                src/ui/GeneralApplicationSettings.ui \
                src/ui/GeneralAppreanceSettings.ui \
                src/ui/GeneralConfirmationSettings.ui \
                src/ui/FittingSettings.ui \
                src/ui/GeneralNumericFormatSettings.ui \
                src/ui/TableBasicSettings.ui \
                src/ui/TableColorSettings.ui \
                src/ui/TableFontSettings.ui \
                src/ui/SettingsDialog.ui \
                src/ui/PropertiesDialog.ui \
                src/ui/RandomDistributionDialog.ui \
                src/About.ui \

########### Future code backported from the aspect framework ##################
INCLUDEPATH  += src
INCLUDEPATH  += src/future

FORMS        += src/future/matrix/matrixcontroltabs.ui \
                src/future/core/ProjectConfigPage.ui \
                src/future/table/controltabs.ui \

HEADERS     += src/future/core/AbstractAspect.h \
               src/future/core/AbstractPart.h \
               src/future/core/AspectPrivate.h \
               src/future/core/aspectcommands.h \
               src/future/core/future_Folder.h \
               src/future/core/Project.h \
               src/future/core/ProjectConfigPage.h \
               src/future/core/PartMdiView.h \
               src/future/core/AbstractColumn.h \
               src/future/core/ControlWidget.h \
               src/future/core/column/Column.h \
               src/future/core/column/ColumnPrivate.h \
               src/future/core/column/columncommands.h \
               src/future/core/AbstractFilter.h \
               src/future/core/AbstractSimpleFilter.h \
               src/future/core/datatypes/SimpleCopyThroughFilter.h \
               src/future/core/datatypes/DateTime2DoubleFilter.h \
               src/future/core/datatypes/DateTime2StringFilter.h \
               src/future/core/datatypes/DayOfWeek2DoubleFilter.h \
               src/future/core/datatypes/Double2DateTimeFilter.h \
               src/future/core/datatypes/NumericDateTimeBaseFilter.h \
               src/future/core/datatypes/Double2DayOfWeekFilter.h \
               src/future/core/datatypes/Double2MonthFilter.h \
               src/future/core/datatypes/Double2StringFilter.h \
               src/future/core/datatypes/Month2DoubleFilter.h \
               src/future/core/datatypes/String2DateTimeFilter.h \
               src/future/core/datatypes/String2DayOfWeekFilter.h \
               src/future/core/datatypes/String2DoubleFilter.h \
               src/future/core/datatypes/String2MonthFilter.h \
               src/future/lib/macros.h \
               src/future/lib/XmlStreamReader.h \
               src/future/lib/ActionManager.h \
               src/future/lib/ConfigPageWidget.h \
               src/future/lib/Interval.h \
               src/future/lib/IntervalAttribute.h \
               src/future/matrix/future_Matrix.h \
               src/future/matrix/MatrixModel.h \
               src/future/matrix/MatrixView.h \
               src/future/matrix/matrixcommands.h \
               src/future/table/future_Table.h \
               src/future/table/TableModel.h \
               src/future/table/TableView.h \
               src/future/table/tablecommands.h \
               src/future/table/TableDoubleHeaderView.h \
               src/future/table/TableItemDelegate.h \
               src/future/table/TableCommentsHeaderModel.h \
               src/future/table/future_SortDialog.h \
               src/future/table/AsciiTableImportFilter.h \
               src/future/core/AbstractImportFilter.h \
               src/future/core/interfaces.h \

SOURCES     += src/future/core/AbstractAspect.cpp \
               src/future/core/AbstractPart.cpp \
               src/future/core/AspectPrivate.cpp \
               src/future/core/future_Folder.cpp \
               src/future/core/PartMdiView.cpp \
               src/future/core/Project.cpp \
               src/future/core/ControlWidget.cpp \
               src/future/core/column/Column.cpp \
               src/future/core/column/ColumnPrivate.cpp \
               src/future/core/column/columncommands.cpp \
               src/future/core/datatypes/DateTime2StringFilter.cpp \
               src/future/core/datatypes/String2DateTimeFilter.cpp \
               src/future/core/datatypes/Double2StringFilter.cpp \
               src/future/core/datatypes/Double2DateTimeFilter.cpp \
               src/future/core/datatypes/NumericDateTimeBaseFilter.cpp \
               src/future/core/AbstractSimpleFilter.cpp \
               src/future/core/AbstractFilter.cpp \
               src/future/core/ProjectConfigPage.cpp \
               src/future/lib/XmlStreamReader.cpp \
               src/future/lib/ActionManager.cpp \
               src/future/lib/ConfigPageWidget.cpp \
               src/future/matrix/future_Matrix.cpp \
               src/future/matrix/MatrixModel.cpp \
               src/future/matrix/MatrixView.cpp \
               src/future/matrix/matrixcommands.cpp \
               src/future/table/future_Table.cpp \
               src/future/table/TableModel.cpp \
               src/future/table/TableView.cpp \
               src/future/table/tablecommands.cpp \
               src/future/table/TableDoubleHeaderView.cpp \
               src/future/table/TableItemDelegate.cpp \
               src/future/table/TableCommentsHeaderModel.cpp \
               src/future/table/future_SortDialog.cpp \
               src/future/table/AsciiTableImportFilter.cpp \

##############################################################
####################### QCustomPlot ##########################
##############################################################

HEADERS     += ../3rdparty/qcustomplot/qcustomplot.h
SOURCES     += ../3rdparty/qcustomplot/qcustomplot.cpp

##############################################################
####################### PropertyBrowser ######################
##############################################################

    SOURCES += ../3rdparty/propertybrowser/qtpropertybrowser.cpp \
               ../3rdparty/propertybrowser/qtpropertymanager.cpp \
               ../3rdparty/propertybrowser/qteditorfactory.cpp \
               ../3rdparty/propertybrowser/qttreepropertybrowser.cpp \
               ../3rdparty/propertybrowser/qtpropertybrowserutils.cpp \
               ../3rdparty/propertybrowser/QtxDoubleSpinBox.cpp

    HEADERS += ../3rdparty/propertybrowser/qtpropertybrowser.h \
               ../3rdparty/propertybrowser/qtpropertymanager.h \
               ../3rdparty/propertybrowser/qteditorfactory.h \
               ../3rdparty/propertybrowser/qttreepropertybrowser.h \
               ../3rdparty/propertybrowser/qtpropertybrowserutils_p.h \
               ../3rdparty/propertybrowser/QtxDoubleSpinBox.h

    RESOURCES += ../3rdparty/propertybrowser/qtpropertybrowser.qrc

##############################################################
####################### PlotCommon ###########################
##############################################################

HEADERS     += src/plotcommon/widgets/ImageExportDialog.h \

SOURCES     += src/plotcommon/widgets/ImageExportDialog.cpp \

##############################################################
####################### 2DPlot ###############################
##############################################################

HEADERS     += src/2Dplot/widgets/LayoutButton2D.h \
               src/2Dplot/widgets/Function2DDialog.h \
               src/2Dplot/widgets/SwapLayout2DDialog.h \
               src/2Dplot/widgets/ArrangeLegend2D.h \
               src/2Dplot/Axis2D.h \
               src/2Dplot/AxisRect2D.h \
               src/2Dplot/Bar2D.h \
               src/2Dplot/Grid2D.h \
               src/2Dplot/Layout2D.h \
               src/2Dplot/LayoutGrid2D.h \
               src/2Dplot/LayoutInset2D.h \
               src/2Dplot/Legend2D.h \
               src/2Dplot/LineSpecial2D.h \
               src/2Dplot/PickerTool2D.h \
               src/2Dplot/Plot2D.h \
               src/2Dplot/StatBox2D.h \
               src/2Dplot/Vector2D.h \
               src/2Dplot/DataManager2D.h \
               src/2Dplot/Curve2D.h \
               src/2Dplot/Pie2D.h \
               src/2Dplot/ColorMap2D.h \
               src/2Dplot/Graph2DCommon.h \
               src/2Dplot/widgets/AddPlot2DDialog.h \
               src/2Dplot/widgets/ErrDialog.h \
               src/2Dplot/LineItem2D.h \
               src/2Dplot/ErrorBar2D.h \
               src/2Dplot/TextItem2D.h \
               src/2Dplot/ImageItem2D.h \
               src/2Dplot/Plotcolumns.h \

SOURCES     += src/2Dplot/widgets/LayoutButton2D.cpp \
               src/2Dplot/widgets/Function2DDialog.cpp \
               src/2Dplot/widgets/SwapLayout2DDialog.cpp \
               src/2Dplot/widgets/ArrangeLegend2D.cpp \
               src/2Dplot/Axis2D.cpp \
               src/2Dplot/AxisRect2D.cpp \
               src/2Dplot/Bar2D.cpp \
               src/2Dplot/Grid2D.cpp \
               src/2Dplot/Layout2D.cpp \
               src/2Dplot/LayoutGrid2D.cpp \
               src/2Dplot/LayoutInset2D.cpp \
               src/2Dplot/Legend2D.cpp \
               src/2Dplot/LineSpecial2D.cpp \
               src/2Dplot/PickerTool2D.cpp \
               src/2Dplot/Plot2D.cpp \
               src/2Dplot/StatBox2D.cpp \
               src/2Dplot/Vector2D.cpp \
               src/2Dplot/DataManager2D.cpp \
               src/2Dplot/Curve2D.cpp \
               src/2Dplot/Pie2D.cpp \
               src/2Dplot/ColorMap2D.cpp \
               src/2Dplot/widgets/AddPlot2DDialog.cpp \
               src/2Dplot/widgets/ErrDialog.cpp \
               src/2Dplot/LineItem2D.cpp \
               src/2Dplot/ErrorBar2D.cpp \
               src/2Dplot/TextItem2D.cpp \
               src/2Dplot/ImageItem2D.cpp \

FORMS       += src/2Dplot/widgets/Function2DDialog.ui \
               src/2Dplot/widgets/SwapLayout2DDialog.ui \

##############################################################
####################### 3DPlot ###############################
##############################################################

HEADERS     += src/3Dplot/Layout3D.h \
               src/3Dplot/DataManager3D.h \
               src/3Dplot/Surface3D.h \
               src/3Dplot/Custom3DInteractions.h \
               src/3Dplot/Bar3D.h \
               src/3Dplot/Graph3DCommon.h \
               src/3Dplot/Scatter3D.h \
               src/3Dplot/SurfaceDialog.h \

SOURCES     += src/3Dplot/Layout3D.cpp \
               src/3Dplot/DataManager3D.cpp \
               src/3Dplot/Surface3D.cpp \
               src/3Dplot/Custom3DInteractions.cpp \
               src/3Dplot/Bar3D.cpp \
               src/3Dplot/Scatter3D.cpp \
               src/3Dplot/SurfaceDialog.cpp \

##############################################################
########################## RPS ###############################
##############################################################

HEADERS  += src/rps/RPSdefines.h \
            src/rps/RPSpluginManager.h \
            src/rps/sealab/widgets/rpsseawavedefinitiondlg.h\
            src/rps/sealab/widgets/rpsselpsddefinitiondialog.h\
            src/rps/sealab/widgets/rpsselcoherencedlg.h\
            src/rps/sealab/widgets/rpsselcorrelationdlg.h\
            src/rps/sealab/widgets/rpsselmodulationdlg.h\
            src/rps/sealab/widgets/prsselsimuoptionsdlg.h\
            src/rps/seismiclab/widgets/prsslsimuoptionsdlg.h\
            src/rps/pluginBrower/RPSPluginsBrowser.h\
            src/rps/pluginBrower/plugininstallerbrowser.h\
            src/rps/rpsSimulation.h\
            src/rps/seaLab/rpsSeaLabSimulation.h\
            src/rps/seismicLab/rpsSeismicLabSimulation.h\
            src/rps/windLab/rpsWindLabSimulation.h\
            src/rps/windlab/widgets/prswlsimuoptionsdlg.h\
            src/rps/windLab/widgets/rpswindvelocitydefinitiondlg.h\
            src/rps/windLab/widgets/rpswlpsddefinitiondialog.h\
            src/rps/windLab/widgets/rpswlmeanwinddlg.h\
            src/rps/windLab/widgets/rpswlcoherencedlg.h\
            src/rps/windLab/widgets/rpswlcorrelationdlg.h\
            src/rps/windLab/widgets/rpswlmodulationdlg.h\
            src/rps/seismicLab/widgets/rpsgroundmotiondefinitiondlg.h\
            src/rps/seismicLab/widgets/rpsslpsddefinitiondialog.h\
            src/rps/seismicLab/widgets/rpsslcoherencedlg.h\
            src/rps/seismicLab/widgets/rpsslcorrelationdlg.h\
            src/rps/seismicLab/widgets/rpsslmodulationdlg.h\
            src/rps/windLab/widgets/rpswlcomparisondialog.h\
            src/rps/windLab/widgets/rpswlaccuracycomparisondialog.h\
            src/rps/windLab/rpsWindLabSimulationWorker.h\
            src/rps/windLab/rpsWindLabSimulationOutputWorker.h\
            src/rps/windLab/rpsWindLabComparisonWorker.h\
            src/rps/githubRestApiClient.h\
            src/rps/windLab/widgets/rpswlcomparisonobjectdependencydialog.h\
            src/rps/windLab/widgets/rpswlcomparisontablezoomindialog.h\
            src/rps/windLab/widgets/rpswlaccuracycomparisontablezoomindialog.h\
            src/rps/windLab/widgets/rpswlaccuracycomparisonobjectdependencydialog.h\
            src/rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulation.h\
            src/rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulationWorker.h\
            src/rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulationOutputWorker.h\
            src/rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenonsimuoptionsdlg.h\
            src/rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenondefinitiondlg.h\

SOURCES  += src/rps/RPSpluginManager.cpp \
            src/rps/sealab/widgets/rpsseawavedefinitiondlg.cpp\
            src/rps/sealab/widgets/rpsselpsddefinitiondialog.cpp\
            src/rps/sealab/widgets/rpsselcoherencedlg.cpp\
            src/rps/sealab/widgets/rpsselcorrelationdlg.cpp\
            src/rps/sealab/widgets/rpsselmodulationdlg.cpp\
            src/rps/sealab/widgets/prsselsimuoptionsdlg.cpp\
            src/rps/seismiclab/widgets/prsslsimuoptionsdlg.cpp\
            src/rps/pluginBrower/RPSPluginsBrowser.cpp\
            src/rps/pluginBrower/plugininstallerbrowser.cpp\
            src/rps/rpsSimulation.cpp\
            src/rps/seaLab/rpsSeaLabSimulation.cpp\
            src/rps/seismicLab/rpsSeismicLabSimulation.cpp\
            src/rps/windLab/rpsWindLabSimulation.cpp\
            src/rps/windlab/widgets/prswlsimuoptionsdlg.cpp\
            src/rps/windLab/widgets/rpswindvelocitydefinitiondlg.cpp\
            src/rps/windLab/widgets/rpswlpsddefinitiondialog.cpp\
            src/rps/windLab/widgets/rpswlmeanwinddlg.cpp\
            src/rps/windLab/widgets/rpswlcoherencedlg.cpp\
            src/rps/windLab/widgets/rpswlcorrelationdlg.cpp\
            src/rps/windLab/widgets/rpswlmodulationdlg.cpp\
            src/rps/seismicLab/widgets/rpsgroundmotiondefinitiondlg.cpp\
            src/rps/seismicLab/widgets/rpsslpsddefinitiondialog.cpp\
            src/rps/seismicLab/widgets/rpsslcoherencedlg.cpp\
            src/rps/seismicLab/widgets/rpsslcorrelationdlg.cpp\
            src/rps/seismicLab/widgets/rpsslmodulationdlg.cpp\
            src/rps/windLab/widgets/rpswlcomparisondialog.cpp\
            src/rps/windLab/widgets/rpswlaccuracycomparisondialog.cpp\
            src/rps/windLab/rpsWindLabSimulationWorker.cpp\
            src/rps/windLab/rpsWindLabSimulationOutputWorker.cpp\
            src/rps/windLab/rpsWindLabComparisonWorker.cpp\
            src/rps/githubRestApiClient.cpp\
            src/rps/windLab/widgets/rpswlcomparisonobjectdependencydialog.cpp\
            src/rps/windLab/widgets/rpswlcomparisontablezoomindialog.cpp\
            src/rps/windLab/widgets/rpswlaccuracycomparisontablezoomindialog.cpp\
            src/rps/windLab/widgets/rpswlaccuracycomparisonobjectdependencydialog.cpp\
            src/rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulation.cpp\
            src/rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulationWorker.cpp\
            src/rps/userDefinedPhenomenon/rpsUserDefinedPhenomenonSimulationOutputWorker.cpp\
            src/rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenonsimuoptionsdlg.cpp\
            src/rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenondefinitiondlg.cpp\


FORMS    += src/rps/sealab/widgets/rpsseawavedefinitiondlg.ui\
            src/rps/sealab/widgets/rpsselpsddefinitiondialog.ui\
            src/rps/sealab/widgets/rpsselcoherencedlg.ui\
            src/rps/sealab/widgets/rpsselcorrelationdlg.ui\
            src/rps/sealab/widgets/rpsselmodulationdlg.ui\
            src/rps/sealab/widgets/prsselsimuoptionsdlg.ui\
            src/rps/seismiclab/widgets/prsslsimuoptionsdlg.ui\
            src/rps/pluginBrower/plugininstallerbrowser.ui\
            src/rps/windlab/widgets/prswlsimuoptionsdlg.ui\
            src/rps/windLab/widgets/rpswindvelocitydefinitiondlg.ui\
            src/rps/windLab/widgets/rpswlpsddefinitiondialog.ui\
            src/rps/windLab/widgets/rpswlmeanwinddlg.ui\
            src/rps/windLab/widgets/rpswlcoherencedlg.ui\
            src/rps/windLab/widgets/rpswlcorrelationdlg.ui\
            src/rps/windLab/widgets/rpswlmodulationdlg.ui\
            src/rps/seismicLab/widgets/rpsgroundmotiondefinitiondlg.ui\
            src/rps/seismicLab/widgets/rpsslpsddefinitiondialog.ui\
            src/rps/seismicLab/widgets/rpsslcoherencedlg.ui\
            src/rps/seismicLab/widgets/rpsslcorrelationdlg.ui\
            src/rps/seismicLab/widgets/rpsslmodulationdlg.ui\
            src/rps/windLab/widgets/rpswlcomparisondialog.ui\
            src/rps/windLab/widgets/rpswlaccuracycomparisondialog.ui\
            src/rps/windLab/widgets/rpswlcomparisonobjectdependencydialog.ui\
            src/rps/windLab/widgets/rpswlcomparisontablezoomindialog.ui\
            src/rps/windLab/widgets/rpswlaccuracycomparisontablezoomindialog.ui\
            src/rps/windLab/widgets/rpswlaccuracycomparisonobjectdependencydialog.ui\
            src/rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenonsimuoptionsdlg.ui\
            src/rps/userDefinedPhenomenon/widgets/rpsuserdefinedphenomenondefinitiondlg.ui\


