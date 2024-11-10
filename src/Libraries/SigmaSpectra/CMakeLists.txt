# add_compile_definitions(DGSL_DLL)

# -------QT stuff----------------------------------------------------------------------
include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)


set(SigmaSpectra_LIBS
LabRPSBase

)

if (BUILD_QT5)
    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
    )

    list(APPEND SigmaSpectra_LIBS
        ${Qt5Core_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
    )

else()
    include_directories(
        ${QT_INCLUDE_DIR}
        ${QT_QTCORE_INCLUDE_DIR}

    )
    list(APPEND SigmaSpectra_LIBS
        ${QT_LIBRARIES}
        ${QT_QTUITOOLS_LIBRARY}
        ${QT_QTXML_INCLUDE_DIR}
    )
    list(APPEND SigmaSpectra_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()


# SET(Gui_UIC_SRCS


# )

# SET(Gui_RES_SRCS
# )

# if (BUILD_QT5)
#     QT5_ADD_RESOURCES(Gui_QRC_SRCS ${Gui_RES_SRCS})
#     QT5_WRAP_UI(Gui_UIC_HDRS ${Gui_UIC_SRCS})
# else()
#     QT4_ADD_RESOURCES(Gui_QRC_SRCS ${Gui_RES_SRCS})
#     QT4_WRAP_UI(Gui_UIC_HDRS ${Gui_UIC_SRCS})
# endif()
# SOURCE_GROUP("Uic" FILES ${Gui_UIC_HDRS})

SET(SigmaSpectra_CPP_SRCS
   Motion.cpp
   AbstractMotion.cpp
   MotionGroup.cpp
   MotionLibrary.cpp
   MotionPair.cpp
   MotionSuite.cpp
)

SET(SigmaSpectra_HPP_SRCS
    Motion.h
    AbstractMotion.h
    MotionGroup.h
    MotionLibrary.h
    MotionPair.h
    MotionSuite.h
)

# SET(SigmaSpectra_Data_DUZCE
#     Data/DUZCE/531-E.AT2
#     Data/DUZCE/531-N.AT2
#     Data/DUZCE/1060-E.AT2
#     Data/DUZCE/1060-N.AT2
# )

# SET(SigmaSpectra_Data_HECTOR
#     Data/HECTOR/HEC000.AT2
#     Data/HECTOR/HEC090.AT2
# )

# SET(SigmaSpectra_Data_KOBE
#     Data/KOBE/NIS000.AT2
#     Data/KOBE/NIS090.AT2
# )

# SET(SigmaSpectra_Data_LOMAP
# Data/LOMAP/G01000.AT2
# Data/LOMAP/G01090.AT2
# Data/LOMAP/G06000.AT2
# Data/LOMAP/G06090.AT2
# Data/LOMAP/GIL067.AT2
# Data/LOMAP/GIL337.AT2
# Data/LOMAP/LOB000.AT2
# Data/LOMAP/LOB090.AT2
# Data/LOMAP/SJTE225.AT2
# Data/LOMAP/SJTE315.AT2
# Data/LOMAP/UC2000.AT2
# Data/LOMAP/UC2090.AT2
# )

# SET(SigmaSpectra_Data_NORTHR
# Data/NORTHR/0141-270.AT2
# Data/NORTHR/0141-360.AT2
# Data/NORTHR/5080-270.AT2
# Data/NORTHR/5080-360.AT2
# Data/NORTHR/CHL070.AT2
# Data/NORTHR/CHL160.AT2
# Data/NORTHR/H12090.AT2
# Data/NORTHR/H12180.AT2
# Data/NORTHR/HOW060.AT2
# Data/NORTHR/HOW330.AT2
# Data/NORTHR/L09000.AT2
# Data/NORTHR/L09090.AT2
# Data/NORTHR/LA0000.AT2
# Data/NORTHR/LA0090.AT2
# Data/NORTHR/VAS000.AT2
# Data/NORTHR/VAS090.AT2
# Data/NORTHR/WON095.AT2
# Data/NORTHR/WON185.AT2
# )

# SET(SigmaSpectra_Data_SFERN
# Data/SFERN/L04111.AT2
# Data/SFERN/L04201.AT2
# Data/SFERN/L09021.AT2
# Data/SFERN/L09291.AT2
# Data/SFERN/L12021.AT2
# Data/SFERN/L12291.AT2
# )

# SET(SigmaSpectra_Data
#     ${SigmaSpectra_Data_DUZCE}
#     ${SigmaSpectra_Data_HECTOR}
#     ${SigmaSpectra_Data_KOBE}
#     ${SigmaSpectra_Data_LOMAP}
#     ${SigmaSpectra_Data_NORTHR}
#     ${SigmaSpectra_Data_SFERN}
# )

SET(SigmaSpectra_SRCS
    ${SigmaSpectra_CPP_SRCS}
    ${SigmaSpectra_HPP_SRCS}
    # ${Gui_QRC_SRCS}
    # ${Gui_UIC_HDRS}

)


add_library(SigmaSpectra SHARED ${SigmaSpectra_SRCS})

target_link_libraries(SigmaSpectra ${SigmaSpectra_LIBS})

set_target_properties(SigmaSpectra PROPERTIES FOLDER "Libraries")

# # save the paths to lib and include in GSL_LIB_PATH and GSL_INCLUDE_PATH repectively
# set(GSL_LIB_PATH "C:/DEV/vcpkg/packages/gsl_x64-windows/lib")
# set(GSL_INCLUDE_PATH "C:/DEV/vcpkg/packages/gsl_x64-windows/include")

# # add the two paths to cmake 
# list(APPEND CMAKE_PREFIX_PATH ${GSL_LIB_PATH})
# list(APPEND CMAKE_PREFIX_PATH ${GSL_INCLUDE_PATH})

# #find the two library lib
# find_library(GSL_LIB gsl)
# find_library(GSLCBLAS_LIB gslcblas)

# # link to the libs
# target_link_libraries(SigmaSpectra ${GSL_LIB} ${GSLCBLAS_LIB})
# set_target_properties(SigmaSpectra PROPERTIES FOLDER "Libraries")

# # find the include files
# find_path (GSL_INCLUDE gsl)

# #  add the include file to the project
# target_include_directories(SigmaSpectra PRIVATE "${GSL_INCLUDE}")


# rps_copy_sources(SigmaSpectra "${CMAKE_BINARY_DIR}/Libraries/SigmaSpectra" ${SigmaSpectra_Data})


SET_BIN_DIR(SigmaSpectra SigmaSpectra)

if(WIN32)
    INSTALL(TARGETS SigmaSpectra
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
else(WIN32)
    INSTALL(TARGETS SigmaSpectra
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif(WIN32)

# INSTALL(
#     FILES
#         ${SigmaSpectra_Data_DUZCE}
#     DESTINATION
#     Libraries/SigmaSpectra/Data/DUZCE
# )

# INSTALL(
#     FILES
#         ${SigmaSpectra_Data_HECTOR}
#     DESTINATION
#     Libraries/SigmaSpectra/Data/HECTOR
# )

# INSTALL(
#     FILES
#         ${SigmaSpectra_Data_KOBE}
#     DESTINATION
#     Libraries/SigmaSpectra/Data/KOBE
# )

# INSTALL(
#     FILES
#         ${SigmaSpectra_Data_LOMAP}
#     DESTINATION
#     Libraries/SigmaSpectra/Data/LOMAP
# )

# INSTALL(
#     FILES
#         ${SigmaSpectra_Data_NORTHR}
#     DESTINATION
#     Libraries/SigmaSpectra/Data/NORTHR
# )

# INSTALL(
#     FILES
#         ${SigmaSpectra_Data_SFERN}
#     DESTINATION
#     Libraries/SigmaSpectra/Data/SFERN
# )

