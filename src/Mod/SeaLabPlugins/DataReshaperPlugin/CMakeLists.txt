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

set(DataReshaperPlugin_LIBS
    LabRPSGui
    SeaLabAPI
    GeneralTools
    SeaLabTools
)

SET(DataReshaperPlugin_SRCS
PreCompiled.cpp
PreCompiled.h

DataReshaperPlugin.cpp
DataReshaper.cpp
DataReshaper.h
)

SET(Metadata_Files
DataReshaperPlugin.txt

)

SET(DataReshaperPluginIcon_SVG
)

add_library(DataReshaperPlugin SHARED ${DataReshaperPlugin_SRCS} ${Metadata_Files} ${DataReshaperPluginIcon_SVG})
target_link_libraries(DataReshaperPlugin ${DataReshaperPlugin_LIBS})
set_target_properties(DataReshaperPlugin PROPERTIES FOLDER "Plugins/SeaLab")


SET_BIN_DIR(DataReshaperPlugin DataReshaperPlugin /Plugins/SeaLabWorkbench/DataReshaperPlugin)

rps_copy_sources(DataReshaperPlugin "${CMAKE_BINARY_DIR}/Plugins/SeaLabWorkbench/DataReshaperPlugin" ${Metadata_Files})
INSTALL(TARGETS DataReshaperPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeaLabWorkbench/DataReshaperPlugin")
INSTALL(FILES DataReshaperPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeaLabWorkbench/DataReshaperPlugin")
INSTALL(FILES ${DataReshaperPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/SeaLab/DataReshaperPlugin/Resources/icons")

