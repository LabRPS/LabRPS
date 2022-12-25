
#include "CholeskyDecomposition.h"
#include "RPSWindLabFramework.h"
#include <QMessageBox>
#include "../../libraries/rpsTools/rpsTools/src/general/CholeskyDecomposition.h"

bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorF(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    ObjectDescription description = CRPSWindLabFramework::getFrequencyDistributionObjDescription(Data.freqencyDistribution);
//    if(NULL == description)
//    {
//        strinformation.append("Invalid frequency distribution. The computation fails.")
//    }
    
    if(Data.freqencyDistribution != "Double Index Frequency" || description.m_pluginName != "windLab" || description.m_publicationAuthor != "Koffi Daniel")
    {
        strInformation.append("Computation fails. This method requires the double index frequency distribution from the windLab plugin created by Koffi Daneil");
        return false;
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
        return false;
    }

    const double dTime = Data.maxTime + Data.timeIncrement * Data.timeIndex;


    bool returnResult = CRPSWindLabFramework::ComputeLocationCoordinateMatrixP3(Data, dLocCoord, strInformation);
    if(!returnResult)
    {
       strInformation.append("The computation of the location coordinates matrix has failed.") ;
       return false;
    }

    for (int m = 1; m <= n && false == Data.isInterruptionRequested && true == returnResult; m++)
    {
        for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
        {
            returnResult = CRPSWindLabFramework::ComputeFrequencyValue(Data, frequencies(l - 1, m-1), m-1, l - 1, strInformation);
        }
    }

    if(!returnResult)
    {
       strInformation.append("The computation of the frequencies matrix has failed.") ;
       return false;
    }

    dVarVector = frequencies;

    for (int i = 1; i <= n && false == Data.isInterruptionRequested && true == returnResult; i++)
    {
        // Simulation starts
        for (int l = 1; l <= N && false == Data.isInterruptionRequested && true == returnResult; l++)
        {
            for (int j = 1; j <= n && false == Data.isInterruptionRequested && true == returnResult; j++)
            {
                // compute auto spectrum Sj(w)
                returnResult = CRPSWindLabFramework::ComputeAutoSpectrumValue(Data,
                                                               PSD1(j-1, l-1),
                                                               dLocCoord(j-1,0),
                                                               dLocCoord(j-1,1),
                                                               dLocCoord(j-1,2),
                                                               frequencies(l - 1,j-1),
                                                               dTime,
                                                               strInformation);

                returnResult = CRPSWindLabFramework::ComputeCrossCoherenceValue(Data, Kz(j-1, i-1, l-1),
                                                            dLocCoord(j-1,0),
                                                            dLocCoord(j-1,1),
                                                            dLocCoord(j-1,2),
                                                            dLocCoord(i-1,0),
                                                            dLocCoord(i-1,1),
                                                            dLocCoord(i-1,2),
                                                            frequencies(l - 1,i-1),
                                                            dTime,
                                                            strInformation);


                PSD2(j-1, i-1, l-1) = sqrt(PSD1(j-1, l-1)*PSD1(i-1, l-1))*Kz(j-1, i-1, l-1);

                PSD3(j-1, i-1) = PSD2(j-1, i-1, l-1);

            }

            returnResult = CRPSWindLabFramework::ComputeDecomposedCrossSpectrumMatrixPP(Data, PSD4, PSD3, strInformation);

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
            dVarVector(l-1) = frequencies(l - 1,Data.locationJ);
            dValVector(l-1) = PSD(Data.locationJ, Data.locationK, l-1);
        }
    }

    if(!returnResult)
    {
       strInformation.append("The computation of the spectrum matrix has failed.") ;
       return false;
    }

    return true;
}

bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumVectorT(const CRPSWindLabsimuData &Data, vec &dVarVector, vec &dValVector, QStringList &strInformation)
{
    return false;
}
bool CCholeskyDecomposition::ComputeDecomposedCrossSpectrumMatrixPP(const CRPSWindLabsimuData &Data, mat &dCPSDDecomMatrix, mat &dPSDMatrix, QStringList &strInformation)
{
    rps::General::CholeskyDecomposition decomposition;
    decomposition.computeCholeskyDecomposition(dPSDMatrix, dCPSDDecomMatrix);
return true;
}
bool CCholeskyDecomposition::OnInitialSetting(const CRPSWindLabsimuData &Data, QStringList &strInformation)
{
    QMessageBox::warning(0, "Cholesky Decomposition", "Please, note that the lower triangular matrix will be computed.");
    return true;
}

bool CCholeskyDecomposition::ComputeDecomposedPSDValue(const CRPSWindLabsimuData &Data, double &dValue, const double &dLocationJxCoord, const double &dLocationJyCoord, const double &dLocationJzCoord, const double &dLocationKxCoord, const double &dLocationKyCoord, const double &dLocationKzCoord, const double &dFrequency, const double &dTime, QStringList &strInformation)
{
    strInformation.append("ComputeDecomposedPSDValue function is not implemented.");
    return false;
}
