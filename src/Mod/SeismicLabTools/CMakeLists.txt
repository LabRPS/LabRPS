add_subdirectory(App)

set(SeismicLabTools_Scripts
Init.py)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND SeismicLabTools_Scripts InitGui.py)
endif(BUILD_GUI)

add_custom_target(SeismicLabToolsScripts ALL
    SOURCES ${SeismicLabTools_Scripts}
)
set_target_properties(SeismicLabToolsScripts PROPERTIES FOLDER "Workbenches/SeismicLabTools")

rps_target_copy_resource_flat(SeismicLabToolsScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeismicLabTools
    ${SeismicLabTools_Scripts}
)

INSTALL(
    FILES
        ${SeismicLabTools_Scripts}
    DESTINATION
        Mod/SeismicLabTools
)