include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(SeismicLabToolsGui_LIBS
    LabRPSGui 
)

if(BUILD_QT5)
    qt5_add_resources(SeismicLabToolsGui_SRCS Resources/SeismicLabPythonAPI.qrc)
else()
    qt4_add_resources(SeismicLabToolsGui_SRCS Resources/SeismicLabPythonAPI.qrc)
endif()

set(SeismicLabToolsGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(SeismicLabToolsGui_UIC_HDRS ${SeismicLabToolsGui_UIC_SRCS})
else()
    qt4_wrap_ui(SeismicLabToolsGui_UIC_HDRS ${SeismicLabToolsGui_UIC_SRCS})
endif()

SET(SeismicLabToolsGui_SRCS
    AppSeismicLabToolsGui.cpp
    ${SeismicLabToolsGui_UIC_SRCS}
    PreCompiled.cpp
    PreCompiled.h
)

add_library(SeismicLabToolsGui SHARED ${SeismicLabToolsGui_SRCS})
target_link_libraries(SeismicLabToolsGui ${SeismicLabToolsGui_LIBS})
set_target_properties(SeismicLabToolsGui PROPERTIES FOLDER "Workbenches/SeismicLabTools")

SET_BIN_DIR(SeismicLabToolsGui SeismicLabToolsGui /Mod/SeismicLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(SeismicLabToolsGui)
    
install(TARGETS SeismicLabToolsGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
