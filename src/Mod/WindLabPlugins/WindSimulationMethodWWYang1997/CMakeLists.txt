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

set(WindSimulationMethodWWYang1997_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

set(WindSimulationMethodWWYang1997_UIC_SRCS


)

SET(WindSimulationMethodWWYang1997_SRCS
    ${WindSimulationMethodWWYang1997_SRCS}
    WWYang1997.cpp
    WindSimulationMethodWWYang1997.cpp
    WWYang1997.h
)

SET(Metadata_Files
WindSimulationMethodWWYang1997.txt

)


SET(WindSimulationMethodWWYang1997Icon_SVG
    # Resources/icons/WindSimulationMethodWWYang1997Workbench.svg
)

add_library(WindSimulationMethodWWYang1997 SHARED ${WindSimulationMethodWWYang1997_SRCS} ${Metadata_Files} ${WindSimulationMethodWWYang1997Icon_SVG})
target_link_libraries(WindSimulationMethodWWYang1997 ${WindSimulationMethodWWYang1997_LIBS})
set_target_properties(WindSimulationMethodWWYang1997 PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(WindSimulationMethodWWYang1997 WindSimulationMethodWWYang1997 /Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997)

rps_copy_sources(WindSimulationMethodWWYang1997 "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997" ${Metadata_Files})
INSTALL(TARGETS WindSimulationMethodWWYang1997 DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997")
INSTALL(FILES WindSimulationMethodWWYang1997.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindSimulationMethodWWYang1997")
INSTALL(FILES ${WindSimulationMethodWWYang1997Icon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/WindSimulationMethodWWYang1997/Resources/icons")

