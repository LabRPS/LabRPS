################################################################################
### Choose between common configurations                                       #
################################################################################

unix:isEmpty(PRESET) {                     # command-line argument to override
  ### Link dynamically against system-wide installed libraries(default).
  if(!macx) {
    PRESET = linux_all_dynamic
    ### Link statically against all.
    #PRESET = linux_static
    ### Link statically as much as possible.except Qt.
    #PRESET = linux_all_static
  } else {
    PRESET = osx_dist
  }
}

!contains(PRESET, linux_all_static) {                 # Linux Desktop integration
  unix:INSTALLS   += desktop_entry mime_package mime_link icons
}

unix {                                                       # Linux / MacOS X
  contains(PRESET, linux_all_static) {
    ### When installing into a self-contained directory structure use relative
    ### paths at runtime in order to support relocation.
    isEmpty(INSTALLBASE): INSTALLBASE = .
    target.path           = "$$INSTALLBASE"
    documentation.path    = "$$INSTALLBASE/doc"
    manual.path           = "$$INSTALLBASE/manual"
    translationfiles.path = "$$INSTALLBASE/translations"
    plugins.path          = "$$INSTALLBASE/plugins"
  } else {
    ### this is what is called "prefix" when using GNU autotools
    isEmpty(INSTALLBASE): INSTALLBASE = /usr
    target.path           = "$$INSTALLBASE/bin"
    documentation.path    = "$$INSTALLBASE/share/doc/labrps"
    manual.path = "$$INSTALLBASE/share/doc/labrps/manual"
    translationfiles.path = "$$INSTALLBASE/share/labrps/translations"
    plugins.path      = "$$INSTALLBASE/lib/labrps/plugins"
  }
}                                                            # Linux / MacOS X

win32 {                                                      # Windows
  isEmpty(INSTALLBASE): INSTALLBASE = .
  target.path            = "$$INSTALLBASE"
  documentation.path     = "$$INSTALLBASE"
  translationfiles.path  = "$$INSTALLBASE/translations"
  plugins.path           = "$$INSTALLBASE/plugins"
}

### 64bit Linux only suffix
#linux-g++-64: libsuff  = 64
#unix:LIBS             += -L/usr/lib$${libsuff}

################################################################################
### Optional features                                                          #
################################################################################

### a console displaying output of scripts.
DEFINES         += SCRIPTING_CONSOLE
DEFINES         += SCRIPTING_MUPARSER
### a dialog for selecting the scripting language.
DEFINES         += SCRIPTING_DIALOG
DEFINES         += SEARCH_FOR_UPDATES
CONFIG          += console
!contains(PRESET, linux_all_dynamic) {
  DEFINES       += DYNAMIC_PLUGIN_PATH
}

################################################################################
### Dependencies                                                               #
################################################################################

contains(PRESET, linux_all_dynamic) {
  ### dynamically link against installed system-wide
  message(Build configuration: Linux all dynamic)

  INCLUDEPATH   = "$(HOME)/usr/include" $$INCLUDEPATH
  QMAKE_LIBDIR  = "$(HOME)/usr/lib" $$QMAKE_LIBDIR

  LIBS         += -lGLU -lgsl -lgslcblas -libsealabapi -libseismiclabapi -libwindlabapi -libuserdefinedphenomenonapi -librpsTools -libQGLViewer2 -libmatplot.a -libnodesoup.a
}

contains(PRESET, linux_static) {
  ### Link statically and dynamically against rest.
  LIBS         += -lgsl -lgslcblas -lGLU -libsealabapi -libseismiclabapi -libwindlabapi -libuserdefinedphenomenonapi -librpsTools -libQGLViewer2 -libmatplot.a -libnodesoup.a
}

contains(PRESET, linux_all_static) {
  ### mostly static linking, for self-contained binaries
  message(Build configuration: Linux all static)

  LIBS         += /usr/lib/libgsl.a /usr/lib/libgslcblas.a
  LIBS         += /usr/lib/libsealabapi.a /usr/lib/libseismiclabapi.a /usr/lib/libwindlabapi.a /usr/lib/libuserdefinedphenomenonapi.a /usr/lib/librpsTools.a /usr/lib/libQGLViewer2.a /usr/lib/libmatplot.a /usr/lib/libnodesoup.a
}

