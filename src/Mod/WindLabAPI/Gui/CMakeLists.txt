add_compile_definitions(RPS_BUILDING_CORE)

IF (BUILD_GUI)
    PYSIDE_WRAP_RC(WindLabPythonAPI_QRC_SRCS Resources/WindLabPythonAPI.qrc)
ENDIF (BUILD_GUI)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(WindLabAPIGui_LIBS
    WindLabAPI
    LabRPSGui
    Alphaplot
)

if(BUILD_QT5)
    qt5_add_resources(WindLabAPIGui_SRCS Resources/WindLabPythonAPI.qrc)
else()
    qt4_add_resources(WindLabAPIGui_SRCS Resources/WindLabPythonAPI.qrc)
endif()

set(WindLabAPIGui_UIC_SRCS

)

if(BUILD_QT5)
    qt5_wrap_ui(WindLabAPIGui_UIC_HDRS ${WindLabAPIGui_UIC_SRCS})
else()
    qt4_wrap_ui(WindLabAPIGui_UIC_HDRS ${WindLabAPIGui_UIC_SRCS})
endif()

SET(WindLabAPIGui_SRCS
    AppWindLabAPIGui.cpp
    ${WindLabAPIGui_UIC_SRCS}
    Resources/WindLabPythonAPI.qrc
    PreCompiled.cpp
    PreCompiled.h
)

add_library(WindLabAPIGui SHARED ${WindLabAPIGui_SRCS})
target_link_libraries(WindLabAPIGui ${WindLabAPIGui_LIBS})
set_target_properties(WindLabAPIGui PROPERTIES FOLDER "Workbenches/WindLabAPI")

SET_BIN_DIR(WindLabAPIGui WindLabAPIGui /Mod/WindLabPythonAPI)
SET_PYTHON_PREFIX_SUFFIX(WindLabAPIGui)
    
install(TARGETS WindLabAPIGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
