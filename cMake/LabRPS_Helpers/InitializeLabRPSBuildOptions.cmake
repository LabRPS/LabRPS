macro(InitializeLabRPSBuildOptions)
    # ==============================================================================
    # =================   All the options for the build process    =================
    # ==============================================================================

    option(BUILD_FORCE_DIRECTORY "The build directory must be different to the source directory." OFF)
    option(BUILD_GUI "Build LabRPS Gui. Otherwise you have only the command line and the Python import module." ON)
    option(LABRPS_USE_EXTERNAL_ZIPIOS "Use system installed zipios++ instead of the bundled." OFF)
    option(LABRPS_USE_EXTERNAL_SMESH "Use system installed smesh instead of the bundled." OFF)
    option(LABRPS_USE_EXTERNAL_KDL "Use system installed orocos-kdl instead of the bundled." OFF)
    option(LABRPS_USE_FREETYPE "Builds the features using FreeType libs" ON)
    option(LABRPS_BUILD_DEBIAN "Prepare for a build of a Debian package" OFF)
    option(BUILD_WITH_CONDA "Set ON if you build LabRPS with conda" OFF)
    option(BUILD_DYNAMIC_LINK_PYTHON "If OFF extension-modules do not link against python-libraries" ON)
    option(INSTALL_TO_SITEPACKAGES "If ON the labrps root namespace (python) is installed into python's site-packages" OFF)
    option(OCCT_CMAKE_FALLBACK "disable usage of occt-config files" OFF)
    if (WIN32 OR APPLE)
        option(LABRPS_USE_QT_FILEDIALOG "Use Qt's file dialog instead of the native one." OFF)
    else()
        option(LABRPS_USE_QT_FILEDIALOG "Use Qt's file dialog instead of the native one." ON)
    endif()

    # == Win32 is default behaviour use the LibPack copied in Source tree ==========
    if(MSVC)
        option(LABRPS_RELEASE_PDB "Create PDB files for Release version." ON)
        option(LABRPS_RELEASE_SEH "Enable Structured Exception Handling for Release version." ON)
        option(LABRPS_LIBPACK_USE "Use the LibPack to Build LabRPS (only Win32 so far)." ON)
        option(LABRPS_LIBPACK_USEPYSIDE "Use PySide in LibPack rather to PyQt and Swig." ON)
        option(LABRPS_USE_PCH "Activate precompiled headers where it's used." ON)

        if (DEFINED ENV{LABRPS_LIBPACK_DIR})
            set(LABRPS_LIBPACK_DIR $ENV{LABRPS_LIBPACK_DIR} CACHE PATH  "Directory of the LabRPS LibPack")
            message(STATUS "Found libpack env variable: ${LABRPS_LIBPACK_DIR}")
        else()
            set(LABRPS_LIBPACK_DIR ${CMAKE_SOURCE_DIR} CACHE PATH  "Directory of the LabRPS LibPack")
        endif()

        set(LIBPACK_FOUND OFF )
        if (EXISTS ${LABRPS_LIBPACK_DIR}/plugins/imageformats/qsvg.dll)
            set(LIBPACK_FOUND ON )
            set(COPY_LIBPACK_BIN_TO_BUILD OFF )
            # Create install commands for dependencies for INSTALL target in LabRPS solution
            option(LABRPS_INSTALL_DEPEND_DIRS "Create install dependency commands for the INSTALL target found
                in the LabRPS solution." ON)
            # Copy libpack smaller dependency folders to build folder per user request - if non-existent at destination
            if (NOT EXISTS ${CMAKE_BINARY_DIR}/bin/imageformats/qsvg.dll)
                option(LABRPS_COPY_DEPEND_DIRS_TO_BUILD "Copy smaller libpack dependency directories to build directory." OFF)
            endif()
            # Copy libpack 'bin' directory contents to build 'bin' per user request - only IF NOT EXISTS already
            if (NOT EXISTS ${CMAKE_BINARY_DIR}/bin/DLLs)
                set(COPY_LIBPACK_BIN_TO_BUILD ON )
                option(LABRPS_COPY_LIBPACK_BIN_TO_BUILD "Copy larger libpack dependency 'bin' folder to the build directory." OFF)
                # Copy only the minimum number of files to get a working application
                option(LABRPS_COPY_PLUGINS_BIN_TO_BUILD "Copy plugins to the build directory." OFF)
            endif()
        else()
            message("Libpack NOT found.\nIf you intend to use a Windows libpack, set the LABRPS_LIBPACK_DIR to the libpack directory.")
            message(STATUS "Visit: https://github.com/apeltauer/LabRPS/releases/ for Windows libpack downloads.")
        endif()
    else(MSVC)
        option(LABRPS_LIBPACK_USE "Use the LibPack to Build LabRPS (only Win32 so far)." OFF)
        set(LABRPS_LIBPACK_DIR ""  CACHE PATH  "Directory of the LabRPS LibPack")
    endif(MSVC)
    option(BUILD_QT5 "Build with Qt5." ON)

    # https://blog.kitware.com/constraining-values-with-comboboxes-in-cmake-cmake-gui/
    set(LABRPS_USE_OCC_VARIANT "Community Edition"  CACHE STRING  "Official OpenCASCADE version or community edition")
    set_property(CACHE LABRPS_USE_OCC_VARIANT PROPERTY STRINGS
                 "Official Version"
                 "Community Edition"
    )

    if (BUILD_QT5)
      set(LABRPS_USE_QTWEBMODULE "Automatic"  CACHE STRING  "Qt Webkit or Qt WebEngine")
      set_property(CACHE LABRPS_USE_QTWEBMODULE PROPERTY STRINGS
                   "Automatic"
                   "Qt Webkit"
                   "Qt WebEngine"
      )
    endif()
    configure_file(${CMAKE_SOURCE_DIR}/src/QtOpenGL.h.cmake ${CMAKE_BINARY_DIR}/src/QtOpenGL.h)

    option(BUILD_DESIGNER_PLUGIN "Build and install the designer plugin" OFF)

    if(APPLE)
        option(LABRPS_CREATE_MAC_APP "Create app bundle on install" OFF)

        if(LABRPS_CREATE_MAC_APP)
            install(
                DIRECTORY ${CMAKE_SOURCE_DIR}/src/MacAppBundle/LabRPS.app/
                DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app
            )

            # It should be safe to assume we've got sed on OSX...
            install(CODE "
                execute_process(COMMAND
                    sed -i \"\" -e s/VERSION_STRING_FROM_CMAKE/${PACKAGE_VERSION}/
                    -e s/NAME_STRING_FROM_CMAKE/${PROJECT_NAME}/
                    ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app/Contents/Info.plist)
                   ")

            set(CMAKE_INSTALL_PREFIX
                ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app/Contents)
            set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib )
        endif(LABRPS_CREATE_MAC_APP)
        set(CMAKE_MACOSX_RPATH TRUE )
    endif(APPLE)

    option(BUILD_TEMPLATE "Build the LabRPS template module which is only for testing purposes" OFF)
    option(BUILD_ADDONMGR "Build the LabRPS addon manager module" ON)
    option(BUILD_IDF "Build the LabRPS idf module" ON)
    option(BUILD_IMAGE "Build the LabRPS image module" ON)
    option(BUILD_IMPORT "Build the LabRPS import module" ON)
    option(BUILD_PART "Build the LabRPS part module" ON)
    option(BUILD_PLOT "Build the LabRPS plot module" ON)
    option(BUILD_SPREADSHEET "Build the LabRPS spreadsheet module" ON)
    option(BUILD_START "Build the LabRPS start module" ON)
    option(BUILD_TEST "Build the LabRPS test module" ON)
    option(BUILD_WEB "Build the LabRPS web module" ON)
    option(BUILD_HELP "Build the LabRPS help module" ON)

    option(BUILD_WindLab "Build the WindLab module" ON)
    option(BUILD_SeismicLab "Build the Seismic Lab module" ON)
    option(BUILD_SeaLab "Build the SeaLab module" ON)
    option(BUILD_WindLabPlugin "Build the WindLab plugin module" ON)
    option(BUILD_SeismicLabPlugin "Build the Seismic plugin module" ON)
    option(BUILD_SeaLabPlugin "Build the SeaLab plugin module" ON)
    option(BUILD_UserDefinedPhenomenonLab "Build the UserDefinedPhenomenon module" ON)
    option(BUILD_UserDefinedPhenomenonLabPlugin "Build the UserDefinedPhenomenon plugin module" ON)
    
    if(MSVC)
        option(BUILD_FEM_NETGEN "Build the LabRPS FEM module with the NETGEN mesher" ON)
        option(LABRPS_USE_PCL "Build the features that use PCL libs" OFF) # 3/5/2021 current LibPack uses non-C++17 FLANN
        option(LABRPS_USE_3DCONNEXION "Use the 3D connexion SDK to support 3d mouse." ON)
    elseif(APPLE)
        find_library(3DCONNEXIONCLIENT_FRAMEWORK 3DconnexionClient)
        if(IS_DIRECTORY ${3DCONNEXIONCLIENT_FRAMEWORK})
            option(LABRPS_USE_3DCONNEXION "Use the 3D connexion SDK to support 3d mouse." ON)
        else(IS_DIRECTORY ${3DCONNEXIONCLIENT_FRAMEWORK})
            option(LABRPS_USE_3DCONNEXION "Use the 3D connexion SDK to support 3d mouse." OFF)
        endif(IS_DIRECTORY ${3DCONNEXIONCLIENT_FRAMEWORK})
    else(MSVC)
        set(LABRPS_USE_3DCONNEXION OFF )
    endif(MSVC)
    if(NOT MSVC)
        option(LABRPS_USE_PCL "Build the features that use PCL libs" OFF)
    endif(NOT MSVC)

    # if this is set override some options
    if (LABRPS_BUILD_DEBIAN)
        set(LABRPS_USE_EXTERNAL_ZIPIOS ON )
        # A Debian package for SMESH doesn't exist
        #set(LABRPS_USE_EXTERNAL_SMESH ON )
    endif (LABRPS_BUILD_DEBIAN)

    # for Windows the minimum required cmake version is 3.4.3 to build the Path module
    if(WIN32 AND CMAKE_VERSION VERSION_LESS 3.4.3)
        message(WARNING "Disable Path, requires cmake >= 3.4.3 in order to build this module")
        set(BUILD_PATH OFF )
    endif()

    # force build directory to be different to source directory
    if (BUILD_FORCE_DIRECTORY)
        if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
            message(FATAL_ERROR "The build directory (${CMAKE_BINARY_DIR}) must be different to the source directory (${CMAKE_SOURCE_DIR}).\n"
                                "Please choose another build directory! Or disable the option BUILD_FORCE_DIRECTORY.")
        endif()
    endif()
endmacro(InitializeLabRPSBuildOptions)
