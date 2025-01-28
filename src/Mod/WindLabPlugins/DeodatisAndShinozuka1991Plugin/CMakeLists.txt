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

set(DeodatisAndShinozuka1991Plugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

if(BUILD_QT5)
    qt5_add_resources(DeodatisAndShinozuka1991Plugin_SRCS Resources/DeodatisAndShinozuka1991Plugin.qrc)
else()
    qt4_add_resources(DeodatisAndShinozuka1991Plugin_SRCS Resources/DeodatisAndShinozuka1991Plugin.qrc)
endif()

set(DeodatisAndShinozuka1991Plugin_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(DeodatisAndShinozuka1991Plugin_UIC_HDRS ${DeodatisAndShinozuka1991Plugin_UIC_SRCS})
else()
    qt4_wrap_ui(DeodatisAndShinozuka1991Plugin_UIC_HDRS ${DeodatisAndShinozuka1991Plugin_UIC_SRCS})
endif()

SET(DeodatisAndShinozuka1991Plugin_SRCS
${DeodatisAndShinozuka1991Plugin_SRCS}
${DeodatisAndShinozuka1991Plugin_UIC_HDRS}
Resources/DeodatisAndShinozuka1991Plugin.qrc
PreCompiled.cpp
PreCompiled.h
DeodatisAndShinozuka1991Plugin.cpp
DeodatisAndShinozuka1991.h
DeodatisAndShinozuka1991.cpp
)

SET(Metadata_Files
DeodatisAndShinozuka1991Plugin.txt

)


SET(DeodatisAndShinozuka1991PluginIcon_SVG
    # Resources/icons/DeodatisAndShinozuka1991PluginWorkbench.svg
)

add_library(DeodatisAndShinozuka1991Plugin SHARED ${DeodatisAndShinozuka1991Plugin_SRCS} ${Metadata_Files} ${DeodatisAndShinozuka1991PluginIcon_SVG})
target_link_libraries(DeodatisAndShinozuka1991Plugin ${DeodatisAndShinozuka1991Plugin_LIBS})
set_target_properties(DeodatisAndShinozuka1991Plugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(DeodatisAndShinozuka1991Plugin DeodatisAndShinozuka1991Plugin /Plugins/WindLabWorkbench/DeodatisAndShinozuka1991Plugin)

rps_copy_sources(DeodatisAndShinozuka1991Plugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/DeodatisAndShinozuka1991Plugin" ${Metadata_Files})
INSTALL(TARGETS DeodatisAndShinozuka1991Plugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/DeodatisAndShinozuka1991Plugin")
INSTALL(FILES DeodatisAndShinozuka1991Plugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/DeodatisAndShinozuka1991Plugin")
INSTALL(FILES ${DeodatisAndShinozuka1991PluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/DeodatisAndShinozuka1991Plugin/Resources/icons")

