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

set(DesignResponseSpectrumPlugin_LIBS
    LabRPSGui
    SeismicLabAPI
    GeneralTools
    SeismicLabTools
)


set(DesignResponseSpectrumPlugin_UIC_SRCS

widgets/DlgDesignResponseSpectrum.ui


)

if(BUILD_QT5)
    qt5_wrap_ui(DesignResponseSpectrumPlugin_UIC_HDRS ${DesignResponseSpectrumPlugin_UIC_SRCS})
else()
    qt4_wrap_ui(DesignResponseSpectrumPlugin_UIC_HDRS ${DesignResponseSpectrumPlugin_UIC_SRCS})
endif()

SET(DesignResponseSpectrumPlugin_SRCS
    ${DesignResponseSpectrumPlugin_SRCS}
    ${DesignResponseSpectrumPlugin_UIC_HDRS}
    DesignResponseSpectrum.cpp
    DesignResponseSpectrum.h
    DesignResponseSpectrumPlugin.cpp
    widgets/DlgDesignResponseSpectrum.h
    widgets/DlgDesignResponseSpectrum.cpp


)

SET(Metadata_Files
DesignResponseSpectrumPlugin.txt

)


SET(DesignResponseSpectrumPluginIcon_SVG
    # Resources/icons/DesignResponseSpectrumPluginWorkbench.svg
)

add_library(DesignResponseSpectrumPlugin SHARED ${DesignResponseSpectrumPlugin_SRCS} ${Metadata_Files} ${DesignResponseSpectrumPluginIcon_SVG})
target_link_libraries(DesignResponseSpectrumPlugin ${DesignResponseSpectrumPlugin_LIBS})
set_target_properties(DesignResponseSpectrumPlugin PROPERTIES FOLDER "Plugins/SeismicLab")


SET_BIN_DIR(DesignResponseSpectrumPlugin DesignResponseSpectrumPlugin /Plugins/SeismicLabWorkbench/DesignResponseSpectrumPlugin)

rps_copy_sources(DesignResponseSpectrumPlugin "${CMAKE_BINARY_DIR}/Plugins/SeismicLabWorkbench/DesignResponseSpectrumPlugin" ${Metadata_Files})
INSTALL(TARGETS DesignResponseSpectrumPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/DesignResponseSpectrumPlugin")
INSTALL(FILES DesignResponseSpectrumPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/DesignResponseSpectrumPlugin")
INSTALL(FILES ${DesignResponseSpectrumPluginIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/SeismicLab/DesignResponseSpectrumPlugin/Resources/icons")

