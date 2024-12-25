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

generate_from_xml(ViewProviderUserLabFeatureSimulationMethodPy)
generate_from_xml(ViewProviderUserLabSimulationPy)

# The XML files
set(UserLabGui_XML_SRCS
    ViewProviderUserLabFeatureSimulationMethodPy.xml
    ViewProviderUserLabSimulationPy.xml
)

set(UserLabGui_LIBS
    UserLabAPI
    UserLab
    LabRPSGui
    LabRPSApp
)

if(BUILD_QT5)
    qt5_add_resources(UserLabGui_SRCS Resources/UserLab.qrc)
else()
    qt4_add_resources(UserLabGui_SRCS Resources/UserLab.qrc)
endif()

set(UserLabGui_UIC_SRCS
DlgNewSimulation.ui
DlgUserLabFeatures.ui
DlgUserLabFeaturesCreation.ui
DlgSettingsUserLabLimit.ui
DlgSettingsUserLabGeneral.ui

)


SET(UserLabGui_DLG_SRCS
    ${UserLabGui_UIC_HDRS}
    DlgSettingsUserLabLimit.ui
    DlgSettingsUserLabLimitImp.cpp
    DlgSettingsUserLabLimitImp.h
    DlgSettingsUserLabGeneral.ui
    DlgSettingsUserLabGeneralImp.cpp
    DlgSettingsUserLabGeneralImp.h

)

SOURCE_GROUP("Setting-Dialogs" FILES ${UserLabGui_DLG_SRCS})


if(BUILD_QT5)
    qt5_wrap_ui(UserLabGui_UIC_HDRS ${UserLabGui_UIC_SRCS})
else()
    qt4_wrap_ui(UserLabGui_UIC_HDRS ${UserLabGui_UIC_SRCS})
endif()

SET(ViewProvider_CPP_SRCS
ViewProviderUserLabSimulation.cpp
DlgUserLabFeaturesCreation.cpp
ViewProviderUserLabFeatureSimulationMethod.cpp
ViewProviderUserLabSimulation.cpp

ViewProviderUserLabFeatureSimulationMethodPyImp.cpp
ViewProviderUserLabSimulationPyImp.cpp

)
SET(ViewProvider_HPP_SRCS
ViewProviderUserLabSimulation.h
DlgUserLabFeaturesCreation.h
ViewProviderUserLabFeatureSimulationMethod.h
)

SET(ViewProvider_SRCS
    ${ViewProvider_CPP_SRCS}
    ${ViewProvider_HPP_SRCS}
    ${UserLabGui_XML_SRCS}

)
SOURCE_GROUP("ViewProvider" FILES ${ViewProvider_SRCS})

SET(UserLabGui_SRCS
    ${UserLabGui_SRCS}
    ${UserLabGui_UIC_HDRS}
    ${ViewProvider_SRCS}
    ${UserLabGui_DLG_SRCS}
    AppUserLabGui.cpp
    Command.cpp
    Resources/UserLab.qrc
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
    DlgNewSimulation.cpp
    DlgNewSimulation.h
    UserLabSimulationObserver.h
    UserLabSimulationObserver.cpp
    UserLabSimulationWorker.h
    UserLabSimulationWorker.cpp
    UserLabAllFeaturesComputation.h
    UserLabAllFeaturesComputation.cpp
)

if(LABRPS_USE_PCH)
    add_definitions(-D_PreComp_)
    GET_MSVC_PRECOMPILED_SOURCE("PreCompiled.cpp" PCH_SRCS ${UserLabGui_SRCS})
    ADD_MSVC_PRECOMPILED_HEADER(UserLabGui PreCompiled.h PreCompiled.cpp PCH_SRCS)
endif(LABRPS_USE_PCH)


SET(UserLabGuiIcon_SVG
    Resources/icons/UserLabWorkbench.svg
)

add_library(UserLabGui SHARED ${UserLabGui_SRCS} ${UserLabGuiIcon_SVG})
target_link_libraries(UserLabGui ${UserLabGui_LIBS})
set_target_properties(UserLabGui PROPERTIES FOLDER "Workbenches/UserLab")


SET_BIN_DIR(UserLabGui UserLabGui /Mod/UserLab)
SET_PYTHON_PREFIX_SUFFIX(UserLabGui)

rps_copy_sources(UserLabGui "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Mod/UserLab" ${UserLabGuiIcon_SVG})

INSTALL(TARGETS UserLabGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(FILES ${UserLabGuiIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Mod/UserLab/Resources/icons")
