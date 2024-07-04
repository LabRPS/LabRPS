
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(WindLab_Scripts
    Init.py
    WindLabObjects.py
    TestWindLabApp.py
    WindLabUtils.py
)

SET(WindLabCommands_SRCS
    windlabcommands/__init__.py
    windlabcommands/commands.py
    windlabcommands/manager.py
)

SET(WindLabExamples_SRCS
    windlabexamples/__init__.py
    windlabexamples/examplesgui.py
    windlabexamples/manager.py
    windlabexamples/Deodatis1998_LocationDistribution.py
    windlabexamples/Deodatis1998_MeanWind.py
    windlabexamples/Deodatis1998_CoherenceFunction.py
    windlabexamples/Deodatis1998_FrequencyDistribution.py
    windlabexamples/Deodatis1998_SpectrumModel.py
    windlabexamples/Deodatis1998_SpectrumDecomposition.py
    windlabexamples/Deodatis1998_SimulationMethod.py
    windlabexamples/Deodatis1998_UniformRandomPhases.py
    windlabexamples/RPS_WavePassageEffect.py
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
    SOURCES ${WindLab_Scripts} ${WindLab_TestScripts} ${WindLabCommands_SRCS} ${WindLabExamples_SRCS}
)
set_target_properties(WindLabScripts PROPERTIES FOLDER "Workbenches/WindLab")

rps_target_copy_resource(WindLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/WindLab
    ${WindLab_Scripts}
    ${WindLab_TestScripts}
    ${WindLabCommands_SRCS}
    ${WindLabExamples_SRCS}  
)

INSTALL(FILES ${WindLab_Scripts} DESTINATION Mod/WindLab)
INSTALL(FILES ${WindLabCommands_SRCS} DESTINATION Mod/WindLab/windlabcommands)
INSTALL(FILES ${WindLabExamples_SRCS} DESTINATION Mod/WindLab/windlabexamples)
INSTALL(FILES ${WindLab_TestScripts} DESTINATION Mod/WindLab/WindLabTests)
