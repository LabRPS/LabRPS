
SET(PreferencePackTemplates_Files
    Console_Colors.cfg
    Editor_Colors.cfg
    Editor_Font.cfg
    Main_window_layout.cfg
    Start_Colors.cfg
    Window_Colors.cfg
)

ADD_CUSTOM_TARGET(PreferencePackTemplates_data ALL
    SOURCES ${PreferencePackTemplates_Files}
)
set_target_properties(PreferencePackTemplates_data PROPERTIES FOLDER "Gui")

rps_copy_sources(PreferencePackTemplates_data "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Gui/PreferencePackTemplates"
                                  ${PreferencePackTemplates_Files})

INSTALL(
    FILES
        ${PreferencePackTemplates_Files}
    DESTINATION
        ${CMAKE_INSTALL_DATADIR}/Gui/PreferencePackTemplates
)
