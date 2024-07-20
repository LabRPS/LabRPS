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

#ifndef QBLADE_GLOBALS_H
#define QBLADE_GLOBALS_H

#include <QString>
#include <QVector>
#include <QRegularExpression>

class QTextStream;
class QColor;


class DummyAssociatedObject
{
public:
    //this is used for curves that dont belong to an object
    DummyAssociatedObject() {}
    QString getObjectName() { return QString(); }
};

bool ReadAVLString(QTextStream& in, int& Line, QString& strong);
void ReadValues(QString line, int& res, double& x, double& y, double& z);
void ReynoldsFormat(QString& str, double f);

void ReadCString(QDataStream& ar, QString& strong);
void WriteCString(QDataStream& ar, QString const& strong);
void ReadCOLORREF(QDataStream& ar, QColor& color);
void WriteCOLORREF(QDataStream& ar, QColor const& color);

Qt::PenStyle GetStyle(int s);
int GetStyleRevers(Qt::PenStyle s);

enum GuiMode
{
    HAWT_MODE,
    VAWT_MODE,
    PROP_MODE,
    FLIGHT_MODE
};
enum Unit
{
    NONE,
    LENGTH,
    AREA,
    WEIGHT,
    SPEED,
    FORCE,
    MOMENT,
    POWER,
    PERCENT
};
enum StructuralModel
{
    NO_STRUCT,
    CHRONO
};
enum ControllerType
{
    NO_CONTROLLER,
    BLADED,
    DTU,
    TUB
};
enum WindType
{
    UNIFORM,
    WINDFIELD,
    HUBHEIGHT
};
enum WindProfileType
{
    POWERLAW,
    LOGARITHMIC
};
enum WakeIntegration
{
    EULER,
    PC,
    PC2B
};
enum DynamicStall
{
    NO_DS,
    OYE,
    GORMONT,
    ATEFLAP
};
enum WakeCountType
{
    WAKE_REVS,
    WAKE_STEPS
};
enum WakeType
{
    VORTEX,
    U_BEM
};
enum OmegaPrescribeType
{
    PRECOMP_PRESCRIBED,
    ALL_PRESCRIBED,
    NONE_PRESCRIBED
};
enum WakeConvectionType
{
    LOCALMEAN,
    HHMEAN,
    LOCALTURB
};
enum WaveFrequencySpectrum
{
    IMP_TIMESERIES,
    IMP_COMPONENTS,
    SINGLE,
    JONSWAP,
    ISSC,
    TORSETHAUGEN,
    OCHI_HUBBLE,
    IMP_SPECTRUM
};
enum WaveDiscretization
{
    EQUAL_ENERGY,
    EQUAL_FREQUENCY,
    GEOM_PROGRESSION
};
enum WaveDirectionalSpectrum
{
    UNIDIRECTIONAL,
    COSINE
};
enum WaveStretching
{
    VERTICAL,
    WHEELER,
    EXTRAPOLATION,
    NOSTRETCHING
};
enum PotFlowType
{
    BEMUSE,
    NEMOH,
    WAMIT
};
enum WaveKinEvalType
{
    LOCALEVAL,
    REFEVAL,
    LAGGEDEVAL
};

enum WindInputType1
{
    NTM_1,
    ETM_1,
    EWM1T_1,
    EWM50T_1,
    EWM1S_1,
    EWM50S_1,
    EOG50_1,
    EDC_1,
    ECD_1,
    EWS_1,
    NWP_1
};
enum WindInputType2
{
    NTM_2,
    EWM1S_2,
    EWM50S_2,
    EOG1_2,
    EOG50_2,
    EDC1_2,
    EDC50_2,
    ECG_2,
    ECD_2,
    NWP_2
};
enum WindInputType3
{
    NTM_3,
    ETM_3,
    EWM1T_3,
    EWM50T_3,
    EWM1S_3,
    EWM50S_3,
    EOG_3,
    EDC_3,
    ECD_3,
    EWS_3,
    NWP_3
};
enum GraphArrangement
{
    ONEGRAPH,
    TWOGRAPHS_H,
    TWOGRAPHS_V,
    THREEGRAPHS_V,
    FOURGRAPHS_H,
    FOURGRAPHS_V,
    SIXGRAPHS_H,
    SIXGRAPHS_V,
    EIGHTGRAPHS_H,
    EIGHTGRAPHS_V
};

enum TurbineClass
{
    CLASS_I,
    CLASS_II,
    CLASS_III,
    CLASS_S
};
enum TurbulenceClass
{
    CLASS_A,
    CLASS_B,
    CLASS_C,
    CLASS_TS
};
enum IntegratorType
{
    HHT,
    EI_LIN,
    EI_PRO,
    EI
};
enum DLC1
{
    DLC1_11,
    DLC1_12,
    DLC1_13,
    DLC1_14,
    DLC1_15,
    DLC1_21,
    DLC1_22,
    DLC1_23,
    DLC1_24,
    DLC1_31,
    DLC1_32,
    DLC1_33,
    DLC1_41,
    DLC1_42,
    DLC1_51,
    DLC1_61t,
    DLC1_61s,
    DLC1_62t,
    DLC1_62s,
    DLC1_63t,
    DLC1_63s,
    DLC1_64,
    DLC1_71s,
    DLC1_71t,
    CUSTOM1,
    SP1
};
enum DLC2
{
    DLC2_11,
    DLC2_12,
    DLC2_13,
    DLC2_14,
    DLC2_15,
    DLC2_21,
    DLC2_22,
    DLC2_23,
    DLC2_31,
    DLC2_32,
    DLC2_41,
    DLC2_51t,
    DLC2_51s,
    DLC2_52,
    DLC2_61t,
    DLC2_61s,
    CUSTOM2,
    SP2
};

enum IEC
{
    IEC61400_1Ed2,
    IEC61400_1Ed3,
    IEC61400_2Ed2,
    IEC61400_3_1Ed1,
    IEC61400_3_2Ed1,
    STEADY_POWER,
    PRESCRIBED_RPM
};
enum SPECTRAL
{
    IECKAI,
    IECVKM,
    GP_LLJ,
    NWTCUP,
    SMOOTH,
    WF_UPW,
    WF_07D,
    WF_14D,
    TIDAL,
    NONN
};
enum ProfileType
{
    PL,
    LOG,
    H2L,
    JET,
    IEC
};

extern QString g_ChronoVersion;
extern QString g_VersionName;
extern QString g_applicationDirectory;
extern QString g_xfoilPath;
extern QString g_turbsimPath;
extern QString g_controllerPath;
extern QString g_tempPath;
extern bool debugSimulation;
extern bool debugStores;
extern bool debugStruct;
extern bool debugSerializer;
extern bool debugTurbine;
extern bool debugController;
extern bool uintRes;
extern bool uintVortexWake;
extern bool twoDAntiAliasing;
extern bool isGUI;
extern bool isWIN;
extern double kinViscAir;
//double globalLineAlpha;
extern QRegularExpression ANY_NUMBER;
extern QRegularExpression S_CHAR;

QString getUnitName(Unit unit);// wrappers for the super inconvenient functions
double getUnitFactor(Unit unit);

//color relates stuff
typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

hsv      rgb2hsv(rgb in);
rgb      hsv2rgb(hsv in);

#endif// QBLADE_GLOBALS_H
