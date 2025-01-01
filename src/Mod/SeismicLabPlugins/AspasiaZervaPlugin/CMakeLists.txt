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

set(AspasiaZervaPlugin_LIBS
    LabRPSGui
    SeismicLabAPI
    GeneralTools

)

SET(AspasiaZervaPlugin_SRCS
PreCompiled.cpp
PreCompiled.h
AspasiaZervaPlugin.cpp
RPSAspasiaZerva.cpp
RPSAspasiaZerva.h
)

SET(Metadata_Files
AspasiaZervaPlugin.txt

)


SET(AspasiaZervaPluginIcon_SVG
    # Resources/icons/AspasiaZervaPluginWorkbench.svg
)

add_library(AspasiaZervaPlugin SHARED ${AspasiaZervaPlugin_SRCS} ${Metadata_Files} ${AspasiaZervaPluginIcon_SVG})
target_link_libraries(AspasiaZervaPlugin ${AspasiaZervaPlugin_LIBS})
set_target_properties(AspasiaZervaPlugin PROPERTIES FOLDER "Plugins/SeismicLab")


SET_BIN_DIR(AspasiaZervaPlugin AspasiaZervaPlugin /Plugins/SeismicLabWorkbench/AspasiaZervaPlugin)

rps_copy_sources(AspasiaZervaPlugin "${CMAKE_BINARY_DIR}/Plugins/SeismicLabWorkbench/AspasiaZervaPlugin" ${Metadata_Files})
INSTALL(TARGETS AspasiaZervaPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/AspasiaZervaPlugin")
INSTALL(FILES AspasiaZervaPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/AspasiaZervaPlugin")
INSTALL(FILES ${AspasiaZervaPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/SeismicLab/AspasiaZervaPlugin/Resources/icons")

