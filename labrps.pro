#######################################################
#              LabRPS main project file            #
# run "qmake LabRPS.pro" to generate the Makefile  #
#######################################################

TEMPLATE = subdirs

SUBDIRS += pluginapi/windlabapi\
                      pluginapi/seismiclabapi\
                      pluginapi/sealabapi\
                      app\
                      plugins/seaLab\  

CONFIG += ordered
