
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(UserLab_Scripts
    Init.py
    UserLabObjects.py
    TestUserLabApp.py
)

set(UserLab_TestScripts
    UserLabTests/__init__.py
    UserLabTests/TestUserLab.py
)

if(BUILD_GUI)
    list (APPEND UserLab_Scripts
          InitGui.py
          TestUserLabGui.py
    )
endif(BUILD_GUI)

add_custom_target(UserLabScripts ALL
    SOURCES ${UserLab_Scripts} ${UserLab_TestScripts}
)
set_target_properties(UserLabScripts PROPERTIES FOLDER "Workbenches/UserLab")

rps_target_copy_resource(UserLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/UserLab
    ${UserLab_Scripts}
    ${UserLab_TestScripts}  
)

INSTALL(FILES ${UserLab_Scripts} DESTINATION Mod/UserLab)
INSTALL(FILES ${UserLab_TestScripts} DESTINATION Mod/UserLab/UserLabTests)
