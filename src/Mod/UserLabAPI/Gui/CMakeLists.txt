add_compile_definitions(RPS_BUILDING_CORE)

IF (BUILD_GUI)
    PYSIDE_WRAP_RC(UserLabPythonAPI_QRC_SRCS Resources/UserLabPythonAPI.qrc)
ENDIF (BUILD_GUI)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(UserLabAPIGui_LIBS
    UserLabAPI
    LabRPSGui
)

if(BUILD_QT5)
    qt5_add_resources(UserLabAPIGui_SRCS Resources/UserLabPythonAPI.qrc)
else()
    qt4_add_resources(UserLabAPIGui_SRCS Resources/UserLabPythonAPI.qrc)
endif()

set(UserLabAPIGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(UserLabAPIGui_UIC_HDRS ${UserLabAPIGui_UIC_SRCS})
else()
    qt4_wrap_ui(UserLabAPIGui_UIC_HDRS ${UserLabAPIGui_UIC_SRCS})
endif()

SET(UserLabAPIGui_SRCS
    AppUserLabAPIGui.cpp
    ${UserLabAPIGui_UIC_SRCS}
    Resources/UserLabPythonAPI.qrc
    PreCompiled.cpp
    PreCompiled.h
)

add_library(UserLabAPIGui SHARED ${UserLabAPIGui_SRCS})
target_link_libraries(UserLabAPIGui ${UserLabAPIGui_LIBS})
set_target_properties(UserLabAPIGui PROPERTIES FOLDER "Workbenches/UserLabAPI")

SET_BIN_DIR(UserLabAPIGui UserLabAPIGui /Mod/UserLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(UserLabAPIGui)
    
install(TARGETS UserLabAPIGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
