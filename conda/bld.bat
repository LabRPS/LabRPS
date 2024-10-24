mkdir build
cd build

if "%FEATURE_DEBUG%"=="1" (
      set BUILD_TYPE="Debug"
      echo "#! building debug package !#") else (
      set BUILD_TYPE="Release")


set "CFLAGS= "
set "CXXFLAGS= "
set "LDFLAGS_SHARED= ucrt.lib"

cmake -G "Ninja" ^
      -D BUID_WITH_CONDA:BOOL=ON ^
      -D CMAKE_BUILD_TYPE=%BUILD_TYPE% ^
      -D LABRPS_LIBPACK_USE:BOOL=OFF ^
      -D CMAKE_INSTALL_PREFIX:FILEPATH=%LIBRARY_PREFIX% ^
      -D CMAKE_PREFIX_PATH:FILEPATH=%LIBRARY_PREFIX% ^
      -D CMAKE_INCLUDE_PATH:FILEPATH=%LIBRARY_PREFIX%/include ^
      -D CMAKE_LIBRARY_PATH:FILEPATH=%LIBRARY_PREFIX%/lib ^
      -D CMAKE_INSTALL_LIBDIR:FILEPATH=%LIBRARY_PREFIX%/lib ^
      -D BUILD_QT5:BOOL=ON ^
      -D NGLIB_INCLUDE_DIR:FILEPATH=%LIBRARY_PREFIX%/include/netgen ^
      -D USE_BOOST_PYTHON:BOOL=OFF ^
      -D LABRPS_USE_PYBIND11:BOOL=ON ^
      -D LABRPS_USE_EXTERNAL_SMESH:BOOL=ON ^
      -D PYTHON_EXECUTABLE:FILEPATH=%PREFIX%/python ^
      -D BUILD_DYNAMIC_LINK_PYTHON:BOOL=ON ^
      -D Boost_NO_BOOST_CMAKE:BOOL=ON ^
      -D LABRPS_USE_PCH:BOOL=OFF ^
      -D INSTALL_TO_SITEPACKAGES:BOOL=ON ^
      ..

if errorlevel 1 exit 1
ninja install
if errorlevel 1 exit 1

rmdir /s /q "%LIBRARY_PREFIX%\doc"
ren %LIBRARY_PREFIX%\bin\LabRPS.exe labrps.exe
ren %LIBRARY_PREFIX%\bin\LabRPSCmd.exe labrpscmd.exe
