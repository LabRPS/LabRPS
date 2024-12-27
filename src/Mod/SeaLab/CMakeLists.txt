
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(SeaLab_Scripts
    Init.py
    SeaLabObjects.py
    TestSeaLabApp.py
)

set(SeaLab_TestScripts
    SeaLabTests/__init__.py
    SeaLabTests/TestSeaLab.py
)

if(BUILD_GUI)
    list (APPEND SeaLab_Scripts
          InitGui.py
          TestSeaLabGui.py
    )
endif(BUILD_GUI)

add_custom_target(SeaLabScripts ALL
    SOURCES ${SeaLab_Scripts} ${SeaLab_TestScripts}
)
set_target_properties(SeaLabScripts PROPERTIES FOLDER "Workbenches/SeaLab")

rps_target_copy_resource(SeaLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeaLab
    ${SeaLab_Scripts}
    ${SeaLab_TestScripts} 
)

INSTALL(FILES ${SeaLab_Scripts} DESTINATION Mod/SeaLab)
INSTALL(FILES ${SeaLab_TestScripts} DESTINATION Mod/SeaLab/SeaLabTests)