contains(PRESET, osx_dist) {
  # Uses HomeBrew supplied versions of the dependencies
  message(Build configuration: OSX Distro)

  INCLUDEPATH  += /usr/local/include
  QMAKE_LIBDIR += /usr/local/lib
  LIBS         += -lgsl -lgslcblas -libsealabapi -libseismiclabapi -libwindlabapi -libuserdefinedphenomenonapi -librpsTools -libQGLViewer2 -libmatplot.a -libnodesoup.a
}

win32: {
  !mxe {
    ### Static linking mostly.
    message(Build configuration: Win32)

    isEmpty(LIBPATH): LIBPATH = ../3rdparty
    isEmpty(APILIBPATH): APILIBPATH = ../pluginapi
    isEmpty(TOOLSPATH): TOOLSPATH = ../libraries

    INCLUDEPATH  += "$${LIBPATH}/gsl/include"
    INCLUDEPATH  += "$${APILIBPATH}/sealabapi"
    INCLUDEPATH  += "$${APILIBPATH}/seismiclabapi"
    INCLUDEPATH  += "$${APILIBPATH}/windlabapi"
    INCLUDEPATH  += "$${APILIBPATH}/userdefinedphenomenonapi"

    INCLUDEPATH  += "$${LIBPATH}/Eigen/Core"
    INCLUDEPATH  += "$${TOOLSPATH}/rpsTools"
    INCLUDEPATH  += "$${LIBPATH}/QGLViewer"
    INCLUDEPATH  += "$${LIBPATH}/QGLViewer/VRender"
    INCLUDEPATH  += "$${LIBPATH}/MatPlot/include"

    LIBS         += "$${LIBPATH}/gsl/lib/libgsl.a"
    LIBS         += "$${LIBPATH}/gsl/lib/libgslcblas.a"
    LIBS         += "$${APILIBPATH}/sealabapi/release/libsealabapi.a"
    LIBS         += "$${APILIBPATH}/seismiclabapi/release/libseismiclabapi.a"
    LIBS         += "$${APILIBPATH}/windlabapi/release/libwindlabapi.a"
    LIBS         += "$${APILIBPATH}/userdefinedphenomenonapi/release/libuserdefinedphenomenonapi.a"
    LIBS         += "$${TOOLSPATH}/rpsTools/release/librpsTools.a"
    LIBS         += "$${LIBPATH}/QGLViewer/libQGLViewer2.a"
    LIBS         += "$${LIBPATH}/MatPlot/lib/libmatplot.a"
    LIBS         += "$${LIBPATH}/MatPlot/lib/libnodesoup.a"



  }
}

mxe {
  ### Mingw cross compilation environment on Linux.
  message(Build configuration: Mxe all static)

  QMAKE_CXXFLAGS +=-g
  DEFINES        += CONSOLE
  
  LIBS           +=  -mwindows -lgsl -lgslcblas libsealabapi libseismiclabapi libwindlabapi libuserdefinedphenomenonapi librpsTools libQGLViewer2 libmatplot

  # Qt libs specified here to get around a dependency bug in qmake
  LIBS += -lQt5OpenGL -lQt5Gui -lQt5Widgets -lQt5Network -lQt5Core -lQt5Svg
  LIBS += -lQt5PrintSupport -lQt5Xml -lQt5XmlPatterns -lQt5DataVisualization
  LIBS += -lole32 -loleaut32 -limm32 -lcomdlg32 -luuid 
  LIBS += -lwinspool -lssl -lcrypto -lwinmm -lgdi32 -lws2_32
  LIBS += -ljpeg -lpng -lmng -ltiff -llzma -llcms2
  LIBS += -lopengl32 -lglu32 
}

# include openGL & glu
     win32: LIBS += -lopengl32 -lglu32
else:unix:  LIBS += -lGLU

## add the proper include path for libraries
#     win32:CONFIG(build32bit): LIBS += -L$$PWD/libs_windows_32bit
#else:win32:CONFIG(build64bit): LIBS += -L$$PWD/libs_windows_64bit
#else:unix: CONFIG(build32bit): LIBS += -L$$PWD/libs_unix_32bit
#else:unix: CONFIG(build64bit): LIBS += -L$$PWD/libs_unix_64bit

## includes QGLViewer
#INCLUDEPATH += QGLViewer_headers
#     win32:CONFIG(release, debug|release): LIBS += -lQGLViewer2
#else:win32:CONFIG(debug,   debug|release): LIBS += -lQGLViewerd2
#else:unix: LIBS += -lQGLViewer
