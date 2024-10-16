macro(SetupGSL)
# ------------------------------ GSL ------------------------------

    find_package(GSL)
    if (MATPLOTLIB_FOUND)
        message(STATUS "Found GSL: ${MATPLOTLIB_PATH_DIRS} (found version \"${MATPLOTLIB_VERSION}\")")
    else(MATPLOTLIB_FOUND)
        message("=====================================================\n"
                "GSL not found, Plot module won't be available.\n"
                "=====================================================\n")
    endif(MATPLOTLIB_FOUND)

endmacro(SetupGSL)
