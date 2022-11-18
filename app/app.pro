# Aspect framework legacy code
DEFINES += LEGACY_CODE_0_2_x
# Enable OpenGL for QCustomPlot
DEFINES += QCUSTOMPLOT_USE_OPENGL
DEFINES += RPS_BUILDING_CORE

# Qt modules
QT += core gui widgets opengl network svg xml
QT += script scripttools printsupport datavisualization

# enable C++11 support
CONFIG += c++17
CONFIG += qt warn_on exceptions opengl thread


INCLUDEPATH += labrps app/src ../data/translations

include(muparser.pri)
include(sourcefiles.pri)
include(../config.pri)

# detect application build mode(not proper)
contains(QMAKE_HOST.arch, x86_64):{
DEFINES += Q_BUILD_64
}
contains(QMAKE_HOST.arch, i386):{
DEFINES += Q_BUILD_32
}

#############################################################################
###################### BASIC PROJECT PROPERTIES #############################
#############################################################################

TARGET         = labrps
TEMPLATE       = app

DEFINES       += QT_PLUGIN
DEFINES       += TS_PATH="\\\"$$replace(translationfiles.path," ","\\ ")\\\""
DEFINES       += DOC_PATH="\\\"$$replace(documentation.path," ","\\ ")\\\""

!isEmpty(manual.path) {
  DEFINES     += MANUAL_PATH="\\\"$$replace(manual.path," ","\\ ")\\\""
}

!isEmpty(plugins.path) {
  DEFINES += PLUGIN_PATH=\\\"$$replace(plugins.path," ","\\ ")\\\"
}

!mxe {
  win32:DEFINES += QT_DLL QT_THREAD_SUPPORT
}

MOC_DIR         = ../tmp/labrps
OBJECTS_DIR     = ../tmp/labrps
DESTDIR         = ./

INSTALLS        += target

###################### STYLES ###############################################
RESOURCES      += ../data/styles/style.qrc

###################### ICONS ################################################
RESOURCES      += ../data/icons.qrc
RESOURCES      += ../data/xmlschema.qrc
RC_FILE         = ../data/labrps.rc
macx:ICON       = ../data/icons/app/labrps.icns

win32 {
  win_icon.files = ../data/icons/app/labrps.ico
  win_icon.path  = "$$INSTALLBASE"
  INSTALLS  += win_icon
}

###################### TRANSLATIONS #########################################
TRANSLATIONS     = ../data/translations/labrps_de.ts \
                   ../data/translations/labrps_es.ts \
                   ../data/translations/labrps_fr.ts \
                   ../data/translations/labrps_ru.ts \
                   ../data/translations/labrps_ja.ts \
                   ../data/translations/labrps_sv.ts \
                   ../data/translations/labrps_pt-br.ts \
                   ../data/translations/labrps_cs.ts \
                   ../data/translations/labrps_cs-alt.ts \

exists(../data/translations/labrps_de.ts) {
  translationfiles.files   = ../data/translations/labrps_de.qm \
                             ../data/translations/labrps_es.qm \
                             ../data/translations/labrps_fr.qm \
                             ../data/translations/labrps_ru.qm \
                             ../data/translations/labrps_ja.qm \
                             ../data/translations/labrps_sv.qm \
                             ../data/translations/labrps_pt-br.qm \
                             ../data/translations/labrps_cs.qm \
                             ../data/translations/labrps_cs-alt.qm \

  unix: tstarget.target  = ../data/translations/labrps_de.qm
  win32: tstarget.target = ..\data\translations\labrps_de.qm

  tstarget.commands = (! test -w ../data/translations/labrps_de.ts || \
  $$LUPDATE_BIN src/*.cpp -ts ../data/translations/*.ts) && \
  $$LRELEASE_BIN ../data/translations/*.ts

  QMAKE_EXTRA_TARGETS     += tstarget
  QMAKE_CLEAN             += $$translationfiles.files

# comment out for now to get rid of LabRPS compile time error
#  PRE_TARGETDEPS          += ../data/translations/labrps_de.qm
}

!exists(../data/translations/labrps_de.ts){
  message("=======================================")
  message("Could not find translation (.ts) files.")
  message("=======================================")
}

INSTALLS        += translationfiles

###################### DOCUMENTATION ########################################
documentation.files += ../data/manual \
                       ../data/INSTALL.md \
                       ../data/labrps.css \
                       ../data/labrps-logo.png \
                       ../data/README.md \
                       ../data/CHANGES \
                       ../data/gpl.txt

INSTALLS        += documentation

unix {
  ###################### DESKTOP INTEGRATION ##################################

  #VARIABLES
  isEmpty(PREFIX) {
    PREFIX = /usr
  }

  desktop_entry.files = ../data/labrps.desktop
  desktop_entry.path  = "$$PREFIX/share/applications"

  mime_package.files  = ../data/labrps.xml
  mime_package.path   = "$$PREFIX/share/mime/packages"

  #deprecated
  mime_link.files     = ../data/x-aproj.desktop
  mime_link.path      = "$$PREFIX/share/mimelnk/application"

  contains(INSTALLS, icons) {
    # scalable icon
    icons.files       = ../data/icons/app/labrps.svg
    icons.path        = "$$PREFIX/share/icons/hicolor/scalable/apps"

    # hicolor icons for different resolutions
    resolutions       = 16 22 32 48 64 96 128
    for(res, resolutions) {
      eval(icon_hicolor_$${res}.files = ../data/icons/app/$${res}/labrps.png)
      eval(icon_hicolor_$${res}.path = "$$PREFIX/share/icons/hicolor/$${res}x$${res}/apps")
      INSTALLS                       += icon_hicolor_$${res}
    }

    # locolor icons for different resolutions
    resolutions        = 16 22 32 48 64 96 128
    for(res, resolutions) {
      eval(icon_locolor_$${res}.files = ../data/icons/app/$${res}/labrps.png)
      eval(icon_locolor_$${res}.path = "$$PREFIX/share/icons/locolor/$${res}x$${res}/apps")
      INSTALLS                       += icon_locolor_$${res}
    }
  }
}
