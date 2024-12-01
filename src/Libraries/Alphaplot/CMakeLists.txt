# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)
add_compile_definitions(SCRIPTING_MUPARSER)
add_compile_definitions(DGSL_DLL)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

# -------QT stuff----------------------------------------------------------------------
include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Alphaplot
    ${CMAKE_CURRENT_BINARY_DIR}/Alphaplot

    ${CMAKE_CURRENT_SOURCE_DIR}/2Dplot
    ${CMAKE_CURRENT_SOURCE_DIR}/2Dplot/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/3Dplot
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qcustomplot
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/future/core
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/table
    ${CMAKE_CURRENT_SOURCE_DIR}/future/column
    ${CMAKE_CURRENT_SOURCE_DIR}/future/datatypes
    ${CMAKE_CURRENT_SOURCE_DIR}/plotcommon/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_BINARY_DIR}/2Dplot
    ${CMAKE_CURRENT_BINARY_DIR}/2Dplot/widgets
    ${CMAKE_CURRENT_BINARY_DIR}/3Dplot
    ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/qcustomplot
    ${CMAKE_CURRENT_BINARY_DIR}/3rdparty
    ${CMAKE_CURRENT_BINARY_DIR}/future/core
    ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/lib
    ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/matrix
    ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/table
    ${CMAKE_CURRENT_BINARY_DIR}/future/column
    ${CMAKE_CURRENT_BINARY_DIR}/future/datatypes
    ${CMAKE_CURRENT_BINARY_DIR}/plotcommon/widgets
    ${CMAKE_CURRENT_BINARY_DIR}/ui


)

if(MSVC)
    include_directories(
        ${CMAKE_SOURCE_DIR}/src/3rdParty/OpenGL/api
    )
endif(MSVC)


