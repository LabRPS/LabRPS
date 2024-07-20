add_compile_definitions(RPS_BUILDING_CORE)

IF (BUILD_GUI)
    PYSIDE_WRAP_RC(SeismicLabPythonAPI_QRC_SRCS Resources/SeismicLabPythonAPI.qrc)
ENDIF (BUILD_GUI)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${COIN3D_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(SeismicLabAPIGui_LIBS
    SeismicLabAPI
    LabRPSGui
    Alphaplot
)

if(BUILD_QT5)
    qt5_add_resources(SeismicLabAPIGui_SRCS Resources/SeismicLabPythonAPI.qrc)
else()
    qt4_add_resources(SeismicLabAPIGui_SRCS Resources/SeismicLabPythonAPI.qrc)
endif()

set(SeismicLabAPIGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(SeismicLabAPIGui_UIC_HDRS ${SeismicLabAPIGui_UIC_SRCS})
else()
    qt4_wrap_ui(SeismicLabAPIGui_UIC_HDRS ${SeismicLabAPIGui_UIC_SRCS})
endif()

SET(SeismicLabAPIGui_SRCS
    AppSeismicLabAPIGui.cpp
    ${SeismicLabAPIGui_UIC_SRCS}
    Resources/SeismicLabPythonAPI.qrc
    PreCompiled.cpp
    PreCompiled.h
)

add_library(SeismicLabAPIGui SHARED ${SeismicLabAPIGui_SRCS})
target_link_libraries(SeismicLabAPIGui ${SeismicLabAPIGui_LIBS})
set_target_properties(SeismicLabAPIGui PROPERTIES FOLDER "Workbenches/SeismicLabAPI")

SET_BIN_DIR(SeismicLabAPIGui SeismicLabAPIGui /Mod/SeismicLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(SeismicLabAPIGui)
    
install(TARGETS SeismicLabAPIGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
