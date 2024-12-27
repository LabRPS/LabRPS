
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(SeismicLab_Scripts
    Init.py
    SeismicLabObjects.py
    TestSeismicLabApp.py
)

set(SeismicLab_TestScripts
    SeismicLabTests/__init__.py
    SeismicLabTests/TestSeismicLab.py
)

if(BUILD_GUI)
    list (APPEND SeismicLab_Scripts
          InitGui.py
          TestSeismicLabGui.py
    )
endif(BUILD_GUI)

add_custom_target(SeismicLabScripts ALL
    SOURCES ${SeismicLab_Scripts} ${SeismicLab_TestScripts}
)
set_target_properties(SeismicLabScripts PROPERTIES FOLDER "Workbenches/SeismicLab")

rps_target_copy_resource(SeismicLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeismicLab
    ${SeismicLab_Scripts}
    ${SeismicLab_TestScripts}
)

INSTALL(FILES ${SeismicLab_Scripts} DESTINATION Mod/SeismicLab)
INSTALL(FILES ${SeismicLab_TestScripts} DESTINATION Mod/SeismicLab/SeismicLabTests)
