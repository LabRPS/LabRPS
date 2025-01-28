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

set(RandomWalkPlugin_LIBS
    LabRPSGui
    UserLabAPI
    GeneralTools
)

set(RandomWalkPlugin_Scripts
    RandomWalk.py
)

if(BUILD_QT5)
    qt5_add_resources(RandomWalkPlugin_SRCS Resources/RandomWalkPlugin.qrc)
else()
    qt4_add_resources(RandomWalkPlugin_SRCS Resources/RandomWalkPlugin.qrc)
endif()

set(RandomWalkPlugin_UIC_SRCS
Widgets/DlgRandomWalk.ui
)

if(BUILD_QT5)
    qt5_wrap_ui(RandomWalkPlugin_UIC_HDRS ${RandomWalkPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(RandomWalkPlugin_UIC_HDRS ${RandomWalkPlugin_UIC_SRCS})
endif()

SET(RandomWalkPlugin_SRCS
${RandomWalkPlugin_SRCS}
${RandomWalkPlugin_UIC_HDRS}
Resources/RandomWalkPlugin.qrc
PreCompiled.cpp
PreCompiled.h
RandomWalkPlugin.cpp
Widgets/DlgRandomWalk.h
Widgets/DlgRandomWalk.cpp
RPSRandomWalk.cpp
RPSRandomWalk.h
JsonObject.h
JsonObject.cpp
)

SET(Metadata_Files
RandomWalkPlugin.txt

)


SET(RandomWalkPluginIcon_SVG
    # Resources/icons/RandomWalkPluginWorkbench.svg
)

add_library(RandomWalkPlugin SHARED ${RandomWalkPlugin_SRCS} ${Metadata_Files} ${RandomWalkPlugin_Scripts} ${RandomWalkPluginIcon_SVG})
target_link_libraries(RandomWalkPlugin ${RandomWalkPlugin_LIBS} nlohmann_json::nlohmann_json)

set_target_properties(RandomWalkPlugin PROPERTIES FOLDER "Plugins/UserLab")


SET_BIN_DIR(RandomWalkPlugin RandomWalkPlugin /Plugins/UserLabWorkbench/RandomWalkPlugin)

rps_copy_sources(RandomWalkPlugin "${CMAKE_BINARY_DIR}/Plugins/UserLabWorkbench/RandomWalkPlugin" ${Metadata_Files})
rps_copy_sources(RandomWalkPlugin "${CMAKE_BINARY_DIR}/Plugins/UserLabWorkbench/RandomWalkPlugin" ${RandomWalkPlugin_Scripts})
INSTALL(TARGETS RandomWalkPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/UserLabWorkbench/RandomWalkPlugin")
INSTALL(FILES RandomWalkPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/UserLabWorkbench/RandomWalkPlugin")
INSTALL(FILES ${RandomWalkPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/UserLab/RandomWalkPlugin/Resources/icons")

