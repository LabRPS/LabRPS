### Your Random Phenomenon Simulation Tool

[Website](https://www.labrps.com) • 
[Documentation](https://wiki.labrps.com) •
[Forum](https://labrps.com/boards) •
[Bug tracker](https://www.labrps.com/tracker/) •
[Git repository](https://github.com/LabRPS/LabRPS)


[![Release](https://img.shields.io/github/release/labrps/labrps.svg)](https://github.com/labrps/labrps/releases/latest) 
[![Liberapay](https://img.shields.io/liberapay/receives/LabRPS.svg?logo=liberapay)](https://liberapay.com/LabRPS)

![LabRPS with SeaLab actived](https://github.com/LabRPS/Images/blob/main/LabRPS_Screenshot_1.png?raw=true)

![LabRPS Scripting](https://github.com/LabRPS/Images/blob/main/LabRPS_Scripting_Wind_Simuation_Example.png?raw=true)

Overview
--------

* **Purposes**  LabRPS is designed to fit a wide range of uses around sciences and engineerings, such as random vibration in mechanical engineering, buffeting analysis in bridge engineering, study of passengers confort on ship, etc.... LabRPS is mainly to assist reseachers in related fields to quickly implement new simulation methods programmatically in their new research work based on the existing works, help engineers and researchers to numerically generate random phenomena in a more realistic way, helps students and new comers to this field to learn quickly. 

* **Modular System** LabRPS is highly modular. It is designed to allow the usage of modules, each serving a specific function or purpose. These modules can be developed, updated, and maintained independently, allowing for greater flexibility, scalability, and ease of integration. This architecture facilitates reusability, as modules can be used in various configurations to meet changing requirements and enhance collaboration among engineers, researchers, students and others.

* **Visualization** It is integrated with a data visualization tool for graphical representation of data allowing powerful mathematical treatment and visualization of the simulation data while keeping a user-friendly graphical user interface. Its data visualizer which can generate different types of publication quality 2D and 3D plots (such as line, scatter, bar, pie, and surface plots) from data that is either resulted from a simulation, imported from ASCII files, entered by hand, or calculated using formulas. The data is held in spreadsheets, which are referred to as tables with column-based data (typically X and Y values for 2D plots) or matrices (for 3D plots). 

* **Cross platform** LabRPS runs on Windows, macOS and Linux operating systems.

* **Underlying technology**
    * **Python** LabRPS offers a broad Python API.
    * **Qt** Graphical user interface built with Qt.

Installing
----------

Precompiled packages for stable releases are available for Windows, macOS and Linux on the
[Releases page](https://github.com/LabRPS/LabRPS/releases).

Compiling
---------

Compiling LabRPS requires installation of several libraries and their 
development files such as Python and Qt, listed in the 
pages below. Once this is done, LabRPS can be compiled with 
CMake. On Windows, these libraries are bundled and offered 
in a convenient package. On Linux, they are usually found 
in your distribution's repositories, and on macOS and other platforms, 
you will usually have to compile them yourself.

The pages below contain up-to-date build instructions:

- [Linux](https://wiki.labrps.com/Compile_on_Linux)
- [Windows](https://wiki.labrps.com/Compile_on_Windows)
- [macOS](https://wiki.labrps.com/Compile_on_MacOS)
- [Cygwin](https://wiki.labrps.com/Compile_on_Cygwin)
- [MinGW](https://wiki.labrps.com/Compile_on_MinGW)


Reporting Issues
---------

To report an issue please:
- First post to forum to verify the issue; 
- Link forum thread to bug tracker ticket and vice-a-versa; 
- Use the most updated stable or development versions of LabRPS; 
- Post version info from eg. `Help > About LabRPS > Copy to clipboard`; 
- Post a Step-By-Step explanation on how to recreate the issue; 
- Upload an example file to demonstrate problem. 

For more detail see:
- [Wiki Page about the Bug Tracker](https://wiki.labrps.com/Tracker)


Usage & Getting help
--------------------

The LabRPS wiki contains documentation on 
general LabRPS usage, Python scripting, and development. These 
pages might help you get started:

- [Getting started](https://wiki.labrps.com/Getting_started)
- [Features list](https://wiki.labrps.com/Feature_list)
- [Frequent questions](https://wiki.labrps.com/FAQ/en)
- [Workbenches](https://wiki.labrps.com/Workbenches)
- [Scripting](https://wiki.labrps.com/Power_users_hub)
- [Development](https://wiki.labrps.com/Developer_hub)

The [LabRPS forum](https://labrps.com/boards) is also a great place
to find help and solve specific problems you might encounter when
learning to use LabRPS.

Acknowledgments
---------------

Important part of this project is based on or adapted from the following source code:

- **[FreeCAD](https://github.com/FreeCAD/FreeCAD)**  
  Original work by [Jürgen Riegel and others].  
  Licensed under the [LGPL](http://en.wikipedia.org/wiki/LGPL).

We would like to express our sincere gratitude to the original authors for providing such a helpful and well-constructed codebase. Modifications have been made to adapt it to our needs, but some core principles and ideas are drawn from the original work.