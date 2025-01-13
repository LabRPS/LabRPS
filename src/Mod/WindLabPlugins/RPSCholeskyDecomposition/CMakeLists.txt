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

set(RPSCholeskyDecomposition_LIBS
    LabRPSGui
    WindLabAPI
    GeneralTools
    WindLabTools
)

set(RPSCholeskyDecomposition_UIC_SRCS


)

if(BUILD_QT5)
    qt5_wrap_ui(RPSCholeskyDecomposition_UIC_HDRS ${RPSCholeskyDecomposition_UIC_SRCS})
else()
    qt4_wrap_ui(RPSCholeskyDecomposition_UIC_HDRS ${RPSCholeskyDecomposition_UIC_SRCS})
endif()

SET(RPSCholeskyDecomposition_SRCS
    # ${RPSCholeskyDecomposition_UIC_HDRS}
    choleskyDecomposition.cpp
    RPSCholeskyDecomposition.cpp
    choleskyDecomposition.h


)

SET(Metadata_Files
RPSCholeskyDecomposition.txt

)

SET(RPSCholeskyDecompositionIcon_SVG
    # Resources/icons/RPSCholeskyDecompositionWorkbench.svg
)

add_library(RPSCholeskyDecomposition SHARED ${RPSCholeskyDecomposition_SRCS} ${Metadata_Files} ${RPSCholeskyDecompositionIcon_SVG})
target_link_libraries(RPSCholeskyDecomposition ${RPSCholeskyDecomposition_LIBS})
set_target_properties(RPSCholeskyDecomposition PROPERTIES FOLDER "Plugins/WindLab")


SET_BIN_DIR(RPSCholeskyDecomposition RPSCholeskyDecomposition /Plugins/WindLabWorkbench/RPSCholeskyDecomposition)

rps_copy_sources(RPSCholeskyDecomposition "${CMAKE_BINARY_DIR}/Plugins/WindLabWorkbench/RPSCholeskyDecomposition" ${Metadata_Files})
INSTALL(TARGETS RPSCholeskyDecomposition DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/RPSCholeskyDecomposition")
INSTALL(FILES RPSCholeskyDecomposition.txt DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins/WindLabWorkbench/RPSCholeskyDecomposition")
INSTALL(FILES ${RPSCholeskyDecompositionIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Plugins/WindLab/RPSCholeskyDecomposition/Resources/icons")

