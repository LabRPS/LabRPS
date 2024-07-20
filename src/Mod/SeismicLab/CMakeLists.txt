
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(SeismicLab_Scripts
    Init.py
    SeismicLabObjects.py
    TestSeismicLabApp.py
    SeismicLabUtils.py
)

SET(SeismicLabCommands_SRCS
    seismiclabcommands/__init__.py
    seismiclabcommands/commands.py
    seismiclabcommands/manager.py
)

SET(SeismicLabExamples_SRCS
    seismiclabexamples/__init__.py
    seismiclabexamples/examplesgui.py
    seismiclabexamples/manager.py
    seismiclabexamples/Deodatis1998_LocationDistribution.py
    seismiclabexamples/Deodatis1998_FrequencyDistribution.py
    seismiclabexamples/Deodatis1998_UniformRandomPhases.py
    seismiclabexamples/RPS_WavePassageEffect.py
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
    SOURCES ${SeismicLab_Scripts} ${SeismicLab_TestScripts} ${SeismicLabCommands_SRCS} ${SeismicLabExamples_SRCS}
)
set_target_properties(SeismicLabScripts PROPERTIES FOLDER "Workbenches/SeismicLab")

rps_target_copy_resource(SeismicLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/SeismicLab
    ${SeismicLab_Scripts}
    ${SeismicLab_TestScripts}
    ${SeismicLabCommands_SRCS}
    ${SeismicLabExamples_SRCS}  
)

INSTALL(FILES ${SeismicLab_Scripts} DESTINATION Mod/SeismicLab)
INSTALL(FILES ${SeismicLabCommands_SRCS} DESTINATION Mod/SeismicLab/seismiclabcommands)
INSTALL(FILES ${SeismicLabExamples_SRCS} DESTINATION Mod/SeismicLab/seismiclabexamples)
INSTALL(FILES ${SeismicLab_TestScripts} DESTINATION Mod/SeismicLab/SeismicLabTests)
