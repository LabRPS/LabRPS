add_subdirectory(App)

set(SeaLabTools_Scripts
Init.py
TestSeaLabToolsApp.py
)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND SeaLabTools_Scripts InitGui.py TestSeaLabToolsGui.py)
endif(BUILD_GUI)

add_custom_target(SeaLabToolsScripts ALL
    SOURCES ${SeaLabTools_Scripts}
)
set_target_properties(SeaLabToolsScripts PROPERTIES FOLDER "Workbenches/SeaLabTools")

rps_target_copy_resource_flat(SeaLabToolsScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeaLabTools
    ${SeaLabTools_Scripts}
)

INSTALL(
    FILES
        ${SeaLabTools_Scripts}
    DESTINATION
        Mod/SeaLabTools
)