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

set(generalizedSpectrum_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

if(BUILD_QT5)
    qt5_add_resources(generalizedSpectrum_SRCS data/icons.qrc)
else()
    qt4_add_resources(generalizedSpectrum_SRCS data/icons.qrc)
endif()

set(generalizedSpectrum_UIC_SRCS
 Widgets/DlgGeneralizedKaimalSpectrum.ui
 Widgets/DlgGeneralizedVonKarmanSpectrum.ui
 
)

if(BUILD_QT5)
    qt5_wrap_ui(generalizedSpectrum_UIC_HDRS ${generalizedSpectrum_UIC_SRCS})
else()
    qt4_wrap_ui(generalizedSpectrum_UIC_HDRS ${generalizedSpectrum_UIC_SRCS})
endif()

SET(generalizedSpectrum_SRCS
    ${generalizedSpectrum_SRCS}
    ${generalizedSpectrum_UIC_HDRS}
    PreCompiled.cpp
    PreCompiled.h
    widgets/IconLoader.cpp
    widgets/IconLoader.h
    GeneralizedAlongWindKaimalSpectrum.cpp
    GeneralizedAcrossWindKaimalSpectrum.cpp
    GeneralizedVerticalWindKaimalSpectrum.cpp
    GeneralizedAlongWindVonKarmanSpectrum.cpp
    GeneralizedAcrossWindVonKarmanSpectrum.cpp
    GeneralizedVerticalWindVonKarmanSpectrum.cpp
    GeneralizedSpectrum.cpp
    GeneralizedAlongWindKaimalSpectrum.h
    GeneralizedAcrossWindKaimalSpectrum.h
    GeneralizedVerticalWindKaimalSpectrum.h
    GeneralizedAlongWindVonKarmanSpectrum.h
    GeneralizedAcrossWindVonKarmanSpectrum.h
    GeneralizedVerticalWindVonKarmanSpectrum.h
    Widgets/DlgGeneralizedKaimalSpectrum.h
    Widgets/DlgGeneralizedKaimalSpectrum.cpp
    Widgets/DlgGeneralizedVonKarmanSpectrum.h
    Widgets/DlgGeneralizedVonKarmanSpectrum.cpp


)

SET(Metadata_Files
GeneralizedSpectrum.txt

)


SET(generalizedSpectrumIcon_SVG
    # Resources/icons/generalizedSpectrumWorkbench.svg
)

add_library(GeneralizedSpectrum SHARED ${generalizedSpectrum_SRCS} ${Metadata_Files} ${generalizedSpectrumIcon_SVG})
target_link_libraries(GeneralizedSpectrum ${generalizedSpectrum_LIBS})
set_target_properties(GeneralizedSpectrum PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(GeneralizedSpectrum GeneralizedSpectrum /Plugins/WindLabWorkbench/GeneralizedSpectrum)

fc_copy_sources(GeneralizedSpectrum "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/GeneralizedSpectrum" ${Metadata_Files})
INSTALL(TARGETS GeneralizedSpectrum DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/GeneralizedSpectrum")
INSTALL(FILES GeneralizedSpectrum.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/GeneralizedSpectrum")
INSTALL(FILES ${generalizedSpectrumIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/GeneralizedSpectrum/Resources/icons")

