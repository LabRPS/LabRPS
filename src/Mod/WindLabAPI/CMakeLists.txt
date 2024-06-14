add_subdirectory(App)

set(WindLabAPI_Scripts
Init.py
WindLabAPIScripts.py
)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND WindLabAPI_Scripts InitGui.py)
endif(BUILD_GUI)

add_custom_target(WindLabAPIScripts ALL
    SOURCES ${WindLabAPI_Scripts}
)
set_target_properties(WindLabAPIScripts PROPERTIES FOLDER "Workbenches/WindLabAPI")

rps_target_copy_resource_flat(WindLabAPIScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/WindLabAPI
    ${WindLabAPI_Scripts}
)

INSTALL(
    FILES
        ${WindLabAPI_Scripts}
    DESTINATION
        Mod/WindLabAPI
)