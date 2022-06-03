
[![License][license-badge]][license-page] 

[license-page]: COPYING
[license-badge]: http://img.shields.io/badge/License-GPL2-blue.svg

LabRPS is a tool for the simulation of random phenomena such as wind velocity, seismic ground motion, sea surface....LabPRS is available for Windows, Linux and Mac OS X (probably BSD also).
This tool is under active development. Everyone is encouraged to give comments in order to improve the tool. Please open an issue to give your comment. 

| Web         | Link                                             |
|:------------|:-------------------------------------------------|
| Website     | https://labrps.com/                |
| Wiki        | https://labrps.com/wiki                |
| Github      | https://github.com/LabRPS/LabRPS    |
| Sourceforge | https://sourceforge.net/projects/labrps/      |
| Test builds | https://labrps.sourceforge.io/test-build.html |

[![Packaging status](https://repology.org/badge/vertical-allrepos/labrps.svg)](https://repology.org/project/labrps/versions)
<a href='https://flathub.org/apps/details/io.github.narunlifescience.LabRPS'><img width='120' alt='Download on Flathub' src='https://flathub.org/assets/badges/flathub-badge-en.png'/></a>

# Donate
LabRPS is an open-source project that has been made possible due to the generous contributions by community backers. If you are interested in supporting this project, please consider becoming a sponsor or becoming a patron https://www.patreon.com/labrps


# Installation
Get the code (if you haven't already):

    git clone https://github.com/LabRPS/LabRPS.git 

Compile and install:

    qmake
    make 
    sudo make install

For Windows/OSX see [installation notes](data/INSTALL.md)

Opening an issue
----------------
### Ask for a new feature

Please:

 * Check if the new feature is not already implemented (Changelog)
 * Check if another person didn't already open an issue
 * If there is already an opened issue, there is no need to comment unless you have more information, it won't help. Instead, you can click on :thumbsup: and subscribe to the issue to be notified of anything new about it 

### Report a bug

Please:
 
 * Try the latest developer build to see if the bug is still present (**Attention**, those builds aren't stable so they might not work well and could sometimes break things like user settings). If it works like a charm even though you see an open issue, please comment on it and explain that the issue has been fixed
 * Check if another person has already opened the same issue to avoid duplicates
 * If there already is an open issue you could comment on it to add precisions about the problem or confirm it
 * In case there isn't, you can open a new issue with an explicit title and as much information as possible (OS, Alpha Plot version, how to reproduce the problem...)
 * Please use http://pastebin.com/ for logs/debug
 
If there are no answers, it doesn't mean we don't care about your feature request/bug. It just means we can't reproduce the bug or haven't had time to implement it :smiley:

## Dependencies

LabRPS may require the following packages ...

| Package       | Link                                         |
|:--------------|:---------------------------------------------|
| Qt            | https://www.qt.io/                           |
| QCustomPlot   | https://www.qcustomplot.com/                 |
| muParser      | http://muparser.beltoforion.de/              |
| GSL           | http://www.gnu.org/software/gsl/             |

Out of this, QCustomPlot and muParser sources(s) are already present in 3rdparty folder and will be statically built to LabRPS. So these packages need not be installed on your system.

Note: LabRPS uses QtDataVisualization module for 3D plotting. You may have to install its equivalent manually if the build fails with the following ERROR: Unknown module(s) in QT: datavisualization. If you are building with a local Qt installation, you may install the module with Qt maintenance tool.

# Credits

## Author

- **LabRPS Team**

## Data Visualization and UI

Most of data visualization and ui codes are from AlphaPlot  project which is a fork of SciDAVis(at the time of the fork, i.e. SciDAVis 1.D009) which also in turn is a fork of QtiPlot(at the time of the fork, i.e. QtiPlot 0.9-rc2). 

The LabRPS manual is based on the AlphaPlot manual.

We thank all the tools and library developers & contributors used by LabRPS(in no particular order):

- Qt (https://www.qt.io/),
- Qt Creator (https://www.qt.io/product/development-tools),
- QCustomPlot (https://www.qcustomplot.com/),
- muParser (https://beltoforion.de/en/muparser/),
- Sublime Text editor (https://www.sublimetext.com/),
- GSL (http://www.gnu.org/software/gsl/),
- Git (https://git-scm.com/),
- Breeze Icons (https://github.com/KDE/breeze-icons),
- Inno Setup (https://jrsoftware.org/isinfo.php),
- Flatpak (https://flatpak.org/)

... and many more we just forgot to mention.
