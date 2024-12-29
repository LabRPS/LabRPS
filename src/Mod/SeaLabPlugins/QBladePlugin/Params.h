/**********************************************************************

    Copyright (C) 2010 David Marten <david.marten@qblade.org>

    This program is licensed under the Academic Public License
    (APL) v1.0; You can use, redistribute and/or modify it in
    non-commercial academic environments under the terms of the
    APL as published by the QBlade project; See the file 'LICENSE'
    for details; Commercial use requires a commercial license
    (contact info@qblade.org).

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

***********************************************************************/

#ifndef PARAMS_H
#define PARAMS_H

//General
#define PI_                     3.14159265358979323846
#define KINVISCAIR              1.647e-05
#define DENSITYAIR              1.225
#define KINVISCWATER            1.307e-6
#define DENSITYWATER            1025
#define GRAVITY                 9.80665
#define TINYVAL                 1.0e-10
#define ZERO_MASS               1.0e-5

#define BRIGHTGREY              0.8
#define LIGHTGREY               0.75
#define DARKGREY                0.55

#define MAXRECENTFILES          8
#define VERSIONNUMBER           310005
#define COMPATIBILITY           310000

#define arraySizeTUB            550
#define arraySizeBLADED         550
#define arraySizeDTU            100

// Applications
#define BLADEVIEW               33
#define BEM                     9
#define BEMSIMVIEW              32
#define POLARVIEW               31
#define TURBINEVIEW             34
#define CHARSIMVIEW             35
#define CHARPROPSIMVIEW         36
#define PROPSIMVIEW             37
#define SECTIONHIGHLIGHT        1420
#define INNERGEOM               1429
#define DMS                     10
#define WINDFIELDMODULE         4299
#define TURDMSMODULE            4301
#define DMSMULTIMODULE          4302
#define NOISEMODULE             4303
#define ROTDMSMODULE            4304
#define VAWTDESIGNMODULE        4305
#define BEMROTMODULE            4307
#define BEMTURMODULE            4308
#define QFEMMODULE              4400
#define STRMODULE               4405
#define LLTMULTIMODULE          4406
#define QTURBINEMODULE          4407
#define WINGDESIGNER            4410
#define PLANEDESIGNER           4409
#define QFLIGHTMODULE           4408
#define WAVEMODULE              4411
#define FOILMODULE              4412
#define POLARMODULE             4413

//GL
#define VLMSTREAMLINES          1220
#define WINGSURFACES            1300
#define AFCSURFACES             1301
#define DAMAGESURFACES          1302
#define WINGVAWT                232323
#define OUTLINEVAWT             242424
#define TOPSURFACES             1310
#define BOTTOMSURFACES          1311
#define WINGOUTLINE             1304
#define WING2OUTLINE            1305
#define GLWINGWAKEPANELS        1383
#define GLSTRUCTMODEL           1384
#define ICEPARTICLES            1385
#define GLBODYMESHPANELS        1402
#define GLBLADEOUTLINES         1411
#define GLWINDFIELD             1415
#define GLBLADESURFACES         1416
#define GLTURBINESURFACES       1417
#define GLSTRMODEL              1418
#define GLCOORDS                1419
#define GLGRIDS                 1430
#define GLENVIRONMENT           1431
#define GLMOORINGS              1433
#define GLVMSTRESSES            4555
#define GLCUTPLANESETUP         4556
#define GLCUTPLANES             4557
#define GLWAVE                  4558

//3D analysis parameters
#define MAXBLADESTATIONS        200
//Airfoil Parameters
#define IQX                     302
#define IBX                     604

#endif // PARAMS_H
