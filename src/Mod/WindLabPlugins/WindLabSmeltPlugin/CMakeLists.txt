# If you only include this third party in PRIVATE source files, you do not need to install it
# when your main project gets installed.
set(JSON_Install OFF CACHE INTERNAL "")

if(MSVC)
    add_definitions(-DHAVE_ACOSH -DHAVE_ATANH -DHAVE_ASINH)
else(MSVC)
    add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
endif(MSVC)

# Adding MATH defines for M_PI when building on Windows
if (WIN32)
  add_compile_definitions(_USE_MATH_DEFINES)
endif()

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(WindLabSmeltPlugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
    smelt
    kissfft
)

SET(WindLabSmeltPlugin_SRCS
WittigSinhaEqualFloors.h
WittigSinhaEqualFloors.cpp
WindLabSmeltPlugin.cpp
)

SET(Metadata_Files
WindLabSmeltPlugin.txt

)

SET(WindLabSmeltPluginIcon_SVG
    # Resources/icons/WindLabSmeltPluginWorkbench.svg
)

add_library(WindLabSmeltPlugin SHARED ${WindLabSmeltPlugin_SRCS} ${Metadata_Files})
target_link_libraries(WindLabSmeltPlugin ${WindLabSmeltPlugin_LIBS} nlohmann_json::nlohmann_json)
set_target_properties(WindLabSmeltPlugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(WindLabSmeltPlugin WindLabSmeltPlugin /Plugins/WindLabWorkbench/WindLabSmeltPlugin)

rps_copy_sources(WindLabSmeltPlugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/WindLabSmeltPlugin" ${Metadata_Files})
INSTALL(TARGETS WindLabSmeltPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindLabSmeltPlugin")
INSTALL(FILES WindLabSmeltPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindLabSmeltPlugin")

