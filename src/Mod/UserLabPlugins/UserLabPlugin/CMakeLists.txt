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

set(UserLabPlugin_LIBS
    LabRPSGui
    UserLabAPI
    GeneralTools
)

if(BUILD_QT5)
    qt5_add_resources(UserLabPlugin_SRCS Resources/UserLabPlugin.qrc)
else()
    qt4_add_resources(UserLabPlugin_SRCS Resources/UserLabPlugin.qrc)
endif()

set(UserLabPlugin_UIC_SRCS
Widgets/DlgGoenagaEtAl2017.ui
)

if(BUILD_QT5)
    qt5_wrap_ui(UserLabPlugin_UIC_HDRS ${UserLabPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(UserLabPlugin_UIC_HDRS ${UserLabPlugin_UIC_SRCS})
endif()

SET(UserLabPlugin_SRCS
${UserLabPlugin_SRCS}
${UserLabPlugin_UIC_HDRS}
Resources/UserLabPlugin.qrc
PreCompiled.cpp
PreCompiled.h
UserLabPlugin.cpp
Widgets/DlgGoenagaEtAl2017.h
Widgets/DlgGoenagaEtAl2017.cpp
RPSGoenagaEtAl2017.cpp
RPSGoenagaEtAl2017.h
)

SET(Metadata_Files
UserLabPlugin.txt

)


SET(UserLabPluginIcon_SVG
    # Resources/icons/UserLabPluginWorkbench.svg
)

add_library(UserLabPlugin SHARED ${UserLabPlugin_SRCS} ${Metadata_Files} ${UserLabPluginIcon_SVG})
target_link_libraries(UserLabPlugin ${UserLabPlugin_LIBS})
set_target_properties(UserLabPlugin PROPERTIES FOLDER "Plugins/UserLab")


SET_BIN_DIR(UserLabPlugin UserLabPlugin /Plugins/UserLabWorkbench/UserLabPlugin)

rps_copy_sources(UserLabPlugin "${CMAKE_BINARY_DIR}/Plugins/UserLabWorkbench/UserLabPlugin" ${Metadata_Files})
INSTALL(TARGETS UserLabPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/UserLabWorkbench/UserLabPlugin")
INSTALL(FILES UserLabPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/UserLabWorkbench/UserLabPlugin")
INSTALL(FILES ${UserLabPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/UserLab/UserLabPlugin/Resources/icons")

