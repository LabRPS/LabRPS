#include "untitled3.h"
#include "RPS.h"
Untitled3::Untitled3()
{
}

QString Untitled3::print()
{
    mat matr(3,3);
    matr(0,0) = 4;
    QString stringvalue = QString::number(matr(0,0));
    return stringvalue;
}