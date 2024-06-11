
add_subdirectory(App)
if(LABRPS_BUILD_GUI)
    #add_subdirectory(Gui)
endif(LABRPS_BUILD_GUI)

INSTALL(
    FILES
        Init.py
    DESTINATION
        Mod/Measure
)
