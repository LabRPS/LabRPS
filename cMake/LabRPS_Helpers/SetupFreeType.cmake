macro(SetupFreetype)
#--------------------FreeType-----------------------

    if(LABRPS_USE_FREETYPE)
        find_package(Freetype)
        if(NOT FREETYPE_FOUND)
            message("===============================================================\n"
                    "FreeType2 not found. Part module will lack of makeWireString().\n"
                    "===============================================================\n")
        endif(NOT FREETYPE_FOUND)
    endif(LABRPS_USE_FREETYPE)

endmacro(SetupFreetype)
