
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(WindLab_Scripts
    Init.py
    WindLabObjects.py
    TestWindLabApp.py
)

set(WindLab_TestScripts
    WindLabTests/__init__.py
    WindLabTests/TestWindLab.py
)

if(BUILD_GUI)
    list (APPEND WindLab_Scripts
          InitGui.py
          TestWindLabGui.py
    )
endif(BUILD_GUI)

add_custom_target(WindLabScripts ALL
    SOURCES ${WindLab_Scripts} ${WindLab_TestScripts}
)
set_target_properties(WindLabScripts PROPERTIES FOLDER "Workbenches/WindLab")

rps_target_copy_resource(WindLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/WindLab
    ${WindLab_Scripts}
    ${WindLab_TestScripts} 
)

INSTALL(FILES ${WindLab_Scripts} DESTINATION Mod/WindLab)
INSTALL(FILES ${WindLab_TestScripts} DESTINATION Mod/WindLab/WindLabTests)
