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
#include "Vec3f.h"
#include "Quaternion.h"


void Vec3i::serialize(){

}

void Vec3f::serialize(){
 
}

void Vec3f::serializeCompressed(float intercept, float slope){

   
}

void Vec3f::Rotate(Vec3f &O, Vec3f const &R, double Angle){

    Quaternion qt;
    qt.set(Angle, R);
    Vec3f OP;
    OP.x = x-O.x;
    OP.y = y-O.y;
    OP.z = z-O.z;
    qt.conj(OP);
    x = O.x + OP.x;
    y = O.y + OP.y;
    z = O.z + OP.z;
}

void Vec3f::RotateN(Vec3f n, float NTilt){

    Vec3f r;
    n.Normalize();
    r=Vec3f(x,y,z);
    r = n*(n.dot(r))+(n*r)*n*cos(NTilt/180*PI_)+(n*r)*sin(NTilt/180*PI_);
    x=r.x;
    y=r.y;
    z=r.z;

}

void Vec3f::RotateX(Vec3f const &O, float XTilt){

    Vec3f OP;
    OP.x = x-O.x;
    OP.y = y-O.y;
    OP.z = z-O.z;

    XTilt *=PI_/180.0;
    y = O.y + OP.y * cos(XTilt) - OP.z * sin(XTilt);
    z = O.z + OP.y * sin(XTilt) + OP.z * cos(XTilt);
}

void Vec3f::RotateY(Vec3f const &O, float YTilt){

    Vec3f OP;
    OP.x = x-O.x;
    OP.y = y-O.y;
    OP.z = z-O.z;

    YTilt *=PI_/180.0;

    x = O.x + OP.x * cos(YTilt) + OP.z * sin(YTilt);
    z = O.z - OP.x * sin(YTilt) + OP.z * cos(YTilt);
}

void Vec3f::RotateZ(Vec3f const &O, float ZTilt){

    Vec3f OP;
    OP.x = x-O.x;
    OP.y = y-O.y;
    OP.z = z-O.z;

    ZTilt *=PI_/180.0;

    x = O.x + OP.x * cos(ZTilt) + OP.y * sin(ZTilt);
    y = O.y - OP.x * sin(ZTilt) + OP.y * cos(ZTilt);
}

void Vec3f::RotZ(float ZTilt){

    Vec3f OP;
    OP.x = x;
    OP.y = y;

    x =  OP.x * cos(ZTilt) - OP.y * sin(ZTilt);
    y =  OP.x * sin(ZTilt) + OP.y * cos(ZTilt);
}

void Vec3f::RotY(float YTilt){

    Vec3f OP;
    OP.x = x;
    OP.z = z;

    x =  OP.x * cos(YTilt) + OP.z * sin(YTilt);
    z = -OP.x * sin(YTilt) + OP.z * cos(YTilt);
}

void  Vec3f::RotateY(float YTilt){

    YTilt *=PI_/180.0;

    float xo = x;
    float zo = z;
    x =  xo * cos(YTilt) + zo * sin(YTilt);
    z = -xo * sin(YTilt) + zo * cos(YTilt);
}
