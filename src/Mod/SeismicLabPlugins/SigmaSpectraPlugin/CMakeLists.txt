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

set(SigmaSpectraPlugin_LIBS
    LabRPSGui
    SeismicLabAPI
    GeneralTools
    SeismicLabTools
    SigmaSpectra
)


SET(SigmaSpectraPlugin_SRCS
SigmaSpectra.h
SigmaSpectra.cpp
SigmaSpectraPlugin.cpp
)

SET(Metadata_Files
SigmaSpectraPlugin.txt

)


SET(SigmaSpectraPluginIcon_SVG
    # Resources/icons/SigmaSpectraPluginWorkbench.svg
)

add_library(SigmaSpectraPlugin SHARED ${SigmaSpectraPlugin_SRCS} ${Metadata_Files})
target_link_libraries(SigmaSpectraPlugin ${SigmaSpectraPlugin_LIBS})
set_target_properties(SigmaSpectraPlugin PROPERTIES FOLDER "Plugins/SeismicLab")


SET_BIN_DIR(SigmaSpectraPlugin SigmaSpectraPlugin /Plugins/SeismicLabWorkbench/SigmaSpectraPlugin)

rps_copy_sources(SigmaSpectraPlugin "${CMAKE_BINARY_DIR}/Plugins/SeismicLabWorkbench/SigmaSpectraPlugin" ${Metadata_Files})

INSTALL(TARGETS SigmaSpectraPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/SigmaSpectraPlugin")
INSTALL(FILES SigmaSpectraPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/SigmaSpectraPlugin")

