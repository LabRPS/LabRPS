add_subdirectory(App)

set(WindLabTools_Scripts
Init.py
TestWindLabToolsApp.py
)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND WindLabTools_Scripts InitGui.py TestWindLabToolsGui.py)
endif(BUILD_GUI)

add_custom_target(WindLabToolsScripts ALL
    SOURCES ${WindLabTools_Scripts}
)
set_target_properties(WindLabToolsScripts PROPERTIES FOLDER "Workbenches/WindLabTools")

rps_target_copy_resource_flat(WindLabToolsScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/WindLabTools
    ${WindLabTools_Scripts}
)

INSTALL(
    FILES
        ${WindLabTools_Scripts}
    DESTINATION
        Mod/WindLabTools
)