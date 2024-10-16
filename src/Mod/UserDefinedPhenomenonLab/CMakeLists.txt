
add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(UserDefinedPhenomenonLab_Scripts
    Init.py
    UserDefinedPhenomenonLabObjects.py
    TestUserDefinedPhenomenonLabApp.py
    UserDefinedPhenomenonLabUtils.py
)

SET(UserDefinedPhenomenonLabCommands_SRCS
    userdefinedphenomenonlabcommands/__init__.py
    userdefinedphenomenonlabcommands/commands.py
    userdefinedphenomenonlabcommands/manager.py
)

SET(UserDefinedPhenomenonLabExamples_SRCS
    userdefinedphenomenonlabexamples/__init__.py
    userdefinedphenomenonlabexamples/examplesgui.py
    userdefinedphenomenonlabexamples/manager.py
    userdefinedphenomenonlabexamples/Deodatis1996_SimulationMethod.py
)


set(UserDefinedPhenomenonLab_TestScripts
    UserDefinedPhenomenonLabTests/__init__.py
    UserDefinedPhenomenonLabTests/TestUserDefinedPhenomenonLab.py
)

if(BUILD_GUI)
    list (APPEND UserDefinedPhenomenonLab_Scripts
          InitGui.py
          TestUserDefinedPhenomenonLabGui.py
    )
endif(BUILD_GUI)

add_custom_target(UserDefinedPhenomenonLabScripts ALL
    SOURCES ${UserDefinedPhenomenonLab_Scripts} ${UserDefinedPhenomenonLab_TestScripts} ${UserDefinedPhenomenonLabCommands_SRCS} ${UserDefinedPhenomenonLabExamples_SRCS}
)
set_target_properties(UserDefinedPhenomenonLabScripts PROPERTIES FOLDER "Workbenches/UserDefinedPhenomenonLab")

rps_target_copy_resource(UserDefinedPhenomenonLabScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/UserDefinedPhenomenonLab
    ${UserDefinedPhenomenonLab_Scripts}
    ${UserDefinedPhenomenonLab_TestScripts}
    ${UserDefinedPhenomenonLabCommands_SRCS}
    ${UserDefinedPhenomenonLabExamples_SRCS}  
)

INSTALL(FILES ${UserDefinedPhenomenonLab_Scripts} DESTINATION Mod/UserDefinedPhenomenonLab)
INSTALL(FILES ${UserDefinedPhenomenonLabCommands_SRCS} DESTINATION Mod/UserDefinedPhenomenonLab/userdefinedphenomenonlabcommands)
INSTALL(FILES ${UserDefinedPhenomenonLabExamples_SRCS} DESTINATION Mod/UserDefinedPhenomenonLab/userdefinedphenomenonlabexamples)
INSTALL(FILES ${UserDefinedPhenomenonLab_TestScripts} DESTINATION Mod/UserDefinedPhenomenonLab/UserDefinedPhenomenonLabTests)
