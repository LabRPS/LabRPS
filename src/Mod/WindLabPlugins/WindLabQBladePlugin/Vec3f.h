/**********************************************************************

    Copyright (C) 2016 David Marten <david.marten@qblade.org>

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

#include <math.h>
#include "Vec3.h"
#include <qglobal.h>

#ifndef VEC3F_H
#define VEC3F_H


class Vec3i
{
public:
    qint16 x;
    qint16 y;
    qint16 z;

    Vec3i(){
        x  = 0.0;
        y  = 0.0;
        z  = 0.0;
    }

    void serialize();
};

class Vec3f
{
public:
    float x;
    float y;
    float z;

    void serialize();
    void serializeCompressed(float intercept, float slope);

    Vec3f(){
        x  = 0.0;
        y  = 0.0;
        z  = 0.0;
    }

    Vec3f(float const &xi, float const &yi, float const &zi){
        x  = xi;
        y  = yi;
        z  = zi;
    }

    bool operator ==(Vec3f const &V){
        return (V.x-x)*(V.x-x) + (V.y-y)*(V.y-y) + (V.z-z)*(V.z-z)<0.000000001;
    }

    void operator =(Vec3f const &T){
        x = T.x;
        y = T.y;
        z = T.z;
    }

    void operator =(Vec3 const &T){
        x = T.x;
        y = T.y;
        z = T.z;
    }

    void operator+=(Vec3f const &T){
        x += T.x;
        y += T.y;
        z += T.z;
    }

    void operator+=(Vec3 const &T){
        x += T.x;
        y += T.y;
        z += T.z;
    }

    void operator-=(Vec3f const &T){
        x -= T.x;
        y -= T.y;
        z -= T.z;
    }

    void operator-=(Vec3 const &T){
        x -= T.x;
        y -= T.y;
        z -= T.z;
    }

    void operator*=(float const &d){
        x *= d;
        y *= d;
        z *= d;
    }

    Vec3f operator *(float const &d){
        Vec3f T(x*d, y*d, z*d);
        return T;
    }

    Vec3f operator *(Vec3f const &T){
        Vec3f C;
        C.x =  y*T.z - z*T.y;
        C.y = -x*T.z + z*T.x;
        C.z =  x*T.y - y*T.x;
        return C;
    }

    Vec3f operator /(float const &d){
        Vec3f T(x/d, y/d, z/d);
        return T;
    }

    Vec3f operator +(Vec3f const &V){
        Vec3f T(x+V.x, y+V.y, z+V.z);
        return T;
    }

    Vec3f operator -(Vec3f const &V){
        Vec3f T(x-V.x, y-V.y, z-V.z);
        return T;
    }

    void Copy(Vec3f const &V){
        x = V.x;
        y = V.y;
        z = V.z;
    }

    void Set(float const &x0, float const &y0, float const &z0){
        x = x0;
        y = y0;
        z = z0;
    }

    void Set(Vec3f const &V){
        x = V.x;
        y = V.y;
        z = V.z;
    }

    void Normalize(){
        float abs = VAbs();
        if(abs< 1.e-10) return;
        x/=abs;
        y/=abs;
        z/=abs;
    }

    float VAbs(){
        return sqrtf(x*x+y*y+z*z);
    }

    float dot(Vec3f const &V){
        return x*V.x + y*V.y + z*V.z;
    }

    bool IsSame(Vec3f const &V){
        return (V.x-x)*(V.x-x) + (V.y-y)*(V.y-y) + (V.z-z)*(V.z-z)<0.000000001;
    }

    void Translate(Vec3f const &T){
        x += T.x;
        y += T.y;
        z += T.z;
    }

    //other methods
    void Rotate(Vec3f &O, Vec3f const &R, double Angle);
    void RotateN(Vec3f n, float NTilt);
    void RotateX(Vec3f const &O, float XTilt);
    void RotateY(Vec3f const &O, float YTilt);
    void RotateZ(Vec3f const &O, float ZTilt);
    void RotateY(float YTilt);
    void RotZ(float ZTilt);
    void RotY(float YTilt);

};

#endif //VEC3F_H
