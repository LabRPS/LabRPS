#add_defintions(-D_RPS_GUI_ENABLED_)
#add_defintions(-DLABRPSMAINPY)

configure_file(labrps.rc.cmake ${CMAKE_CURRENT_BINARY_DIR}/labrps.rc)
configure_file(labrpsCmd.rc.cmake ${CMAKE_CURRENT_BINARY_DIR}/labrpsCmd.rc)
file(COPY icon.ico DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_GUI)
    include_directories(
        ${Boost_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${QT_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
        ${XercesC_INCLUDE_DIRS}
    )
else(BUILD_GUI)
    include_directories(
        ${Boost_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${QT_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
        ${XercesC_INCLUDE_DIRS}
    )
endif(BUILD_GUI)

######################## LabRPSMain ########################
if(BUILD_GUI)

    SET(LabRPS_SRCS
        ${CMAKE_CURRENT_BINARY_DIR}/labrps.rc
        icon.ico
        MainGui.cpp
    )

    SET(LabRPS_LIBS
        LabRPSGui
    )

    if (MSVC AND NOT BUILD_QT5)
        list(APPEND LabRPS_LIBS
            ${QT_QTMAIN_LIBRARY}
        )
    endif()

    if(NOT BUILD_DYNAMIC_LINK_PYTHON)
        # executables have to be linked against python libraries,
        # because extension modules are not.
        list(APPEND LabRPS_LIBS
            ${PYTHON_LIBRARIES}
        )
    endif(NOT BUILD_DYNAMIC_LINK_PYTHON)

    add_executable(LabRPSMain WIN32 ${LabRPS_SRCS})
    target_link_libraries(LabRPSMain ${LabRPS_LIBS})
    set_target_properties(LabRPSMain PROPERTIES FOLDER "LabRPS")

    SET_BIN_DIR(LabRPSMain LabRPS)

    if(WIN32)
        INSTALL(TARGETS LabRPSMain
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    elseif(APPLE AND NOT BUILD_WITH_CONDA)
        INSTALL(TARGETS LabRPSMain
	    RUNTIME DESTINATION MacOS
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    else()
        INSTALL(TARGETS LabRPSMain
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
    endif()
endif(BUILD_GUI)
######################## LabRPSMainCmd ########################

SET(LabRPSMainCmd_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/labrpsCmd.rc
    icon.ico
    MainCmd.cpp
)

add_executable(LabRPSMainCmd ${LabRPSMainCmd_SRCS})

SET(LabRPSMainCmd_LIBS
    LabRPSApp
)

if (BUILD_QT5)
    list(APPEND LabRPSMainCmd_LIBS
        ${Qt5Core_LIBRARIES}
        ${Qt5Xml_LIBRARIES}
    )
else()
    list(APPEND LabRPSMainCmd_LIBS
        ${QT_QTCORE_LIBRARY}
        ${QT_QTXML_LIBRARY}
    )
endif()

if(NOT BUILD_DYNAMIC_LINK_PYTHON)
    # executables have to be linked against python libraries,
    # because extension modules are not.
    list(APPEND LabRPSMainCmd_LIBS
        ${PYTHON_LIBRARIES}
    )
endif(NOT BUILD_DYNAMIC_LINK_PYTHON)

target_link_libraries(LabRPSMainCmd
    ${LabRPSMainCmd_LIBS}
)

set_target_properties(LabRPSMainCmd PROPERTIES FOLDER "LabRPS")

SET_BIN_DIR(LabRPSMainCmd LabRPSCmd)

if(WIN32)
    INSTALL(TARGETS LabRPSMainCmd
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
elseif(APPLE AND NOT BUILD_WITH_CONDA)
    INSTALL(TARGETS LabRPSMainCmd
        RUNTIME DESTINATION MacOS
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
else()
    INSTALL(TARGETS LabRPSMainCmd
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

######################## LabRPSMainPy ########################

SET(LabRPSMainPy_SRCS
    MainPy.cpp
)

add_library(LabRPSMainPy SHARED ${LabRPSMainPy_SRCS})

target_link_libraries(LabRPSMainPy LabRPSApp)
set_target_properties(LabRPSMainPy PROPERTIES FOLDER "LabRPS")


SET_BIN_DIR(LabRPSMainPy LabRPS)
SET_PYTHON_PREFIX_SUFFIX(LabRPSMainPy)

if(WIN32)
    INSTALL(TARGETS LabRPSMainPy
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
else(WIN32)
    INSTALL(TARGETS LabRPSMainPy
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif(WIN32)

######################## LabRPSGuiPy ########################
if(BUILD_GUI)

    SET(LabRPSGuiPy_SRCS
        LabRPSGuiPy.cpp
    )

    add_library(LabRPSGuiPy SHARED ${LabRPSGuiPy_SRCS})

    target_link_libraries(LabRPSGuiPy LabRPSGui)
    set_target_properties(LabRPSGuiPy PROPERTIES FOLDER "LabRPS")


    SET_BIN_DIR(LabRPSGuiPy LabRPSGui)
    SET_PYTHON_PREFIX_SUFFIX(LabRPSGuiPy)
    if(WIN32)
        # Name clash with target "LabRPSGui"
        # Must be called "LabRPSGuiPy_d" and "LabRPSGuiPy" to work so override default
        set_target_properties(LabRPSGuiPy PROPERTIES PDB_NAME_DEBUG "LabRPSGuiPy_d")
        set_target_properties(LabRPSGuiPy PROPERTIES PDB_NAME_RELEASE "LabRPSGuiPy")
    endif(WIN32)

    if(WIN32)
        INSTALL(TARGETS LabRPSGuiPy
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    else(WIN32)
        INSTALL(TARGETS LabRPSGuiPy
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif(WIN32)
endif(BUILD_GUI)
