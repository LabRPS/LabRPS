macro(LabRPSLibpackChecks)
    # ==============================================================================

    if(LABRPS_LIBPACK_USE)

        # checking for a unique file in LibPack location to make sure the right version of the LibPack is there
        find_file(LABRPS_LIBPACK_CHECKFILE_CLBUNDLER MANIFEST.db ${LABRPS_LIBPACK_DIR})

        # don't show them in the GUI
        set(LABRPS_LIBPACK_CHECKFILE_CLBUNDLER "${LABRPS_LIBPACK_CHECKFILE_CLBUNDLER}" CACHE INTERNAL "Find libpack")

        if (LABRPS_LIBPACK_CHECKFILE_CLBUNDLER)
            set(LABRPS_LIBPACK_VERSION "CLbundler" CACHE STRING "Displays if the libpack has been found" FORCE)
            include(cMake/UseLibPackCLbundler.cmake)
        else(LABRPS_LIBPACK_CHECKFILE_CLBUNDLER)
            set(LABRPS_LIBPACK_VERSION "NOTFOUND" CACHE STRING "Displays if the libpack has been found" FORCE)
            message(SEND_ERROR  "Could not find libpack in specified location:" ${LABRPS_LIBPACK_DIR})
        endif(LABRPS_LIBPACK_CHECKFILE_CLBUNDLER)
# -------------------------------- PyCXX --------------------------------

    find_package(PyCXX REQUIRED)

# -------------------------------- Swig ----------------------------------

    find_package(SWIG)

    if(NOT SWIG_FOUND)
        message("==================================================\n"
                "SWIG not found, don't build SWIG binding for pivy.\n"
                "==================================================\n")
    endif(NOT SWIG_FOUND)

endif(LABRPS_LIBPACK_USE)

endmacro(LabRPSLibpackChecks)
