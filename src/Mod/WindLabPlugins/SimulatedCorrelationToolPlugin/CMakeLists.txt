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

set(SimulatedCorrelationToolPlugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)



set(SimulatedCorrelationToolPlugin_UIC_SRCS
widgets/DlgSimulatedCorrelationTool.ui


)

if(BUILD_QT5)
    qt5_wrap_ui(SimulatedCorrelationToolPlugin_UIC_HDRS ${SimulatedCorrelationToolPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(SimulatedCorrelationToolPlugin_UIC_HDRS ${SimulatedCorrelationToolPlugin_UIC_SRCS})
endif()

SET(SimulatedCorrelationToolPlugin_SRCS
    ${SimulatedCorrelationToolPlugin_SRCS}
    ${SimulatedCorrelationToolPlugin_UIC_HDRS}
    SimulatedCorrelationTool.cpp
    SimulatedCorrelationToolPlugin.cpp
    widgets/DlgSimulatedCorrelationTool.cpp
    widgets/DlgSimulatedCorrelationTool.h
    SimulatedCorrelationTool.h


)

SET(Metadata_Files
SimulatedCorrelationToolPlugin.txt

)

SET(SimulatedCorrelationToolPluginIcon_SVG
    # Resources/icons/SimulatedCorrelationToolPluginWorkbench.svg
)

add_library(SimulatedCorrelationToolPlugin SHARED ${SimulatedCorrelationToolPlugin_SRCS} ${Metadata_Files} ${SimulatedCorrelationToolPluginIcon_SVG})
target_link_libraries(SimulatedCorrelationToolPlugin ${SimulatedCorrelationToolPlugin_LIBS})
set_target_properties(SimulatedCorrelationToolPlugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(SimulatedCorrelationToolPlugin SimulatedCorrelationToolPlugin /Plugins/WindLabWorkbench/SimulatedCorrelationToolPlugin)

rps_copy_sources(SimulatedCorrelationToolPlugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/SimulatedCorrelationToolPlugin" ${Metadata_Files})
INSTALL(TARGETS SimulatedCorrelationToolPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/SimulatedCorrelationToolPlugin")
INSTALL(FILES SimulatedCorrelationToolPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/SimulatedCorrelationToolPlugin")
INSTALL(FILES ${SimulatedCorrelationToolPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/SimulatedCorrelationToolPlugin/Resources/icons")

