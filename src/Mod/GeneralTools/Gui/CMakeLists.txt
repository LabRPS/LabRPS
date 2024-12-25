include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(GeneralToolsGui_LIBS
    LabRPSGui 
)

if(BUILD_QT5)
    qt5_add_resources(GeneralToolsGui_SRCS Resources/WindLabPythonAPI.qrc)
else()
    qt4_add_resources(GeneralToolsGui_SRCS Resources/WindLabPythonAPI.qrc)
endif()

set(GeneralToolsGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(GeneralToolsGui_UIC_HDRS ${GeneralToolsGui_UIC_SRCS})
else()
    qt4_wrap_ui(GeneralToolsGui_UIC_HDRS ${GeneralToolsGui_UIC_SRCS})
endif()

SET(GeneralToolsGui_SRCS
    AppGeneralToolsGui.cpp
    ${GeneralToolsGui_UIC_SRCS}
    PreCompiled.cpp
    PreCompiled.h
    RPSGeneralToolsPyTool.h
    RPSGeneralToolsPyTool.cpp
)

add_library(GeneralToolsGui SHARED ${GeneralToolsGui_SRCS})
target_link_libraries(GeneralToolsGui ${GeneralToolsGui_LIBS})
set_target_properties(GeneralToolsGui PROPERTIES FOLDER "Workbenches/GeneralTools")

SET_BIN_DIR(GeneralToolsGui GeneralToolsGui /Mod/WindLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(GeneralToolsGui)
    
install(TARGETS GeneralToolsGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
