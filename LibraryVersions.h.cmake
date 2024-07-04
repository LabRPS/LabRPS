#ifndef LIBRARY_VERSIONS_H
#define LIBRARY_VERSIONS_H

/* LibraryVersions.h.  Generated from LibraryVersions.h.cmake by cmake.  */

#cmakedefine HAVE_OCC_VERSION

#if defined(HAVE_OCC_VERSION)
#  include <${OCC_INCLUDE_DIR}/Standard_Version.hxx>
#endif


/* No need for Boost (version info is always included in the source) */
/* No need for Python (version info is always included in the source) */
/* No need for Qt (version info is always included in the source) */
/* No need for zlib (version info is always included in the source) */

// No CMake version info for SMESH, libarea, Zipios, or KDL

// Coin3D
constexpr char * RPS_COIN3D_VERSION = "${COIN3D_VERSION}";

// Eigen3
constexpr char * RPS_EIGEN3_VERSION = "${EIGEN3_VERSION}";

// FreeType
constexpr char * RPS_FREETYPE_VERSION = "${FREETYPE_VERSION_STRING}";

// pcl
constexpr char * RPS_PCL_VERSION = "${PCL_VERSION}";

// PyCXX
constexpr char * RPS_PYCXX_VERSION = "${PYCXX_VERSION}";

// PySide
constexpr char * RPS_PYSIDE_VERSION = "${PySide2_VERSION}";

// PyBind
constexpr char * RPS_PYBIND11_VERSION = "${pybind11_VERSION}";

// Shiboken
constexpr char * RPS_SHIBOKEN_VERSION = "${Shiboken2_VERSION}";

// vtk
constexpr char * RPS_VTK_VERSION = "${VTK_VERSION}";

// Xerces-C
constexpr char * RPS_XERCESC_VERSION = "${XercesC_VERSION}";

// Pivy
constexpr char * RPS_PIVY_VERSION = "${PIVY_VERSION}";


#endif // LIBRARY_VERSIONS_H

