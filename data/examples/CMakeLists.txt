
SET(Examples_Files 
    PartExample.RPSStd
)

ADD_CUSTOM_TARGET(Example_data ALL
    SOURCES ${Examples_Files}
)

# 0001097: CMake stops with error "Circular ... <- ... dependency dropped."
if(NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    rps_copy_sources(Example_data "${CMAKE_BINARY_DIR}/data/examples" ${Examples_Files})
endif()

if (WIN32 AND LABRPS_LIBPACK_USE)
    # pivy
    foreach (it ${LABRPS_LIBPACK_PIVY_COIN})
        get_filename_component(libfile ${it} NAME)
        set(out "${CMAKE_BINARY_DIR}/lib/pivy/${libfile}")
        add_custom_command(
            DEPENDS   ${it}
            OUTPUT    ${out}
            COMMAND   ${CMAKE_COMMAND}
            ARGS      -E copy_if_different ${it} ${out}
            MAIN_DEPENDENCY ${it}
            COMMENT   "Copy file to ${out}"
    )
    endforeach (it)
    SOURCE_GROUP("pivy" FILES ${LABRPS_LIBPACK_PIVY_COIN})

    # shiboken
    foreach (it ${LABRPS_LIBPACK_SHIBOKEN})
        get_filename_component(libfile ${it} NAME)
        set(out "${CMAKE_BINARY_DIR}/lib/${libfile}")
        add_custom_command(
            DEPENDS   ${it}
            OUTPUT    ${out}
            COMMAND   ${CMAKE_COMMAND}
            ARGS      -E copy_if_different ${it} ${out}
            MAIN_DEPENDENCY ${it}
            COMMENT   "Copy file to ${out}"
    )
    endforeach (it)
    SOURCE_GROUP("Shiboken" FILES ${LABRPS_LIBPACK_SHIBOKEN})

    # PySide
    foreach (it ${LABRPS_LIBPACK_PYSIDE})
        get_filename_component(libfile ${it} NAME)
        set(out "${CMAKE_BINARY_DIR}/lib/PySide/${libfile}")
        add_custom_command(
            DEPENDS   ${it}
            OUTPUT    ${out}
            COMMAND   ${CMAKE_COMMAND}
            ARGS      -E copy_if_different ${it} ${out}
            MAIN_DEPENDENCY ${it}
            COMMENT   "Copy file to ${out}"
    )
    endforeach (it)
    SOURCE_GROUP("PySide" FILES ${LABRPS_LIBPACK_PYSIDE})

    # PySide tools
    foreach (it ${LABRPS_LIBPACK_PYSIDEUIC})
        get_filename_component(libpath ${it} PATH)
        set(src "${LABRPS_LIBPACK_PYSIDEUIC_REL}/${it}")
        if("${libpath}" STREQUAL "pysideuic")
            set(LABRPS_LIBPACK_PYSIDEUIC_TOP ${LABRPS_LIBPACK_PYSIDEUIC_TOP} ${src})
        elseif("${libpath}" STREQUAL "pysideuic/Compiler")
            set(LABRPS_LIBPACK_PYSIDEUIC_CMP ${LABRPS_LIBPACK_PYSIDEUIC_CMP} ${src})
        elseif("${libpath}" STREQUAL "pysideuic/port_v2")
            set(LABRPS_LIBPACK_PYSIDEUIC_PV2 ${LABRPS_LIBPACK_PYSIDEUIC_PV2} ${src})
        elseif("${libpath}" STREQUAL "pysideuic/port_v3")
            set(LABRPS_LIBPACK_PYSIDEUIC_PV3 ${LABRPS_LIBPACK_PYSIDEUIC_PV3} ${src})
        elseif("${libpath}" STREQUAL "pysideuic/widget-plugins")
            set(LABRPS_LIBPACK_PYSIDEUIC_WPL ${LABRPS_LIBPACK_PYSIDEUIC_WPL} ${src})
        else()
            set(LABRPS_LIBPACK_PYSIDEUIC_OTH ${LABRPS_LIBPACK_PYSIDEUIC_OTH} ${src})
        endif()
        set(LABRPS_LIBPACK_PYSIDEUIC_ABS ${LABRPS_LIBPACK_PYSIDEUIC_ABS} ${src})
        set(out "${CMAKE_BINARY_DIR}/lib/${it}")
        add_custom_command(
            DEPENDS   ${src}
            OUTPUT    ${out}
            COMMAND   ${CMAKE_COMMAND}
            ARGS      -E copy_if_different ${src} ${out}
            MAIN_DEPENDENCY ${src}
            COMMENT   "Copy file to ${out}"
    )
    endforeach (it)
    SOURCE_GROUP("PySide tools" FILES ${LABRPS_LIBPACK_PYSIDEUIC_OTH})
    SOURCE_GROUP("PySide tools\\pysideuic" FILES ${LABRPS_LIBPACK_PYSIDEUIC_TOP})
    SOURCE_GROUP("PySide tools\\pysideuic\\Compiler" FILES ${LABRPS_LIBPACK_PYSIDEUIC_CMP})
    SOURCE_GROUP("PySide tools\\pysideuic\\port_v2" FILES ${LABRPS_LIBPACK_PYSIDEUIC_PV2})
    SOURCE_GROUP("PySide tools\\pysideuic\\port_v3" FILES ${LABRPS_LIBPACK_PYSIDEUIC_PV3})
    SOURCE_GROUP("PySide tools\\pysideuic\\widget-plugins" FILES ${LABRPS_LIBPACK_PYSIDEUIC_WPL})

    # Python extension modules
    foreach (it ${LABRPS_LIBPACK_PYTHON})
        get_filename_component(libfile ${it} NAME)
        set(out "${CMAKE_BINARY_DIR}/lib/${libfile}")
        add_custom_command(
            DEPENDS   ${it}
            OUTPUT    ${out}
            COMMAND   ${CMAKE_COMMAND}
            ARGS      -E copy_if_different ${it} ${out}
            MAIN_DEPENDENCY ${it}
            COMMENT   "Copy file to ${out}"
    )
    endforeach (it)
    SOURCE_GROUP("Python" FILES ${LABRPS_LIBPACK_PYTHON})

    set(LABRPS_LIBPACK_FILES
        ${LABRPS_LIBPACK_PIVY_COIN}
        ${LABRPS_LIBPACK_SHIBOKEN}
        ${LABRPS_LIBPACK_PYSIDE}
        ${LABRPS_LIBPACK_PYSIDEUIC_ABS}
        ${LABRPS_LIBPACK_PYTHON}
    )
    add_custom_target(LibPack_Files ALL SOURCES ${LABRPS_LIBPACK_FILES})

endif(WIN32 AND LABRPS_LIBPACK_USE)

INSTALL(
    FILES
        ${Examples_Files}
    DESTINATION
        ${CMAKE_INSTALL_DATADIR}/examples
)

