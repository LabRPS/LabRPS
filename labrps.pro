#######################################################
#              LabRPS main project file            #
# run "qmake LabRPS.pro" to generate the Makefile  #
#######################################################

TEMPLATE = subdirs

SUBDIRS += libraries/rpsTools\
           pluginapi/windlabapi\
           pluginapi/seismiclabapi\
           pluginapi/sealabapi\
           pluginapi/userdefinedphenomenonapi\
           app\
           plugins/windLab\
           plugins/seismicLab\ 
           plugins/seaLab\
           plugins/myWindVelocity\
           plugins/windSimulationMethodWWYang1997\   
           plugins/windSimulationMethodWWYang1997Ind\   


CONFIG += ordered
