add_subdirectory(App)

set(GeneralTools_Scripts
Init.py)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND GeneralTools_Scripts InitGui.py)
endif(BUILD_GUI)

add_custom_target(GeneralToolsScripts ALL
    SOURCES ${GeneralTools_Scripts}
)
set_target_properties(GeneralToolsScripts PROPERTIES FOLDER "Workbenches/GeneralTools")

rps_target_copy_resource_flat(GeneralToolsScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/GeneralTools
    ${GeneralTools_Scripts}
)

INSTALL(
    FILES
        ${GeneralTools_Scripts}
    DESTINATION
        Mod/GeneralTools
)