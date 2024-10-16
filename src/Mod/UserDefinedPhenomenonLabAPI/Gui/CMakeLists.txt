add_compile_definitions(RPS_BUILDING_CORE)

IF (BUILD_GUI)
    PYSIDE_WRAP_RC(UserDefinedPhenomenonLabPythonAPI_QRC_SRCS Resources/UserDefinedPhenomenonLabPythonAPI.qrc)
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

set(UserDefinedPhenomenonLabAPIGui_LIBS
    UserDefinedPhenomenonLabAPI
    LabRPSGui
)

if(BUILD_QT5)
    qt5_add_resources(UserDefinedPhenomenonLabAPIGui_SRCS Resources/UserDefinedPhenomenonLabPythonAPI.qrc)
else()
    qt4_add_resources(UserDefinedPhenomenonLabAPIGui_SRCS Resources/UserDefinedPhenomenonLabPythonAPI.qrc)
endif()

set(UserDefinedPhenomenonLabAPIGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(UserDefinedPhenomenonLabAPIGui_UIC_HDRS ${UserDefinedPhenomenonLabAPIGui_UIC_SRCS})
else()
    qt4_wrap_ui(UserDefinedPhenomenonLabAPIGui_UIC_HDRS ${UserDefinedPhenomenonLabAPIGui_UIC_SRCS})
endif()

SET(UserDefinedPhenomenonLabAPIGui_SRCS
    AppUserDefinedPhenomenonLabAPIGui.cpp
    ${UserDefinedPhenomenonLabAPIGui_UIC_SRCS}
    Resources/UserDefinedPhenomenonLabPythonAPI.qrc
    PreCompiled.cpp
    PreCompiled.h
)

add_library(UserDefinedPhenomenonLabAPIGui SHARED ${UserDefinedPhenomenonLabAPIGui_SRCS})
target_link_libraries(UserDefinedPhenomenonLabAPIGui ${UserDefinedPhenomenonLabAPIGui_LIBS})
set_target_properties(UserDefinedPhenomenonLabAPIGui PROPERTIES FOLDER "Workbenches/UserDefinedPhenomenonLabAPI")

SET_BIN_DIR(UserDefinedPhenomenonLabAPIGui UserDefinedPhenomenonLabAPIGui /Mod/UserDefinedPhenomenonLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(UserDefinedPhenomenonLabAPIGui)
    
install(TARGETS UserDefinedPhenomenonLabAPIGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
