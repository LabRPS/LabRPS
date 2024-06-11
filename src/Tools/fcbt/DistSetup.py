
from . import DistTools,FileTools

DistName = DistTools.BuildDistName()

DistInst  = DistName + "_installer.msi"
DistDir  = "../../DistTemp/"

#====================================================================
# copy intaller file

FileTools.cpfile("../../Install/LabRPS.msi",DistDir+DistInst)

