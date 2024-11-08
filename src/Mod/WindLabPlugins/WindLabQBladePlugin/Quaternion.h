/**********************************************************************

    Copyright (C) 2012 David Marten <david.marten@qblade.org>

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

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vec3.h"
#include "Vec3f.h"

#define PI_ 3.14159265358979323846

class Quaternion
{

public:

    Quaternion(){
		a=0.0; qx= 0.0; qy=0.0; qz = 0.0;
        ang_rad = 0.0; setmat();
    }

    void conj(Vec3 &vec){

        v.x = vec.x; v.y = vec.y; v.z = vec.z;
        vec.x = 2.0*( (m8 + m10)*v.x + (m6 -  m4)*v.y + (m3 + m7)*v.z ) + v.x;
        vec.y = 2.0*( (m4 +  m6)*v.x + (m5 + m10)*v.y + (m9 - m2)*v.z ) + v.y;
        vec.z = 2.0*( (m7 -  m3)*v.x + (m2 +  m9)*v.y + (m5 + m8)*v.z ) + v.z;
    }

    void conj(Vec3f &vec){
        v.x = vec.x; v.y = vec.y; v.z = vec.z;
        vec.x = 2.0*( (m8 + m10)*v.x + (m6 -  m4)*v.y + (m3 + m7)*v.z ) + v.x;
        vec.y = 2.0*( (m4 +  m6)*v.x + (m5 + m10)*v.y + (m9 - m2)*v.z ) + v.y;
        vec.z = 2.0*( (m7 -  m3)*v.x + (m2 +  m9)*v.y + (m5 + m8)*v.z ) + v.z;
    }

    void conj(double &x, double &y, double &z){
        v.x = x; v.y = y; v.z = z;
        x = 2.0*( (m8 + m10)*v.x + (m6 -  m4)*v.y + (m3 + m7)*v.z ) + v.x;
        y = 2.0*( (m4 +  m6)*v.x + (m5 + m10)*v.y + (m9 - m2)*v.z ) + v.y;
        z = 2.0*( (m7 -  m3)*v.x + (m2 +  m9)*v.y + (m5 + m8)*v.z ) + v.z;
    }
	
    void setmat(){
        m2 =   a*qx;  m3 =   a*qy;  m4 =   a*qz;
        m5 =  -qx*qx; m6 =   qx*qy; m7 =   qx*qz;
        m8 =  -qy*qy; m9 =   qy*qz; m10 = -qz*qz;
    }

    void set(double const &ang_deg, Vec3 const &v){
        Vec3 n = v; n.Normalize();
        ang_rad = ang_deg*PI_/180.0;
        a = cos(ang_rad/2.0);
        double sina = sin(ang_rad/2.0);

        qx = n.x*sina; qy = n.y*sina; qz = n.z*sina;
        setmat();
    }

    void set(double const &ang_deg, Vec3f const &v){
        Vec3f n = v; n.Normalize();
        ang_rad = ang_deg*PI_/180.0;
        a = cos(ang_rad/2.0);
        double sina = sin(ang_rad/2.0);

        qx = n.x*sina; qy = n.y*sina; qz = n.z*sina;
        setmat();
    }

private:
    double ang_rad;
    double m2, m3, m4, m5, m6, m7, m8, m9, m10;
    Vec3 v;
    double a,qx,qy,qz;


};
#endif
