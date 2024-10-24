add_compile_definitions(RPS_BUILDING_CORE)

IF (BUILD_GUI)
    PYSIDE_WRAP_RC(SeaLabPythonAPI_QRC_SRCS Resources/SeaLabPythonAPI.qrc)
ENDIF (BUILD_GUI)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(SeaLabAPIGui_LIBS
    SeaLabAPI
    LabRPSGui
    Alphaplot
)

if(BUILD_QT5)
    qt5_add_resources(SeaLabAPIGui_SRCS Resources/SeaLabPythonAPI.qrc)
else()
    qt4_add_resources(SeaLabAPIGui_SRCS Resources/SeaLabPythonAPI.qrc)
endif()

set(SeaLabAPIGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(SeaLabAPIGui_UIC_HDRS ${SeaLabAPIGui_UIC_SRCS})
else()
    qt4_wrap_ui(SeaLabAPIGui_UIC_HDRS ${SeaLabAPIGui_UIC_SRCS})
endif()

SET(SeaLabAPIGui_SRCS
    AppSeaLabAPIGui.cpp
    ${SeaLabAPIGui_UIC_SRCS}
    Resources/SeaLabPythonAPI.qrc
    PreCompiled.cpp
    PreCompiled.h
)

add_library(SeaLabAPIGui SHARED ${SeaLabAPIGui_SRCS})
target_link_libraries(SeaLabAPIGui ${SeaLabAPIGui_LIBS})
set_target_properties(SeaLabAPIGui PROPERTIES FOLDER "Workbenches/SeaLabAPI")

SET_BIN_DIR(SeaLabAPIGui SeaLabAPIGui /Mod/SeaLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(SeaLabAPIGui)
    
install(TARGETS SeaLabAPIGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
