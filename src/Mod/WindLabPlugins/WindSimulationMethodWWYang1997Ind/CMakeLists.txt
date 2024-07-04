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
    ${EIGEN3_INCLUDE_DIR}
)

set(WindSimulationMethodWWYang1997Ind_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

# if(BUILD_QT5)
#     qt5_add_resources(WindSimulationMethodWWYang1997Ind_SRCS Resources/WindSimulationMethodWWYang1997Ind.qrc)
# else()
#     qt4_add_resources(WindSimulationMethodWWYang1997Ind_SRCS Resources/WindSimulationMethodWWYang1997Ind.qrc)
# endif()

set(WindSimulationMethodWWYang1997Ind_UIC_SRCS
widgets/wwyang1997indinputdlg.ui


)

if(BUILD_QT5)
    qt5_wrap_ui(WindSimulationMethodWWYang1997Ind_UIC_HDRS ${WindSimulationMethodWWYang1997Ind_UIC_SRCS})
else()
    qt4_wrap_ui(WindSimulationMethodWWYang1997Ind_UIC_HDRS ${WindSimulationMethodWWYang1997Ind_UIC_SRCS})
endif()

SET(WindSimulationMethodWWYang1997Ind_SRCS
    ${WindSimulationMethodWWYang1997Ind_SRCS}
    ${WindSimulationMethodWWYang1997Ind_UIC_HDRS}
    widgets/wwyang1997indinputdlg.cpp
    WWYang1997Ind.cpp
    WindSimulationMethodWWYang1997Ind.cpp
    widgets/wwyang1997indinputdlg.h
    WWYang1997Ind.h


)

SET(Metadata_Files
WindSimulationMethodWWYang1997Ind.txt

)


SET(WindSimulationMethodWWYang1997IndIcon_SVG
    # Resources/icons/WindSimulationMethodWWYang1997IndWorkbench.svg
)

add_library(WindSimulationMethodWWYang1997Ind SHARED ${WindSimulationMethodWWYang1997Ind_SRCS} ${Metadata_Files} ${WindSimulationMethodWWYang1997IndIcon_SVG})
target_link_libraries(WindSimulationMethodWWYang1997Ind ${WindSimulationMethodWWYang1997Ind_LIBS})
set_target_properties(WindSimulationMethodWWYang1997Ind PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(WindSimulationMethodWWYang1997Ind WindSimulationMethodWWYang1997Ind /Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997Ind)

rps_copy_sources(WindSimulationMethodWWYang1997Ind "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997Ind" ${Metadata_Files})
INSTALL(TARGETS WindSimulationMethodWWYang1997Ind DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997Ind")
INSTALL(FILES WindSimulationMethodWWYang1997Ind.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997Ind")
INSTALL(FILES ${WindSimulationMethodWWYang1997IndIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/WindSimulationMethodWWYang1997Ind/Resources/icons")
