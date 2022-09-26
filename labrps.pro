#######################################################
#              LabRPS main project file            #
# run "qmake LabRPS.pro" to generate the Makefile  #
#######################################################

TEMPLATE = subdirs

SUBDIRS += pluginapi/windlabapi\
           pluginapi/seismiclabapi\
           pluginapi/sealabapi\
           pluginapi/userdefinedphenomenonapi\
           app\
           plugins/windLab\
           plugins/seismicLab\ 
           plugins/seaLab\   

CONFIG += ordered