set(Alphaplot_LIBS
    LabRPSBase
)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5OpenGL_INCLUDE_DIRS}
        ${Qt5PrintSupport_INCLUDE_DIRS}
        ${Qt5Svg_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS}
        ${Qt5UiTools_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
        ${Qt5DataVisualization_INCLUDE_DIRS}
        ${Qt5Script_INCLUDE_DIRS}

    )

    list(APPEND Alphaplot_LIBS
        ${Qt5Core_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5OpenGL_LIBRARIES}
        ${Qt5PrintSupport_LIBRARIES}
        ${Qt5Svg_LIBRARIES}
        ${Qt5Network_LIBRARIES}
        ${Qt5UiTools_LIBRARIES}
        ${Qt5Xml_LIBRARIES}
        ${Qt5DataVisualization_LIBRARIES}
        ${Qt5Script_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
    )

else()
    include_directories(
        ${QT_INCLUDE_DIR}
        ${QT_QTCORE_INCLUDE_DIR}

    )
    list(APPEND Alphaplot_LIBS
        ${QT_LIBRARIES}
        ${QT_QTUITOOLS_LIBRARY}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND Alphaplot_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()



# The document stuff
SET(Document_CPP_SRCS
            core/AppearanceManager.cpp
            core/IconLoader.cpp
            core/Utilities.cpp
            Table.cpp
            PlotWizard.cpp
            Matrix.cpp
            MyWidget.cpp
            Folder.cpp
            FindDialog.cpp
            OpenProjectDialog.cpp
            ImageExportDlg.cpp
            globals.cpp
            ui/ExportDialog.cpp
            ui/ExtensibleFileDialog.cpp
            ui/RandomDistributionDialog.cpp
            future/lib/XmlStreamWriter.cpp
            future/core/AbstractAspect.cpp
               future/core/AbstractPart.cpp
               future/core/AspectPrivate.cpp
               future/core/future_Folder.cpp
               future/core/PartMdiView.cpp
               future/core/Project.cpp
               future/core/ControlWidget.cpp
               future/core/column/Column.cpp
               future/core/column/ColumnPrivate.cpp
               future/core/column/columncommands.cpp
               future/core/datatypes/DateTime2StringFilter.cpp
               future/core/datatypes/String2DateTimeFilter.cpp
               future/core/datatypes/Double2StringFilter.cpp
               future/core/datatypes/Double2DateTimeFilter.cpp
               future/core/datatypes/NumericDateTimeBaseFilter.cpp
               future/core/AbstractSimpleFilter.cpp
               future/core/AbstractFilter.cpp
               future/lib/XmlStreamReader.cpp
               future/lib/ActionManager.cpp
               future/matrix/future_Matrix.cpp
               future/matrix/MatrixModel.cpp
               future/matrix/MatrixView.cpp
               future/matrix/matrixcommands.cpp
               future/table/future_Table.cpp
               future/table/TableModel.cpp
               future/table/TableView.cpp
               future/table/tablecommands.cpp
               future/table/TableDoubleHeaderView.cpp
               future/table/TableItemDelegate.cpp
               future/table/TableCommentsHeaderModel.cpp
               future/table/future_SortDialog.cpp
               future/table/AsciiTableImportFilter.cpp
               3rdparty/qcustomplot/qcustomplot.cpp
               plotcommon/widgets/ImageExportDialog.cpp
               2Dplot/widgets/LayoutButton2D.cpp
               2Dplot/widgets/Function2DDialog.cpp
               2Dplot/widgets/SwapLayout2DDialog.cpp
               2Dplot/widgets/ArrangeLegend2D.cpp
               2Dplot/Axis2D.cpp
               2Dplot/AxisRect2D.cpp
               2Dplot/Bar2D.cpp
               2Dplot/Grid2D.cpp
               2Dplot/Layout2D.cpp
               2Dplot/LayoutGrid2D.cpp
               2Dplot/LayoutInset2D.cpp
               2Dplot/Legend2D.cpp
               2Dplot/LineSpecial2D.cpp
               2Dplot/PickerTool2D.cpp
               2Dplot/Plot2D.cpp
               2Dplot/StatBox2D.cpp
               2Dplot/Vector2D.cpp
               2Dplot/DataManager2D.cpp
               2Dplot/Curve2D.cpp
               2Dplot/Pie2D.cpp
               2Dplot/ColorMap2D.cpp
               2Dplot/widgets/AddPlot2DDialog.cpp
               2Dplot/widgets/ErrDialog.cpp
               2Dplot/LineItem2D.cpp
               2Dplot/ErrorBar2D.cpp
               2Dplot/TextItem2D.cpp
               2Dplot/ImageItem2D.cpp
               3Dplot/Layout3D.cpp
               3Dplot/DataManager3D.cpp
               3Dplot/Surface3D.cpp
               3Dplot/Custom3DInteractions.cpp
               3Dplot/Bar3D.cpp
               3Dplot/Scatter3D.cpp
               3Dplot/SurfaceDialog.cpp
               ui/PropertiesDialog.cpp
               TableStatistics.cpp
               ImportASCIIDialog.cpp

            AlphaplotGlobal.h
            core/AppearanceManager.h
            core/IconLoader.h
            core/Utilities.h
            globals.h
            Table.h
            PlotWizard.h
            Matrix.h
            MyWidget.h
            ImageExportDlg.h
            Folder.h
            FindDialog.h
            OpenProjectDialog.h
            ui/ExportDialog.h
            ui/ExtensibleFileDialog.h
            ui/RandomDistributionDialog.h
            future/lib/XmlStreamWriter.h
            future/core/AbstractAspect.h
               future/core/AbstractPart.h
               future/core/AspectPrivate.h
               future/core/aspectcommands.h
               future/core/future_Folder.h
               future/core/Project.h
               future/core/PartMdiView.h
               future/core/AbstractColumn.h
               future/core/ControlWidget.h
               future/core/column/Column.h
               future/core/column/ColumnPrivate.h
               future/core/column/columncommands.h
               future/core/AbstractFilter.h
               future/core/AbstractSimpleFilter.h
               future/core/datatypes/SimpleCopyThroughFilter.h
               future/core/datatypes/DateTime2DoubleFilter.h
               future/core/datatypes/DateTime2StringFilter.h
               future/core/datatypes/DayOfWeek2DoubleFilter.h
               future/core/datatypes/Double2DateTimeFilter.h
               future/core/datatypes/NumericDateTimeBaseFilter.h
               future/core/datatypes/Double2DayOfWeekFilter.h
               future/core/datatypes/Double2MonthFilter.h
               future/core/datatypes/Double2StringFilter.h
               future/core/datatypes/Month2DoubleFilter.h
               future/core/datatypes/String2DateTimeFilter.h
               future/core/datatypes/String2DayOfWeekFilter.h
               future/core/datatypes/String2DoubleFilter.h
               future/core/datatypes/String2MonthFilter.h
               future/lib/macros.h
               future/lib/XmlStreamReader.h
               future/lib/ActionManager.h
               future/lib/Interval.h
               future/lib/IntervalAttribute.h
               future/matrix/future_Matrix.h
               future/matrix/MatrixModel.h
               future/matrix/MatrixView.h
               future/matrix/matrixcommands.h
               future/table/future_Table.h
               future/table/TableModel.h
               future/table/TableView.h
               future/table/tablecommands.h
               future/table/TableDoubleHeaderView.h
               future/table/TableItemDelegate.h
               future/table/TableCommentsHeaderModel.h
               future/table/future_SortDialog.h
               future/table/AsciiTableImportFilter.h
               future/core/AbstractImportFilter.h
               future/core/interfaces.h
               3rdparty/qcustomplot/qcustomplot.h
               plotcommon/widgets/ImageExportDialog.h
               2Dplot/widgets/LayoutButton2D.h
               2Dplot/widgets/Function2DDialog.h
               2Dplot/widgets/SwapLayout2DDialog.h
               2Dplot/widgets/ArrangeLegend2D.h
               2Dplot/Axis2D.h
               2Dplot/AxisRect2D.h
               2Dplot/Bar2D.h
               2Dplot/Grid2D.h
               2Dplot/Layout2D.h
               2Dplot/LayoutGrid2D.h
               2Dplot/LayoutInset2D.h
               2Dplot/Legend2D.h
               2Dplot/LineSpecial2D.h
               2Dplot/PickerTool2D.h
               2Dplot/Plot2D.h
               2Dplot/StatBox2D.h
               2Dplot/Vector2D.h
               2Dplot/DataManager2D.h
               2Dplot/Curve2D.h
               2Dplot/Pie2D.h
               2Dplot/ColorMap2D.h
               2Dplot/Graph2DCommon.h
               2Dplot/widgets/AddPlot2DDialog.h
               2Dplot/widgets/ErrDialog.h
               2Dplot/LineItem2D.h
               2Dplot/ErrorBar2D.h
               2Dplot/TextItem2D.h
               2Dplot/ImageItem2D.h
               2Dplot/Plotcolumns.h
               3Dplot/Layout3D.h
               3Dplot/DataManager3D.h
               3Dplot/Surface3D.h
               3Dplot/Custom3DInteractions.h
               3Dplot/Bar3D.h
               3Dplot/Graph3DCommon.h
               3Dplot/Scatter3D.h
               3Dplot/SurfaceDialog.h
               ui/PropertiesDialog.h
               GraphType.h
               TableStatistics.h
               ImportASCIIDialog.h


)

# The muParser sources
SET(muParser_CPP_SRCS
    3rdparty/muparser/muParser.cpp
    3rdparty/muparser/muParserBase.cpp
    3rdparty/muparser/muParserBytecode.cpp
    3rdparty/muparser/muParserCallback.cpp
    3rdparty/muparser/muParserError.cpp
    3rdparty/muparser/muParserTokenReader.cpp
)
SET(muParser_HPP_SRCS
    3rdparty/muparser/muParser.h
    3rdparty/muparser/muParserBase.h
    3rdparty/muparser/muParserBytecode.h
    3rdparty/muparser/muParserCallback.h
    3rdparty/muparser/muParserDef.h
    3rdparty/muparser/muParserError.h
    3rdparty/muparser/muParserFixes.h
    3rdparty/muparser/muParserStack.h
    3rdparty/muparser/muParserToken.h
    3rdparty/muparser/muParserTokenReader.h
    3rdparty/muparser/muParserTemplateMagic.h
)

SET(muParser_SRCS
    ${muParser_CPP_SRCS}
    ${muParser_HPP_SRCS}
)
SOURCE_GROUP("muParser" FILES ${muParser_SRCS})

# The Scripting sources
SET(Scripting_CPP_SRCS
scripting/MuParserScript.cpp
scripting/MuParserScripting.cpp
scripting/MyParser.cpp
scripting/ScriptEdit.cpp
# scripting/ScriptingFunctions.cpp
scripting/ScriptingEnv.cpp
scripting/Script.cpp
# scripting/ScriptingLangDialog.cpp
# scripting/widgets/Console.cpp
# scripting/widgets/ConsoleWidget.cpp
scripting/SyntaxHighlighter.cpp
)
SET(Scripting_HPP_SRCS
scripting/MuParserScript.h
scripting/MuParserScripting.h
# scripting/ScriptingFunctions.h
scripting/MyParser.h
scripting/ScriptingEnv.h
scripting/Script.h
scripting/ScriptEdit.h
scripting/customevents.h
# scripting/ScriptingLangDialog.h
# scripting/widgets/Console.h
# scripting/widgets/ConsoleWidget.h
scripting/SyntaxHighlighter.h
)

SET(Scripting_SRCS
    ${Scripting_CPP_SRCS}
    ${Scripting_HPP_SRCS}
)
SOURCE_GROUP("Scripting" FILES ${Scripting_SRCS})

SET(Gui_UIC_SRCS
                future/matrix/matrixcontroltabs.ui
                future/table/controltabs.ui
                2Dplot/widgets/Function2DDialog.ui
                2Dplot/widgets/SwapLayout2DDialog.ui
                ui/PropertiesDialog.ui
                ui/RandomDistributionDialog.ui

                # scripting/widgets/ConsoleWidget.ui

)

SET(Gui_RES_SRCS
data/icons.qrc
)

if (BUILD_QT5)
    QT5_ADD_RESOURCES(Gui_QRC_SRCS ${Gui_RES_SRCS})
    QT5_WRAP_UI(Gui_UIC_HDRS ${Gui_UIC_SRCS})
else()
    QT4_ADD_RESOURCES(Gui_QRC_SRCS ${Gui_RES_SRCS})
    QT4_WRAP_UI(Gui_UIC_HDRS ${Gui_UIC_SRCS})
endif()
SOURCE_GROUP("Uic" FILES ${Gui_UIC_HDRS})

SET(Alphaplot_CPP_SRCS
    ${Document_CPP_SRCS}
    
)

SET(Alphaplot_HPP_SRCS
    ${Document_HPP_SRCS}

)

SET(Alphaplot_SRCS
    ${Alphaplot_CPP_SRCS}
    ${Alphaplot_HPP_SRCS}
    ${Document_CPP_SRCS}
    ${Gui_QRC_SRCS}
    ${Gui_UIC_HDRS}
    ${muParser_SRCS}
    ${Scripting_SRCS}
    # ${Gui_UIC_SRCS}
    PreCompiled.cpp
    PreCompiled.h
)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    ADD_MSVC_PRECOMPILED_HEADER(Alphaplot PreCompiled.h PreCompiled.cpp Alphaplot_CPP_SRCS)
endif(LABRPS_USE_PCH)

add_library(Alphaplot SHARED ${Alphaplot_SRCS})

target_link_libraries(Alphaplot ${Alphaplot_LIBS})

set(QT5VIUSALIZATION_INCLUDE_PATH ${LABRPS_LIBPACK_DIR}/include)
set(QT5SCRIPT_INCLUDE_PATH ${LABRPS_LIBPACK_DIR}/include)

set_target_properties(Alphaplot PROPERTIES FOLDER "Libraries")

# GSL configuration here is very ugly. But we are working a proper GSL CMake configuration
set(GSL_LIB_PATH "C:/DEV/vcpkg/packages/gsl_x64-windows/lib") # change this link according to your gsl location or you can configure GLS CMakeList.txt
set(GSL_INCLUDE_PATH "C:/DEV/vcpkg/packages/gsl_x64-windows/include") # change this link according to your gsl location or you can configure GLS CMakeList.txt

set(QT5VIUSALIZATION_INCLUDE_PATH ${LABRPS_LIBPACK_DIR}/include)
set(QT5SCRIPT_INCLUDE_PATH ${LABRPS_LIBPACK_DIR}/include)

# add the two paths to cmake 
list(APPEND CMAKE_PREFIX_PATH ${GSL_LIB_PATH})
list(APPEND CMAKE_PREFIX_PATH ${GSL_INCLUDE_PATH})

#find the two library lib
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)

# link to the libs
target_link_libraries(Alphaplot ${GSL_LIB} ${GSLCBLAS_LIB})
set_target_properties(Alphaplot PROPERTIES FOLDER "Libraries")

# find the include files
find_path (GSL_INCLUDE gsl)

#  add the include file to the project
target_include_directories(Alphaplot PRIVATE "${GSL_INCLUDE}")

include_directories(${Qt5DataVisualization_INCLUDE_DIRS})
include_directories(${Qt5Script_INCLUDE_DIRS})
include_directories(${Qt5PrintSupport_INCLUDE_DIRS})

target_link_libraries(Alphaplot ${Qt5DataVisualization_LIBRARIES})
target_link_libraries(Alphaplot ${Qt5Script_LIBRARIES})
target_link_libraries(Alphaplot ${Qt5PrintSupport_LIBRARIES})



SET_BIN_DIR(Alphaplot Alphaplot)

if(WIN32)
    INSTALL(TARGETS Alphaplot
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
else(WIN32)
    INSTALL(TARGETS Alphaplot
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif(WIN32)