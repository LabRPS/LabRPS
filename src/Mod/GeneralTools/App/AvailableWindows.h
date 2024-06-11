#ifndef RPSTOOL_AVAILABLEWINDOWS_H
#define RPSTOOL_AVAILABLEWINDOWS_H

#include "RPS.h"
#include <Mod/GeneralTools/GeneralToolsGlobal.h>

namespace rps {

namespace General {

class GeneralToolsExport AvailableWindows
{
public:
    AvailableWindows();
    ~AvailableWindows();

    void BartlettWindow(vec &win, int L);
    void BartlettHannWindow(vec &win, int L);
    void BlackmanWindow(vec &win, int L, int flag = 1);
    void BlackmanHarrisWindow(vec &win, int L, int flag = 1);
    void BohmanWindow(vec &win, int L);
    void ChebyshevWindow(vec &win, int L, double r = 100);
    void FatTopWindow(vec &win, int L, int flag = 1);
    void GaussianWindow(vec &win, int L, double alpha = 2.5);
    void HammingWindow(vec &win, int L, int flag = 1);
    void HannWindow(vec &win, int L, int flag = 1);
    void KaiserWindow(vec &win, int L, double beta = 0.5);
    void NuttallBlackmanHarrisWindow(vec &win, int L, int flag = 1);
    void ParzenWindow(vec &win, int L);
    void RectangularWindow(vec &win, int L);
    void TrapezedCosineWindow(vec &win, int L, double r = 0.5);
    void TriangularWindow(vec &win, int L);

    void BlackmanSymmetricWindow(vec &win, int L);
    void BlackmanHarrisWindow0(vec &win, int L, int flag);
    void FatTopWindow0(vec &win, int L, int flag);
    void HammingWindow0(vec &win, int L, int flag);
    void HannWindow0(vec &win, int L, int flag);
    void NuttallBlackmanHarrisWindow0(vec &win, int L, int flag);

};

}

}

#endif //RPSTOOL_AVAILABLEWINDOWS_H
