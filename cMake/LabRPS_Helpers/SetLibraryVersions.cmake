macro(SetLibraryVersions)
    # version information of libraries
    #
    configure_file(LibraryVersions.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/LibraryVersions.h)

endmacro(SetLibraryVersions)
