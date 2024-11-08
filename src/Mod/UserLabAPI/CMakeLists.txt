add_subdirectory(App)

set(UserLabAPI_Scripts
Init.py
UserLabAPIScripts.py
)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND UserLabAPI_Scripts InitGui.py)
endif(BUILD_GUI)

add_custom_target(UserLabAPIScripts ALL
    SOURCES ${UserLabAPI_Scripts}
)
set_target_properties(UserLabAPIScripts PROPERTIES FOLDER "Workbenches/UserLabAPI")

rps_target_copy_resource_flat(UserLabAPIScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/UserLabAPI
    ${UserLabAPI_Scripts}
)

INSTALL(
    FILES
        ${UserLabAPI_Scripts}
    DESTINATION
        Mod/UserLabAPI
)