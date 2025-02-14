---
title: 'LabRPS: Laboratory of Random Phenomena Simulation'
tags:
  - Random phenomenon
  - simulation
  - probability
  - statistics
  - random wind velocity
  - seismic ground motion
  - random sea surface elevation
  - random walk
authors:
  - name: Koffi Togbenou
    orcid: 0009-0009-5538-229X
    affiliation: 1,2
    corresponding: true
  - name: Gabin Koto N’Gobi
    affiliation: 2
  - name: Chuanjin Yu
    affiliation: 3
  - name: Dossa Didier Boko-haya
    affiliation: 1,2
  - name: Eklou Eric Hiheglo
    affiliation: 4
  - name: Médard Noukpo Agbazo, 
    affiliation: 2
  - name: Guy Hervé Houngue
    affiliation: 2
  - name: Hagninou Elagnon Venance Donnou
    orcid: 0000-0002-2207-0398
    affiliation: 2
  - name: Patrick Arnaud Wandji Zoumb
    orcid: 0000-0002-1449-6604
    affiliation: 5
affiliations:
 - name: China Railway Major Bridge Reconnaissance & Design Institute Co., Ltd., Wuhan 430056, China
   index: 1
 - name: Laboratoire de Physique du Rayonnement (L.P.R), Faculté des Sciences et Techniques (FAST), Université d’Abomey-Calavi, Cotonou, Bénin.
   index: 2
 - name: Department of Bridge Engineering, Southwest Jiaotong University, 610031, Chengdu, Sichuan,  China
   index: 3
 - name: Department of Mechanical Engineering, Systems for Hybrid-Additive Process Engineering Lab, Pennsylvania State University, USA
   index: 4
 - name: School of Civil Engineering, National Advanced School of Public Works, Yaoundé, Cameroon
   index: 5
date: 12 February 2025
bibliography: paper.bib
---

# Summary

LabRPS is an open-source computational tool designed for the numerical simulation of random phenomena. It leverages a modular framework enabling reusable of algorithm components, allowing for efficient simulation of various stochastic processes, including wind velocity, seismic ground motion, sea surface behaviour, road surface roughness, temperature fluctuations, and random material properties, among others.

LabRPS is primarily intended to assist researchers in this field to quickly implement new simulation methods programmatically in their research work based on existing works by providing a flexible platform for implementing and testing new simulation methods and also for accessing existing implementations that have already been stored. It enables engineers and scientists to generate more realistic simulations of random phenomena, enhancing the accuracy, the computation time consumption and the memory usage of their simulation models. Additionally, it serves as a learning tool for students and newcomers to the field, offering a streamlined approach to grasping complex concepts.

The tool is highly modular and seamlessly integrates with an advanced data visualizer, enabling the creation of high-quality 2D and 3D visualizations for simulation results, as well as data imported from files, manually entered, or derived from formulas. These data visualizations are optimized for academic publications, empowering users to effectively communicate their findings with precision and clarity.

![LabRPS Interface\label{fig:figure1}](Figures/Figure1.png)

# 1. Statement of Need

Most of the problems that engineers, and scientists face involve random phenomena or randomness which is the lack of predictability. In many situations, it is desired to numerically represent those random phenomena. For example: (a) numerical correlated stochastic wind velocity is required for the buffeting analysis of flexible long span cable supported bridges, (b) boundary layer turbulence is required for the analysis of panel vibrations of aircraft and submarines, (c) ocean waves need to be numerically represented for the analysis of ship oscillations, (d) randomness in material must be well represented for the analysis of the effect of randomness in geometrical configuration of structural component due to fabrication errors on the vibration and buckling eigenvalues, (e) numerical representation of random surface roughness of airport run-way is required for the analysis of aircraft vibration caused by the roughness.

Currently, there are several methods available to numerically represent those random phenomena. Most of these methods are based on Monte Carlo simulation [@Spanos_Monte_1998; @Kareem_Numerical_2008]  which can be achieved by frequency domain approaches such as linear filtering [@Yousun_ARMA_1990; @George_AutoRegressive_1988; @MIGNOLET_ARMA_1987] approaches or spectral representation method [@Lizhong_Adeterministic_2004; @Yousun_Simulation_1991; @Shinozuka_Digital_1972; @Mircea_Onthespectral_1993; @Koffi_Anefficient_2016; @Koffi_Improved_2018; @Koffi_Simulation_2017]. From the previous studies, the complexity associated with these methods are undoubtable. The application of these methods generally results in a time-consuming task due to the significantly large number of processes that is simulated. This can even lead to a higher demand in terms of computer memory. In the recent years, effort has been made to provide these issues with suitable solutions. However, almost all the solutions involve complex mathematical tool and physics which make their implementations in a computation program very difficult and time consuming.

