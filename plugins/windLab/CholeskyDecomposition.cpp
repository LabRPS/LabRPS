
#include "CholeskyDecomposition.h"
#include "RPSWindLabTools.h"
#include "RPSWindLabFramework.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/general/CholeskyDecomposition.h"

void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dPSDVector, QStringList &strInformation)
{
    ObjectDescription description = CRPSWindLabFramework::getFrequencyDistributionObjDescription(Data.freqencyDistribution);
    if(Data.freqencyDistribution != "Double Index Frequency" || description.m_pluginName != "windLab" || description.m_publicationAuthor != "Koffi Daniel")
    {
        strInformation.append("Computation fails. This method requires the double index frequency distribution from the windLab plugin created by Koffi Daneil");
        return;
    }



    int n = Data.numberOfSpatialPosition                       ;
    int N = Data.numberOfFrequency                    ;
    mat PSD1;
    cube PSD2;
    mat PSD3;
    mat PSD4;
    cube PSD5;
    cube PSD;
    cube Kz;
    mat dLocCoord;
    mat frequencies;

    try
    {
        PSD1.setZero(n,N);
        PSD2.setZero();
        PSD3.setZero(n,n);
        PSD4.setZero(n,n);
        PSD5.setZero();
        PSD.setZero();
        Kz.setZero();
        dLocCoord.setZero(n, 3);
        frequencies.setZero(N,n);
    }
    catch (std::bad_alloc &ba)
    {
        QString msg(ba.what());
        strInformation.append(msg);
        return;
    }


    CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);


    for (int m = 1; m <= n && false == Data.isInterruptionRequested; m++)
    {
        for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
        {
            CRPSWindLabFramework::ComputeFrequencyValue(Data, frequencies(l - 1, m-1), m-1, l - 1, strInformation);
        }
    }

    for (int i = 1; i <= n && false == Data.isInterruptionRequested; i++)
    {
        // Simulation starts
        for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
        {
            for (int j = 1; j <= n && false == Data.isInterruptionRequested; j++)
            {
                // compute auto spectrum Sj(w)
                CRPSWindLabFramework::ComputeAutoSpectrumValue(Data,
                                                               PSD1(j-1, l-1),
                                                               dLocCoord(j-1,0),
                                                               dLocCoord(j-1,1),
                                                               dLocCoord(j-1,2),
                                                               frequencies(l - 1,j-1),
                                                               0,
                                                               strInformation);

                CRPSWindLabFramework::ComputeCoherenceValue(Data, Kz(j-1, i-1, l-1),
                                                            dLocCoord(j-1,0),
                                                            dLocCoord(j-1,1),
                                                            dLocCoord(j-1,2),
                                                            dLocCoord(i-1,0),
                                                            dLocCoord(i-1,1),
                                                            dLocCoord(i-1,2),
                                                            frequencies(l - 1,i-1),
                                                            0,
                                                            strInformation);


                PSD2(j-1, i-1, l-1) = sqrt(PSD1(j-1, l-1)*PSD1(i-1, l-1))*Kz(j-1, i-1, l-1);

                PSD3(j-1, i-1) = PSD2(j-1, i-1, l-1);

            }

            CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, PSD4, PSD3, strInformation);

            for (int j = 1; j <= n && false == Data.isInterruptionRequested; j++)
            {
                for (int m = 1; m <= n && false == Data.isInterruptionRequested; m++)
                {

                    PSD5(j-1, m-1, l-1) =  PSD4(j-1, m-1);
                }

                PSD(j-1, i-1, l-1) =  PSD5(j-1, i-1, l-1);
            }

        }

        for (int l = 1; l <= N && false == Data.isInterruptionRequested; l++)
        {
            dPSDVector(l-1) = PSD(Data.locationJ, Data.locationK, l-1);
        }
    }
}
void CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
    rps::General::CholeskyDecomposition decomposition;
    decomposition.computeCholeskyDecomposition(dPSDMatrix, dCPSDDecomMatrix);
}
bool CCholeskyDecomposition::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    QMessageBox::warning(0, "Cholesky Decomposition", "Please, note that the lower triangular matrix will be computed.");
    return true;
}

void CCholeskyDecomposition::ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    strInformation.append("ComputeDecomposedPSDValue function is not implemented.");
}
