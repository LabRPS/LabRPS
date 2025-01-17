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

set(DeodatisAndShinozyka1991Plugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

if(BUILD_QT5)
    qt5_add_resources(DeodatisAndShinozyka1991Plugin_SRCS Resources/DeodatisAndShinozyka1991Plugin.qrc)
else()
    qt4_add_resources(DeodatisAndShinozyka1991Plugin_SRCS Resources/DeodatisAndShinozyka1991Plugin.qrc)
endif()

set(DeodatisAndShinozyka1991Plugin_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(DeodatisAndShinozyka1991Plugin_UIC_HDRS ${DeodatisAndShinozyka1991Plugin_UIC_SRCS})
else()
    qt4_wrap_ui(DeodatisAndShinozyka1991Plugin_UIC_HDRS ${DeodatisAndShinozyka1991Plugin_UIC_SRCS})
endif()

SET(DeodatisAndShinozyka1991Plugin_SRCS
${DeodatisAndShinozyka1991Plugin_SRCS}
${DeodatisAndShinozyka1991Plugin_UIC_HDRS}
Resources/DeodatisAndShinozyka1991Plugin.qrc
PreCompiled.cpp
PreCompiled.h
DeodatisAndShinozyka1991Plugin.cpp
DeodatisAndShinozyka1991.h
DeodatisAndShinozyka1991.cpp
)

SET(Metadata_Files
DeodatisAndShinozyka1991Plugin.txt

)


SET(DeodatisAndShinozyka1991PluginIcon_SVG
    # Resources/icons/DeodatisAndShinozyka1991PluginWorkbench.svg
)

add_library(DeodatisAndShinozyka1991Plugin SHARED ${DeodatisAndShinozyka1991Plugin_SRCS} ${Metadata_Files} ${DeodatisAndShinozyka1991PluginIcon_SVG})
target_link_libraries(DeodatisAndShinozyka1991Plugin ${DeodatisAndShinozyka1991Plugin_LIBS})
set_target_properties(DeodatisAndShinozyka1991Plugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(DeodatisAndShinozyka1991Plugin DeodatisAndShinozyka1991Plugin /Plugins/WindLabWorkbench/DeodatisAndShinozyka1991Plugin)

rps_copy_sources(DeodatisAndShinozyka1991Plugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/DeodatisAndShinozyka1991Plugin" ${Metadata_Files})
INSTALL(TARGETS DeodatisAndShinozyka1991Plugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/DeodatisAndShinozyka1991Plugin")
INSTALL(FILES DeodatisAndShinozyka1991Plugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/DeodatisAndShinozyka1991Plugin")
INSTALL(FILES ${DeodatisAndShinozyka1991PluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/DeodatisAndShinozyka1991Plugin/Resources/icons")

