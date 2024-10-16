add_subdirectory(App)

set(UserDefinedPhenomenonLabAPI_Scripts
Init.py
UserDefinedPhenomenonLabAPIScripts.py
)

if(BUILD_GUI)
    add_subdirectory(Gui)
    list (APPEND UserDefinedPhenomenonLabAPI_Scripts InitGui.py)
endif(BUILD_GUI)

add_custom_target(UserDefinedPhenomenonLabAPIScripts ALL
    SOURCES ${UserDefinedPhenomenonLabAPI_Scripts}
)
set_target_properties(UserDefinedPhenomenonLabAPIScripts PROPERTIES FOLDER "Workbenches/UserDefinedPhenomenonLabAPI")

rps_target_copy_resource_flat(UserDefinedPhenomenonLabAPIScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/UserDefinedPhenomenonLabAPI
    ${UserDefinedPhenomenonLabAPI_Scripts}
)

INSTALL(
    FILES
        ${UserDefinedPhenomenonLabAPI_Scripts}
    DESTINATION
        Mod/UserDefinedPhenomenonLabAPI
)