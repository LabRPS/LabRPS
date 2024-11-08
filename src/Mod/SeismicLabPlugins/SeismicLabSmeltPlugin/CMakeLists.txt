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
    ${CMAKE_BINARY_DIR}/src/Libraries/smelt/

)

set(SeismicLabSmeltPlugin_LIBS
    LabRPSGui
    SeismicLabAPI
    GeneralTools
    SeismicLabTools
    smelt
    kissfft
)


SET(SeismicLabSmeltPlugin_SRCS
VlachosEtAl.h
VlachosEtAl.cpp
DabaghiDerKiureghian.h
DabaghiDerKiureghian.cpp
SeismicLabSmeltPlugin.cpp
)

SET(Metadata_Files
SeismicLabSmeltPlugin.txt

)


SET(SeismicLabSmeltPluginIcon_SVG
    # Resources/icons/SeismicLabSmeltPluginWorkbench.svg
)

add_library(SeismicLabSmeltPlugin SHARED ${SeismicLabSmeltPlugin_SRCS} ${Metadata_Files})
target_link_libraries(SeismicLabSmeltPlugin ${SeismicLabSmeltPlugin_LIBS} nlohmann_json::nlohmann_json)
set_target_properties(SeismicLabSmeltPlugin PROPERTIES FOLDER "Plugins/SeismicLab")


SET_BIN_DIR(SeismicLabSmeltPlugin SeismicLabSmeltPlugin /Plugins/SeismicLabWorkbench/SeismicLabSmeltPlugin)

rps_copy_sources(SeismicLabSmeltPlugin "${CMAKE_BINARY_DIR}/Plugins/SeismicLabWorkbench/SeismicLabSmeltPlugin" ${Metadata_Files})
INSTALL(TARGETS SeismicLabSmeltPlugin DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/SeismicLabSmeltPlugin")
INSTALL(FILES SeismicLabSmeltPlugin.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/SeismicLabWorkbench/SeismicLabSmeltPlugin")