It has been noticed that computer programs that offer suitable features for the computation works related to the numerical simulation of random phenomena are very few. In most cases, the simulation approach is implemented in the commercial software such as MATLAB which is a very powerful tool that offers number of solutions in numerical computation. The numerical simulation of random phenomena using Matlab requires some programming skills. It may be time consuming to be involved with programming tasks each time a simulation is required. We observed that researchers, who often build upon the works of other researchers during the study of new simulation approaches, frequently invest significant time and effort merely to replicate the existing computational results. Reproducing computational research presents challenges in this field. A well-designed computer program that makes scientific computations reproducible, storageble and accessible will be of a big benefit. A program that helps researchers and engineers to implement quickly new simulation approaches without having to implement or to understand the programming background of the existing simulation approaches is needed. To address these problems, we developed LabRPS, a plugin-based system designed to facilitate the implementation, storage, and access of simulation algorithm source codes and binaries in order to accelerate the development of new simulation algorithms in this field. Additionally, LabRPS features an intuitive user interface that enables users to numerically simulate random phenomena without the need for coding.

# 2. Programming Language

LabRPS leverages the strengths of both C++ and Python, providing a powerful and flexible environment that benefits from the performance of C++ and the ease of use and rapid development capabilities of Python. This combination offers significant advantages, making LabRPS a versatile tool for both professional developers and casual users.

# 3. Workbench Framework 

In LabRPS, a Workbench is a set of tools, features, and functions that are organized based on specific tasks or workflows. Each workbench in LabRPS is tailored to a particular aspect of the simulation process, providing an optimized interface for users working on a particular type of random phenomenon. The workbench concept allows users to switch between different tools depending on the stage or needs of the simulation. Examples of LabRPS Workbenches:

- **[WindLab Workbench:](https://wiki.labrps.com/WindLab_Workbench)** Focuses the simulation of random wind velocity
- **[SeismicLab Workbench:](https://wiki.labrps.com/SeismicLab_Workbench)** For the simulation of seismic ground motion
- **[SeaLab Workbench:](https://wiki.labrps.com/SeaLab_Workbench)** Enables users to simulate random sea surface elevation

By switching between workbenches, users can tackle different aspects of a simulation more effectively, providing a tailored and efficient workflow for diverse simulation tasks.

# 4. Plugin System 

LabRPS is a highly modular and flexible software platform, structured around a system of workbenches, each designed to cater to specific tasks or workflows in the simulation of random phenomena. These workbenches, which form the core of LabRPS, are composed of plugins which are individual, reusable components that provide specific functionality within each workbench.

By organizing the software into workbenches and plugins, LabRPS enables efficient, task specific customization, providing users with the flexibility to expand the software’s capabilities as required. Plugins can be easily integrated into existing workbenches, allowing for quick implementation of new methods or algorithms without disrupting the overall structure of the software. This architecture ensures that LabRPS remains a powerful yet accessible tool for diverse users with varying needs, from academic researchers developing new simulation techniques to industry professionals seeking realistic numerical models of random phenomena.

![Plugin System\label{fig:figure2}](Figures/Figure2.png)

# 5. LabRPS Scripting 

LabRPS scripting using Python is a powerful way to automate and customize your simulation process, especially for parametric features and repetitive tasks. Whether you're a hobbyist or a professional, understanding scripting opens up endless possibilities for enhancing your LabRPS experience.

![LabRPS Scripting\label{fig:figure3}](Figures/Figure3.png)

# Resources

* Official Website: [https://labrps.com](https://labrps.com)
* Documentation: [https://wiki.labrps.com](https://wiki.labrps.com)
* Download Page: [https://sourceforge.net/projects/labrps](https://sourceforge.net/projects/labrps)
* Plugin API Documentation: [https://api.labrps.com](https://api.labrps.com)
* Community Forum: [https://labrps.com/boards](https://labrps.com/boards)
* Tutorials: [https://wiki.labrps.com/Tutorials](https://wiki.labrps.com/Tutorials)
* Plugins: [https://wiki.labrps.com/Plugins](https://wiki.labrps.com/Plugins)
* Add your Research: [https://wiki.labrps.com/Plugin_Creation](https://wiki.labrps.com/Plugin_Creation)

# Acknowledgements

We would like to express our sincere gratitude to Siyu Zhu from the College of Environment and Civil Engineering at Chengdu University of Technology, China, for his insightful suggestions and thorough review. We also wish to thank Williams Adilehou and Hermann Sakponou for their continuous support throughout the development of this project.

# References