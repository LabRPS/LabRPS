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

set(WindLabQBladePlugin_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)


SET(WindLabQBladePlugin_SRCS
QbladeMethods.h
QbladeMethods.cpp
WindField.h
WindField.cpp
WindLabQBladePlugin.cpp
Vec3f.h
Vec3f.cpp
Vec3.h
Vec3.cpp
Quaternion.h

)

SET(Metadata_Files
WindLabQBladePlugin.txt

)


SET(WindLabQBladePluginIcon_SVG
    # Resources/icons/WindLabQBladePluginWorkbench.svg
)

add_library(WindLabQBladePlugin SHARED ${WindLabQBladePlugin_SRCS} ${Metadata_Files})
target_link_libraries(WindLabQBladePlugin ${WindLabQBladePlugin_LIBS} nlohmann_json::nlohmann_json)
set_target_properties(WindLabQBladePlugin PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(WindLabQBladePlugin WindLabQBladePlugin /Plugins/WindLabWorkbench/WindLabQBladePlugin)

rps_copy_sources(WindLabQBladePlugin "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/WindLabQBladePlugin" ${Metadata_Files})
INSTALL(TARGETS WindLabQBladePlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindLabQBladePlugin")
INSTALL(FILES WindLabQBladePlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/WindLabQBladePlugin")

