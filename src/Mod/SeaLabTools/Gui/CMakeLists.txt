include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(SeaLabToolsGui_LIBS
    LabRPSGui 
)

if(BUILD_QT5)
    qt5_add_resources(SeaLabToolsGui_SRCS Resources/SeaLabPythonAPI.qrc)
else()
    qt4_add_resources(SeaLabToolsGui_SRCS Resources/SeaLabPythonAPI.qrc)
endif()

set(SeaLabToolsGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(SeaLabToolsGui_UIC_HDRS ${SeaLabToolsGui_UIC_SRCS})
else()
    qt4_wrap_ui(SeaLabToolsGui_UIC_HDRS ${SeaLabToolsGui_UIC_SRCS})
endif()

SET(SeaLabToolsGui_SRCS
    AppSeaLabToolsGui.cpp
    ${SeaLabToolsGui_UIC_SRCS}
    PreCompiled.cpp
    PreCompiled.h
)

add_library(SeaLabToolsGui SHARED ${SeaLabToolsGui_SRCS})
target_link_libraries(SeaLabToolsGui ${SeaLabToolsGui_LIBS})
set_target_properties(SeaLabToolsGui PROPERTIES FOLDER "Workbenches/SeaLabTools")

SET_BIN_DIR(SeaLabToolsGui SeaLabToolsGui /Mod/SeaLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(SeaLabToolsGui)
    
install(TARGETS SeaLabToolsGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
