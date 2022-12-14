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
           3rdparty/QGLViewer\
           app\
           plugins/windLab\
           plugins/seismicLab\ 
           plugins/seaLab\
           plugins/myWindVelocity\
           plugins/windSimulationMethodWWYang1997\   
           plugins/windSimulationMethodWWYang1997Ind\   
           plugins/correlationTool\
           plugins/spectrumTool\
           plugins/rpsCholeskyDecomposition\
           plugins/ergodicityCheckToolPlugin\
           plugins/rpsRandomnessProviders\
           plugins/pdfCheckToolPlugin\
           plugins/generalizedSpectrum\
           plugins/resultCheckingToolPlugin\
           plugins/resultCheckingToolPlugin2\


CONFIG += ordered
