# Aspect framework legacy code
add_compile_definitions(LEGACY_CODE_0_2_x)

# Enable OpenGL for QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_OPENGL)

add_compile_definitions(RPS_BUILDING_CORE)

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
    ${PYTHON_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${XercesC_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

generate_from_xml(ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethodPy)
generate_from_xml(ViewProviderUserDefinedPhenomenonLabSimulationPy)
generate_from_xml(ViewProviderUserDefinedPhenomenonLabSimulationComparisonPy)


# The XML files
set(UserDefinedPhenomenonLabGui_XML_SRCS
    ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethodPy.xml
    ViewProviderUserDefinedPhenomenonLabSimulationPy.xml
    ViewProviderUserDefinedPhenomenonLabSimulationComparisonPy.xml
)

set(UserDefinedPhenomenonLabGui_LIBS
    UserDefinedPhenomenonLabAPI
    UserDefinedPhenomenonLab
    LabRPSGui
    LabRPSApp
    Part
)

if(BUILD_QT5)
    qt5_add_resources(UserDefinedPhenomenonLabGui_SRCS Resources/UserDefinedPhenomenonLab.qrc)
else()
    qt4_add_resources(UserDefinedPhenomenonLabGui_SRCS Resources/UserDefinedPhenomenonLab.qrc)
endif()

set(UserDefinedPhenomenonLabGui_UIC_SRCS
DlgNewSimulation.ui
DlgUserDefinedPhenomenonLabFeatures.ui
DlgUserDefinedPhenomenonLabFeaturesCreation.ui
DlgSimulationComparison.ui
DlgSettingsUserDefinedPhenomenonLabLimit.ui
DlgSettingsUserDefinedPhenomenonLabGeneral.ui

)


SET(UserDefinedPhenomenonLabGui_DLG_SRCS
    ${UserDefinedPhenomenonLabGui_UIC_HDRS}
    DlgSettingsUserDefinedPhenomenonLabLimit.ui
    DlgSettingsUserDefinedPhenomenonLabLimitImp.cpp
    DlgSettingsUserDefinedPhenomenonLabLimitImp.h
    DlgSettingsUserDefinedPhenomenonLabGeneral.ui
    DlgSettingsUserDefinedPhenomenonLabGeneralImp.cpp
    DlgSettingsUserDefinedPhenomenonLabGeneralImp.h

)

SOURCE_GROUP("Setting-Dialogs" FILES ${UserDefinedPhenomenonLabGui_DLG_SRCS})


if(BUILD_QT5)
    qt5_wrap_ui(UserDefinedPhenomenonLabGui_UIC_HDRS ${UserDefinedPhenomenonLabGui_UIC_SRCS})
else()
    qt4_wrap_ui(UserDefinedPhenomenonLabGui_UIC_HDRS ${UserDefinedPhenomenonLabGui_UIC_SRCS})
endif()

SET(ViewProvider_CPP_SRCS
ViewProviderUserDefinedPhenomenonLabSimulation.cpp
DlgUserDefinedPhenomenonLabFeaturesCreation.cpp
DlgSimulationComparison.cpp
ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod.cpp
ViewProviderUserDefinedPhenomenonLabSimulation.cpp
ViewProviderUserDefinedPhenomenonLabSimulationComparison.cpp

ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethodPyImp.cpp
ViewProviderUserDefinedPhenomenonLabSimulationPyImp.cpp
ViewProviderUserDefinedPhenomenonLabSimulationComparisonPyImp.cpp

)
SET(ViewProvider_HPP_SRCS
ViewProviderUserDefinedPhenomenonLabSimulation.h
DlgUserDefinedPhenomenonLabFeaturesCreation.h
DlgSimulationComparison.h
ViewProviderUserDefinedPhenomenonLabFeatureSimulationMethod.h
ViewProviderUserDefinedPhenomenonLabSimulationComparison.h
)

SET(ViewProvider_SRCS
    ${ViewProvider_CPP_SRCS}
    ${ViewProvider_HPP_SRCS}
    ${UserDefinedPhenomenonLabGui_XML_SRCS}

)
SOURCE_GROUP("ViewProvider" FILES ${ViewProvider_SRCS})

SET(UserDefinedPhenomenonLabGui_SRCS
    ${UserDefinedPhenomenonLabGui_SRCS}
    ${UserDefinedPhenomenonLabGui_UIC_HDRS}
    ${ViewProvider_SRCS}
    ${UserDefinedPhenomenonLabGui_DLG_SRCS}
    AppUserDefinedPhenomenonLabGui.cpp
    Command.cpp
    Resources/UserDefinedPhenomenonLab.qrc
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
    DlgNewSimulation.cpp
    DlgNewSimulation.h
    RPSUserDefinedPhenomenonLabPyTool.cpp
    RPSUserDefinedPhenomenonLabPyTool.h
    UserDefinedPhenomenonLabSimulationObserver.h
    UserDefinedPhenomenonLabSimulationObserver.cpp
    UserDefinedPhenomenonLabSimulationWorker.h
    UserDefinedPhenomenonLabSimulationWorker.cpp
    UserDefinedPhenomenonLabAllFeaturesComputation.h
    UserDefinedPhenomenonLabAllFeaturesComputation.cpp
    UserDefinedPhenomenonLabComparisonStarter.h
    UserDefinedPhenomenonLabComparisonStarter.cpp

)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" PCH_SRCS ${UserDefinedPhenomenonLabGui_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(UserDefinedPhenomenonLabGui PreCompiled.h PreCompiled.cpp PCH_SRCS)
endif(LABRPS_USE_PCH)


SET(UserDefinedPhenomenonLabGuiIcon_SVG
    Resources/icons/UserDefinedPhenomenonLabWorkbench.svg
)

add_library(UserDefinedPhenomenonLabGui SHARED ${UserDefinedPhenomenonLabGui_SRCS} ${UserDefinedPhenomenonLabGuiIcon_SVG})
target_link_libraries(UserDefinedPhenomenonLabGui ${UserDefinedPhenomenonLabGui_LIBS})
set_target_properties(UserDefinedPhenomenonLabGui PROPERTIES FOLDER "Workbenches/UserDefinedPhenomenonLab")


SET_BIN_DIR(UserDefinedPhenomenonLabGui UserDefinedPhenomenonLabGui /Mod/UserDefinedPhenomenonLab)
SET_PYTHON_PREFIX_SUFFIX(UserDefinedPhenomenonLabGui)

rps_copy_sources(UserDefinedPhenomenonLabGui "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Mod/UserDefinedPhenomenonLab" ${UserDefinedPhenomenonLabGuiIcon_SVG})

INSTALL(TARGETS UserDefinedPhenomenonLabGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(FILES ${UserDefinedPhenomenonLabGuiIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Mod/UserDefinedPhenomenonLab/Resources/icons")
