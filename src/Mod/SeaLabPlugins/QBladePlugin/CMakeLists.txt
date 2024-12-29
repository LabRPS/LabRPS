#define QT_NO_KEYWORDS

if(MSVC)
    add_definitions(-DHAVE_ACOSH -DHAVE_ATANH -DHAVE_ASINH)
else(MSVC)
    add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
endif(MSVC)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(QBladePlugin_LIBS
    LabRPSGui
    SeaLabAPI
    GeneralTools
    SeaLabTools
)

if(BUILD_QT5)
    qt5_add_resources(QBladePlugin_SRCS Resources/QBladePlugin.qrc)
else()
    qt4_add_resources(QBladePlugin_SRCS Resources/QBladePlugin.qrc)
endif()

set(QBladePlugin_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(QBladePlugin_UIC_HDRS ${QBladePlugin_UIC_SRCS})
else()
    qt4_wrap_ui(QBladePlugin_UIC_HDRS ${QBladePlugin_UIC_SRCS})
endif()

SET(QBladePlugin_SRCS
${QBladePlugin_SRCS}
${QBladePlugin_UIC_HDRS}
Resources/QBladePlugin.qrc
PreCompiled.cpp
PreCompiled.h
QBladePlugin.cpp
AppQBladePlugin.cpp

LinearWave.h
LinearWave.cpp
Globals.h
Globals.cpp
Params.h
RPSQBladeMethods.cpp
RPSQBladeMethods.h
# WaveModule.h
# WaveModule.cpp
# Module.h
# Module.cpp
# GLWidget.h
# GLWidget.cpp
# GLLightSettings.cpp
# GLLightSettings.h
)

SET(Metadata_Files
QBladePlugin.txt

)


SET(QBladePluginIcon_SVG
    # Resources/icons/QBladePluginWorkbench.svg
)

add_library(QBladePlugin SHARED ${QBladePlugin_SRCS} ${Metadata_Files} ${QBladePluginIcon_SVG})
target_link_libraries(QBladePlugin ${QBladePlugin_LIBS})
set_target_properties(QBladePlugin PROPERTIES FOLDER "Plugins/SeaLab")


SET_BIN_DIR(QBladePlugin QBladePlugin /Plugins/SeaLabWorkbench/QBladePlugin)

rps_copy_sources(QBladePlugin "${CMAKE_BINARY_DIR}/Plugins/SeaLabWorkbench/QBladePlugin" ${Metadata_Files})
INSTALL(TARGETS QBladePlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeaLabWorkbench/QBladePlugin")
INSTALL(FILES QBladePlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeaLabWorkbench/QBladePlugin")
INSTALL(FILES ${QBladePluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/SeaLab/QBladePlugin/Resources/icons")

