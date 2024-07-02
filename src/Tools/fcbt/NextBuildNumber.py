# LabRPS MakeNewBuildNbr script
# (c) 2002 Juergen Riegel
#
# Increase the Build Number in Version.h

#***************************************************************************
#*   (c) Juergen Riegel (juergen.riegel@web.de) 2002                       *
#*                                                                         *
#*   This file is part of the LabRPS CAx development system.              *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   LabRPS is distributed in the hope that it will be useful,            *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Lesser General Public License for more details.                   *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with LabRPS; if not, write to the Free Software        *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#*   Juergen Riegel 2002                                                   *
#***************************************************************************/

import time

# reading the last Version information
[RPSVersionMajor,RPSVersionMinor,FCVersionBuild,FCVersionDisDa] = open("../Version.h",'r').readlines()

# increasing build number
BuildNumber = int(FCVersionBuild[23:-1]) +1

print("New Buildnumber is:")
print(BuildNumber)
print("\n")

# writing new Version.h File
open("../Version.h",'w').writelines([RPSVersionMajor,
                                     RPSVersionMinor,
                                     FCVersionBuild[:23]+str(BuildNumber)+'\n',
                                     FCVersionDisDa[:23]+ '"'+time.asctime()+'" \n\n'])

# writing the ChangeLog.txt
open("../ChangeLog.txt",'a').write("\nVersion: V"+RPSVersionMajor[23:-1]+"."+RPSVersionMinor[23:-1]+"B"+
                                   str(BuildNumber)+" Date: "+time.asctime()+' +++++++++++++++++++++++++++++++\n')

# writing new Version.wxi File
open("../Version.wxi",'w').writelines(["<Include>\n",
                                     "   <?define RPSVersionMajor ="+RPSVersionMajor[23:-1] + " ?>\n",
                                     "   <?define RPSVersionMinor ="+RPSVersionMinor[23:-1] + " ?>\n",
                                     "   <?define FCVersionBuild ="+ str(BuildNumber)     + " ?>\n",
                                     "</Include> \n"])

