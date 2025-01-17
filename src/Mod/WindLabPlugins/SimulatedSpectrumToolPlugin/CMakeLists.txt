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

set(SimulatedSpectrumToolPlugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)



set(SimulatedSpectrumToolPlugin_UIC_SRCS
widgets/DlgSimulatedSpectrumTool.ui


)

if(BUILD_QT5)
    qt5_wrap_ui(SimulatedSpectrumToolPlugin_UIC_HDRS ${SimulatedSpectrumToolPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(SimulatedSpectrumToolPlugin_UIC_HDRS ${SimulatedSpectrumToolPlugin_UIC_SRCS})
endif()

SET(SimulatedSpectrumToolPlugin_SRCS
    ${SimulatedSpectrumToolPlugin_SRCS}
    ${SimulatedSpectrumToolPlugin_UIC_HDRS}
    SimulatedSpectrumTool.cpp
    SimulatedSpectrumToolPlugin.cpp
    widgets/DlgSimulatedSpectrumTool.cpp
    widgets/DlgSimulatedSpectrumTool.h
    SimulatedSpectrumTool.h


)

SET(Metadata_Files
SimulatedSpectrumToolPlugin.txt

)

SET(SimulatedSpectrumToolPluginIcon_SVG
    # Resources/icons/SimulatedSpectrumToolPluginWorkbench.svg
)

add_library(SimulatedSpectrumToolPlugin SHARED ${SimulatedSpectrumToolPlugin_SRCS} ${Metadata_Files} ${SimulatedSpectrumToolPluginIcon_SVG})
target_link_libraries(SimulatedSpectrumToolPlugin ${SimulatedSpectrumToolPlugin_LIBS})
set_target_properties(SimulatedSpectrumToolPlugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(SimulatedSpectrumToolPlugin SimulatedSpectrumToolPlugin /Plugins/WindLabWorkbench/SimulatedSpectrumToolPlugin)

rps_copy_sources(SimulatedSpectrumToolPlugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/SimulatedSpectrumToolPlugin" ${Metadata_Files})
INSTALL(TARGETS SimulatedSpectrumToolPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/SimulatedSpectrumToolPlugin")
INSTALL(FILES SimulatedSpectrumToolPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/SimulatedSpectrumToolPlugin")
INSTALL(FILES ${SimulatedSpectrumToolPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/SimulatedSpectrumToolPlugin/Resources/icons")

