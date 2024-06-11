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

set(RPSRandomnessProviders_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

if(BUILD_QT5)
    qt5_add_resources(RPSRandomnessProviders_SRCS data/icons.qrc)
else()
    qt4_add_resources(RPSRandomnessProviders_SRCS data/icons.qrc)
endif()

set(RPSRandomnessProviders_UIC_SRCS
    widgets/cgaussianrandomnessproviderdlg.ui
    widgets/RPSRandomDistributionDialog.ui

)

if(BUILD_QT5)
    qt5_wrap_ui(RPSRandomnessProviders_UIC_HDRS ${RPSRandomnessProviders_UIC_SRCS})
else()
    qt4_wrap_ui(RPSRandomnessProviders_UIC_HDRS ${RPSRandomnessProviders_UIC_SRCS})
endif()

SET(RPSRandomnessProviders_SRCS
    ${RPSRandomnessProviders_SRCS}
    ${RPSRandomnessProviders_UIC_HDRS}
    PreCompiled.cpp
    PreCompiled.h
    RPSRandomnessProviders.cpp
    Widgets/IconLoader.cpp
    Widgets/IconLoader.h
    randomnessProviders.cpp
    RPSRandomnessProviders.cpp
    widgets/cgaussianrandomnessproviderdlg.cpp
    widgets/RPSRandomDistributionDialog.cpp
    randomnessProviders.h
    widgets/cgaussianrandomnessproviderdlg.h
    widgets/RPSRandomDistributionDialog.h
    widgets/IconLoader.h



)

SET(Metadata_Files
RPSRandomnessProviders.txt

)


SET(RPSRandomnessProvidersIcon_SVG
    # Resources/icons/RPSRandomnessProvidersWorkbench.svg
)

add_library(RPSRandomnessProviders SHARED ${RPSRandomnessProviders_SRCS} ${Metadata_Files} ${RPSRandomnessProvidersIcon_SVG})
target_link_libraries(RPSRandomnessProviders ${RPSRandomnessProviders_LIBS})
set_target_properties(RPSRandomnessProviders PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(RPSRandomnessProviders RPSRandomnessProviders /Plugins/WindLabWorkbench/RPSRandomnessProviders)

fc_copy_sources(RPSRandomnessProviders "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/RPSRandomnessProviders" ${Metadata_Files})
INSTALL(TARGETS RPSRandomnessProviders DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/RPSRandomnessProviders")
INSTALL(FILES RPSRandomnessProviders.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/RPSRandomnessProviders")
INSTALL(FILES ${RPSRandomnessProvidersIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/RPSRandomnessProviders/Resources/icons")

