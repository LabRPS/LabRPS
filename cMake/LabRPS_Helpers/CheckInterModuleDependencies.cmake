macro(CheckInterModuleDependencies)
    # ==============================================================================
    #inter-module dependencies

    # Takes a dependent module followed by a variable-length list of prerequisite
    # modules.  Warns if any of the prerequisite modules are disabled.
    function(REQUIRES_MODS dependent)
        if(${dependent})
            foreach(prerequisite IN LISTS ARGN)
                if(NOT ${prerequisite})
                    message(STATUS "${dependent} requires ${prerequisite} to be ON, but it"
                                   " is \"${${prerequisite}}\"")
                    set(${dependent} OFF PARENT_SCOPE)
                    break()
                endif(NOT ${prerequisite})
            endforeach()
        endif(${dependent})
    endfunction(REQUIRES_MODS)

    REQUIRES_MODS(BUILD_START              BUILD_WEB)
endmacro(CheckInterModuleDependencies)
