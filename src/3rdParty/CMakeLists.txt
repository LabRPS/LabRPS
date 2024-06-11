# Build SalomeMesh for all Platforms since heavily patched
if (BUILD_SMESH AND NOT LABRPS_USE_EXTERNAL_SMESH)
    add_subdirectory(salomesmesh)
endif()

add_subdirectory(lazy_loader)
add_subdirectory(libE57Format)