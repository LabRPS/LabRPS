add_subdirectory(App)

set(SeismicLabAPI_Scripts
Init.py
SeismicLabAPIScripts.py
TestSeismicLabAPIApp.py

)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND SeismicLabAPI_Scripts InitGui.py TestSeismicLabAPIGui.py
    )
endif(BUILD_GUI)

add_custom_target(SeismicLabAPIScripts ALL
    SOURCES ${SeismicLabAPI_Scripts}
)
set_target_properties(SeismicLabAPIScripts PROPERTIES FOLDER "Workbenches/SeismicLabAPI")

rps_target_copy_resource_flat(SeismicLabAPIScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeismicLabAPI
    ${SeismicLabAPI_Scripts}
)

INSTALL(
    FILES
        ${SeismicLabAPI_Scripts}
    DESTINATION
        Mod/SeismicLabAPI
)