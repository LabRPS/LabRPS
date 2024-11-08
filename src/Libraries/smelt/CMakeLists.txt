# # If you only include this third party in PRIVATE source files, you do not need to install it
# # when your main project gets installed.
# set(JSON_Install OFF CACHE INTERNAL "")

# # add_subdirectory(nlohmann_json)
# # add_subdirectory(kissfft)

# if(MSVC)
#     add_definitions(-DHAVE_ACOSH -DHAVE_ATANH -DHAVE_ASINH)
# else(MSVC)
#     add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
# endif(MSVC)

# # Adding MATH defines for M_PI when building on Windows
# if (WIN32)
#   add_compile_definitions(_USE_MATH_DEFINES)
# endif()

# include_directories(
#     ${CMAKE_BINARY_DIR}
#     ${CMAKE_SOURCE_DIR}/src
#     ${CMAKE_BINARY_DIR}/src
#     ${CMAKE_CURRENT_BINARY_DIR}
#     ${Boost_INCLUDE_DIRS}
#     ${EIGEN3_INCLUDE_DIR}
# )

# set(Smelt_LIBS
#     LabRPSGui
#     WindLabAPI
#     GeneralTools
#     WindLabTools
#     kissfft
# )


# SET(Smelt_SRCS
# src/numeric_utils.cc
# src/normal_multivar.cc
# src/normal_dist.cc
# src/lognormal_dist.cc
# src/beta_dist.cc
# src/inv_gauss_dist.cc
# src/students_t_dist.cc
# src/json_object.cc
# src/vlachos_et_al.cc
# src/configure.cc
# src/wittig_sinha.cc
# src/filter.cc
# src/wind_profile.cc
# src/uniform_dist.cc
# src/dabaghi_der_kiureghian.cc
# src/nelder_mead.cc

# include/beta_dist.h
# include/configure.h
# include/dabaghi_der_kiureghian.h 
# include/distribution.h 
# include/factory.h 
# include/filter.h 
# include/function_dispatcher.h 
# include/inv_gauss_dist.h 
# include/json_object.h 
# include/json_object.tcc 
# include/lognormal_dist.h 
# include/nelder_mead.h 
# include/normal_dist.h 
# include/normal_multivar.h 
# include/numeric_utils.h 
# include/stochastic_model.h 
# include/students_t_dist.h 
# include/uniform_dist.h 
# include/vlachos_et_al.h 
# include/wind_profile.h 
# include/window.h 
# include/wittig_sinha.h
# )

# add_library(smelt SHARED ${Smelt_SRCS})
# target_link_libraries(smelt ${Smelt_LIBS} nlohmann_json::nlohmann_json)
# set_target_properties(smelt PROPERTIES FOLDER "Libraries")

# SET_BIN_DIR(smelt smelt)

# if(WIN32)
#     INSTALL(TARGETS smelt
#         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     )
# else(WIN32)
#     INSTALL(TARGETS smelt
#         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     )
# endif(WIN32)



































# Provide option for building testing
option(BUILD_STATIC_LIBS "Build the static library" ON)
option(BUILD_SHARED_LIBS "Build the shared library" OFF)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

set(Smelt_LIBS
    kissfft
)


# Set sources
set(SOURCES
src/numeric_utils.cc
src/normal_multivar.cc
src/normal_dist.cc
src/lognormal_dist.cc
src/beta_dist.cc
src/inv_gauss_dist.cc
src/students_t_dist.cc
src/json_object.cc
src/vlachos_et_al.cc
src/configure.cc
src/wittig_sinha.cc
src/filter.cc
src/wind_profile.cc
src/uniform_dist.cc
src/dabaghi_der_kiureghian.cc
src/nelder_mead.cc

include/beta_dist.h
include/configure.h
include/dabaghi_der_kiureghian.h 
include/distribution.h 
include/factory.h 
include/filter.h 
include/function_dispatcher.h 
include/inv_gauss_dist.h 
include/json_object.h 
include/json_object.tcc 
include/lognormal_dist.h 
include/nelder_mead.h 
include/normal_dist.h 
include/normal_multivar.h 
include/numeric_utils.h 
include/stochastic_model.h 
include/students_t_dist.h 
include/uniform_dist.h 
include/vlachos_et_al.h 
include/wind_profile.h 
include/window.h 
include/wittig_sinha.h
  )

# Add library as target and add libraries to link target to
if (BUILD_STATIC_LIBS)
  add_library(smelt_static STATIC ${SOURCES})
  set_target_properties(smelt_static PROPERTIES OUTPUT_NAME smelt) 
  target_link_libraries(smelt_static ${Smelt_LIBS} nlohmann_json::nlohmann_json)
  set_target_properties(smelt_static PROPERTIES FOLDER "Libraries")

endif()

if (BUILD_SHARED_LIBS)
  if (WIN32)  
    add_library(smelt_shared STATIC ${SOURCES})
  else()
    add_library(smelt_shared SHARED ${SOURCES})    
  endif()
  
  set_target_properties(smelt_shared PROPERTIES OUTPUT_NAME smelt)
  target_link_libraries(smelt_shared ${Smelt_LIBS} nlohmann_json::nlohmann_json)
  set_target_properties(smelt_shared PROPERTIES FOLDER "Libraries")

endif()

# Adding MATH defines for M_PI when building on Windows
if (WIN32)
  add_compile_definitions(_USE_MATH_DEFINES)
endif()

