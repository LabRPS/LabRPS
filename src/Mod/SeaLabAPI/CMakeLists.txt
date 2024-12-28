add_subdirectory(App)

set(SeaLabAPI_Scripts
Init.py
SeaLabAPIScripts.py
TestSeaLabAPIApp.py
)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND SeaLabAPI_Scripts InitGui.py TestSeaLabAPIGui.py
    )
endif(BUILD_GUI)

add_custom_target(SeaLabAPIScripts ALL
    SOURCES ${SeaLabAPI_Scripts}
)
set_target_properties(SeaLabAPIScripts PROPERTIES FOLDER "Workbenches/SeaLabAPI")

rps_target_copy_resource_flat(SeaLabAPIScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeaLabAPI
    ${SeaLabAPI_Scripts}
)

INSTALL(
    FILES
        ${SeaLabAPI_Scripts}
    DESTINATION
        Mod/SeaLabAPI
)