# March 2021, the oldest we have to support : Ununtu 18.04 LTS
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

option(LABRPS_FILE_GROUPED "Arrange files in groups" ON)
if(LABRPS_FILE_GROUPED)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
endif()

# policy CMP0072 was introduced with CMake 3.11
# relates to FindOpenGL module
# and cache variables OPENGL_gl_LIBRARY, OPENGL_glu_LIBRARY
if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE LEGACY)
endif(POLICY CMP0072)

# FindPythonInterp and FindPythonLibs modules are deprecated.
# Currently, they are still used by shiboken's CMake files
if (POLICY CMP0148)
    cmake_policy(SET CMP0148 OLD)
endif()
if (POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

option(LABRPS_USE_CCACHE "Auto detect and use ccache during compilation" ON)

if(LABRPS_USE_CCACHE)
    find_program(CCACHE_PROGRAM ccache)  #This check should occur before project()
    if(CCACHE_PROGRAM)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    endif()
endif()

project(LabRPS)

set(PACKAGE_VERSION_NAME "Vulcan")
set(PACKAGE_VERSION_MAJOR "0")
set(PACKAGE_VERSION_MINOR "1")
set(PACKAGE_VERSION_PATCH "0")
set(PACKAGE_VERSION_SUFFIX "dev") # either "dev" for development snapshot or "" (empty string)
set(LABRPS_VERSION_PATCH "0") # number of patch release (e.g. "4" for the 0.1.4 release)

set(LABRPS_VERSION "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}")
set(PACKAGE_VERSION "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}.${PACKAGE_VERSION_PATCH}")
set(PACKAGE_STRING "${PROJECT_NAME} ${PACKAGE_VERSION}")

# include local modules
include(CheckCXXCompilerFlag)
include(AddFileDependencies)
include(cMake/LabRpsMacros.cmake)
# include helper functions/macros
add_subdirectory(cMake/LabRPS_Helpers)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")

CompilerChecksAndSetups()
ConfigureCMakeVariables()
InitializeLabRPSBuildOptions()
CheckInterModuleDependencies()
LabRPSLibpackChecks()
SetupDoxygen()
if(NOT LABRPS_LIBPACK_USE OR LABRPS_LIBPACK_CHECKFILE_CLBUNDLER)
    SetupPython()
    SetupPCL()
    SetupPybind11()
    SetupXercesC()
    find_package(ZLIB REQUIRED)
    find_package(PyCXX REQUIRED)
    SetupBoost()
    SetupSwig()
    SetupEigen()
    # This file is included directly due to some cMake macros that are defined within.
    # If these macro definitions are embedded within another macro, it causes problems.
    include(cMake/LabRPS_Helpers/SetupQt.cmake)
    SetupFreetype()

    if(BUILD_GUI)
        SetupShibokenAndPyside()
        SetupMatplotlib()
    endif(BUILD_GUI)
endif(NOT LABRPS_LIBPACK_USE OR LABRPS_LIBPACK_CHECKFILE_CLBUNDLER)

SetLibraryVersions()
SetGlobalCompilerAndLinkerSettings()

add_subdirectory(src)
add_subdirectory(data)

BuildAndInstallDesignerPlugin()

CreatePackagingTargets()

PrintFinalReport()
