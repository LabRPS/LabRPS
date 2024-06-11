include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(WindLabToolsGui_LIBS
    LabRPSGui 
)

if(BUILD_QT5)
    qt5_add_resources(WindLabToolsGui_SRCS Resources/WindLabPythonAPI.qrc)
else()
    qt4_add_resources(WindLabToolsGui_SRCS Resources/WindLabPythonAPI.qrc)
endif()

set(WindLabToolsGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(WindLabToolsGui_UIC_HDRS ${WindLabToolsGui_UIC_SRCS})
else()
    qt4_wrap_ui(WindLabToolsGui_UIC_HDRS ${WindLabToolsGui_UIC_SRCS})
endif()

SET(WindLabToolsGui_SRCS
    AppWindLabToolsGui.cpp
    ${WindLabToolsGui_UIC_SRCS}
    PreCompiled.cpp
    PreCompiled.h
)

add_library(WindLabToolsGui SHARED ${WindLabToolsGui_SRCS})
target_link_libraries(WindLabToolsGui ${WindLabToolsGui_LIBS})
set_target_properties(WindLabToolsGui PROPERTIES FOLDER "Workbenches/WindLabTools")

SET_BIN_DIR(WindLabToolsGui WindLabToolsGui /Mod/WindLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(WindLabToolsGui)
    
install(TARGETS WindLabToolsGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
